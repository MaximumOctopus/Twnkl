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

#include <string>

#include "Matrix4.h"
#include "Quaternion.h"


class Ray
{
public:

	Quaternion Origin;
	Quaternion Direction;

	Ray(Quaternion, Quaternion) noexcept;

	Ray(double, double, double, double, double, double) noexcept;

	[[nodiscard]] Quaternion Position(double);

	[[nodiscard]] Ray Transform(Matrix4&);
	[[nodiscard]] Ray Negate();

	[[nodiscard]] Quaternion NegativeDirection();

	[[nodiscard]] std::wstring ToString();
};