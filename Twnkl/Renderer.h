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

#include <chrono>
#include <string>

#include "Colour.h"
#include "Intersections.h"

#include "Constants.h"
#include "Light.h"
#include "PhongMaterial.h"
#include "Matrix4.h"
#include "Object.h"
#include "Quaternion.h"
#include "Ray.h"
#include "World.h"


class Renderer
{
	Intersections intersections;

	int LightRecursion = __DefaultRendererLightRecursion;

	std::chrono::system_clock::time_point StartTime;

	void Standard();
	void SuperSample(int);

	void ShowRenderTime();

public:

	Renderer();
	~Renderer();

	void Render(int);

	[[nodiscard]] Ray RayForPixel(int, int);
	[[nodiscard]] Ray RayForPixelSS(double, double);

	[[nodiscard]] Colour ShadeHit(Computation&, int);
	[[nodiscard]] Colour ColourAt(Ray&, int);
	[[nodiscard]] bool IsShadowed(Quaternion&, Quaternion&);
	[[nodiscard]] Colour ReflectedColour(Computation&, int);
	[[nodiscard]] Colour RefractedColour(Computation&, int);
	double IntensityAt(Light*, Quaternion&);
	[[nodiscard]] void IntersectsWorld(Ray&);

	[[nodiscard]] Colour Lighting(Object*, Light*, Quaternion&, Quaternion&, Quaternion&, double);
};