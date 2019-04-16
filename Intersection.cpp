#include "Intersection.hpp"

bool	Intersection::Cylinder(	const cadcam::mwTPoint3d<double> &testpt,
								const cadcam::mwTPoint3d<double> &p1,
								const cadcam::mwTPoint3d<double> &p2,
								const double &sphereSqRad)
{
	cadcam::mwTVector3d<double>	p21 = p2 - p1;				//!This is vector that describes cylinder orientation in space.
	double						cyli_length_sq = p21 * p21;	//!This value correspond to cylinder squared length.
	cadcam::mwTVector3d<double>	tp = testpt - p1;			//!This vector describe test point relative to cylinder (p1).
	double						dot = p21 * tp;				//!This value describe point projection on cylinder axis.

	if( dot <= 0.0 || dot >= cyli_length_sq)				//!Check if point lies between cylinder caps (excluding caps).
		return(false);
	else
	{														//!In case point is in the right perpendicular to cylinder axis plane
		double dsq = tp * tp - dot * dot / cyli_length_sq;	//!check distant between point and the axis.
		return (dsq <= sphereSqRad);
	}
}

bool	Intersection::Sphere(	const cadcam::mwTPoint3d<double> &test_point,
								const cadcam::mwTPoint3d<double> &sphere_center,
								const double &sphereSqRad)
{															//!Simply check distant from sphere center to the test point.
	return (test_point - sphere_center) * (test_point - sphere_center) <= sphereSqRad;
}
