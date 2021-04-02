#pragma once

//#include "pch.h"

#include<string>
#include<vector>
#include"IEnvironement.h"

#ifndef MODEL_EXPORTS
#define MODEL_DLL_API __declspec(dllexport)
#else
#define MODEL_DLL_API __declspec(dllimport)
#endif // !



class Environment;

class Model
{
public:

    MODEL_DLL_API Model(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int itial_time);
    MODEL_DLL_API Model(const char configfile [], const char state_file [], const char logfile [], const char messages [], unsigned int itial_time);
#if DEBUG
    MODEL_DLL_API void print_env();
    MODEL_DLL_API void test();
#endif
private:
    Model();
    IEnvironement* Env;

};



