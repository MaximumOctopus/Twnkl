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

#include "TestPattern.h"


TestPattern::TestPattern(std::wstring name) : Pattern(name)
{
	Name = name;
}


Colour TestPattern::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	return Colour(pattern_point.x, pattern_point.y, pattern_point.z);
}


std::wstring TestPattern::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}