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
#include "Gradient.h"


Gradient::Gradient(bool noise, std::wstring name) : Pattern(noise, name)
{
	Name = name;
	Design = PatternDesign::Gradient;
}


Colour Gradient::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	Colour d = Colours[1].Sub(Colours[0]);

	double f = pattern_point.x - Fast::Floor(pattern_point.x);

	Colour dmf = d.Mult(f);

	return Colours[0].Add(dmf);
}


std::wstring Gradient::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}


void Gradient::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkGradient + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[0].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[1].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}