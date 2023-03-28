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


class PlanarTexture : public Pattern
{
	Colour UVColourAt(double, double);
	std::pair<double, double> PlanarMap(Quaternion&);

public:

	Colour* Texture = nullptr;

	int Width = 0;
	int Height = 0;

	PlanarTexture(std::wstring);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] std::wstring ToString() override;
};