// PathTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <PathTracer.h>
#include <Color.h>
#include <HittableWorld.h>
#include <Sphere.h>
#include <Camera.h>
#include <Material.h>

using namespace nv;
using namespace nv::math;

Color RayColor(const Ray& ray, const HittableWorld& world, int depth)
{
	HitRecord hit;
	constexpr float epsilon = 0.001f;
	if (depth <= 0)
		return Color(0, 0, 0);

	if (world.Hit(ray, epsilon, infinity, hit))
	{
		Ray scattered;
		Color attenutation;
		if (hit.MaterialPtr->Scatter(ray, hit, attenutation, scattered))
		{
			return attenutation * RayColor(scattered, world, depth - 1);
		}

		return Color(0, 0, 0);
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
	constexpr int maxDepth = 50;

	// Define World
	HittableWorld world;

	auto materialGround = make_shared<Lambertian>(Color(0.8f, 0.8f, 0.1f));
	auto materialCenter = make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));
	auto materialLeft = make_shared<Dielectric>(1.5f);
	auto materialRight = make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 1.f);

	world.Add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100.f, materialGround));
	world.Add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5f, materialCenter));
	world.Add(std::make_shared<Sphere>(Vec3(-1, 0, -1), 0.5f, materialLeft));
	world.Add(std::make_shared<Sphere>(Vec3(-1, 0, -1), -0.4f, materialLeft));
	world.Add(std::make_shared<Sphere>(Vec3(1, 0, -1), 0.5f, materialRight));

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

				pixelColor = pixelColor + RayColor(ray, world, maxDepth);
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
