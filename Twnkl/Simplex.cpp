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
#include "Simplex.h"


Simplex::Simplex(std::wstring name) : Pattern(name)
{
    Name = name;
    Design = PatternDesign::Simplex;

    noize = new Noise();
}


Simplex::~Simplex()
{
    delete noize;
}


Colour Simplex::ColourAt(Object* o, Quaternion& q)
{
    Quaternion object_point = o->InverseTransform.MultQ(q);
    Quaternion pattern_point = InverseTransform.MultQ(object_point);

    if (Simple)
    {
        if (noize->Simplex(pattern_point.x, pattern_point.y, pattern_point.z) > 0)
        {
            return Colours[0];
        }

        return Colours[1];
    }

    double delta = 0.5 * (1.0 + noize->Simplex(pattern_point.x, pattern_point.y, pattern_point.z));

    double r = Colours[0].r + ((Colours[1].r - Colours[0].r) * delta);
    double g = Colours[0].g + ((Colours[1].g - Colours[0].g) * delta);
    double b = Colours[0].b + ((Colours[1].b - Colours[0].b) * delta);

    return Colour(r, g, b);
}


std::wstring Simplex::ToString()
{
    return L"#1 " + Colours[0].ToString() + L" #2 " + Colours[1].ToString();
}


void Simplex::ToFile(std::ofstream& ofile)
{
    ofile << Formatting::to_utf8(__SceneChunkSimplex + L"\n");
    ofile << Formatting::to_utf8(L"colour=" + Colours[0].ToCommaString() + L"\n");
    ofile << Formatting::to_utf8(L"colour=" + Colours[1].ToCommaString() + L"\n");
    if (Simple)
    {
        ofile << Formatting::to_utf8(L"simple=yes\n");
    }
    ofile << Formatting::to_utf8(L"}\n");

    for (int t = 0; t < Transforms.size(); t++)
    {
        Transforms[t].ToFile(ofile);
    }
}