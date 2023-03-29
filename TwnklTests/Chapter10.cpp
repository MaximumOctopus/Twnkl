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

#include "../Twnkl/Sphere.h"
#include "../Twnkl/Pattern.h"
#include "../Twnkl/TestPattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Patterns

namespace TwnklTestsChapter10
{
	TEST_CLASS(TwnklTestsChapter10)
	{
	public:

		TEST_METHOD(Page134_1)
		{
			Sphere* s = new Sphere(L"");
			s->SetTransform(Matrix4(0, 2, 2, 2));
			s->CreateInverseTransform();

			PhongMaterial* p = new PhongMaterial();
			TestPattern* tp = new TestPattern(L"TestPattern");
			p->SetPattern(tp);

			Quaternion qpos(2, 3, 4, 1);

			Colour col = tp->ColourAt(s, qpos);

			Logger::WriteMessage(col.ToString().c_str());

			Assert::IsTrue(col.Equals(Colour(1, 1.5, 2)));
		}

		TEST_METHOD(Page134_2)
		{
			Sphere* s = new Sphere(L"");

			PhongMaterial* p = new PhongMaterial();
			TestPattern* tp = new TestPattern(L"TestPattern");
			tp->SetTransform(Matrix4(0, 2, 2, 2));
			tp->Finalise();
			p->SetPattern(tp);

			Quaternion qpos(2, 3, 4, 1);

			Colour col = tp->ColourAt(s, qpos);

			Logger::WriteMessage(col.ToString().c_str());

			Assert::IsTrue(col.Equals(Colour(1, 1.5, 2)));
		}

		TEST_METHOD(Page134_3)
		{
			Sphere* s = new Sphere(L"");
			s->SetTransform(Matrix4(0, 2, 2, 2));
			s->CreateInverseTransform();

			PhongMaterial* p = new PhongMaterial();
			TestPattern* tp = new TestPattern(L"TestPattern");
			tp->SetTransform(Matrix4(1, 0.5, 1, 1.5));
			tp->Finalise();
			p->SetPattern(tp);

			Quaternion qpos(2.5, 3, 3.5, 1);

			Colour col = tp->ColourAt(s, qpos);

			Logger::WriteMessage(col.ToString().c_str());

			Assert::IsTrue(col.Equals(Colour(0.75, 0.5, 0.25)));
		}

	};
}