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

#pragma once

#include "Colour.h"
#include "Constants.h"

enum class ImageProcess { None = 0, Greyscale = 1 };


struct PatternProperties
{
	Colour Colour1;
	Colour Colour2;

	std::wstring FileName = L"";

	Colour SurfaceColour = Colour(1.0, 1.0, 1.0);
	double Ambient         = __DefaultMaterialAmbient;
	double Diffuse         = __DefaultMaterialDiffuse;
	double Reflectivity    = __DefaultMaterialReflectivity;
	double RefractiveIndex = __DefaultMaterialRefractiveIndex;
	double Shininess       = __DefaultMaterialShininess;
	double Specular        = __DefaultMaterialSpecular;
	double Transparency    = __DefaultMaterialTransparency;

	double u = 0;
	double v = 0;
	ImageProcess process = ImageProcess::None;
	double scale = __DefaultPerlinScale;
	double phase = __DefaultPerlinPhase;
	double frequency = __DefaultFractalFrequency;
	double amplitude = __DefaultFractalAmplitude;
	double lacunarity = __DefaultFractalLacunarity;
	double persistence = __DefaultFractalPersistence;
	bool simple = false;

	bool noise = false;
	double npscale = 0.9;
	double nscale = 0.1;

	bool HasTexture = false;

	void Clear()
	{
		u = 0;
		v = 0;
		process = ImageProcess::None;
		scale = __DefaultPerlinScale;
		phase = __DefaultPerlinPhase;
		frequency = __DefaultFractalFrequency;
		amplitude = __DefaultFractalAmplitude;
		lacunarity = __DefaultFractalLacunarity;
		persistence = __DefaultFractalPersistence;
		simple = false;

		noise = false;
		npscale = 0.9;
		nscale = 0.1;
	}
};
