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

#include "../Twnkl/Triangle.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Tringles

namespace TwnklTestsChapter15
{
	TEST_CLASS(TwnklTestsChapter15)
	{
	public:

		TEST_METHOD(Page208_1)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));

			Assert::IsTrue(tringle.e1.Equals(Quaternion(-1, -1, 0, 0)));
		}

		TEST_METHOD(Page208_2)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));

			Assert::IsTrue(tringle.e2.Equals(Quaternion(1, -1, 0, 0)));
		}

		TEST_METHOD(Page208_3)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));

			Assert::IsTrue(tringle.Normal.Equals(Quaternion(0, 0, -1, 0)));
		}

		TEST_METHOD(Page209_1)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));
		
			Quaternion point(0, 0.5, 0, 1);

			Quaternion normal = tringle.LocalNormalAt(point);

			Assert::IsTrue(tringle.Normal.Equals(normal));
		}

		TEST_METHOD(Page209_2)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));

			Quaternion point(-0.5, 0.75, 0, 1);

			Quaternion normal = tringle.LocalNormalAt(point);

			Assert::IsTrue(tringle.Normal.Equals(normal));
		}

		TEST_METHOD(Page209_3)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));

			Quaternion point(0.5, 0.25, 0, 1);

			Quaternion normal = tringle.LocalNormalAt(point);

			Assert::IsTrue(tringle.Normal.Equals(normal));
		}


		TEST_METHOD(Page211)
		{
			Triangle tringle = Triangle(L"");
			tringle.SetPoints(Quaternion(0, 1, 0, 1), Quaternion(-1, 0, 0, 1), Quaternion(1, 0, 0, 1));

			Ray r = Ray(0, 0.5, -2, 0, 0, 1);

			Intersections i;

			tringle.LocalIntersect(i, r);

			std::wstring s = std::to_wstring(i.List.size());

			Logger::WriteMessage(s.c_str());

			Assert::AreEqual(2.0, i.List[0].Tvalue);
		}


	};
}
