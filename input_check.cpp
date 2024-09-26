#include "input_check.h"
#include "stats_check.h"
#include "time_from.h"
#include "window_check.h"
#include "output_directory_arguments.h"
#include <iostream>
#include <cstring>
#include <fstream>


std::vector<std::string> arguments;


bool parse_check_errors(char** argv, int argc) {
    bool error_found = true;//флаг для поиска ошибок

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "--", 2) == 0) {//проверка длинных аргументов
            char* equalPos = strchr(argv[i], '=');//поиск = в строке
            if (equalPos != nullptr) {//если равно был найден
                
                char* option = argv[i];//значение строки до равно
                char* value = equalPos + 1;//значение после равно

                if (strncmp(option, "--output", equalPos - option) == 0 || //equalPos - option вычисляет длину строки до символа = и эта длина сравнивается с допустимыми аргументами
                    strncmp(option, "--stats", equalPos - option) == 0 ||
                    strncmp(option, "--window", equalPos - option) == 0 ||
                    strncmp(option, "--from", equalPos - option) == 0 || 
                    strncmp(option, "--to", equalPos - option) == 0) {
                    continue;
                } else {
                    error_found = false;
                    break;
                }
            } else if (strcmp(argv[i], "--print") == 0) {
                continue;
            }

            else {
                error_found = false;
                break;
            }
        } else if (strncmp(argv[i], "-", 1) == 0) {//проверка коротких аргументов
            if ((strcmp(argv[i], "-o") == 0 && i + 1 < argc) || //i+1<argc - гарантия не выхода за пределы массива
                strcmp(argv[i], "-p") == 0 ||
                (strcmp(argv[i], "-s") == 0  && i + 1 < argc)||
                (strcmp(argv[i], "-w") == 0 && i + 1 < argc) ||
                (strcmp(argv[i], "-f") == 0 && i + 1 < argc) || 
                (strcmp(argv[i], "-e") == 0 && i + 1 < argc)) {
                i++;//если у данной опции есть какое то значение, то пропускаем следующий эллемент, так как он уже обработан
                continue;
            
            } 
            else {
                error_found = false;
                break;
            }
        } else if (strcmp(argv[i], "access.log") == 0) {
            continue;
        } 
        else {
            error_found = false;
            break;
        }
    }
    return error_found;
}

// Функция для разбора аргументов
void parse_args(char** argv, int argc) {


    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "--", 2) == 0) {  // Длинная опция с "="
            char* equalPos = strchr(argv[i], '='); // ищу знак равно в длинном аргументе
            if (equalPos != nullptr) {//если символ равно найден в длинном аргументе
                *equalPos = '\0';  // разделяем строку на опцию и значение, на до равно и после равно
                char* option = argv[i];//разделяем аргв на две разные строки, на опцию и аргумент опции
                char* value = equalPos + 1;//строка после равно
                if (strcmp(option, "--output") == 0) {
                    std::cout << "Option: --output, Path: " << value << std::endl;
                    arguments.push_back("--output");
                    set_file_name(value);
                } 
                else if (strcmp(option, "--stats") == 0) {
                    arguments.push_back("--stats");
                    get_number_of_errors(value);
                    std::cout << "Option: --stats, Value: " << value << std::endl;
                } 
                else if (strcmp(option, "--window") == 0) {
                    arguments.push_back("--window");
                    get_operations_number(value);
                    std::cout << "Option: --window, Time: " << value << std::endl;
                } 
                else if (strcmp(option, "--from") == 0) {
                    arguments.push_back("--from");
                    std::cout << "Option: --from, Time: " << value << std::endl;
                    change_time_start(value);
                }
                else if (strcmp(option, "--to") == 0) {
                    arguments.push_back("--to");
                    std::cout << "Option: --to, Time: " << value << std::endl;
                    change_time_end(value);
                }
            }
            else {
            if ((strcmp(argv[i], "--print") == 0)){
                arguments.push_back("--print");
                std::cout<< "Print was detected" << std::endl;
            }
            }

        } else if (strncmp(argv[i], "-", 1) == 0) {  // разбираем короткие аргументы, начинающиеся с одного тире
            if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
                arguments.push_back("-o");
                std::cout << "Short option -o, Path: " << argv[i + 1] << std::endl;//проверка, идет ли после опции значение, чтобы не выходить за пределы массива
                set_file_name(argv[i+1]);
                i++;  // пропускаем эллемент, если у опции есть значение, так как он уже обработан
            } 
            else if (strcmp(argv[i], "-p") == 0) {
                arguments.push_back("-p");
                std::cout << "Short option -p (print)\n" << std::endl;;
            } 
            else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
                arguments.push_back("-s");
                get_number_of_errors(argv[i+1]);
                std::cout << "Short option -s, Stats: " << argv[i + 1] << std::endl;
                i++;  
            } 
            else if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
                arguments.push_back("-w");
                std::cout << "Short option -w, Window: " << argv[i + 1] << std::endl;
                get_operations_number(argv[i+1]);
                i++;  
            } 
            else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
                arguments.push_back("-f");
                std::cout << "Short option -f, From: " << argv[i + 1] << std::endl;
                change_time_start(argv[i+1]);
                i++;  
            }
            else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
                arguments.push_back("-e");
                std::cout << "Short option -f, From: " << argv[i + 1] << std::endl;
                change_time_end(argv[i+1]);
                i++;  
            } 

 
            
        } 
        else if (strcmp(argv[i], "access.log") == 0) {  // проверяем наличие access.log
            std::cout << "File: access.log" << std::endl;
        }

    }
}