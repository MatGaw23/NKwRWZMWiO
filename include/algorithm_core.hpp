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

public:
    int num_of_vertexes = 0;

    bool somsiad_function(Matrix2Dim<int> *obj_matrix, int current_row, struct cell_data **table, bool skip_value_above);
    void update_costs_in_current_row(int current_row, struct cell_data **table);
    bool history_is_the_same_chamber(int current_row, struct cell_data **table);
    int get_max_num_of_chambers(int starting_vertex, int max_time);
    bool algorithm_start(Matrix2Dim<int> initial_matrix, int starting_vertex);
    void algorithm_cleanup(void);
};

















// struct vertex_data
// {
//     bool visited = false;
//     int value = -1;
//     int last_one = -1;
//     int distance = -1;
// };

// class DFS
// {
// private:
//     Matrix2Dim<int> *obj_matrix = NULL;
//     int num_of_vertexes = 0;
//     // int starting_vertex = -1;

//     int longest_path_with_starting_vertex(int starting_vertex);
//     void get_neighbour_coords(vertex_data *tab, int col_in, int row_in, int* col_out, int* row_out);
//     int longest_path(void);
//     vertex_data* dfs(int start);
//     void visit_node(vertex_data *tab, int u, int distan);
//     int get_starting_vertex_position(int col, int row);
//     void count_vertexes();

// public:
//     bool dfs_start(Matrix2Dim<int> initial_matrix, int starting_position_col, int starting_position_row);
//     void dfs_cleanup(void);
// };

#endif