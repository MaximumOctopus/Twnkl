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

#include <fstream>

#include "Colour.h"
#include "Constants.h"
#include "Formatting.h"
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

	std::wstring Name = L"";

	int ID = 0;

	Light(std::wstring, double, double, double, double, double, double);

	virtual Quaternion PointOn(double, double);

	virtual std::wstring ToString();

	virtual void ToFile(std::ofstream& ofile);
};