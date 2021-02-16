#pragma once

#include "PathTracer.h"

namespace nv
{
	class Camera
	{
	public:
		using Vec3 = math::Vec3;
		using Ray = math::Ray;
		Camera(
			Vec3 lookFrom,
			Vec3 lookAt,
			Vec3 vUp,
			float vfovInDegrees,
			float aspectRatio,
			float aperture,
			float focusDistance)
		{
			float theta = DegreesToRadians(vfovInDegrees);
			float h = tan(theta / 2.f);
			float viewportHeight = 2.f * h;
			float viewportWidth = aspectRatio * viewportHeight;

			w = UnitVector(lookFrom - lookAt);
			u = UnitVector(Cross(vUp, w));
			v = Cross(w, u);

			Origin = lookFrom;
			Horizontal = focusDistance * viewportWidth * u;
			Vertical = focusDistance * viewportHeight * v;
			LowerLeftCorner = Origin - Horizontal / 2.f - Vertical / 2.f - focusDistance * w;

			LensRadius = aperture / 2.f;
		}

		Ray GetRay(float s, float t) const
		{
			Vec3 rd = LensRadius * math::RandomInUnitDisk();
			Vec3 offset = u * rd.x + v * rd.y;

			return Ray(Origin + offset, LowerLeftCorner + s * Horizontal + t * Vertical - Origin - offset);
		}

	protected:
		Vec3 Origin;
		Vec3 LowerLeftCorner;
		Vec3 Horizontal;
		Vec3 Vertical;

		Vec3 u, v, w;
		float LensRadius;
	};
}
