#include <print>
#include "vector.hpp"
#include "matrix.hpp"

int main()
{
	la::Mat3 rotation{ la::rotate(la::radians(-15.0f), la::Vec3{0.267f, -0.535f, 0.802f})};
	la::printMatrix(rotation);

	std::cout << "\n\n";

	la::Mat3 scale{ la::scale(5.0f, la::Vec3{0.267f, -0.535f, 0.802f}) };
	la::printMatrix(scale);

	std::cout << "\n\n";

	la::Mat3 projection{ la::scale(0.0f, la::Vec3{0.267f, -0.535f, 0.802f}) };
	la::printMatrix(projection);

	std::cout << "\n\n";

	la::Mat3 reflection{ la::scale(-1.0f, la::Vec3{0.267f, -0.535f, 0.802f}) };
	la::printMatrix(reflection);

	std::cout << "\n\n";

	la::Mat3 ry{ la::rotate(la::radians(-30.0f), la::Vec3{ 0.0f, 1.0f, 0.0f }) };
	la::Mat3 rx{ la::rotate(la::radians(22.0f), la::Vec3{ 1.0f, 0.0f, 0.0f }) };
	la::Mat3 result{ ry * rx };

	la::printMatrix(result);

	la::Mat3 det
	{ 
		3.0f, -1.0f, 5.0f, 
		1.0f, 2.0f, -3.0f, 
		2.0f, 6.0f, 1.0f 
	};

	std::cout << la::determinant(det) << "\n";

	std::cout << la::cofactor(det, 0, 0) << "\n";
	std::cout << la::cofactor(det, 0, 1) << "\n";

	la::Mat4 det4x4
	{
		3.0f, -1.0f, 5.0f, 3.0f,
		1.0f, 2.0f, -3.0f, -2.0f,
		2.0f, 6.0f, 1.0f, 0.0f,
		3.0f, -1.0f, 0.0f, 4.0f
	};

	la::printMatrix(det4x4);
	std::cout << "\n";

	std::cout << la::determinant(det4x4) << "\n";
}
