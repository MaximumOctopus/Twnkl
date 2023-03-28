//
// Twnkl 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
// 
// https://github.com/MaximumOctopus/Twnkl
// 
// 

#pragma once

class Object;

#include "Computation.h"
#include "Object.h"
#include "Ray.h"


class Intersect
{
public:

	double Tvalue = -1;
	Object* PObject = nullptr;
	double u = -1;
	double v = -1;

	Intersect() noexcept;

	Intersect(double, Object*) noexcept;

	Intersect(double, double, double, Object*) noexcept;
};