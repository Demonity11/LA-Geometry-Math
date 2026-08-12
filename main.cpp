#include <print>
#include "vector.hpp"
#include "matrix.hpp"
#include <iostream>

template <size_t N>
void printMatrix(const LA::Mat<N>& m)
{
	for (size_t i{ 0 }; i < N; ++i)
	{
		std::cout << "|";

		for (size_t j{ 0 }; j < N; ++j)
		{
			std::cout << m[j][i];

			if (j != N - 1)
			{
				std::cout << " ";
			}
		}

		std::cout << "|\n";
	}
}

template <size_t N>
void printVector(const LA::Vec<N>& v)
{
	std::cout << "(";

	for (size_t i{ 0 }; i < N; ++i)
	{
		std::cout << v[i];

		if (i != N - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << ")\n";
}

int main()
{
	//std::println("{}", LA::abs(-DBL_MIN));
	//std::println("{}", LA::abs(DBL_MIN));
	//std::println("{}", LA::abs(-FLT_MIN));
	//std::println("{}", LA::abs(FLT_MIN));
	//std::println("{}", LA::abs(-2));

	//LA::Vec2 dividend{ 2.0f, 2.0f };
	//LA::Vec2 vec{ dividend / 0.0f };

	//LA::Vec2 dividendNormalized{ LA::normalize(dividend) };
	//LA::Vec2 null{ LA::normalize(LA::Vec2{0.0f, 0.0f}) };

	//std::println("{}, {}", vec.x, vec.y);

	//std::println("{}", dividend.length());

	//std::println("{}, {}", dividendNormalized.x, dividendNormalized.y);

	//std::println("{}, {}", null.x, null.y);

	//LA::Vec3 cross1{ LA::cross(LA::Vec3{ 1,2,3 }, LA::Vec3{ -3,1,2 }) };
	//LA::Vec3 cross2{ LA::cross(LA::Vec3{ -3,1,2 }, LA::Vec3{ 1,2,3 }) };

	//std::println("cross1 = ({}, {}, {})", cross1.x, cross1.y, cross1.z);
	//std::println("cross2 = ({}, {}, {})", cross2.x, cross2.y, cross2.z);

	LA::Mat2 m1{ 1.0f, 2.0f, 3.0f, 4.0f };
	LA::Mat2 m2{ 5.0f, 6.0f, 7.0f, 8.0f };

	LA::Mat2 mult{ m1 * m2 };

	LA::Mat2 m1T{ transpose(m1) };
	
	printMatrix(m1);

	std::cout << "\n*\n\n";

	printMatrix(m2);

	std::cout << "\n=\n\n";

	printMatrix(mult);

	LA::Vec4 v{ 0.0f, 1.0f, 2.0f, 3.0f };
	printVector(v);
}
