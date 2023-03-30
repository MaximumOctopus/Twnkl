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


class CubeChecker : public Pattern
{
	int FaceFromPoint(Quaternion);

	std::pair<double, double> CubeUVFront(Quaternion&);
	std::pair<double, double> CubeUVBack(Quaternion&);
	std::pair<double, double> CubeUVLeft(Quaternion&);
	std::pair<double, double> CubeUVRight(Quaternion&);
	std::pair<double, double> CubeUVUp(Quaternion&);
	std::pair<double, double> CubeUVDown(Quaternion&);

	Colour UVColourAt(double, double);

public:

	int Width = 0;
	int Height = 0;

	CubeChecker(std::wstring);

	void SetDimensions(double, double);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] std::wstring ToString() override;
};