//
// Created by User on 10-Feb-20.
//

#pragma once

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Recipe.h"

//класс партии
class Batch {
public:

    Batch(unsigned int ID=0, unsigned int count=0, std::deque <Recipe> recipes={});//конструктор с параметрами
    Batch(const Batch &p);//конструктор копирования

    Recipe& get_first();//возвращает link первый рецепт в маршрутном листе
    const unsigned int get_count() const;//возвращает количество изделий
    unsigned int get_ID() const;//возвращает ID

    void execute();//

    friend std::istream & operator>> (std::istream & is, Batch & p);//перегрузка оператора сдвига для потока ввода
    friend std::ostream &operator<<(std::ostream & os, Batch & p);//перегрузка оператора сдвига для вывода

    friend void to_json(json& j, const Batch& b);
    friend void from_json(const json& j, Batch& b);

private:

    unsigned int _ID; //имя партии
    unsigned int _count; //число пластин
    std::deque <Recipe> _recipes;//маршрутный лист / вектор для быстрого доступа

};


