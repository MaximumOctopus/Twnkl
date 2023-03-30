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
#include "Perlin.h"


Perlin::Perlin(std::wstring name) : Pattern(name)
{
	Name = name;

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


Perlin::~Perlin()
{
	delete[] ranvec;
	delete[] perm_x;
	delete[] perm_y;
	delete[] perm_z;
}


void Perlin::SetDimensions(double u, double v, double scale)
{
	Width = u;
	Height = v;

	Scale = scale;
}


int* Perlin::PerlinGeneratePerm() 
{
	auto p = new int[point_count];
	for (int i = 0; i < point_count; i++)
	{
		p[i] = i;
	}

	Permute(p, point_count);
	
	return p;
}


void Perlin::Permute(int* p, int n) 
{
	for (int i = n - 1; i > 0; i--) 
	{
		int target = static_cast<int>(i * (rand() / (RAND_MAX + 1.0)));
		int tmp = p[i];

		p[i] = p[target];
		p[target] = tmp;
	}
}


double Perlin::PerlinInterpolation(Quaternion c[2][2][2], double u, double v, double w)
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


double Perlin::Noise(const Quaternion& p)
{
	auto u = p.x - floor(p.x);
	auto v = p.y - floor(p.y);
	auto w = p.z - floor(p.z);
	auto i = static_cast<int>(floor(p.x));
	auto j = static_cast<int>(floor(p.y));
	auto k = static_cast<int>(floor(p.z));

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


Colour Perlin::ColourAt(Object* o, Quaternion& q)
{
	Quaternion object_point = o->InverseTransform.MultQ(q);
	Quaternion pattern_point = InverseTransform.MultQ(object_point);

	if (Scale > 1.0)
	{
		pattern_point.Scale(Scale);
	}

	return Colours[0].Mult(0.5 * (1.0 + Noise(pattern_point))); // scale * pattern_point
}


std::wstring Perlin::ToString()
{
	return L"Colour " + Colours[0].ToString() + L", Scale " + std::to_wstring(Scale);
}