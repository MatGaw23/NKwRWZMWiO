#include <iostream>
#include <vector>
#include <assert.h>
#include "algorithm_core.hpp"
#include "matrix.hpp"

//TODO: todo: ToDo: Todo:
// somsiad function - dla current_row, sprawdz wszystkich sasiadow w tabeli (komory) POWYZEJ (zmien to), znajdz tego co jest najtanszy 
//+ wpisz do obecnej komórki z której to wywołujemy ( też do zmiany, przerobienia. elo.)

//ta funkcja jest uposledzona o brak sprawdzania historii.
bool Algorithm :: somsiad_function(Matrix2Dim<int> *obj_matrix, int current_table_row, int current_table_col, struct cell_data **table, bool skip_table_value_above)
{
    int num_of_vertexes = obj_matrix->dim_column;
    int lowest_somsiad_cost_vertex_number = 0;
    int lowest_somsiad_cost = 999;
        
    //sprawdzamy sąsiadów dla danego wierzchołka określonego przez current_table_column
    for(int current_vertex_check = 0; current_vertex_check < num_of_vertexes; current_vertex_check++)
    {
        int upper_row = current_table_row - 1;
        if (upper_row < 0)
            upper_row = 0;

        int temp_value = obj_matrix->get_cell(current_table_col, current_vertex_check);
        
        // to nie jest sąsiad.
        if (temp_value == 0)
            continue;

        //jeżeli vertex sprawdzany (trzeba zobaczyc na ilosc kolumn - kolejna zmienna, do przerobienia, todo.)
        // nie mozemy sprawdzic samego siebie, wiec to skipujemy
        if (skip_table_value_above && current_vertex_check == current_table_col)
            continue;

        //sprawdzacz historii. -> sprawdz w historii, w poprzednim wierszu tabelii czy historia dla danego sprawdzanego wierzchołka nie zawiera już czasem
        //naszej komórki - czyli naszego w sumie jebanego wierzchołka
        if (check_history(upper_row, current_vertex_check, current_table_col, table))
            continue;

        //sprawdzamy jaki jest koszt tego sasiada, jezeli jest nizszy niz poprzednich, wstawimy wartosc i updateniemy jego numer
        if (lowest_somsiad_cost > temp_value)
        {
            lowest_somsiad_cost = temp_value;
            lowest_somsiad_cost_vertex_number = current_vertex_check;
        }
    }

    //jeżeli nie znalezlismy sąsiada, FUCK
    if (lowest_somsiad_cost == 999)
    {
        std::cout<<"FUCK. Brak somsiadów"<<std::endl;
        return false;
    }


    table[current_table_row][current_table_col].distance = lowest_somsiad_cost;
    table[current_table_row][current_table_col].history.push_back(lowest_somsiad_cost_vertex_number);
    



    //przejsc do tego co jest w historii -> sprawdzic jego historie, przepisujemy jego historie do naszej.
    //kopiowanie historia poprzedniego
    std::vector<int> vector = table[current_table_row - 1][lowest_somsiad_cost_vertex_number].history;
    for (auto& a: vector)
        table[current_table_row][current_table_col].history.push_back(a);

    table[current_table_row][current_table_col].distance += table[current_table_row - 1][lowest_somsiad_cost_vertex_number].distance;

    return true;
}

// funkcja przyjmuje wiersz w którym sprawdza, czy w danej historii wierzchołka column_to_check nie ma czasem vertex_to_check. Jezeli jest, zwraca true
bool Algorithm :: check_history(int row_to_check, int column_to_check, int vertex_to_check, struct cell_data **table)
{
    assert(row_to_check >= 0);
    assert(column_to_check >= 0);
    
    //pole zaraz nad nami
    int history_check_size = table[row_to_check][column_to_check].history.size();
    for (int j = 0; j < history_check_size; j++)
    {
        if (table[row_to_check][column_to_check].history[j] == vertex_to_check)
            return true;
    }

    return false;
}


// #include <algorithm>
// #include <vector>

// if ( std::find(vec.begin(), vec.end(), item) != vec.end() )
//    do_this();
// else
//    do_that();

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

    //struct cell_data table[num_of_vertexes][num_of_vertexes];
    auto table = new struct cell_data*[num_of_vertexes];
    for (int i = 0; i < num_of_vertexes; i++)
        table[i] = new struct cell_data[num_of_vertexes];

    //Inicjalizacja pierwszego(zerowego) wiersza zerami       //tablica [wiersze][kolumny]
    for(int i=0; i<num_of_vertexes; i++)
        table[0][i].distance = 0;

    //Punkt 3 -> dokument Cygana
    //sprawdzanie wszystkich sasiadow komory nr. 1 (if (somsiad_vertex_distance > 0)) -- i bierzemy najtanszego somsiada
    //zapisujemy najnizszy koszt i historie dojscia do tego pola w tabeli (w tym wypadku 2,1) - u nas (1,0)
    //powtórka dla pola 2,2; potem 2,3 itd. do konca wiersza

    int current_row = 1;
    for (int column_number = 0; column_number < num_of_vertexes; column_number++)
        Algorithm :: somsiad_function(obj_matrix, current_row, column_number, table, false); // dla wiersza 2 -> mamy somsiadów

        // print_cygan_table(obj_matrix, table);

    //Tutaj punkt 4
    //jestesmy w wierszu 3,1. Nie sprawdzamy pola w wierszu powyzej, sprawdzamy pozostale.
        // Jezeli w ich historii jest nasza komorka - pomijamy
        // Jezeli nie jestesmy sasiadem tego wierzcholka, pomijamy.
    // w wypadku wiersz 3,1 jedyna komorka jest 2,2 - liczymy koszt calej historii ==  koszt w polu 2,2(table[1,1].distance) + koszt z wierzchołka z tego pola
        // czytaj - koszt w polu niebieskim + koszt przejscia z komory 2 do 1 --> 1 + 3
    current_row = 2;
    for (int column_number = 0; column_number < num_of_vertexes; column_number++)
        Algorithm :: somsiad_function(obj_matrix, current_row, column_number, table, true);

        // print_cygan_table(obj_matrix, table);

    current_row = 3;
    for (int column_number = 0; column_number < num_of_vertexes; column_number++)
        Algorithm :: somsiad_function(obj_matrix, current_row, column_number, table, true);

    current_row = 4;
    for (int column_number = 0; column_number < num_of_vertexes; column_number++)
        Algorithm :: somsiad_function(obj_matrix, current_row, column_number, table, true);

    current_row = 5;
    for (int column_number = 0; column_number < num_of_vertexes; column_number++)
        Algorithm :: somsiad_function(obj_matrix, current_row, column_number, table, true);
    
    print_cygan_table(obj_matrix, table);

    // Algorithm :: update_costs_in_current_row(current_row, table); //updatenij koszta w obecnym wierszu
}

int Algorithm :: print_cygan_table(Matrix2Dim<int> *obj_matrix, struct cell_data **table)
{
    int table_dimension = obj_matrix->dim_column;

    for (int j = 0; j < table_dimension; j++)
    {
        for (int i = 0; i < table_dimension; i++)
        {
            // DISTANCE (HISTORY, ...)
            std::cout<<table[j][i].distance<<" ";
            std::cout<<"(";
            for (auto& a : table[j][i].history)
                std::cout<<a + 1<<",";
            std::cout<<") | ";
        }
        std::cout<<std::endl<<"=================================================================="<<std::endl;
    }

}   

int Algorithm :: get_max_num_of_chambers(int starting_vertex, int max_time)
{

}


void Algorithm :: algorithm_cleanup(void)
{

}
