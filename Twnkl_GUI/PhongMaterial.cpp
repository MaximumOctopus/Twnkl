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

#include "CubeTexture.h"
#include "CubeMultiTexture.h"
#include "CylinderTexture.h"
#include "PlanarTexture.h"
#include "SphericalTexture.h"


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


PatternProperties PhongMaterial::GetProperties()
{
	PatternProperties properties;

	properties.SurfaceColour = SurfaceColour;
	properties.Ambient         = Ambient;
	properties.Diffuse         = Diffuse;
	properties.Reflectivity    = Reflectivity;
	properties.RefractiveIndex = RefractiveIndex;
	properties.Shininess       = Shininess;
	properties.Specular        = Specular;
	properties.Transparency    = Transparency;

	if (HasPattern)
	{
		properties.Colour1 = SurfacePattern->Colours[0];
		properties.Colour2 = SurfacePattern->Colours[1];

		properties.noise = SurfacePattern->IncludeNoise;
		properties.npscale = SurfacePattern->pscale;
		properties.nscale = SurfacePattern->scale;

		if (SurfacePattern->IncludeNoise)
		{
			properties.scale = SurfacePattern->scale;
			properties.phase = SurfacePattern->pscale;

			properties.frequency = SurfacePattern->noize->Frequency;
			properties.amplitude = SurfacePattern->noize->Amplitude;
			properties.lacunarity = SurfacePattern->noize->Lacunarity;
			properties.persistence = SurfacePattern->noize->Persistence;
			properties.simple = false;
		}

		switch (SurfacePattern->Design)
		{
		case PatternDesign::CubeTexture:
		{
			CubeTexture* p = dynamic_cast<CubeTexture*>(SurfacePattern);
			properties.FileName = p->FileName;
			break;
		}
		case PatternDesign::CubeMultiTexture:
		{
			CubeMultiTexture* p = dynamic_cast<CubeMultiTexture*>(SurfacePattern);
			properties.FileName = p->FileName;
			break;
		}
		case PatternDesign::PlanarTexture:
		{
			PlanarTexture* p = dynamic_cast<PlanarTexture*>(SurfacePattern);
			properties.FileName = p->FileName;
			break;
		}
		case PatternDesign::CylinderTexture:
		{
			CylinderTexture* p = dynamic_cast<CylinderTexture*>(SurfacePattern);
			properties.FileName = p->FileName;
			break;
		}
		case PatternDesign::SphericalTexture:
		{
			SphericalTexture* p = dynamic_cast<SphericalTexture*>(SurfacePattern);
			properties.FileName = p->FileName;
			break;
		}
		}

		properties.u = SurfacePattern->PatternWidth;
        properties.v = SurfacePattern->PatternHeight;
	}

//	properties.process = ImageProcess::None;

	return properties;
}