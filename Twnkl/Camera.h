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

#include "Matrix4.h"


class Camera
{

public:

	Quaternion From;
	Quaternion To;
	Quaternion Up;

	int Width = 0;
	int Height = 0;
	double FoV = 0;
	Matrix4 Transform;
	Matrix4 InverseTransform;

	double HalfView = 0;
	double HalfWidth = 0;
	double HalfHeight = 0;

	double PixelSize = 0;

	// create camera using identity matrix for transform
	Camera(int, int, double);

	// create camera using custom transform
	Camera(int, int, double, Matrix4);

	// not used by the code, but needed for output
	void SetViewport(Quaternion, Quaternion, Quaternion);

	void CalculatePixelSize();

	void ToFile(std::ofstream&);
};