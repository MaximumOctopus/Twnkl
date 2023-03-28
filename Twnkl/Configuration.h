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

#include "Constants.h"
#include "ConfigurationConstants.h"


#pragma region CommandLineParameters
static const std::wstring kCats = L"/cat";							// the best option of them all

static const std::wstring kLoadScene = L"/scene";					// loads a scene from file

static const std::wstring kLoadConfig = L"/loadconfig";				// loads a config from file
static const std::wstring kSaveConfig = L"/saveconfig";				// saves the current config to a file

static const std::wstring kSaveImage = L"/export";					// saves ppm image to file

static const std::wstring kImageWidth = L"/width";					// output image width
static const std::wstring kImageHeight = L"/height";				// output image height

static const std::wstring kSamplesPerPixel = L"/samples";           // samples per pixel for image antialiasing
static const std::wstring kLightRecursion = L"/recursion";			// reflection bounces
static const std::wstring kShadow = L"/shadow";						// shadow detail

static const std::wstring kDebug = L"/debug";						// 
static const std::wstring kHelp = L"/help";							// 
static const std::wstring kHelpLazy = L"/?";						//


enum class ParameterOption {
	None = 0, Cats = 1, LoadScene = 2, LoadConfig = 3, SaveConfig = 4, SaveImage = 5,
	ImageWidth = 6, ImageHeight = 7,
	Help = 8,
	ShadowDetail = 9, LightRecursion = 10, SamplesPerPixel = 11,
	Debug = 12
};


static const int kCommandListCount = 14;

static const std::wstring CommandList[kCommandListCount] = { kCats, kLoadScene, kLoadConfig, kSaveConfig, kSaveImage, kImageWidth, kImageHeight, 
	kHelp, kHelpLazy, 
	kShadow, kLightRecursion, kSamplesPerPixel,
	kDebug 
};

static const ParameterOption ParameterReference[kCommandListCount] = { ParameterOption::Cats, 
    ParameterOption::LoadScene, ParameterOption::LoadConfig, ParameterOption::SaveConfig, ParameterOption::SaveImage,
    ParameterOption::ImageWidth, ParameterOption::ImageHeight, 
	ParameterOption::Help, ParameterOption::Help,
	ParameterOption::ShadowDetail, ParameterOption::LightRecursion, ParameterOption::SamplesPerPixel,
	ParameterOption::Debug
};
#pragma endregion


struct MetaData 
{
	bool LoadedFromConfig = false;
	bool SaveToConfig = false;
	std::wstring SaveFileName = L"";
	bool ShowConfig = false;
	bool Silent = false;

	bool Debug = false;
};


struct RenderSettings
{
	std::wstring SceneFileName = L"";
	std::wstring ConfigFileName = L"";
	std::wstring ImageFileName = L"$yyyy$mm$dd_$Th$Tm$Ts.ppm";

	int ImageWidth = 0;
	int ImageHeight = 0;
	double FocalLength = 0;

	int ShadowDetail = __DefaultRendererShadowDetail;
	int LightRecursion = __DefaultRendererLightRecursion;		// maximum number of levels of recursion for reflection/refraction
	int SamplesPerPixel = 0;									// anti-aliasing samples per pixel
};


struct ParameterData {
	std::wstring command = L"";
	std::wstring property = L"";

	ParameterOption option = ParameterOption::None;
};


class Configuration
{
	std::vector<ParameterData> Parameters;

	void ShowConfiguration();
	void SetFromCommandLine();

	[[nodiscard]] int SafelyGetIntFromString(const std::wstring, int);

	[[nodiscard]] std::wstring GetCommandValue(const std::wstring);
	[[nodiscard]] std::wstring GetPropertyValue(const std::wstring);
	[[nodiscard]] ParameterOption GetPropertyOption(const std::wstring);

	[[nodiscard]] bool IsValidParameter(const std::wstring);

	[[nodiscard]] bool LoadConfiguration(const std::wstring);
	[[nodiscard]] bool SaveConfiguration(const std::wstring);

	[[nodiscard]] std::wstring GetAsCommandLineParameters();

public:

	MetaData Meta;

	RenderSettings Render;

	Configuration(int argc, wchar_t* argv[]);

	[[nodiscard]] bool FindParameter(std::wstring);
};