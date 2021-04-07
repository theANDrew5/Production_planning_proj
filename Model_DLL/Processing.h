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

//��������� ��������� ������
class IProcessing
{
public:

	virtual unsigned int push_ev(std::list <Batch*> &batches, std::deque<Recipe> &recipes, Recipe& last_resipe, unsigned int& time) = 0;//����� ���������� ����� �������
	virtual void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe) = 0;//����� ��������� �������

	virtual ~IProcessing() = default;

protected:
	ProcessingType _type;//TODO ������� �� ������������ ���
};

//��������� ���������
class Flow_Processing: public IProcessing
{
public:
	Flow_Processing();
	~Flow_Processing() = default;

	unsigned int push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time) override;
	void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe) override;//����� ��������� �������
};

//��������� ������� �������
class Group_Processing: public IProcessing
{
public:
	Group_Processing(int count);
	~Group_Processing() = default;

	unsigned int push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time);//����� ���������� ����� �������
	void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe);//����� ��������� �������

private:
	unsigned int _count;

	Group_Processing();
};

//��������� ������� ������
class Stack_Processing: public IProcessing
{
public:
	Stack_Processing(int count);
	~Stack_Processing() = default;

	unsigned int push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time) override;//����� ���������� ����� �������
	void execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe) override;//����� ��������� �������

private:
	unsigned int _count;

	Stack_Processing();
};
