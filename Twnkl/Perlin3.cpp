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

#include <cmath>

#include "Fast.h"
#include "PatternCommon.h"
#include "Perlin3.h"


Perlin3::Perlin3(bool noise, std::wstring name) : Pattern(noise, name)
{
	Name = name;
	Design = PatternDesign::Perlin3;

	ranvec = new Quaternion[point_count];

	for (int i = 0; i < point_count; ++i)
	{
		ranvec[i] = Quaternion(-1, 1);

		ranvec[i].Normalise();
	}

	perm_x = PerlinGeneratePerm();
	perm_y = PerlinGeneratePerm();
	perm_z = PerlinGeneratePerm();
}


Perlin3::~Perlin3()
{
	delete[] ranvec;
	delete[] perm_x;
	delete[] perm_y;
	delete[] perm_z;
}


void Perlin3::SetDimensions(double u, double v, double scale, double phase)
{
	Width = u;
	Height = v;

	Scale = scale;
	Phase = phase;
}


int* Perlin3::PerlinGeneratePerm()
{
	auto p = new int[point_count];

	for (int i = 0; i < point_count; i++)
	{
		p[i] = i;
	}

	Permute(p, point_count);

	return p;
}


void Perlin3::Permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = static_cast<int>(i * (rand() / (RAND_MAX + 1.0)));
		int tmp = p[i];

		p[i] = p[target];
		p[target] = tmp;
	}
}


double Perlin3::PerlinInterpolation(Quaternion c[2][2][2], double u, double v, double w)
{
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);
	auto accum = 0.0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++) {
				Quaternion weight_v(u - i, v - j, w - k, 0);

				accum += (i * uu + (1 - i) * (1 - uu))
					* (j * vv + (1 - j) * (1 - vv))
					* (k * ww + (1 - k) * (1 - ww))
					* c[i][j][k].Dot(weight_v);
			}
		}
	}

	return accum;
}


double Perlin3::Turbulance(const Quaternion& p)
{
	auto accum = 0.0;
	auto temp_p = p;
	auto weight = 1.0;

	for (int i = 0; i < Depth; i++) 
	{
		accum += weight * Noise(temp_p);
		weight *= 0.5;
		temp_p.Scale(2);
	}

	return std::fabs(accum);
}


double Perlin3::Noise(const Quaternion& p)
{
	auto u = p.x - Fast::Floor(p.x);
	auto v = p.y - Fast::Floor(p.y);
	auto w = p.z - Fast::Floor(p.z);
	auto i = static_cast<int>(Fast::Floor(p.x));
	auto j = static_cast<int>(Fast::Floor(p.y));
	auto k = static_cast<int>(Fast::Floor(p.z));

	Quaternion c[2][2][2];

	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				c[di][dj][dk] = ranvec[
					perm_x[(i + di) & 255] ^
						perm_y[(j + dj) & 255] ^
						perm_z[(k + dk) & 255]
				];
			}
		}
	}

	return PerlinInterpolation(c, u, v, w);
}


Colour Perlin3::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	if (Scale > 1.0)
	{
		pattern_point.Scale(Scale);
	}

	return Colours[0].Mult(0.5 * (1.0 + std::sin(Scale * q.z + Phase * Turbulance(pattern_point)))); // scale * pattern_point
}


std::wstring Perlin3::ToString()
{
	return L"Colour " + Colours[0].ToString() + L", Scale " + std::to_wstring(Scale) + L", Phase " + std::to_wstring(Phase);
}


void Perlin3::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkPerlin3 + L"\n");
	ofile << Formatting::to_utf8(L"colour=" + Colours[0].ToCommaString() + L"\n");
	ofile << Formatting::to_utf8(L"u=" + std::to_wstring(Width) + L"\n");
	ofile << Formatting::to_utf8(L"v=" + std::to_wstring(Height) + L"\n");
	ofile << Formatting::to_utf8(L"phase=" + std::to_wstring(Phase) + L"\n");
	ofile << Formatting::to_utf8(L"scale=" + std::to_wstring(Scale) + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}
}