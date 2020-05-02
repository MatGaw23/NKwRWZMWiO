#include <vector>

template <typename T>
class Matrix2Dim
{
    std::vector<std::vector<T>> matrix;
    int dim_x;
    int dim_y;

public:

    Matrix2Dim (T init_value, int _dim_x, int _dim_y);

    void print(void);
};