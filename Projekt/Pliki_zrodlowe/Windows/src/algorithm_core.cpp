#include <iostream>
#include <vector>
#include <assert.h>
#include "algorithm_core.hpp"
#include "matrix.hpp"

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

        // nie mozemy sprawdzic samego siebie, wiec to skipujemy
        if (skip_table_value_above && current_vertex_check == current_table_col)
            continue;

        //sprawdzacz historii. -> sprawdz w historii, w poprzednim wierszu tabelii czy historia dla danego sprawdzanego wierzchołka nie zawiera już czasem
        //naszej komórki - czyli naszego w sumie wierzchołka
        if (check_history(upper_row, current_vertex_check, current_table_col, table))
            continue;

        //sprawdzamy jaki jest koszt tego sasiada, jezeli jest nizszy niz poprzednich, wstawimy wartosc i updateniemy jego numer
        if (lowest_somsiad_cost > temp_value)
        {
            lowest_somsiad_cost = temp_value;
            lowest_somsiad_cost_vertex_number = current_vertex_check;
        }
    }

    //jeżeli nie znalezlismy sąsiada, false
    if (lowest_somsiad_cost == 999)
    {
        // std::cout<<"Brak wierzchołka"<<std::endl;
            
        table[current_table_row][current_table_col].distance = -1;
        table[current_table_row][current_table_col].history.clear();

        for(auto i = 0; i < num_of_vertexes; i++)
            table[current_table_row][current_table_col].history.push_back(i);

        return false;
    }

    table[current_table_row][current_table_col].distance = lowest_somsiad_cost;
    table[current_table_row][current_table_col].history.push_back(lowest_somsiad_cost_vertex_number);
    
    //przejsc do tego co jest w historii -> sprawdzic jego historie, przepisujemy jego historie do naszej.
    //kopiowanie historii poprzedniego
    std::vector<int> vector = table[current_table_row - 1][lowest_somsiad_cost_vertex_number].history;
    for (auto& a: vector)
        table[current_table_row][current_table_col].history.push_back(a);

    table[current_table_row][current_table_col].distance += table[current_table_row - 1][lowest_somsiad_cost_vertex_number].distance;

    return true;
}

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

bool Algorithm :: algorithm_start(Matrix2Dim<int> initial_matrix, int starting_vertex, int max_time_given)
{
    obj_matrix = &initial_matrix;   //macierz sasiedztwa
    if (obj_matrix == NULL)
        return false;

    int num_of_vertexes = obj_matrix->dim_column; //ilosc wierzcholkow

    //alokowanie tablicy
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
        //Tutaj punkt 4
    //jestesmy w wierszu 3,1. Nie sprawdzamy pola w wierszu powyzej, sprawdzamy pozostale.
        // Jezeli w ich historii jest nasza komorka - pomijamy
        // Jezeli nie jestesmy sasiadem tego wierzcholka, pomijamy.
    // w wypadku wiersz 3,1 jedyna komorka jest 2,2 - liczymy koszt calej historii ==  koszt w polu 2,2(table[1,1].distance) + koszt z wierzchołka z tego pola
        // czytaj - koszt w polu niebieskim + koszt przejscia z komory 2 do 1 --> 1 + 3

    for(auto current_row = 1; current_row < num_of_vertexes; current_row++)
    {
        for (int column_number = 0; column_number < num_of_vertexes; column_number++)
            Algorithm :: somsiad_function(obj_matrix, current_row, column_number, table, false); // dla wiersza 2 -> mamy somsiadów
    }
    
    print_cygan_table(obj_matrix, table);

    int cost, num_of_chambers = 0;
    std::vector<int> path;
    Algorithm :: num_of_chambers_within_given_time(num_of_vertexes, table, starting_vertex, max_time_given, &cost, &num_of_chambers, &path);

    //cleanup tablicy
    for (int i = 0; i < num_of_vertexes; i++)
        delete[] table[i];

    delete[] table;

    return true;
}

bool Algorithm :: num_of_chambers_within_given_time(int num_of_vertexes, struct cell_data **table, int starting_vertex, int max_time_given, int *cost, int *num_of_chambers, std::vector<int> *path)
{
    *cost = 999;
    bool found = false;
    starting_vertex--;
    for(auto checked_row = (num_of_vertexes-1) ; checked_row > 0; checked_row--)
    {
        for (auto iteration_over_columns = 0; iteration_over_columns < num_of_vertexes; iteration_over_columns++)
        {
            if ((iteration_over_columns == starting_vertex) || (table[checked_row][iteration_over_columns].history.back() == starting_vertex))
            {
                if ((table[checked_row][iteration_over_columns].distance <= max_time_given) && (table[checked_row][iteration_over_columns].distance > 0))
                {
                    if (table[checked_row][iteration_over_columns].history.size()+1 <= path->size())
                        continue;

                    if (table[checked_row][iteration_over_columns].distance >= *cost)
                        continue;

                    *cost = table[checked_row][iteration_over_columns].distance;
                    *num_of_chambers = checked_row+1;
                    *path = table[checked_row][iteration_over_columns].history;
                    path->insert(path->begin(), 1, iteration_over_columns);
                    std::cout<<std::endl<<"Wyniki -> koszt: "<<*cost<<", Ilosc komor kosmitow: "<<*num_of_chambers<<", Sciezka: ";
                    //std::cout<<++starting_vertex<<",";
                    for (auto& a: *path)
                    {
                        std::cout<<a + 1<<",";
                    }
                    std::cout<<std::endl<<std::endl;
                    found = true;
                    // return true;
                }
            }
        }
    }
    //sprawdzac od dolu czy jakis jeden z nich ma czas mniejszy od max_time given
    //-> po prostu sprawdzac tylko kolumne z wierzcholkiem z ktorego zaczynamy -- update: sprawdzamy tez inne kolumny. 
        //Jezeli w ich historii na poczatku albo koncu jest startting_vertex to tez go uwzgledniamy
    if (found)
        return true;

    std::cout<<std::endl<<"W takim czasie nawet nie dojdziesz do drugiej komory!"<<std::endl<<std::endl;
    return false;
}

void Algorithm :: print_cygan_table(Matrix2Dim<int> *obj_matrix, struct cell_data **table)
{
    int table_dimension = obj_matrix->dim_column;

    std::cout<<std::endl<<"==================================================================================================="<<std::endl;

    for (int j = 0; j < table_dimension; j++)
    {
        for (int i = 0; i < table_dimension; i++)
        {
            // DISTANCE (HISTORY, ...)
            if (table[j][i].distance != -1)
            {
                std::cout<<i+1<<": "<<table[j][i].distance<<" ";
                std::cout<<"(";
                for (auto& a : table[j][i].history)
                    std::cout<<a + 1<<",";
                for (auto b = 0; b < (table_dimension - table[j][i].history.size()); b++)
                {
                    if (b == (table_dimension - table[j][i].history.size() - 1))
                        std::cout<<"-";
                    else
                       std::cout<<"-,"; 
                }

                std::cout<<")     ";
            }
            else
            {
                std::cout<<i+1<<": "<<"X (";
                for (auto b = 0; b < table_dimension ; b++)
                {
                    if (b == (table_dimension- 1))
                        std::cout<<"-";
                    else
                       std::cout<<"-,"; 
                }
                std::cout<<")     ";
            }
        }
        std::cout<<std::endl<<"==================================================================================================="<<std::endl;
    }

}   
