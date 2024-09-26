#ifndef STATS_CHECK_H
#define STATS_CHECK_H

#include <vector>

// extern int number_of_errors_in_log;

// void getting_number_of_errors(char* value);





//структура
struct url_check_count {
    char url[256];//url
    int count;//колличество ошибок
};

extern int check_number_of_errors;

void get_number_of_errors(char* value);

extern std::vector <url_check_count> count_url;

bool compare_count(const url_check_count &first, const url_check_count &second);

void string_copy(char* location, const char* source, size_t max_length);

void full_array_with_data(std::vector<url_check_count> &count_url, char* word5, char* error);

void compare_url_with_errors(std::vector<url_check_count> &count_url, int n);

#endif