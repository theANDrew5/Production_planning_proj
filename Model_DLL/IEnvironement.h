#pragma once

#include <vector>

class IEnvironement
{
public:
    virtual void time_shift(unsigned int time)=0;//сдвинуть время модели
    virtual void do_step_till_machine(unsigned int mch_ID)=0;//моделировать до машины ID
    virtual void do_step()=0;//моделировать до коца
    virtual void do_step(unsigned int n)=0;//сделать n шагов моделирования
    virtual void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0)=0;//вставить в очередь машины партию
    virtual void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0)=0;
    //вставить в очередь машины несколько партий
    virtual void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID)=0;//замена очереди, не заменяет нулевой элемент

#if DEBUG
    virtual void print_env()=0;
#endif // DEBUG
};
