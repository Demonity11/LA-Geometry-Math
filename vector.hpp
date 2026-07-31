#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <array>
#include <cmath>
#include <numbers>

namespace LA
{
	template <size_t N>
	struct Vec;

	template <>
	struct Vec<2>
	{
		union
		{
			std::array<float, 2> data{};
			struct { float x, y; };
		};

		Vec<2>(float n) : x{ n }, y{ n } {}
		Vec<2>(float xP, float yP) : x{ xP }, y{ yP } {}
		Vec<2>() : x{ 0.0f }, y{ 0.0f } {}

		constexpr float& operator[](size_t idx) { return data[idx]; }
		constexpr const float& operator[](size_t idx) const { return data[idx]; }
		static constexpr size_t size() { return 2; }

		constexpr float length() const;
	};

	template <>
	struct Vec<3>
	{
		union
		{
			std::array<float, 3> data{};
			struct { float x, y, z; };
		};

		Vec<3>(float n) : x{ n }, y{ n }, z{ n } {}
		Vec<3>(float xP, float yP, float zP) : x{ xP }, y{ yP }, z{ zP } {}
		Vec<3>() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}

		constexpr float& operator[](size_t idx) { return data[idx]; }
		constexpr const float& operator[](size_t idx) const { return data[idx]; }
		static constexpr size_t size() { return 3; }

		constexpr float length() const;
	};

	template <>
	struct Vec<4>
	{
		union
		{
			std::array<float, 4> data{};
			struct { float x, y, z, w; };
		};

		Vec<4>(float n) : x{ n }, y{ n }, z{ n }, w{ n } {}
		Vec<4>(float xP, float yP, float zP, float wP) : x{ xP }, y{ yP }, z{ zP }, w{ wP } {}
		Vec<4>() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 0.0f } {}

		constexpr float& operator[](size_t idx) { return data[idx]; }
		constexpr const float& operator[](size_t idx) const { return data[idx]; }
		static constexpr size_t size() { return 4; }

		constexpr float length() const;
	};

	using Vec2 = Vec<2>;
	using Vec3 = Vec<3>;
	using Vec4 = Vec<4>;

	template <size_t N>
	constexpr Vec<N> operator+(const Vec<N>& v1, const Vec<N>& v2)
	{
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < result.size(); ++idx)
		{
			result[idx] = v1[idx] + v1[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Vec<N> operator-(const Vec<N>& v1, const Vec<N>& v2)
	{
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < result.size(); ++idx)
		{
			result[idx] = v1[idx] - v1[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Vec<N> operator*(const Vec<N>& v, const float f)
	{
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < result.size(); ++idx)
		{
			result[idx] = f * v[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Vec<N> operator*(const float f, const Vec<N>& v)
	{
		return v * f;
	}

	template <size_t N>
	constexpr Vec<N> operator/(const Vec<N>& v, const float f)
	{
		if (abs(f) < FLT_EPSILON)
			return Vec<N>(INFINITY);

		Vec<N> result{};

		for (size_t idx{ 0 }; idx < result.size(); ++idx)
		{
			result[idx] = v[idx] / f;
		}

		return result;
	}

	constexpr int abs(int value) { return value < 0 ? -value : value; }
	constexpr float abs(float value) { return value < 0.0f ? -value : value; }
	constexpr double abs(double value) { return value < 0.0 ? -value : value; }

	template <size_t N>
	constexpr Vec<N> normalize(const Vec<N>& v)
	{
		if (isNullVec(v))
		{
			return Vec<N>(NAN);
		}

		const float length{ v.length() };
		Vec<N> result{};

		for (size_t idx{ 0 }; idx < v.size(); ++idx)
		{
			result[idx] = v[idx] / length;
		}

		return result;
	}

	template <size_t N>
	constexpr bool isNullVec(const Vec<N>& v)
	{
		for (size_t idx{ 0 }; idx < v.size(); ++idx)
		{
			const float comp{ v[idx] };

			if (abs(comp) > FLT_EPSILON)
			{
				return false;
			}
		}

		return true;
	}

	template <size_t N>
	constexpr float dot(const Vec<N>& v1, const Vec<N>& v2)
	{
		float dot{ 0.0f };

		for (size_t idx{ 0 }; idx < v1.size(); ++idx)
		{
			dot += v1[idx] * v2[idx];
		}

		return dot;
	}

	Vec3 cross(const Vec3& v1, const Vec3& v2)
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
		const float c{ cos(v1, v2) };

		return std::sqrt(1.0f - c * c);
	}

	constexpr float Vec<2>::length() const { return std::sqrt(dot(*this, *this)); }
	constexpr float Vec<3>::length() const { return std::sqrt(dot(*this, *this)); }
	constexpr float Vec<4>::length() const { return std::sqrt(dot(*this, *this)); }
}

#endif