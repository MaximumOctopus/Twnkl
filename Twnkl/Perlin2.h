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


class Perlin2 : public Pattern
{
	double Width = 0;
	double Height = 0;
	double Scale = __DefaultPerlinScale;
	int Depth = 7;

	static const int point_count = 256;
	Quaternion* ranvec;
	int* perm_x;
	int* perm_y;
	int* perm_z;

	static int* PerlinGeneratePerm();
	static void Permute(int* p, int n);
	double PerlinInterpolation(Quaternion c[2][2][2], double, double, double);
	double Turbulance(const Quaternion&);

	double Noise(const Quaternion&);

public:

	Perlin2(std::wstring);
	~Perlin2();

	void SetDimensions(double, double, double);

	[[nodiscard]] Colour ColourAt(Object*, Quaternion&) override;

	[[nodiscard]] virtual std::wstring ToString() override;
};