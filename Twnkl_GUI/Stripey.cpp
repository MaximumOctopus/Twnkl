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
#include "Stripey.h"


Stripey::Stripey(std::wstring name) : Pattern(name)
{
	Name = name;
	Design = PatternDesign::Stripey;
}


Colour Stripey::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);
	
	if (static_cast<int>(Fast::Floor(pattern_point.x)) % 2 == 0)
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


void Stripey::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkStripey + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[0].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[1].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}