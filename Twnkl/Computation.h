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


#include "Quaternion.h"


class Computation
{
public:

	double Tvalue = 0;
	int ObjectID = 0;
	
	Quaternion EyeVector;
	Quaternion NormalVector;
	Quaternion OverPoint;
	Quaternion ReflectVector;
	Quaternion UnderPoint;

	double N1 = 0.0;
	double N2 = 0.0;

	Computation(double, int, Quaternion, Quaternion, Quaternion, Quaternion, Quaternion, double, double) noexcept;

	[[nodiscard]] double Schlick();
};