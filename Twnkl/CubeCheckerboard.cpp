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

#include "CubeCheckerboard.h"
#include "Fast.h"
#include "PatternCommon.h"


CubeChecker::CubeChecker(bool noise, std::wstring name) : Pattern(noise, name)
{
	Name = name;
	Design = PatternDesign::CubeCheckerboard;
}


void CubeChecker::SetDimensions(double u, double v)
{
	PatternWidth = u;
	PatternHeight = v;
}


Colour CubeChecker::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = { 0, 0 };

	int face = PatternCommon::FaceFromPoint(pattern_point);

	if (face == 1)
		uv = PatternCommon::CubeUVLeft(pattern_point);
	else if (face == 0)
		uv = PatternCommon::CubeUVRight(pattern_point);
	else if (face == 4)
		uv = PatternCommon::CubeUVFront(pattern_point);
	else if (face == 5)
		uv = PatternCommon::CubeUVBack(pattern_point);
	else if (face == 2)
		uv = PatternCommon::CubeUVUp(pattern_point);
	else
		uv = PatternCommon::CubeUVDown(pattern_point);

	return UVColourAt(/*cube_map.faces[face]*/ uv.first, uv.second);
}


Colour CubeChecker::UVColourAt(double u, double v)
{
	int x = std::abs(static_cast<int>(u * PatternWidth));
	int y = std::abs(static_cast<int>(v * PatternHeight));

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
		else
		{
			return Colours[1];
		}
	}
	else if ((x + y) % 2 == 0)
	{
		return Colours[0];
	}

	return Colours[1];
}


std::wstring CubeChecker::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString() + L", Dimensions " + std::to_wstring(PatternWidth) + L" x " + std::to_wstring(PatternHeight);
}


void CubeChecker::ToFile(std::ofstream& ofile)
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