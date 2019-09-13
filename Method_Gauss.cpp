#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


#include "function_read_matrix.hpp"
#include "calculation_partial_choice.hpp"
#include "calculation_main_choice.hpp"
#include "find_solution.hpp"
#include "find_2solution.hpp"
#include "qr.hpp"
#include "condition_number.hpp"
#include "lowest_condition_number.hpp"
#include "error.hpp"

using namespace std;

template <typename Type>
void calculate(vector<std::string> test_names, Type var){
    int i = 0;
    bool error = false;
    for (const auto &s: test_names){
        cout << "                                       ТЕСТ " << i + 1 << endl;
        cout<< "Считанная расширенная матрица из файла" << endl;
        auto matrix = open_test_read_slae(s,var);
        

        cout<< "Метод Гаусса.Частичный выбор главного элемента. Решение,полученное при использовании метода Гаусса" << endl;
        auto matrix1 = calculation_partial_choice(matrix);
        auto sol1= find_solution(matrix1, error);
        // auto matrix1 = calculation_main_choice(matrix);
        // sol1 = find_2solution(matrix1);


        if (error == false){
            nevyazka(matrix, sol1);

            lowest_conditional_number(matrix, sol1);

            cout<< "QR метод" << endl;
            auto matrix2 = qr(matrix);

    
            cout<< "Решение" << endl;
            auto sol2 = find_solution(matrix2, error);

        }
        // // if (error == false){
        //     nevyazka(matrix, sol1);
        // }
        
        if (error == false ){
            lowest_conditional_number(matrix, sol1);
        }

        // error = false;
        
        cout << endl;
        if (error == false){
            cout<< "QR метод" << endl;
        auto matrix2 = qr(matrix);

    
        cout<< "Решение" << endl;
        auto sol2 = find_solution(matrix2, error);
        


        }

        error = false;
        //cout << "Число обусловленности" << endl;
        condition_number(matrix, matrix1);
        i++;

    }

}

int main() {     
    // vector<std::string> test_names = {"/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/DATA1.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/DATA2.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/DATA3.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/DATA4.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/DATA5.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/BASE1.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/BASE2.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/BASE3.TXT",
    //                                   "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/BASE4.TXT",
    vector<std::string> test_names = {"/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/NEW1.TXT",
                                      "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/NEW2.TXT",
                                      "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/NEW3.TXT",
                                      "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/NEW4.TXT",
                                      "/home/darya/Method_of_calculation/LabaFirst/_Lab1/SYS1/NEW5.TXT"}; 
    float a = 0;
    double b = 0;



    //СЧЕЧИК ДЛЯ УМНОЖЕНИЯ МАТРИЦ
    
    cout<<endl<<endl<<endl;
    
    

    cout << "Какой тип данных будете использовать? Выберете соответствующую цифру \n 1: float \n 2: double\n";
    int choice_type;
    cin >> choice_type;



    switch(choice_type){
    case 1: calculate(test_names, a);break;
    case 2: calculate(test_names, b);break;
    }

    


    // auto matrix = open_test_read_slae(test_names[0],a);
    // calculation(matrix);
    return 0;
}