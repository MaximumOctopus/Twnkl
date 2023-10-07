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

#include "Constants.h"

class TwnklProject
{
public:

	std::wstring Author = L"";
	std::wstring Description = L"";

	void ToFile(std::ofstream& ofile)
	{
		ofile << Formatting::to_utf8(__SceneChunkProject + L"\n");
		ofile << Formatting::to_utf8(L"author=" + Author + L"\n");
		ofile << Formatting::to_utf8(L"description=" + Description + L"\n");
		ofile << Formatting::to_utf8(L"}\n");
	}
};
