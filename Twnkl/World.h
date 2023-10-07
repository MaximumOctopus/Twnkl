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
#include "Pattern.h"
#include "Project.h"


class World
{
	static const int __LastObject = -1;

	bool AddCheckerTo(int, PatternProperties);
	bool AddGradientTo(int, PatternProperties);
	bool AddGradient2To(int, PatternProperties);
	bool AddRingTo(int, PatternProperties);
	bool AddStripeyTo(int, PatternProperties);
	bool AddPerlinTo(int, PatternProperties);
	bool AddPerlin2To(int, PatternProperties);
	bool AddPerlin3To(int, PatternProperties);
	bool AddFractalTo(int, PatternProperties);
	bool AddSimplexTo(int, PatternProperties);
	bool AddCheckerSphereTo(int, PatternProperties);
	bool AddCheckerCylinderTo(int, PatternProperties);
	bool AddCheckerCubeTo(int, PatternProperties);
	bool AddTextureCubeTo(int, PatternProperties, bool);
	bool AddTextureCylinderTo(int, PatternProperties, bool);
	bool AddTexturePlaneTo(int, PatternProperties, bool);
	bool AddTextureSphereTo(int, PatternProperties, bool);

public:

	std::wstring LastError = L"";

	TwnklProject Project;

	#ifdef _GUI
	std::vector<std::wstring> Errors;
	#endif

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

	#ifdef _GUI
	void AddNewObject(int, PatternDesign, PatternProperties, std::wstring);
	bool SetObjectPattern(int, PatternDesign, PatternProperties);
    void ReplaceTexture(int, std::wstring);
	#endif

	bool SetLastObjectPattern(PatternDesign, PatternProperties);

	#ifdef _GUI
	void MakeCopyOfObjectAt(int);
	#endif

	void ToString();

	void SaveScene(std::wstring);

	#ifdef _GUI
	void DefaultScene();
	#endif

	#ifdef _DEBUG
	void DefaultWorld(int);
	#endif
};
