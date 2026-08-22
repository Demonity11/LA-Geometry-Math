#include "vector.hpp"
#include <array>

namespace la
{
	template <size_t N>
	struct Mat;

	template <>
	struct Mat<2>
	{
	public:
		constexpr Mat<2>() : m_data { Vec2{ 1.0f, 0.0f }, Vec2{ 0.0f, 1.0f } } {}
		constexpr explicit Mat<2>(float scalar) : m_data{ Vec2{ scalar, 0.0f }, Vec2{ 0.0f, scalar } } {}
		constexpr explicit Mat<2>(const Vec2& col0, const Vec2& col1) : m_data{ col0, col1 } {}
		constexpr explicit Mat<2>(float x0, float y0, float x1, float y1) : m_data { Vec2{ x0, y0 }, Vec2{ x1, y1 } } {}

		constexpr Vec2& operator[](size_t index) { return m_data[index]; }
		constexpr const Vec2& operator[](size_t index) const { return m_data[index]; }

		Mat<2> operator-() const { return Mat<2>{ -m_data[0], -m_data[1] }; }

	private:
		std::array<Vec2, 2> m_data{};
	};

	template <>
	struct Mat<3>
	{
	public:
		constexpr Mat<3>() : m_data{ Vec3{ 1.0f, 0.0f, 0.0f }, Vec3{ 0.0f, 1.0f, 0.0f }, Vec3{ 0.0f, 0.0f, 1.0f } } {}
		constexpr explicit Mat<3>(float scalar) : m_data{ Vec3{ scalar, 0.0f, 0.0f }, Vec3{ 0.0f, scalar, 0.0f }, Vec3{ 0.0f, 0.0f, scalar } } {}
		constexpr explicit Mat<3>(const Vec3& col0, const Vec3& col1, const Vec3& col2) : m_data{ col0, col1, col2 } {}
		constexpr explicit Mat<3>(float x0, float y0, float z0, 
						float x1, float y1, float z1, 
						float x2, float y2, float z2) 
			: m_data{ Vec3{ x0, y0, z0 }, Vec3{ x1, y1, z1 }, Vec3{ x2, y2, z2 } } {}

		constexpr Vec3& operator[](size_t index) { return m_data[index]; }
		constexpr const Vec3& operator[](size_t index) const { return m_data[index]; }

		Mat<3> operator-() const { return Mat<3>{ -m_data[0], -m_data[1], -m_data[2] }; }

	private:
		std::array<Vec3, 3> m_data{};
	};

	template <>
	struct Mat<4>
	{
	public:
		constexpr Mat<4>() : m_data{ Vec4{ 1.0f, 0.0f, 0.0f, 0.0f }, Vec4{ 0.0f, 1.0f, 0.0f, 0.0f }, Vec4{ 0.0f, 0.0f, 1.0f, 0.0f }, Vec4{ 0.0f, 0.0f, 0.0f, 1.0f } } {}
		constexpr explicit Mat<4>(float scalar) 
			: m_data{ Vec4{ scalar, 0.0f, 0.0f, 0.0f }, Vec4{ 0.0f, scalar, 0.0f, 0.0f }, Vec4{ 0.0f, 0.0f, scalar, 0.0f }, Vec4{ 0.0f, 0.0f, 0.0f, scalar } } {}
		constexpr explicit Mat<4>(const Vec4& col0, const Vec4& col1, const Vec4& col2, const Vec4& col3) : m_data{ col0, col1, col2, col3 } {}
		constexpr explicit Mat<4>(float x0, float y0, float z0, float w0,
			float x1, float y1, float z1, float w1,
			float x2, float y2, float z2, float w2,
			float x3, float y3, float z3, float w3)
			: m_data{ Vec4{ x0, y0, z0, w0 }, Vec4{ x1, y1, z1, w1 }, Vec4{ x2, y2, z2, w2 }, Vec4{ x3, y3, z3, w3 } } {}

		constexpr Vec4& operator[](size_t index) { return m_data[index]; }
		constexpr const Vec4& operator[](size_t index) const { return m_data[index]; }

		Mat<4> operator-() const { return Mat<4>{ -m_data[0], -m_data[1], -m_data[2], -m_data[3] }; }

	private:
		std::array<Vec4, 4> m_data{};
	};

	using Mat2 = Mat<2>;
	using Mat3 = Mat<3>;
	using Mat4 = Mat<4>;

	// overload operator<< to print matrices
	template <size_t N>
	std::ostream& operator<<(std::ostream& out, const Mat<N>& m)
	{
		for (size_t i{ 0 }; i < N; ++i)
		{
			out << "|";

			for (size_t j{ 0 }; j < N; ++j)
			{
				if (j == N - 1)
				{
					out << std::right; out.width(10);
				}
				else
				{
					out << std::left; out.width(10);
				}

				out << m[j][i];
			}

			out << "|\n";
		}

		return out;
	}

	template <size_t N>
	constexpr Mat<N> transpose(const Mat<N>& m)
	{
		Mat<N> result{};

		for (size_t col{ 0 }; col < N; ++col)
		{
			for (size_t row{ 0 }; row < N; ++row)
			{
				result[col][row] = m[row][col];
			}
		}

		return result;
	}

	constexpr Mat3 crossMatrix(const Vec3& v)
	{
		return Mat3
		{
			Vec3{  0.0f, v.z, -v.y },
			Vec3{ -v.z,  0.0f, v.x },
			Vec3{  v.y, -v.x,  0.0f }
		};
	}

	template <size_t N>
	constexpr Mat<N> operator+(const Mat<N>& m1, const Mat<N>& m2)
	{
		Mat<N> result{};

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			result[idx] = m1[idx] + m2[idx];
		}

		return result;
	}

	template <size_t N>
	constexpr Mat<N> operator-(const Mat<N>& m1, const Mat<N>& m2)
	{
		Mat<N> result{};

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			result[idx] = m1[idx] - m2[idx];
		}

		return result;
	}
	
	template <size_t N>
	constexpr Mat<N> operator*(const Mat<N>& m1, float scalar)
	{
		Mat<N> result{};

		for (size_t idx{ 0 }; idx < N; ++idx)
		{
			result[idx] = m1[idx] * scalar;
		}

		return result;
	}

	template <size_t N>
	constexpr Mat<N> operator*(float scalar, const Mat<N>& m1)
	{
		return m1 * scalar;
	}

	template <size_t N>
	constexpr Mat<N> operator/(const Mat<N>& m1, float scalar)
	{
		if (abs(scalar) < FLT_EPSILON)
		{
			return Mat<N>(std::numeric_limits<float>::quiet_NaN());
		}

		float invScalar{ 1.0f / scalar };

		return m1 * invScalar;
	}

	template <size_t N>
	constexpr Mat<N> operator*(const Mat<N>& m1, const Mat<N>& m2)
	{
		Mat<N> result{};

		Mat<N> m1T{ transpose(m1) };

		for (size_t j{ 0 }; j < N; ++j) 
		{
			for (size_t i{ 0 }; i < N; ++i) 
			{
				result[j][i] = dot(m1T[i], m2[j]);
			}
		}

		return result;
	}

	template <size_t N>
	requires (N >= 2 && N <= 4)
	constexpr Vec<N> operator*(const Mat<N>& m, const Vec<N>& v)
	{
		Vec<N> result{ m[0] * v[0] };

		for (size_t i{ 1 }; i < N; ++i)
		{
			result = result + (m[i] * v[i]);
		}

		return result;
	}

	template <size_t N>
	requires (N >= 2 && N <= 4)
	constexpr float determinant(const Mat<N>& m)
	{
		if constexpr (N == 2)
		{
			return m[0][0] * m[1][1] - (m[1][0] * m[0][1]);
		}
		else if constexpr (N == 3)
		{
			return
				m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) +
				m[1][0] * (m[2][1] * m[0][2] - m[0][1] * m[2][2]) +
				m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		}
		else if constexpr (N == 4)
		{
			return
				m[0][0] * (m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) + m[2][1] * (m[3][2] * m[1][3] - m[1][2] * m[3][3]) + m[3][1] * (m[1][2] * m[2][3] - m[2][2] * m[1][3])) -
				m[1][0] * (m[0][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) + m[2][1] * (m[3][2] * m[0][3] - m[0][2] * m[3][3]) + m[3][1] * (m[0][2] * m[2][3] - m[2][2] * m[0][3])) +
				m[2][0] * (m[0][1] * (m[1][2] * m[3][3] - m[3][2] * m[1][3]) + m[1][1] * (m[3][2] * m[0][3] - m[0][2] * m[3][3]) + m[3][1] * (m[0][2] * m[1][3] - m[1][2] * m[0][3])) -
				m[3][0] * (m[0][1] * (m[1][2] * m[2][3] - m[2][2] * m[1][3]) + m[1][1] * (m[2][2] * m[0][3] - m[0][2] * m[2][3]) + m[2][1] * (m[0][2] * m[1][3] - m[1][2] * m[0][3]));
		}
	}

	template <size_t N>
	requires (N >= 2 && N <= 4)
	constexpr float cofactor(const Mat<N>& m, size_t row, size_t col)
	{
		if constexpr (N == 2)
		{
			float minorVal{ m[(col == 0) ? 1 : 0][(row == 0) ? 1 : 0] };

			return ((row + col) % 2 == 0) ? minorVal : -minorVal;
		}

		else
		{
			using SubMat = Mat<N - 1>;

			SubMat minor{};

			for (size_t c{ 0 }; c < N - 1; ++c)
			{
				for (size_t r{ 0 }; r < N - 1; ++r)
				{
					size_t srcCol{ (c >= col) ? c + 1 : c };
					size_t srcRow{ (r >= row) ? r + 1 : r };

					minor[c][r] = m[srcCol][srcRow];
				}
			}

			float det{ determinant(minor) };

			return ((row + col) % 2 == 0) ? det : -det;
		}
	}

	template <size_t N>
	constexpr Mat<N> adjoint(const Mat<N>& m)
	{
		Mat<N> result{};

		for (size_t c{ 0 }; c < N; ++c)
		{
			for (size_t r{ 0 }; r < N; ++r)
			{
				result[c][r] = cofactor(m, r, c);
			}
		}

		return transpose(result);
	}

	template <size_t N>
	constexpr Mat<N> inverse(const Mat<N>& m)
	{
		float det{ determinant(m) };

		if (std::abs(det) < FLT_EPSILON)
		{
			return Mat<N>(std::numeric_limits<float>::quiet_NaN());
		}

		float invDet{ 1.0f / det };

		Mat<N> adj{ adjoint(m) };

		return invDet * adj;
	}

	constexpr Mat3 rotate(float angleRadians, const Vec3& axis)
	{
		const Vec3 n{ normalize(axis) };
		const float cos{ std::cos(angleRadians) };
		const float sin{ std::sin(angleRadians) };

		const float oneMinusCos{ 1.0f - cos };

		const Vec3 p
		{ 
			n.x * n.x * oneMinusCos + cos,
			n.x * n.y * oneMinusCos + n.z * sin,
			n.x * n.z * oneMinusCos - n.y * sin
		};

		const Vec3 q
		{
			n.x * n.y * oneMinusCos - n.z * sin,
			n.y * n.y * oneMinusCos + cos,
			n.y * n.z * oneMinusCos + n.x * sin
		};

		const Vec3 r
		{
			n.x * n.z * oneMinusCos + n.y * sin,
			n.y * n.z * oneMinusCos - n.x * sin,
			n.z * n.z * oneMinusCos + cos
		};

		return Mat3{ p, q, r };
	}

	constexpr Mat3 scale(float factor, const Vec3& direction)
	{
		const Vec3 n{ normalize(direction) };

		const float factorMinusOne{ factor - 1.0f };

		const Vec3 p
		{
			1.0f + factorMinusOne * n.x * n.x,
			factorMinusOne * n.x * n.y,
			factorMinusOne * n.x * n.z
		};

		const Vec3 q
		{
			factorMinusOne * n.x * n.y,
			1.0f + factorMinusOne * n.y * n.y,
			factorMinusOne * n.y * n.z
		};

		const Vec3 r
		{
			factorMinusOne * n.x * n.z,
			factorMinusOne * n.y * n.z,
			1.0f + factorMinusOne * n.z * n.z
		};

		return Mat3{ p, q, r };
	}
}