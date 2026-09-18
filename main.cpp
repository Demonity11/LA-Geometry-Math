#include "vector.h"
#include "matrix.h"
#include "polar.h"

int main()
{
	la::Vec2 a{ 1.0f, 0.0f };
	
	a += la::Vec2{ 0.0f, 1.0f };

	std::cout << a << "\n";

	return 0;
}
