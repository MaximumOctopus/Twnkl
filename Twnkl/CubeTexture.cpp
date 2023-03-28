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

#include "CubeTexture.h"


CubeTexture::CubeTexture(std::wstring name) : Pattern(name)
{
	Name = name;
}


int CubeTexture::FaceFromPoint(Quaternion p)
{
	double abs_x = abs(p.x);
	double abs_y = abs(p.y);
	double abs_z = abs(p.z);
	double coord = std::max(abs_x, std::max(abs_y, abs_z));

	if (coord == p.x)			// right
		return 0;
	else if (coord == -p.x)		// left
		return 1;	
	else if (coord == p.y)		// up
		return 2;				
	else if (coord == -p.y)		// down
		return 3;				
	else if (coord == p.z)		// front
		return 4;				
	else
		return 5;				// back
}


std::pair<double, double> CubeTexture::CubeUVFront(Quaternion& p)
{
	double u = fmod(p.x + 1, 2.0) / 2.0;
	double v = fmod(p.y + 1, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> CubeTexture::CubeUVBack(Quaternion& p)
{
	double u = fmod(1 - p.x, 2.0) / 2.0;
	double v = fmod(p.y + 1, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> CubeTexture::CubeUVLeft(Quaternion& p)
{
	double u = fmod(p.z + 1.0, 2.0) / 2.0;
	double v = fmod(p.y + 1.0, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> CubeTexture::CubeUVRight(Quaternion& p)
{
	double u = fmod(1 - p.z, 2.0) / 2.0;
	double v = fmod(p.y + 1, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> CubeTexture::CubeUVUp(Quaternion& p)
{
	double u = fmod(1 - p.x, 2.0) / 2.0;
	double v = fmod(1 - p.z, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> CubeTexture::CubeUVDown(Quaternion& p)
{
	double u = fmod(1 - p.x, 2.0) / 2.0;
	double v = fmod(p.z + 1, 2.0) / 2.0;

	return { u, v };
}


Colour CubeTexture::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	std::pair<double, double> uv = { 0, 0 };

	int face = FaceFromPoint(pattern_point);

	if (face == 1)
		uv = CubeUVLeft(pattern_point);
	else if (face == 0)
		uv = CubeUVRight(pattern_point);
	else if (face == 4)
		uv = CubeUVFront(pattern_point);
	else if (face == 5)
		uv = CubeUVBack(pattern_point);
	else if (face == 2)
		uv = CubeUVUp(pattern_point);
	else 
		uv = CubeUVDown(pattern_point);

	// colour test
	/*if (uv.second > 0.8)
	{
		if (uv.first < 0.2) return Colour(1.0, 0, 0);
		if (uv.first > 0.8) return Colour(1.0, 1.0, 0);
	}
	else if (uv.second < 0.2)
	{
		if (uv.first < 0.2) return Colour(0, 1.0, 0);
		if (uv.first > 0.8) return Colour(0, 1.0, 1.0);
	}

	return Colour(1.0, 1.0, 1.0);*/

	return UVColourAt(/*cube_map.faces[face]*/ uv.first, uv.second);
}


Colour CubeTexture::UVColourAt(double u, double v)
{
	// flip v over so it matches the image layout, with y at the top
	v = 1.0 - abs(v);
	u = 1.0 - abs(u);

	int x = abs(static_cast<int>(u * (Width - 1)));
	int y = abs(static_cast<int>(v * (Height - 1)));

	// be sure and round x and y to the nearest whole number
	return Texture[y * Width + x];
}


std::wstring CubeTexture::ToString()
{
	return L"Texture " + std::to_wstring(Width) + L" x " + std::to_wstring(Height);
}

