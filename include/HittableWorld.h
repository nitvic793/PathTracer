#pragma once

#include <Math/Vec3.h>
#include <Math/Ray.h>
#include <Hittable.h>
#include <vector>
#include <memory>

namespace nv
{
	class HittableWorld
	{
	public:
		using Ray = math::Ray;

		bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const;

		inline void Add(std::shared_ptr<Hittable> object)
		{
			objects.push_back(object);
		}

	protected:
		std::vector<std::shared_ptr<Hittable>> objects;
	};

	bool HittableWorld::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const
	{
		HitRecord hit;
		bool hasHit = false;
		float closestSoFar = tMax;

		for (const auto& object : objects)
		{
			if (object->Hit(ray, tMin, closestSoFar, hit))
			{
				hitRecord = hit;
				closestSoFar = hit.T;
				hasHit = true;
			}
		}

		return hasHit;
	}

}
