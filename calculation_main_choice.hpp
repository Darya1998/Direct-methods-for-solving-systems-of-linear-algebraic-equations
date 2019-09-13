#ifndef _CALCULATION_MAIN_CHOICE_
#define _CALCULATION_MAIN_CHOICE_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename Type>
struct LOCATION_NUMBER {
    Type number;
    int row;
    int column;
};

template <typename Type>
std::vector<std::vector<LOCATION_NUMBER<Type>>>  calculation_main_choice(std::vector<std::vector<Type>> matrix){
    std::vector<std::vector<LOCATION_NUMBER<Type>>> matrix_of_struct(matrix.size());
    for (int i = 0; i < matrix.size(); i++){
        std::vector<LOCATION_NUMBER<Type>> data(matrix[0].size());
        for (int j = 0; j < matrix[0].size(); j++){
            data[j].number = matrix[i][j];
            data[j].row = i;
            data[j].column = j;
        }
        matrix_of_struct[i] =data;
    }

    for (int i = 0; i < matrix_of_struct.size() - 1; i++){
        int max_i = i;
        int max_j = i;
        for (int j = i; j < matrix_of_struct.size(); j ++){
            for (int k = i; k < matrix_of_struct.size(); k++){          
                if (fabs(matrix_of_struct[j][k].number) > fabs(matrix_of_struct[max_i][max_j].number)){
                    max_i = j;
                    max_j = k;
                }
            }
        }
        LOCATION_NUMBER<Type> max = matrix_of_struct[max_i][max_j]; 

        std::vector<LOCATION_NUMBER<Type>> temp_column(matrix_of_struct.size());
        //ПЕРЕСТАНОВКА СТРОК
        std::swap(matrix_of_struct[i], matrix_of_struct[max_i]);
        
        //ПЕРЕСТАНОВКА СТОЛБЦОВ
        for (int n = 0; n < matrix_of_struct.size(); n ++){
            temp_column[n] = matrix_of_struct[n][i];
            matrix_of_struct[n][i] = matrix_of_struct[n][max_j];
            matrix_of_struct[n][max_j] = temp_column[n];            
        }

        for (int j = 1 + i; j < matrix_of_struct.size(); j ++){
            LOCATION_NUMBER<Type> temp = matrix_of_struct[j][i];
            for (int m = 0; m < matrix_of_struct[0].size(); m++){
                matrix_of_struct[j][m].number += - matrix_of_struct[i][m].number * temp.number/ matrix_of_struct[i][i].number;
                
                if (fabs(matrix_of_struct[j][m].number) < EPSILON){
                    matrix_of_struct[j][m].number = 0;
                }
            }

        }
    }

    for (const auto &v:matrix_of_struct){
        for (const auto &n:v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n.number << "\t";
        }
        std::cout << std::endl;
    }


    return matrix_of_struct;
}




#endif