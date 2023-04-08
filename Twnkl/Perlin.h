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

// based on code from the second part of https://raytracing.github.io/books/RayTracingInOneWeekend.html :
//     Ray Tracng: The Next Week

#pragma once

#include "Pattern.h"


class Perlin : public Pattern
{
	static const int point_count = 256;
	double* ranfloat;
	Quaternion* ranvec;
	int* perm_x;
	int* perm_y;
	int* perm_z;

	static int* PerlinGeneratePerm();
	static void Permute(int* p, int n);
	double PerlinInterpolation(Quaternion c[2][2][2], double, double, double);

	double Noise(const Quaternion&);

public:

	double Width = 0;
	double Height = 0;
	double Scale = 1.0;

	Perlin(std::wstring);
	~Perlin();

	void SetDimensions(double, double, double);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] virtual std::wstring ToString() override;

	void ToFile(std::ofstream&) override;
};