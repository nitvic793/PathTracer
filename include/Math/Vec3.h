
#pragma once


#include <cmath>
#include <iostream>
#include <PathTracer.h>

namespace nv::math
{
	class Vec3
	{
	public:
		Vec3() : x(0), y(0), z(0) {}
		Vec3(float e0, float e1, float e2) : x(e0), y(e1), z(e2) {}

		float X() const { return x; }
		float Y() const { return y; }
		float Z() const { return z; }

		Vec3 operator-() const { return Vec3(-x, -y, -z); }
		//float operator[](int i) const { return e[i]; }
		//float& operator[](int i) { return e[i]; }

		Vec3& operator+=(const Vec3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vec3& operator*=(const float t) {
			x *= t;
			y *= t;
			z *= t;
			return *this;
		}

		Vec3& operator/=(const float t) {
			return *this *= 1 / t;
		}

		float Length() const {
			return sqrt(LengthSquared());
		}

		float LengthSquared() const {
			return x * x + y * y + z * z;
		}

		inline static Vec3 Random()
		{
			return Vec3(nv::Random(), nv::Random(), nv::Random());
		}

		inline static Vec3 Random(float min, float max)
		{
			return Vec3(nv::Random(min, max), nv::Random(min, max), nv::Random(min, max));
		}

		bool NearZero() const
		{
			const auto s = 1e-8;
			return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
		}

		float x;
		float y;
		float z;
	};

	using Float3 = Vec3;
	using Point3 = Vec3;
	using Color = Vec3;

	inline std::ostream& operator<<(std::ostream& out, const nv::math::Vec3& v)
	{
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}

	inline nv::math::Vec3 operator+(const nv::math::Vec3& u, const nv::math::Vec3& v)
	{
		return nv::math::Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
	}

	inline nv::math::Vec3 operator-(const nv::math::Vec3& u, const nv::math::Vec3& v)
	{
		return nv::math::Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
	}

	inline nv::math::Vec3 operator*(const nv::math::Vec3& u, const nv::math::Vec3& v)
	{
		return nv::math::Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
	}

	inline nv::math::Vec3 operator*(float t, const nv::math::Vec3& v)
	{
		return nv::math::Vec3(t * v.x, t * v.y, t * v.z);
	}

	inline nv::math::Vec3 operator*(const nv::math::Vec3& v, float t)
	{
		return t * v;
	}

	inline nv::math::Vec3 operator/(nv::math::Vec3 v, float t)
	{
		return (1 / t) * v;
	}

	inline float Dot(const nv::math::Vec3& u, const nv::math::Vec3& v)
	{
		return u.x * v.x
			+ u.y * v.y
			+ u.z * v.z;
	}

	inline nv::math::Vec3 Cross(const nv::math::Vec3& u, const nv::math::Vec3& v)
	{
		return nv::math::Vec3(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
	}

	inline nv::math::Vec3 UnitVector(nv::math::Vec3 v)
	{
		return v / v.Length();
	}

	template<typename T>
	inline T Lerp(const T& x, const T& y, float t)
	{
		return (1.f - t) * x + t * y;
	}

	Vec3 RandomInUnitSphere()
	{
		while (true)
		{
			Vec3 out = Vec3::Random(-1.f, 1.f);
			if (out.LengthSquared() >= 1.f) continue;
			return out;
		}
	}

	Vec3 RandomUnitVector()
	{
		return UnitVector(RandomInUnitSphere());
	}

	Vec3 RandomInHemisphere(const Vec3& normal)
	{
		Vec3 inUnitSphere = RandomInUnitSphere();
		if (Dot(inUnitSphere, normal) > 0.f)
		{
			return inUnitSphere;
		}
		else
		{
			return -inUnitSphere;
		}
	}

	Vec3 Reflect(const Vec3& v, const Vec3& n)
	{
		return v - 2.f * Dot(v, n) * n;
	}

	Vec3 Refract(const Vec3& uv, const Vec3& n, float etaiOverEtat)
	{
		float cosTheta = fmin(Dot(uv, -n), 1.f);
		Vec3 rOutperp = etaiOverEtat * (uv + cosTheta * n);
		Vec3 rOutParallel = -sqrt(fabs(1.f -rOutperp.LengthSquared())) * n;
		return rOutperp + rOutParallel;
	}
}




