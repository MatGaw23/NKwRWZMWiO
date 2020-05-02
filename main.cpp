#include <iostream>
#include "matrix.cpp"

int main(void)
{
    Matrix2Dim<double> m(0.3653, 2, 4);

	std::cout<<"Hello word!"<< std::endl;
    
    m.print();
	return 0;
}
