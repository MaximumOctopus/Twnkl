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

#include "PatternCommon.h"
#include "Fractal.h"


Fractal::Fractal(std::wstring name) : Pattern(name)
{
	Name = name;

    noize = new Noise();
}


Fractal::~Fractal()
{
    delete noize;
}


void Fractal::SetFALP(double f, double a, double l, double p)
{
    noize->SetFALP(f, a, l, p);
}


Colour Fractal::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

    double delta = 0.5 * (1.0 + noize->Fractal(pattern_point));

    double r = Colours[0].r + ((Colours[1].r - Colours[0].r) * delta);
    double g = Colours[0].g + ((Colours[1].g - Colours[0].g) * delta);
    double b = Colours[0].b + ((Colours[1].b - Colours[0].b) * delta);

    return Colour(r, g, b);
}


std::wstring Fractal::ToString()
{
	return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}