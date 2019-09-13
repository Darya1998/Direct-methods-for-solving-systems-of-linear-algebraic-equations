#ifndef _QR_
#define _QR_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


using namespace std;
#define sqr(x) x*x 



template <typename Type>
std::vector<std::vector<Type>>  qr(std::vector<std::vector<Type>> matrix);

template <typename Type>
std::vector<std::vector<Type>> product_rotation_matrix(std::vector<std::vector<Type>> matrix1,std::vector<std::vector<Type>> matrix2, int str, int row);

template <typename Type>
std::vector<std::vector<Type>> product_triangle(std::vector<std::vector<Type>> matrix1,std::vector<std::vector<Type>> matrix2);

template <typename Type>
std::vector<std::vector<Type>> product_triangle(std::vector<std::vector<Type>> matrix1,std::vector<std::vector<Type>> matrix2){
    int new_row = matrix1.size();
    int old_col_matrix1 = matrix1[0].size();
    int new_col = matrix2[0].size();
    int m = matrix2.size() - 1;

    vector<vector<Type>> matrix_product_triangle(new_row, vector<Type>(new_col));
                // cout << "новая матрица" << endl;
                // for (const auto &v : matrix_product_triangle){
                //     for (const auto &n: v){
                //         std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
                //     }
                // std::cout << std::endl;
                // }
            std::cout << std::endl;
    for (int i = 0; i < new_col; i++){
        for (int j = 0; j < new_row; j++){
            matrix_product_triangle[j][i] = 0;
            for (int k = 0; k < old_col_matrix1 - m; k++){
                matrix_product_triangle[j][i] = matrix_product_triangle[j][i] + (matrix1[j][k]*matrix2[k][i]);
            }
        }
        m--;
        if (m < 0){
            m = 0;
        }
    }

    return matrix_product_triangle;

}


// template <typename Type>
// std::vector<std::vector<Type>> product_rotation_matrix(std::vector<std::vector<Type>> matrix1,std::vector<std::vector<Type>> matrix2){
//     int new_row = matrix1.size();
//     int old_col_matrix1 = matrix1[0].size();
//     int new_col = matrix2[0].size();

//     vector<vector<Type>> matrix_product(new_row, vector<Type>(new_col));
//     for (int i = 0; i < new_row; i++){
//         for (int j = 0; j < new_col; j++){
//             matrix_product[i][j] = 0;
//             for (int k = 0; k < old_col_matrix1; k++){
//                 matrix_product[i][j] = matrix_product[i][j] + (matrix1[i][k]*matrix2[k][j]);
//             }
//         }
//     }

//     return matrix_product;
// }

template <typename Type>
std::vector<std::vector<Type>> product_rotation_matrix(std::vector<std::vector<Type>> matrix1,std::vector<std::vector<Type>> matrix2, int str, int row){
    vector<vector<Type>> product_rotation_matrix(matrix2.size(), vector<Type>(matrix2[0]. size()));
    for (int i = 0; i < matrix2.size(); i++){
        for (int j = 0; j < matrix2[0].size(); j++){
            product_rotation_matrix[i][j] = matrix2[i][j];
        }
    }
    for (int k = 0; k < matrix2[0]. size(); k ++){
        product_rotation_matrix[str][k] = matrix2[str][k] * matrix1[str][str] + matrix2[row][k] * matrix1[str][row];
        product_rotation_matrix[row][k] = matrix2[row][k] * matrix1[str][str] - matrix2[str][k] * matrix1[str][row];
    }

    return product_rotation_matrix;
}



template <typename Type>
std::vector<std::vector<Type>>  qr(std::vector<std::vector<Type>> matrix){
    Type c, s;

    // СОЗДАНИЕ ЕДИНИЧНОЙ МАТРИЦЫ (КВАДРАТНАЯ)
    vector<vector<Type>> MatrixInitial(matrix.size(), vector<Type>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++){ // 2 + MATRIX.SIZE() * (2 + 
        for (int j = 0; j < matrix.size(); j++){// 2 + MATRIX.SIZE() * (2 + 
            if (i == j){ // 2
                MatrixInitial[i][j] = 1; // 3 
            }
            else{
                MatrixInitial[i][j] = 0; // 3
            }
        }
    }



    for (int i = 0; i < matrix[0].size() - 2; i++){ // 5 + (matrix.size() - 2) * (2 +
        for(int j = 1 + i; j < matrix.size(); j++){ // 4 + matrix.size() * (3+ 
            if (fabs(matrix[i][i]) + fabs(matrix[j][i]) != 0){ // 9
                c = matrix[i][i]/sqrt(sqr(matrix[i][i])+ sqr(matrix[j][i])); // 12 +
                s = matrix[j][i]/sqrt(sqr(matrix[i][i])+ sqr(matrix[j][i])); // 12 +

                for (int m = i; m < matrix[i].size(); m++){ // 4 + matrix.size() * (2 +
                    Type temp = matrix[i][m];// 3 +
                    matrix[i][m] = c * temp + s * matrix[j][m]; // 8 + 
                    matrix[j][m] = -s * temp + c * matrix[j][m]; // 8
                }

                // 5 + (matrix.size() - 2) * (2 + 4 + matrix.size() * (3 + 9 + 12 + 12 + 4 + matrix.size() * (2 + 8 + 8))))

                //matrix.size() = n;
                // matrix[0].size() = n + 1;

                //Sum_{i = 0}^{n-1} * Sum_{j = i + 1}^{n  - 1} * 4 + Sum_{i = 0}^{n-1} * Sum_{i = j + 1}^{n -1} * Sum{m = i}^{n - 1} * 4

                // Sum_{j = 1}^{n} * (n-1) * 4 - j + Sum_{j = 1}^{n} * Sum_{m = 0}^{n-1} - i + (n-1) * 4 - j 

                


                 //СОЗДАНИЕ НОВОЙ МАТРИЦЫ 
                vector<vector<Type>> MatrixNew(matrix.size(), vector<Type>(matrix[0].size() - 1));
                for (int i = 0; i < matrix.size(); i++){
                    for (int j = 0; j < matrix[0].size() - 1; j++){
                        if (j == i){
                            MatrixNew[i][j] = 1;
                        }
                        else MatrixNew[i][j] = 0;
                    }
                }

                MatrixNew[i][i] = c;
                MatrixNew[j][j] = c;
                MatrixNew[i][j] = s;
                MatrixNew[j][i] = -s;

            //ПЕРЕМНОЖЕНИЕ МАТРИЦ ПОВОРОТА
            MatrixInitial = product_rotation_matrix(MatrixNew, MatrixInitial, i , j); 
            }
        }
           
    }

    cout << "матрица T" << endl;
    for (const auto &v : MatrixInitial){
        for (const auto &n: v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    cout << "матрица R" << endl;
    for (const auto &v : matrix){
        for (const auto &n: v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //  транспонированная матрица к матрице Т
    for (int i = 0; i < MatrixInitial.size(); i++){
        for (int j = i; j < MatrixInitial.size(); j++){
            std::swap(MatrixInitial[i][j], MatrixInitial[j][i]);
        }
    }

    cout << "матрица Q" << endl;
    for (const auto &v : MatrixInitial){
        for (const auto &n: v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::vector<std::vector<Type>> checking_matrix;

    checking_matrix = product_triangle(MatrixInitial, matrix);

    cout << "Матрица А = QR" << endl;
    for (const auto &v : checking_matrix){
        for (const auto &n: v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return matrix;
}

#endif