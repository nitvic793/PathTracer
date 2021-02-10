#pragma once

#include <Math/Vec3.h>

namespace nv::math
{
	class Ray
	{
	public:
		Ray(){}
		Ray(const Vec3& origin, const Vec3& direction) 
			: origin(origin), dir(direction)
		{}

		Vec3 Origin() const { return origin; }
		Vec3 Direction() const { return dir; }

		Vec3 At(float t) const 
		{
			return origin + t * dir;
		}

		Vec3 origin;
		Vec3 dir;
	};
}
