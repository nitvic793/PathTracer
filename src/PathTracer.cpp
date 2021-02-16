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

HittableWorld GenerateRandomScene()
{
	HittableWorld world;

	auto materialGround = make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
	world.Add(std::make_shared<Sphere>(Vec3(0, -1000, -1), 1000.f, materialGround));

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			float chooseMat = Random();
			Vec3 center(a + 0.9f * Random(), 0.2f, b + 0.9f * Random());

			if ((center - Vec3(4.f, 0.2f, 0.f)).Length() > 0.9f)
			{
				shared_ptr<Material> sphereMaterial;

				if (chooseMat < 0.8f)
				{
					Color albedo = Color::Random() * Color::Random();
					sphereMaterial = make_shared<Lambertian>(albedo);
					world.Add(make_shared<Sphere>(center, 0.2f, sphereMaterial));
				}
				else if (chooseMat < 0.95)
				{
					Color albedo = Color::Random(0.5f, 1.f);
					float roughness = Random(0, 0.5f);
					sphereMaterial = make_shared<Metal>(albedo, roughness);
					world.Add(make_shared<Sphere>(center, 0.2f, sphereMaterial));
				}
				else
				{
					sphereMaterial = make_shared<Dielectric>(1.5f);
					world.Add(make_shared<Sphere>(center, 0.2f, sphereMaterial));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5f);
	world.Add(make_shared<Sphere>(Vec3(0, 1, 0), 1.f, material1));

	auto material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
	world.Add(make_shared<Sphere>(Vec3(-4, 1, 0), 1.f, material2));

	auto material3 = make_shared<Metal>(Vec3(0.7f, 0.6f, 0.5f), 0.f);
	world.Add(make_shared<Sphere>(Vec3(4, 1, 0), 1.f, material3));

	return world;
}

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

	//  World
	HittableWorld world = GenerateRandomScene();

	// Camera
	Vec3 lookFrom(13, 2, 3);
	Vec3 lookAt(0, 0, 0);
	Vec3 vUp(0, 1, 0);
	float distanceToFocus = 10.f;
	float aperture = 0.1f;
	Camera camera(lookFrom, lookAt, vUp, 20.f, aspectRatio, aperture, distanceToFocus);

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
