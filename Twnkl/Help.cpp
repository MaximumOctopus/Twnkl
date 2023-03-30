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
	void Header()
	{
		std::wcout << L"\n  Twnkl " << __TwnklVersion << L" / " << __TwnklDate << "\n\n";

		std::wcout << L"    (c) Paul Alan Freshney 2023\n\n";
		std::wcout << L"      https://github.com/MaximumOctopus/Twnkl\n";
		std::wcout << L"      paul@freshney.org\n\n";
	}


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
		std::wcout << L"                                 default is " << __DefaultRendererSamplesPerPixel << L" (off)\n";
		std::wcout << L"    /recursion:x               : reflection/refraction ray recursion\n";
		std::wcout << L"                                 default is " << __DefaultRendererLightRecursion << L"\n";
		std::wcout << L"    /shadow:x                  : shadow detail (only valid for area lights)\n";
		std::wcout << L"                                 default is " << __DefaultRendererShadowDetail << L"\n";
		std::wcout << L"\n";
		std::wcout << L"    /debug	                   : displays extra output\n";
		std::wcout << L"                                 (includes scene debug)\n";
		std::wcout << L"\n";
	}


	// all of my software is now free and open source. 
	// please donate to your local cat charity or shelter.
	void Cat()
	{
		std::wcout << "\n";
		std::wcout << L"               *        ,MMM8&&&.            *\n";
		std::wcout << L"                       MMMM88&&&&&    .\n";
		std::wcout << L"                      MMMM88&&&&&&&\n";
		std::wcout << L"       *              MMM88&&&&&&&&\n";
		std::wcout << L"                      MMM88&&&&&&&&\n";
		std::wcout << L"                      'MMM88&&&&&&'\n";
		std::wcout << L"                        'MMM8&&&'      *\n";
		std::wcout << L"            |\\___/|\n";
		std::wcout << L"            )     (             .              \n";
		std::wcout << L"           =\\     /=\n";
		std::wcout << L"             )===(       *\n";
		std::wcout << L"            /     \\\n";
		std::wcout << L"            |     |\n";
		std::wcout << L"           /       \\\n";
		std::wcout << L"           \\       /\n";
		std::wcout << L"    _/\\_/\\_/\\__  _/_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_\n";
		std::wcout << L"    |  |  |  |( (  |  |  |  |  |  |  |  |  |  |\n";
		std::wcout << L"    |  |  |  | ) ) |  |  |  |  |  |  |  |  |  |\n";
		std::wcout << L"    |  |  |  |(_(  |  |  |  |  |  |  |  |  |  |\n";
		std::wcout << L"    |  |  |  |  |  |  |  |  |  |  |  |  |  |  |\n";
		std::wcout << L"    |  |  |  |  |  |  |  |  |  |  |  |  |  |  |\n";
		std::wcout << "\n";
		std::wcout << L"please donate to your local cat charity or shelter.\n\n";
		std::wcout << L"A big thanks to my cats, Rutherford, Freeman, and Maxwell\n";
		std::wcout << "\n";
		std::wcout << L"        www.maximumoctopus.com/developmentcats.htm\n";
		std::wcout << "\n";
	}
}