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

#include "Pattern.h"


Pattern::Pattern(std::wstring name)
{

}


void Pattern::SetColours(Colour a, Colour b)
{
	Colours[0] = a;
	Colours[1] = b;
}


void Pattern::SetReflectivity(double a, double b)
{
	Reflectivity[0] = a;
	Reflectivity[1] = b;

	HasReflectivity = true;
}


Colour Pattern::ColourAt(Object*, Quaternion&)
{
	return Colour(1.0, 0, 1.0);
}


void Pattern::ProcessTransforms()
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


void Pattern::AddTransform(TransformConfiguration tc)
{
	Transforms.push_back(tc);
}


void Pattern::RemoveTransformAt(int index)
{
	Transforms.erase(Transforms.begin() + index);

	// if there are no transforms then the transform "merg" won't happen,
	// and the Transform will not change to reflect the lack of transforms in the stack.
	// so we reset the Transform to the identity matrix. 
	if (Transforms.size() == 0)
	{
		Transform = Matrix4();
	}
}


void Pattern::CreateInverseTransform()
{
	InverseTransform = Transform.Inverse();
}


int Pattern::TransformsCount()
{
	return Transforms.size();
}


TransformConfiguration Pattern::TransformAt(int index)
{
	return Transforms[index];
}


void Pattern::TransformReplaceAt(int index, TransformConfiguration tc)
{
	Transforms[index].Type = tc.Type;

	Transforms[index].Angle = tc.Angle;
	Transforms[index].XYZ = tc.XYZ;

	switch (Transforms[index].Type)
	{
	case TransformType::Scale:
		Transforms[index].Transform = Matrix4(0, tc.XYZ.x, tc.XYZ.y, tc.XYZ.z);
		break;
	case TransformType::Translate:
		Transforms[index].Transform = Matrix4(1, tc.XYZ.x, tc.XYZ.y, tc.XYZ.z);
		break;
	case TransformType::RotateX:
		Transforms[index].Transform = Matrix4(0, tc.Angle);
		break;
	case TransformType::RotateY:
		Transforms[index].Transform = Matrix4(1, tc.Angle);
		break;
	case TransformType::RotateZ:
		Transforms[index].Transform = Matrix4(2, tc.Angle);
		break;
	}
}


std::wstring Pattern::FriendlyName()
{
	switch (Design)
	{
	case PatternDesign::None:
		return L"None!";
	case PatternDesign::Checkerboard:
		return L"Checkerboard";
	case PatternDesign::Gradient:
		return L"Gradient";
	case PatternDesign::Gradient2:
		return L"Gradient II";
	case PatternDesign::Ring:
		return L"Ring";
	case PatternDesign::Stripey:
		return L"Stripey";
	case PatternDesign::Fractal:
		return L"Fractal";
	case PatternDesign::Simplex:
		return L"Simplex";
	case PatternDesign::Perlin1:
		return L"Perlin";
	case PatternDesign::Perlin2:
		return L"Perlin II";
	case PatternDesign::Perlin3:
		return L"Perlin III";
	case PatternDesign::CubeCheckerboard:
		return L"Checkerboard (Cube)";
	case PatternDesign::CubeTexture:
		return L"Texture (Cube)";
	case PatternDesign::CubeMultiTexture:
		return L"Multi-texture (Cube)";
	case PatternDesign::CylinderCheckerboard:
		return L"Checkerboard (Cylinder)";
	case PatternDesign::CylinderTexture:
		return L"Texture (Cylinder)";
	case PatternDesign::PlanarTexture:
		return L"Texture (Planar)";
	case PatternDesign::SphericalCheckerboard:
		return L"Checkerboard (Sphere)";
	case PatternDesign::SphericalTexture:
		return L"Texture (Spherical)";
	}

	return L"Unknown";
}


std::wstring Pattern::ToString()
{
	return L"base class!";
}


void Pattern::ToFile(std::ofstream& ofile)
{
}