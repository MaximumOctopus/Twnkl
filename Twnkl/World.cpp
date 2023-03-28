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

#ifdef _DEBUG
#include "Plane.h"
#include "Sphere.h"
#include "TestPattern.h"
#endif

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


bool World::Finalise()
{
	bool HasErrors = false;

	for (int t = 0; t < Objects.size(); t++)
	{
		Objects[t]->ID = t;

		Objects[t]->CreateInverseTransform();

		// sanity checking...
		if (Objects[t]->Material != nullptr)
		{		
			if (Objects[t]->Material->RefractiveIndex == 0)
			{
				std::wcout << L"    Object (" << t << L", " << Objects[t]->Name << L") has zero IoR! This will cause rendering issues.\n";
			}

			if (Objects[t]->Material->HasPattern)
			{
				Objects[t]->Material->SurfacePattern->Finalise();
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

	Canvas = new Colour[Cam->Width * Cam->Height];

	Cam->InverseTransform = Cam->Transform.Inverse();

	return HasErrors;
}


// =================================================================================
// == File Output ==================================================================
// =================================================================================


std::string World::ColourToPPM(Colour c)
{
	int r = static_cast<int>(c.r * 255);
	int g = static_cast<int>(c.g * 255);
	int b = static_cast<int>(c.b * 255);

	if (r > 255)
	{
		r = 255;
	}
	else if (r < 0)
	{
		r = 0;
	}

	if (g > 255)
	{
		g = 255;
	}
	else if (g < 0)
	{
		g = 0;
	}

	if (b > 255)
	{
		b = 255;
	}
	else if (b < 0)
	{
		b = 0;
	}

	return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b) + " ";
}


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
				row += ColourToPPM(Canvas[y * GWorld->Cam->Width + x]);
			}

			file << row << "\n";
		}

		file.close();

		return true;
	}

	return false;
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
		}

		std::wcout << "\n";
	}

	for (int t = 0; t < Lights.size(); t++)
	{
		std::wcout << L" Light " << t << L" (" << Lights[t]->ID << L")\n";
		std::wcout << L"    Position   : " << Lights[t]->Position.ToString() << L"\n";
		std::wcout << L"    Intensity  : " << Lights[t]->Intensity.ToString() << L"\n";
		std::wcout << L"    Detail     : " << Lights[t]->ToString() << L"\n";

		std::wcout << "\n";
	}
}


#ifdef _DEBUG
void World::DefaultWorld(int testid)
{
	Light* l = new Light(1.0, 1.0, 1.0, -10, 10, -10);
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

	s2->SetTransform(Matrix4(0, 0.5, 0.5, 0.5));

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
		p->Finalise();

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