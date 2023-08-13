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

#include <fstream>
#include <math.h>

#include "Camera.h"
#include "Constants.h"
#include "Formatting.h"


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
	if (Width != 0 && Height != 0)
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
}


void Camera::SetViewport(Quaternion from, Quaternion to, Quaternion up)
{
	From = from;
	To = to;
	Up = up;
}


void Camera::ResizeToFit(int gui_width, int gui_height)
{
	double scene_aspect = (double)gui_width / double(gui_height);

	double xratio = (double)gui_width / (double)Width;
	double yratio = (double)gui_height / (double)Height;

	if (xratio > yratio)
	{
		Width = std::floor(scene_aspect * (double)gui_height);
		Height = std::floor((double)gui_height);
	}
	else
	{
		Width = std::floor((double)gui_width);
		Height = std::floor((1.0 / scene_aspect) * (double)gui_width);
	}

	CalculatePixelSize();
}


void Camera::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkCamera + L"\n");
	ofile << Formatting::to_utf8(L"width=" + std::to_wstring(Width) + L"\n");
	ofile << Formatting::to_utf8(L"height=" + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"focallength=" + std::to_wstring(FoV) + L"\n");
	ofile << Formatting::to_utf8(L"from=" + std::to_wstring(From.x) + L", " + std::to_wstring(From.y) + L", " + std::to_wstring(From.z) + L"\n");
	ofile << Formatting::to_utf8(L"to=" + std::to_wstring(To.x) + L", " + std::to_wstring(To.y) + L", " + std::to_wstring(To.z) + L"\n");
	ofile << Formatting::to_utf8(L"up=" + std::to_wstring(Up.x) + L", " + std::to_wstring(Up.y) + L", " + std::to_wstring(Up.z) + L"\n");
	ofile << Formatting::to_utf8(L"}\n");
}