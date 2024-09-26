#include "output_directory_arguments.h"
#include <iostream>
#include <fstream>
const char* file_name = nullptr;

void set_file_name(char* value) {//установка глобальной переменной file_name для функции output directoru arguments
    file_name = value;
}

void output_directory_arguments(char* error_number, char buffer[8192]) {
    std::ofstream file_output;
    file_output.open(file_name, std::ios::app);
    if (!error_number || error_number[0] == '\0' || error_number[1] == '\0' || error_number[2] == '\0') {
        return;
    }

    if (error_number[0] != '5') {
        return;
    }

    if (!(error_number[1] >= '0' && error_number[1] <= '9') || !(error_number[2] >= '0' && error_number[1] <= '9')) {
        return;
    }

    if (error_number[3] != '\0') {
        return;
    }
    if (file_output.is_open()) {
        file_output << buffer << std::endl;
        file_output.close();
    }

}