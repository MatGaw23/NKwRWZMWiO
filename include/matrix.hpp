#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>

// class HelloWorld {
// public:
//  void say();
// };

#include <vector>
#include <iostream>

template <class T>
class Matrix2Dim
{
    std::vector<std::vector<T>> matrix;
    int dim_x;
    int dim_y;

public:
    Matrix2Dim (T init_value, int _dim_x, int _dim_y);

    void print(void);
};

#endif /* _MATRIX_H */