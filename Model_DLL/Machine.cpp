//
// Created by User on 10-Feb-20.
//
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Machine.h"

//========================		Machine class methods	================================ класс интерфейс

//Machine::Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, bool state, std::list<Batch*> batches, Recipe l_rcp):
//    _ID(ID), _recipes(recipes), _batches(batches), _state(state), _time(time)
//{
//    switch (type)
//    {
//    case FLOW:
//
//    case GROUP:
//        break;
//    case STACK:
//        break;
//    default:
//        break;
//    }
//    if (l_rcp!=NULL)
//        this->_last_resipe = l_rcp;
//    else
//        this->_last_resipe = Recipe();
//}

Machine::Machine()
{

}

Machine::Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, unsigned int count, bool state, std::list<Batch*> batches, Recipe l_rcp):
    _ID(ID), _recipes(recipes), _time(time), _state(state), _batches(batches), _last_resipe(l_rcp)
{
    switch (type)
    {
    case ProcessingType::FLOW:
        this->_processor = new Flow_Processing(*this);
        break;
    case ProcessingType::GROUP:
        this->_processor = new Group_Processing(*this, count);
        break;
    case ProcessingType::STACK:
        this->_processor = new Stack_Processing(*this, count);
        break;
    default:
        break;
    }
}



Machine::Machine(const Machine &p):
    _ID(p._ID), _processor(p._processor), _recipes(p._recipes), _time(p._time), _state(p._state), _batches(p._batches), _last_resipe(p._last_resipe)
{
}


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
	if (pos == 0) //если pos = 0 добавляем в конец
	{
        this->_batches.push_back(btc);
        return;
	}
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

	if (pos == 0) //нельзя заменять нулевой элемент он уже в потоке событий!
	{
        this->_batches.insert(this->_batches.end(), container.begin(), container.end());
        return;
	}
    unsigned int n = 0;
    auto btc_pos = this->_batches.begin();
    while (n != pos && !this->_batches.empty())
    {
        btc_pos++;
        n++;
    }
    this->_batches.insert(btc_pos, container.begin(), container.end());

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

void to_json(json& j, const Machine& mch)
{
    //std::deque <int> batch_IDs;

    //for (auto btc : mch._batches)
    //    batch_IDs.push_back(btc->get_ID());

    //Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, unsigned int count, bool state, std::list<Batch*> batches, Recipe l_rcp) :

    j = json{
        {"Machine_ID", mch._ID},
        {"Machine_type", mch._processor->get_type()},
        {"Machine_recipes", mch._recipes},
        {"Machine_time", mch._time},
        {"Machine_count", mch._processor->get_count()}
        //{"Machine_state", mch._state},
        //{"Machine_batches", batch_IDs},
        //{"Machine_last_resipe", mch._last_resipe}
    };
}

void from_json(const json& j, Machine& mch)
{
    //(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, unsigned int count, bool state, std::list<Batch*> batches, Recipe l_rcp)
    Machine p = Machine(
        j.at("Machine_ID").get<int>(),
        j.at("Machine_type").get<ProcessingType>(),
        j.at("Machine_recipes").get<std::deque<Recipe>>(),
        j.at("Machine_time").get<int>(),
        j.at("Machine_count").get<int>());
    mch = p;
}

std::ostream &operator<<(std::ostream & os, Machine &p)//перегрузка оператора сдвига для вывода
{
    //os<<"TYPE: "<<p._type;
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






