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

#include "Stripey.h"


Stripey::Stripey(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour Stripey::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);
	
	if (static_cast<int>(floor(pattern_point.x)) % 2 == 0)
	{
		return Colours[0];
	}
	else
	{
		return Colours[1];
	}
}


std::wstring Stripey::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}