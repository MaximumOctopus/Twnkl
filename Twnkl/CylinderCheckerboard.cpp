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

#include <iostream>

#include "CylinderCheckerboard.h"
#include "Fast.h"
#include "PatternCommon.h"


CylinderCheckerboard::CylinderCheckerboard(bool noise, std::wstring name) : Pattern(noise, name)
{
	Name = name;
	Design = PatternDesign::CylinderCheckerboard;
}


void CylinderCheckerboard::SetDimensions(double u, double v)
{
	PatternWidth = u;
	PatternHeight = v;
}


Colour CylinderCheckerboard::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = PatternCommon::CylindricalMap(pattern_point);

	return UVColourAt(uv.first, uv.second);
}


Colour CylinderCheckerboard::UVColourAt(double u, double v)
{
	int u2 = static_cast<int>(Fast::Floor(u * PatternWidth));
	int v2 = static_cast<int>(Fast::Floor(v * PatternHeight));

    if (IncludeNoise)
	{
		Quaternion pp = Quaternion(u, v, -1, 1);
		Quaternion newpp = pp.Mult(pscale);

		Quaternion qq = noize->TripleFractal(newpp, scale);

		qq.Add(pp);

		if (static_cast<int>(Fast::Floor(qq.x) + Fast::Floor(qq.y)) % 2 == 0)
		{
			return Colours[0];
		}

		return Colours[1];
	}
	else
	{
		if ((u2 + v2) % 2 == 0)
		{
			return Colours[0];
        }
	}

	return Colours[1];
}


std::wstring CylinderCheckerboard::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString() + L", Dimensions " + std::to_wstring(PatternWidth) + L" x " + std::to_wstring(PatternHeight);
}


void CylinderCheckerboard::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkChecker + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[0].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[1].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"u=" + std::to_wstring(PatternWidth) + L"\n");
	ofile << Formatting::to_utf8(L"v=" + std::to_wstring(PatternHeight) + L"\n");
	if (IncludeNoise)
	{
		ofile << Formatting::to_utf8(L"noise=true\n");
		ofile << Formatting::to_utf8(L"frequency=" + std::to_wstring(noize->Frequency) + L"\n");
		ofile << Formatting::to_utf8(L"amplitude=" + std::to_wstring(noize->Amplitude) + L"\n");
		ofile << Formatting::to_utf8(L"lacunarity=" + std::to_wstring(noize->Lacunarity) + L"\n");
		ofile << Formatting::to_utf8(L"persistence=" + std::to_wstring(noize->Persistence) + L"\n");
		ofile << Formatting::to_utf8(L"nscale" + std::to_wstring(scale) + L"\n");
		ofile << Formatting::to_utf8(L"npscale" + std::to_wstring(pscale) + L"\n");
	}
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}