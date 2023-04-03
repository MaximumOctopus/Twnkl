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


enum class Primative { None = 0, Sphere = 1, Plane = 2 };


class Object
{
	std::vector<TransformConfiguration> Transforms;

public:

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
	void CreateInverseTransform();

	int TransformsCount();
	[[nodiscard]] TransformConfiguration TransformAt(int);

	[[nodiscard]] Quaternion WorldToObject(Quaternion&);
	[[nodiscard]] Quaternion NormalToWorld(Quaternion&);

	void Intersects(Intersections&, Ray&);
	[[nodiscard]] Quaternion NormalAt(Quaternion&);

	virtual void LocalIntersect(Intersections&, Ray&);
	virtual [[nodiscard]] Quaternion LocalNormalAt(Quaternion&);

	virtual void PostSetup(int);

	virtual std::wstring ToString();
};