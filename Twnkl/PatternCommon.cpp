

#include "PatternCommon.h"


std::pair<double, double> PatternCommon::CylindricalMap(Quaternion& p)
{
	// compute the azimuthal angle, same as sphericalmap()
	double theta = atan2(p.x, p.z);
	double raw_u = theta / (2.0 * 3.1415926535);
	double u = 1.0 - (raw_u + 0.5);

	// let v go from 0 to 1 between whole units of y
	double v = fmod(p.y, 1.0);

	return { u, v };
}


std::pair<double, double> PatternCommon::SphericalMap(Quaternion& p)
{
	// compute the azimuthal angle
	// -pi < theta <= pi
	// angle increases clockwise as viewed from above,
	// which is opposite of what we want, but we'll fix it later.
	double theta = atan2(p.x, p.z);

	// vec is the vector pointing from the sphere's origin (the world origin)
	// to the point, which will also happen to be exactly equal to the sphere's radius.
	Quaternion vec = Quaternion(p.x, p.y, p.z, 0);
	double radius = vec.Magnitude();

	// compute the polar angle
	// 0 <= phi <= pi
	double phi = acos(p.y / radius);

	// -0.5 < raw_u <= 0.5
	double raw_u = theta / (2.0 * 3.1415926535);

	// 0 <= u < 1
	// here's also where we fix the direction of u. Subtract it from 1,
	// so that it increases counterclockwise as viewed from above.
	double u = 1.0 - (raw_u + 0.5);

	// we want v to be 0 at the south pole of the sphere,
	// and 1 at the north pole, so we have to "flip it over"
	// by subtracting it from 1.
	double v = 1.0 - (phi / 3.1415926535);

	return { u, v };
}


int PatternCommon::FaceFromPoint(Quaternion p)
{
	double abs_x = std::abs(p.x);
	double abs_y = std::abs(p.y);
	double abs_z = std::abs(p.z);
	double coord = std::max(abs_x, std::max(abs_y, abs_z));

	if (coord == p.x)			// right
		return 0;
	else if (coord == -p.x)		// left
		return 1;
	else if (coord == p.y)		// up
		return 2;
	else if (coord == -p.y)		// down
		return 3;
	else if (coord == p.z)		// front
		return 4;

	return 5;				// back
}


std::pair<double, double> PatternCommon::CubeUVFront(Quaternion& p)
{
	double u = fmod(p.x + 1, 2.0) / 2.0;
	double v = fmod(p.y + 1, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> PatternCommon::CubeUVBack(Quaternion& p)
{
	double u = fmod(1 - p.x, 2.0) / 2.0;
	double v = fmod(p.y + 1, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> PatternCommon::CubeUVLeft(Quaternion& p)
{
	double u = fmod(p.z + 1.0, 2.0) / 2.0;
	double v = fmod(p.y + 1.0, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> PatternCommon::CubeUVRight(Quaternion& p)
{
	double u = fmod(1 - p.z, 2.0) / 2.0;
	double v = fmod(p.y + 1, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> PatternCommon::CubeUVUp(Quaternion& p)
{
	double u = fmod(p.x + 1, 2.0) / 2.0;
	double v = fmod(1 - p.z, 2.0) / 2.0;

	return { u, v };
}


std::pair<double, double> PatternCommon::CubeUVDown(Quaternion& p)
{
	double u = fmod(p.x + 1, 2.0) / 2.0;
	double v = fmod(p.z + 1, 2.0) / 2.0;

	return { u, v };
}