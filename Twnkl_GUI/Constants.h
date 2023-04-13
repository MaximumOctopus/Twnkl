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
#ifdef _GUI
static const std::wstring __TwnklVersion = L"0.8 GUI (debug)";
#else
static const std::wstring __TwnklVersion = L"0.6 (debug)";
#endif
#else
#ifdef _GUI
static const std::wstring __TwnklVersion = L"0.8 GUI";
#else
static const std::wstring __TwnklVersion = L"0.5";
#endif
#endif

static const std::wstring __TwnklDate = L"April 13th 2023";

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

static std::wstring __SceneChunkCamera = L"{camera";
static std::wstring __SceneChunkPointLight = L"{pointlight";
static std::wstring __SceneChunkAreaLight = L"{arealight";

static std::wstring __SceneChunkObjectSphere = L"{objectsphere";
static std::wstring __SceneChunkObjectPlane = L"{objectplane";
static std::wstring __SceneChunkObjectCone = L"{objectcone";
static std::wstring __SceneChunkObjectCube = L"{objectcube";
static std::wstring __SceneChunkObjectCylinder = L"{objectcylinder";
static std::wstring __SceneChunkObjectModel = L"{objectmodel";
static std::wstring __SceneChunkObjectModelSmooth = L"{objectmodelsmooth";
static std::wstring __SceneChunkObjectSmoothTriangle = L"{objectsmoothtriangle";
static std::wstring __SceneChunkObjectTriangle = L"{objecttriangle";

static std::wstring __SceneChunkMaterial = L"{material";
static std::wstring __SceneChunkTransform = L"{transform";

static std::wstring __SceneChunkChecker = L"{patternchecker";
static std::wstring __SceneChunkGradient = L"{patterngradient";
static std::wstring __SceneChunkGradient2 = L"{patterngradient2";
static std::wstring __SceneChunkRing = L"{patternring";
static std::wstring __SceneChunkStripey = L"{patternstripey";
static std::wstring __SceneChunkPerlin = L"{patternperlin";
static std::wstring __SceneChunkPerlin2 = L"{patternperlin2";
static std::wstring __SceneChunkPerlin3 = L"{patternperlin3";
static std::wstring __SceneChunkTexture = L"{patterntexture";
static std::wstring __SceneChunkFractal = L"{patternfractal";
static std::wstring __SceneChunkSimplex = L"{patternsimplex";
