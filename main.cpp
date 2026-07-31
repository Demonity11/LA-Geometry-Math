#include <print>
#include "vector.hpp"
#include <iostream>

int main()
{
	std::println("{}", LA::abs(-DBL_MIN));
	std::println("{}", LA::abs(DBL_MIN));
	std::println("{}", LA::abs(-FLT_MIN));
	std::println("{}", LA::abs(FLT_MIN));
	std::println("{}", LA::abs(-2));

	std::println("{}", LA::isNullVec(LA::Vec2{ 1.0f, 2.0f }));
	std::println("{}", LA::isNullVec(LA::Vec3{ 1.0f, 2.0f, 3.0f }));
	std::println("{}", LA::isNullVec(LA::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }));
	std::println("{}", LA::isNullVec(LA::Vec4{ 0.0f }));

	LA::Vec2 dividend{ 2.0f, 2.0f };
	LA::Vec2 vec{ dividend / 0.0f };

	LA::Vec2 dividendNormalized{ LA::normalize(dividend) };
	LA::Vec2 null{ LA::normalize(LA::Vec2{0.0f, 0.0f}) };

	std::println("{}, {}", vec.x, vec.y);

	std::println("{}", dividend.length());

	std::println("{}, {}", dividendNormalized.x, dividendNormalized.y);

	std::println("{}, {}", null.x, null.y);

	LA::Vec3 cross1{ LA::cross(LA::Vec3{ 1,2,3 }, LA::Vec3{ -3,1,2 }) };
	LA::Vec3 cross2{ LA::cross(LA::Vec3{ -3,1,2 }, LA::Vec3{ 1,2,3 }) };

	std::println("cross1 = ({}, {}, {})", cross1.x, cross1.y, cross1.z);
	std::println("cross2 = ({}, {}, {})", cross2.x, cross2.y, cross2.z);
}
