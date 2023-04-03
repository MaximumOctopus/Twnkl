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

class Intersect;

#include <vector>

#include "Intersect.h"
#include "Ray.h"


class Intersections
{
public:

	std::vector<Intersect> List;

	Intersections() noexcept;

	void Sort();

	[[nodiscard]] int LowestNonNegative();
	[[nodiscard]] bool LowestNonNegativeLessDistance(double);

	[[nodiscard]] Computation PrepareComputation(int, Ray&);

	[[nodiscard]] std::wstring ToString();
};