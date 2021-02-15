// PathTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <PathTracer.h>
#include <Color.h>
#include <HittableWorld.h>
#include <Sphere.h>

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

	// Define World
	HittableWorld world;
	world.Add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5f));
	world.Add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100.f));

	// Camera
	float viewportHeight = 2.f;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.f;

	Vec3 origin = Vec3(0.f, 0.f, 0.f);
	Vec3 horizontal = Vec3(viewportWidth, 0, 0);
	Vec3 vertical = Vec3(0, viewportHeight, 0);
	Vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

	// Render

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto u = float(i) / (imageWidth - 1u);
			auto v = float(j) / (imageHeight - 1u);

			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);

			Color pixelColor = RayColor(ray, world);
			WriteColor(std::cout, pixelColor);
		}
	}

	std::cerr << "\nDone.\n";
}

int main()
{
	RenderImage();
	return 0;
}
