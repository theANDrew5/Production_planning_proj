//
// Created by User on 10-Feb-20.
//

#pragma once

#include "pch.h"// pch.h: This is a precompiled header file.

#include "Event.h"
#include "Batch.h"
#include "Machine.h"
//static const bool DEBUG = true;

class Environment
{
public:
    Environment(std::string name, std::map <unsigned int, Batch>& batches, std::map <unsigned int, Machine>& machines, 
        std::deque <Event>& events = *new std::deque <Event>{}, unsigned int global_model_time = 0);
    Environment(std::string name, std::list<Batch>& batches, std::list<Machine>& machines,
        std::deque <Event>& events = *new std::deque <Event>{}, unsigned int global_model_time = 0);

    Environment()=default;
    ~Environment()=default;


    friend std::ostream & operator<< (std::ostream & os, Environment & p);//перегрузка оператора <<

    void add_batch(std::string j_string);//добавить в модель партию
    void add_machine(std::string j_string);//добавить в модель машину

    void time_shift(unsigned int time);//сдвинуть время модели
    void do_step_till_machine(unsigned int mch_ID);//моделировать до машины ID
    void do_step();//моделировать до коца
    void do_step(unsigned int n);//сделать n шагов моделирования
    void q_add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos=0);//вставить в очередь машины партию
    void q_add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos=0);
    //вставить в очередь машины несколько партий
    void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID);//замена очереди, не заменяет нулевой элемент

//JSON methods
    friend void to_json(json& j, const Environment& env);
    

    #if DEBUG
        void print_env();
    #endif // DEBUG

private:

    void push_event(Machine& mch); //вставка события из машины
    void make_events();//рассчёт массива событий при запуске модели
    void change_event(Machine& mch);//замена события
    Batch& search_batch(unsigned int btc_ID);//возвращает указатель на партию по её ID
    Machine& search_machine(unsigned int mch_ID);//возвращает указатель на машину по её ID
    std::deque<Event>::iterator search_event (Machine& ptr);//возвращает итератор на событие по указателю на машину

    std::string _name;//имя среды
    std::map <unsigned int, Batch>& _batches;//партии
    std::map <unsigned int, Machine>& _machines;//машины
    std::deque <Event>& _events;//вектор событий, по которому происходят шаги
    unsigned int _global_model_time;

    std::ostream* _messages = &std::cout;

};


