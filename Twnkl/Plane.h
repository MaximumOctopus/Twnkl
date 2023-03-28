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

#include "Object.h"

class Plane : public Object
{
public:

	Plane(std::wstring);

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void PostSetup(int) override;

	[[nodiscard]] std::wstring ToString() override;
};