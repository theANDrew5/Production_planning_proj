#pragma once

#include <vector>

class IEnvironement
{
public:
    virtual void time_shift(unsigned int time)=0;//�������� ����� ������
    virtual void do_step_till_machine(unsigned int mch_ID)=0;//������������ �� ������ ID
    virtual void do_step()=0;//������������ �� ����
    virtual void do_step(unsigned int n)=0;//������� n ����� �������������
    virtual void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0)=0;//�������� � ������� ������ ������
    virtual void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0)=0;
    //�������� � ������� ������ ��������� ������
    virtual void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID)=0;//������ �������, �� �������� ������� �������

#if DEBUG
    virtual void print_env()=0;
#endif // DEBUG
};
