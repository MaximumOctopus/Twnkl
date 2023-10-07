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

#include "Formatting.h"
#include "Matrix4.h"


enum class TransformType { None = 0, Scale = 1, Translate = 2, RotateX = 3, RotateY = 4, RotateZ = 5 };


struct TransformConfiguration
{
	TransformType Type = TransformType::None;

	Matrix4 Transform;

	Quaternion XYZ;
	double Angle = 0;					// radians

	std::wstring TypeAsString()
	{
		switch (Type)
		{
		case TransformType::None:
			return L"None";
		case TransformType::Scale:
			return L"Scale";
		case TransformType::Translate:
			return L"Translate";
		case TransformType::RotateX:
			return L"Rotate x-axis";
		case TransformType::RotateY:
			return L"Rotate y-axis";
		case TransformType::RotateZ:
			return L"Rotate z-axis";
		}

		return L"Error!";
	}


	// as the actual Transform and the readable values are not linked,
	// if either XYZ or angle is altered, then calling rebuild will
	// recreate the Transform using the new values
	void Rebuild()
	{
		switch (Type)
		{
		case TransformType::None:
            break;
		case TransformType::Scale:
			Transform = Matrix4(0, XYZ.x, XYZ.y, XYZ.z);
			break;
		case TransformType::Translate:
			Transform = Matrix4(1, XYZ.x, XYZ.y, XYZ.z);
			break;
		case TransformType::RotateX:
			Transform = Matrix4(0, Angle);
			break;
		case TransformType::RotateY:
			Transform = Matrix4(1, Angle);
			break;
		case TransformType::RotateZ:
			Transform = Matrix4(2, Angle);
			break;
		}
	}


	void ToFile(std::ofstream& ofile)
	{
		ofile << Formatting::to_utf8(__SceneChunkTransform + L"\n");
		switch (Type)
		{
		case TransformType::None:
			break;
		case TransformType::Scale:
			ofile << Formatting::to_utf8(L"type=scale\n");
			break;
		case TransformType::Translate:
			ofile << Formatting::to_utf8(L"type=translate\n");
			break;
		case TransformType::RotateX:
			ofile << Formatting::to_utf8(L"type=rotatex\n");
			break;
		case TransformType::RotateY:
			ofile << Formatting::to_utf8(L"type=rotatey\n");
			break;
		case TransformType::RotateZ:
			ofile << Formatting::to_utf8(L"type=rotatez\n");
			break;
		}
		switch (Type)
		{
		case TransformType::None:
			break;
		case TransformType::Scale:
		case TransformType::Translate:
			ofile << Formatting::to_utf8(L"xyz=" + std::to_wstring(XYZ.x) + L", " + std::to_wstring(XYZ.y) + L", " + std::to_wstring(XYZ.z) + L"\n");
			break;
		case TransformType::RotateX:
		case TransformType::RotateY:
		case TransformType::RotateZ:
			ofile << Formatting::to_utf8(L"angle=" + std::to_wstring(Angle) + L"\n");
			break;
		}
		ofile << Formatting::to_utf8(L"}\n");
	}
};