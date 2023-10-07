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


Pattern::Pattern(bool noise, std::wstring name)
{
	IncludeNoise = noise;

	if (IncludeNoise)
	{
		noize = new Noise();
	}
}


Pattern::~Pattern()
{
	if (IncludeNoise)
	{
		delete noize;
	}
}


void Pattern::SetNoise(double f, double a, double l, double p, double ps, double sl)
{
   	noize->SetFALPI(f, a, l, p, 10);

	pscale = ps;
	scale = sl;
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
	case TransformType::None:
        break;
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
	std::wstring name = L"";

	switch (Design)
	{
	case PatternDesign::None:
		name = L"None!";
		break;
	case PatternDesign::Checkerboard:
		name = L"Checkerboard";
		break;
	case PatternDesign::Gradient:
		name = L"Gradient";
		break;
	case PatternDesign::Gradient2:
		name = L"Gradient II";
		break;
	case PatternDesign::Ring:
		name = L"Ring";
		break;
	case PatternDesign::Stripey:
		name = L"Stripey";
		break;
	case PatternDesign::Fractal:
		name = L"Fractal";
		break;
	case PatternDesign::Simplex:
		name = L"Simplex";
		break;
	case PatternDesign::Perlin1:
		name = L"Perlin";
		break;
	case PatternDesign::Perlin2:
		name = L"Perlin II";
		break;
	case PatternDesign::Perlin3:
		name = L"Perlin III";
		break;
	case PatternDesign::CubeCheckerboard:
		name = L"Checkerboard (Cube)";
		break;
	case PatternDesign::CubeTexture:
		name = L"Texture (Cube)";
		break;
	case PatternDesign::CubeMultiTexture:
		name = L"Multi-texture (Cube)";
		break;
	case PatternDesign::CylinderCheckerboard:
		name = L"Checkerboard (Cylinder)";
		break;
	case PatternDesign::CylinderTexture:
		name = L"Texture (Cylinder)";
		break;
	case PatternDesign::PlanarTexture:
		name = L"Texture (Planar)";
		break;
	case PatternDesign::SphericalCheckerboard:
		name = L"Checkerboard (Sphere)";
		break;
	case PatternDesign::SphericalTexture:
		name = L"Texture (Spherical)";
		break;

	default:
		return L"Unknown";
		break;
	}

	if (IncludeNoise)
	{
        name += L" (+ noise)";
	}

	return name;
}


std::wstring Pattern::ToString()
{
	return L"base class!";
}


void Pattern::ToFile(std::ofstream& ofile)
{
}