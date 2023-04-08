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

#include <iostream>
#include <math.h>

#include "Constants.h"
#include "Quaternion.h"


Quaternion::Quaternion() noexcept
{

}


// create random between from and to
Quaternion::Quaternion(double min, double max) noexcept
{
	x = min + (max - min) * (rand() / (RAND_MAX + 1.0));
	y = min + (max - min) * (rand() / (RAND_MAX + 1.0));
	z = min + (max - min) * (rand() / (RAND_MAX + 1.0));

	w = 0;
}


Quaternion::Quaternion(double xx, double yy, double zz, double ww) noexcept
{
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}


void Quaternion::Add(Quaternion& q)
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
}


void Quaternion::Sub(Quaternion& q)
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;
}


Quaternion Quaternion::SubQ(Quaternion& q)
{
	return Quaternion(x - q.x, 
		y - q.y,
		z - q.z,
		w - q.w);
}


void Quaternion::Negate()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}


void Quaternion::Scale(double factor)
{
	x = factor * x;
	y = factor * y;
	z = factor * z;
	w = factor * w;
}


Quaternion Quaternion::Mult(double factor)
{
	return Quaternion(factor * x, 
	factor * y,
	factor * z,
	factor * w);
}


void Quaternion::Normalise()
{
	double m = Magnitude();

	x = x / m;
	y = y / m;
	z = z / m;
	w = w / m;
}


double Quaternion::Dot(Quaternion& q)
{
	return (x * q.x) + (y * q.y) + (z * q.z) + (w * q.w);
}


Quaternion Quaternion::Cross(Quaternion& a, Quaternion& b)
{
	return Quaternion(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0);
}


Quaternion Quaternion::Cross(Quaternion& b)
{
	return Quaternion(y * b.z - z * b.y,
		z * b.x - x * b.z,
		x * b.y - y * b.x,
		0);
}


double Quaternion::Magnitude()
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}


// reflect around normal vector q
Quaternion Quaternion::Reflect(Quaternion& q)
{
	double twodot = 2.0 * ((x * q.x) + (y * q.y) + (z * q.z) + (w * q.w));

	return Quaternion(x - (q.x * twodot),
		y - (q.y * twodot),
		z - (q.z * twodot),
		0);// w - (q.w * twodot));
}

// from (this): point
// to         : point
// up         : vector
Matrix4 Quaternion::ViewTransform(Quaternion& to, Quaternion& up)
{
	Quaternion forward = Quaternion(to.x - x, to.y - y, to.z - z, to.w - w);

	forward.Normalise();

	up.Normalise();

	Quaternion left = Cross(forward, up);

	Quaternion true_up = Cross(left, forward);

	Matrix4 orientation = Matrix4(left.x, left.y, left.z, 0,
		true_up.x, true_up.y, true_up.z, 0,
		-forward.x, -forward.y, -forward.z, 0,
		0, 0, 0, 1);

	Matrix4 translation = Matrix4(1, -x, -y, -z);

	return orientation.MultM(translation);
}


bool Quaternion::Equals(Quaternion& q)
{
	double xx = std::abs(x - q.x);
	double yy = std::abs(y - q.y);
	double zz = std::abs(z - q.z);
	double ww = std::abs(w - q.w);

	if (xx < epsilon && yy < epsilon && zz < epsilon && ww < epsilon)
	{
		return true;
	}

	return false;
}


std::wstring Quaternion::ToString()
{
	std::wstring s = std::to_wstring(x) + L" / " + std::to_wstring(y) + L" / " + std::to_wstring(z) + L" / " + std::to_wstring(w);

	return s;
}