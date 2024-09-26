#include "stats_check.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>


int check_number_of_errors = 10;

void get_number_of_errors(char* value) {//перевод value в число
    check_number_of_errors = atoi(value);
}

std::vector <url_check_count> count_url;//глобальный вектор хранящий структуру для каждого URL с ошибками

bool compare_count(const url_check_count &first, const url_check_count &second) {//функция для сортировки
    return first.count > second.count;//если значение count первого обьекта больше чем count второго обьяекта
}

void string_copy(char* location, const char* source, size_t max_length) {//1.указатель, куда будет копироваться содержимое.2.строка, из которой копируем.3. максимальная длина строки, из которой покируем
    if (source == nullptr){
        return;// проверяю на nullptr
    } 
    int i = 0;
    while (source[i] != '\0' && i < max_length - 1) {//копируем строку
        location[i] = source[i];
        i++;
    }
    location[i] = '\0';
}

void full_array_with_data(std::vector<url_check_count> &count_url, char* word5, char* error) {//вектор со структурой, url, код ошибки
    if (error == nullptr || error[0] != '5') return; // Проверка на nullptr

    bool find_error = false;//флаг
    char full_url[256] = {0}; //хранение копии word5

    if (word5 != nullptr) {
        snprintf(full_url, sizeof(full_url), "%s", word5);//строка копируется в full_url засчет snprintf
    }
    
    for (auto &now : count_url) {
        if (strcmp(now.url, full_url) == 0) {//есть ли в векторе уже такой урл
            now.count += 1;//если найден, то повышаем счетчик
            find_error = true;
            break;
        }
    }

    if (!find_error) {//если флаг фолз
        url_check_count new_url_enter;//создаем новый обьект структуры 
        string_copy(new_url_enter.url, full_url, sizeof(new_url_enter.url));//поле объекта заполняется новой строкой
        new_url_enter.count = 1;
        count_url.push_back(new_url_enter);//добавляем его в вектор
    }
}

void compare_url_with_errors(std::vector<url_check_count> &count_url, int n) {
    if (count_url.empty()) {//если вектор пуст
        std::cout << "No URLs available." << std::endl;
        return;
    }

    std::vector<url_check_count> sorted_vector = count_url; //вектор count_url копируется в новый вектор sorted_vector, который 
    std::sort(sorted_vector.begin(), sorted_vector.end(), compare_count);//сортируется по количеству ошибок с помощью функции compare_count.

    // используем размер вектора для ограничения итераций
    for (int i = 0; i < n && i < static_cast<int>(sorted_vector.size()); i++) {//выводим первые эн адресов и их колличество ошибок
        std::cout << "For URL: " << sorted_vector[i].url << " = " << sorted_vector[i].count << " err" << std::endl;
    }
}
