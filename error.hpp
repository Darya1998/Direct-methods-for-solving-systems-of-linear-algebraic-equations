#ifndef _ERROR_
#define _ERROR_

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
double nevyazka (std::vector<std::vector<Type>> matrix, std::vector<Type> solution);

template <typename Type>
double nevyazka (std::vector<std::vector<Type>> matrix, std::vector<Type> solution){
    std::vector<double> matr_product(matrix.size());


    for (int i = 0; i < matrix.size(); i ++){
        matr_product[i] = 0;
        for (int j = 0; j < solution.size(); j++){
            matr_product[i] += matrix[i][j] * solution[j];
        }
    }

    //Найдем разницу между векторами b и b*
    vector<Type> delta_b(matr_product.size());
    double norm_nevyazky = 0;
    for (int i = 0; i < matr_product.size(); i++){
        delta_b[i] = fabs(matr_product[i] - matrix[i][matrix[0].size() - 1]);
        norm_nevyazky += pow(delta_b[i], 2);
    }



    cout << "Норма невязки" << endl;
    cout << setprecision(20) << fixed << sqrt(norm_nevyazky) << endl;
}


#endif