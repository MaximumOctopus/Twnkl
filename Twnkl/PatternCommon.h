#pragma once


#include "Quaternion.h"


namespace PatternCommon
{
	std::pair<double, double> CylindricalMap(Quaternion&);
	std::pair<double, double> SphericalMap(Quaternion&);
}