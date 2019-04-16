#ifndef CREATESKIN_HPP
#define CREATESKIN_HPP

#include <fstream>
#include <iostream>
#include <algorithm>
#include "mwTPoint3d.hpp"
#include "mwDiscreteFunction.hpp"
#include "WriteFile.hpp"
#include "Intersection.hpp"

void CreateSkin(	cadcam::mwTPoint3d<double> refPoint,
					unsigned long nx,
					unsigned long ny,
					unsigned long nz,
					double sphereRad,
					mwDiscreteFunction &func,
					double deltaT,
					double delta,
					const std::string &skinFileName );

#endif /* CREATESKIN_HPP */
