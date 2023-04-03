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


class Triangle : public Object
{



public:

	Quaternion Points[3];
	Quaternion e1;
	Quaternion e2;
	Quaternion Normal;

	Triangle(std::wstring);

	void SetPoints(Quaternion, Quaternion, Quaternion);
	void SetPointsWithNormal(Quaternion, Quaternion, Quaternion, Quaternion);

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void PostSetup(int) override;

	void Finalise();

	[[nodiscard]] std::wstring ToString() override;
};