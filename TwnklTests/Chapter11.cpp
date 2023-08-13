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

#include "../Twnkl/Formatting.cpp"

#include "../Twnkl/Cone.cpp"
#include "../Twnkl/Cube.cpp"
#include "../Twnkl/Cylinder.cpp"
#include "../Twnkl/Model.cpp"
#include "../Twnkl/Plane.cpp"
#include "../Twnkl/Sphere.cpp"

#include "../Twnkl/Bounds.cpp"
#include "../Twnkl/Trinion.cpp"

#include "../Twnkl/Camera.cpp"
#include "../Twnkl/Computation.cpp"
#include "../Twnkl/Colour.cpp"
#include "../Twnkl/Intersect.cpp"
#include "../Twnkl/Intersections.cpp"
#include "../Twnkl/Light.cpp"
#include "../Twnkl/PointLight.cpp"
#include "../Twnkl/PhongMaterial.cpp"
#include "../Twnkl/Renderer.cpp"
#include "../Twnkl/World.cpp"

#include "../Twnkl/Checkerboard.cpp"
#include "../Twnkl/CubeCheckerboard.cpp"
#include "../Twnkl/CubeTexture.cpp"
#include "../Twnkl/CubeMultiTexture.cpp"
#include "../Twnkl/CylinderCheckerboard.cpp"
#include "../Twnkl/CylinderTexture.cpp"
#include "../Twnkl/Fractal.cpp"
#include "../Twnkl/Gradient.cpp"
#include "../Twnkl/Gradient2.cpp"
#include "../Twnkl/Noise.cpp"
#include "../Twnkl/PatternCommon.cpp"
#include "../Twnkl/Perlin.cpp"
#include "../Twnkl/Perlin2.cpp"
#include "../Twnkl/Perlin3.cpp"
#include "../Twnkl/PlanarTexture.cpp"
#include "../Twnkl/Ring.cpp"
#include "../Twnkl/Simplex.cpp"
#include "../Twnkl/SphericalCheckerboard.cpp"
#include "../Twnkl/SphericalTexture.cpp"
#include "../Twnkl/Stripey.cpp"

#include "../Twnkl/TextureLoader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Reflections and Refractions

namespace TwnklTestsChapter11
{
	TEST_CLASS(TwnklTestsChapter11)
	{
	public:

		TEST_METHOD(Page143)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Plane* p = new Plane(L"");
			PhongMaterial* m = new PhongMaterial();
			p->Material = m;

			p->CreateInverseTransform();

			GWorld->Objects.push_back(p);

			Ray r = Ray(0, 1, -1, 0, -sqrt(2) / 2, sqrt(2) / 2);

			Intersections i;

			i.List.push_back(Intersect(sqrt(2), GWorld->Objects[0]));

			Computation c = i.PrepareComputation(0, r);

			Quaternion expected(0, sqrt(2) / 2, sqrt(2) / 2, 0);

			Assert::IsTrue(c.ReflectVector.Equals(expected));
		}

		TEST_METHOD(Page144_1)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(144);

			Ray r = Ray(0, 0, 0, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(1, GWorld->Objects[1]));

			Computation c = i.PrepareComputation(0, r);

			Renderer rx = Renderer();

			Colour col = rx.ReflectedColour(c, 5);

			Assert::IsTrue(col.Equals(Colour(0, 0, 0)));
		}

		TEST_METHOD(Page144_2)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(0);

			Plane* p = new Plane(L"");
			PhongMaterial* m = new PhongMaterial();
			m->Reflectivity = 0.5;

			p->Material = m;
			p->Transform = Matrix4(1, 0, -1, 0);

			p->CreateInverseTransform();
			p->ID = 2;

			GWorld->Objects.push_back(p);

			Ray r = Ray(0, 0, -3, 0, -sqrt(2) / 2, sqrt(2) / 2);

			Intersections i;

			i.List.push_back(Intersect(sqrt(2), GWorld->Objects[2]));

			Computation c = i.PrepareComputation(0, r);

			Renderer rx = Renderer();

			Colour col = rx.ReflectedColour(c, 5);

			Logger::WriteMessage(col.ToString().c_str());

			delete GWorld;

			Assert::IsTrue(col.Equals(Colour(0.19032, 0.2379, 0.14274)));
		}

		TEST_METHOD(Page145)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(0);

			Plane* p = new Plane(L"");
			PhongMaterial* m = new PhongMaterial();
			m->Reflectivity = 0.5;

			p->Material = m;
			p->Transform = Matrix4(1, 0, -1, 0);

			p->CreateInverseTransform();
			p->ID = 2;

			GWorld->Objects.push_back(p);

			Ray r = Ray(0, 0, -3, 0, -sqrt(2) / 2, sqrt(2) / 2);

			Intersections i;

			i.List.push_back(Intersect(sqrt(2), GWorld->Objects[2]));

			Computation c = i.PrepareComputation(0, r);

			Renderer rx = Renderer();

			Colour col = rx.ShadeHit(c, 5);

			Logger::WriteMessage(col.ToString().c_str());

			delete GWorld;

			Assert::IsTrue(col.Equals(Colour(0.87677, 0.92436, 0.82918)));
		}

		TEST_METHOD(Page147)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(0);

			Plane* p = new Plane(L"");
			PhongMaterial* m = new PhongMaterial();
			m->Reflectivity = 0.5;

			p->Material = m;
			p->Transform = Matrix4(1, 0, -1, 0);

			p->CreateInverseTransform();
			p->ID = 2;

			GWorld->Objects.push_back(p);

			Ray r = Ray(0, 0, -3, 0, -sqrt(2) / 2, sqrt(2) / 2);

			Intersections i;

			i.List.push_back(Intersect(sqrt(2), GWorld->Objects[2]));

			Computation c = i.PrepareComputation(0, r);

			Renderer rx = Renderer();

			Colour col = rx.ReflectedColour(c, 0);

			Logger::WriteMessage(col.ToString().c_str());

			Assert::IsTrue(col.Equals(Colour(0, 0, 0)));
		}

		TEST_METHOD(Page152_1)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->Transform = Matrix4(0, 2, 2, 2);

			GWorld->Objects.push_back(s1);
			
			Sphere* s2 = new Sphere(L"");
			PhongMaterial* m2 = new PhongMaterial();
			m2->Transparency = 1.0;
			m2->RefractiveIndex = 2.0;
			s2->Material = m2;

			s2->Transform = Matrix4(1, 0, 0, -0.25);

			GWorld->Objects.push_back(s2);

			Sphere* s3 = new Sphere(L"");
			PhongMaterial* m3 = new PhongMaterial();
			m3->Transparency = 1.0;
			m3->RefractiveIndex = 2.5;
			s3->Material = m3;

			s3->Transform = Matrix4(1, 0, 0, 0.25);

			GWorld->Objects.push_back(s3);

			GWorld->Finalise();

			Ray r = Ray(0, 0, -4, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(2, GWorld->Objects[0]));
			i.List.push_back(Intersect(2.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(3.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(4.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(5.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(0, r);

			//Logger::WriteMessage();

			delete GWorld;

			Assert::IsTrue(c.N1 == 1.0 && c.N2 == 1.5);
		}

		TEST_METHOD(Page152_2)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->Transform = Matrix4(0, 2, 2, 2);

			GWorld->Objects.push_back(s1);

			Sphere* s2 = new Sphere(L"");
			PhongMaterial* m2 = new PhongMaterial();
			m2->Transparency = 1.0;
			m2->RefractiveIndex = 2.0;
			s2->Material = m2;

			s2->Transform = Matrix4(1, 0, 0, -0.25);

			GWorld->Objects.push_back(s2);

			Sphere* s3 = new Sphere(L"");
			PhongMaterial* m3 = new PhongMaterial();
			m3->Transparency = 1.0;
			m3->RefractiveIndex = 2.5;
			s3->Material = m3;

			s3->Transform = Matrix4(1, 0, 0, 0.25);

			GWorld->Objects.push_back(s3);

			GWorld->Finalise();

			Ray r = Ray(0, 0, -4, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(2, GWorld->Objects[0]));
			i.List.push_back(Intersect(2.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(3.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(4.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(5.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(1, r);

			//Logger::WriteMessage();

			delete GWorld;

			Assert::IsTrue(c.N1 == 1.5 && c.N2 == 2.0);
		}

		TEST_METHOD(Page152_3)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->Transform = Matrix4(0, 2, 2, 2);

			GWorld->Objects.push_back(s1);

			Sphere* s2 = new Sphere(L"");
			PhongMaterial* m2 = new PhongMaterial();
			m2->Transparency = 1.0;
			m2->RefractiveIndex = 2.0;
			s2->Material = m2;

			s2->Transform = Matrix4(1, 0, 0, -0.25);

			GWorld->Objects.push_back(s2);

			Sphere* s3 = new Sphere(L"");
			PhongMaterial* m3 = new PhongMaterial();
			m3->Transparency = 1.0;
			m3->RefractiveIndex = 2.5;
			s3->Material = m3;

			s3->Transform = Matrix4(1, 0, 0, 0.25);

			GWorld->Objects.push_back(s3);

			GWorld->Finalise();

			Ray r = Ray(0, 0, -4, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(2, GWorld->Objects[0]));
			i.List.push_back(Intersect(2.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(3.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(4.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(5.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(2, r);

			//Logger::WriteMessage();

			delete GWorld;

			Assert::IsTrue(c.N1 == 2.0 && c.N2 == 2.5);
		}

		TEST_METHOD(Page152_4)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->Transform = Matrix4(0, 2, 2, 2);

			GWorld->Objects.push_back(s1);

			Sphere* s2 = new Sphere(L"");
			PhongMaterial* m2 = new PhongMaterial();
			m2->Transparency = 1.0;
			m2->RefractiveIndex = 2.0;
			s2->Material = m2;

			s2->Transform = Matrix4(1, 0, 0, -0.25);

			GWorld->Objects.push_back(s2);

			Sphere* s3 = new Sphere(L"");
			PhongMaterial* m3 = new PhongMaterial();
			m3->Transparency = 1.0;
			m3->RefractiveIndex = 2.5;
			s3->Material = m3;

			s3->Transform = Matrix4(1, 0, 0, 0.25);

			GWorld->Objects.push_back(s3);

			GWorld->Finalise();

			Ray r = Ray(0, 0, -4, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(2, GWorld->Objects[0]));
			i.List.push_back(Intersect(2.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(3.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(4.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(5.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(3, r);

			//Logger::WriteMessage();

			delete GWorld;

			Assert::IsTrue(c.N1 == 2.5 && c.N2 == 2.5);
		}

		TEST_METHOD(Page152_5)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->Transform = Matrix4(0, 2, 2, 2);

			GWorld->Objects.push_back(s1);

			Sphere* s2 = new Sphere(L"");
			PhongMaterial* m2 = new PhongMaterial();
			m2->Transparency = 1.0;
			m2->RefractiveIndex = 2.0;
			s2->Material = m2;

			s2->Transform = Matrix4(1, 0, 0, -0.25);

			GWorld->Objects.push_back(s2);

			Sphere* s3 = new Sphere(L"");
			PhongMaterial* m3 = new PhongMaterial();
			m3->Transparency = 1.0;
			m3->RefractiveIndex = 2.5;
			s3->Material = m3;

			s3->Transform = Matrix4(1, 0, 0, 0.25);

			GWorld->Objects.push_back(s3);

			GWorld->Finalise();

			Ray r = Ray(0, 0, -4, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(2, GWorld->Objects[0]));
			i.List.push_back(Intersect(2.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(3.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(4.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(5.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(4, r);

			//Logger::WriteMessage();

			delete GWorld;

			Assert::IsTrue(c.N1 == 2.5 && c.N2 == 1.5);
		}

		TEST_METHOD(Page152_6)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->Transform = Matrix4(0, 2, 2, 2);

			GWorld->Objects.push_back(s1);

			Sphere* s2 = new Sphere(L"");
			PhongMaterial* m2 = new PhongMaterial();
			m2->Transparency = 1.0;
			m2->RefractiveIndex = 2.0;
			s2->Material = m2;

			s2->Transform = Matrix4(1, 0, 0, -0.25);

			GWorld->Objects.push_back(s2);

			Sphere* s3 = new Sphere(L"");
			PhongMaterial* m3 = new PhongMaterial();
			m3->Transparency = 1.0;
			m3->RefractiveIndex = 2.5;
			s3->Material = m3;

			s3->Transform = Matrix4(1, 0, 0, 0.25);

			GWorld->Objects.push_back(s3);

			GWorld->Finalise();

			Ray r = Ray(0, 0, -4, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(2, GWorld->Objects[0]));
			i.List.push_back(Intersect(2.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(3.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(4.75, GWorld->Objects[1]));
			i.List.push_back(Intersect(5.25, GWorld->Objects[2]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(5, r);

			//Logger::WriteMessage();

			delete GWorld;

			Assert::IsTrue(c.N1 == 1.5 && c.N2 == 1.0);
		}

		TEST_METHOD(Page154)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			// default glass sphere
			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			s1->AddTransform({ TransformType::Translate, Matrix4(1, 0, 0, 1), Quaternion(), 0 });
			s1->ProcessTransforms();

			GWorld->Objects.push_back(s1);

			Intersections i;

			i.List.push_back(Intersect(5, GWorld->Objects[0]));

			Ray r = Ray(0, 0, -5, 0, 0, 1);

			Computation c = i.PrepareComputation(0, r);

			Assert::IsTrue(c.UnderPoint.z > (0.0001 / 2) && c.OverPoint.z < c.UnderPoint.z);
		}

		TEST_METHOD(Page155)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(0);

			Intersections i;

			i.List.push_back(Intersect(4, GWorld->Objects[0]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Ray r = Ray(0, 0, -5, 0, 0, 1);

			Computation c = i.PrepareComputation(0, r);

			Renderer rx = Renderer();
			Colour col = rx.RefractedColour(c, 5);

			Assert::IsTrue(col.Equals(Colour(0, 0, 0)));
		}

		TEST_METHOD(Page156)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(156);

			Intersections i;

			i.List.push_back(Intersect(4, GWorld->Objects[0]));
			i.List.push_back(Intersect(6, GWorld->Objects[0]));

			Ray r = Ray(0, 0, -5, 0, 0, 1);

			Computation c = i.PrepareComputation(0, r);

			Renderer rx = Renderer();
			Colour col = rx.RefractedColour(c, 0);

			Assert::IsTrue(col.Equals(Colour(0, 0, 0)));
		}

		TEST_METHOD(Page157)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(156); // 156 is correct, it uses the same modifications as 156

			Intersections i;

			i.List.push_back(Intersect(-sqrt(2) / 2, GWorld->Objects[0]));
			i.List.push_back(Intersect(sqrt(2) / 2, GWorld->Objects[0]));

			Ray r = Ray(0, 0, sqrt(2) / 2, 0, 1, 0);

			Computation c = i.PrepareComputation(1, r);

			Renderer rx = Renderer();
			Colour col = rx.RefractedColour(c, 5);

			Assert::IsTrue(col.Equals(Colour(0, 0, 0)));
		}

		TEST_METHOD(Page158)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(158); 

			Intersections i;

			i.List.push_back(Intersect(-0.9899, GWorld->Objects[0]));
			i.List.push_back(Intersect(-0.4899, GWorld->Objects[1]));
			i.List.push_back(Intersect(0.4899, GWorld->Objects[1]));
			i.List.push_back(Intersect(0.9899, GWorld->Objects[0]));

			Ray r = Ray(0, 0, 0.1, 0, 1, 0);

			Computation c = i.PrepareComputation(2, r);

			Renderer rx = Renderer();
			Colour col = rx.RefractedColour(c, 5);

			Logger::WriteMessage(col.ToString().c_str());

			delete GWorld;

			Assert::IsTrue(col.Equals(Colour(0, 0.99888, 0.04725)));
		}

		TEST_METHOD(Page159)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(159);
	
			Renderer rx = Renderer();

			Ray r = Ray(0, 0, -3, 0, -sqrt(2) / 2, sqrt(2) / 2);

			Intersections i;

			i.List.push_back(Intersect(sqrt(2), GWorld->Objects[2]));

			Computation c = i.PrepareComputation(0, r);

			Colour col = rx.ShadeHit(c, 5);		

			Logger::WriteMessage(col.ToString().c_str());

			delete GWorld;

			Assert::IsTrue(col.Equals(Colour(0.93642, 0.68642, 0.68642)));
		}

		TEST_METHOD(Page161)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			// default glass sphere
			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			GWorld->Objects.push_back(s1);

			Ray r = Ray(0, 0, sqrt(2) / 2, 0, 1, 0);

			Intersections i;

			i.List.push_back(Intersect(-sqrt(2) / 2, GWorld->Objects[0]));
			i.List.push_back(Intersect(sqrt(2) / 2, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(1, r);

			delete GWorld;

			Assert::AreEqual(c.Schlick(), 1.0);
		}

		TEST_METHOD(Page162)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			// default glass sphere
			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			GWorld->Objects.push_back(s1);

			Ray r = Ray(0, 0,0, 0, 1, 0);

			Intersections i;

			i.List.push_back(Intersect(-1, GWorld->Objects[0]));
			i.List.push_back(Intersect(1, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(1, r);

			delete GWorld;

			Assert::AreEqual(0.040, c.Schlick());
		}

		TEST_METHOD(Page163)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			// default glass sphere
			Sphere* s1 = new Sphere(L"");
			PhongMaterial* m1 = new PhongMaterial();
			m1->Transparency = 1.0;
			m1->RefractiveIndex = 1.5;
			s1->Material = m1;

			GWorld->Objects.push_back(s1);

			Ray r = Ray(0, 0.99, -2, 0, 0, 1);

			Intersections i;

			i.List.push_back(Intersect(1.8589, GWorld->Objects[0]));

			Computation c = i.PrepareComputation(0, r);

			Logger::WriteMessage(std::to_string(c.Schlick()).c_str());

			delete GWorld;

			Assert::AreEqual(0.488731, c.Schlick());
		}

		TEST_METHOD(Page164)
		{
			GWorld = new World(640, 320, 3.14159265358979311600 / 3.0);

			GWorld->DefaultWorld(164);

			Renderer rx = Renderer();

			Ray r = Ray(0, 0, -3, 0, -sqrt(2) / 2, sqrt(2) / 2);

			Intersections i;

			i.List.push_back(Intersect(sqrt(2), GWorld->Objects[2]));

			Computation c = i.PrepareComputation(0, r);

			Colour col = rx.ShadeHit(c, 5);

			Logger::WriteMessage(col.ToString().c_str());

			delete GWorld;

			Assert::IsTrue(col.Equals(Colour(0.93391, 0.69643, 0.69243)));
		}

	};
}