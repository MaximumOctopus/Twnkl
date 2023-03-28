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


namespace Utility
{
	[[nodiscard]] int CurrentYear();

	[[nodiscard]] std::wstring GetFileExtension(const std::wstring&);
	[[nodiscard]] std::wstring ProcessFileName(const std::wstring&);

	[[nodiscard]] std::wstring ReplaceString(const std::wstring, const std::wstring&, const std::wstring&);
}