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

class Cube : public Object
{

	static std::pair<double, double> CheckAxis(double origin, double direction);

public:

	Cube(std::wstring);

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void PostSetup(int) override;

	[[nodiscard]] std::wstring ToString() override;

	void ToFile(std::ofstream& ofile) override;
};