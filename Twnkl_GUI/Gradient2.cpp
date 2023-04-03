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

#include "Fast.h"
#include "Gradient2.h"


Gradient2::Gradient2(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour Gradient2::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	double factor = 2 * pattern_point.x - Fast::Floor(2 * pattern_point.x);

	if (std::abs(pattern_point.x - Fast::Floor(pattern_point.x)) < 0.5)
	{
		Colour c1(Colours[1].Sub(Colours[0]));

		c1.Scale(factor);

		return Colours[0].Add(c1);
	}
	else
	{
		Colour c1(Colours[0].Sub(Colours[1]));

		c1.Scale(factor);

		return Colours[1].Add(c1);
	}
}


std::wstring Gradient2::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}