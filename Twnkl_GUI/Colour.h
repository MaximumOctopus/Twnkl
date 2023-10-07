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

#ifdef _GUI
#include <Vcl.Graphics.hpp>
#endif

#include <string>


class Colour
{

public:

	double r = 0;   // 0 to 1
	double g = 0;   // 0 to 1
	double b = 0;   // 0 to 1

	[[nodiscard]] Colour Add(Colour&);
	void AddTo(Colour&);
	[[nodiscard]] Colour Sub(Colour&);
	void Scale(double);
	[[nodiscard]] Colour Mult(double);

	Colour() noexcept;

	Colour(std::wstring) noexcept;

	Colour(double, double, double) noexcept;

	void Reset();

	int To255(double);

	int ToIntBGR();					// to Windows format: BGR
	int ToIntRGB();
	#ifdef _GUI
	TRGBTriple ToRGBTriple();
	#endif
	void FromIntBGR(int);			// from Windows format: BGR
	void FromIntRGB(int);

	std::string RGBString();

	[[nodiscard]] std::wstring ToCommaString();
	[[nodiscard]] std::wstring ToString();

	[[nodiscard]] bool Equals(Colour);
};