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


void Pattern::ProcessTransforms()
{
	for (int t = 0; t < Transforms.size(); t++)
	{
		if (t == 0)
		{
			Transform = Transforms[t].Transform;
		}
		else
		{
			Transform.MultiplyBy(Transforms[t].Transform);
		}
	}

	CreateInverseTransform();
}


void Pattern::AddTransform(TransformConfiguration tc)
{
	Transforms.push_back(tc);
}


void Pattern::CreateInverseTransform()
{
	InverseTransform = Transform.Inverse();
}


int Pattern::TransformsCount()
{
	return Transforms.size();
}


TransformConfiguration Pattern::TransformAt(int index)
{
	return Transforms[index];
}


std::wstring Pattern::ToString()
{
	return L"base class!";
}