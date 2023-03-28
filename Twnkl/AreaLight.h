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
public:

	AreaLight(double, double, double, double, double, double);

	Quaternion PointOn(double, double) override;

	void SetDimensions(Quaternion, Quaternion, int);

	std::wstring ToString() override;
};