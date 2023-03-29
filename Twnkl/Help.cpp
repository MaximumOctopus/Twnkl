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

#include <iostream>
#include <string>

#include "Constants.h"
#include "Help.h"


namespace Help
{
	void About()
	{
		Header();

		std::wcout << L"    /saveconfig:file_name      : save parameter list to a file\n";
		std::wcout << L"    /loadconfig:file_name      : load parameter list from a file\n";
		std::wcout << L"\n";
		std::wcout << L"    /scene:file_name           : load scene from file\n";
		std::wcout << L"\n";
		std::wcout << L"    /export:file_name          : save render to file_name\n";
		std::wcout << L"                                 default is yyyymmdd_hhmmss.ppm\n";
		std::wcout << L"\n";
		std::wcout << L"    /width:pixels              : image width\n";
		std::wcout << L"    /height:pixels             : image height\n";
		std::wcout << L"                                 overrides any values set in scene file.\n";
		std::wcout << L"\n";
		std::wcout << L"    /samples:x                 : supersampling resample count\n";
		std::wcout << L"                                 default is 0 (off)\n";
		std::wcout << L"    /recursion:x               : reflection/refraction ray recursion\n";
		std::wcout << L"                                 default is 5\n";
		std::wcout << L"    /shadow:x                  : shadow detail (only valid for area lights)\n";
		std::wcout << L"                                 default is 5\n";
		std::wcout << L"\n";
		std::wcout << L"    /debug	                   : shows various debug output\n";
		std::wcout << L"                                 (includes scene debug)\n";
		std::wcout << L"\n";
	}

	void Header()
	{
		std::wcout << L"\n  Twnkl " << __TwnklVersion << L" / " << __TwnklDate << "\n\n";

		std::wcout << L"    (c) Paul Alan Freshney 2023\n\n";
		std::wcout << L"      https://github.com/MaximumOctopus/Twnkl\n";
		std::wcout << L"      paul@freshney.org\n\n";
	}
}