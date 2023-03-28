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

#include "Ray.h"


Ray::Ray(Quaternion p, Quaternion v) noexcept
{
	Origin = p;

	Direction = v;
}


Ray::Ray(double px, double py, double pz, double vx, double vy, double vz) noexcept
{
	Origin = Quaternion(px, py, pz, 1);

	Direction = Quaternion(vx, vy, vz, 0);
}


Quaternion Ray::Position(double t)
{
	return Quaternion(Origin.x + (Direction.x * t),
					  Origin.y + (Direction.y * t),
		              Origin.z + (Direction.z * t),
					  Origin.w + (Direction.w * t)); // 1?
}


// returns a ray that's been transformed by the input matrix
Ray Ray::Transform(Matrix4& m)
{
	double i[4] = { 0, 0, 0, 0 };
	double j[4] = { 0, 0, 0, 0 };

	for (int y = 0; y < 4; y++)
	{
		i[y] += m.Data[y][0] * Origin.x +
			m.Data[y][1] * Origin.y +
			m.Data[y][2] * Origin.z +
			m.Data[y][3] * Origin.w;

		j[y] += m.Data[y][0] * Direction.x +
			m.Data[y][1] * Direction.y +
			m.Data[y][2] * Direction.z +
			m.Data[y][3] * Direction.w;
	}

	return Ray(i[0], i[1], i[2], j[0], j[1], j[2]);
}


// returns a negative version of the current ray
// by negating the direction vector
Ray Ray::Negate()
{
	return Ray(Origin.x, Origin.y, Origin.z, -Direction.x, -Direction.y, -Direction.z);
}


Quaternion Ray::NegativeDirection()
{
	return Quaternion(-Direction.x, -Direction.y, -Direction.z, 0);
}


std::wstring Ray::ToString()
{
	std::wstring w = std::to_wstring(Origin.x) + L" / " + std::to_wstring(Origin.y) + L" / " + std::to_wstring(Origin.z) + L" :: " +
		std::to_wstring(Direction.x) + L" // " + std::to_wstring(Direction.y) + L" // " + std::to_wstring(Direction.z);

	return w;
}