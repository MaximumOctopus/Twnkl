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

#include <string>

#include "Colour.h"
#include "Quaternion.h"


class SceneLoader
{
	enum class Chunk {
		None = 0, ObjectSphere = 1, ObjectPlane = 2, ObjectCone = 3, ObjectCube = 4, ObjectCylinder = 5, ObjectModel = 6, ObjectModelSmooth = 7,
		PatternChecker = 10, PatternGradient = 11, PatternGradient2 = 12, PatternRing = 13, PatternStripey = 14,
		SphericalChecker = 20, CylinderChecker = 21, SphericalTexture = 22, PlanarTexture = 23, CubicTexture = 24,
		Material = 30, Transform = 31, PointLight = 32, AreaLight = 33,
		Camera = 40
	};

	enum class ImageProcess { None = 0, Greyscale = 1 };

	enum class TransformType { None = 0, Scale = 1, Translate = 2, RotateX = 3, RotateY = 4, RotateZ = 5 };

	enum class FileProperty {
		None = 0, NotFound = 1, DataBegin = 2, DataEnd = 3, Colour = 4, Position = 5, Name = 6,
		Ambience = 10, Diffuse = 11, Reflectivity = 12, RefractiveIndex = 13, Shininess = 14, Specular = 15, Transparency = 16,
		TransformType = 20, Angle = 21, XYZ = 22,
		FocalLength = 30, CameraFrom = 31, CameraUp = 32, CameraTo = 33,
		CanvasWidth = 40, CanvasHeight = 41,
		Minimum = 42, Maximum = 43, Closed = 44,
		UVector = 45, VVector = 46,
		TextureWidth = 47, TextureHeight = 48,
		FileName = 49, Process = 50
	};

	static const int kPropertyListCount = 55;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		L"{camera", L"{pointlight", L"{arealight",
		L"{objectsphere", L"{objectplane", L"{objectcone", L"{objectcube", L"{objectcylinder", L"{objectmodel", L"{objectmodelsmooth",
		L"{material", L"{transform", L"{patternchecker", L"{patterngradient", L"{patterngradient2", L"{patternring", L"{patternstripey",
		L"{sphericalchecker", L"{cylinderchecker", L"{sphericaltexture", L"{planartexture", L"{cubictexture",
		L"}",
		L"colour", L"color", L"position", L"name",
		L"ambient", L"diffuse", L"reflectivity", L"refractiveindex", L"shininess", L"specular", L"transparency",
		L"type", L"angle", L"xyz",
		L"focallength", L"from", L"to", L"up",
		L"width", L"height", 
		L"minimum", L"maximum", L"closed",
		L"uvector", L"vvector",
		L"u", L"v",
		L"filename", L"process"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataEnd,
		FileProperty::Colour, FileProperty::Colour, FileProperty::Position, FileProperty::Name,
		FileProperty::Ambience,FileProperty::Diffuse, FileProperty::Reflectivity, FileProperty::RefractiveIndex, FileProperty::Shininess, FileProperty::Specular, FileProperty::Transparency,
		FileProperty::TransformType, FileProperty::Angle, FileProperty::XYZ,
		FileProperty::FocalLength, FileProperty::CameraFrom, FileProperty::CameraTo, FileProperty::CameraUp,
		FileProperty::CanvasWidth, FileProperty::CanvasHeight,
		FileProperty::Minimum, FileProperty::Maximum, FileProperty::Closed,
		FileProperty::UVector, FileProperty::VVector,
		FileProperty::TextureWidth, FileProperty::TextureHeight,
		FileProperty::FileName, FileProperty::Process
	};

	[[nodiscard]] TransformType TransformTypeFrom(const std::wstring);
	[[nodiscard]] Colour ColourFrom(const std::wstring);
	[[nodiscard]] Quaternion XYZFrom(const std::wstring, int);
	void AddObject(Chunk, std::wstring, std::wstring, int, int, bool);

	void ObjectSetPattern(Chunk, Colour, Colour, double, double, std::wstring, ImageProcess);
	[[nodiscard]] FileProperty GetInputProperty(std::wstring);

	[[nodiscard]] bool LoadScene(const std::wstring, int);

public:

	bool Loaded = false;

	SceneLoader(const std::wstring, int);
};