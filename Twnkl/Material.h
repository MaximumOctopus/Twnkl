#pragma once

class Material
{
public:

	double Ambient = 0;
	double Diffuse = 0;
	double Shininess = 0;
	double Specular = 0;

	Material();

	Material(double, double, double, double);
};