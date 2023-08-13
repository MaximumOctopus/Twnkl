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

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "Configuration.h"
#include "Constants.h"
#include "DateUtility.h"
#include "Formatting.h"
#include "Ini.h"


#ifdef _DEBUG
#include "Debug.h"
#endif

Configuration* GConfiguration;


Configuration::Configuration(int argc, wchar_t* argv[])
{
	if (argc != 0)
	{
		for (int t = 1; t < argc; t++)
		{
			std::wstring parameter = argv[t];

			if (IsValidParameter(parameter))
			{
				ParameterData pd;

				pd.command = GetCommandValue(parameter);
				pd.property = GetPropertyValue(parameter);
				pd.option = GetPropertyOption(pd.command);

				std::transform(pd.command.begin(), pd.command.end(), pd.command.begin(), ::tolower);

				Parameters.push_back(pd);
			}
			else
			{
				std::wcerr << std::format(L"Error, invalid parameter \"{0}\".\n", parameter);
			}
		}
	}

	SetFromCommandLine();

	if (!Meta.Silent)
	{
		ShowConfiguration();
	}

	if (Meta.SaveToConfig)
	{
		if (!SaveConfiguration(Meta.SaveFileName))
		{
			std::wcerr << std::format(L"Error saving configuration to \"{0}\".\n", Meta.SaveFileName);
		}
	}
}


void Configuration::ShowConfiguration()
{
	if (Meta.LoadedFromConfig)
	{
		std::wcout << L"    Config source     : Config file\n\n";
	}

	std::wcout << L"    Scene source      : " << Render.SceneFileName << L"\n";
	std::wcout << L"    Image file name   : " << Render.ImageFileName << L"\n";

	if (Render.ImageWidth != 0 && Render.ImageHeight != 0)
	{
		std::wcout << L"    Render size       : " << Render.ImageWidth << L" x " << Render.ImageHeight << L"\n";
	}
	else
	{
		std::wcout << L"    Render size       : Using scene file settings \n";
	}

	std::wcout << L"\n";
	std::wcout << L"    Samples per pixel : " << Render.SamplesPerPixel << L"\n";
	std::wcout << L"    Ray recursion     : " << Render.LightRecursion << L"\n";
	std::wcout << L"    Shadow detail     : " << Render.ShadowDetail << L"\n";
	std::wcout << L"\n";
}


void Configuration::SetFromCommandLine()
{
	if (Parameters.size() != 0)
	{
		for (int p = 0; p < Parameters.size(); p++)
		{
			#ifdef _DEBUG
			TwnklDebug::Output(L"command: " + Parameters[p].command + L" value: " + Parameters[p].property);
			#endif

			static const std::wstring kLoadConfig = L"/loadconfig";				// loads a scene from file
			static const std::wstring kSaveConfig = L"/saveconfig";				// loads a scene from file

			static const std::wstring kSaveImage = L"/export";					// saves ppm image to file

			static const std::wstring kImageWidth = L"/width";					// output image width
			static const std::wstring kImageHeight = L"/height";				// output image height

			switch (Parameters[p].option)
			{
			case ParameterOption::None:
			case ParameterOption::Cats:
			case ParameterOption::Help:
				// already handled, shouldn't even get here
				break;

			case ParameterOption::LoadScene:
				Render.SceneFileName = Formatting::AffixFileExtension(Parameters[p].property, L".twnkl");
				break;

			case ParameterOption::LoadConfig:
			{
				std::wstring file_name = Formatting::AffixFileExtension(Parameters[p].property, L".txt");

				Meta.LoadedFromConfig = LoadConfiguration(file_name);

				if (!Meta.LoadedFromConfig)
				{
					std::wcout << std::format(L"Error loading configuration file \"{0}\"", file_name) << L"\n";
				}

				break;
			}
			case ParameterOption::SaveConfig:
			{
				std::wstring file_name = Formatting::AffixFileExtension(Parameters[p].property, L".txt");

				Meta.SaveFileName = file_name;
				Meta.SaveToConfig = true;

				break;
			}
			case ParameterOption::SaveImage:
			{
				std::wstring file_name = Formatting::AffixFileExtension(Parameters[p].property, L".ppm");

				Render.ImageFileName = file_name;
				Meta.SaveToConfig = true;

				break;
			}
			case ParameterOption::ImageWidth:
			{
				int w = SafelyGetIntFromString(Parameters[p].property, 0);

				if (w > 0)
				{
					Render.ImageWidth = w;
				}
				else
				{
					std::wcerr << std::format(L"Error, invalid image width \"{0}\". Using {1} (default).\n", Parameters[p].property, 320);
				}

				break;
			}
			case ParameterOption::ImageHeight:
			{
				int h = SafelyGetIntFromString(Parameters[p].property, 0);

				if (h > 0)
				{
					Render.ImageHeight = h;
				}
				else
				{
					std::wcerr << std::format(L"Error, invalid image height \"{0}\". Using {1} (default).\n", Parameters[p].property, 160);
				}

				break;
			}
			case ParameterOption::ShadowDetail:
			{
				int s = SafelyGetIntFromString(Parameters[p].property, 0);

				if (s > 0)
				{
					Render.ShadowDetail = s;
				}
				else
				{
					std::wcerr << std::format(L"Error, invalid shadow detail \"{0}\". Using {1} (default).\n", Parameters[p].property, 16);
				}

				break;
			}
			case ParameterOption::LightRecursion:
			{
				int b = SafelyGetIntFromString(Parameters[p].property, 0);

				if (b > 0)
				{
					Render.LightRecursion = b;
				}
				else
				{
					std::wcerr << std::format(L"Error, invalid light recursion \"{0}\". Using {1} (default).\n", Parameters[p].property, __DefaultRendererLightRecursion);
				}

				break;
			}
			case ParameterOption::SamplesPerPixel:
			{
				int s = SafelyGetIntFromString(Parameters[p].property, 0);

				if (s > 0)
				{
					Render.SamplesPerPixel = s;
				}
				else
				{
					std::wcerr << std::format(L"Error, invalid samples per pixel \"{0}\". Using {1} (default).\n", Parameters[p].property, __DefaultRendererSamplesPerPixel);
				}

				break;
			}
			case ParameterOption::Debug:
				Meta.Debug = true;
				break;

			default:
				std::wcout << L" Warning, parameter \"" << Parameters[p].command << "\" was unhandled.\n";
			}
		}
	}

	#ifdef _DEBUG
	std::wcout << L"\n";
	#endif
}


// because we can always trust users to correctly enter values in command-line parameters...
int Configuration::SafelyGetIntFromString(const std::wstring input, int default_value)
{
	int Value = default_value;

	try
	{
		Value = stoi(input);
	}
	catch (...)
	{

	}

	return Value;
}


std::wstring Configuration::GetCommandValue(const std::wstring input)
{
	size_t pos = input.find(';');

	if (pos == std::wstring::npos)
	{
		pos = input.find(':');
	}

	if (pos != std::wstring::npos)
	{
		return input.substr(0, pos);
	}

	return input;
}


std::wstring Configuration::GetPropertyValue(const std::wstring input)
{
	size_t pos = input.find(';');

	if (pos == std::wstring::npos)
	{
		pos = input.find(':');
	}

	if (pos != std::wstring::npos)
	{
		return input.substr(pos + 1);
	}

	return L"";
}


ParameterOption Configuration::GetPropertyOption(const std::wstring input)
{
	ParameterOption po = ParameterOption::None;

	for (int t = 0; t < kCommandListCount; t++)
	{
		if (CommandList[t].starts_with(input))
		{
			return ParameterReference[t];
		}
	}

	return po;
}


bool Configuration::IsValidParameter(const std::wstring input)
{
	std::wstring parameter = input;

	std::transform(parameter.begin(), parameter.end(), parameter.begin(), ::tolower);

	auto value_delimeter = parameter.find(L':');

	if (value_delimeter != std::wstring::npos)
	{
		parameter = parameter.substr(0, value_delimeter - 1);
	}

	for (int t = 0; t < kCommandListCount; t++)
	{
		if (CommandList[t].starts_with(parameter))
		{
			return true;
		}
	}

	return false;
}


bool Configuration::FindParameter(std::wstring parameter)
{
	std::transform(parameter.begin(), parameter.end(), parameter.begin(), ::tolower);

	for (int t = 0; t < Parameters.size(); t++)
	{
		std::wstring p = Parameters[t].command;

		std::transform(p.begin(), p.end(), p.begin(), ::tolower);

		if (p == parameter)
		{
			return true;
		}
	}

	return false;
}


bool Configuration::LoadConfiguration(const std::wstring file_name)
{
	Ini* config = new Ini(file_name);

	if (config->Loaded)
	{
		int IntegerKey = 0;
		std::wstring StringKey = L"";

		// == load from aircraft section ==============================================================

		StringKey = config->ReadString(L"Render", L"Scene", L"");
		if (config->LastKeyExist)
		{
			Render.SceneFileName = StringKey;
		}

		StringKey = config->ReadString(L"Render", L"Image", L"");
		if (config->LastKeyExist)
		{
			Render.ImageFileName = StringKey;
		}

		IntegerKey = config->ReadInteger(L"Render", L"Width", 320);
		if (config->LastKeyExist)
		{
			Render.ImageWidth = IntegerKey;
		}

		IntegerKey = config->ReadInteger(L"Render", L"Height", 160);
		if (config->LastKeyExist)
		{
			Render.ImageHeight = IntegerKey;
		}

		IntegerKey = config->ReadInteger(L"Render", L"Shadows", __DefaultRendererShadowDetail);
		if (config->LastKeyExist)
		{
			Render.ShadowDetail = IntegerKey;
		}

		IntegerKey = config->ReadInteger(L"Render", L"LightRecursion", __DefaultRendererLightRecursion);
		if (config->LastKeyExist)
		{
			Render.LightRecursion = IntegerKey;
		}

		IntegerKey = config->ReadInteger(L"Render", L"SamplesPerPiexl", __DefaultRendererSamplesPerPixel);
		if (config->LastKeyExist)
		{
			Render.SamplesPerPixel = IntegerKey;
		}

		IntegerKey = config->ReadInteger(L"Meta", L"Debug", 0);
		if (config->LastKeyExist)
		{
			Meta.Debug = IntegerKey;
		}

		delete config;

		return true;
	}

	delete config;

	return false;
}


std::wstring Configuration::GetAsCommandLineParameters()
{
	if (Parameters.size() != 0)
	{
		std::wstring output = L"";

		for (int t = 0; t < Parameters.size(); t++)
		{
			if (Parameters[t].property == L"")
			{
				output += Parameters[t].command + L" ";
			}
			else
			{
				output += Parameters[t].command + L":" + Parameters[t].property + L" ";
			}			
		}

		return output;
	}

	return L"";
}


// are you really too lazy to make your own config file?!
// only writes out values that differ from the defaults
bool Configuration::SaveConfiguration(const std::wstring file_name)
{
	std::ofstream ofile(file_name);

	if (ofile)
	{
		std::wcout << L"Saving current configuration to file: " << file_name << L"\n\n";

		ofile << Formatting::to_utf8(L"// Created " + DateUtility::DateTime(kDisplayModeConsole) + L"\n");
		ofile << Formatting::to_utf8(L"// Original command-line input: " + GetAsCommandLineParameters() + L"\n\n");

		ofile << Formatting::to_utf8(L"[Render]\n");
		ofile << Formatting::to_utf8(L"Scene=" + Render.SceneFileName + L"\n");
		ofile << Formatting::to_utf8(L"Image=" + Render.ImageFileName + L"\n");
		ofile << Formatting::to_utf8(L"Width=" + std::to_wstring(Render.ImageWidth) + L"\n");
		ofile << Formatting::to_utf8(L"Height=" + std::to_wstring(Render.ImageHeight) + L"\n");

		ofile << Formatting::to_utf8(L"Shadows=" + std::to_wstring(Render.ShadowDetail) + L"\n");
		ofile << Formatting::to_utf8(L"LightRecursion=" + std::to_wstring(Render.LightRecursion) + L"\n");
		ofile << Formatting::to_utf8(L"SamplesPerPiexl=" + std::to_wstring(Render.SamplesPerPixel) + L"\n");

		ofile << Formatting::to_utf8(L"[Meta]\n");
		ofile << Formatting::to_utf8(L"Debug=" + std::to_wstring(Meta.Debug) + L"\n");

		ofile.close();

		return true;
	}

	return false;
}