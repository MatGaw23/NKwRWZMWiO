#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <vector>
#include <string>

template <class T>
class Matrix2Dim
{
    std::vector<std::vector<T>> matrix;
    int dim_row;
    int dim_column;

public:
    Matrix2Dim (T init_value, int _dim_row, int _dim_column);
    void set_cell(T value, int row, int column);
    T get_cell(int row, int column);
    void print(void);
    bool load_from_file(std::string filename);
};

#endif /* _MATRIX_H */