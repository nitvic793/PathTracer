#pragma once

#include <PathTracer.h>

namespace nv
{
	void WriteColor(std::ostream& out, math::Color pixelColor, int samplesPerPixel)
	{
		float r = pixelColor.x;
		float g = pixelColor.y;
		float b = pixelColor.z;

		float scale = 1.f / samplesPerPixel;
		r *= scale;
		g *= scale;
		b *= scale;

		// Write the translated [0,255] value of each color component.
		out << static_cast<int>(256 * Clamp(r, 0.f, 0.999f)) << ' '
			<< static_cast<int>(256 * Clamp(g, 0.f, 0.999f)) << ' '
			<< static_cast<int>(256 * Clamp(b, 0.f, 0.999f)) << '\n';
	}
}
