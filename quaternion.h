#include "vector.h"

namespace la
{
	struct Quat
	{
		float w{ 1.0f };
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };

		constexpr Quat() = default;
		constexpr Quat(float n) : w{ n }, x{ n }, y{ n }, z{ n } {}
		constexpr Quat(float wP, float xP, float yP, float zP) : w{ wP }, x{ xP }, y{ yP }, z{ zP } {}
		constexpr Quat(float wP, const Vec3& vP) : w{ wP }, x{ vP.x }, y{ vP.y }, z{ vP.z } {}

		float magnitude() const { return std::sqrt(w * w + x * x + y * y + z * z); }
		float magnitudeSquared() const { return w * w + x * x + y * y + z * z; }
	};

	constexpr Quat operator+(const Quat& q1, const Quat& q2)
	{
		return Quat{ q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z };
	}

	constexpr Quat operator-(const Quat& q1, const Quat& q2)
	{
		return Quat{ q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z };
	}

	constexpr Quat operator*(const Quat& q, float k)
	{
		return Quat{ q.w * k, q.x * k, q.y * k, q.z * k };
	}

	constexpr Quat operator*(float k, const Quat& q)
	{
		return q * k;
	}

	constexpr Quat operator*(const Quat& q1, const Quat& q2)
	{
		const Vec3 v1{ q1.x, q1.y, q1.z };
		const Vec3 v2{ q2.x, q2.y, q2.z };

		return Quat
		{ 
			q1.w * q2.w - dot(v1, v2), 
		    q1.w * v2 + q2.w * v1 + cross(v1, v2) 
		};
	}

	constexpr Quat operator/(const Quat& q, float k)
	{
		const float invK{ 1.0f / k };

		return q * invK;
	}

	constexpr float dot(const Quat& q1, const Quat& q2)
	{
		return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	}

	constexpr Quat conjugate(const Quat& q)
	{
		return Quat{ q.w, -q.x, -q.y, -q.z };
	}

	constexpr Quat inverse(const Quat& q)
	{
		if (const float magnitude{ q.magnitude() }; std::abs(magnitude) < FLT_EPSILON)
		{
			return conjugate(q) / magnitude;
		}

		return Quat(std::numeric_limits<float>::quiet_NaN());
	}
}