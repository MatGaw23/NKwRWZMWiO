#include <iostream>
#include "matrix.hpp"

int main(void)
{
    Matrix2Dim<int> m(0, 5, 5);
    
    m.set_cell(6, 1, 2);
    m.print();
    m.load_from_file("test_matrix.txt");
    m.print();

	return 0;
}