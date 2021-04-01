
#include "pch.h"
#include "Interface.h"
#include "Environment.h"



Model::Model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int itial_time)
	:_env(new Environment(configfile, state_file,logfile, messages, itial_time))
{
}

Model::Model(const char configfile[], const char state_file[], const char logfile[], const char messages[], unsigned int itial_time)
	: _env(new Environment(configfile, state_file, logfile, messages, itial_time))
{
}

//Model::Model( const char configfile[], const  char state_file[], const  char logfile[], const  char messages[], unsigned int itial_time)
//	:_env(new Environment(std::string (configfile), std::string(state_file), std::string(logfile), std::string(messages), itial_time))
//{
//	//configfile, state_file, logfile, messages, itial_time
//}

#if DEBUG
void Model::print_env()
{
	this->_env->print_env();
}
void Model::test()
{
	std::cout << "Succes!!!\n";
}
#endif



//void Model::time_shift(unsigned int time)
//{
//}
//
//void Model::do_step()
//{
//	//this->_env->do_step();
//}


//void test()
//{
//	std::cout<<"You got it!\n";
//}
//
//Test::Test()
//{
//}
//
//void Test::call()
//{
//	std::cout << "You got it again!\n";
//}
