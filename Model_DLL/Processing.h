#pragma once
#include "pch.h"
#include "Batch.h"
#include "Recipe.h"

class Machine;

enum class ProcessingType
{
	FLOW,   //0
	GROUP,  //1
	STACK   //2
};

//»нтерфейс обработки партий
class IProcessing
{
public:
	IProcessing(Machine& mptr);

	virtual unsigned int push_ev() = 0;//метод возвращает врем€ событи€
	virtual void execute(std::ostream* log) = 0;//метод выполн€ет событие

	virtual ~IProcessing() = default;

	ProcessingType get_type();
	unsigned int get_count();

	friend void to_json(json j, const IProcessing& prc);//TODO проблема с процессором

protected:
	ProcessingType _type;
	Machine* const _mptr;
	unsigned int _count;
};

//ѕотокова€ обработка
class Flow_Processing: public IProcessing
{
public:
	Flow_Processing(Machine& mptr);
	~Flow_Processing() = default;

	unsigned int push_ev() override;
	void execute(std::ostream* log) override;//метод выполн€ет событие
};

//ќбработка группой изделий
class Group_Processing: public IProcessing
{
public:
	Group_Processing(Machine& mptr, int count);
	~Group_Processing() = default;

	unsigned int push_ev() override;//метод возвращает врем€ событи€
	void execute(std::ostream* log);//метод выполн€ет событие

private:
	Group_Processing();
};

//ќбработка группой партий
class Stack_Processing: public IProcessing
{
public:
	Stack_Processing(Machine& mptr, int count);
	~Stack_Processing() = default;

	unsigned int push_ev() override;//метод возвращает врем€ событи€
	void execute(std::ostream* log) override;//метод выполн€ет событие

private:
	Stack_Processing();
};
