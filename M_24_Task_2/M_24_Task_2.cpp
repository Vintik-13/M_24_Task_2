/*Задание 2. Реализация программы напоминания о днях рождения
* 
Что нужно сделать
Реализуйте простую программу по вычислению ближайшего дня рождения.
В начале программы пользователь последовательно вводит данные о днях
рождения своих друзей: вводит имя друга и саму дату рождения полностью,
включая месяц и год, в формате год/месяц/день. Сигналом окончания ввода
дней рождения является “end” введённое в качестве имени.
После этого программа вычисляет ближайший день рождения по отношению к
текущему времени и выводит его на экран вместе с именем в удобном,
локальном формате - месяц/день. Если день рождения уже был в этом году,
данные о пользователе пропускаются. Если у кого-то из друзей день рождения
сегодня, то в консоль выводится специальное сообщение об этом. Учтите,
что таких сообщений может быть несколько, ведь сразу несколько людей могут
иметь дни рождения в один день.*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <iomanip>

const std::string PATTERN = "([A-Z]{1}[a-z]*)\\s+(\\d{4})/(\\d{2})/(\\d{2})";

struct birthday {
    std::string name;
    std::tm date{};
};

bool validInput(std::string& str, std::cmatch& result) {
    std::regex r(PATTERN);
    return std::regex_match(str.c_str(), result, r);
}

int dateStoi(std::string str) {
    try {
        return std::stoi(str);
    }
    catch (const std::exception& ex) {
        std::cout << ex.what();
    }
}

bool creatBirthday(birthday& men, std::cmatch& result) {
    
    std::vector<int> tmp{ 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((dateStoi(result[2]) % 4 == 0 && dateStoi(result[2]) % 100 != 0) || dateStoi(result[2]) % 400 == 0)
        tmp[1] = 29;    

    if (dateStoi(result[3]) <= tmp.size() && dateStoi(result[4]) <= tmp[dateStoi(result[3]) - 1]) {
        std::time_t t = std::time(nullptr);
        
        men.name = result[1];
        men.date.tm_year = dateStoi(result[2]) - 1900;
        men.date.tm_mon = dateStoi(result[3]) - 1;
        men.date.tm_mday = dateStoi(result[4]);
        return true;
    }
    else
        return false;
}

std::vector<birthday> inputDate() {
    std::vector<birthday> v_tmp;
    birthday tmp;
    std::string str;
    std::cmatch result;

    std::cout << "Enter your name and birthday in the format \"Name YYYY-MM-DD\"";
    std::getline(std::cin, str);
    while (str != "end")
    {
        if (validInput(str, result)) {
            if(creatBirthday(tmp, result))
                v_tmp.push_back(tmp);
        }
        else 
            std::cout << "Incorret input\n";            
        
        std::cout << "Enter your name and birthday in the format \"Name YYYY-MM-DD\"";
        std::getline(std::cin, str);            
    }
    return v_tmp;
}

bool comp(birthday first, birthday second) {
    first.date.tm_year = 70;
    second.date.tm_year = 70;
    time_t one = std::mktime(&first.date);
    time_t two = std::mktime(&second.date);
   
    return two > one ? true : false;
}

void ShowBirthday(std::vector<birthday>& list) {
    
    std::vector<birthday> tmp;
    std::sort(list.begin(), list.end(), comp);
    std::time_t tt = std::time(nullptr);
    birthday b_tmp;
    std::tm* tm = std::localtime(&tt);    
    b_tmp.date.tm_mon = tm->tm_mon;
    b_tmp.date.tm_mday = tm->tm_mday;    
    
    for (int i = 0; i < list.size(); i++) {
        bool aaa = comp(b_tmp, list[i]);
        if (comp(b_tmp, list[i])) {
            std::cout << list[i].name << " " << std::put_time(&list[i].date, "%Y-%m-%d") << std::endl;
        }
    }    
}

int main()
{    
    std::vector<birthday> list = inputDate();

    ShowBirthday(list);    
}
    

