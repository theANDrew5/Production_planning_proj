#pragma once
#include <vector>
#include <string>


#ifndef MODEL_EXPORTS
#define MODEL_DLL_API __declspec(dllexport)
#else
#define MODEL_DLL_API __declspec(dllimport)
#endif // !

//��������������� ����������
class Environement;

class Model
{
public:

//������ ���������� ���������� ������

    MODEL_DLL_API void add_batch(std::string j_string);//�������� � ������ ������
    MODEL_DLL_API void add_machine(std::string j_string);//�������� � ������ ������

//������ �������������

    MODEL_DLL_API void time_shift(unsigned int time);//�������� ����� ������
    MODEL_DLL_API void do_step_till_machine(unsigned int mch_ID);//������������ �� ������ ID
    MODEL_DLL_API void do_step();//������������ �� ����
    MODEL_DLL_API void do_step(unsigned int n);//������� n ����� �������������
    MODEL_DLL_API void q_add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0);//�������� � ������� ������ ������
    MODEL_DLL_API void q_add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0);
    //�������� � ������� ������ ��������� ������
    MODEL_DLL_API void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID);//������ �������, �� �������� ������� �������

#if DEBUG
    MODEL_DLL_API void print_env();
    MODEL_DLL_API void test();
#endif
private:
    Model();
    Environement* Env;

};



