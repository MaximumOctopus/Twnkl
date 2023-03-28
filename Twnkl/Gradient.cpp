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

#include "Gradient.h"


Gradient::Gradient(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour Gradient::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	Colour d = Colours[1].Sub(Colours[0]);

	double f = pattern_point.x - floor(pattern_point.x);

	Colour dmf = d.Mult(f);

	return Colours[0].Add(dmf);
}


std::wstring Gradient::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}