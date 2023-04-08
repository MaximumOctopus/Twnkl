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

#include <chrono>
#include <iostream>

#include "Colour.h"
#include "Quaternion.h"
#include "Renderer.h"
#include "World.h"


extern World* GWorld;


Renderer::Renderer()
{

}


Renderer::~Renderer()
{
}


void Renderer::Render(int super_samples)
{
	StartTime = std::chrono::system_clock::now();

	std::wcout << L"\nRendering...\n";	

	if (super_samples == 0)
	{
		Standard();
	}
	else
	{
		SuperSample(super_samples);
	}

	/*
	for (int y = 200; y < 230; y++)
	{
		for (int x = 460; x < 480; x++)
		{
			Ray r = RayForPixel(x, y);

			//GWorld->Canvas[x][y] = ColourAt(r, LightRecursion);

			std::wcout << ColourAt(r, 5).ToString() << L"\n";
		}
	} */
	
	// =================================================================================

	ShowRenderTime();
}


void Renderer::Standard()
{
	for (int y = 0; y < GWorld->Cam->Height; y++)
	{
		for (int x = 0; x < GWorld->Cam->Width; x++)
		{
			Ray r = RayForPixel(x, y);

			GWorld->Canvas[y * GWorld->Cam->Width + x] = ColourAt(r, 5);
		}
	}
}


void Renderer::SuperSample(int super_samples)
{
	double oneoverss = 1.0 / (double)super_samples;

	for (int y = 0; y < GWorld->Cam->Height; y++)
	{
		for (int x = 0; x < GWorld->Cam->Width; x++)
		{
			Colour colour;

			for (int s = 0; s < super_samples; s++)
			{
				auto u = (double)x + (0.5 - (rand() / (RAND_MAX + 1.0)));
				auto v = (double)y + (0.5 - (rand() / (RAND_MAX + 1.0)));

				Ray r = RayForPixelSS(u, v);

				Colour cat(ColourAt(r, 5));

				colour.AddTo(cat);
			}

			GWorld->Canvas[y * GWorld->Cam->Width + x] = Colour(colour.r * oneoverss, colour.g * oneoverss, colour.b * oneoverss);
		}
	}
}


void Renderer::ShowRenderTime()
{
	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = EndTime - StartTime;

	std::wcout << L"\n  Render time         : " << elapsed_seconds.count() << L" seconds \n";

	RenderTime = std::to_wstring(elapsed_seconds.count());
}


// =================================================================================
// == Rays =========================================================================
// =================================================================================


Ray Renderer::RayForPixel(int x, int y)
{
	// the offset from the edge of the canvas to the pixel's center
	double xoffset = ((double)x + 0.5) * GWorld->Cam->PixelSize;
	double yoffset = ((double)y + 0.5) * GWorld->Cam->PixelSize;

	// the untransformed coordinates of the pixel in world space.
	// (remember that the camera looks toward -z, so +x is to the *left*.)
	double world_x = GWorld->Cam->HalfWidth - xoffset;
	double world_y = GWorld->Cam->HalfHeight - yoffset;

	// using the camera matrix, transform the canvas point and the origin,
	// and then compute the ray's direction vector.
	// (remember that the canvas is at z = -1)
	Quaternion qworld(world_x, world_y, -1.0, 1.0);
	Quaternion qzero(0, 0, 0, 1.0);

	Quaternion pixel = GWorld->Cam->InverseTransform.MultQ(qworld);
	Quaternion origin = GWorld->Cam->InverseTransform.MultQ(qzero);

	Quaternion direction = pixel.SubQ(origin);

	direction.Normalise();

	return Ray(origin, direction);
}


Ray Renderer::RayForPixelSS(double x, double y)
{
	// the offset from the edge of the canvas to the pixel's center
	double xoffset = ((double)x + 0.5) * GWorld->Cam->PixelSize;
	double yoffset = ((double)y + 0.5) * GWorld->Cam->PixelSize;

	// the untransformed coordinates of the pixel in world space.
	// (remember that the camera looks toward -z, so +x is to the *left*.)
	double world_x = GWorld->Cam->HalfWidth - xoffset;
	double world_y = GWorld->Cam->HalfHeight - yoffset;

	// using the camera matrix, transform the canvas point and the origin,
	// and then compute the ray's direction vector.
	// (remember that the canvas is at z = -1)
	Quaternion qworld(world_x, world_y, -1.0, 1.0);
	Quaternion qzero(0, 0, 0, 1.0);

	Quaternion pixel = GWorld->Cam->InverseTransform.MultQ(qworld);
	Quaternion origin = GWorld->Cam->InverseTransform.MultQ(qzero);

	Quaternion direction = pixel.SubQ(origin);

	direction.Normalise();

	return Ray(origin, direction);
}


// =================================================================================
// == Lighting =====================================================================
// =================================================================================


Colour Renderer::ReflectedColour(Computation& c, int recursion)
{
	if (GWorld->Objects[c.ObjectID]->Material->Reflectivity < epsilon || recursion <= 0)
	{
		return Colour(0, 0, 0);
	}

	Ray reflect_ray = Ray(c.OverPoint.x, c.OverPoint.y, c.OverPoint.z, c.ReflectVector.x, c.ReflectVector.y, c.ReflectVector.z);

	Colour cat = ColourAt(reflect_ray, recursion - 1);

	cat.Scale(GWorld->Objects[c.ObjectID]->Material->Reflectivity);

	return cat;
}


Colour Renderer::RefractedColour(Computation& c, int recursion)
{
	if (GWorld->Objects[c.ObjectID]->Material->Transparency < epsilon || recursion <= 0)
	{
		return Colour(0, 0, 0);
	}

	double n_ratio = c.N1 / c.N2;

	double cos_i = c.EyeVector.Dot(c.NormalVector);

	double sin2_t = n_ratio * n_ratio * (1.0 - (cos_i * cos_i));

	// total internal reflection
	if (sin2_t > 1.0)
	{
		return Colour(0, 0, 0);
	}

	double cos_t = std::sqrt(1.0 - sin2_t);

	Quaternion direction = Quaternion((c.NormalVector.x * (n_ratio * cos_i - cos_t)) - (c.EyeVector.x * n_ratio),
		(c.NormalVector.y * (n_ratio * cos_i - cos_t)) - (c.EyeVector.y * n_ratio),
		(c.NormalVector.z * (n_ratio * cos_i - cos_t)) - (c.EyeVector.z * n_ratio),
		0);

	Ray refract_ray = Ray(c.UnderPoint.x, c.UnderPoint.y, c.UnderPoint.z, direction.x, direction.y, direction.z);

	const Colour cat = ColourAt(refract_ray, recursion - 1).Mult(GWorld->Objects[c.ObjectID]->Material->Transparency);

	return cat;
}


Colour Renderer::ColourAt(Ray& r, int recursion)
{
	IntersectsWorld(r);

	int i = intersections.LowestNonNegative();

	if (i != -1)
	{
		Computation computation = intersections.PrepareComputation(i, r);

		return ShadeHit(computation, recursion);
	}

	return Colour(0, 0, 0);
}


Colour Renderer::Lighting(Object* o, Light* l, Quaternion& pos, Quaternion& eyev, Quaternion& normalv, double shade_intensity)
{
	Colour MaterialColour;

	if (o->Material->HasPattern)
	{
		MaterialColour = o->Material->SurfacePattern->ColourAt(o, pos);
	}
	else
	{
		MaterialColour = o->Material->SurfaceColour;
	}

	// combine the surface colour with the light's colour/intensity
	Colour effective = Colour(MaterialColour.r * l->Intensity.r, MaterialColour.g * l->Intensity.g, MaterialColour.b * l->Intensity.b);

	// compute the ambient contribution
	Colour ambient = Colour(effective.r * o->Material->Ambient, effective.g * o->Material->Ambient, effective.b * o->Material->Ambient);

	if (shade_intensity < epsilon)
	{
		return ambient;
	}

	Colour total = Colour(0, 0, 0);

	for (int v = 0; v < l->deltav; v++)
	{
		for (int u = 0; u < l->deltau; u++)
		{
			Quaternion p = l->PointOn(u, v);

			Quaternion lightv = p.SubQ(pos);
			lightv.Normalise();
			double light_dot_normal = lightv.Dot(normalv);

			if (light_dot_normal > 0)
			{
				// compute the diffuse contribution
				total.r += effective.r * o->Material->Diffuse * light_dot_normal;
				total.g += effective.g * o->Material->Diffuse * light_dot_normal;
				total.b += effective.b * o->Material->Diffuse * light_dot_normal;

				// reflect_dot_eye represents the cosine of the angle between the
				// reflection vectorand the eye vector.A negative number means the
				// light reflects away from the eye.
				//lightv.Negate();

				Quaternion reflectv = lightv.Reflect(normalv);
				reflectv.Negate();

				double reflect_dot_eye = reflectv.Dot(eyev);

				if (reflect_dot_eye > 0)
				{
					// compute the specular contribution
					double factor = std::pow(reflect_dot_eye, o->Material->Shininess);

					total.r += l->Intensity.r * o->Material->Specular * factor;
					total.g += l->Intensity.g * o->Material->Specular * factor;
					total.b += l->Intensity.b * o->Material->Specular * factor;
				}
			}
		}
	}

	return Colour(ambient.r + (total.r / (double)l->Samples) * shade_intensity,
		ambient.g + (total.g / (double)l->Samples) * shade_intensity,
		ambient.b + (total.b / (double)l->Samples) * shade_intensity);
}


Colour Renderer::ShadeHit(Computation& c, int recursion)
{
	Colour surface = Lighting(GWorld->Objects[c.ObjectID], GWorld->Lights[0], c.OverPoint, c.EyeVector, c.NormalVector, IntensityAt(GWorld->Lights[0], c.OverPoint));

	Colour reflected = ReflectedColour(c, recursion);
	Colour refracted = RefractedColour(c, recursion);

	if (GWorld->Objects[c.ObjectID]->Material->Reflectivity > 0 && GWorld->Objects[c.ObjectID]->Material->Transparency > 0)
	{
		double reflectance = c.Schlick();

		reflected.Scale(reflectance);
		refracted.Scale(1.0 - reflectance);
	}

	return Colour(surface.r + reflected.r + refracted.r,
		surface.g + reflected.g + refracted.g,
		surface.b + reflected.b + refracted.b);
}


bool Renderer::IsShadowed(Quaternion& position, Quaternion& point)
{
	Quaternion v = position.SubQ(point);

	double distance = v.Magnitude();
	Quaternion direction = position.SubQ(point);

	direction.Normalise();

	Ray r = Ray(point.x, point.y, point.z, direction.x, direction.y, direction.z);
	
	IntersectsWorld(r);

	return intersections.LowestNonNegativeLessDistance(distance);
}


double Renderer::IntensityAt(Light* light, Quaternion& point)
{
	if (light->Samples < 2)
	{
		if (IsShadowed(light->Position, point))
		{
			return 0.0;
		}

		return 1.0;
	}

	double total = 0;

	for (int v = 0; v < light->deltav; v++)
	{
		for (int u = 0; u < light->deltau; u++)
		{
			Quaternion p = light->PointOn(u, v);

			if (!IsShadowed(p, point))
			{
				total += 1.0;
			}
		}
	}

	return total / (double)light->Samples;
}


void Renderer::IntersectsWorld(Ray& r)
{
	intersections.List.clear();

	for (int t = 0; t < GWorld->Objects.size(); t++)
	{
		GWorld->Objects[t]->Intersects(intersections, r);
	}

	intersections.Sort();
}