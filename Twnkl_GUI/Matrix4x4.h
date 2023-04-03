#pragma once

class Matrix4x4
{
public:

	double Data[4][4] = { {1, 0, 0, 0}, 
		                  {0, 1, 0, 0},
						  {0, 0, 1, 0},
		                  {0, 0, 0, 1} };

	// identity matrix
	Matrix4x4();

	Matrix4x4(int, double);

	Matrix4x4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);

	// translation matrix
	Matrix4x4(double, double, double);

	// shearing matrix
	Matrix4x4(double, double, double, double, double, double);

	double Determinant();

	void Invert();

	bool Equals(Matrix4x4);
};