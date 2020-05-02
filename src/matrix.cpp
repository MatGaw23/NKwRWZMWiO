#include "matrix.hpp"

// void HelloWorld::say() {
//  std::cout << "Hello, World"; 
// }
template <class T>
Matrix2Dim<T> :: Matrix2Dim (T init_value, int _dim_x, int _dim_y)
{
    dim_x = _dim_x;
    dim_y = _dim_y;

    for (int i = 0; i < dim_x; i++)
        matrix.push_back(std::vector<T>(dim_y, init_value));
}

template <class T>
void Matrix2Dim<T> :: print(void)
{
    for (auto dim_vector : matrix)
    {
        for (auto item : dim_vector)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

template class Matrix2Dim<float>;
template class Matrix2Dim<int>;
template class Matrix2Dim<double>;