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


class CubeMultiTexture : public Pattern
{
	Colour UVColourAt(int, double, double);

public:

	std::wstring FileName = L"";

	Colour* Texture[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	
	CubeMultiTexture(bool, std::wstring);
	~CubeMultiTexture();

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] std::wstring ToString() override;

	void ToFile(std::ofstream&) override;
};