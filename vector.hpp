#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <cmath>
#include <cfloat>
#include <numbers>
#include <algorithm>

namespace LA
{
	template <size_t N>
	struct Vec;

	// forward declaration
	template <size_t N>
	constexpr float dot(const Vec<N>& v1, const Vec<N>& v2);

	template <>
	struct Vec<2>
	{
		float x{ 0.0f };
		float y{ 0.0f };

		constexpr Vec<2>() = default;
		constexpr explicit Vec<2>(float n) : x{ n }, y{ n } {}
		constexpr explicit Vec<2>(float xP, float yP) : x{ xP }, y{ yP } {}

		constexpr float& operator[](size_t idx) 
		{ 
			return (idx == 0) ? x : y;
		}
		constexpr const float& operator[](size_t idx) const
		{
			return (idx == 0) ? x : y;
		}

		constexpr Vec<2> operator-() const { return Vec<2>{ -x, -y }; }

		constexpr float length() const { return std::sqrt(dot(*this, *this)); }
		constexpr float lengthSquared() const { return dot(*this, *this); }
	};

	template <>
	struct Vec<3>
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };

		constexpr Vec<3>() = default;
		constexpr explicit Vec<3>(float n) : x{ n }, y{ n }, z{ n } {}
		constexpr explicit Vec<3>(float xP, float yP, float zP) : x{ xP }, y{ yP }, z{ zP } {}

		constexpr float& operator[](size_t idx)
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			default: return z;
			}
		}
		constexpr const float& operator[](size_t idx) const 
		{ 
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			default: return z;
			}
		}

		constexpr Vec<3> operator-() const { return Vec<3>{ -x, -y, -z }; }

		constexpr float length() const { return std::sqrt(dot(*this, *this)); }
		constexpr float lengthSquared() const { return dot(*this, *this); }
	};

	template <>
	struct Vec<4>
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
		float w{ 0.0f };

		constexpr Vec<4>() = default;
		constexpr explicit Vec<4>(float n) : x{ n }, y{ n }, z{ n }, w{ n } {}
		constexpr explicit Vec<4>(float xP, float yP, float zP, float wP) : x{ xP }, y{ yP }, z{ zP }, w{ wP } {}

		constexpr float& operator[](size_t idx)
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: return w;
			}
		}
		constexpr const float& operator[](size_t idx) const
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: return w;
			}
		}

		constexpr Vec<4> operator-() const { return Vec<4>{ -x, -y, -z, -w }; }

		constexpr float length() const { return std::sqrt(dot(*this, *this)); }
		constexpr float lengthSquared() const { return dot(*this, *this); }
	};

	using Vec2 = Vec<2>;
	using Vec3 = Vec<3>;
	using Vec4 = Vec<4>;

	template <size_t N>
	constexpr Vec<N> operator+(const Vec<N>& v1, const Vec<N>& v2)
	{
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			result[idx] = v1[idx] + v2[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Vec<N> operator-(const Vec<N>& v1, const Vec<N>& v2)
	{
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			result[idx] = v1[idx] - v2[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Vec<N> operator*(const Vec<N>& v, const float scalar)
	{
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			result[idx] = scalar * v[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Vec<N> operator*(const float scalar, const Vec<N>& v)
	{
		return v * scalar;
	}

	template <size_t N>
	constexpr Vec<N> operator/(const Vec<N>& v, float scalar)
	{
		if (std::abs(scalar) < FLT_EPSILON)
			return Vec<N>(std::numeric_limits<float>::quiet_NaN());

		float invScalar{ 1.0f / scalar };

		return v * invScalar;
	}

	template <size_t N>
	constexpr bool operator==(const Vec<N>& v1, const Vec<N>& v2)
	{
		for (size_t i{ 0 }; i < N; ++i)
		{
			if (std::abs(v1[i] - v2[i]) > FLT_EPSILON)
			{
				return false;
			}
		}

		return true;
	}

	template <size_t N>
	constexpr bool operator!=(const Vec<N>& v1, const Vec<N>& v2)
	{
		return !(v1 == v2);
	}

	template <size_t N>
	constexpr Vec<N> normalize(const Vec<N>& v)
	{
		const float length{ v.lengthSquared() };

		if (length < FLT_EPSILON)
		{
			return Vec<N>(0.0f);
		}

		const float invLength{ 1.0f / length };

		return v * invLength;
	}

	template <size_t N>
	constexpr float dot(const Vec<N>& v1, const Vec<N>& v2)
	{
		float dot{ 0.0f };

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			dot += v1[idx] * v2[idx];
		}

		return dot;
	}

	constexpr Vec3 cross(const Vec3& v1, const Vec3& v2)
	{
		return Vec3
		{
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		};
	}

	constexpr float radians(float angle)
	{
		const float pi{ static_cast<float>(std::numbers::pi) };
		
		return pi * angle / 180.0f;
	}

	template <size_t N>
	constexpr float cos(const Vec<N>& v1, const Vec<N>& v2)
	{
		return dot(normalize(v1), normalize(v2));
	}

	template <size_t N>
	constexpr float sin(const Vec<N>& v1, const Vec<N>& v2)
	{
		const float c{ std::clamp(cos(v1, v2), -1.0f, 1.0f) };

		return std::sqrt(1.0f - c * c);
	}
}

#endif