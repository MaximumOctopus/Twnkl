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

#include "Noise.h"
#include "Pattern.h"


class Fractal : public Pattern
{

public:

	Noise* noize;

    Fractal(std::wstring);
	~Fractal();

	void SetFALP(double, double, double, double);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] virtual std::wstring ToString() override;

	void ToFile(std::ofstream&) override;
};