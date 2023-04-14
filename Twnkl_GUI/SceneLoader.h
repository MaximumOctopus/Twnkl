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
#include "Constants.h"
#include "Object.h"
#include "Quaternion.h"
#include "TransformConfiguration.h"


struct GUIProperties
{
	bool ResizeToDisplay = false;
	int DisplayWidth = 0;
	int DisplayHeight = 0;
};


class SceneLoader
{
	enum class Chunk {
		None = 0, ObjectSphere = 1, ObjectPlane = 2, ObjectCone = 3, ObjectCube = 4, ObjectCylinder = 5, ObjectModel = 6, ObjectModelSmooth = 7,
		PatternChecker = 8, PatternGradient = 9, PatternGradient2 = 10, PatternRing = 11, PatternStripey = 12, PatternPerlin = 13, PatternPerlin2 = 14, PatternPerlin3 = 15, PatternTexture = 16,
		PatternFractal = 17, PatternSimplex = 18,
		Material = 30, Transform = 31, PointLight = 32, AreaLight = 33,
		Camera = 40
	};

	static const int BlockTitlesCount = 23;

	const std::wstring BlockTitles[BlockTitlesCount] = 
		{ L"objectsphere", L"objectplane", L"objectcube", L"objectcone", L"objectcylinder", L"objectmodel", L"objectmodelsmooth",
		L"material", 
		L"patternchecker", L"patterngradient", L"patterngradient2", L"patternring", L"patternstripey", L"patternperlin", L"patternperlin2", L"patternperlin3", L"patterntexture",
		L"patternfractal", L"patternsimplex",
		L"transform", L"pointlight", L"arealight", L"camera"};

	const Chunk BlockChunk[BlockTitlesCount] = { 
		Chunk::ObjectSphere, Chunk::ObjectPlane, Chunk::ObjectCube, Chunk::ObjectCone, Chunk::ObjectCylinder, Chunk::ObjectModel, Chunk::ObjectModelSmooth,
		Chunk::Material, 
		Chunk::PatternChecker, Chunk::PatternGradient, Chunk::PatternGradient2, Chunk::PatternRing, Chunk::PatternStripey, Chunk::PatternPerlin, Chunk::PatternPerlin2, Chunk::PatternPerlin3, Chunk::PatternTexture,
		Chunk::PatternFractal, Chunk::PatternSimplex,
		Chunk::Transform, Chunk::PointLight, Chunk::AreaLight, Chunk::Camera
	};
		
	enum class FileProperty {
		None = 0, NotFound = 1, DataBegin = 2, DataEnd = 3, Colour = 4, Position = 5, Name = 6,
		Ambience = 10, Diffuse = 11, Reflectivity = 12, RefractiveIndex = 13, Shininess = 14, Specular = 15, Transparency = 16,
		TransformType = 20, Angle = 21, XYZ = 22,
		FocalLength = 30, CameraFrom = 31, CameraUp = 32, CameraTo = 33,
		CanvasWidth = 40, CanvasHeight = 41,
		Minimum = 42, Maximum = 43, Closed = 44,
		UVector = 45, VVector = 46,
		TextureWidth = 47, TextureHeight = 48,
		FileName = 49, Process = 50, Scale = 51, Phase = 52,
		Frequency = 53, Amplitude = 54, Lacunarity = 55, Persistence = 56, Simple = 57
	};

	static const int kPropertyListCount = 60;

	const std::wstring FilePropertyList[kPropertyListCount] = {
		__SceneChunkCamera, __SceneChunkPointLight, __SceneChunkAreaLight,
		__SceneChunkObjectSphere, __SceneChunkObjectPlane, __SceneChunkObjectCone, __SceneChunkObjectCube, __SceneChunkObjectCylinder, __SceneChunkObjectModel, __SceneChunkObjectModelSmooth,
		__SceneChunkMaterial, __SceneChunkTransform,
		__SceneChunkChecker, __SceneChunkGradient, __SceneChunkGradient2, __SceneChunkRing, __SceneChunkStripey, __SceneChunkPerlin, __SceneChunkPerlin2, __SceneChunkPerlin3,
		__SceneChunkTexture,
		__SceneChunkFractal, __SceneChunkSimplex,
		L"}",
		L"colour", L"color", L"position", L"name",
		L"ambient", L"diffuse", L"reflectivity", L"refractiveindex", L"shininess", L"specular", L"transparency",
		L"type", L"angle", L"xyz",
		L"focallength", L"from", L"to", L"up",
		L"width", L"height", 
		L"minimum", L"maximum", L"closed",
		L"uvector", L"vvector",
		L"u", L"v",
		L"filename", L"process", L"scale", L"phase",
		L"frequency", L"amplitude", L"lacunarity", L"persistence", L"simple"
	};

	const FileProperty FilePropertyReference[kPropertyListCount] = {
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataBegin, FileProperty::DataBegin, 
		FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, FileProperty::DataBegin, 
		FileProperty::DataBegin,
		FileProperty::DataBegin, FileProperty::DataBegin,
		FileProperty::DataEnd,
		FileProperty::Colour, FileProperty::Colour, FileProperty::Position, FileProperty::Name,
		FileProperty::Ambience,FileProperty::Diffuse, FileProperty::Reflectivity, FileProperty::RefractiveIndex, FileProperty::Shininess, FileProperty::Specular, FileProperty::Transparency,
		FileProperty::TransformType, FileProperty::Angle, FileProperty::XYZ,
		FileProperty::FocalLength, FileProperty::CameraFrom, FileProperty::CameraTo, FileProperty::CameraUp,
		FileProperty::CanvasWidth, FileProperty::CanvasHeight,
		FileProperty::Minimum, FileProperty::Maximum, FileProperty::Closed,
		FileProperty::UVector, FileProperty::VVector,
		FileProperty::TextureWidth, FileProperty::TextureHeight,
		FileProperty::FileName, FileProperty::Process, FileProperty::Scale, FileProperty::Phase,
		FileProperty::Frequency, FileProperty::Amplitude, FileProperty::Lacunarity, FileProperty::Persistence, FileProperty::Simple
	};

	struct MaterialProperties
	{
		double ambient = __DefaultMaterialAmbient;
		double diffuse = __DefaultMaterialDiffuse;
		double reflectivity = __DefaultMaterialReflectivity;
		double refractiveindex = __DefaultMaterialRefractiveIndex;
		double shininess = __DefaultMaterialShininess;
		double specular = __DefaultMaterialSpecular;
		double transparent = __DefaultMaterialTransparency;

		void Clear()
		{
			ambient = __DefaultMaterialAmbient;
			diffuse = __DefaultMaterialDiffuse;
			reflectivity = __DefaultMaterialReflectivity;
			refractiveindex = __DefaultMaterialRefractiveIndex;
			shininess = __DefaultMaterialShininess;
			specular = __DefaultMaterialSpecular;
			transparent = __DefaultMaterialTransparency;
		}
	};
	
	[[nodiscard]] TransformType TransformTypeFrom(const std::wstring);
	[[nodiscard]] Colour ColourFrom(const std::wstring);
	[[nodiscard]] Chunk GetDataBlockChunkFrom(const std::wstring);
	[[nodiscard]] Quaternion XYZFrom(const std::wstring, int);
	void AddObject(Chunk, std::wstring, std::wstring, int, int, bool);
	
	AvailablePatterns PatternFromObject(Chunk, Chunk);
	[[nodiscard]] FileProperty GetInputProperty(std::wstring);

	bool ValidateParameter(bool, std::wstring, int);

public:

	bool Loaded = false;

	SceneLoader();

	SceneLoader(const std::wstring, int);

	#ifdef _GUI
	AvailablePatterns PatternFromObject2(PrimitiveType, int);
	#endif

	std::pair<int, int> ResizeForDisplay(double, double, double, double);

	[[nodiscard]] bool LoadScene(const std::wstring, int, GUIProperties);
}; 