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


class Ring : public Pattern
{

public:

	Ring(bool, std::wstring);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] virtual std::wstring ToString() override;

	void ToFile(std::ofstream&) override;
};