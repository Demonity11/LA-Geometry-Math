#include <print>
#include "vector.hpp"
#include "matrix.hpp"

int main()
{
	//la::Mat3 det
	//{ 
	//	3.0f, -1.0f, 5.0f, 
	//	1.0f, 2.0f, -3.0f, 
	//	2.0f, 6.0f, 1.0f 
	//};

	//std::cout << la::determinant(det) << "\n";

	//std::cout << la::cofactor(det, 0, 0) << "\n";
	//std::cout << la::cofactor(det, 0, 1) << "\n";

	la::Mat3 det3x3
	{
		-4.0f, 0.0f, 1.0f,
		-3.0f, 2.0f, 4.0f,
		3.0f, -2.0f, -1.0f
	};

	std::cout << "matriz M\n" << det3x3 << "\n";

	std::cout << "det(M) = " << la::determinant(det3x3) << "\n";

	std::cout << "inversa de M\n" << la::inverse(det3x3) << "\n";

	std::cout << "matrix M * inversa M\n";
	std::cout << inverse(det3x3) * det3x3 << "\n";

	std::cout << std::boolalpha << la::equal(la::Vec2{ 1.0f }, la::Vec2{ 1.0f }) << "\n";
	std::cout << std::boolalpha << la::equal(det3x3, det3x3) << "\n";
	std::cout << std::boolalpha << la::equal(det3x3, la::Mat3{ 1.0f }) << "\n";
}
