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


class SmoothTriangle : public Object
{

public:

	Quaternion Points[3];
	Quaternion e1;
	Quaternion e2;
	Quaternion Normals[3];

	SmoothTriangle(std::wstring);

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void SetPointsNormals(Quaternion, Quaternion, Quaternion, Quaternion, Quaternion, Quaternion);

	void Finalise();

	void PostSetup(int) override;

	[[nodiscard]] std::wstring ToString() override;

	void ToFile(std::ofstream& ofile) override;
};