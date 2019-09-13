#ifndef _FIND_SOLUTION_
#define _FIND_SOLUTION_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename Type>
std::vector<Type> find_solution(std::vector<std::vector<Type>> matrix, bool &error);

template <typename Type>
std::vector<Type> find_solution(std::vector<std::vector<Type>> matrix, bool &error){
    vector <Type> solution;
    int check = 0;
    // for (int i = 0; i < matrix.size(); i ++){
    //     for (int j = 0; j < matrix.size(); j++){
    //         if (matrix[i][j] = matrix_old[i][j]){
    //             check++;
    //         }

    //         if (check == matrix.size() * matrix[0].size())
    //             return solution;
    //     }
    // } 
    for (int i = 0; i < matrix.size(); i++){
        if (fabs(matrix[i][i]) <= EPSILON){
            error = true;
            cout << "Матрица системы вырождена. Система несовместна" << endl;
            return solution;
        }
        error = false;
    }
    solution.resize(matrix.size());
    for (int i = 0; i < matrix.size(); i++){
        solution[i] = 0;
    }

    Type root, combination_roots;
    for (int i = matrix.size() - 1; i >= 0; i--){
        combination_roots = 0;
        for (int j = i + 1; j <= matrix.size() - 1; j ++){
            combination_roots += matrix[i][j] * solution[j];
        }
        root = (matrix[i][matrix[0].size() - 1] - combination_roots)/matrix[i][i];
        solution[i] = root;
    }

    for (const auto &n:solution){
        cout << n << " " << endl;
    }

    return solution;
} 


#endif