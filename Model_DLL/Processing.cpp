#include "pch.h"
#include "Processing.h"


//========================		Flow_Processing class methods	================================
Flow_Processing::Flow_Processing():IProcessing()
{
	this->_type = FLOW;
}

unsigned int Flow_Processing::push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time)
{
    if (!batches.empty())
    {
        Batch* it = batches.front();
        Recipe& rcp = it->get_first();
        if (std::any_of(recipes.begin(), recipes.end(), [rcp](Recipe const r) {return rcp == r; }))
            //проверка рецептов
        {
            return  ((last_resipe == it->get_first()) ?
                rcp.get_time() * it->get_count() : rcp.get_time() * it->get_count() + time); //OK
        }
        else throw (it);//ошибка в очереди партия с неверным рецептом
    }
    else
    {
        Batch* ptr = nullptr;
        throw (ptr); //очередь пуста
    }
}

void Flow_Processing::execute(std::ostream* log, unsigned int& ID , unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe)
{
    Batch* bt_ptr = batches.front();
    if (last_resipe != bt_ptr->get_first())
    {
        *log << "Change_recipe\tMachine_ID: " << ID << "\ttime: " << time << '\n';
        last_resipe = bt_ptr->get_first();
        //вставить вывод в лог
    }
    *log << "Execute_batch\tMachine_ID: " << ID << "\tBatch_ID: " << bt_ptr->get_first().get_ID();
    bt_ptr->execute();
    batches.pop_front();
}

//========================		Group_Processing class methods	================================

Group_Processing::Group_Processing(int count): IProcessing()
{
    this->_type = GROUP;
    this->_count = count;
}

unsigned int Group_Processing::push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time)
{

    //		Check if queue is empty
    if (!batches.empty())
    {
        Batch* firstBatchPtr = batches.front();

        Recipe& firstBatchRecipeRef = firstBatchPtr->get_first();

        if (std::any_of(recipes.begin(), recipes.end(), [firstBatchRecipeRef](Recipe const r) {return firstBatchRecipeRef == r; }))
            //проверка рецептов
        {
            return  ((last_resipe == firstBatchPtr->get_first()) ?

                firstBatchRecipeRef.get_time() :

                firstBatchRecipeRef.get_time() + time); //OK
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

void Group_Processing::execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe)
{
    //		Check if the recipe need to be changed, and change it if requireed
    Batch* btcPtr = batches.front();
    if (last_resipe != btcPtr->get_first())
    {
        last_resipe = btcPtr->get_first();
        *log << "Change_recipe\tMachine_ID: " << ID << "\ttime: " << time << '\n';

    }

    //		Contains the amount of Batch with the same recipes in queue
    int tmpCntr = 0;

    //		Count the group of Batchs with the same recipe from queue, and call Batch.execute() for each of them 
    for (auto iter = batches.begin(); iter != batches.end(); iter++)
    {
        if ((*iter)->get_first() != last_resipe || tmpCntr == this->_count) break;
        (*iter)->execute();

        *log << "Execute_batch\tMachine_ID: " << ID << "\tBatch_ID: " << (*iter)->get_ID() << "\n";

        tmpCntr++;

    }

    //		Drop n = tmpCntr Batches from queue
    for (int i = 0; i < tmpCntr; i++)
    {
        batches.pop_front();
    }
}

//========================		Stack_Processing class methods	================================

Stack_Processing::Stack_Processing(int count)
{
    this->_type = STACK;
    this->_count = count;
}

unsigned int Stack_Processing::push_ev(std::list <Batch*>& batches, std::deque<Recipe>& recipes, Recipe& last_resipe, unsigned int& time)
{
    if (!batches.empty())
    {
        Batch* it = batches.front();
        Recipe& rcp = it->get_first();
        if (std::any_of(recipes.begin(), recipes.end(), [rcp](Recipe const r) {return rcp == r; }))
            //проверка рецептов
        {
            return  ((last_resipe == it->get_first()) ?
                rcp.get_time() * (int(it->get_count() / this->_count) + 1) :
                rcp.get_time() * (int(it->get_count() / this->_count) + 1) + time); //OK
        }
        else throw (it);//ошибка в очереди партия с неверным рецептом
    }
    else
    {
        Batch* ptr = nullptr;
        throw (ptr); //очередь пуста
    }
}

void Stack_Processing::execute(std::ostream* log, unsigned int& ID, unsigned int& time, std::list <Batch*>& batches, Recipe& last_resipe)
{
    Batch* bt_ptr = batches.front();
    if (last_resipe != bt_ptr->get_first())
    {
        *log << "Change_recipe\tMachine_ID: " << ID << "\ttime: " << time << '\n';
        last_resipe = bt_ptr->get_first();
        //вставить вывод в лог
    }
    *log << "Execute_batch\tMachine_ID: " << ID << "\tBatch_ID: " << bt_ptr->get_ID();
    bt_ptr->execute();
    batches.pop_front();
}
