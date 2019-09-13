#ifndef _LOWEST_CONDITION_NUMBER_
#define _LOWEST_CONDITION_NUMBER_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

#define sqr(x) x*x 


//норма решения
template <typename Type>
double octahedron_norm_vector(std::vector<Type> vec);

//норма правой части
template <typename Type>
double octahedron_norm_b_vector(std::vector<std::vector<Type>> matrix);

//кубическая норма для вектора правой части
template <typename Type>
double cube_norm_b_vector(std::vector<std::vector<Type>> matrix);

//кубическая норма для решения
template <typename Type>
double cube_norm_vector(std::vector<Type> vec);

double cond (double norm_init_x, double norm_init_b, double norm_error_x, double norm_error_b);

template <typename Type>
void lowest_conditional_number(std::vector<std::vector<Type>> matrix, std::vector<Type> solution);




//норма решения
template <typename Type>
double octahedron_norm_vector(std::vector<Type> vec){
    double octahedron_norm_SOL = 0;
    for (int i = 0; i < vec.size(); i++){
        octahedron_norm_SOL += fabs(vec[i]);
    }
    return octahedron_norm_SOL;
}



//норма правой части
template <typename Type>
double octahedron_norm_b_vector(std::vector<std::vector<Type>> matrix){
    double octahedron_norm_B = 0;
    for (int i = 0; i < matrix.size(); i++){
        octahedron_norm_B += fabs(matrix[i][matrix[0].size() - 1]);
    }

    return octahedron_norm_B;
}
    

//кубическая норма для решения
template <typename Type>
double cube_norm_vector(std::vector<Type> vec){
    double cube_norm_SOL = 0;
    for (int i = 0; i < vec.size(); i++){
        if (fabs(vec[i]) > cube_norm_SOL){
            cube_norm_SOL = fabs(vec[i]);
        }
    }

    return cube_norm_SOL;
}

//кубическая норма для вектора правой части
template <typename Type>
double cube_norm_b_vector(std::vector<std::vector<Type>> matrix){
    double cube_norm_B = 0;
    for (int i = 0; i < matrix.size(); i++){
        if (fabs(matrix[i][matrix[0].size() - 1]) > cube_norm_B){
            cube_norm_B = fabs(matrix[i][matrix[0].size() - 1]);
        }
    }

    return cube_norm_B;
}


double cond (double norm_init_x, double norm_init_b, double norm_error_x, double norm_error_b){
    double relative_error_b = norm_error_b/norm_init_b;
    double relative_error_x = norm_error_x/norm_init_x;
    double low_cond = relative_error_x/relative_error_b;
    return low_cond;
}


template <typename Type>
void lowest_conditional_number(std::vector<std::vector<Type>> matrix, std::vector<Type> solution){
    double octahedron_norm_vect = 0;
    double octahedron_norm_b = 0;
    double cube_norm_vect = 0;
    double cube_norm_b = 0;
    double norm_delta_b_octahedron = 0;
    double norm_delta_b_cube = 0;
    double norm_delta_x_octahedron = 0;
    double norm_delta_x_cube = 0;
    double delta = 0;
    const int amount_tests = 8;
    const double delta1 = 0.01;

    //ОКТАЭДРИЧЕСКАЯ НОРМА
    //cout << "Октаэдрическая норма правой части - ||b||" << endl;
    octahedron_norm_b = octahedron_norm_b_vector(matrix);
   //cout << octahedron_norm_b << endl;
    //cout << "Октаэдрическая норма решения уравнения - ||x||" << endl;
    octahedron_norm_vect = octahedron_norm_vector(solution);
    //cout << octahedron_norm_vect << endl;

    //КУБИЧЕСКАЯ НОРМА
   // cout << "Кубическая норма правой части - ||b||" << endl;
    cube_norm_b = cube_norm_b_vector(matrix);
    //cout << cube_norm_b << endl;
   // cout << "Кубическая норма решения уравнения - ||x||" << endl;
    cube_norm_vect = cube_norm_vector(solution);
    //cout << cube_norm_vect << endl;

    //вектор для подсчета нормы погрешности
    vector<Type> delta_vector_b(matrix.size());
    vector<Type> delta_vector_x(matrix[0].size() - 1);



    //Созание копии матрицы
    vector<vector<Type>> MatrixChanged(matrix.size(), vector<Type>(matrix[0].size()));  
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[0].size(); j++){
            MatrixChanged[i][j] = matrix[i][j];
        }
    }

    vector<double>experiment_octahedron;
    vector<double>experiment_cube;
    double delta_znach;

    for (int k = 0; k < 4; k ++){
        for (int n = 0; n < 2; n ++){
            vector<double> delta_vector_b; //Вектор погрешностей
            delta_znach = pow(-1, n) * delta1;
            MatrixChanged[k][MatrixChanged[0].size() - 1] += delta_znach;
            delta_vector_b.push_back(delta_znach);

            //ПОСЧИТАМ ||delta(b)||.Октаэдрическая норма
            norm_delta_b_octahedron = octahedron_norm_vector(delta_vector_b);
                

            //ПОСЧИТАМ ||delta(b)||. Кубическая норма
            norm_delta_b_cube = cube_norm_vector(delta_vector_b);

            //Найдем решение уравнения методом Гаусса
            vector<vector<Type>> MatrixChangedNew;
            vector<Type> solution_with_delta;
            bool error = false;

            MatrixChangedNew = calculation_partial_choice(MatrixChanged);
            cout << "\nРешение  "<< k + 1<<"- ая координата, возмущение = " << setprecision(6) << fixed <<  pow(-1, n) * delta1 << endl << endl;
            solution_with_delta = find_solution(MatrixChangedNew, error);

            // Найдем вектор delta(x)
            vector<double> delta_vector_x;
            for (int i = 0; i < solution_with_delta.size(); i ++){
                delta_vector_x.push_back(fabs(solution_with_delta[i] - solution[i]));
            }

            //ПОСЧИТАМ ||delta(x)||. Октаэдрическая норма
            norm_delta_x_octahedron = octahedron_norm_vector(delta_vector_x);

            //ПОСЧИТАМ ||delta(x)||. Кубическая норма
            norm_delta_x_cube = cube_norm_vector(delta_vector_x);
        
        experiment_octahedron.push_back(cond(octahedron_norm_vect, octahedron_norm_b, norm_delta_x_octahedron, norm_delta_b_octahedron));
        experiment_cube.push_back(cond(cube_norm_vect, cube_norm_b, norm_delta_x_cube, norm_delta_b_cube));
        }       

    }

    cout << "\n Вывод значений чисел обусловленноси.Октаэдрическая норма" <<endl;
    for (const auto v : experiment_octahedron){
            std::cout << left << setw(15)<< setprecision(6) << fixed << v << "\n";
    }
    cout << endl << endl;

    cout << "Вывод значений чисел обусловленноси.Кубическая норма" <<endl;
    for (const auto v : experiment_cube){
            std::cout << left << setw(15)<< setprecision(6) << fixed <<  v << "\n";
    }
    cout << endl << endl;



    double max_cond_octahedron = experiment_octahedron[0];
    double max_cond_cube = experiment_cube[0];
    int number_max_octahedron = 0;
    int number_max_cube = 0;


    for (int i = 0; i < experiment_octahedron.size(); i ++){
        if (experiment_octahedron[i] > max_cond_octahedron){
            max_cond_octahedron = experiment_octahedron[i];
            number_max_octahedron = i/2 + 1;
        }

        if(experiment_cube[i] > max_cond_cube){
            max_cond_cube = experiment_cube[i];
            number_max_cube = i / 2 + 1;
        }
    }

    cout << "Нижняя грань числа обусловленности достигается на" << number_max_octahedron << " координате.Октаэдрическая норма = " << setprecision(6) << fixed << max_cond_octahedron << endl;
    cout << "Нижняя грань числа обусловленности достигается на" << number_max_cube << " координате. Кубическая норма = " << setprecision(6) << fixed << max_cond_cube << endl;

}
    

#endif