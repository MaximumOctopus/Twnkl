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


class Simplex : public Pattern
{
    Noise* noize;

public:

    bool Simple = false;

    Simplex(std::wstring);
    ~Simplex();

    [[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

    [[nodiscard]] virtual std::wstring ToString() override;
};