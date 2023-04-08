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

class Cone : public Object
{

	bool Closed = false;
	double Minimum = 0.0;
	double Maximum = 0.0;

	[[nodiscard]] static bool CheckCap(double, double, Ray&);
	void IntersectCaps(Intersections&, Ray&);

public:

	Cone(std::wstring);

	void SetParameters(int, int, bool);

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void PostSetup(int) override;

	[[nodiscard]] std::wstring ToString() override;

	void ToFile(std::ofstream& ofile) override;
};