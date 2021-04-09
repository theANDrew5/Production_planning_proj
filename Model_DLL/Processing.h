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

//��������� ��������� ������
class IProcessing
{
public:
	IProcessing(Machine& mptr);

	virtual unsigned int push_ev() = 0;//����� ���������� ����� �������
	virtual void execute(std::ostream* log) = 0;//����� ��������� �������

	virtual ~IProcessing() = default;

	ProcessingType get_type();
	unsigned int get_count();

	friend void to_json(json j, const IProcessing& prc);//TODO �������� � �����������

protected:
	ProcessingType _type;
	Machine* const _mptr;
	unsigned int _count;
};

//��������� ���������
class Flow_Processing: public IProcessing
{
public:
	Flow_Processing(Machine& mptr);
	~Flow_Processing() = default;

	unsigned int push_ev() override;
	void execute(std::ostream* log) override;//����� ��������� �������
};

//��������� ������� �������
class Group_Processing: public IProcessing
{
public:
	Group_Processing(Machine& mptr, int count);
	~Group_Processing() = default;

	unsigned int push_ev() override;//����� ���������� ����� �������
	void execute(std::ostream* log);//����� ��������� �������

private:
	Group_Processing();
};

//��������� ������� ������
class Stack_Processing: public IProcessing
{
public:
	Stack_Processing(Machine& mptr, int count);
	~Stack_Processing() = default;

	unsigned int push_ev() override;//����� ���������� ����� �������
	void execute(std::ostream* log) override;//����� ��������� �������

private:
	Stack_Processing();
};
