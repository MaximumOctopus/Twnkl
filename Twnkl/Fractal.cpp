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

#include "PatternCommon.h"
#include "Fractal.h"


Fractal::Fractal(bool noise, std::wstring name) : Pattern(noise, name)
{
	Name = name;
    Design = PatternDesign::Fractal;
}


Colour Fractal::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

    double delta = 0.5 * (1.0 + noize->Fractal(pattern_point));

    double r = Colours[0].r + ((Colours[1].r - Colours[0].r) * delta);
    double g = Colours[0].g + ((Colours[1].g - Colours[0].g) * delta);
    double b = Colours[0].b + ((Colours[1].b - Colours[0].b) * delta);

    return Colour(r, g, b);
}


std::wstring Fractal::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}


void Fractal::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkFractal + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[0].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[1].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"frequency=" + std::to_wstring(noize->Frequency) + L"\n");
	ofile << Formatting::to_utf8(L"amplitude=" + std::to_wstring(noize->Amplitude) + L"\n");
	ofile << Formatting::to_utf8(L"lacunarity=" + std::to_wstring(noize->Lacunarity) + L"\n");
	ofile << Formatting::to_utf8(L"persistence=" + std::to_wstring(noize->Persistence) + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}