#include <iostream>
#include "algorithm_core.hpp"
#include "matrix.hpp"

void DFS :: count_vertexes(void)
{
    int vertexes = 0;

    for(auto t = 0; t < obj_matrix->dim_row; t++)
        for (auto x = 0; x < obj_matrix->dim_column; x++)
            if (obj_matrix->get_cell(t, x) != 0)
                vertexes++;

    // num_of_vertexes = vertexes;
    num_of_vertexes = obj_matrix->dim_row;
    std::cout<<std::endl<<"number of vertexes: "<<num_of_vertexes<<std::endl;
}

bool DFS :: dfs_start(Matrix2Dim<int> initial_matrix, int starting_position_col, int starting_position_row)
{
    obj_matrix = &initial_matrix;
    if (obj_matrix == NULL)
        return false;


    count_vertexes();
    if (num_of_vertexes < 0)
        return false;


    std::cout<<"Longest path: "<<longest_path()<<std::endl;

    int startvertex = 1;
    std::cout<<"Longest path, starting from "<<startvertex <<" vertex: "<<longest_path_with_starting_vertex(startvertex)<<std::endl;

   
}

// Dziala jedynie dla grafow typu drzewo //
int DFS :: longest_path_with_starting_vertex(int starting_vertex)
{
    int maximum = 0;

    vertex_data *result = dfs(starting_vertex);
    for (int i = 0; i < num_of_vertexes; i++)
    {
        if (result[i].distance > maximum)
        {
            maximum = result[i].distance;
        }
        delete result;
    }
    return maximum;
}


int DFS :: longest_path(void)
{
    int maximum = 0;

    for (int i = 0; i < num_of_vertexes; i++)
    {
        vertex_data *result = dfs(i);
        for (int j = 0; j < num_of_vertexes; j++)
        {
            if (result[j].distance > maximum)
            {
                maximum = result[j].distance;
            }
        }
        delete result;
    }
    return maximum;
}

vertex_data* DFS :: dfs(int start)
{
    vertex_data *tab = new vertex_data[num_of_vertexes];
    if (tab == NULL)
        return NULL;

    visit_node(tab, start, 0);

    for (int i = 0; i < num_of_vertexes; i++) 
        if (!tab[i].visited)
            visit_node(tab, i, 0);

    return tab;
}

void DFS :: visit_node(vertex_data *tab, int v, int distan)
{
    tab[v].visited = true;
    tab[v].distance = distan;

    for (int i = 0; i < num_of_vertexes; i++) 
    {
        if (obj_matrix->get_cell(v, i) > 0 && !tab[i].visited) 
        {
            tab[i].last_one = v;
            visit_node(tab, i, distan + 1);
        }
    }
}


void DFS :: dfs_cleanup(void)
{

}