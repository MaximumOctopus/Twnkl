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
	Quaternion Position;

	Quaternion uvec;
	Quaternion vvec;
	int deltau = 0;
	int deltav = 0;

	int ID = 0;

	Light(double, double, double, double, double, double);

	virtual Quaternion PointOn(double, double);

	virtual std::wstring ToString();
};