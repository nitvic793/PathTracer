#pragma once

#include <Math/Vec3.h>

namespace nv
{
	void WriteColor(std::ostream& out, math::Color pixelColor)
	{
		// Write the translated [0,255] value of each color component.
		out << static_cast<int>(255.999 * pixelColor.x) << ' '
			<< static_cast<int>(255.999 * pixelColor.y) << ' '
			<< static_cast<int>(255.999 * pixelColor.z) << '\n';
	}
}
