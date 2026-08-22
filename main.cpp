#include <print>
#include "vector.hpp"
#include "matrix.hpp"

int main()
{
	la::Mat3 det
	{ 
		3.0f, -1.0f, 5.0f, 
		1.0f, 2.0f, -3.0f, 
		2.0f, 6.0f, 1.0f 
	};

	std::cout << la::determinant(det) << "\n";

	std::cout << la::cofactor(det, 0, 0) << "\n";
	std::cout << la::cofactor(det, 0, 1) << "\n";

	la::Mat3 det3x3
	{
		-4.0f, -3.0f, 3.0f,
		0.0f, 2.0f, -2.0f,
		1.0f, 4.0f, -1.0f	
	};

	std::cout << transpose(det3x3) << "\n";

	std::cout << la::determinant(det3x3) << "\n";

	std::cout << la::inverse(transpose(det3x3)) << "\n";

	std::cout << inverse(transpose(det3x3)) * transpose(det3x3) << "\n";
}
