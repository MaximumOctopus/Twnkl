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

// represents a single model, and obj, and group of tringles

#pragma once

#include "Bounds.h"
#include "Object.h"
#include "Trinion.h"
#include "Triangle.h"


class Model : public Object
{
	std::wstring FileName = L"";

	Bounds bounds;

	std::vector<Object*> Objects;

	Trinion VectorsFrom(const std::wstring, int);
	Quaternion XYZFrom(const std::wstring);

	void SetBounds(Triangle*);

public:

	Model(std::wstring);
	~Model();

	void LocalIntersect(Intersections&, Ray&) override;

	[[nodiscard]] Quaternion LocalNormalAt(Quaternion&) override;

	void PostSetup(int) override;

	void Load(std::wstring);

	[[nodiscard]] std::wstring ToString() override;

	void ToFile(std::ofstream& ofile) override;
};