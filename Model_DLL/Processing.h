#pragma once
#include "pch.h"
#include "Batch.h"
#include "Recipe.h"

class Machine;

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
	IProcessing(const Machine& mptr);

	virtual unsigned int push_ev() = 0;//����� ���������� ����� �������
	virtual void execute(std::ostream* log) = 0;//����� ��������� �������

	virtual ~IProcessing() = default;

protected:
	ProcessingType _type;
	Machine* const _mptr;
};

//��������� ���������
class Flow_Processing: public IProcessing
{
public:
	Flow_Processing(const Machine& mptr);
	~Flow_Processing() = default;

	unsigned int push_ev() override;
	void execute(std::ostream* log) override;//����� ��������� �������
};

//��������� ������� �������
class Group_Processing: public IProcessing
{
public:
	Group_Processing(const Machine& mptr, int count);
	~Group_Processing() = default;

	unsigned int push_ev() override;//����� ���������� ����� �������
	void execute(std::ostream* log);//����� ��������� �������

private:
	unsigned int _count;

	Group_Processing();
};

//��������� ������� ������
class Stack_Processing: public IProcessing
{
public:
	Stack_Processing(const Machine& mptr, int count);
	~Stack_Processing() = default;

	unsigned int push_ev() override;//����� ���������� ����� �������
	void execute(std::ostream* log) override;//����� ��������� �������

private:
	unsigned int _count;

	Stack_Processing();
};
