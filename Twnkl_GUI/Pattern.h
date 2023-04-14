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

#include "Colour.h"
#include "Object.h"
#include "Quaternion.h"
#include "TransformConfiguration.h"


enum class PatternDesign {
	None = 0, Checkerboard = 1, Gradient = 2, Gradient2 = 3, Ring = 4, Stripey = 5,
	Fractal = 6, Simplex = 7, Perlin1 = 8, Perlin2 = 9, Perlin3 = 10,
	CubeCheckerboard = 20, CubeTexture = 21, CubeMultiTexture = 22, CylinderCheckerboard = 23, CylinderTexture = 24, PlanarTexture = 25,
	SphericalCheckerboard = 26, SphericalTexture = 27
};


class Pattern
{

protected:

	std::vector<TransformConfiguration> Transforms;

public:

	PatternDesign Design = PatternDesign::None;

	std::wstring Name = L"";

	Matrix4 Transform;
	Matrix4 InverseTransform;

	Colour Colours[2];
	double Reflectivity[2] = { 0, 0 };
	bool HasReflectivity = false;

	Pattern(std::wstring);

	void SetColours(Colour, Colour);
	void SetReflectivity(double, double);

	[[nodiscard]] virtual Colour ColourAt(Object*, Quaternion&);

	void ProcessTransforms();
	void AddTransform(TransformConfiguration);
	void RemoveTransformAt(int);

	int TransformsCount();
	[[nodiscard]] TransformConfiguration TransformAt(int);
	void TransformReplaceAt(int, TransformConfiguration);

	void CreateInverseTransform();

	std::wstring FriendlyName();

	[[nodiscard]] virtual std::wstring ToString();

	virtual void ToFile(std::ofstream&);
};