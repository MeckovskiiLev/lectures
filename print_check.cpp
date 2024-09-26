#include <iostream>
#include "print_check.h"


void print_check(char* error_number, char buffer[8192]) {

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

    std::cout<<buffer<<std::endl;

}
