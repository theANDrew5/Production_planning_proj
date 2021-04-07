#include "pch.h"
#include "Processing.h"
#include "Machine.h"



//========================		IProcessing class methods	================================
IProcessing::IProcessing(const Machine& mptr):_mptr(&mptr)
{
}

//========================		Flow_Processing class methods	================================
Flow_Processing::Flow_Processing(const Machine& mptr):IProcessing(mptr)
{
	this->_type = FLOW;
}

unsigned int Flow_Processing::push_ev()
{
    if (!_mptr->_batches.empty())
    {
        Batch* it = _mptr->_batches.front();
        Recipe& rcp = it->get_first();
        if (std::any_of(_mptr->_recipes.begin(), _mptr->_recipes.end(), [rcp](Recipe const r) {return rcp == r; }))
            //проверка рецептов
        {
            return  ((_mptr->_last_resipe == it->get_first()) ?
                rcp.get_time() * it->get_count() : rcp.get_time() * it->get_count() + _mptr->_time); //OK
        }
        else throw (it);//ошибка в очереди партия с неверным рецептом
    }
    else
    {
        Batch* ptr = nullptr;
        throw (ptr); //очередь пуста
    }
}

void Flow_Processing::execute(std::ostream* log)
{
    Batch* bt_ptr = _mptr->_batches.front();
    if (_mptr->_last_resipe != bt_ptr->get_first())
    {
        *log << "Change_recipe\tMachine_ID: " << _mptr->_ID << "\ttime: " << time << '\n';
        _mptr->_last_resipe = bt_ptr->get_first();
        //вставить вывод в лог
    }
    *log << "Execute_batch\tMachine_ID: " << _mptr->_ID << "\tBatch_ID: " << bt_ptr->get_first().get_ID();
    bt_ptr->execute();
    _mptr->_batches.pop_front();
}

//========================		Group_Processing class methods	================================

Group_Processing::Group_Processing(const Machine& mptr, int count): IProcessing(mptr)
{
    this->_type = GROUP;
    this->_count = count;
}

unsigned int Group_Processing::push_ev()
{

    //		Check if queue is empty
    if (!_mptr->_batches.empty())
    {
        Batch* firstBatchPtr = _mptr->_batches.front();

        Recipe& firstBatchRecipeRef = firstBatchPtr->get_first();

        if (std::any_of(_mptr->_recipes.begin(), _mptr->_recipes.end(), [firstBatchRecipeRef](Recipe const r) {return firstBatchRecipeRef == r; }))
            //проверка рецептов
        {
            return  ((_mptr->_last_resipe == firstBatchPtr->get_first()) ?

                firstBatchRecipeRef.get_time() :

                firstBatchRecipeRef.get_time() + _mptr->_time); //OK
        }
        else throw (firstBatchPtr);//ошибка в очереди партия с неверным рецептом

    }
    else
    {

        //		null pointer exception
        Batch* ptr = nullptr;

        throw (ptr);
    }
}

void Group_Processing::execute(std::ostream* log)
{
    //		Check if the recipe need to be changed, and change it if requireed
    Batch* btcPtr = _mptr->_batches.front();
    if (_mptr->_last_resipe != btcPtr->get_first())
    {
        _mptr->_last_resipe = btcPtr->get_first();
        *log << "Change_recipe\tMachine_ID: " << _mptr->_ID << "\ttime: " << time << '\n';

    }

    //		Contains the amount of Batch with the same recipes in queue
    int tmpCntr = 0;

    //		Count the group of Batchs with the same recipe from queue, and call Batch.execute() for each of them 
    for (auto iter = _mptr->_batches.begin(); iter != _mptr->_batches.end(); iter++)
    {
        if ((*iter)->get_first() != _mptr->_last_resipe || tmpCntr == this->_count) break;
        (*iter)->execute();

        *log << "Execute_batch\tMachine_ID: " << _mptr->_ID << "\tBatch_ID: " << (*iter)->get_ID() << "\n";

        tmpCntr++;

    }

    //		Drop n = tmpCntr Batches from queue
    for (int i = 0; i < tmpCntr; i++)
    {
        _mptr->_batches.pop_front();
    }
}

//========================		Stack_Processing class methods	================================

Stack_Processing::Stack_Processing(const Machine& mptr, int count):IProcessing(mptr)
{
    this->_type = STACK;
    this->_count = count;
}

unsigned int Stack_Processing::push_ev()
{
    if (!_mptr->_batches.empty())
    {
        Batch* it = _mptr->_batches.front();
        Recipe& rcp = it->get_first();
        if (std::any_of(_mptr->_recipes.begin(), _mptr->_recipes.end(), [rcp](Recipe const r) {return rcp == r; }))
            //проверка рецептов
        {
            return  ((_mptr->_last_resipe == it->get_first()) ?
                rcp.get_time() * (int(it->get_count() / this->_count) + 1) :
                rcp.get_time() * (int(it->get_count() / this->_count) + 1) + _mptr->_time); //OK
        }
        else throw (it);//ошибка в очереди партия с неверным рецептом
    }
    else
    {
        Batch* ptr = nullptr;
        throw (ptr); //очередь пуста
    }
}

void Stack_Processing::execute(std::ostream* log)
{
    Batch* bt_ptr = _mptr->_batches.front();
    if (_mptr->_last_resipe != bt_ptr->get_first())
    {
        *log << "Change_recipe\tMachine_ID: " << _mptr->_ID << "\ttime: " << time << '\n';
        _mptr->_last_resipe = bt_ptr->get_first();
        //вставить вывод в лог
    }
    *log << "Execute_batch\tMachine_ID: " << _mptr->_ID << "\tBatch_ID: " << bt_ptr->get_ID();
    bt_ptr->execute();
    _mptr->_batches.pop_front();
}


