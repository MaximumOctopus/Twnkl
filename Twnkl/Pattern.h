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


class Pattern
{
	std::vector<TransformConfiguration> Transforms;

public:

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

	int TransformsCount();
	[[nodiscard]] TransformConfiguration TransformAt(int);

	void CreateInverseTransform();

	[[nodiscard]] virtual std::wstring ToString();
};