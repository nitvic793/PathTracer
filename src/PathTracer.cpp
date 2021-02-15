// PathTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <PathTracer.h>
#include <Color.h>
#include <HittableWorld.h>
#include <Sphere.h>
#include <Camera.h>

using namespace nv;
using namespace nv::math;

float HitSphere(const Vec3& center, float radius, const Ray& ray)
{
	Vec3 oc = ray.origin - center;
	float a = ray.Direction().LengthSquared();
	float halfB = Dot(oc, ray.dir);
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = halfB * halfB - a * c;
	if (discriminant < 0)
	{
		return -1.f;
	}
	else
	{
		return (-halfB - sqrt(discriminant)) / a;
	}
}

Color RayColor(const Ray& ray, const HittableWorld& world)
{
	HitRecord hit;
	if (world.Hit(ray, 0, infinity, hit))
	{
		return 0.5f * (hit.Normal + Color(1, 1, 1));
	}

	Vec3 unitDirection = UnitVector(ray.Direction());
	float t = 0.5f * (unitDirection.y + 1.f);
	return Lerp(Color(1.f, 1.f, 1.f), Color(0.5f, 0.7f, 1.f), t);
}

void RenderImage()
{
	// Image
	constexpr float aspectRatio = 16.f / 9.f;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = (int)(imageWidth / aspectRatio);
	constexpr int samplesPerPixel = 100;

	// Define World
	HittableWorld world;
	world.Add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5f));
	world.Add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100.f));

	// Camera
	Camera camera;

	// Render

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			Color pixelColor(0, 0, 0);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				auto u = (float(i) + Random()) / (imageWidth - 1u);
				auto v = (float(j) + Random()) / (imageHeight - 1u);

				Ray ray = camera.GetRay(u, v);

				pixelColor = pixelColor + RayColor(ray, world);
			}

			WriteColor(std::cout, pixelColor, samplesPerPixel);
		}
	}

	std::cerr << "\nDone.\n";
}

int main()
{
	RenderImage();
	return 0;
}
