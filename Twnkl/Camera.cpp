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

#include <math.h>

#include "Camera.h"


Camera::Camera(int h, int v, double f)
{
	Width = h;
	Height = v;
	FoV = f;

	CalculatePixelSize();
}


Camera::Camera(int h, int v, double f, Matrix4 t)
{
	Width = h;
	Height = v;
	FoV = f;
	Transform = t;

	CalculatePixelSize();
}


void Camera::CalculatePixelSize()
{
	HalfView = tan(FoV / 2.0);

	double aspect = (double)Width / (double)Height;

	if (aspect >= 1.0)
	{
		HalfWidth = HalfView;
		HalfHeight = HalfView / aspect;
	}
	else
	{
		HalfWidth = HalfView * aspect;
		HalfHeight = HalfView;
	}

	PixelSize = (HalfWidth * 2.0) / (double)Width;
}