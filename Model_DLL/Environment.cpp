//
// Created by User on 10-Feb-20.
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Environment.h"

Environment::Environment(std::string name, std::map<unsigned int, Batch>& batches, std::map<unsigned int, Machine>& machines, 
    std::deque<Event>& events, unsigned int global_model_time):
    _name(name), _batches(batches), _machines(machines), _events(events), _global_model_time(global_model_time)
{
}

Environment::Environment(std::string name, std::list<Batch>& batches, std::list<Machine>& machines, std::deque<Event>& events, unsigned int global_model_time):
    _name(name), _batches(*new std::map<unsigned int, Batch>{}), _machines(*new std::map<unsigned int, Machine>{}), _events(events), _global_model_time(global_model_time)
{
    for (auto batch : batches)
    {
        _batches.insert(std::pair<unsigned int, Batch>(batch.get_ID(), batch));
    }
    
    for (auto machine : machines)
    {
        _machines.insert(std::pair<unsigned int, Machine>(machine.get_ID(), machine));
    }
}


Batch& Environment::search_batch(unsigned int btc_ID)
{

    return this->_batches[btc_ID];
}

Machine& Environment::search_machine(unsigned int mch_ID)
{
    return this->_machines[mch_ID];
}

std::deque<Event>::iterator Environment::search_event(Machine& ptr)
{
    auto it=this->_events.begin();
    while (it->get_ptr()!=&ptr) it++;
    return it;
}

void Environment::add_batch(std::string j_string)
{
    json j = json::parse(j_string);
    this->_batches.insert(std::pair<int, Batch>(j.at("Batch_ID").get<unsigned int>(), Batch(j.get<Batch>())));
}

void Environment::add_machine(std::string j_string)
{
    json j = json::parse(j_string);
    this->_machines.insert(std::pair<int, Machine>(j.at("Machine_ID").get<unsigned int>(), Machine(j.get<Machine>())));
}

void Environment::change_event(Machine& mch)
{
    auto ev_it=this->search_event(mch);
    this->_events.erase(ev_it);
    this->push_event(mch);
}

void Environment::push_event(Machine &mch)
{
    try
    {
        this->_events.emplace_back(mch, mch._processor->push_ev());
    }
    catch (Batch* bt_ptr)
    {
        if (bt_ptr!= nullptr)
        {
            *this->_messages << "Batch with wrong recipe!\n\tMachine ID: " << mch.get_ID()

                       << "\n\tBatch ID: " << bt_ptr->get_ID() << '\n';
            throw (-1);//рассчёт событий прерван
        }
        else
            *this->_messages<<"Queue is empty!\n\tMachine ID: "<<mch.get_ID()<<'\n';
        return;
    }
    //сортируем
    Event& last=this->_events.back();
    for (auto ev=this->_events.begin();ev!=--(this->_events.end());ev++)
    {
        if (*ev>this->_events.back())
        {
            this->_events.insert(ev, this->_events.back());
            this->_events.pop_back();
            break;
        }
    }
}


//метод рассчёта событий
void Environment::make_events()
{
    for(auto pair : this->_machines)
    {
        try
        {
            this->push_event(pair.second);
        }
        catch (int)
        {
            *this->_messages<<"Modelling stopped!\n";
        }
    }

    if(DEBUG)
    {
        for (auto n:this->_events) std::cout<<n<<'\t';
        std::cout<<'\n';
    }

}



void Environment::do_step(unsigned int n)
{
    if (n < 1) return;
    try
    {
        if (this->_events.empty()) throw (-1);
        for (int i = 0; i < n; ++i)
        {
            auto ev_it = this->_events.begin();
            *this->_messages << "MODEL_TIME: " << this->_global_model_time << '\n';
            if (this->_events.empty()) throw (i);
            this->_global_model_time += ev_it->get_time();
            auto ev_it_f = ev_it;
            ++ev_it_f;
            for (ev_it_f; ev_it_f != this->_events.end()--; ev_it_f++)
            {
                ev_it_f->time_shift(ev_it->get_time());
            }
            ev_it->execute(this->_messages);
            Machine * m_ptr=ev_it->get_ptr();
            ev_it++;
            this->_events.pop_front();
            this->push_event(*m_ptr);
        }

    }
    catch (int err)
    {
        switch (err)
        {
            case -1:
                *this->_messages << "Event vector is empty!\n";
                break;
            default:
                *this->_messages << "End of event vector reached by step:\t"<<err<<'\n';
        }
        return;
    }

    if (DEBUG)
    {
        for (auto n:this->_events) std::cout<<n<<'\t';
        std::cout<<'\n';
    }
}

void Environment::do_step()
{
    while (!this->_events.empty())
    {
        this->do_step(1);
    }
}

void Environment::q_add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos)
{
    Batch& btc=search_batch(btc_ID);
    Machine& mch=search_machine(mch_ID);
    bool push_event = mch.check_queue();//проверка на пустую очередь
    mch.insert_batch(&btc, pos);
    if (push_event) this->push_event(mch);
    if(push_event==0 && pos==0)//необходимо поменять event
    {
        this->change_event(mch);
    }
    //выводим сообщение
    *this->_messages<<"Batch added:\nBatch:\t"<<btc_ID<<"\tMachine:\t"<<mch_ID<<'\n';
}

void Environment::q_add_batch(std::vector<unsigned int> btc_IDs, unsigned int mch_ID, unsigned int pos)
{
    Machine& mch = this->search_machine(mch_ID);
    bool push_event = mch.check_queue();//проверка на пустую очередь
    std::deque <Batch*> batches ={};
    for (auto n:btc_IDs)
    {
        Batch* btc =&this->search_batch(n);
        batches.push_back(btc);
    }
    mch.insert_batch(batches,pos);
    if (push_event) this->push_event(mch);
    if(push_event==0 && pos==0)//необходимо поменять event
    {
        this->change_event(mch);
    }
    //выводим сообщение
    *this->_messages<<"Batches added:\nBatches:\t";
    for (auto n:btc_IDs)
        *this->_messages<<n<<' ';
    *this->_messages<<"\tMachine:\t"<<mch_ID<<'\n';
}

void Environment::replace_queue(std::vector<unsigned int> btc_IDs, unsigned int mch_ID)
{
    Machine& mch = this->search_machine(mch_ID);
    bool push_event = mch.check_queue();//проверка на пустую очередь
    std::deque <Batch*> batches ={};
    for (auto n:btc_IDs)
    {
        Batch* btc =&this->search_batch(n);
        batches.push_back(btc);
    }
    mch.replace_queue(batches);
    if (push_event) this->push_event(mch);
    else this->change_event(mch);
    //выводим сообщение
    *this->_messages<<"Queue replaced:\nBatches:\t";
    for (auto n:btc_IDs)
        *this->_messages<<n<<' ';
    *this->_messages<<"\tMachine:\t"<<mch_ID<<'\n';
}

void Environment::do_step_till_machine(unsigned int mch_ID)
{
    Machine* m_ptr = &this->search_machine(mch_ID);
    while (this->_events.front().get_ptr() != m_ptr)
    {
        this->do_step(1);
    }
}

void Environment::time_shift(unsigned int time)
{
    while (this->_events.front().get_time() < time)
    {
        time -= this->_events.front().get_time();
        this->do_step(1);
    }
    for (auto n : this->_events)
    {
        n.time_shift(time);
    }
    this->_global_model_time += time;

    if (DEBUG) std::cout << this->_global_model_time << '\n';
}


void to_json(json& j, const Environment& env)
{
    j = json{
        {"Environment_name", env._name},
        {"Environment_batches", env._batches},
        {"Environment_machines", env._machines}
    };
}


#if DEBUG
//отладочный метод для просмотра среды
void Environment::print_env()
{

        std::cout<<"NAME:\t" << this->_name << '\n';
        
        std::cout << "EVENTS:\t";
        for (auto n : this->_events)
        {
            std::cout << n << '\t';
        }
        std::cout << '\n';

        std::cout << "MACHINES:\t";
        for (auto n : this->_machines)
        {
            std::cout << n << '\t';
        }
        std::cout << '\n';

        std::cout << "BATCHES:\t";
        for (auto n : this->_batches)
        {
            std::cout << n << '\t';
        }
        std::cout << '\n';
}
#endif








































