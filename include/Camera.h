#pragma once

#include "PathTracer.h"

namespace nv
{
	class Camera
	{
	public:
		using Vec3 = math::Vec3;
		using Ray = math::Ray;
		Camera()
		{
			float aspectRatio = 16.f / 9.f;
			float viewportHeight = 2.f;
			float viewportWidth = aspectRatio * viewportHeight;
			float focalLength = 1.f;

			Origin = Vec3(0, 0, 0);
			Horizontal = Vec3(viewportWidth, 0, 0);
			Vertical = Vec3(0, viewportHeight, 0);
			LowerLeftCorner = Origin - Horizontal / 2.f - Vertical / 2.f - Vec3(0, 0, focalLength);
		}

		Ray GetRay(float u, float v) const
		{
			return Ray(Origin, LowerLeftCorner + u * Horizontal + v * Vertical);
		}

	protected:
		Vec3 Origin;
		Vec3 LowerLeftCorner;
		Vec3 Horizontal;
		Vec3 Vertical;
	};
}
