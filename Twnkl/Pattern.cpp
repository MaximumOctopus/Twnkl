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

#include "Pattern.h"


Pattern::Pattern(std::wstring name)
{

}


void Pattern::SetColours(Colour a, Colour b)
{
	Colours[0] = a;
	Colours[1] = b;
}


void Pattern::SetReflectivity(double a, double b)
{
	Reflectivity[0] = a;
	Reflectivity[1] = b;

	HasReflectivity = true;
}


Colour Pattern::ColourAt(Object*, Quaternion&)
{
	return Colour(1.0, 0, 1.0);
}


void Pattern::SetTransform(Matrix4 m)
{
	Transform = m;

	TransformSet = true;
}


void Pattern::Finalise()
{
	InverseTransform = Transform.Inverse();
}


std::wstring Pattern::ToString()
{
	return L"base class!";
}