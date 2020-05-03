#include <iostream>
#include "matrix.hpp"

int main(void)
{
    Matrix2Dim<int> m(0, 2, 4);
    m.set_cell(6, 1, 2);
    m.print();
    
	return 0;
}
