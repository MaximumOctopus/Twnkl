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

// http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/indrf.html

#pragma once


class Pattern;

#include <fstream>

#include "Constants.h"
#include "Colour.h"
#include "Formatting.h"
#include "Pattern.h"


class PhongMaterial
{
public:

	Colour SurfaceColour = Colour(1.0, 1.0, 1.0);
	double Ambient         = __DefaultMaterialAmbient;
	double Diffuse         = __DefaultMaterialDiffuse;
	double Reflectivity    = __DefaultMaterialReflectivity;
	double RefractiveIndex = __DefaultMaterialRefractiveIndex;
	double Shininess       = __DefaultMaterialShininess;
	double Specular        = __DefaultMaterialSpecular;
	double Transparency    = __DefaultMaterialTransparency;

	Pattern* SurfacePattern = nullptr;

	bool HasPattern = false;

	PhongMaterial();
	~PhongMaterial();

	PhongMaterial(double, double, double, double, double, double, double, double, double, double);

	void SetPattern(Pattern*);

	void RemovePattern();

	void ToFile(std::ofstream& ofile);
};