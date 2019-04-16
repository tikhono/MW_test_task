#include "CreateSkin.hpp"

void 	CreateSkin( const cadcam::mwTPoint3d<double> refPoint,
					const unsigned long nx, const unsigned long ny,
					const unsigned long nz, const double sphereRad,
					mwDiscreteFunction &func, const double deltaT,
					const double delta, const std::string &skinFileName )
{
	//!Creating array of sphere intermediate positions.
	double	start = func.GetBeginParameter();
	double	end = func.GetEndParameter();
	auto	pos_count = static_cast<unsigned long>((end - start) / deltaT);
	cadcam::mwTVector3d<double> points[pos_count];
	double	cur = start;
	for (int i = 0; i < pos_count; i++)
	{
		points[i] = func.Evaluate(cur);
		cur += deltaT;
	}

	//!Creating squared sphere radius for further calculation to avoid repeating recalculations.
	const double	sphereSqRad = sphereRad * sphereRad;

	//!creating vector to store skin
	std::vector < std::vector <unsigned long> > skin(nx, std::vector<unsigned long>(nx, ny));

	//!NOTE: if sphere moves thru bottom layer, this layer stays on place for better visualisation
	//!Each Z column starts at first point above bottom one to save bottom layer.

	//!Using OpenMP to parallelize calculation on maximum available CPU cores.
	#pragma omp parallel for
	for (unsigned long i = 0; i < nx; i++)
	{
		for (unsigned long j = 0; j < ny; j++)
		{
			for (unsigned long k = 1; k < nz; k++)
			{
				//!For reducing memory reads after finding skim point in Z column just start iterating next column.
				//!Due to restrictions of OpenMP every thread needs own testpoint.
				//!So, there small increasing of memory usage with testpoint copies.
				cadcam::mwTVector3d<double> testpoint(i * delta, j * delta, k * delta);
				bool isDeleted = false;
				for (unsigned long n = 0; n < pos_count; n++)
				{
					//!Every testpoint testing on intersection with cylinder and 2 spheres on cylinders caps.
					//!Second cap always first in next position, so it`s enough to check only first cap and cylinder.
					//!Ternary expression resolving problem with last position, where need to check only one cap.
					if ((n == pos_count - 1 ? false :
						Intersection::Cylinder(refPoint + testpoint, points[n], points[n + 1], sphereSqRad))
					||	Intersection::Sphere(refPoint + testpoint, points[n], sphereSqRad))
					{
						skin[i][j] = k - 1;
						isDeleted = true;
						break ;
					}
					else if (k == nz - 1)
					{
						skin[i][j] = k;
						break ;
					}
				}
				if (isDeleted)
					break;
			}
		}
	}
	//!After finding skim - just write it to the file.
	WriteFile::to(skinFileName, nx, ny, nz, delta, skin);
}
