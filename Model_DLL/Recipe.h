//
// Created by User on 10-Feb-20.
//
#pragma once

#include "pch.h"// pch.h: This is a precompiled header file.

class Recipe {
public:
    Recipe(unsigned int ID=0, unsigned int time=0);//конструктор
    Recipe(const Recipe &p);//конструктор копирования
    Recipe(json j);//конструктор из json

    unsigned int get_ID() const;//геттер ID рецепта
    unsigned int get_time() const;//геттер времени рецепта

    json to_json();//возвращает json
    


    friend std::istream & operator>> (std::istream & is, Recipe & p);//перегрузка оператора сдвига для потока ввода
    friend std::ostream &operator<<(std::ostream & os, Recipe & p);//перегрузка оператора сдвига для вывода
    friend bool operator==(Recipe &left, Recipe &right);//перегрузка оператора сравнения
    friend bool operator!=(Recipe &left, Recipe &right);//перегрузка оператора сравнения
    friend bool operator==(const Recipe &left, const Recipe &right);//перегрузка оператора сравнения

    friend void from_json(const json& j, Recipe& r);

private:
    unsigned int _ID; //имя рецепта
    unsigned int _time; //константа времени рецепта
};

void to_json(json& j, const Recipe& r);


