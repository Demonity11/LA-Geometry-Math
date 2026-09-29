#include "matrix.h"

namespace la
{
	// ===================================
	// forward declarations for Quat
	// ===================================

	struct Quat;

	[[nodiscard]] constexpr float dot(const Quat& q1, const Quat& q2);
	[[nodiscard]] constexpr Quat conjugate(const Quat& q);
	[[nodiscard]] constexpr Quat inverse(const Quat& q);
	[[nodiscard]] constexpr Quat slerp(const Quat& q0, Quat q1, float t);

	constexpr Quat operator*(const Quat& q1, const Quat& q2);

	// ===================================
	// type definitions for Quat
	// ===================================

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

		constexpr Quat operator-() const { return Quat{ -w, -x, -y, -z }; }

		constexpr Quat& operator+=(const Quat& q)
		{
			this->w += q.w;
			this->x += q.x;
			this->y += q.y;
			this->z += q.z;

			return *this;
		}

		constexpr Quat& operator-=(const Quat& q)
		{
			this->w -= q.w;
			this->x -= q.x;
			this->y -= q.y;
			this->z -= q.z;

			return *this;
		}

		constexpr Quat& operator*=(const float k)
		{
			this->w *= k;
			this->x *= k;
			this->y *= k;
			this->z *= k;

			return *this;
		}

		constexpr Quat& operator*=(const Quat& q)
		{
			*this = *this * q;

			return *this;
		}

		constexpr Quat& operator/=(const float k)
		{
			const float invK{ 1.0f / k };
			*this *= invK;

			return *this;
		}
	};

	// ===================================
	// operator overloading for Quat
	// ===================================

	constexpr Quat operator+(Quat q1, const Quat& q2)
	{
		q1 += q2;

		return q1;
	}

	constexpr Quat operator-(Quat q1, const Quat& q2)
	{
		q1 -= q2;

		return q1;
	}

	constexpr Quat operator*(Quat q, const float k)
	{
		q *= k;

		return q;
	}

	constexpr Quat operator*(const float k, Quat q)
	{
		q *= k;

		return q;
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

	constexpr Quat operator/(Quat q, float k)
	{
		q /= k;

		return q;
	}

	// ===================================
	// function definitions for Quat
	// ===================================

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

	constexpr Quat slerp(const Quat& q0, Quat q1, float t)
	{
		float cosOmega{ dot(q0, q1) };

		if (cosOmega < 0.0f)
		{
			q1 = -q1;
			cosOmega = -cosOmega;
		}

		float k0{}, k1{};

		if (cosOmega > 0.9999f)
		{
			k0 = 1.0f - t;
			k1 = t;
		}

		else
		{
			float sinOmega{ std::sqrt(1.0f - cosOmega * cosOmega) };

			float omega{ std::atan2(sinOmega, cosOmega) };

			float oneOverSinOmega{ 1.0f / sinOmega };

			k0 = std::sin((1.0f - t) * omega) * oneOverSinOmega;
			k1 = std::sin(t * omega) * oneOverSinOmega;
		}

		return k0 * q0 + k1 * q1;
	}
}