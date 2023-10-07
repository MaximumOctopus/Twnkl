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


class CubeTexture : public Pattern
{

	Colour UVColourAt(double, double);

public:

	std::wstring FileName = L"";

	Colour* Texture = nullptr;

	CubeTexture(bool, std::wstring);
	~CubeTexture();

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] std::wstring ToString() override;

	void ToFile(std::ofstream&) override;
};