#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

namespace nv
{
	// Usings

	using std::shared_ptr;
	using std::make_shared;
	using std::sqrt;

	// Constants

	constexpr float infinity = std::numeric_limits<float>::infinity();
	constexpr float PI = 3.1415926535897932385f;

	// Utility Functions

	inline constexpr float DegreesToRadians(float degrees) 
	{
		return degrees * PI / 180.f;
	}

	inline float Random()
	{
		static std::uniform_real_distribution<float> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline float Random(float min, float max)
	{
		return min + (max - min) * Random();
	}

	inline float Clamp(float x, float min, float max)
	{
		//float result = std::max(x, min);
		//result = std::min(max, x);
		//return result;
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

}

// Common Headers

#include "Math/Ray.h"
#include "Math/Vec3.h"
