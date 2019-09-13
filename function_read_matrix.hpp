#ifndef _FUNCTION_READ_MATRIX_
#define _FUNCTION_READ_MATRIX_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


using namespace std;

template <typename Type>
std::vector<std::vector<Type>> open_test_read_slae(std::string str, Type t);

template <typename Type>
std::vector<std::vector<Type>> open_test_read_slae(std::string str, Type t){   
    ifstream file(str);
    if (!file.is_open()){
        cout << "Файл не может быть открыт! Имя файла:"<< str << endl;
        exit(EXIT_FAILURE);
    }

    //Считываем первую строку, т.к. нужные значения начинаются со второй
    std::string line;
    getline(file, line);
    //Закончили считывание первой строки
    std::vector<std::vector<Type>> matrixV;
    while (std::getline(file, line)){
        if (line[0] == '\n' or line[0] == '\r'){
            break;
        }
        // cout<< line<< endl;
        std::istringstream iss(line);
        std::vector<Type> data;
        Type num;
        while(iss >> num){
            data.push_back(num);
        }
        matrixV.push_back(data);
    }

    for (const auto &v : matrixV){
        for (const auto &n: v){
            std::cout << left << setw(15)<< n << "\t";
        }
        std::cout << std::endl;
    }
    cout << endl << endl;
   
    return matrixV;
}

#endif