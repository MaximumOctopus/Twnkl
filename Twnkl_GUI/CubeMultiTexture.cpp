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

#include "CubeMultiTexture.h"
#include "PatternCommon.h"


CubeMultiTexture::CubeMultiTexture(bool noise, std::wstring name) : Pattern(noise, name)
{
	Name = name;
	Design = PatternDesign::CubeMultiTexture;
}


CubeMultiTexture::~CubeMultiTexture()
{
	for (int t = 0; t < 6; t++)
	{
		delete Texture[t];
	}
}


Colour CubeMultiTexture::ColourAt(Object* o, Quaternion& q)
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

	return UVColourAt(face, uv.first, uv.second);
}


Colour CubeMultiTexture::UVColourAt(int face, double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - std::abs(v);
	u = 1.0 - std::abs(u);

	int x = std::abs(static_cast<int>(u * (TextureWidth - 1)));
	int y = std::abs(static_cast<int>(v * (TextureHeight - 1)));

	if (IncludeNoise)
	{
		Quaternion pattern_point = Quaternion(x, y, -1, 1);
		Quaternion newpp = pattern_point.Mult(pscale);

		Quaternion qq = noize->TripleFractal(newpp, scale);

		qq.Add(newpp);

		int tx = static_cast<int>(qq.x);
		int ty = static_cast<int>(qq.y);

		if (tx > TextureWidth - 1) tx = std::floor(std::div(tx, TextureWidth - 1).quot);
		if (tx < 0) tx = TextureWidth - 1 - std::floor((TextureWidth - 1) * std::div(std::abs(tx), TextureWidth - 1).quot);

		if (ty > TextureHeight - 1) ty = std::floor(std::div(ty, TextureHeight - 1).quot);
		if (ty < 0) ty = TextureHeight - 1 - std::floor((TextureHeight - 1)* std::div(std::abs(ty), TextureHeight - 1).quot);

		return Texture[face][ty * TextureWidth + tx];
	}

	return Texture[face][y * TextureWidth + x];
}


std::wstring CubeMultiTexture::ToString()
{
	return L"Texture " + std::to_wstring(TextureWidth) + L" x " + std::to_wstring(TextureHeight) + L" (x6)";
}


void CubeMultiTexture::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkTexture + L"\n");
	ofile << Formatting::to_utf8(L"filename=" + FileName + L"\n");
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