#ifndef _CONDITION_NUMBER_
#define _CONDITION_NUMBER_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename Type>
std::vector<std::vector<Type>> inversion(std::vector<std::vector<Type>> matrix);

template <typename Type>
Type condition_number(std::vector<std::vector<Type>> matrix, std::vector<std::vector<Type>> matrix_triangle);




template <typename Type>
std::vector<std::vector<Type>> inversion(std::vector<std::vector<Type>> matrix){
    //копия матрица А
    std::vector<std::vector<Type>> init_matrix(matrix.size(), vector<Type> (matrix[0].size() - 1));
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size() - 1; j++){
            init_matrix[i][j] = matrix[i][j];
        }
    }

    int N = init_matrix.size();
    //Обратная матрица, в которую будем записывать вектора решений
    std::vector<std::vector<Type>> invers_matrix(matrix.size(), vector<Type> (matrix[0].size() - 1));

    std::vector<std::vector<Type>> single_matrix(matrix.size(), vector<Type> (matrix[0].size() - 1));

     std::vector<std::vector<Type>> matrix_new(matrix.size(), vector<Type> (matrix[0].size()));



    //ЕДЕНИЧНАЯ МАТРИЦА 
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i == j){
                single_matrix[i][j] = 1;
            }
            else{
                single_matrix[i][j] = 0;
            }
        }
    }



    std::vector<Type> solution_temp(matrix.size());//вектор решения

    bool error1 = true;

    for (int k = 0; k < matrix.size(); k ++){//кол-во использования матода гаусса
        //Записываем в правую часть столбец единичной матрицы
        for (int i = 0; i < matrix.size(); i ++){
            matrix[i][matrix[0].size() - 1] = single_matrix[i][k];
        }
        cout << "\n Записываем в правую часть столбец единичной матрицы" << endl;
        for (const auto &v : matrix){
            for (const auto &n: v){
                std::cout << left << setw(15)<< n << "\t";
            }
            std::cout << std::endl;
        }
        cout << endl << endl;


        //решаем СЛАУ
        matrix_new = calculation_partial_choice(matrix);

        cout << endl << endl;
        solution_temp = find_solution(matrix_new, error1);

        //ЗАПИСЫВАЕМ ВЕКТОР РЕШЕНИЯ В СТОЛБЕЦ МАТРИЦЫ
        for (int j = 0; j < matrix.size(); j ++){
            invers_matrix[j][k] = solution_temp[j];
        }
    }

    return invers_matrix;
}



template <typename Type>
Type  condition_number(std::vector<std::vector<Type>> matrix, std::vector<std::vector<Type>> matrix_triangle){
    for (int i = 0; i < matrix_triangle.size(); i++){
        if (matrix_triangle[i][i] == 0){
            cout << "Матрица вырождена. Число обусловленности равно бесконечности" << endl;
            return 1;
        }
    }

        //копия матрица А
    std::vector<std::vector<Type>> init_matrix(matrix.size(), vector<Type> (matrix[0].size() - 1));
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size() - 1; j++){
            init_matrix[i][j] = matrix[i][j];
        }
    }

    Type max_row1 = 0;
    Type max_col1 = 0;
    Type max_row2 = 0;
    Type max_col2 = 0;
    Type temp_max_row1, temp_max_col1, temp_max_row2, temp_max_col2 ;


    //НОРМА А
    for (int i = 0; i < matrix.size(); i++){
        temp_max_row1 = 0;
        for (int j = 0; j < matrix[0].size() - 1; j ++){
            temp_max_row1 += fabs(matrix[i][j]);
        }

        if (temp_max_row1 > max_row1){
            max_row1 = temp_max_row1;
        }
    }


    // ПОИСК ОБРАТНОЙ МАТРИЦЫ


    auto inverse = inversion(matrix);
       cout << "\n ПЕрвоначальная матрица A" << endl;
    for (const auto &v : init_matrix){
        for (const auto &n: v){
            std::cout << left << setw(15)<< n << "\t";
        }
        std::cout << std::endl;
    }
    cout << endl << endl;
    
    cout << "\n Обратная матрица A^(-1)" << endl;
        for (const auto &v : inverse){
        for (const auto &n: v){
            std::cout << left << setw(15)<< n << "\t";
        }
        std::cout << std::endl;
    }
    cout << endl << endl;



    //Умножение оператора А и обратного
    std::vector<std::vector<Type>> product(init_matrix.size(), vector<Type>(init_matrix.size()));
    double result;
    for (int i = 0; i < init_matrix. size(); i++){
        for (int j = 0; j < init_matrix.size(); j++){
            result = 0;
            for (int k = 0; k < init_matrix.size(); k++){
                result += init_matrix[i][k] * inverse[k][j];
            }
            product[i][j] = result;

        }
    }






    cout << "Проверка" << endl;

    for (const auto &v : product){
        for (const auto &n: v){
            std::cout << left << setw(15)<< n << "\t";
        }
        std::cout << std::endl;
    }
    cout << endl << endl;


    // НОРМА ОБРАТНОГО ОПЕРАТОРА А
    for (int i = 0; i < inverse.size(); i++){
        temp_max_row2 = 0;
        for (int j = 0; j < inverse[0].size(); j ++){
            temp_max_row2 += fabs(inverse[i][j]);
        }

        if (temp_max_row2 > max_row2){
            max_row2 = temp_max_row2;
        }
    }

    cout << "БЕСКОНЕЧНОСТЬ - НОРМА(кубическая)" << endl;
    cout << setprecision(6) << fixed << max_row1 * max_row2 << endl;


    //1 - НОРМА
    cout << "1 - НОРМА(октаэдрическая)" << endl;
    for (int i = 0; i < matrix.size(); i++){
        temp_max_col1 = 0;
        for (int j = 0; j < matrix[0].size() - 1; j ++){
            temp_max_col1 += fabs(matrix[j][i]);
        }

        if (temp_max_col1 > max_col1){
            max_col1 = temp_max_col1;
        }
    }


    // 1- НОРМА ОБРАТНОГО ОПЕРАТОРА А
    for (int i = 0; i < inverse.size(); i++){
        temp_max_col2 = 0;
        for (int j = 0; j < inverse[0].size(); j ++){
            temp_max_col2 += fabs(inverse[j][i]);
        }

        if (temp_max_col2 > max_col2){
            max_col2 = temp_max_col2;
        }
    }

    cout << max_col1 * max_col2 << endl;

}


#endif