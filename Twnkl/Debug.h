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


#include <source_location>
#include <string>


namespace TwnklDebug
{
	void Output(const std::wstring, const std::source_location& = std::source_location::current());
}