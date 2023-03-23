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

#include "../Twnkl/Renderer.h"
#include "../Twnkl/Sphere.h"
#include "../Twnkl/World.h"

extern World* GWorld;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Shadows

namespace TwnklTestsChapter8
{
	TEST_CLASS(TwnklTestsChapter8)
	{
	public:

		TEST_METHOD(Page112_1)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(0);

			Renderer* rx = new Renderer();

			Quaternion q = Quaternion(10, -10, 10, 1);

			Assert::IsTrue(rx->IsShadowed(q));
		}

		TEST_METHOD(Page112_2)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(0);

			Renderer* rx = new Renderer();

			Quaternion q = Quaternion(-20, 20, -20, 1);

			Assert::IsFalse(rx->IsShadowed(q));
		}

		TEST_METHOD(Page115)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			// default glass sphere
			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			s1->Material = m1;

			s1->SetTransform(Matrix4(1, 0, 0, 1));
			s1->CreateInverseTransform();

			GWorld->Objects.push_back(s1);

			Intersections i;

			i.List.push_back(Intersect(5, GWorld->Objects[0]));

			Ray r = Ray(0, 0, -5, 0, 0, 1);

			Computation c = i.PrepareComputation(0, r);

			Assert::IsTrue(c.OverPoint.z < (0.0001 / 2) && c.Point.z > c.OverPoint.z);
		}

	};
}