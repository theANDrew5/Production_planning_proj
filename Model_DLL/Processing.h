#pragma once
#include "pch.h"
#include "Batch.h"
#include "Recipe.h"


enum ProcessingType
{
	FLOW,   //0
	GROUP,  //1
	STACK   //2
};

//»нтерфейс обработки партий
class IProcessing
{
public:

	virtual unsigned int push_ev(std::list <Batch*> &batches, std::deque<Recipe> &recipes, Recipe& last_resipe, unsigned int& time) = 0;//метод возвращает врем€ событи€
	virtual void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe) = 0;//метод выполн€ет событие

	virtual ~IProcessing() = default;

protected:
	ProcessingType _type;//TODO перейти на перечислимый тип
};

//ѕотокова€ обработка
class Flow_Processing: public IProcessing
{
public:
	Flow_Processing();
	~Flow_Processing() = default;

	unsigned int push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time) override;
	void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe) override;//метод выполн€ет событие
};

//ќбработка группой изделий
class Group_Processing: public IProcessing
{
public:
	Group_Processing(int count);
	~Group_Processing() = default;

	unsigned int push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time);//метод возвращает врем€ событи€
	void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe);//метод выполн€ет событие

private:
	unsigned int _count;

	Group_Processing();
};

//ќбработка группой партий
class Stack_Processing: public IProcessing
{
public:
	Stack_Processing(int count);
	~Stack_Processing() = default;

	unsigned int push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time) override;//метод возвращает врем€ событи€
	void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe) override;//метод выполн€ет событие

private:
	unsigned int _count;

	Stack_Processing();
};
