#include <iostream>
#include "time_from.h"
#include <ctime>
#include <cstring>

int start_time = 804556801;
int end_time = 806938345;


void change_time_start(char* value) {//функция для глобальное п
    start_time = atoi(value);
}

void change_time_end(char* value) {
    end_time = atoi(value);
}



int word_to_number(char* month_word) {
    const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_word, months[i]) == 0) {
            return i;
        }
    }
    return 0;
}


time_t first_time_check(char* start_time) {

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

    int month_number = word_to_number(month_word);
    

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