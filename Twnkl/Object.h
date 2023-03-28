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


enum class Primative { None = 0, Sphere = 1, Plane = 2 };


class Object
{
public:

	Object* Parent = nullptr;

	std::wstring Name = L"";

	PhongMaterial* Material = nullptr;

	Quaternion Position = Quaternion(0.0, 0.0, 0.0, 1.0);

	Matrix4 Transform;
	Matrix4 InverseTransform;

	int ID = 0;

	bool TransformSet = false;

	Object(std::wstring);

	void SetTransform(Matrix4);
	void SetMaterial(PhongMaterial);

	// cache the inverse transform for speeeed
	void CreateInverseTransform();

	Quaternion WorldToObject(Quaternion&);
	Quaternion NormalToWorld(Quaternion&);

	void Intersects(Intersections&, Ray&);
	[[nodiscard]] Quaternion NormalAt(Quaternion&);

	virtual void LocalIntersect(Intersections&, Ray&);
	virtual [[nodiscard]] Quaternion LocalNormalAt(Quaternion&);

	virtual void PostSetup(int);

	virtual std::wstring ToString();
};