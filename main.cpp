
//nullptr — это специальное ключевое слово, которое используется для указания на "нулевой" указатель, то есть указатель, который не указывает ни на какой объект или память
//указатель — это переменная, которая хранит адрес другой переменной в памяти, вместо того, чтобы хранить значение, указатель хранит место, где это значение находится
// с помощью * можно получить значение, которое хранится по адресу, на который указывает указатель. с помощью & вернуть адрес переменной.


#include "output_directory_arguments.h"
#include "stats_check.h"
#include "time_from.h"
#include "print_check.h"
#include "window_check.h"
#include "input_check.h"
#include <limits.h>
#include <windows.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream> // для работы с файловыми потоками(для ifstream)
#include <ctime>// - для timestamp

// int stats_value = 10;//основная, к которой обращаемся
// int default_value = 10;
//[01/Jul/1995:00:11:02
// void set_stats_value(int value) {
//     stats_value = value;
// }

bool is_status_code(const char* word) {
    // проверяем, является ли слово трёхзначным числом
    return strlen(word) == 3 && isdigit(word[0]) && isdigit(word[1]) && isdigit(word[2]);
}
//копирование строки вручную
void manual_copy(char* destination, const char* strc) {//destination - куда копируем, strc - откуда
    while (*strc) {//пока символ строки не равне \0
        *destination++ = *strc++;//копиурем символ и увеличиваем указатели
    }
    *destination = '\0';
}
//ручное обьединение строк с пробелом вручную, также добавляя между ними пробел
void manual_concat(char* destination, const char* strc) {
    while (*destination) {  // двигаем пока не найдем \0
        destination++;
    }
    *destination++ = ' ';  // добавляем пробел между словами, как только нашли первую строку
    while (*strc) {   // копируем вторую строку из strc в destination , уже наиная после пробела
        *destination++ = *strc++;
    }
    *destination = '\0';//заврешаем строку
}

//копирование буффера
char* duplicate_buffer(const char buffer[8192]) {
          char* buffer_copy = new char[8192];
          for (int i =0; i < 8192; i++) {
                buffer_copy[i] = buffer[i];
          }
          return buffer_copy;  
    }


int main(int argc, char** argv) {
    if (argc < 2) {//есть ли хотя бы два эллемента в командной строке
        std::cout << "Not enough elements";
        return 1;
    }

    const char* target = "access.log";//файл, который программа должна найти в эллементах командной строки
    const char* file_name = nullptr;//указатель для хранения имени файла

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], target) == 0) {//если находит access.log
            file_name = argv[i];//сохранем указатель
            break;
        }
    }

    if (!file_name) {
        std::cout << "No file or way to file detected" << std::endl;//если переменная не nullptr то файл был надйен
        return 1;
    }

    if (!parse_check_errors(argv, argc)) {//если хоть что то введено не верно
        std::cout << "Error was detected. Incorrect input" << std::endl;//если функция выдала false
        return 1;
    }
    else {
        parse_args(argv, argc);//иначе выполняем функцию на считывание аргументов
    }





    const char* original_path = "C:\\Users\\levfr\\github-classroom\\is-itmo-c-24\\labwork1-MeckovskiiLev\\input\\NASA_access_log_Jul95\\access_log_Jul95";

    
    char buffer[8192];//обявляем массив символов для  хранения строк из файла

    std::ifstream file(original_path); // открываем файл для чтения с помощью ifstream

    if (!file.is_open()) {//проверяем открылся ли файл корректно
        std::cout << "Incorrect input";
        return 1;
    } 
    //---для --stats
    //std::vector<LogEntry> error_lines;
    // std::vector<int> time_stamps_collection;

    int k = 0;
    while (file.getline(buffer, sizeof(buffer))) {//цикл, который считывает строки из файла построчно с помощью метода getline,каждая строка сохраняется в массив buffer
        char* buffer_copy = duplicate_buffer(buffer);
        //if (k>=100) {
          //  break;
        //}
        const int max_words_in_log = 15; // максимальное количество слов, которое мы можем сохранить из строки
        char* words[max_words_in_log];//массив указателей words, хранящий указатели на слова в строке
        char* start = buffer;//указатель для поиска слов, изначально указыывающий на начало строки
        char* end = nullptr;//указатель, указывающий на позицию пробела
        int word_count = 0;

        while ((end = strchr(start, ' ')) != nullptr) {//ищем пробелы в строке с помощью strchr, если пробел находится то end указывает на его позиццию
            *end = '\0';  // заменяем пробел на нулевой символ, для разделения строки на отдельные слова

            if (word_count < max_words_in_log) {//если колличество найденных слов меньше максимального
                words[word_count++] = start;  // сохраняем указатель на слово в массив words
            }

            start = end + 1;  // перемещение указателя start на следущую позицию
        }

        
        if (*start != '\0' && word_count < max_words_in_log) {//проверка на достижение концца строки и можно ли сохранить еще одно слово
            words[word_count++] = start;  // сохраняем указатель на последнее слово, если оно существует
        } 

        if (word_count > 5) {//проверяем массив с пятого эллемента
            char* full_url = new char[8192];//создание нового буфера для хранения полной строки URL
            manual_copy(full_url, words[5]);//копируем содержимое слова под индексом 5 в буффер full_url

            for (int i = 6; i < word_count; ++i) {//идем начиная с шестого символа
                if (is_status_code(words[i])) {//если является кодом ошибки
                    words[6] = words[i];//сохраняем
                    break;
                }
                manual_concat(full_url, words[i]);//если не является статус кодом то присодединяем в full_url

            }
            words[5] = full_url;//вся созданная строка сохранется в words[5]

        }
        if (first_time_check(words[3]) > start_time){///----start_time
            if (first_time_check(words[3]) < end_time){////--end_time

                if (std::find(arguments.begin(), arguments.end(), "--output") != arguments.end() || 
                    std::find(arguments.begin(), arguments.end(), "-o") != arguments.end()) {
                    output_directory_arguments(words[6], buffer_copy);
                }
                if (std::find(arguments.begin(), arguments.end(), "--print") != arguments.end() || 
                        std::find(arguments.begin(), arguments.end(), "-p") != arguments.end()) {
                    print_check(words[6], buffer_copy);
                }

                //for stats
                char url[256] = {0};
                char error[4] = {0};

                string_copy(url, words[5], sizeof(url));
                string_copy(error, words[6], sizeof(error));

                full_array_with_data(count_url, url, error);


                //for window
                int value_main = first_time_check_main(words[3]);
                full_vector(time_stamps_collection, value_main);
            }
        }
        //
        //std::cout << words[3] << std::endl;
        //std::cout << words[5] << std::endl;
        //char url[256] = {0};
        //char error[4] = {0};

        //string_copy(url, words[5], sizeof(url));
        //string_copy(error, words[6], sizeof(error));
        
        //std::cout<<words[8] << std::endl;
        //std::cout << url3 << std::endl;
        //std::cout << "Extracted URL: " << url << ", Error: " << error << std::endl;
        //full_array_with_data(count_url, url, error);
        //int value_main = first_time_check_main(words[3]);////// ------ window
        //full_vector(time_stamps_collection, value_main);///////-----window
        //if (first_time_check(words[3]) > start_time){///----start_time
            //if (first_time_check(words[3]) < end_time){////--end_time
        //output_directory_arguments(words[6], buffer_copy);/////-----output
                //print_check(words[8], buffer_copy);//////-----print
            //}
        //}
        
        //print_check(words[6], buffer_copy);
        //output_directory_arguments(words[8], buffer_copy);
        //delete[] buffer_copy;
        //k++;
    }
    //pointers_metod(time_stamps_collection, size_of_window);//////------window
    //std::cout << max_time << std::endl;

    compare_url_with_errors(count_url, check_number_of_errors);
    
    pointers_metod(time_stamps_collection, size_of_window);
    
    
    //compare_url_with_errors(count_url, check_number_of_errors);
    return 0;
}