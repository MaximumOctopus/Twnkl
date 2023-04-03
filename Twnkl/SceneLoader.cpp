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

#include "SceneLoader.h"
#include "TextureLoader.h"

#include "AreaLight.h"
#include "PointLight.h"

#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Model.h"
#include "Plane.h"
#include "Sphere.h"
#include "World.h"

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
#ifdef _CONSOLE
#include "TestPattern.h"
#endif

#include "TransformConfiguration.h"

#ifdef _GUI
SceneLoader* GSceneLoader;
#endif

extern World* GWorld;


SceneLoader::SceneLoader()
{

}


SceneLoader::SceneLoader(const std::wstring file_name, int shadow_detail)
{
	GUIProperties gui;

	Loaded = LoadScene(file_name, shadow_detail, gui);
}


std::pair<int, int> SceneLoader::ResizeForDisplay(double dx, double dy, double cx, double cy)
{
	double scene_aspect = cx / cy;

	double xratio = dx / cx;
	double yratio = dy / cy;

	if (xratio > yratio)
	{
		return { std::floor(scene_aspect * dy), std::floor(dy) };
	}

	return { std::floor(dx), std::floor((1.0 / scene_aspect) * dx) };	
}


TransformType SceneLoader::TransformTypeFrom(const std::wstring input)
{
	if (input == L"scale")
	{
		return TransformType::Scale;
	}
	else if (input == L"translate")
	{
		return TransformType::Translate;
	}
	else if (input == L"rotatex")
	{
		return TransformType::RotateX;
	}
	else if (input == L"rotatey")
	{
		return TransformType::RotateY;
	}
	else if (input == L"rotatez")
	{
		return TransformType::RotateZ;
	}

	return TransformType::None;
}


// input in the form r,g,b
Colour SceneLoader::ColourFrom(const std::wstring input)
{
	int mode = 0;
	double components[3] = { 0, 0, 0 };
	std::wstring temp = L"";

	for (int t = 0; t < input.length(); t++)
	{
		if (t == input.length() - 1 && input[t] != ' ')
		{
			temp += input[t];
		}

		if (input[t] == ',' || t == input.length() - 1)
		{
			if (temp != L"")
			{
				components[mode] = stod(temp);
			}

			mode++;
			temp = L"";
		}
		else if (input[t] != ' ')
		{
			temp += input[t];
		}
	}

	return Colour(components[0], components[1], components[2]);
}



SceneLoader::Chunk SceneLoader::GetDataBlockChunkFrom(const std::wstring name)
{
	for (int t = 0; t < BlockTitlesCount; t++)
	{
		if (BlockTitles[t] == name)
		{
			return BlockChunk[t];
		}
	}

	std::wcout << name << L"\n";
	
	return Chunk::None;
}


Quaternion SceneLoader::XYZFrom(const std::wstring input, int w)
{
	int mode = 0;
	double components[3] = { 0, 0, 0 };
	std::wstring temp = L"";

	for (int t = 0; t < input.length(); t++)
	{
		if (t == input.length() - 1 && input[t] != ' ')
		{
			temp += input[t];
		}

		if (input[t] == ',' || t == input.length() - 1)
		{
			if (temp != L"")
			{
				components[mode] = stod(temp);
			}

			mode++;
			temp = L"";
		}
		else if (input[t] != ' ')
		{
			temp += input[t];
		}
	}

	return Quaternion(components[0], components[1], components[2], w);
}


// returns the correct pattern for the object type
SceneLoader::Pattern SceneLoader::PatternFromObject(Chunk object, Chunk pattern)
{
	switch (pattern)
	{
	case Chunk::PatternChecker:
		switch (object)
		{
		case Chunk::ObjectCone:
		case Chunk::ObjectCylinder:
			return Pattern::CylinderChecker;
		case Chunk::ObjectCube:
			return Pattern::CubeChecker;
		case Chunk::ObjectPlane:
			return Pattern::Checker;
		case Chunk::ObjectSphere:
			return Pattern::SphericalChecker;
		}
		break;
	case Chunk::PatternGradient:
		return Pattern::Gradient;
	case Chunk::PatternGradient2:
		return Pattern::Gradient2;
	case Chunk::PatternRing:
		return Pattern::Ring;
	case Chunk::PatternStripey:
		return Pattern::Stripey;
	case Chunk::PatternPerlin:
		return Pattern::Perlin;
	case Chunk::PatternPerlin2:
		return Pattern::Perlin2;
	case Chunk::PatternPerlin3:
		return Pattern::Perlin3;
	case Chunk::PatternFractal:
		return Pattern::Fractal;
	case Chunk::PatternSimplex:
		return Pattern::Simplex;
	case Chunk::PatternTexture:
		switch (object)
		{
		case Chunk::ObjectCone:
		case Chunk::ObjectCylinder:
			return Pattern::CylinderTexture;
		case Chunk::ObjectCube:
			return Pattern::CubicTexture;
		case Chunk::ObjectPlane:
			return Pattern::PlanarTexture;
		case Chunk::ObjectSphere:
			return Pattern::SphericalTexture;
		}
		break;
	}
	
	return Pattern::None;
}


void SceneLoader::ObjectSetPattern(Pattern pattern, Colour a, Colour b, std::wstring file_name, PatternProperties properties)
{
	bool greyscale = false;

	if (properties.process == ImageProcess::Greyscale)
	{
		greyscale = true;
	}

	switch (pattern)
	{
	case Pattern::Checker:
	{
		Checkerboard* p = new Checkerboard(L"Checkboard");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Gradient:
	{
		Gradient* p = new Gradient(L"Gradient");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Gradient2:
	{
		Gradient2* p = new Gradient2(L"Gradient2");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Ring:
	{
		Ring* p = new Ring(L"Ring");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Stripey:
	{
		Stripey* p = new Stripey(L"Stripey");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Perlin:
	{
		Perlin* p = new Perlin(L"Perlin");
		p->SetColours(a, b);
		p->SetDimensions(properties.u, properties.v, properties.scale);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Perlin2:
	{
		Perlin2* p = new Perlin2(L"Perlin2");
		p->SetColours(a, b);
		p->SetDimensions(properties.u, properties.v, properties.scale);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Perlin3:
	{
		Perlin3* p = new Perlin3(L"Perlin3");
		p->SetColours(a, b);
		p->SetDimensions(properties.u, properties.v, properties.scale, properties.phase);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Fractal:
	{
		Fractal* p = new Fractal(L"Fractal");
		p->SetColours(a, b);
		p->SetFALP(properties.frequency, properties.amplitude, properties.lacunarity, properties.persistence);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::Simplex:
	{
		Simplex* p = new Simplex(L"Simplex");
		p->SetColours(a, b);
		p->Simple = properties.simple;
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::SphericalChecker:
	{
		SphericalCheckerboard* p = new SphericalCheckerboard(L"SphericalChecker");
		p->SetColours(a, b);
		p->SetDimensions(properties.u, properties.v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::CylinderChecker:
	{
		CylinderCheckerboard* p = new CylinderCheckerboard(L"CylinderChecker");
		p->SetColours(a, b);
		p->SetDimensions(properties.u, properties.v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::CubeChecker:
	{
		CubeChecker* p = new CubeChecker(L"CubeChecker");
		p->SetColours(a, b);
		p->SetDimensions(properties.u, properties.v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Pattern::SphericalTexture:
	{
		SphericalTexture* p = new SphericalTexture(L"SphericalTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, file_name, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << file_name << L"\"\n";
		}

		break;
	}
	case Pattern::PlanarTexture:
	{
		PlanarTexture* p = new PlanarTexture(L"PlanarTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, file_name, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << file_name << L"\"\n";
		}

		break;
	}
	case Pattern::CubicTexture:
	{
		CubeTexture* p = new CubeTexture(L"CubicTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, file_name, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << file_name << L"\"\n";
		}

		break;
	}
	case Pattern::CylinderTexture:
	{
		CylinderTexture* p = new CylinderTexture(L"CylinderTexture");

		TextureLoader tl;

		if (tl.Go(&p->Texture, file_name, greyscale))
		{
			p->Width = tl.TextureWidth;
			p->Height = tl.TextureHeight;

			GWorld->Objects.back()->Material->SetPattern(p);
		}
		else
		{
			std::wcout << L"error loading texture \"" << file_name << L"\"\n";
		}

		break;
	}
	}
}


SceneLoader::FileProperty SceneLoader::GetInputProperty(std::wstring input)
{
	for (int t = 0; t < kPropertyListCount; t++)
	{
		if (input == FilePropertyList[t])
		{
			return FilePropertyReference[t];
		}
	}

	return FileProperty::NotFound;
}


void SceneLoader::AddObject(Chunk chunk, std::wstring name, std::wstring file_name, int min, int max, bool closed)
{
	switch (chunk)
	{
	case Chunk::ObjectSphere:
		GWorld->Objects.push_back(new Sphere(name));
		break;
	case Chunk::ObjectPlane:
		GWorld->Objects.push_back(new Plane(name));
		break;
	case Chunk::ObjectCone:
	{
		Cone* cone = new Cone(name);
		cone->SetParameters(min, max, closed);

		GWorld->Objects.push_back(cone);
		break;
	}
	case Chunk::ObjectCube:
		GWorld->Objects.push_back(new Cube(name));
		break;
	case Chunk::ObjectCylinder:
	{
		Cylinder* cylinder = new Cylinder(name);
		cylinder->SetParameters(min, max, closed);

		GWorld->Objects.push_back(cylinder);
		break;
	}
	case Chunk::ObjectModel:
	{
		Model* model = new Model(name);
		model->Load(file_name);

		GWorld->Objects.push_back(model);
		break;
	}
	case Chunk::ObjectModelSmooth:
	{
		break;
	}
	}
}


bool SceneLoader::ValidateParameter(bool condition, std::wstring parameter, int line)
{
	if (!condition)
	{
		std::wcout << L"  Error               : \"" << parameter << L"\" found in incorrect data block at line " << line << L"\n";
	}

	return condition;
}


// twnkl scene file format
bool SceneLoader::LoadScene(const std::wstring file_name, int shadow_detail, GUIProperties gui)
{
	std::wifstream file(file_name);

	if (file)
	{
		int Line = 1;

		int MaterialCount = 0;
		int TransformCount = 0;
		int PatternCount = 0;

		std::wstring s(L"");

		Matrix4 Transform;

		Chunk mode = Chunk::None;
		Chunk last_object = Chunk::None;
		Chunk last_chunk = Chunk::None;

		Colour Colours[2] = { Colour(0, 0, 0), Colour(0, 0, 0) };
		int ColourIndex = 0;

		std::wstring Name = L"";
		std::wstring FileName = L"";

		PatternProperties pattern_properties;
		MaterialProperties material_properties;

		double angle = 0;
		TransformType tt = TransformType::None;
		Quaternion XYZ;
		Quaternion UVector;
		Quaternion VVector;
		Quaternion CameraFrom;
		Quaternion CameraTo;
		Quaternion CameraUp;
		int Minimum = 0; // for cylinders
		int Maximum = 0;
		bool Closed = 0;

		while (std::getline(file, s))
		{
			if (s != L"")
			{
				if (s[0] == L'/' || s[0] == L'#')
				{
					// comment, do nothing
				}
				else
				{
					auto equals = s.find(L'=');
					FileProperty PropertyName = FileProperty::None;

					std::wstring key = s.substr(0, equals);
					std::wstring value = s.substr(equals + 1);

					if (equals == std::wstring::npos)
					{
						key = s;
					}

					PropertyName = GetInputProperty(key);

					switch (PropertyName)
					{
					case FileProperty::None:
						break;
					case FileProperty::NotFound:
						std::wcout << L"Unknown property key \"" << key << L"\" on line " << Line << L" of scene file.\n";
						break;
					case FileProperty::DataBegin:
					{
						std::wstring chunk = s.substr(1);

						mode = GetDataBlockChunkFrom(chunk);

						switch (mode)
						{
						case Chunk::ObjectSphere:
						case Chunk::ObjectPlane:
						case Chunk::ObjectCube:
						case Chunk::ObjectCone:
						case Chunk::ObjectCylinder:
						case Chunk::ObjectModel:
						case Chunk::ObjectModelSmooth:
							last_object = mode;
							last_chunk = mode;
							break;
						case Chunk::Material:
							mode = Chunk::Material;
							MaterialCount++;
							break;
						case Chunk::PatternChecker:
						case Chunk::PatternGradient:
						case Chunk::PatternGradient2:
						case Chunk::PatternRing:
						case Chunk::PatternStripey:
						case Chunk::PatternPerlin:
						case Chunk::PatternPerlin2:
						case Chunk::PatternPerlin3:
						case Chunk::PatternTexture:
						case Chunk::PatternFractal:
						case Chunk::PatternSimplex:
							last_chunk = mode;
							PatternCount++;
							break;
						case Chunk::Transform:
							TransformCount++;
							break;
						case Chunk::PointLight:
						case Chunk::AreaLight:
							last_chunk = mode;
							break;
						case Chunk::Camera:
							break;
						case Chunk::None:
							//last_object = mode;
							break;
						}
						break;
					}
					case FileProperty::DataEnd:
					{
						switch (mode)
						{
						case Chunk::ObjectSphere:
						case Chunk::ObjectPlane:
						case Chunk::ObjectCone:
						case Chunk::ObjectCube:
						case Chunk::ObjectCylinder:
						case Chunk::ObjectModel:
						case Chunk::ObjectModelSmooth:
							AddObject(mode, Name, FileName, Minimum, Maximum, Closed);
							break;
						case Chunk::Material:
							GWorld->Objects.back()->Material = new PhongMaterial(Colours[0].r, Colours[0].g, Colours[0].b,
								material_properties.ambient, material_properties.diffuse, material_properties.reflectivity, material_properties.refractiveindex, material_properties.shininess, material_properties.specular, material_properties.transparent);
							break;
						case Chunk::PatternChecker:
						case Chunk::PatternGradient:
						case Chunk::PatternGradient2:
						case Chunk::PatternRing:
						case Chunk::PatternStripey:
						case Chunk::PatternPerlin:
						case Chunk::PatternPerlin2:
						case Chunk::PatternPerlin3:
						case Chunk::PatternTexture:
						case Chunk::PatternFractal:
						case Chunk::PatternSimplex:
							ObjectSetPattern(PatternFromObject(last_object, mode), Colours[0], Colours[1], FileName, pattern_properties);
							break;
						case Chunk::Transform:
						{
							switch (tt)
							{
							case TransformType::Scale:
								Transform = Matrix4(0, XYZ.x, XYZ.y, XYZ.z);
								break;
							case TransformType::Translate:
								Transform = Matrix4(1, XYZ.x, XYZ.y, XYZ.z);
								break;
							case TransformType::RotateX:
								Transform = Matrix4(0, angle);
								break;
							case TransformType::RotateY:
								Transform = Matrix4(1, angle);
								break;
							case TransformType::RotateZ:
								Transform = Matrix4(2, angle);
								break;
							}

							// are there transforms to add to the last object?
							switch (last_chunk)
							{
							case Chunk::ObjectSphere:
							case Chunk::ObjectPlane:
							case Chunk::ObjectCone:
							case Chunk::ObjectCube:
							case Chunk::ObjectCylinder:
							case Chunk::ObjectModel:
							case Chunk::ObjectModelSmooth:
							{
								TransformConfiguration tc;
								tc.Type = tt;
								tc.Transform = Transform;
								tc.Angle = angle;
								tc.XYZ = XYZ;

								GWorld->Objects.back()->AddTransform(tc);
								break;
							}
							case Chunk::PatternChecker:
							case Chunk::PatternGradient:
							case Chunk::PatternGradient2:
							case Chunk::PatternRing:
							case Chunk::PatternStripey:
							case Chunk::PatternPerlin:
							case Chunk::PatternPerlin2:
							case Chunk::PatternPerlin3:
							case Chunk::PatternTexture:
							case Chunk::PatternFractal:
							case Chunk::PatternSimplex:
							{
								TransformConfiguration tc;
								tc.Type = tt;
								tc.Transform = Transform;
								tc.Angle = angle;
								tc.XYZ = XYZ;

								GWorld->Objects.back()->Material->SurfacePattern->AddTransform(tc);
								break;
							}
							}

							break;
						}
						case Chunk::PointLight:
						{
							PointLight* l = new PointLight(Name, Colours[0].r, Colours[0].g, Colours[0].b, XYZ.x, XYZ.y, XYZ.z);

							GWorld->Lights.push_back(l);
							break;
						}
						case Chunk::AreaLight:
						{
							AreaLight* l = new AreaLight(Name, Colours[0].r, Colours[0].g, Colours[0].b, XYZ.x, XYZ.y, XYZ.z);

							l->SetDimensions(UVector, VVector, shadow_detail);

							GWorld->Lights.push_back(l);
							break;
						}
						}

						ColourIndex = 0;
						Colours[0].Reset();
						Colours[1].Reset();
						Minimum = 0;
						Maximum = 0;
						Closed = false;
						pattern_properties.Clear();
						material_properties.Clear();

						break;
					}
					case FileProperty::Colour:						// colour in the form r,g,b
						if (ValidateParameter(mode == Chunk::Material || mode == Chunk::PointLight || mode == Chunk::AreaLight ||
							mode == Chunk::PatternChecker || mode == Chunk::PatternGradient || mode == Chunk::PatternGradient2 || mode == Chunk::PatternRing ||
							mode == Chunk::PatternStripey || mode == Chunk::PatternPerlin || mode == Chunk::PatternPerlin2 || mode == Chunk::PatternPerlin3 ||
							mode == Chunk::PatternFractal || mode == Chunk::PatternSimplex,
							L"colour", Line))
						{
							Colours[ColourIndex] = ColourFrom(value);

							ColourIndex++;
						}
						break;
					case FileProperty::Position:
					{
						XYZ = XYZFrom(value, 0);
						break;
					}
					case FileProperty::Name:
						if (ValidateParameter(mode == Chunk::ObjectSphere || mode == Chunk::ObjectPlane || mode == Chunk::ObjectCone || mode == Chunk::ObjectCube || mode == Chunk::ObjectCylinder || mode == Chunk::ObjectModel ||
							mode == Chunk::PointLight || mode == Chunk::AreaLight,
							L"name", Line))
						{
							Name = value;
						}
						break;
					case FileProperty::Ambience:					// ambient
						if (ValidateParameter(mode == Chunk::Material, L"ambience", Line))
						{
							material_properties.ambient = stod(value);
						}
						break;
					case FileProperty::Diffuse:						// difuse
						if (ValidateParameter(mode == Chunk::Material, L"diffuse", Line))
						{
							material_properties.diffuse = stod(value);
						}
						break;
					case FileProperty::Reflectivity:				// reflectivity
						if (ValidateParameter(mode == Chunk::Material, L"reflectivity", Line))
						{
							material_properties.reflectivity = stod(value);
						}
						break;
					case FileProperty::RefractiveIndex:				// index of refraction
						if (ValidateParameter(mode == Chunk::Material, L"refractiveindex", Line))
						{
							material_properties.refractiveindex = stod(value);
						}
						break;
					case FileProperty::Shininess:					// shininess
						if (ValidateParameter(mode == Chunk::Material, L"shininess", Line))
						{
							material_properties.shininess = stod(value);
						}
						break;
					case FileProperty::Specular:					// specular
						if (ValidateParameter(mode == Chunk::Material, L"specular", Line))
						{
							material_properties.specular = stod(value);
						}
						break;
					case FileProperty::Transparency:				// transparency
						if (ValidateParameter(mode == Chunk::Material, L"transparency", Line))
						{
							material_properties.transparent = stod(value);
						}
						break;
					case FileProperty::TransformType:
						if (ValidateParameter(mode == Chunk::Transform, L"type", Line))
						{
							tt = TransformTypeFrom(value);

							if (tt == TransformType::None)
							{
								std::wcout << L"  Error               : invalid transform type \"" << value << "\" found at line " << Line << L"\n";
							}
						}
						break;
					case FileProperty::Angle:
						if (ValidateParameter(mode == Chunk::Transform, L"angle", Line))
						{
							if (tt == TransformType::RotateX || tt == TransformType::RotateY || tt == TransformType::RotateZ)
							{
								angle = stod(value);
							}
							else
							{
								std::wcout << L"  Error               : \"angle\" only valid for rotatex, rotatey, and rotatez transforms. line " << Line << L"\n";
							}
						}
						break;
					case FileProperty::XYZ:
						if (ValidateParameter(mode == Chunk::Transform, L"xyz", Line))
						{
							if (tt == TransformType::Scale || tt == TransformType::Translate)
							{
								XYZ = XYZFrom(value, 0);
							}
							else
							{
								std::wcout << L"  Error               : \"xyz\" only valid for translate and scale transforms. line " << Line << L"\n";
							}
						}
						break;
					case FileProperty::FocalLength:
						if (ValidateParameter(mode == Chunk::Camera, L"focallength", Line))
						{
							GWorld->Cam->FoV = stod(value);
						}
						break;
					case FileProperty::CameraFrom:
						if (ValidateParameter(mode == Chunk::Camera, L"from", Line))
						{
							CameraFrom = XYZFrom(value, 1);
						}
						break;
					case FileProperty::CameraUp:
						if (ValidateParameter(mode == Chunk::Camera, L"up", Line))
						{
							CameraUp = XYZFrom(value, 0);
						}
						break;
					case FileProperty::CameraTo:
						if (ValidateParameter(mode == Chunk::Camera, L"to", Line))
						{
							CameraTo = XYZFrom(value, 1);
						}
						break;
					case FileProperty::CanvasWidth:
						if (GWorld->Cam->Width == 0)				// allows command-line parameter to override scene parameters
						{
							GWorld->Cam->Width = stoi(value);
						}
						break;
					case FileProperty::CanvasHeight:
						if (GWorld->Cam->Height == 0)				// allows command-line parameter to override scene parameters
						{
							GWorld->Cam->Height = stoi(value);
						}
						break;
					case FileProperty::Minimum:
						if (ValidateParameter(mode == Chunk::ObjectCone || mode == Chunk::ObjectCylinder, L"minimum", Line))
						{
							Minimum = stoi(value);
						}
						break;
					case FileProperty::Maximum:
						if (ValidateParameter(mode == Chunk::ObjectCone || mode == Chunk::ObjectCylinder, L"maximum", Line))
						{
							Maximum = stoi(value);
						}
						break;
					case FileProperty::Closed:
						if (ValidateParameter(mode == Chunk::ObjectCone || mode == Chunk::ObjectCylinder, L"closed", Line))
						{
							Closed = true;
						}
						break;
					case FileProperty::UVector:
						if (ValidateParameter(mode == Chunk::AreaLight, L"uvector", Line))
						{
							UVector = XYZFrom(value, 0);
						}
						break;
					case FileProperty::VVector:
						if (ValidateParameter(mode == Chunk::AreaLight, L"vvector", Line))
						{
							VVector = XYZFrom(value, 0);
						}
						break;
					case FileProperty::TextureWidth:
						pattern_properties.u = stod(value);
						break;
					case FileProperty::TextureHeight:
						pattern_properties.v = stod(value);
						break;
					case FileProperty::FileName:
						if (ValidateParameter(mode == Chunk::ObjectModel || mode == Chunk::PatternTexture, L"filename", Line))
						{
							FileName = value;
						}
						break;
					case FileProperty::Process:
						if (ValidateParameter(mode == Chunk::PatternTexture, L"process", Line))
						{
							if (value == L"greyscale")
							{
								pattern_properties.process = ImageProcess::Greyscale;
							}
						}
						break;
					case FileProperty::Scale:
						if (ValidateParameter(mode == Chunk::PatternPerlin || mode == Chunk::PatternPerlin2 || mode == Chunk::PatternPerlin3, L"scale", Line))
						{
							pattern_properties.scale = stod(value);
						}
						break;
					case FileProperty::Phase:
						if (ValidateParameter(mode == Chunk::PatternFractal, L"phase", Line))
						{
							pattern_properties.phase = stod(value);
						}
						break;
					case FileProperty::Frequency:
						if (ValidateParameter(mode == Chunk::PatternFractal, L"frequency", Line))
						{
							pattern_properties.frequency = stod(value);
						}
						break;
					case FileProperty::Amplitude:
						if (ValidateParameter(mode == Chunk::PatternFractal, L"amplitude", Line))
						{
							pattern_properties.amplitude = stod(value);
						}
						break;
					case FileProperty::Lacunarity:
						if (ValidateParameter(mode == Chunk::PatternFractal, L"lacunarity", Line))
						{
							pattern_properties.lacunarity = stod(value);
						}
						break;
					case FileProperty::Persistence:
						if (ValidateParameter(mode == Chunk::PatternFractal, L"persistence", Line))
						{
							pattern_properties.persistence = stod(value);
						}
						break;
					case FileProperty::Simple:
						if (ValidateParameter(mode == Chunk::PatternFractal, L"simple", Line))
						{
							pattern_properties.simple = true;
						}
						break;
					}

				}
			}

			Line++;
		}

		std::wcout << L"  Loaded              : " << GWorld->Objects.size() << " objects, " << GWorld->Lights.size() << L" lights, " << MaterialCount << L" materials, " << TransformCount << L" transforms.\n";

		file.close();

		if (gui.ResizeToDisplay)
		{
			std::pair<int, int> newsize = ResizeForDisplay(gui.DisplayWidth, gui.DisplayHeight, GWorld->Cam->Width, GWorld->Cam->Height);

			GWorld->Cam->Width = newsize.first;
			GWorld->Cam->Height = newsize.second;
		}

		Quaternion campos = CameraFrom;
		GWorld->Cam->Transform = campos.ViewTransform(CameraTo, CameraUp);
		GWorld->Cam->CalculatePixelSize();

		return true;
	}

	std::wcout << L"\n  Error Loading Scene : " << file_name << L"\n";

	return false;
}