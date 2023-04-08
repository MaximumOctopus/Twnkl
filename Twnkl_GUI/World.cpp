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

#ifdef _DEBUG
#include "PointLight.h"
#ifndef _GUI
#include "TestPattern.h"
#endif
#endif

#ifdef _GUI
#include "PointLight.h"
#endif

#include "Checkerboard.h"
#include "CubeCheckerboard.h"
#include "CubeTexture.h"
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
				std::wcout << L"    Object (" << t << L", " << Objects[t]->Name << L") has zero IoR! This will cause rendering issues.\n";
			}

			if (Objects[t]->Material->HasPattern)
			{
				Objects[t]->Material->SurfacePattern->ProcessTransforms();
			}

			Objects[t]->PostSetup(t);
		}
		else
		{
			std::wcout << L"    Object (" << t << L", " << Objects[t]->Name << L") has no assigned material! This will cause serious rendering issues.\n";

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
		std::wcout << L"  Saving image        : " << file_name << L"\n";

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


void World::AddNewObject(int primitive, AvailablePatterns pattern, PatternProperties properties, std::wstring name)
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

	if (pattern != AvailablePatterns::None)
	{
		SetLastObjectPattern(pattern, properties);
	}
}


void World::SetLastObjectPattern(AvailablePatterns pattern, PatternProperties properties)
{
	bool greyscale = false;

	if (properties.process == ImageProcess::Greyscale)
	{
		greyscale = true;
	}

	switch (pattern)
	{
	case AvailablePatterns::Checker:
	{
		Checkerboard* p = new Checkerboard(L"Checkboard");
		p->SetColours(properties.Colour1, properties.Colour2);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Gradient:
	{
		Gradient* p = new Gradient(L"Gradient");
		p->SetColours(properties.Colour1, properties.Colour2);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Gradient2:
	{
		Gradient2* p = new Gradient2(L"Gradient2");
		p->SetColours(properties.Colour1, properties.Colour2);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Ring:
	{
		Ring* p = new Ring(L"Ring");
		p->SetColours(properties.Colour1, properties.Colour2);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Stripey:
	{
		Stripey* p = new Stripey(L"Stripey");
		p->SetColours(properties.Colour1, properties.Colour2);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Perlin:
	{
		Perlin* p = new Perlin(L"Perlin");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetDimensions(properties.u, properties.v, properties.scale);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Perlin2:
	{
		Perlin2* p = new Perlin2(L"Perlin2");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetDimensions(properties.u, properties.v, properties.scale);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Perlin3:
	{
		Perlin3* p = new Perlin3(L"Perlin3");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetDimensions(properties.u, properties.v, properties.scale, properties.phase);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Fractal:
	{
		Fractal* p = new Fractal(L"Fractal");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetFALP(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::Simplex:
	{
		Simplex* p = new Simplex(L"Simplex");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->Simple = properties.simple;
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::SphericalChecker:
	{
		SphericalCheckerboard* p = new SphericalCheckerboard(L"SphericalChecker");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetDimensions(properties.u, properties.v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::CylinderChecker:
	{
		CylinderCheckerboard* p = new CylinderCheckerboard(L"CylinderChecker");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetDimensions(properties.u, properties.v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::CubeChecker:
	{
		CubeChecker* p = new CubeChecker(L"CubeChecker");
		p->SetColours(properties.Colour1, properties.Colour2);
		p->SetDimensions(properties.u, properties.v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case AvailablePatterns::SphericalTexture:
	{
		SphericalTexture* p = new SphericalTexture(L"SphericalTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, properties.FileName, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << properties.FileName << L"\"\n";
		}

		break;
	}
	case AvailablePatterns::PlanarTexture:
	{
		PlanarTexture* p = new PlanarTexture(L"PlanarTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, properties.FileName, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << properties.FileName << L"\"\n";
		}

		break;
	}
	case AvailablePatterns::CubicTexture:
	{
		CubeTexture* p = new CubeTexture(L"CubicTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, properties.FileName, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << properties.FileName << L"\"\n";
		}

		break;
	}
	case AvailablePatterns::CylinderTexture:
	{
		CylinderTexture* p = new CylinderTexture(L"CylinderTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, properties.FileName, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << properties.FileName << L"\"\n";
		}

		break;
	}
	}
}
		  /*
{camera
width=400
height=200
focallength=1.152
from=-2.6, 1.5, -3.9
to=-0.6, 1, -0.8
up=0.0, 1.0, 0.0
}
            */

#ifdef _GUI
void World::DefaultScene()
{
	PointLight* l = new PointLight(L"pointlight", 1.0, 1.0, 1.0, -4.9, 4.9, -1);
	Lights.push_back(l);

	Plane* p = new Plane(L"floor");
	PhongMaterial* mf = new PhongMaterial();
	mf->Reflectivity = 0.4;
	mf->Specular = 0.0;
	p->Material = mf;

	Checkerboard* cp = new Checkerboard(L"cbfloor");
	cp->SetColours(Colour(0.35, 0.35, 0.35), Colour(0.65, 0.65, 0.65));
	p->Material->SetPattern(cp);

	p->AddTransform({ TransformType::RotateY, Matrix4(1, 0.31415), Quaternion(), 0.31415 });
	Objects.push_back(p);

	Sphere* s = new Sphere(L"ball");
	PhongMaterial* sm = new PhongMaterial();
	s->Material = sm;
	s->AddTransform({ TransformType::Translate, Matrix4(1, 4.6, 0.4, 1.0), Quaternion(4.6, 0.4, 1.0, 1.0), 0 });

	SphericalCheckerboard* sc = new SphericalCheckerboard(L"scball");
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

		TestPattern* p = new TestPattern(L"TestPattern");
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