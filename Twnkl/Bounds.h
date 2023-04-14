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

#include "Matrix4.h"
#include "Quaternion.h"
#include "Ray.h"


class BoundingBox
{
	std::pair<double, double> CheckAxis(double, double, double, double);

public:

	Quaternion Minimum = Quaternion(999999, 999999, 999999, 999999);
	Quaternion Maximum = Quaternion(-999999, -999999, -999999, -999999);

	bool ContainsPoint(Quaternion);
	void Transform(Matrix4);
	bool Intersects(Ray&);
};