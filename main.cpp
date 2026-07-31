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

	std::println("{}, {}", vec.x, vec.y);

	std::println("{}", dividend.length());
}
