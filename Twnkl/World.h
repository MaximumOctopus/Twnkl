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
#include <vector>

#include "Camera.h"
#include "Colour.h"
#include "Light.h"
#include "Object.h"


class World
{
public:

	Colour* Canvas = nullptr;

	std::vector<Object*> Objects;
	std::vector<Light*> Lights;

	Camera* Cam = nullptr;

	World(int, int, double);
	~World();

	void Clear();

	// call when all objects/lights/camera have been initialised and added
	// caches copies of inverse transforms for objects and camera
	[[nodiscard]] bool Finalise();

	[[nodiscard]] bool SaveCanvasToFile(const std::wstring);

	void AddNewObject(int, AvailablePatterns, PatternProperties, std::wstring);
	void SetLastObjectPattern(AvailablePatterns, PatternProperties);

	void ToString();

	void SaveScene(std::wstring);

	#ifdef _DEBUG
	void DefaultWorld(int);
	#endif
};