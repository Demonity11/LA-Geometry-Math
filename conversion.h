#ifndef CONVERSION_H
#define CONVERSION_H

#include "quaternion.h"

namespace la
{
	constexpr Mat4 EulerToMatrix(float h, float p, float b)
	{
		using std::cos;
		using std::sin;

		return Mat4
		{
			Vec4{ cos(h) * cos(b) + sin(h) * sin(p) * sin(b), sin(b) * cos(p), -sin(h) * cos(b) + cos(h) * sin(p) * sin(b), 0.0f },
			Vec4{ -cos(h) * sin(b) + sin(h) * sin(p) * cos(b), cos(b) * cos(p), sin(b) * sin(h) + cos(h) * sin(p) * cos(b), 0.0f },
			Vec4{ sin(h) * cos(p), -sin(p), cos(h) * cos(p), 0.0f },
			Vec4{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
	}

	constexpr Vec3 MatrixToEuler(const Mat4& m)
	{
		float h{}, p{}, b{};

		if (-m[2][1] <= -1.0f)
		{
			p = -1.570796f; // -pi/2
		}
		else if (-m[2][1] >= 1.0f)
		{
			p = 1.570796f; // pi/2
		}
		else
		{
			p = std::asin(-m[2][1]);
		}

		if (std::abs(-m[2][1]) > 0.9999f)
		{
			b = 0.0f;
			h = std::atan2(-m[0][2], m[0][0]);
		}
		else
		{
			h = std::atan2(m[2][0], m[2][2]);
			b = std::atan2(m[0][1], m[1][1]);
		}

		return Vec3{ h, p, b };
	}

	constexpr Mat4 QuatToMatrix(const Quat& q)
	{
		return Mat4
		{
			Vec4{ 1 - 2 * q.y * q.y - 2 * q.z * q.z, 2 * q.x * q.y + 2 * q.w * q.z, 2 * q.x * q.z - 2 * q.w * q.y, 0.0f },
			Vec4{ 2 * q.x * q.y - 2 * q.w * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z, 2 * q.y * q.z + 2 * q.w * q.x, 0.0f },
			Vec4{ 2 * q.x * q.z + 2 * q.w * q.y, 2 * q.y * q.z - 2 * q.w * q.x, 1 - 2 * q.x * q.x - 2 * q.y * q.y, 0.0f },
			Vec4{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
	}

	constexpr Quat MatrixToQuat(const Mat4& m)
	{
		float fourWSquaredMinus1{  m[0][0] + m[1][1] + m[2][2] };
		float fourXSquaredMinus1{  m[0][0] - m[1][1] - m[2][2] };
		float fourYSquaredMinus1{ -m[0][0] + m[1][1] - m[2][2] };
		float fourZSquaredMinus1{ -m[0][0] - m[1][1] + m[2][2] };

		int biggestIndex{ 0 };

		float fourBiggestSquaredMinus1{ fourWSquaredMinus1 };

		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		float biggestVal{ std::sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f };
		float mult{ 0.25f / biggestVal };

		switch (biggestIndex)
		{
		case 0: return { biggestVal, (m[2][1] - m[1][2]) * mult, (m[0][2] - m[2][0]) * mult, (m[1][0] - m[0][1]) * mult };

		case 1: return { (m[2][1] - m[1][2]) * mult, biggestVal, (m[1][0] + m[0][1]) * mult, (m[0][2] + m[2][0]) * mult };

		case 2: return { (m[0][2] - m[2][0]) * mult, (m[1][0] - m[0][1]) * mult, biggestVal, (m[2][1] + m[1][2]) * mult };

		case 3: return { (m[1][0] - m[0][1]) * mult, (m[0][2] - m[2][0]) * mult, (m[2][1] + m[1][2]) * mult, biggestVal };
		}

		return Quat{};
	}

	constexpr Quat EulerToQuat(float h, float p, float b)
	{
		float hOver2{ h * 0.5f };
		float pOver2{ p * 0.5f };
		float bOver2{ b * 0.5f };

		float cosh{ std::cos(hOver2) }, sinh{ std::sin(hOver2) };
		float cosp{ std::cos(pOver2) }, sinp{ std::sin(pOver2) };
		float cosb{ std::cos(bOver2) }, sinb{ std::sin(bOver2) };

		return Quat
		{
			cosh * cosp * cosb + sinh * sinp * sinb,
			cosh * sinp * cosb + sinh * cosp * sinb,
			sinh * cosp * cosb - cosh * sinp * sinb,
			cosh * cosp * sinb - sinh * sinp * cosb
		};
	}
}

#endif
