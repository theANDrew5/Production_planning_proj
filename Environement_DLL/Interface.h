#pragma once

//#include "pch.h"

#include<string>
#include<vector>

#ifndef MODEL_EXPORTS
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API __declspec(dllimport)
#endif // !



class Environment;

class Model
{
public:

    MODEL_API Model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int itial_time);
    MODEL_API Model(const char configfile [], const char state_file [], const char logfile [], const char messages [], unsigned int itial_time);
    //MODEL_API Model(const char configfile[], const char state_file[], const char logfile[], const char messages[], unsigned int itial_time);

//    void time_shift(unsigned int time);//сдвинуть время модели 
//    void do_step_till_machine(unsigned int mch_ID);//моделировать до машины ID
//    void do_step();//моделировать до коца
//    void do_step(unsigned int n);//сделать n шагов моделирования
//    void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0);//вставить в очередь машины партию
//    void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0);
//    //вставить в очередь машины несколько партий
//    void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID);//замена очереди, не заменяет нулевой элемент
//
#if DEBUG
    MODEL_API void print_env();
    MODEL_API void test();
#endif
private:
    Model();
    Environment  *const _env;

};



