#pragma once

#include <cmath>
#include <limits>
#include <memory>

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

	inline constexpr float DegreesToRadians(float degrees) {
		return degrees * PI / 180.f;
	}

}

// Common Headers

#include "Math/Ray.h"
#include "Math/Vec3.h"