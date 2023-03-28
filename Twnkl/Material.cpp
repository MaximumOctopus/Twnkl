#include "Material.h"


Material::Material()
{

}


Material::Material(double a, double d, double h, double p)
{
	Ambient = a;
	Diffuse = d;
	Shininess = h;
	Specular = p;
}