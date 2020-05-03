#include "matrix.hpp"

#include <assert.h>

template <class T>
Matrix2Dim<T> :: Matrix2Dim (T init_value, int _dim_row, int _dim_column)
{
    dim_row = _dim_row;
    dim_column = _dim_column;

    for (int i = 0; i < dim_row; i++)
        matrix.push_back(std::vector<T>(dim_column, init_value));
}

template <class T>
void Matrix2Dim<T> :: set_cell(T value, int row, int column)
{
    assert( row >= 0 && row < dim_row && column >= 0 && column < dim_column);
    
    matrix[row][column] = value;
}

template <class T>
T Matrix2Dim<T> :: get_cell(int row, int column)
{
    assert( row >= 0 && row < dim_row && column >= 0 && column < dim_column);

    return matrix[row][column];
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