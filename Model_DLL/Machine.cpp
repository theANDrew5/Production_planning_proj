//
// Created by User on 10-Feb-20.
//
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Machine.h"

//========================		Machine class methods	================================ класс интерфейс

Machine::Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, bool state, unsigned int time, std::list<Batch*> batches):
    _ID(ID), _recipes(recipes), _batches(batches), _state(state), _time(time)
{
    switch (type)
    {
    case FLOW:
        this->Processor = new Flow_Processing();
        break;
    case GROUP:
        break;
    case STACK:
        break;
    default:
        break;
    }
    this->_last_resipe = Recipe();
}

Machine::Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int count, bool state, unsigned int time, std::list<Batch*> batches)
{
    switch (type)
    {
    case FLOW:
        break;
    case GROUP:
        this->Processor = new Group_Processing(count);
        break;
    case STACK:
        this->Processor = new Stack_Processing(count);
        break;
    default:
        break;
    }
    this->_last_resipe = Recipe();
}

Machine::Machine(const Machine &p):
_ID(p._ID), _batches(p._batches),_recipes(p._recipes), _state(p._state),_time(p._time)
{_last_resipe= Recipe ();}


unsigned int Machine::get_ID()
{
	return this->_ID;
}

void Machine::addRecipe(Recipe newRecipe)
{
	this->_recipes.push_back(newRecipe);
}


bool Machine::check_queue()
{
    return (this->_batches.empty());
}

void Machine::insert_batch(Batch* btc, unsigned int pos)
{
	//замена нулевого элемента неадо исправить
	/*
	if (pos == 0) //нельзя заменять нулевой элемент он уже в потоке событий!
	{
		throw(-1);
	}*/
    unsigned int n = 0;
    auto btc_pos = this->_batches.begin();
    while (n!= pos && !this->_batches.empty())
    {
        btc_pos++;
        n++;
    }
    this->_batches.insert(btc_pos, btc);

}

void Machine::insert_batch(std::deque<Batch*> &container, unsigned int pos)
{//замена нулевого элемента неадо исправить
	/*
	if (pos == 0) //нельзя заменять нулевой элемент он уже в потоке событий!
	{
		throw(-1);
	}
	*/
    for (auto n:container)
    {
        this->insert_batch(n,pos++);
    }
}

void Machine::replace_queue(std::deque<Batch *> &container)
{
	//замена нулевого элемента неадо исправить
	//нельзя заменять нулевой элемент, он уже в потоке событий
	this->_batches.erase(_batches.begin(), this->_batches.end());
    unsigned int pos=0;
    for (auto n:container)
    {
        this->insert_batch(n,pos++);
    }
}

std::ostream &operator<<(std::ostream & os, Machine &p)//перегрузка оператора сдвига для вывода
{
    os<<"TYPE: "<<p._type;
    os<<"\tID: "<<p._ID;
    os<<"\tSTATE: "<<p._state;
    os<<"\tTIME "<<p._time;
    os<<"\tRECIPES:";
    for(Recipe n:p._recipes) os<<'\t'<<n;
    os<<'\n';
    /*
    for(Batch* n:p._batches) os<<n->get_ID()<<' ';
    os<<'\t';*/
    return os;
}


//
//void to_json(json& j, const Machine& mch)
//{
//    std::deque <int> batch_IDs;
//
//    for (auto btc : mch._batches)
//        batch_IDs.push_back(btc->get_ID());
//
//    j = json{
//        {"Machine_type", mch._type},
//        {"Machine_ID", mch._ID},
//        {"Machine_state", mch._state},
//        {"Machine_time", mch._time},
//        {"Machine_recipes", mch._recipes},
//        {"Machine_batches", batch_IDs},
//        {"Machine_last_resipe", mch._last_resipe}
//    };
//}






