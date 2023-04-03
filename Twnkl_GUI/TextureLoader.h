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

#include "Colour.h"


class TextureLoader
{
public:

	int TextureHeight = 0;	// size of loaded texture
	int TextureWidth = 0;	// size of loaded texture

	bool Go(Colour**, const std::wstring, bool);
};