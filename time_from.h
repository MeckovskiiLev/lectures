#ifndef TIME_FROM_H
#define TIME_FROM_H

#include <ctime>
extern int end_time;//для конечного времени
extern int start_time;//обьявяляю глдобальную переменную
void change_time_start(char* value);

void change_time_end(char* value);

int word_to_number(char* month_word);

time_t first_time_check(char* start_time);


#endif