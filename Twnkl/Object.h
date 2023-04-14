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

class Intersections;

class PhongMaterial;

#include "Intersections.h"
#include "PhongMaterial.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Ray.h"
#include "TransformConfiguration.h"


enum class PrimitiveType { None = 0, Cone = 1, Cube = 2, Cylinder = 3, Model = 4, Plane = 5, SmoothTriangle = 6, Sphere = 7, Triangle = 8 };

enum class ImageProcess { None = 0, Greyscale = 1 };

enum class AvailablePatterns {
	None = 0,
	Checker = 1, Gradient = 2, Gradient2 = 3, Ring = 4, Stripey = 5,
	Perlin = 6, Perlin2 = 7, Perlin3 = 8,
	Fractal = 9, Simplex = 10,
	SphericalChecker = 11, CylinderChecker = 12, SphericalTexture = 13, PlanarTexture = 14, CubicTexture = 15, CubicMultiTexture = 16, CylinderTexture = 17, CubeChecker = 18
};

struct PatternProperties
{
	Colour Colour1;
	Colour Colour2;

	std::wstring FileName = L"";

	double u = 0;
	double v = 0;
	ImageProcess process = ImageProcess::None;
	double scale = __DefaultPerlinScale;
	double phase = __DefaultPerlinPhase;
	double frequency = __DefaultFractalFrequency;
	double amplitude = __DefaultFractalAmplitude;
	double lacunarity = __DefaultFractalLacunarity;
	double persistence = __DefaultFractalPersistence;
	double simple = false;

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
	}
};


class Object
{

protected:

	std::vector<TransformConfiguration> Transforms;

public:

	PrimitiveType Primitive = PrimitiveType::None;

	Object* Parent = nullptr;

	std::wstring Name = L"";

	PhongMaterial* Material = nullptr;

	Quaternion Position = Quaternion(0.0, 0.0, 0.0, 1.0);

	Matrix4 Transform;
	Matrix4 InverseTransform;

	int ID = 0;

	Object(std::wstring);

	void SetMaterial(PhongMaterial);

	// cache the inverse transform for speeeed
	void ProcessTransforms();
	void AddTransform(TransformConfiguration);
	void RemoveTransformAt(int);
	void CreateInverseTransform();

	int TransformsCount();
	[[nodiscard]] TransformConfiguration TransformAt(int);
	void TransformReplaceAt(int, TransformConfiguration);

	[[nodiscard]] Quaternion WorldToObject(Quaternion&);
	[[nodiscard]] Quaternion NormalToWorld(Quaternion&);

	void Intersects(Intersections&, Ray&);
	[[nodiscard]] Quaternion NormalAt(Quaternion&);

	virtual void LocalIntersect(Intersections&, Ray&);
	virtual Quaternion LocalNormalAt(Quaternion&);

	virtual void PostSetup(int);

	std::wstring FriendlyName();

	virtual std::wstring ToString();

	virtual void ToFile(std::ofstream& ofile);
};