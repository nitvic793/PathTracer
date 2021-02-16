#pragma once

#include <PathTracer.h>

#define ALTERNATE_DIFFUSE 0
#define OLD_LAMBERTIAN_DIFFUSE 0

namespace nv
{
	struct HitRecord;

	class Material
	{
	public:
		using Vec3 = math::Vec3;
		using Ray = math::Ray;
		using Color = math::Color;
		virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const = 0;
	};

	class Lambertian : public Material
	{
	public:
		Lambertian(const Color& albedo) : Albedo(albedo) {}

		virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
		Color Albedo;
	};

	class Metal : public Material
	{
	public:
		Metal(const Color& albedo, float roughness = 0.f) : Albedo(albedo), Roughness(roughness < 1.f ? roughness : 1.f) {}

		virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
		Color Albedo;
		float Roughness;
	};

	bool Lambertian::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const
	{
#if ALTERNATE_DIFFUSE == 1
		Vec3 scatterDirection = hitRecord.Normal + hitRecord.Normal + math::RandomInHemisphere(hitRecord.Normal);
#elif OLD_LAMBERTIAN_DIFFUSE == 1
		Vec3 scatterDirection = hitRecord.Normal + hitRecord.Normal + math::RandomInUnitSphere();
#else
		Vec3 scatterDirection = hitRecord.Normal + hitRecord.Normal + math::RandomUnitVector();
#endif

		//Catch degenerate scatter direction
		if (scatterDirection.NearZero())
			scatterDirection = hitRecord.Normal;

		scattered = Ray(hitRecord.Point, scatterDirection);
		attenuation = Albedo;
		return true;
	}

	bool Metal::Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered) const
	{
		Vec3 reflected = Reflect(UnitVector(rayIn.Direction()), hitRecord.Normal);
		scattered = Ray(hitRecord.Point, reflected + Roughness * math::RandomInUnitSphere());
		attenuation = Albedo;
		return Dot(scattered.Direction(), hitRecord.Normal) > 0;
	}
}
