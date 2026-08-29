#include <print>
#include "vector.h"
#include "matrix.h"
#include "polar.h"

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

	//la::Mat3 det3x3
	//{
	//	-4.0f, 0.0f, 1.0f,
	//	-3.0f, 2.0f, 4.0f,
	//	3.0f, -2.0f, -1.0f
	//};

	//std::cout << "matriz M\n" << det3x3 << "\n";

	//std::cout << "det(M) = " << la::determinant(det3x3) << "\n";

	//std::cout << "inversa de M\n" << la::inverse(det3x3) << "\n";

	//std::cout << "matrix M * inversa M\n";
	//std::cout << inverse(det3x3) * det3x3 << "\n";

	//std::cout << std::boolalpha << la::equal(la::Vec2{ 1.0f }, la::Vec2{ 1.0f }) << "\n";
	//std::cout << std::boolalpha << la::equal(det3x3, det3x3) << "\n";
	//std::cout << std::boolalpha << la::equal(det3x3, la::Mat3{ 1.0f }) << "\n\n";

	//std::cout << std::boolalpha << (la::Vec2{ 1.0f } == la::Vec2{ 1.0f }) << "\n";

	//la::Vec3 p{ -0.1495f, -0.1986f, -0.9685f };
	//la::Vec3 q{ -0.8256f,  0.5640f,  0.0117f };
	//la::Vec3 r{ -0.5439f, -0.8015f,  0.2484f };

	//std::cout << "pLength = " << p.length() << "\n";
	//std::cout << "qLength = " << q.length() << "\n";
	//std::cout << "rLength = " << r.length() << "\n\n";

	//std::cout << "p * q = " << (int) la::dot(p, q) << "\n";
	//std::cout << "p * r = " << (int) la::dot(p, r) << "\n";
	//std::cout << "q * r = " << (int) la::dot(q, r) << "\n\n";

	//std::cout << "det = " << la::determinant(la::Mat3{ p, q, r }) << "\n";

	//la::Vec3 v{ 1.0f };
	//la::Vec3 vReflected{ la::reflect(v, la::Vec3{ 0.0f, 1.0f, 0.0f }) };

	//std::cout << vReflected << "\n";

	std::cout << "========================================================================\n";
	std::cout << "  INICIANDO BATERIA DE TESTES: SPHERICAL / POLAR 3D COORDINATES\n";
	std::cout << "========================================================================\n\n";

	testCanonicalCoord3D();
	testVec3ToPolar3D();
	testPolar3DToVec3();
	testRoundTrip3D();

	std::cout << "========================================================================\n";
	std::cout << "  TODOS OS TESTES 3D PASSARAM COM RIGOR MATEMATICO!\n";
	std::cout << "========================================================================\n";

	return 0;
}
