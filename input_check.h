#ifndef INPUT_CHECK_H
#define INPUT_CHECK_H

#include <iostream>

#include <vector>

extern std::vector<std::string> arguments;

bool parse_check_errors(char** argv, int argc);

void parse_args(char** argv, int argc);

#endif