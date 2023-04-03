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

class Matrix4;

#include <string>

#include "Matrix4.h"

// w = 0 = vector, w = 1 = point 

class Quaternion
{

public:

	double x = 0;
	double y = 0;
	double z = 0;
	double w = 0;

	void Add(Quaternion&);
	void Sub(Quaternion&);
	[[nodiscard]] Quaternion SubQ(Quaternion&);
	void Negate();
	void Scale(double);
	Quaternion Mult(double);
	void Normalise();
	[[nodiscard]] double Dot(Quaternion&);
	[[nodiscard]] Quaternion Cross(Quaternion&, Quaternion&);
	[[nodiscard]] Quaternion Cross(Quaternion&);

	[[nodiscard]] Matrix4 ViewTransform(Quaternion&, Quaternion&);

	[[nodiscard]] Quaternion Reflect(Quaternion&);

	[[nodiscard]] double Magnitude();

	Quaternion() noexcept;

	Quaternion(double, double) noexcept;

	Quaternion(double, double, double, double) noexcept;

	[[nodiscard]] bool Equals(Quaternion&);

	[[nodiscard]] std::wstring ToString();
};