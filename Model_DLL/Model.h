#pragma once
#include <vector>
#include <string>


#ifndef MODEL_EXPORTS
#define MODEL_DLL_API __declspec(dllexport)
#else
#define MODEL_DLL_API __declspec(dllimport)
#endif // !

//предварительные обьявления
class Environement;

class Model
{
public:

//методы управления структурой модели

    MODEL_DLL_API void add_batch(std::string j_string);//добавить в модель партию
    MODEL_DLL_API void add_machine(std::string j_string);//добавить в модель машину

//методы моделирования

    MODEL_DLL_API void time_shift(unsigned int time);//сдвинуть время модели
    MODEL_DLL_API void do_step_till_machine(unsigned int mch_ID);//моделировать до машины ID
    MODEL_DLL_API void do_step();//моделировать до коца
    MODEL_DLL_API void do_step(unsigned int n);//сделать n шагов моделирования
    MODEL_DLL_API void q_add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0);//вставить в очередь машины партию
    MODEL_DLL_API void q_add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0);
    //вставить в очередь машины несколько партий
    MODEL_DLL_API void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID);//замена очереди, не заменяет нулевой элемент

#if DEBUG
    MODEL_DLL_API void print_env();
    MODEL_DLL_API void test();
#endif
private:
    Model();
    Environement* Env;

};



