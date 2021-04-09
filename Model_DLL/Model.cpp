
#include "pch.h"
#include "Environment.h"
#include "Model.h"





#if DEBUG
void Model::print_env()
{
	this->Env->print_env();
}
void Model::test()
{
	std::cout << "Succes!!!\n";
}
#endif

Model::Model(std::string config):
	_env(*new Environment(json::parse(config).get<Environment>()))
{

}

//методы управления структурой модели

void Model::add_batch(std::string j_string)
{
	this->_env.add_batch(json::parse(j_string));
}

void Model::add_machine(std::string j_string)
{
	this->_env.add_machine(json::parse(j_string));
}


//методы моделирования

void Model::time_shift(unsigned int time)
{
	this->_env.time_shift(time);
}

void Model::do_step_till_machine(unsigned int mch_ID)
{
	this->_env.do_step_till_machine(mch_ID);
}

void Model::do_step()
{
	this->_env.do_step();
}

void Model::do_step(unsigned int n)
{
	this->_env.do_step(n);
}

void Model::q_add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos)
{
	this->_env.q_add_batch(btc_ID, mch_ID, pos);
}

void Model::q_add_batch(std::vector<unsigned int> btc_IDs, unsigned int mch_ID, unsigned int pos)
{
	this->_env.q_add_batch(btc_IDs, mch_ID, pos);
}

void Model::replace_queue(std::vector<unsigned int> btc_IDs, unsigned int mch_ID)
{
	this->_env.replace_queue(btc_IDs, mch_ID);
}