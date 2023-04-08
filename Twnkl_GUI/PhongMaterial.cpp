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

#include "PhongMaterial.h"


PhongMaterial::PhongMaterial()
{

}


PhongMaterial::~PhongMaterial()
{
	if (SurfacePattern != nullptr && HasPattern)
	{
		delete SurfacePattern;
	}
}


PhongMaterial::PhongMaterial(double r, double g, double b,
	double am, double di, double re, double ri, double sh, double sp, double tr)
{
	SurfaceColour.r = r;
	SurfaceColour.g = g;
	SurfaceColour.b = b;

	Ambient = am;
	Diffuse = di;
	Reflectivity = re;
	RefractiveIndex = ri;
	Shininess = sh;
	Specular = sp;
	Transparency = tr;
}


void PhongMaterial::SetPattern(Pattern* p)
{
	SurfacePattern = p;

	HasPattern = true;
}


void PhongMaterial::RemovePattern()
{
	delete SurfacePattern;

	HasPattern = false;
}


void PhongMaterial::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkMaterial + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + SurfaceColour.ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"ambient=" + std::to_wstring(Ambient) + L"\n");
	ofile << Formatting::to_utf8(L"diffuse=" + std::to_wstring(Diffuse) + L"\n");
	ofile << Formatting::to_utf8(L"reflectivity=" + std::to_wstring(Reflectivity) + L"\n");
	ofile << Formatting::to_utf8(L"refractiveindex=" + std::to_wstring(RefractiveIndex) + L"\n");
	ofile << Formatting::to_utf8(L"shininess=" + std::to_wstring(Shininess) + L"\n");
	ofile << Formatting::to_utf8(L"specular=" + std::to_wstring(Specular) + L"\n");
	ofile << Formatting::to_utf8(L"transparency=" + std::to_wstring(Transparency) + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	if (HasPattern)
	{
		SurfacePattern->ToFile(ofile);
	}
}