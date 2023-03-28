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

#include "Constants.h"
#include "Colour.h"


Colour::Colour() noexcept
{
	r = 0;
	g = 0;
	b = 0;
}


Colour::Colour(std::wstring s) noexcept
{

}


Colour::Colour(double R, double G, double B) noexcept
{
	r = R;
	g = G;
	b = B;
}


Colour Colour::Add(Colour& c)
{
	return Colour(r + c.r, g + c.g, b + c.b);
}


void Colour::AddTo(Colour& c)
{
	r += c.r;
	g += c.g;
	b += c.b;
}


Colour Colour::Sub(Colour& c)
{
	return Colour(r - c.r, g - c.g, b - c.b);
}


void Colour::Scale(double factor)
{
	r = r * factor;
	g = g * factor;
	b = b * factor;
}


Colour Colour::Mult(double factor)
{
	return Colour(r * factor, g * factor, b * factor);
}

// 

std::wstring Colour::ToString()
{
	std::wstring s = std::to_wstring(r) + L" / " + std::to_wstring(g) + L" / " + std::to_wstring(b);

	return s;
}


bool Colour::Equals(Colour c)
{
	double rr = abs(r - c.r);
	double gg = abs(g - c.g);
	double bb = abs(b - c.b);

	if (rr < epsilon && gg < epsilon && bb < epsilon)
	{
		return true;
	}

	return false;
}