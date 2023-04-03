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

class Cylinder : public Object
{

	bool Closed = false;
	double Minimum = 0.0;
	double Maximum = 0.0;

	static bool CheckCap(double, Ray&);
	void IntersectCaps(Intersections&, Ray&);

public:

	Cylinder(std::wstring);

	void SetParameters(int, int, bool);

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void PostSetup(int) override;

	[[nodiscard]] std::wstring ToString() override;
};