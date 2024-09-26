//алгоритм скользящего окна
#include "window_check.h"
#include <iostream>
#include <vector>
#include <ctime>

int size_of_window = 0;

void get_operations_number(char* value){
    size_of_window = atoi(value);
}


std::vector<int> time_stamps_collection;

void full_vector(std::vector<int>& time_stamps, int value) {
    time_stamps.push_back(value);
}

void pointers_metod(std::vector<int> time_stamps, int time_value) {
    if (time_value <= 0) {
        std::cout << "For --window calcs cant be done";
        return;
    }
    int max_start_time = 0;
    int max_end_time = 0;
    int start = 0;
    int max_time = 0;
    for (int end = 0; end < time_stamps.size(); end++) {
        while (time_stamps[end] - time_stamps[start] > time_value) {
            start++;
            
            
        }
        if (start <= end) {
            int value_of_seconds = end - start + 1;
            if (value_of_seconds > max_time) {
                max_time = value_of_seconds;
                max_start_time = time_stamps[start];
                max_end_time = time_stamps[end];
            }
        }  
    }
    std::cout << "Max amount of requests: " <<  max_time << std::endl;
    std::cout << "from " << max_start_time << " to " << max_end_time << std::endl;
}

int word_to_number_main(char* month_word) {
    const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_word, months[i]) == 0) {
            return i;
        }
    }
    return 0;
}


time_t first_time_check_main(char* start_time) {

    char day[3];
    int s_p_day = 1;

    for (int i = 0; i < 2; i++) {
        day[i] = start_time[s_p_day + i];
    }
    day[2] = '\0';

    char month_word[4];
    int s_p_m = 4;
    for (int i = 0; i < 3; i ++) {
        month_word[i] = start_time[s_p_m+i];
    }
    month_word[3] = '\0';

    int month_number = word_to_number_main(month_word);
    

    char year[5];
    int s_p_y = 8;
    for (int i = 0; i < 4; i ++) {
        year[i] = start_time[s_p_y + i];
    }
    year[4] = '\0';


    char hours[3];
    int s_p_h = 13;
    for (int i = 0; i < 2; i++) {
        hours[i] = start_time[s_p_h + i];
    }
    hours[2] = '\0';

    char minutes[3];
    int s_p_min = 16;
    for (int i = 0; i < 2; i++) {
        minutes[i] = start_time[s_p_min + i];
    }
    minutes[2] = '\0';

    char seconds[3];
    int s_p_s = 19;
    for (int i = 0; i < 2; i++) {
        seconds[i] = start_time[s_p_s + i];
    }
    seconds[2] = '\0';

    struct tm log_time = {};
        log_time.tm_mday = atoi(day);
        log_time.tm_mon = month_number;
        log_time.tm_year = atoi(year)-1900;
        log_time.tm_hour = atoi(hours);
        log_time.tm_min = atoi(minutes);
        log_time.tm_sec = atoi(seconds);

    time_t log_time_stamp = mktime(&log_time);//преобразую в timestamp
    return log_time_stamp;
}