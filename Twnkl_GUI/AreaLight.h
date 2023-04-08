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
#include "Light.h"
#include "Quaternion.h"


class AreaLight : public Light
{
	Quaternion OriginalUVector;
	Quaternion OriginalVVector;

public:

	AreaLight(std::wstring, double, double, double, double, double, double);

	Quaternion PointOn(double, double) override;

	void SetDimensions(Quaternion, Quaternion, int);

	std::wstring ToString() override;

	void ToFile(std::ofstream& ofile) override;
};