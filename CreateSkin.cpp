#include "CreateSkin.hpp"

template <typename T>
T	clamp(T val, T min, T max) {return (std::max(min, std::min(val, max)));}

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
	for (unsigned long i = 0; i < pos_count; i++)
	{
		points[i] = func.Evaluate(cur) - refPoint;
		cur += deltaT;
	}

	//!Creating two vectors of spheres boundaries mapped in points.
	cadcam::mwTVector3d<unsigned long> point_min[pos_count];
	#pragma parallel for
	for (unsigned long i = 0; i < pos_count; i++)
	{
		point_min[i].x(static_cast<unsigned long>(clamp(ceil(points[i].x() - sphereRad), 0.0, static_cast<double>(nx))));
		point_min[i].y(static_cast<unsigned long>(clamp(ceil(points[i].y() - sphereRad), 0.0, static_cast<double>(ny))));
		point_min[i].z(static_cast<unsigned long>(clamp(ceil(points[i].z() - sphereRad), 0.0, static_cast<double>(nz))));
	}

	cadcam::mwTVector3d<unsigned long> point_max[pos_count];
	#pragma parallel for
	for (unsigned long i = 0; i < pos_count; i++)
	{
		point_max[i].x(static_cast<unsigned long>(clamp(ceil(points[i].x() + sphereRad), 0.0, static_cast<double>(nx))));
		point_max[i].y(static_cast<unsigned long>(clamp(ceil(points[i].y() + sphereRad), 0.0, static_cast<double>(ny))));
		point_max[i].z(static_cast<unsigned long>(clamp(ceil(points[i].z() + sphereRad), 0.0, static_cast<double>(nz))));
	}

	//!Creating squared sphere radius for further calculation to avoid repeating recalculations.
	const double	sphereSqRad = sphereRad * sphereRad;

	//!Creating vector nx to ny with initial value as top point to store skin
	std::vector < std::vector <unsigned long> > skin(nx, std::vector<unsigned long>(ny, nz));

	//!Deleting points that intersect with spheres
	//!Iterating thru cube that contain sphere inside.
	for (unsigned long n = 0; n < pos_count; n++)
	{
		#pragma parallel for
		for (auto i = point_min[n].x(); i < point_max[n].x(); i++)
		{
			for (auto j = point_min[n].y(); j < point_max[n].y(); j++)
			{
				for (auto k = point_min[n].z(); k < point_max[n].z(); k++)
				{
					if (skin[i][j] < k)
						break;
					cadcam::mwTVector3d<double> testpoint(i * delta, j * delta, k * delta);
					if (Intersection::Sphere(testpoint, points[n], sphereSqRad))
						skin[i][j] = k - 1;
				}
			}
		}
	}

	//!Deleting points that intersect with cylinders
	//!Iterating thru prism that contain cylinder inside on one of diagonals.
	for (unsigned long n = 0; n < pos_count - 1; n++)
	{
		#pragma parallel for
		for (auto i = std::min(point_min[n].x(), point_min[n + 1].x()); i < std::max(point_max[n].x(), point_max[n + 1].x()); i++)
		{
			for (auto j = std::min(point_min[n].y(), point_min[n + 1].y()); j < std::max(point_max[n].y(), point_max[n + 1].y()); j++)
			{
				for (auto k = std::min(point_min[n].z(), point_min[n + 1].z()); k < std::max(point_max[n].z(), point_max[n + 1].z()); k++)
				{
					if (skin[i][j] < k)
						break;
					cadcam::mwTVector3d<double> testpoint(i * delta, j * delta, k * delta);
					if (Intersection::Cylinder(testpoint, points[n], points[n + 1], sphereSqRad))
						skin[i][j] = k - 1;
				}
			}
		}
	}
	WriteFile::to(skinFileName, nx, ny, nz, delta, skin);
}
