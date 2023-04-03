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

#include "Pattern.h"


class CylinderCheckerboard : public Pattern
{
	double Width = 0;
	double Height = 0;

	Colour UVColourAt(double, double);

public:

	CylinderCheckerboard(std::wstring);

	void SetDimensions(double, double);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] std::wstring ToString() override;
};