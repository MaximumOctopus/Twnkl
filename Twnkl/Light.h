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

#include "Colour.h"
#include "Quaternion.h"


class Light
{
public:

	int Samples = 0;

	Colour Intensity;
	Quaternion Position;			// position for point light
									// any corner of rectangle for area light
									// uvec and vvec define the two perpendicular components of the rectangle from the corner position

	Quaternion uvec;
	Quaternion vvec;
	int deltau = 0;
	int deltav = 0;

	int ID = 0;

	Light(double, double, double, double, double, double);

	virtual Quaternion PointOn(double, double);

	virtual std::wstring ToString();
};