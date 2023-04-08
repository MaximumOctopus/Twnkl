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


void Colour::Reset()
{
	r = 1.0;
	g = 1.0;
	b = 1.0;
}


// converts from 0 - 1.0 format to 0 - 255 and clamps to the range
int Colour::To255(double colour)
{
	int new_colour = static_cast<int>(colour * 255.0);

	if (new_colour > 255)
	{
		new_colour = 255;
	}
	else if (new_colour < 0)
	{
		new_colour = 0;
	}

	return new_colour;
}


int Colour::ToIntBGR()
{
	int nr = To255(r);
	int ng = To255(g);
	int nb = To255(b);

	return (nb << 16) + (ng << 8) + nr;
}


int Colour::ToIntRGB()
{
	int nr = To255(r);
	int ng = To255(g);
	int nb = To255(b);

	return (nr << 16) + (ng << 8) + nb;
}


std::string Colour::RGBString()
{
	int nr = To255(r);
	int ng = To255(g);
	int nb = To255(b);

	return std::to_string(nr) + " " + std::to_string(ng) + " " + std::to_string(nb) + " ";
}


void Colour::FromIntBGR(int colour)
{
	int cr = (colour & 0x0000FF);
	int cg = (colour & 0x00FF00) >> 8;
	int cb = (colour & 0xFF0000) >> 16;	

	r = (double)cr / 255.0;
	g = (double)cg / 255.0;
	b = (double)cb / 255.0;
}


void Colour::FromIntRGB(int colour)
{
	int cr = (colour & 0xFF0000) >> 16;
	int cg = (colour & 0x00FF00) >> 8;
	int cb = (colour & 0x0000FF);

	r = (double)cr / 255.0;
	g = (double)cg / 255.0;
	b = (double)cb / 255.0;
}


bool Colour::Equals(Colour c)
{
	double rr = std::abs(r - c.r);
	double gg = std::abs(g - c.g);
	double bb = std::abs(b - c.b);

	if (rr < epsilon && gg < epsilon && bb < epsilon)
	{
		return true;
	}

	return false;
}


std::wstring Colour::ToString()
{
	std::wstring s = std::to_wstring(r) + L" / " + std::to_wstring(g) + L" / " + std::to_wstring(b);

	return s;
}


std::wstring Colour::ToCommaString()
{
	std::wstring s = std::to_wstring(r) + L", " + std::to_wstring(g) + L", " + std::to_wstring(b);

	return s;
}