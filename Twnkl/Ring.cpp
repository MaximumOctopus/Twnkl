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
#include "Ring.h"


Ring::Ring(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour Ring::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	if (static_cast<int>(Fast::Floor(sqrt(pattern_point.x * pattern_point.x + pattern_point.z * pattern_point.z))) % 2 == 0)
	{
		return Colours[0];
	}
	else
	{
		return Colours[1];
	}
}


std::wstring Ring::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}