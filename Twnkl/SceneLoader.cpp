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
#include "CubeTexture.h"
#include "CylinderCheckerboard.h"
#include "Gradient.h"
#include "Gradient2.h"
#include "PlanarTexture.h"
#include "Ring.h"
#include "SphericalCheckerboard.h"
#include "SphericalTexture.h"
#include "Stripey.h"
#include "TestPattern.h"

#include "TextureLoader.h"


extern World* GWorld;


SceneLoader::SceneLoader(const std::wstring file_name, int shadow_detail)
{
	Loaded = LoadScene(file_name, shadow_detail);
}


SceneLoader::TransformType SceneLoader::TransformTypeFrom(const std::wstring input)
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


void SceneLoader::ObjectSetPattern(Chunk chunk, Colour a, Colour b, double u, double v, std::wstring file_name, ImageProcess process)
{
	bool greyscale = false;

	if (process == ImageProcess::Greyscale)
	{
		greyscale = true;
	}

	switch (chunk)
	{
	case Chunk::PatternChecker:
	{
		Checkerboard* p = new Checkerboard(L"Checkboard");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::PatternGradient:
	{
		Gradient* p = new Gradient(L"Gradient");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::PatternGradient2:
	{
		Gradient2* p = new Gradient2(L"Gradient2");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::PatternRing:
	{
		Ring* p = new Ring(L"Ring");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::PatternStripey:
	{
		Stripey* p = new Stripey(L"Stripey");
		p->SetColours(a, b);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::SphericalChecker:
	{
		SphericalCheckerboard* p = new SphericalCheckerboard(L"SphericalChecker");
		p->SetColours(a, b);
		p->SetDimensions(u, v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::CylinderChecker:
	{
		CylinderCheckerboard* p = new CylinderCheckerboard(L"CylinderChecker");
		p->SetColours(a, b);
		p->SetDimensions(u, v);
		GWorld->Objects.back()->Material->SetPattern(p);
		break;
	}
	case Chunk::SphericalTexture:
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
	case Chunk::PlanarTexture:
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
	case Chunk::CubicTexture:
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
		GWorld->Objects.push_back(new Cone(name));
		break;
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


// twnkl scene file format
bool SceneLoader::LoadScene(const std::wstring file_name, int shadow_detail)
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

		Colour Colours[2] = { Colour(0, 0, 0), Colour(0, 0, 0) };
		int ColourIndex = 0;

		ImageProcess process = ImageProcess::None;

		std::wstring Name = L"";
		std::wstring FileName = L"";

		double ambient = 0; // material
		double diffuse = 0;
		double reflectivity = 0;
		double refractiveindex = 0;
		double shininess = 0;
		double specular = 0;
		double transparent = 0;
		double angle = 0;
		double u = 0;
		double v = 0;
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
						switch (mode)
						{
						case Chunk::Transform:
						{
							// are there transforms to add to the last object?
							switch (last_object)
							{
							case Chunk::ObjectSphere:
							case Chunk::ObjectPlane:
							case Chunk::ObjectCone:
							case Chunk::ObjectCube:
							case Chunk::ObjectCylinder:
							case Chunk::ObjectModel:
							case Chunk::ObjectModelSmooth:
							{
								if (GWorld->Objects.back()->TransformSet)
								{
									GWorld->Objects.back()->Transform.MultiplyBy(Transform);
								}
								else
								{
									GWorld->Objects.back()->SetTransform(Transform);
								}

								break;
							}
							case Chunk::PatternChecker:
							case Chunk::PatternGradient:
							case Chunk::PatternGradient2:
							case Chunk::PatternRing:
							case Chunk::PatternStripey:
							{
								if (GWorld->Objects.back()->Material->SurfacePattern->TransformSet)
								{
									GWorld->Objects.back()->Material->SurfacePattern->Transform.MultiplyBy(Transform);
								}
								else
								{
									GWorld->Objects.back()->Material->SurfacePattern->SetTransform(Transform);
								}

								break;
							}
							}
							break;
						}
						}

						// ======

						std::wstring chunk = s.substr(1);

						if (chunk == L"objectsphere")
						{
							mode = Chunk::ObjectSphere;
							last_object = Chunk::ObjectSphere;
						}
						else if (chunk == L"objectplane")
						{
							mode = Chunk::ObjectPlane;
							last_object = Chunk::ObjectPlane;
						}
						else if (chunk == L"objectcube")
						{
							mode = Chunk::ObjectCube;
							last_object = Chunk::ObjectCube;
						}
						else if (chunk == L"objectcone")
						{
							mode = Chunk::ObjectCone;
							last_object = Chunk::ObjectCone;
						}
						else if (chunk == L"objectcylinder")
						{
							mode = Chunk::ObjectCylinder;
							last_object = Chunk::ObjectCylinder;
						}
						else if (chunk == L"objectmodel")
						{
							mode = Chunk::ObjectModel;
							last_object = Chunk::ObjectModel;
						}
						else if (chunk == L"objectmodelsmooth")
						{
							mode = Chunk::ObjectModelSmooth;
							last_object = Chunk::ObjectModelSmooth;
						}
						else if (chunk == L"material")
						{
							mode = Chunk::Material;

							Colours[0].r = 1.0;
							Colours[0].g = 1.0;
							Colours[0].b = 1.0;

							ambient = __DefaultMaterialAmbient;
							diffuse = __DefaultMaterialDiffuse;
							reflectivity = __DefaultMaterialReflectivity;
							refractiveindex = __DefaultMaterialRefractiveIndex;
							shininess = __DefaultMaterialShininess;
							specular = __DefaultMaterialSpecular;
							transparent = __DefaultMaterialTransparency;

							MaterialCount++;
						}
						else if (chunk == L"patternchecker")
						{
							mode = Chunk::PatternChecker;
							last_object = Chunk::PatternChecker;

							PatternCount++;
						}
						else if (chunk == L"patterngradient")
						{
							mode = Chunk::PatternGradient;
							last_object = Chunk::PatternGradient;

							PatternCount++;
						}
						else if (chunk == L"patterngradient2")
						{
							mode = Chunk::PatternGradient2;
							last_object = Chunk::PatternGradient2;

							PatternCount++;
						}
						else if (chunk == L"patternring")
						{
							mode = Chunk::PatternRing;
							last_object = Chunk::PatternRing;

							PatternCount++;
						}
						else if (chunk == L"patternstripey")
						{
							mode = Chunk::PatternStripey;
							last_object = Chunk::PatternStripey;

							PatternCount++;
						}
						else if (chunk == L"sphericalchecker")
						{
							mode = Chunk::SphericalChecker;
							last_object = Chunk::SphericalChecker;

							PatternCount++;
						}
						else if (chunk == L"sphericaltexture")
						{
							mode = Chunk::SphericalTexture;
							last_object = Chunk::SphericalTexture;

							PatternCount++;
						}
						else if (chunk == L"planartexture")
						{
							mode = Chunk::PlanarTexture;
							last_object = Chunk::PlanarTexture;

							PatternCount++;
						}
						else if (chunk == L"cubictexture")
						{
							mode = Chunk::CubicTexture;
							last_object = Chunk::CubicTexture;

							PatternCount++;
						}
						else if (chunk == L"transform")
						{
							mode = Chunk::Transform;

							TransformCount++;
						}
						else if (chunk == L"pointlight")
						{
							mode = Chunk::PointLight;
							last_object = Chunk::PointLight;
						}
						else if (chunk == L"arealight")
						{
							mode = Chunk::AreaLight;
							last_object = Chunk::AreaLight;
							}
						else
						{
							mode = Chunk::None;
							last_object = Chunk::None;
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
								ambient, diffuse, reflectivity, refractiveindex, shininess, specular, transparent);
							break;
						case Chunk::PatternChecker:
						case Chunk::PatternGradient:
						case Chunk::PatternGradient2:
						case Chunk::PatternRing:
						case Chunk::PatternStripey:
						case Chunk::SphericalChecker:
						case Chunk::SphericalTexture:
						case Chunk::PlanarTexture:
						case Chunk::CubicTexture:
							ObjectSetPattern(mode, Colours[0], Colours[1], u, v, FileName, process);
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

							break;
						}
						case Chunk::PointLight:
						{
							PointLight* l = new PointLight(Colours[0].r, Colours[0].g, Colours[0].b, XYZ.x, XYZ.y, XYZ.z);

							GWorld->Lights.push_back(l);
							break;
						}
						case Chunk::AreaLight:
						{
							AreaLight* l = new AreaLight(Colours[0].r, Colours[0].g, Colours[0].b, XYZ.x, XYZ.y, XYZ.z);

							l->SetDimensions(UVector, VVector, shadow_detail);

							GWorld->Lights.push_back(l);
							break;
						}
						}

						ColourIndex = 0;
						process = ImageProcess::None;

						break;
					}
					case FileProperty::Colour:						// colour in the form r,g,b
						if (mode == Chunk::Material || mode == Chunk::PointLight || mode == Chunk::AreaLight ||
							mode == Chunk::PatternChecker || mode == Chunk::PatternGradient || mode == Chunk::PatternGradient2 || mode == Chunk::PatternRing || mode == Chunk::PatternStripey ||
							mode == Chunk::SphericalChecker)
						{

							Colours[ColourIndex] = ColourFrom(value);

							ColourIndex++;
						}
						else
						{
							std::wcout << L"  Error               : \"colour\" found in incorrect data block on line " << Line << L"\n";
						}
						break;
					case FileProperty::Position:
					{
						XYZ = XYZFrom(value, 0);
						break;
					}
					case FileProperty::Name:
						if (mode == Chunk::ObjectSphere || mode == Chunk::ObjectPlane || mode == Chunk::ObjectCone || mode == Chunk::ObjectCube || mode == Chunk::ObjectCylinder || mode == Chunk::ObjectModel)
						{
							Name = value;
						}
						else
						{
							std::wcout << L"  Error               : \"name\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Ambience:					// ambient
						if (mode == Chunk::Material)
						{
							ambient = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"ambience\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Diffuse:						// difuse
						if (mode == Chunk::Material)
						{
							diffuse = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"diffuse\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Reflectivity:				// reflectivity
						if (mode == Chunk::Material)
						{
							reflectivity = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"reflectivity\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::RefractiveIndex:				// index of refraction
						if (mode == Chunk::Material)
						{
							refractiveindex = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"refractiveindex\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Shininess:					// shininess
						if (mode == Chunk::Material)
						{
							shininess = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"shininess\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Specular:					// specular
						if (mode == Chunk::Material)
						{
							specular = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"specular\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Transparency:				// transparency
						if (mode == Chunk::Material)
						{
							transparent = stod(value);
						}
						else
						{
							std::wcout << L"  Error               : \"transparency\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::TransformType:
						if (mode == Chunk::Transform)
						{
							tt = TransformTypeFrom(value);

							if (tt == TransformType::None)
							{
								std::wcout << L"  Error               : invalid transform type \"" << value << "\" found at line " << Line << L"\n";
							}
						}
						else
						{
							std::wcout << L"  Error               : \"type\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Angle:
						if (mode == Chunk::Transform)
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
						else
						{
							std::wcout << L"  Error               : \"angle\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::XYZ:
						if (mode == Chunk::PointLight || mode == Chunk::AreaLight || mode == Chunk::ObjectSphere || mode == Chunk::ObjectPlane || mode == Chunk::ObjectCone || mode == Chunk::ObjectCube || mode == Chunk::ObjectCylinder || mode == Chunk::Transform)
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
						else
						{
							std::wcout << L"  Error               : \"xyz\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::FocalLength:
						GWorld->Cam->FoV = stod(value);
						break;
					case FileProperty::CameraFrom:
						CameraFrom = XYZFrom(value, 1);
						break;
					case FileProperty::CameraUp:
						CameraUp = XYZFrom(value, 0);
						break;
					case FileProperty::CameraTo:
						CameraTo = XYZFrom(value, 1);
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
						if (mode == Chunk::ObjectCylinder)
						{
							Minimum = stoi(value);
						}
						break;
					case FileProperty::Maximum:
						if (mode == Chunk::ObjectCylinder)
						{
							Maximum = stoi(value);
						}
						break;
					case FileProperty::Closed:
						if (mode == Chunk::ObjectCylinder)
						{
							Closed = true;
						}
						break;
					case FileProperty::UVector:
						if (mode == Chunk::AreaLight)
						{
							UVector = XYZFrom(value, 0);
						}
						else
						{
							std::wcout << L"  Error               : \"uvector\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::VVector:
						if (mode == Chunk::AreaLight)
						{
							VVector = XYZFrom(value, 0);
						}
						else
						{
							std::wcout << L"  Error               : \"vvector\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::TextureWidth:
						u = stod(value);
						break;
					case FileProperty::TextureHeight:
						v = stod(value);
						break;
					case FileProperty::FileName:
						if (mode == Chunk::ObjectModel || mode == Chunk::SphericalTexture || mode == Chunk::PlanarTexture || mode == Chunk::CubicTexture)
						{
							FileName = value;
						}
						else
						{
							std::wcout << L"  Error               : \"filename\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					case FileProperty::Process:
						if (mode == Chunk::SphericalTexture || mode == Chunk::PlanarTexture)
						{
							if (value == L"greyscale")
							{
								process = ImageProcess::Greyscale;
							}
						}
						else
						{
							std::wcout << L"  Error               : \"process\" found in incorrect data block at line " << Line << L"\n";
						}
						break;
					}
				}
			}

			Line++;
		}

		std::wcout << L"  Loaded              : " << GWorld->Objects.size() << " objects, " << GWorld->Lights.size() << L" lights, " << MaterialCount << L" materials, " << TransformCount << L" transforms.\n";

		file.close();

		Quaternion campos = CameraFrom;
		GWorld->Cam->Transform = campos.ViewTransform(CameraTo, CameraUp);
		GWorld->Cam->CalculatePixelSize();

		return true;
	}

	std::wcout << L"\n  Error Loading Scene : " << file_name << L"\n";

	return false;
}