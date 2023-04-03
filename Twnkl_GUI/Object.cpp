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

#include "Object.h"


Object::Object(std::wstring n)
{
	Name = n;
}


void Object::SetMaterial(PhongMaterial p)
{
	Material->Ambient = p.Ambient;
	Material->Diffuse = p.Diffuse;
	Material->Reflectivity = p.Reflectivity;
	Material->RefractiveIndex = p.RefractiveIndex;
	Material->Shininess = p.Shininess;
	Material->Specular = p.Specular;
	Material->Transparency = p.Transparency;
}


void Object::ProcessTransforms()
{
	for (int t = 0; t < Transforms.size(); t++)
	{
		if (t == 0)
		{
			Transform = Transforms[t].Transform;
		}
		else
		{
			Transform.MultiplyBy(Transforms[t].Transform);
		}
	}

	CreateInverseTransform();
}


void Object::AddTransform(TransformConfiguration tc)
{
	Transforms.push_back(tc);
}


void Object::CreateInverseTransform()
{
	InverseTransform = Transform.Inverse();
}


int Object::TransformsCount()
{
	return Transforms.size();
}


TransformConfiguration Object::TransformAt(int index)
{
	return Transforms[index];
}


void Object::Intersects(Intersections &i, Ray& r)
{
	Ray local_ray = r.Transform(InverseTransform);

	LocalIntersect(i, local_ray);
}


Quaternion Object::WorldToObject(Quaternion& point)
{
	Quaternion new_point(point);

	if (Parent != nullptr)
	{
		new_point = Parent->WorldToObject(point);
	}

	return InverseTransform.MultQ(new_point);
}


Quaternion Object::NormalToWorld(Quaternion& normal)
{
	Quaternion new_normal = InverseTransform.Transpose().MultQ(normal);
	new_normal.w = 0;
	new_normal.Normalise();

	if (Parent != nullptr)
	{
		new_normal = Parent->NormalToWorld(new_normal);
	}

	return new_normal;
}


Quaternion Object::NormalAt(Quaternion& world_point)
{
	Quaternion local_point = WorldToObject(world_point);
	Quaternion local_normal = LocalNormalAt(local_point);

	return NormalToWorld(local_normal);
}


void Object::LocalIntersect(Intersections &i, Ray& rt)
{
}


Quaternion Object::LocalNormalAt(Quaternion& q)
{
	return q;
}


void Object::PostSetup(int i)
{

}


std::wstring Object::ToString()
{
	return L"Object.";
}