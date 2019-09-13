#ifndef _CALCULATION_PARTIAL_CHOICE_
#define _CALCULATION_PARTIAL_CHOICE_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

const float  EPSILON = 1e-6;

template <typename Type>
std::vector<std::vector<Type>>  calculation_partial_choice(std::vector<std::vector<Type>> matrix);

template <typename Type>
std::vector<std::vector<Type>>  calculation_partial_choice(std::vector<std::vector<Type>> matrix){
for (int i = 0; i < matrix.size() - 1; i++ ){
    
    for (int j = 1 + i; j < matrix.size(); j ++){
        vector<Type> temp_vector;
        
        //ПЕРЕСТАНОВКА СТРОК(ЧАСТИЧНЫЙ ВЫБОР ГЛАВНОГО ЭЛЕМЕНТА)
        if (fabs(matrix[j][i]) > fabs(matrix[i][i])){
            for (int k = 0; k < matrix[0].size(); k++){
                temp_vector.push_back(matrix[j][k]);
            }

            for (int n = 0; n < matrix[0].size(); n++){
                matrix[j][n] = matrix[i][n];
                matrix[i][n] = temp_vector[n];
            }
        }
    }

    // ПРИВЕДЕНИЕ МАТРИЦЫ К ВЕРХНЕТРЕУГОЛЬНОМУ ВИДУ
    for (int j = 1 + i; j < matrix.size(); j ++){
        Type temp = matrix[j][i];
        for (int m = 0; m < matrix[0].size(); m++){
            matrix[j][m] += - matrix[i][m] * temp/ matrix[i][i];
            
            if (fabs(matrix[j][m]) < EPSILON){
                matrix[j][m] = 0;
            }
        }

    }

}

    // for (const auto &v : matrix){
    //     for (const auto &n: v){
    //         std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;
    return matrix;
};

#endif
