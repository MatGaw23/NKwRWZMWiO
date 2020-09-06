#include <iostream>
#include <vector>
#include <assert.h>
#include "algorithm_core.hpp"
#include "matrix.hpp"


// bool Algorithm :: somsiad_function(Matrix2Dim<int> *obj_matrix, int current_row, struct cell_data **table, bool skip_value_above)
// {
//     int num_of_vertexes = obj_matrix->dim_column;

//     for (int j = 0; j < num_of_vertexes; j++)
//     {
//         int lowest_somsiad_cost_vertex_number = 0;
//         int lowest_somsiad_cost = 999;
//         int row_to_compute = j;
        
//         for(int k = 0; k < num_of_vertexes; k++)
//         {
//             int temp_value = obj_matrix->get_cell(row_to_compute, k);
//             if (lowest_somsiad_cost > temp_value && (temp_value != 0))
//             {
//                 lowest_somsiad_cost = temp_value;
//                 lowest_somsiad_cost_vertex_number = k;
//             }
//         }
//         if (lowest_somsiad_cost == 999)
//         {
//             std::cout<<"FUCK. Brak somsiadów"<<std::endl;
//             return false;
//         }

//         table[current_row, j]->distance = lowest_somsiad_cost;
//         table[current_row, j]->history.push_back(lowest_somsiad_cost_vertex_number);
//         return true;
//     }    
// }


//TODO: todo: ToDo: Todo:
// somsiad function - dla current_row, sprawdz wszystkich sasiadow w tabeli POWYZEJ (zmien to), znajdz tego co jest najtanszy 
//+ wpisz do obecnej komórki z której to wywołujemy ( też do zmiany, przerobienia. elo.)
bool Algorithm :: somsiad_function(Matrix2Dim<int> *obj_matrix, int current_row, struct cell_data **table, bool skip_value_above)
{
    int num_of_vertexes = obj_matrix->dim_column;
    int lowest_somsiad_cost_vertex_number = 0;
    int lowest_somsiad_cost = 999;
        
    for(int k = 0; k < num_of_vertexes; k++)
    {
        int temp_value = obj_matrix->get_cell(current_row, k);

        if (skip_value_above)
            continue;

        if (lowest_somsiad_cost > temp_value && (temp_value != 0))
        {
            lowest_somsiad_cost = temp_value;
            lowest_somsiad_cost_vertex_number = k;
        }
    }
    if (lowest_somsiad_cost == 999)
    {
        std::cout<<"FUCK. Brak somsiadów"<<std::endl;
        return false;
    }

    table[current_row, j]->distance = lowest_somsiad_cost;
    table[current_row, j]->history.push_back(lowest_somsiad_cost_vertex_number);
    return true;
}

bool Algorithm :: history_is_the_same_chamber(int current_row, struct cell_data **table)
{
    assert(current_row <= 0);

    int num_of_vertexes = obj_matrix->dim_column;
    int upper_row = current_row - 1;

    for (int i = 0; i < num_of_vertexes; i++)
    {
        for (int j = 0; j < table[upper_row][i].history.size(); j++)
        {
            if (table[upper_row][i].history[j] == current_row)
                return true;
        }
    }

    return false;
}

void Algorithm :: update_costs_in_current_row(int current_row, struct cell_data **table)
{
    int num_of_vertexes = obj_matrix->dim_column;
    int upper_row = current_row - 1;

    for(int i = 0; i < num_of_vertexes; i++)
    {
        if (table[current_row][i].history.size() == upper_row)
        {
            int last_vector_element = table[current_row][i].history.size() - 1;
            int last_column_from_history = table[current_row][i].history[last_vector_element];
            table[current_row][i].distance += table[upper_row][last_column_from_history].distance;
        }
    }
}

bool Algorithm :: algorithm_start(Matrix2Dim<int> initial_matrix, int starting_vertex)
{
    obj_matrix = &initial_matrix;   //macierz sasiedztwa
    if (obj_matrix == NULL)
        return false;

    std::cout<<"Started. Starting vertex: "<<starting_vertex<<std::endl;

    num_of_vertexes = obj_matrix->dim_column; //ilosc wierzcholkow

    struct cell_data table[num_of_vertexes][num_of_vertexes];

    //Inicjalizacja pierwszego wiersza zerami       //tablica [wiersze][kolumny]
    for(int i=0; i<num_of_vertexes; i++)
        table[0][i].distance = 0;

    //Punkt 3 -> dokument Cygana
    //sprawdzanie wszystkich sasiadow komory nr. 1 (if (somsiad_vertex_distance > 0)) -- i bierzemy najtanszego somsiada
    //zapisujemy najnizszy koszt i historie dojscia do tego pola w tabeli (w tym wypadku 2,1) - u nas (1,0)
    //powtórka dla pola 2,2; potem 2,3 itd. do konca wiersza

    int current_row = 1;
    Algorithm :: somsiad_function(obj_matrix, current_row, (struct cell_data **)table); // dla wiersza 2 -> mamy somsiadów

    //Tutaj punkt 4
    //jestesmy w wierszu 3,1. Nie sprawdzamy pola w wierszu powyzej, sprawdzamy pozostale.
        // Jezeli w ich historii jest nasza komorka - pomijamy
        // Jezeli nie jestesmy sasiadem tego wierzcholka, pomijamy.
    // w wypadku wiersz 3,1 jedyna komorka jest 2,2 - liczymy koszt calej historii ==  koszt w polu 2,2(table[1,1].distance) + koszt z wierzchołka z tego pola
        // czytaj - koszt w polu niebieskim + koszt przejscia z komory 2 do 1 --> 1 + 3
    int current_row = 2;
    for (int i = 0; i < num_of_vertexes; i++)
    {
        //funkcja do sprawdzenia czy w historii znajduje sie nasza obecna komórka (i) jak tak, to skipuj
        if (Algorithm :: history_is_the_same_chamber(i, (struct cell_data **)table))
            continue;

        Algorithm :: somsiad_function(obj_matrix, current_row, (struct cell_data **)table, true);

    }
    
    Algorithm :: update_costs_in_current_row(current_row, (struct cell_data **)table); //updatenij koszta w obecnym wierszu
}



int Algorithm :: get_max_num_of_chambers(int starting_vertex, int max_time)
{

}


void Algorithm :: algorithm_cleanup(void)
{

}
