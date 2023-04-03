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

#include <string>


class Colour
{

public:

	double r = 0;
	double g = 0;
	double b = 0;

	[[nodiscard]] Colour Add(Colour&);
	void AddTo(Colour&);
	[[nodiscard]] Colour Sub(Colour&);
	void Scale(double);
	[[nodiscard]] Colour Mult(double);

	Colour() noexcept;

	Colour(std::wstring) noexcept;

	Colour(double, double, double) noexcept;

	[[nodiscard]] std::wstring ToString();

	void Reset();

	int To255(double);

	int ToIntBGR();					// to Windows format: BGR
	int ToIntRGB();
	void FromIntBGR(int);			// from Windows format: BGR
	void FromIntRGB(int);

	std::string RGBString();

	[[nodiscard]] bool Equals(Colour);
};