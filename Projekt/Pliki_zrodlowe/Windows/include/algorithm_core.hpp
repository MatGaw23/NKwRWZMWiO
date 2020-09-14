#ifndef ALGORITHM_CORE_HPP
#define ALGORITHM_CORE_HPP

#include <matrix.hpp>
#include <vector>


struct cell_data
{
    int distance;
    std::vector<int> history;
};

class Algorithm
{
private:
    Matrix2Dim<int> *obj_matrix = NULL;
    bool somsiad_function(Matrix2Dim<int> *obj_matrix, int current_row, int current_col, struct cell_data **table, bool skip_value_above);
    bool check_history(int row_to_check, int column_to_check, int vertex_to_check, struct cell_data **table);
    void print_cygan_table(Matrix2Dim<int> *obj_matrix, struct cell_data **table);
    bool num_of_chambers_within_given_time(int num_of_vertexes, struct cell_data **table, int starting_vertex, int max_time_given, int *cost, int *num_of_chambers, std::vector<int> *path);

public:
    bool algorithm_start(Matrix2Dim<int> initial_matrix, int starting_vertex, int max_time_given);
};

#endif