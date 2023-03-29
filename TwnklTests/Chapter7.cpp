//
// Twnkl 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
// 
// https://github.com/MaximumOctopus/Twnkl
// 

#include "pch.h"
#include "CppUnitTest.h"

#include "../Twnkl/Computation.h"
#include "../Twnkl/Renderer.h"
#include "../Twnkl/Sphere.h"
#include "../Twnkl/World.h"

extern World* GWorld;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Shadows

namespace TwnklTestsChapter7
{
	TEST_CLASS(TwnklTestsChapter7)
	{
	public:

		TEST_METHOD(Page93)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* p = new PhongMaterial();
			s1->Material = p;
			s1->CreateInverseTransform();
			GWorld->Objects.push_back(s1);

			Ray r = Ray(0, 0, -5, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(4, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(0, r);

			std::wstring output = c.EyeVector.ToString() + L" " + c.NormalVector.ToString();

			Logger::WriteMessage(output.c_str());

			Assert::IsTrue(Quaternion(0, 0, -1, 1).Equals(c.OverPoint));  // should be point (optimised-out)
		}

		TEST_METHOD(Page95)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* p = new PhongMaterial();
			s1->Material = p;
			s1->CreateInverseTransform();
			GWorld->Objects.push_back(s1);

			Ray r = Ray(0, 0, 0, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(1, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(0, r);

			std::wstring output = c.EyeVector.ToString() + L" " + c.OverPoint.ToString(); // should be point (optimised-out)

			Logger::WriteMessage(output.c_str());

			Assert::IsTrue(Quaternion(0, 0, -1, 0).Equals(c.NormalVector));
		}


	};
}