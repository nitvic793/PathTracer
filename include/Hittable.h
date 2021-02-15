#pragma once

#include <Math/Vec3.h>
#include <Math/Ray.h>
#include <vector>

namespace nv
{
	struct HitRecord
	{
		using Ray = math::Ray;
		using Vec3 = math::Vec3;
		Vec3 Point;
		Vec3 Normal;
		float T;

		bool FrontFace;

		inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
		{
			FrontFace = math::Dot(ray.Direction(), outwardNormal) < 0;
			Normal = FrontFace ? outwardNormal : -outwardNormal;
		}
	};

	class Hittable
	{
	public:
		using Ray = math::Ray;
		virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
	};
}

