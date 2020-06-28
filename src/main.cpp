#include <iostream>
#include "matrix.hpp"
#include "algorithm_core.hpp"

int main(void)
{
    Matrix2Dim<int> m(0, 5, 5);
    
//    m.set_cell(6, 1, 2);
//    m.print();
 
    std::cout<<"Macierz wejsciowa:\n\n";
    m.load_from_file("test_matrix.txt");
    m.print();
    
    DFS d;
    d.dfs_start(m, 0, 2);
    

	return 0;
}