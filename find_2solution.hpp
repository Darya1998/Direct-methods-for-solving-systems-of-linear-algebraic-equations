#ifndef _FIND_2SOLUTION_
#define _FIND_2SOLUTION_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename Type>
std::vector<LOCATION_NUMBER<Type>>find_2solution(std::vector<std::vector<LOCATION_NUMBER<Type>>> matrix);

template <typename Type>
std::vector<LOCATION_NUMBER<Type>> find_2solution(std::vector<std::vector<LOCATION_NUMBER<Type>>> matrix){
    vector <LOCATION_NUMBER<Type>> solution;
    for (int i = 0; i < matrix.size(); i++){
        if (fabs(matrix[i][i].number) <= EPSILON){
            cout << "Матрица системы вырождена. Система несовместна" << endl;
            return solution;
        }
    }
    solution.resize(matrix.size());
    for (int i = 0; i < matrix.size(); i++){
        solution[i].number = 0;
    }

    Type root, combination_roots;
    for (int i = matrix.size() - 1; i >= 0; i--){
        combination_roots = 0;
        for (int j = i + 1; j <= matrix.size() - 1; j ++){
            combination_roots += matrix[i][j].number * solution[j].number;
        }
        root = (matrix[i][matrix[0].size() - 1].number - combination_roots)/matrix[i][i].number;
        int root_j = matrix[i][i].column;
        cout << root_j << endl;
        solution[i].number = root;
        solution[i].column = root_j;
    }

    vector<Type> solution2(solution.size());

    for (int i = 0 ; i < solution.size();i++){
        cout << solution[i].column << " " << solution[i].number << endl;
        solution2[solution[i].column] = solution[i].number;

    }

    cout << "solution" << endl;
    for (const auto &n:solution2){
        cout << n << " " << endl;
    }
    return solution;
} 


#endif