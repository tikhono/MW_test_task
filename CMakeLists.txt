cmake_minimum_required(VERSION 3.13)
project(test_task)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-fopenmp")

include_directories(.)

add_executable(test_task
		CreateSkin.cpp
		CreateSkin.hpp
		cutSphereMove.cpp
		mwArcFunction.cpp
		mwArcFunction.hpp
		mwDiscreteFunction.hpp
		mwException.cpp
		mwException.hpp
		mwIdxRangeException.cpp
		mwIdxRangeException.hpp
		mwMathConstants.hpp
		mwTPoint3d.hpp WriteFile.cpp WriteFile.hpp Intersection.cpp Intersection.hpp)
