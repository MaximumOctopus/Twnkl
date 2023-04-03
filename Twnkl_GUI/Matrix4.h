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

class Quaternion;

#include <string>

#include "Quaternion.h"


class Matrix4
{
public:

	double Data[4][4] = { {1.0, 0.0, 0.0, 0.0},
		                  {0.0, 1.0, 0.0, 0.0},
						  {0.0, 0.0, 1.0, 0.0},
		                  {0.0, 0.0, 0.0, 1.0} };

	// identity matrix
	Matrix4() noexcept;

	Matrix4(int, double) noexcept;

	Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double) noexcept;

	// scaling (0) or translation (1) matrix
	Matrix4(int, double, double, double) noexcept;

	// shearing matrix
	Matrix4(double, double, double, double, double, double) noexcept;

	[[nodiscard]] Quaternion MultQ(Quaternion&);
	[[nodiscard]] Matrix4 MultM(Matrix4&);

	void MultiplyBy(Matrix4&);

	[[nodiscard]] double Determinant();

	void Invert();
	[[nodiscard]] Matrix4 Inverse();

	[[nodiscard]] Matrix4 Transpose();

	[[nodiscard]] bool Equals(Matrix4&);

	[[nodiscard]] std::wstring ToString();
};