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

#include "Intersect.h"


Intersect::Intersect() noexcept
{

}


Intersect::Intersect(double t, Object* o) noexcept
{
	Tvalue = t;
	PObject = o;
}


Intersect::Intersect(double t, double tri_u, double tri_v, Object* o) noexcept
{
	Tvalue = t;
	PObject = o;

	u = tri_u;
	v = tri_v;
}