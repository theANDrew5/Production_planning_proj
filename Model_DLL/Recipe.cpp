//
// Created by User on 10-Feb-20.
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Recipe.h"

Recipe::Recipe(unsigned int ID, unsigned int time):_ID(ID),_time(time) {}
Recipe::Recipe(const Recipe & p): _ID(p._ID), _time(p._time) {}

Recipe::Recipe(json j): Recipe(
    j.at("Recipe_ID").get<int>(), 
    j.at("Recipe_time").get<int>())
{
}


unsigned int Recipe::get_ID()
{
    return this->_ID;
}

unsigned int Recipe::get_time()
{
    return this->_time;
}

json Recipe::to_json()
{
    return json{
        {"Recipe_ID", this->_ID},
        {"Recipe_time", this->_time}
        };
}

std::istream & operator>> (std::istream & is, Recipe & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._ID>>p._time;
    return is;
}

std::ostream &operator<<(std::ostream & os, Recipe & p)//перегрузка оператора сдвига для вывода
{
    return os<<"ID: "<<p._ID<<"\tTIME: "<<p._time;
}

bool operator==(Recipe &left, Recipe &right)
{
    if(left._ID==right._ID && left._time==right._time) return true;
    else return false;
}

bool operator==(const Recipe &left, const Recipe &right)
{
    if(left._ID==right._ID && left._time==right._time) return true;
    else return false;
}

bool operator!=(Recipe &left, Recipe &right) {
    if(left._ID!=right._ID && left._time!=right._time) return true;
    else return false;
}
