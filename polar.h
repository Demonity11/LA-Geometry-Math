#ifndef POLAR_H
#define POLAR_H

#include "vector.h"

namespace la
{
	struct Polar2D
	{
		float r{ 0.0f };     // circle radius
		float theta{ 0.0f }; // angle
	};

	struct Polar3D
	{
		float r{ 0.0f }; // sphere radius
		float h{ 0.0f }; // heading - initially pointing towards +z, rotates clockwise
		float p{ 0.0f }; // pitch   - initially pointing horizontally, rotates downward
	};

	struct Cyl3D
	{
		float r{ 0.0f };     // cylinder radius
		float theta{ 0.0f }; // angle
		float z{ 0.0f };     // height
	};

	constexpr auto convertToCanonicalCoord(const Polar2D& p) -> Polar2D;
	constexpr auto convertToCanonicalCoord(const Polar3D& p) -> Polar3D;	

	constexpr auto convertVec2ToPolar2D(const Vec2& v)		 -> Polar2D;
	constexpr auto convertPolar2DToVec2(const Polar2D& p)	 -> Vec2;

	constexpr auto convertVec3ToPolar3D(const Vec3& v)		 -> Polar3D;
	constexpr auto convertPolar3DToVec3(const Polar3D& p)	 -> Vec3;

	constexpr auto convertVec3ToCyl3D(const Vec3& v)		 -> Cyl3D;
	constexpr auto convertCyl3DToVec3(const Cyl3D& c)		 -> Vec3;

	constexpr Polar2D convertToCanonicalCoord(const Polar2D& p)
	{
        constexpr float PI{ static_cast<float>(std::numbers::pi) };
		constexpr float twoPI{ 2.0f * PI };

		if (std::abs(p.r) < FLT_EPSILON)
		{
			return Polar2D{ 0.0f, 0.0f };
		}

		Polar2D result{ p };

		if (result.r < 0.0f)
		{
			result.r = -result.r;
			result.theta += PI;
		}

        result.theta += PI;
        result.theta -= std::floor(result.theta / twoPI) * twoPI;
        result.theta -= PI;

        if (result.theta <= -PI + 1e-5f || result.theta > PI)
        {
            result.theta = PI;
        }

		return result;
	}

	constexpr Polar3D convertToCanonicalCoord(const Polar3D& p)
	{
		if (std::abs(p.r) < FLT_EPSILON)
		{
			return Polar3D{ 0.0f, 0.0f, 0.0f };
		}

		constexpr float PI{ static_cast<float>(std::numbers::pi) };
		constexpr float twoPI{ 2.0f * PI };
		constexpr float PIOverTwo{ PI / 2.0f };

		Polar3D result{ p };

		if (p.r < 0.0f)
		{
			result.r = -result.r;
			result.h += PI;
			result.p = -result.p;
		}

		if (std::abs(result.p) > PIOverTwo)
		{
			result.p += PIOverTwo;
			result.p -= std::floor(result.p / twoPI) * twoPI;

			if (result.p > PI)
			{
				result.h += PI;
				result.p = 3.0f * PIOverTwo - result.p;
			}
			else
			{
				result.p -= PIOverTwo;
			}
		}

		if (std::abs(result.p) >= PIOverTwo * 0.99999f)
		{
			result.h = 0.0f;
		}
		
		if (std::abs(result.h) > PI)
		{
			result.h += PI;
			result.h -= std::floor(result.h / twoPI) * twoPI;
			result.h -= PI;
		}

        else if (result.h < 0.0f && std::abs(result.h) - PI < 0.00001f)
        {
            result.h = PI;
        }

		return result;
	}

	constexpr Polar2D convertVec2ToPolar2D(const Vec2& v)
	{
        const float vLength{ v.length() };

		if (vLength < FLT_EPSILON)
		{
			return Polar2D{ 0.0f, 0.0f };
		}

		return Polar2D
		{ 
			vLength, 
			std::atan2(v.y, v.x) 
		};
	}

	constexpr Vec2 convertPolar2DToVec2(const Polar2D& p)
	{
		return Vec2
		{ 
			p.r * std::cos(p.theta), 
			p.r * std::sin(p.theta) 
		};
	}

	constexpr Polar3D convertVec3ToPolar3D(const Vec3& v)
	{
        const float r{ v.length() }; 

        if (r < FLT_EPSILON)
        {
            return Polar3D{ 0.0f, 0.0f, 0.0f };
        }

        const float dHorizontal{ std::sqrt(v.x * v.x + v.z * v.z) };

        const float p{ std::atan2(-v.y, dHorizontal) };

        float h{ 0.0f };

        if (dHorizontal > FLT_EPSILON)
        {
            h = std::atan2(v.x, v.z); 
        }

        return Polar3D{ r, h, p };
	}

	constexpr Vec3 convertPolar3DToVec3(const Polar3D& p)
	{
		return Vec3
		{
			 p.r * std::sin(p.h) * std::cos(p.p),
			-p.r * std::sin(p.p),
			 p.r * std::cos(p.h) * std::cos(p.p)
		};
	}

	constexpr Cyl3D convertVec3ToCyl3D(const Vec3& v)
	{
		if (v == Vec3{ 0.0f })
		{
			return Cyl3D{ 0.0f, 0.0f, 0.0f };
		}

		return Cyl3D
		{
			std::sqrt(v.x * v.x + v.y * v.y),
			std::atan2(v.y, v.x),
			v.z
		};
	}

	constexpr Vec3 convertCyl3DToVec3(const Cyl3D& c)
	{
		return Vec3
		{
			c.r * std::cos(c.theta),
			c.r * std::sin(c.theta),
			c.z
		};
	}
}

#endif