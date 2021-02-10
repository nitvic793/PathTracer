// PathTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Math/Vec3.h>
#include <Math/Ray.h>
#include <Color.h>

using namespace nv;
using namespace nv::math;

float HitSphere(const Vec3& center, float radius, const Ray& ray)
{
	Vec3 oc = ray.origin - center;
	float a = Dot(ray.dir, ray.dir);
	float b = 2.f * Dot(oc, ray.dir);
	float c = Dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.f;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.f * a);
	}
}

Color RayColor(const Ray& ray)
{
	Vec3 center(0, 0, -1);
	float radius = 0.5f;
	float t = HitSphere(center, radius, ray);
	if (t > 0.f)
	{
		Vec3 normal = UnitVector(ray.At(t) - center);
		return 0.5f * Color(normal.x + 1, normal.y + 1, normal.z + 1);
	}

	Vec3 unitDirection = UnitVector(ray.Direction());
	t = 0.5f * (unitDirection.y + 1.f);
	return Lerp(Color(1.f, 1.f, 1.f), Color(0.5f, 0.7f, 1.f), t);
}

void RenderImage()
{
	// Image
	constexpr float aspectRatio = 16.f / 9.f;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = (int)(imageWidth / aspectRatio);

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

			Color pixelColor = RayColor(ray);
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
