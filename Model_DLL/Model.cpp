
#include "pch.h"
#include "Model.h"
#include "Environment.h"'
#include "IEnvironement.h"



Model::Model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int itial_time)
	: Env(new Environment(configfile, state_file, logfile, messages, itial_time))
{
}

Model::Model(const char configfile[], const char state_file[], const char logfile[], const char messages[], unsigned int itial_time)
	: Env(new Environment(configfile, state_file, logfile, messages, itial_time))
{
}


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
