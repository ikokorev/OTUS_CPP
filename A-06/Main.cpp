#include <cstdlib>
#include <iostream>

#include <string>
#include "Matrix.h"
#include <unordered_map>

int main()
{
	Matrix<int, -1, > MatrixObj;
	std::cout << MatrixObj[0][0][0][0][0];

	auto m = MatrixObj[0];
	
	const int i = 15;
	MatrixObj[0][0][0][0][0] = i;
	std::cout << MatrixObj[0][0][0][0][0];
	
	system("pause");
    return 0;
}
