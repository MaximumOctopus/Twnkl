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

#include <algorithm>
#include <iostream>

#include "Intersections.h"


Intersections::Intersections() noexcept
{

}


void Intersections::Sort()
{
	std::ranges::sort(List, {}, &Intersect::Tvalue);
}


// must only be used on a sorted list!
int Intersections::LowestNonNegative()
{	
	for (int t = 0; t < List.size(); t++)	
	{
		if (List[t].Tvalue > 0)
		{
			return t;
		}
	}

	return -1;
}


Computation Intersections::PrepareComputation(int hit_object_id, Ray& r)
{
	//std::wcout << L"PC() List " << ToString() << L"\n";

	Quaternion point = r.Position(List[hit_object_id].Tvalue);

	Quaternion eyev = r.NegativeDirection();

	Quaternion normalvector = List[hit_object_id].PObject->NormalAt(point);

	if (normalvector.Dot(eyev) < 0)
	{
		normalvector.Negate();
	}

	Quaternion normalvector_scaled = Quaternion(normalvector.x, normalvector.y, normalvector.z, 0);
	normalvector_scaled.Scale(epsilon);

	Quaternion overpoint = normalvector_scaled;

	overpoint.Add(point);

	Quaternion underpoint = point.SubQ(normalvector_scaled);

	Quaternion reflectvector = r.Direction.Reflect(normalvector);

	double N1 = 1.0;
	double N2 = 1.0;

	std::vector<int> Container;

	//std::wcout << L"hit : " << hit_object_id << L"\n";

	for (int t = 0; t < List.size(); t++)
	{
		if (hit_object_id == t)
		{
			if (Container.empty())
			{
				N1 = 1.0;
			}
			else
			{
				N1 = List[Container.back()].PObject->Material->RefractiveIndex;
			}
		}

		int found = -1;

		for (int z = 0; z < Container.size(); z++)
		{
			if (List[Container[z]].PObject->ID == List[t].PObject->ID)
			{
				found = z;
			}
		}

		if (found == -1)
		{
			Container.push_back(t);
		}
		else
		{
			Container.erase(Container.begin() + found);
		}

		if (hit_object_id == t)
		{
			if (Container.empty())
			{
				N2 = 1.0;
			}
			else
			{
				N2 = List[Container.back()].PObject->Material->RefractiveIndex;
			}

			break;
		}
	}

	return Computation(List[hit_object_id].Tvalue, List[hit_object_id].PObject->ID, eyev, normalvector, overpoint, underpoint, reflectvector, N1, N2);
}


std::wstring Intersections::ToString()
{
	std::wstring output = L"";

	for (int t = 0; t < List.size(); t++)
	{
		output += L"[" + std::to_wstring(t) + L"] " + std::to_wstring(List[t].PObject->ID) + L" (" + std::to_wstring(List[t].Tvalue) + L") ";
	}

	return output;
}