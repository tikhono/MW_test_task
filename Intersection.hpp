#ifndef TEST_TASK_INTERSECTION_H
#define TEST_TASK_INTERSECTION_H

#include "mwTPoint3d.hpp"

class Intersection
{
	public:
		bool	static Cylinder(const cadcam::mwTPoint3d<double> &testpt,
								const cadcam::mwTPoint3d<double> &p1,
								const cadcam::mwTPoint3d<double> &p2,
								const double &sphereSqRad);

		bool	static Sphere  (const cadcam::mwTPoint3d<double> &test_point,
							 	const cadcam::mwTPoint3d<double> &sphere_center,
								const double &sphereSqRad);
};

#endif //TEST_TASK_INTERSECTION_H
