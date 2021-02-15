#pragma once

#include <Hittable.h>
#include <vector>

namespace nv
{
	class Sphere : public Hittable
	{
	public:
		using Vec3 = math::Vec3;
		Sphere()
			: Center(Vec3(0, 0, 0)), Radius(1.f) {}
		Sphere(Vec3 center, float radius)
			: Center(center), Radius(radius) {}

		virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

		Vec3 Center;
		float Radius;
	};

	bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const
	{
		Vec3 oc = ray.origin - Center;
		float a = ray.Direction().LengthSquared();
		float halfB = Dot(oc, ray.dir);
		float c = Dot(oc, oc) - Radius * Radius;
		float discriminant = halfB * halfB - a * c;
		if (discriminant < 0) return false;
		float sqrtd = sqrt(discriminant);

		float root = (-halfB - sqrtd) / a;

		if (root < tMin || root > tMax)
		{
			root = (-halfB + sqrtd) / a;
			if (root < tMin || root > tMax)
				return false;
		}

		hitRecord.T = root;
		hitRecord.Point = ray.At(hitRecord.T);
		Vec3 outwardNormal = (hitRecord.Point - Center) / Radius;

		hitRecord.SetFaceNormal(ray, outwardNormal);

		return true;
	}
}


