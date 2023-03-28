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


static const int kDisplayModeConsole = 0;
static const int kDisplayModeFile = 1;


namespace DateUtility
{
	[[nodiscard]] std::wstring DateTime(int);
}