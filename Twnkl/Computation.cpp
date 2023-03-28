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

#include "Computation.h"


Computation::Computation(double tv, int id, Quaternion e, Quaternion n, Quaternion o, Quaternion u, Quaternion r, double n1, double n2) noexcept
{
	Tvalue = tv;
	ObjectID = id;

	EyeVector = e;
	NormalVector = n;
	OverPoint = o;
	ReflectVector = r;
	UnderPoint = u;

	N1 = n1;
	N2 = n2;
}


double Computation::Schlick()
{
	// find the cosine of the angle between the eye and normal vectors
	double cenv = EyeVector.Dot(NormalVector);

	// total internal reflection can only occur if n1 > n2
	if (N1 > N2)
	{
		double n = N1 / N2;

		double sin2_t = n * n * (1.0 - cenv * cenv);

		// total internal reflection!
		if (sin2_t > 1.0)
		{
			return 1.0;
		}

		// when n1 > n2, use cos(theta_t) instead
		cenv = sqrt(1.0 - sin2_t);
	}

	double rzero = ((N1 - N2) / (N1 + N2)) * ((N1 - N2) / (N1 + N2));

	return rzero + (1.0 - rzero) * pow(1.0 - cenv, 5);
}