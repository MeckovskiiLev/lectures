#ifndef WINDOW_CHECK_H
#define WINDOW_CHECK_H

#include <iostream>
#include <vector>
#include <ctime>
extern int size_of_window;

void get_operations_number(char* value);

extern std::vector<int> time_stamps_collection;


void full_vector(std::vector<int>& time_stamps, int value);
void pointers_metod(std::vector<int> time_stamps, int time_value);
int word_to_number_main(char* month_word);
time_t first_time_check_main(char* start_time);





#endif