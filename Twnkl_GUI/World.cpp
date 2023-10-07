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

#include <fstream>
#include <iostream>

#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Model.h"
#include "Plane.h"
#include "Sphere.h"

#ifdef _GUI
#include "PointLight.h"
#endif

#ifdef _DEBUG
#ifndef _GUI
#include "TestPattern.h"
#endif
#endif

#include "Checkerboard.h"
#include "CubeCheckerboard.h"
#include "CubeTexture.h"
#include "CubeMultiTexture.h"
#include "CylinderCheckerboard.h"
#include "CylinderTexture.h"
#include "Fractal.h"
#include "Gradient.h"
#include "Gradient2.h"
#include "Perlin.h"
#include "Perlin2.h"
#include "Perlin3.h"
#include "PlanarTexture.h"
#include "Ring.h"
#include "Simplex.h"
#include "SphericalCheckerboard.h"
#include "SphericalTexture.h"
#include "Stripey.h"

#include "TextureLoader.h"

#include "World.h"


World* GWorld;


World::World(int w, int h, double f)
{
	Cam = new Camera(w, h, f);
}


World::~World()
{
	delete Cam;
	delete Canvas;
}


void World::Clear()
{
    Project.Description = L"";

	for (int t = 0; t < Objects.size(); t++)
	{
		delete Objects[t];
	}

	Objects.clear();

	for (int t = 0; t < Lights.size(); t++)
	{
		delete Lights[t];
	}

	Lights.clear();
}


bool World::Finalise()
{
	bool HasErrors = false;

	for (int t = 0; t < Objects.size(); t++)
	{
		Objects[t]->ID = t;

		Objects[t]->ProcessTransforms();

		// sanity checking...
		if (Objects[t]->Material != nullptr)
		{		
			if (Objects[t]->Material->RefractiveIndex < epsilon)
			{
				#ifdef _GUI
				Errors.push_back(L"Object (" + std::to_wstring(t) + L", " + Objects[t]->Name + L") has zero IoR! This will cause rendering issues.");
				#else
				std::wcout << L"    Object (" << t << L", " << Objects[t]->Name << L") has zero IoR! This will cause rendering issues.\n";
				#endif
			}

			if (Objects[t]->Material->HasPattern)
			{
				Objects[t]->Material->SurfacePattern->ProcessTransforms();
			}

			Objects[t]->PostSetup(t);
		}
		else
		{
			#ifdef _GUI
			Errors.push_back(L"Object (" + std::to_wstring(t) + L", " + Objects[t]->Name + L") has no assigned material! This will cause serious rendering issues.");
			#else
			std::wcout << L"    Object (" << t << L", " << Objects[t]->Name << L") has no assigned material! This will cause serious rendering issues.\n";
			#endif

			HasErrors = true;
		}
	}

	// now set camera and allocate memory for canvas
	if (Canvas != nullptr)
	{
		delete Canvas;
	}

	Canvas = new Colour[Cam->Width * Cam->Height];

	Cam->InverseTransform = Cam->Transform.Inverse();

	return HasErrors;
}


// =================================================================================
// == File Output ==================================================================
// =================================================================================


// https://netpbm.sourceforge.net/doc/ppm.html
bool World::SaveCanvasToFile(const std::wstring file_name)
{
	std::ofstream file(file_name);

	if (file)
	{
		#ifdef _GUI
		Errors.push_back(L"Saving image: " + file_name);
		#else
		std::wcout << L"  Saving image        : " << file_name << L"\n";
		#endif

		file << "P3\n";
		file << Cam->Width << " " << Cam->Height << "\n";
		file << "255\n";

		for (int y = 0; y < Cam->Height; y++)
		{
			std::string row = "";

			for (int x = 0; x < Cam->Width; x++)
			{
				row += Canvas[y * GWorld->Cam->Width + x].RGBString();
			}

			file << row << "\n";
		}

		file.close();

		return true;
	}

	#ifdef _GUI
	Errors.push_back(L"Error writing image :(");
	#else
	std::wcout << L"  Error writing image :(" << L"\n";
	#endif

	return false;
}


void World::SaveScene(std::wstring file_name)
{
	std::ofstream file(file_name);

	if (file)
	{
		Cam->ToFile(file);

		for (int t = 0; t < Lights.size(); t++)
		{
			Lights[t]->ToFile(file);
		}

		for (int t = 0; t < Objects.size(); t++)
		{
			Objects[t]->ToFile(file);
		}

		file.close();
	}
}



// =================================================================================
// == Debug ========================================================================
// =================================================================================


void World::ToString()
{
	std::wcout << L"\n ====== World ============================================\n\n";

	std::wcout << L" Camera\n";
	std::wcout << L"    HSize      : " << Cam->Width << L"\n";
	std::wcout << L"    VSize      : " << Cam->Height << L"\n";
	std::wcout << L"    FoV        : " << Cam->FoV << L"\n";
	std::wcout << L"    HalfView   : " << Cam->HalfView << L"\n";
	std::wcout << L"    HalfWidth  : " << Cam->HalfWidth << L"\n";
	std::wcout << L"    HalfHeight : " << Cam->HalfHeight << L"\n";
	std::wcout << L"    PixelSize  : " << Cam->PixelSize << L"\n";
	std::wcout << L"\n";

	for (int t = 0; t < Objects.size(); t++)
	{
		std::wcout << L" Object " << t << L" (" << Objects[t]->Name << L", " << Objects[t]->ID << L")\n";
		std::wcout << L"    Detail     : " << Objects[t]->ToString() << L"\n";
		std::wcout << L"    Position   : " << Objects[t]->Position.ToString() << L"\n";

		if (Objects[t]->TransformsCount() != 0)
		{
			std::wcout << L"    Transforms\n";

			for (int x = 0; x < Objects[t]->TransformsCount(); x++)
			{
				TransformConfiguration tc = Objects[t]->TransformAt(x);
				
				std::wcout << L"        Type            : " << tc.TypeAsString() << L"\n";

				switch (tc.Type)
				{
				case TransformType::None:
					break;
				case TransformType::Scale:
				case TransformType::Translate:
					std::wcout << L"        XYZ             : " << tc.XYZ.ToString() << L"\n";
					break;
				case TransformType::RotateX:
				case TransformType::RotateY:
				case TransformType::RotateZ:
					std::wcout << L"        Angle           : " << tc.Angle << L" radians \n";
					break;
				}
			}
		}

		std::wcout << L"    Material\n";
		std::wcout << L"        Colour          : " << Objects[t]->Material->SurfaceColour.ToString() << L"\n";
		std::wcout << L"        Ambient         : " << Objects[t]->Material->Ambient << L"\n";
		std::wcout << L"        Diffuse         : " << Objects[t]->Material->Diffuse << L"\n";
		std::wcout << L"        Reflectivity    : " << Objects[t]->Material->Reflectivity << L"\n";
		std::wcout << L"        RefractiveIndex : " << Objects[t]->Material->RefractiveIndex << L"\n";
		std::wcout << L"        Shininess       : " << Objects[t]->Material->Shininess << L"\n";
		std::wcout << L"        Specular        : " << Objects[t]->Material->Specular << L"\n";
		std::wcout << L"        Transparency    : " << Objects[t]->Material->Transparency << L"\n";

		if (Objects[t]->Material->HasPattern)
		{
			std::wcout << L"    Pattern (" << Objects[t]->Material->SurfacePattern->Name << L")\n";
			std::wcout << L"        Colours         : " << Objects[t]->Material->SurfacePattern->ToString() << L"\n";
			
			if (Objects[t]->TransformsCount() != 0)
			{
				std::wcout << L"        Transforms\n";

				for (int x = 0; x < Objects[t]->Material->SurfacePattern->TransformsCount(); x++)
				{
					TransformConfiguration tc = Objects[t]->Material->SurfacePattern->TransformAt(x);

					std::wcout << L"            Type            : " << tc.TypeAsString() << L"\n";

					switch (tc.Type)
					{
					case TransformType::None:
						break;
					case TransformType::Scale:
					case TransformType::Translate:
						std::wcout << L"            XYZ             : " << tc.XYZ.ToString() << L"\n";
						break;
					case TransformType::RotateX:
					case TransformType::RotateY:
					case TransformType::RotateZ:
						std::wcout << L"            Angle           : " << tc.Angle << L" radians \n";
						break;
					}
				}
			}
		}

		std::wcout << "\n";
	}

	for (int t = 0; t < Lights.size(); t++)
	{
		std::wcout << L" Light " << t << L" (" << Lights[t]->Name << L")\n";
		std::wcout << L"    Position   : " << Lights[t]->Position.ToString() << L"\n";
		std::wcout << L"    Intensity  : " << Lights[t]->Intensity.ToString() << L"\n";
		std::wcout << L"    Detail     : " << Lights[t]->ToString() << L"\n";

		std::wcout << "\n";
	}
}


#ifdef _GUI
void World::MakeCopyOfObjectAt(int id)
{
	int primitive = -1;

	switch (Objects[id]->Primitive)
	{
	case PrimitiveType::Cone:
		primitive = 0;
		break;
	case PrimitiveType::Cube:
		primitive = 1;
		break;
	case PrimitiveType::Cylinder:
		primitive = 2;
		break;
	case PrimitiveType::Plane:
		primitive = 4;
		break;
	case PrimitiveType::Sphere:
		primitive = 5;
		break;
	}

	if (primitive != -1)
	{
		PatternDesign pattern = PatternDesign::None;
		PatternProperties properties = Objects[id]->Material->GetProperties();

		if (Objects[id]->Material->HasPattern)
		{
			pattern = Objects[id]->Material->SurfacePattern->Design;
		}

		AddNewObject(primitive, pattern, properties, L"copy of " + Objects[id]->Name);

		if (Objects[id]->TransformsCount() != 0)
		{
			for (int t = 0; t < Objects[id]->TransformsCount(); t++)
			{
				Objects.back()->AddTransform(Objects[id]->TransformAt(t));
			}

			Objects.back()->ProcessTransforms();
		}

		if (Objects[id]->Material->HasPattern)
		{
			if (Objects[id]->Material->SurfacePattern->TransformsCount() != 0)
			{
				for (int t = 0; t < Objects[id]->Material->SurfacePattern->TransformsCount(); t++)
				{
					Objects.back()->Material->SurfacePattern->AddTransform(Objects[id]->TransformAt(t));
				}

				Objects.back()->Material->SurfacePattern->ProcessTransforms();
			}

		}
	}
}


void World::AddNewObject(int primitive, PatternDesign pattern, PatternProperties properties, std::wstring name)
{
	switch (primitive)
	{
	case 0:             // cone
	{
		Cone* s = new Cone(name);
		s->SetParameters(0, 1, true);
		Objects.push_back(s);
		break;
	}
	case 1:             // cube
	{
		Cube* s = new Cube(name);
		Objects.push_back(s);
		break;
	}
	case 2:             // cylinder
	{
		Cylinder* s = new Cylinder(name);
		s->SetParameters(0, 1, true);
		Objects.push_back(s);
		break;
	}
	case 3:             // model
	{
		Model* s = new Model(name);
		//s->Load(file_name);
		Objects.push_back(s);
		break;
	}
	case 4:             // plane
	{
		Plane* s = new Plane(name);
		Objects.push_back(s);
		break;
	}
	case 5:             // sphere
	{
		Sphere* s = new Sphere(name);
		Objects.push_back(s);
		break;
	}
	}

	PhongMaterial* p = new PhongMaterial();
	Objects.back()->Material = p;

	if (pattern != PatternDesign::None)
	{
		if (!SetLastObjectPattern(pattern, properties))
		{
			#ifdef _GUI
			Errors.push_back(LastError);
			#endif
        }
	}
}
#endif


bool World::SetLastObjectPattern(PatternDesign pattern, PatternProperties properties)
{
	bool greyscale = false;

	if (properties.process == ImageProcess::Greyscale)
	{
		greyscale = true;
	}

	switch (pattern)
	{
	case PatternDesign::None:
		break;

	case PatternDesign::Checkerboard:
		return AddCheckerTo(__LastObject, properties);

	case PatternDesign::Gradient:
		return AddGradientTo(__LastObject, properties);

	case PatternDesign::Gradient2:
		return AddGradient2To(__LastObject, properties);

	case PatternDesign::Ring:
		return AddRingTo(__LastObject, properties);

	case PatternDesign::Stripey:
		return AddStripeyTo(__LastObject, properties);

	case PatternDesign::Fractal:
		return AddFractalTo(__LastObject, properties);

	case PatternDesign::Simplex:
		return AddSimplexTo(__LastObject, properties);

	case PatternDesign::Perlin1:
		return AddPerlinTo(__LastObject, properties);

	case PatternDesign::Perlin2:
		return AddPerlin2To(__LastObject, properties);

	case PatternDesign::Perlin3:
		return AddPerlin3To(__LastObject, properties);

	case PatternDesign::CubeCheckerboard:
		return AddCheckerCubeTo(__LastObject, properties);

	case PatternDesign::CubeTexture:
	case PatternDesign::CubeMultiTexture:
		return AddTextureCubeTo(__LastObject, properties, greyscale);

	case PatternDesign::CylinderCheckerboard:
		return AddCheckerCylinderTo(__LastObject, properties);

	case PatternDesign::CylinderTexture:
		return AddTextureCylinderTo(__LastObject, properties, greyscale);

	case PatternDesign::PlanarTexture:
		return AddTexturePlaneTo(__LastObject, properties, greyscale);

	case PatternDesign::SphericalCheckerboard:
		return AddCheckerSphereTo(__LastObject, properties);

	case PatternDesign::SphericalTexture:
		return AddTextureSphereTo(__LastObject, properties, greyscale);
	}

	return false;
}


bool World::AddCheckerTo(int id, PatternProperties properties)
{
	Checkerboard* p = new Checkerboard(properties.noise, L"Checkerboard");
	p->SetColours(properties.Colour1, properties.Colour2);

	if (properties.noise)
	{
		p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
			properties.npscale, properties.nscale);
	}

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddGradientTo(int id, PatternProperties properties)
{
	Gradient* p = new Gradient(false, L"Gradient");
	p->SetColours(properties.Colour1, properties.Colour2);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddGradient2To(int id, PatternProperties properties)
{
	Gradient2* p = new Gradient2(false, L"Gradient2");
	p->SetColours(properties.Colour1, properties.Colour2);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddRingTo(int id, PatternProperties properties)
{
	Ring* p = new Ring(false, L"Ring");
	p->SetColours(properties.Colour1, properties.Colour2);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddStripeyTo(int id, PatternProperties properties)
{
	Stripey* p = new Stripey(properties.noise, L"Stripey");
	p->SetColours(properties.Colour1, properties.Colour2);

	if (properties.noise)
	{
		p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
			properties.npscale, properties.nscale);
	}

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddPerlinTo(int id, PatternProperties properties)
{
	Perlin* p = new Perlin(false, L"Perlin");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetDimensions(properties.u, properties.v, properties.scale);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddPerlin2To(int id, PatternProperties properties)
{
	Perlin2* p = new Perlin2(false, L"Perlin2");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetDimensions(properties.u, properties.v, properties.scale);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddPerlin3To(int id, PatternProperties properties)
{
	Perlin3* p = new Perlin3(false, L"Perlin3");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetDimensions(properties.u, properties.v, properties.scale, properties.phase);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddFractalTo(int id, PatternProperties properties)
{
	Fractal* p = new Fractal(false, L"Fractal");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence, 1, 1);

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddSimplexTo(int id, PatternProperties properties)
{
	Simplex* p = new Simplex(false, L"Simplex");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->Simple = properties.simple;

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddCheckerSphereTo(int id, PatternProperties properties)
{
	SphericalCheckerboard* p = new SphericalCheckerboard(properties.noise, L"SphericalChecker");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetDimensions(properties.u, properties.v);

	if (properties.noise)
	{
		p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
			properties.npscale, properties.nscale);
	}

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddCheckerCylinderTo(int id, PatternProperties properties)
{
	CylinderCheckerboard* p = new CylinderCheckerboard(properties.noise, L"CylinderChecker");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetDimensions(properties.u, properties.v);

	if (properties.noise)
	{
		p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
			properties.npscale, properties.nscale);
	}

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddCheckerCubeTo(int id, PatternProperties properties)
{
	CubeChecker* p = new CubeChecker(properties.noise, L"CubeChecker");
	p->SetColours(properties.Colour1, properties.Colour2);
	p->SetDimensions(properties.u, properties.v);

	if (properties.noise)
	{
		p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
			properties.npscale, properties.nscale);
	}

	if (id == __LastObject)
	{
		GWorld->Objects.back()->Material->SetPattern(p);
	}
	else
	{
		GWorld->Objects[id]->Material->SetPattern(p);
	}

	return true;
}


bool World::AddTextureCubeTo(int id, PatternProperties properties, bool greyscale)
{
	if (properties.FileName.find(L'*') != std::wstring::npos)
	{
		auto asterisk = properties.FileName.find(L'*');

		wchar_t nums[6] = { L'1', L'2', L'3', L'4', L'5', L'6' };

		CubeMultiTexture* p = new CubeMultiTexture(properties.noise, L"CubeMultiTexture");

		p->FileName = properties.FileName;

		TextureLoader tl;

		for (int t = 0; t < 6; t++)
		{
			properties.FileName[asterisk] = nums[t];

			if (tl.Go(&p->Texture[t], properties.FileName, greyscale))
			{
				p->TextureWidth = tl.TextureWidth;
				p->TextureHeight = tl.TextureHeight;
			}
			else
				{
				LastError = L"error loading texture \"" + properties.FileName + L"\"\n";
				return false;
			}
		}

		if (properties.noise)
		{
			p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
				properties.npscale, properties.nscale);
		}

		if (id == __LastObject)
		{
			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			GWorld->Objects[id]->Material->SetPattern(p);
		}
	}
	else
	{
		CubeTexture* p = new CubeTexture(properties.noise, L"CubicTexture");

		p->FileName = properties.FileName;

		TextureLoader tl;

		if (tl.Go(&p->Texture, properties.FileName, greyscale))
		{
			p->TextureWidth = tl.TextureWidth;
			p->TextureHeight = tl.TextureHeight;
			p->FileName = properties.FileName;

			if (properties.noise)
			{
				p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
					properties.npscale, properties.nscale);
			}

			if (id == __LastObject)
			{
				GWorld->Objects.back()->Material->SetPattern(p);
			}
			else
			{
				GWorld->Objects[id]->Material->SetPattern(p);
			}
		}
		else
		{
			LastError = L"error loading texture \"" + properties.FileName + L"\"\n";
			return false;
		}
	}

	return true;
}


bool World::AddTextureCylinderTo(int id, PatternProperties properties, bool greyscale)
{
	CylinderTexture* p = new CylinderTexture(properties.noise, L"CylinderTexture");

	TextureLoader tl;

	if (tl.Go(&p->Texture, properties.FileName, greyscale))
	{
		p->TextureWidth = tl.TextureWidth;
		p->TextureHeight = tl.TextureHeight;
		p->FileName = properties.FileName;

		if (properties.noise)
		{
			p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
				properties.npscale, properties.nscale);
		}

		if (id == __LastObject)
		{
			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			GWorld->Objects[id]->Material->SetPattern(p);
		}
	}
	else
	{
		LastError = L"error loading texture \"" + properties.FileName + L"\"\n";
		return false;
	}

	return true;
}


bool World::AddTexturePlaneTo(int id, PatternProperties properties, bool greyscale)
{
	PlanarTexture* p = new PlanarTexture(properties.noise, L"PlanarTexture");

	TextureLoader tl;

	if (tl.Go(&p->Texture, properties.FileName, greyscale))
	{
		p->TextureWidth = tl.TextureWidth;
		p->TextureHeight = tl.TextureHeight;
		p->FileName = properties.FileName;

		if (properties.noise)
		{
			p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
				properties.npscale, properties.nscale);
		}

		if (id == __LastObject)
		{
			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			GWorld->Objects[id]->Material->SetPattern(p);
		}
	}
	else
	{
		LastError = L"error loading texture \"" + properties.FileName + L"\"\n";
		return false;
	}

	return true;
}


bool World::AddTextureSphereTo(int id, PatternProperties properties, bool greyscale)
{
	SphericalTexture* p = new SphericalTexture(properties.noise, L"SphericalTexture");

	TextureLoader tl;

	if (tl.Go(&p->Texture, properties.FileName, greyscale))
	{
		p->TextureWidth = tl.TextureWidth;
		p->TextureHeight = tl.TextureHeight;
        p->FileName = properties.FileName;

		if (properties.noise)
		{
			p->SetNoise(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence,
				properties.npscale, properties.nscale);
		}

		if (id == __LastObject)
		{
			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			GWorld->Objects[id]->Material->SetPattern(p);
		}
	}
	else
	{
		LastError = L"error loading texture \"" + properties.FileName + L"\"\n";
		return false;
	}

	return true;
}


bool World::SetObjectPattern(int id, PatternDesign pattern, PatternProperties properties)
{
	bool greyscale = false;

	if (properties.process == ImageProcess::Greyscale)
	{
		greyscale = true;
	}

	switch (pattern)
	{
	case PatternDesign::None:
		break;

	case PatternDesign::Checkerboard:
		return AddCheckerTo(id, properties);

	case PatternDesign::Gradient:
		return AddGradientTo(id, properties);

	case PatternDesign::Gradient2:
		return AddGradient2To(id, properties);

	case PatternDesign::Ring:
		return AddRingTo(id, properties);

	case PatternDesign::Stripey:
		return AddStripeyTo(id, properties);

	case PatternDesign::Perlin1:
		return AddPerlinTo(id, properties);

	case PatternDesign::Perlin2:
		return AddPerlin2To(id, properties);

	case PatternDesign::Perlin3:
		return AddPerlin3To(id, properties);

	case PatternDesign::Fractal:
		return AddFractalTo(id, properties);

	case PatternDesign::Simplex:
		return AddSimplexTo(id, properties);

	case PatternDesign::SphericalCheckerboard:
		return AddCheckerSphereTo(id, properties);

	case PatternDesign::CylinderCheckerboard:
		return AddCheckerCylinderTo(id, properties);

	case PatternDesign::CubeCheckerboard:
		return AddCheckerCubeTo(id, properties);

	case PatternDesign::SphericalTexture:
		return AddTextureSphereTo(id, properties, greyscale);

	case PatternDesign::PlanarTexture:
		return AddTexturePlaneTo(id, properties, greyscale);

	case PatternDesign::CubeTexture:
	case PatternDesign::CubeMultiTexture:
		return AddTextureCubeTo(id, properties, greyscale);

	case PatternDesign::CylinderTexture:
		return AddTextureCylinderTo(id, properties, greyscale);
	}

	return true;
}


#ifdef _GUI
void World::ReplaceTexture(int id, std::wstring file_name)
{
	TextureLoader tl;

	switch(Objects[id]->Material->SurfacePattern->Design)
	{
	case PatternDesign::CubeTexture:
	{
		CubeTexture* p = dynamic_cast<CubeTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

		if (p->Texture != nullptr)
		{
			delete[] p->Texture;
		}

		if (tl.Go(&p->Texture, file_name, false))
		{
			p->TextureWidth = tl.TextureWidth;
			p->TextureHeight = tl.TextureHeight;
			p->FileName = file_name;
			return;
		}
		break;
	}
	case PatternDesign::CubeMultiTexture:
	{
		if (file_name.find(L'*') != std::wstring::npos)
		{
			auto asterisk = file_name.find(L'*');

			wchar_t nums[6] = { L'1', L'2', L'3', L'4', L'5', L'6' };

			CubeMultiTexture* p = dynamic_cast<CubeMultiTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

			p->FileName = file_name;

			for (int t = 0; t < 6; t++)
			{
				file_name[asterisk] = nums[t];

				if (tl.Go(&p->Texture[t], file_name, false))
				{
					p->TextureWidth = tl.TextureWidth;
					p->TextureHeight = tl.TextureHeight;
				}
				else
				{
					Errors.push_back(L"error loading texture \"" + file_name + L"\"");
					return;
				}
			}
			return;
		}
		break;
	}
	case PatternDesign::CylinderTexture:
	{
		CylinderTexture* p = dynamic_cast<CylinderTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

		if (p->Texture != nullptr)
		{
			delete[] p->Texture;
		}

		if (tl.Go(&p->Texture, file_name, false))
		{
			p->TextureWidth = tl.TextureWidth;
			p->TextureHeight = tl.TextureHeight;
			p->FileName = file_name;
			return;
		}
		break;
	}
	case PatternDesign::PlanarTexture:
	{
		PlanarTexture* p = dynamic_cast<PlanarTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

		if (p->Texture != nullptr)
		{
			delete[] p->Texture;
		}

		if (tl.Go(&p->Texture, file_name, false))
		{
			p->TextureWidth = tl.TextureWidth;
			p->TextureHeight = tl.TextureHeight;
			p->FileName = file_name;
			return;
		}
		break;
	}
	case PatternDesign::SphericalTexture:
	{
		SphericalTexture* p = dynamic_cast<SphericalTexture*>(GWorld->Objects[id]->Material->SurfacePattern);

		if (p->Texture != nullptr)
		{
			delete[] p->Texture;
		}

		if (tl.Go(&p->Texture, file_name, false))
		{
			p->TextureWidth = tl.TextureWidth;
			p->TextureHeight = tl.TextureHeight;
			p->FileName = file_name;
			return;
		}
		break;
	}
	}

	Errors.push_back(L"error loading texture \"" + file_name + L"\"");
}


void World::DefaultScene()
{
	PointLight* l = new PointLight(L"pointlight", 1.0, 1.0, 1.0, -4.9, 4.9, -1);
	Lights.push_back(l);

	Plane* p = new Plane(L"floor");
	PhongMaterial* mf = new PhongMaterial();
	mf->Reflectivity = 0.4;
	mf->Specular = 0.0;
	p->Material = mf;

	Checkerboard* cp = new Checkerboard(false, L"cbfloor");
	cp->SetColours(Colour(0.35, 0.35, 0.35), Colour(0.65, 0.65, 0.65));
	p->Material->SetPattern(cp);

	p->AddTransform({ TransformType::RotateY, Matrix4(1, 0.31415), Quaternion(), 0.31415 });
	Objects.push_back(p);

	// blender has a default cube, twnkl has a default sphere with a cool pattern ;)
	Sphere* s = new Sphere(L"ball");
	PhongMaterial* sm = new PhongMaterial();
	s->Material = sm;
	s->AddTransform({ TransformType::Translate, Matrix4(1, 4.6, 0.4, 1.0), Quaternion(4.6, 0.4, 1.0, 1.0), 0 });

	SphericalCheckerboard* sc = new SphericalCheckerboard(false, L"scball");
	sc->SetColours(Colour(0.8, 0.4, 0.0), Colour(0.2, 0.1, 0.0));
	sc->SetDimensions(16, 8);

	s->Material->SetPattern(sc);

	Objects.push_back(s);

	Quaternion campos = Quaternion(-2.6, 1.5, -3.9, 1.0);

	Quaternion to(-0.6, 1, -0.8, 1.0);
	Quaternion up(0.0, 1.0, 0.0, 0.0);

	Cam->Transform = campos.ViewTransform(to, up);
	Cam->Width = 500;
	Cam->Height = 250;

	Cam->SetViewport(campos, to, up);
	GWorld->Cam->CalculatePixelSize();

	Finalise();
}
#endif


#ifdef _DEBUG
#ifndef _GUI
void World::DefaultWorld(int testid)
{
	PointLight* l = new PointLight(L"pointlight", 1.0, 1.0, 1.0, -10, 10, -10);
	//Light l = Light(1.0, 1.0, 1.0, 0, 0.25, 0);

	Lights.push_back(l);

	Sphere* s1 = new Sphere(L"");
	if (testid == 158)
	{
		PhongMaterial* m1 = new PhongMaterial(); // 158 needs the default
		s1->Material = m1;
	}
	else
	{
		PhongMaterial* m1 = new PhongMaterial(0.8, 1.0, 0.6, 0.1, 0.7, 0.1, 1.0, 200.0, 0.2, 0.0);
		s1->Material = m1;
	}
		
	Objects.push_back(s1);

	Sphere* s2 = new Sphere(L"");

	s2->AddTransform({ TransformType::Scale, Matrix4(0, 0.5, 0.5, 0.5), Quaternion(), 0 });

	PhongMaterial* m2 = new PhongMaterial();
	s2->Material = m2;

	Objects.push_back(s2);

	switch (testid)
	{
	case 143:
		Objects[1]->Material->Ambient = 1.0;
		break;
	case 156:
		Objects[0]->Material->Transparency = 1.0;
		Objects[0]->Material->RefractiveIndex = 1.5;
		break;
	case 158:
	{
		Objects[0]->Material->Ambient = 1.0;

		TestPattern* p = new TestPattern(false, L"TestPattern");
		p->ProcessTransforms();

		Objects[0]->Material->SetPattern(p);

		Objects[1]->Material->Transparency = 1.0;
		Objects[1]->Material->RefractiveIndex = 1.5;
		break;
	}
	case 159:
	{
		Plane* p = new Plane(L"");
		PhongMaterial* m3 = new PhongMaterial();
		//m3->Reflectivity = 0.5;
		m3->Transparency = 0.5;
		m3->RefractiveIndex = 1.5;
		p->Material = m3;
		p->AddTransform({ TransformType::Translate, Matrix4(1, 0, -1, 0), Quaternion(), 0 });

		Objects.push_back(p);

		Sphere* s4 = new Sphere(L"");
		PhongMaterial* m4 = new PhongMaterial();
		m4->SurfaceColour = Colour(1, 0, 0);
		m4->Ambient = 0.5;
		s4->AddTransform({ TransformType::Translate, Matrix4(1, 0, -3.5, -0.5), Quaternion(), 0 });
		s4->Material = m4;

		Objects.push_back(s4);

		break;
	}
	case 164:
	{
		Plane* p = new Plane(L"");
		PhongMaterial* m3 = new PhongMaterial();
		m3->Reflectivity = 0.5;
		m3->Transparency = 0.5;
		m3->RefractiveIndex = 1.5;
		p->Material = m3;

		p->Transform = Matrix4(1, 0, -1, 0);

		Objects.push_back(p);

		Sphere* s4 = new Sphere(L"");
		PhongMaterial* m4 = new PhongMaterial();
		m4->SurfaceColour = Colour(1, 0, 0);
		m4->Ambient = 0.5;
		s4->Transform = Matrix4(1, 0, -3.5, -0.5);
		s4->Material = m4;

		Objects.push_back(s4);

		break;
	}
	}

	Quaternion campos = Quaternion(0, 1.5, -5.0, 1.0);
	
	Quaternion to(0, 1.0, 0, 1.0);
	Quaternion up(0, 1.0, 0.0, 0.0);

	Cam->Transform = campos.ViewTransform(to, up);

	Finalise();
}
#endif
#endif