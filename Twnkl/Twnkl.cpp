//
// Twnkl 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
// 
// https://github.com/MaximumOctopus/Twnkl
// 
// started March 4th 2023

// based on the book "The Ray Tracer Challenge : A Test - Driven Guide to Your First 3D Renderer" by Jamis Buck

#include <iostream>

#include "Configuration.h"
#include "Help.h"
#include "Renderer.h"
#include "SceneLoader.h"
#include "Utility.h"
#include "World.h"


extern Configuration* GConfiguration;
extern World* GWorld;


int wmain(int argc, wchar_t* argv[])
{
	if (argc == 1)
	{
		Help::About();

		return 0;
	}

	GConfiguration = new Configuration(argc, argv);

	GWorld = new World(GConfiguration->Render.ImageWidth, GConfiguration->Render.ImageHeight, 1.152);

	SceneLoader loader(GConfiguration->Render.SceneFileName, GConfiguration->Render.ShadowDetail);

	if (loader.Loaded)
	{
		if (!GWorld->Finalise())
		{
			if (GConfiguration->Meta.Debug)
			{
				GWorld->ToString();
			}

			if (GWorld->Objects.size() > 0 && GWorld->Lights.size() > 0)
			{
				Renderer rx = Renderer();

				rx.Render(GConfiguration->Render.SamplesPerPixel);

				if (!GWorld->SaveCanvasToFile(Utility::ProcessFileName(GConfiguration->Render.ImageFileName)))
				{
					std::wcout << L"error saving file.\n";
				}
			}
			else
			{
				std::wcout << L"Scene must have at least one object and one light!!\n";
			}
		}
		else
		{
			std::wcout << L"Errors found during finalise phase. Likely missing materials.\n";
		}
	}

	delete GWorld;
	delete GConfiguration;

	return 0;
}