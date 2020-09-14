#include <iostream>
#include <string>
#include "matrix.hpp"
#include "algorithm_core.hpp"

int main(void)
{
    int matrix_size, max_cost, start_vertex;
    std::string filename;

    std::cout<<"=== ZADANIE Z KOSMITAMI (nr. 15) ==="<<std::endl;
    std::cout<<"Podaj rozmiar macierzy:"<<std::endl;
    std::cin>>matrix_size;
    std::cout<<std::endl;

    std::cout<<"Podaj nazwe pliku z macierza (z rozszerzeniem):"<<std::endl;
    std::cin>>filename;
    std::cout<<std::endl;

    std::cout<<"Podaj komore startowa:"<<std::endl;
    std::cin>>start_vertex;
    std::cout<<std::endl;

    std::cout<<"Podaj czas T:"<<std::endl;
    std::cin>>max_cost;
    std::cout<<std::endl;
 
    std::cout<<"Macierz wejsciowa:\n\n";
    Matrix2Dim<int> m(0, matrix_size, matrix_size);
    m.load_from_file(filename);
    m.print();

    Algorithm aliens;
    aliens.algorithm_start(m, start_vertex, max_cost);


	return 0;
}