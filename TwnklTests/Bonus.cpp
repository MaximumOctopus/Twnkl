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

#include "../Twnkl/AreaLight.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Shadows

namespace TwnklTestsBonus
{
	TEST_CLASS(TwnklTestsBonus)
	{
	public:

		// IMPORTANT: SSPoL tests will need the jitter removing from PointOn before these will pass!!!
		// replace random jitter with 0.5 (and the ability to set separate u and v deltas!)

		TEST_METHOD(SSPoL1)
		{
			AreaLight* l = new AreaLight(L"arealight", 1, 1, 1, 0, 0, 0);
			l->uvec = Quaternion(2, 0, 0, 0);
			l->vvec = Quaternion(0, 0, 1, 0);

			Quaternion pt = l->PointOn(0, 0);

			Logger::WriteMessage(pt.ToString().c_str());

			Assert::IsTrue(Quaternion(0.25, 0, 0.25, 1).Equals(pt)); 
		}

		TEST_METHOD(SSPoL2)
		{
			AreaLight* l = new AreaLight(L"arealight", 1, 1, 1, 0, 0, 0);
			l->uvec = Quaternion(2, 0, 0, 0);
			l->vvec = Quaternion(0, 0, 1, 0);

			Quaternion pt = l->PointOn(1, 0);

			Logger::WriteMessage(pt.ToString().c_str());

			Assert::IsTrue(Quaternion(0.75, 0, 7.25, 1).Equals(pt));  
		}

		TEST_METHOD(SSPoL3)
		{
			AreaLight* l = new AreaLight(L"arealight", 1, 1, 1, 0, 0, 0);
			l->uvec = Quaternion(2, 0, 0, 0);
			l->vvec = Quaternion(0, 0, 1, 0);

			Quaternion pt = l->PointOn(0, 1);

			Logger::WriteMessage(pt.ToString().c_str());

			Assert::IsTrue(Quaternion(0.25, 0, 0.75, 1).Equals(pt));
		}

		TEST_METHOD(SSPoL4)
		{
			AreaLight* l = new AreaLight(L"arealight", 1, 1, 1, 0, 0, 0);
			l->uvec = Quaternion(2, 0, 0, 0);
			l->vvec = Quaternion(0, 0, 1, 0);

			Quaternion pt = l->PointOn(2, 0);

			Logger::WriteMessage(pt.ToString().c_str());

			Assert::IsTrue(Quaternion(1.25, 0, 0.25, 1).Equals(pt));
		}

		TEST_METHOD(SSPoL5)
		{
			AreaLight* l = new AreaLight(L"arealight", 1, 1, 1, 0, 0, 0);
			l->uvec = Quaternion(2, 0, 0, 0);
			l->vvec = Quaternion(0, 0, 1, 0);

			Quaternion pt = l->PointOn(3, 0);

			Logger::WriteMessage(pt.ToString().c_str());

			Assert::IsTrue(Quaternion(1.75, 0, 0.75, 1).Equals(pt));
		}
	};
}