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