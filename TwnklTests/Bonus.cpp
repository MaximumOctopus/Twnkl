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
#include "../Twnkl/Bounds.h"


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

		TEST_METHOD(BBTransform1)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = -1;
			b->Minimum.y = -1;
			b->Minimum.z = -1;
			
			b->Maximum.x = 1;
			b->Maximum.y = 1;
			b->Maximum.z = 1;

			Matrix4 rx(Matrix4(0, 3.14159 / 4));
			Matrix4 ry(Matrix4(1, 3.14159 / 4));

			Matrix4 m = rx.MultM(ry);

			b->Transform(m);

			Assert::IsTrue(Quaternion(-1.4142, -1.7071, -1.7071, 1).Equals(b->Minimum));
		}

		TEST_METHOD(BBTransform2)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = -1;
			b->Minimum.y = -1;
			b->Minimum.z = -1;

			b->Maximum.x = 1;
			b->Maximum.y = 1;
			b->Maximum.z = 1;

			Matrix4 rx(Matrix4(0, 3.14159 / 4));
			Matrix4 ry(Matrix4(1, 3.14159 / 4));

			Matrix4 m = rx.MultM(ry);

			b->Transform(m);

			Assert::IsTrue(Quaternion(1.4142, 1.7071, 1.7071, 1).Equals(b->Maximum));
		}

		TEST_METHOD(BBIntersectTest1)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(15, 1, 2, -1, 0, 0);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest2)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(-5, -1, 4, 1, 0, 0);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest3)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(7, 6, 5, 0, -1, 0);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest4)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(9, -5, 6, 0, 1, 0);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest5)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(8, 2, 12, 0, 0, -1);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest6)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(6, 0, -5, 0, 0, 1);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest7)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(8, 1, 3.5, 0, 0, 1);

			Assert::IsTrue(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest8)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(9, -1, -8, 2, 4, 6);

			Assert::IsFalse(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest9)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(8, 3, -4, 6, 2, 4);

			Assert::IsFalse(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest10)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(9, -1, -2, 4, 6, 2);

			Assert::IsFalse(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest11)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(4, 0, 9, 0, 0, -1);

			Assert::IsFalse(b->Intersects(r));
		}

		TEST_METHOD(BBIntersectTest12)
		{
			BoundingBox* b = new BoundingBox();

			b->Minimum.x = 5;
			b->Minimum.y = -2;
			b->Minimum.z = 0;

			b->Maximum.x = 11;
			b->Maximum.y = 4;
			b->Maximum.z = 7;

			Ray r = Ray(8, 6, -1, 0, -1, 0);

			Assert::IsFalse(b->Intersects(r));
		}
	};
}