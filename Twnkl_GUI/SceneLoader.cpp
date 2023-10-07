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

//#include <Vcl.Dialogs.hpp>

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
	Loaded = LoadScene(file_name, shadow_detail);
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
PatternDesign SceneLoader::PatternFromObject(Chunk object, Chunk pattern)
{
	switch (pattern)
	{
	case Chunk::PatternChecker:
		switch (object)
		{
		case Chunk::None:
			break;
		case Chunk::ObjectCone:
		case Chunk::ObjectCylinder:
			return PatternDesign::CylinderCheckerboard;
		case Chunk::ObjectCube:
			return PatternDesign::CubeCheckerboard;
		case Chunk::ObjectPlane:
			return PatternDesign::Checkerboard;
		case Chunk::ObjectSphere:
			return PatternDesign::SphericalCheckerboard;
		}
		break;
	case Chunk::PatternGradient:
		return PatternDesign::Gradient;
	case Chunk::PatternGradient2:
		return PatternDesign::Gradient2;
	case Chunk::PatternRing:
		return PatternDesign::Ring;
	case Chunk::PatternStripey:
		return PatternDesign::Stripey;
	case Chunk::PatternPerlin:
		return PatternDesign::Perlin1;
	case Chunk::PatternPerlin2:
		return PatternDesign::Perlin2;
	case Chunk::PatternPerlin3:
		return PatternDesign::Perlin3;
	case Chunk::PatternFractal:
		return PatternDesign::Fractal;
	case Chunk::PatternSimplex:
		return PatternDesign::Simplex;
	case Chunk::PatternTexture:
		switch (object)
		{
		case Chunk::None:
			break;
		case Chunk::ObjectCone:
		case Chunk::ObjectCylinder:
			return PatternDesign::CylinderTexture;
		case Chunk::ObjectCube:
			return PatternDesign::CubeTexture;
		case Chunk::ObjectPlane:
			return PatternDesign::PlanarTexture;
		case Chunk::ObjectSphere:
			return PatternDesign::SphericalTexture;
		}
		break;
	}
	
	return PatternDesign::None;
}


#ifdef _GUI
PatternDesign SceneLoader::PatternFromObject2(PrimitiveType object, int pattern)
{
	switch (pattern)
	{
	case 1:
		switch (object)
		{
		case PrimitiveType::None:
			break;
		case PrimitiveType::Cone:
		case PrimitiveType::Cylinder:
			return PatternDesign::CylinderCheckerboard;
		case PrimitiveType::Cube:
			return PatternDesign::CubeCheckerboard;
		case PrimitiveType::Plane:
			return PatternDesign::Checkerboard;
		case PrimitiveType::Sphere:
			return PatternDesign::SphericalCheckerboard;
		}
		break;
	case 3:
		return PatternDesign::Gradient;
	case 4:
		return PatternDesign::Gradient2;
	case 8:
		return PatternDesign::Ring;
	case 10:
		return PatternDesign::Stripey;
	case 5:
		return PatternDesign::Perlin1;
	case 6:
		return PatternDesign::Perlin2;
	case 7:
		return PatternDesign::Perlin3;
	case 2:
		return PatternDesign::Fractal;
	case 9:
		return PatternDesign::Simplex;
	case 11:
		switch (object)
		{
		case PrimitiveType::None:
			break;
		case PrimitiveType::Cone:
		case PrimitiveType::Cylinder:
			return PatternDesign::CylinderTexture;
		case PrimitiveType::Cube:
			return PatternDesign::CubeTexture;
		case PrimitiveType::Plane:
			return PatternDesign::PlanarTexture;
		case PrimitiveType::Sphere:
			return PatternDesign::SphericalTexture;
		}
		break;
	}

	return PatternDesign::None;
}
#endif

	
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
	case Chunk::None:
		break;

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
bool SceneLoader::LoadScene(const std::wstring file_name, int shadow_detail)
{
	std::wifstream file(file_name);

	if (file)
	{
		#if _GUI
		Errors.clear();
		Errors.push_back(L"Loading: " + file_name);
		#endif

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
						#ifdef _GUI
						Errors.push_back(L"Unknown property key \"" + key + L"\" on line " + std::to_wstring(Line) + L" of scene file.\n");
						#else
						std::wcout << L"Unknown property key \"" << key << L"\" on line " << Line << L" of scene file.\n";
						#endif
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
						case Chunk::Project:
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
						case Chunk::None:
							break;
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
							pattern_properties.Colour1 = Colours[0];
							pattern_properties.Colour2 = Colours[1];
							pattern_properties.FileName = FileName;

							if (!GWorld->SetLastObjectPattern(PatternFromObject(last_object, mode), pattern_properties))
							{
								#ifdef _GUI
								Errors.push_back(GWorld->LastError);
								#else
                                std::wcout << GWorld->LastError << "\n";
								#endif
                            }
							break;
						case Chunk::Transform:
						{
							switch (tt)
							{
							case TransformType::None:
                                break;
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
							case Chunk::None:
                                break;
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

							if (shadow_detail < 1)
							{
								shadow_detail = 8;
								#ifdef _GUI
                                Errors.push_back(L"Arealight \"" + Name + L"\" shadow_detail set to 0; invalid, set to default, 8");
								#endif
							}

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
						if (ValidateParameter(mode == Chunk::PatternPerlin || mode == Chunk::PatternPerlin2 || mode == Chunk::PatternPerlin3
							 || mode == Chunk::PatternTexture, L"scale", Line))
						{
							pattern_properties.scale = stod(value);
						}
						break;
					case FileProperty::Phase:
						if (ValidateParameter(mode == Chunk::PatternPerlin3, L"phase", Line))
						{
							pattern_properties.phase = stod(value);
						}
						break;
					case FileProperty::Frequency:
						if (ValidateParameter(mode == Chunk::PatternFractal || mode == Chunk::PatternStripey || mode == Chunk::PatternChecker
							 || mode == Chunk::PatternTexture, L"frequency", Line))
						{
							pattern_properties.frequency = stod(value);
						}
						break;
					case FileProperty::Amplitude:
						if (ValidateParameter(mode == Chunk::PatternFractal || mode == Chunk::PatternStripey || mode == Chunk::PatternChecker
							 || mode == Chunk::PatternTexture, L"amplitude", Line))
						{
							pattern_properties.amplitude = stod(value);
						}
						break;
					case FileProperty::Lacunarity:
						if (ValidateParameter(mode == Chunk::PatternFractal || mode == Chunk::PatternStripey || mode == Chunk::PatternChecker
							 || mode == Chunk::PatternTexture, L"lacunarity", Line))
						{
							pattern_properties.lacunarity = stod(value);
						}
						break;
					case FileProperty::Persistence:
						if (ValidateParameter(mode == Chunk::PatternFractal || mode == Chunk::PatternStripey || mode == Chunk::PatternChecker
							 || mode == Chunk::PatternTexture, L"persistence", Line))
						{
							pattern_properties.persistence = stod(value);
						}
						break;
					case FileProperty::Simple:
						if (ValidateParameter(mode == Chunk::PatternFractal || mode == Chunk::PatternChecker, L"simple", Line))
						{
							pattern_properties.simple = true;
						}
						break;
					case FileProperty::Noise:
						if (ValidateParameter(mode == Chunk::PatternStripey || mode == Chunk::PatternChecker || mode == Chunk::PatternTexture, L"noise", Line))
						{
							if (value == L"true")
							{
								pattern_properties.noise = true;
							}
						}
						break;
					case FileProperty::NPScale:
						if (ValidateParameter(mode == Chunk::PatternStripey || mode == Chunk::PatternChecker || mode == Chunk::PatternTexture, L"npscale", Line))
						{
							pattern_properties.npscale = stod(value);
						}
						break;
					case FileProperty::NScale:
						if (ValidateParameter(mode == Chunk::PatternStripey || mode == Chunk::PatternChecker || mode == Chunk::PatternTexture, L"nscale", Line))
						{
							pattern_properties.nscale = stod(value);
						}
						break;
					case FileProperty::LightSamples:
						if (ValidateParameter(mode == Chunk::AreaLight, L"samples", Line))
						{
                            shadow_detail = stoi(value);
						}
						break;
					case FileProperty::Description:
						if (ValidateParameter(mode == Chunk::Project, L"description", Line))
						{
							GWorld->Project.Description = value;
						}
						break;
					case FileProperty::Author:
						if (ValidateParameter(mode == Chunk::Project, L"author", Line))
						{
							GWorld->Project.Author = value;
						}
						break;
					}

				}
			}

			Line++;
		}

		#if _GUI
		Errors.push_back(L"Loaded : " + std::to_wstring(GWorld->Objects.size()) + L" objects, " + std::to_wstring(GWorld->Lights.size()) + L" lights, " + std::to_wstring(MaterialCount) + L" materials, " +std::to_wstring(TransformCount) + L" transforms.");
		#else
		std::wcout << L"  Loaded              : " << GWorld->Objects.size() << L" objects, " << GWorld->Lights.size() << L" lights, " << MaterialCount << L" materials, " << TransformCount << L" transforms.\n";
		#endif

		file.close();

		GWorld->Cam->SetViewport(CameraFrom, CameraTo, CameraUp);

		Quaternion campos = CameraFrom;
		GWorld->Cam->Transform = campos.ViewTransform(CameraTo, CameraUp);
		GWorld->Cam->CalculatePixelSize();

		return true;
	}

	std::wcout << L"\n  Error Loading Scene : " << file_name << L"\n";

	return false;
}