#pragma once

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
};