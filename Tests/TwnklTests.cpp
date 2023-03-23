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
#include "../Twnkl/Intersect.h"
#include "../Twnkl/Matrix4.cpp"
#include "../Twnkl/Object.cpp"
#include "../Twnkl/Quaternion.cpp"
#include "../Twnkl/Ray.cpp"
#include "../Twnkl/Sphere.cpp"
#include "../Twnkl/Sphere.h"
#include "../Twnkl/Pattern.cpp"
#include "../Twnkl/TestPattern.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TwnklTestsMatrix
{
	// a set of tests for the quaternion and matrix classes

	TEST_CLASS(TwnklTests)
	{
	public:
		
		TEST_METHOD(Matrix4x4Determinant)
		{
			Matrix4 m = Matrix4(8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4);

			Assert::AreEqual(m.Determinant(), -585.0);

				//std::wcout << L"d = " << m.Determinant() << L"\n"; // -585

				//m.Invert();

				//std::wcout << L"0,0 " << m.Data[0][0] << L"\n"; // ~0.153846
				//std::wcout << L"3,3 " << m.Data[3][3] << L"\n"; // -1.92308
		};

		TEST_METHOD(Matrix4x4ShearingXZ)
		{
			Matrix4 m = Matrix4(0, 1, 0, 0, 0, 0);

			Quaternion p = Quaternion(2, 3, 4, 1);

			Quaternion t = m.MultQ(p);

			Assert::AreEqual(t.x, 6.0);
		}

		TEST_METHOD(Matrix4x4ShearingYX)
		{
			Matrix4 m = Matrix4(0, 0, 1, 0, 0, 0);

			Quaternion p = Quaternion(2, 3, 4, 1);

			Quaternion t = m.MultQ(p);

			Assert::AreEqual(t.y, 5.0);
		}

		TEST_METHOD(Matrix4x4ShearingYZ)
		{
			Matrix4 m = Matrix4(0, 0, 0, 1, 0, 0);

			Quaternion p = Quaternion(2, 3, 4, 1);

			Quaternion t = m.MultQ(p);

			Assert::AreEqual(t.y, 7.0);
		}

		TEST_METHOD(Matrix4x4ShearingZX)
		{
			Matrix4 m = Matrix4(0, 0, 0, 0, 1, 0);

			Quaternion p = Quaternion(2, 3, 4, 1);

			Quaternion t = m.MultQ(p);

			Assert::AreEqual(t.z, 6.0);
		}

		TEST_METHOD(Matrix4x4ShearingZY)
		{
			Matrix4 m = Matrix4(0, 0, 0, 0, 0, 1);

			Quaternion p = Quaternion(2, 3, 4, 1);

			Quaternion t = m.MultQ(p);

			Assert::AreEqual(t.z, 7.0);
		}

		TEST_METHOD(QuaternionAdd)
		{
			Quaternion q = Quaternion(5, 10, 15, 20);

			q.Add(Quaternion(3, 4, -5, 10));

			Assert::IsTrue(q.Equals(Quaternion(8, 14, 10, 30)));
		}

		TEST_METHOD(QuaternionSub)
		{
			Quaternion q = Quaternion(5, 10, 15, 20);

			q.Sub(Quaternion(3, 4, -5, 10));

			Assert::IsTrue(q.Equals(Quaternion(2, 6, 20, 10)));
		}

		TEST_METHOD(QuaternionScale)
		{
			Quaternion q = Quaternion(5, 10, 15, 20);

			q.Scale(5);

			Assert::IsTrue(q.Equals(Quaternion(25, 50, 75, 100)));
		}

		TEST_METHOD(QuaternionScale2)
		{
			Quaternion q = Quaternion(5, 10, 15, 20);

			q.Scale(-2);

			Assert::IsTrue(q.Equals(Quaternion(-10, -20, -30, -40)));
		}

		TEST_METHOD(Page80_1)
		{
			Sphere o = Sphere(L"");

			o.SetTransform(Matrix4(1, 0, 1, 0));

			o.CreateInverseTransform();

			Quaternion n = Quaternion(0, 1.70711, -0.70711, 1);

			Quaternion q = o.NormalAt(n);

			Assert::IsTrue(q.Equals(Quaternion(0, 0.70711, -0.70711, 0)));
		}

		TEST_METHOD(Page80_2)
		{
			Sphere o = Sphere(L"");

			Matrix4 m = Matrix4(0, 1.0, 0.5, 1.0);

			o.SetTransform(m.MultM(Matrix4(2, 0.6283185307)));

			o.CreateInverseTransform();

			Quaternion l = Quaternion(0, 0.7071067, -0.7071067, 1.0);

			Quaternion q = o.NormalAt(l);

			Assert::IsTrue(q.Equals(Quaternion(0, 0.97014, -0.24254, 0)));
		}

		TEST_METHOD(Page83_1)
		{
			Quaternion v = Quaternion(1, -1, 0, 0);
			Quaternion n = Quaternion(0, 1, 0, 0);

			Quaternion r = v.Reflect(n);

			Assert::IsTrue(r.Equals(Quaternion(1, 1, 0, 0)));
		}


		TEST_METHOD(Page83_2)
		{
			Quaternion v = Quaternion(0, -1, 0, 0);
			Quaternion n = Quaternion(sqrt(2) / 2, sqrt(2) / 2, 0, 0);

			Quaternion r = v.Reflect(n);

			Assert::IsTrue(r.Equals(Quaternion(1, 0, 0, 0)));
		}
	};
}
