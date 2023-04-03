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

#ifdef _DEBUG
static const std::wstring __TwnklVersion = L"0.5 (debug)";
#else
static const std::wstring __TwnklVersion = L"0.5";
#endif

static const std::wstring __TwnklDate = L"March 28th 2023";

static double epsilon = 0.0001;

static double __DefaultMaterialAmbient = 0.1;
static double __DefaultMaterialDiffuse = 0.9;
static double __DefaultMaterialReflectivity = 0.0;
static double __DefaultMaterialRefractiveIndex = 1.0;
static double __DefaultMaterialShininess = 200.0;
static double __DefaultMaterialSpecular = 0.9;
static double __DefaultMaterialTransparency = 0.0;

static int __DefaultRendererShadowDetail = 5;
static int __DefaultRendererLightRecursion = 5;
static int __DefaultRendererSamplesPerPixel = 0;

static double __DefaultPerlinScale = 1.0;
static double __DefaultPerlinPhase = 10.0;

static double __DefaultFractalFrequency = 1.0;
static double __DefaultFractalAmplitude = 1.0;
static double __DefaultFractalLacunarity = 2.0;
static double __DefaultFractalPersistence = 0.5;
