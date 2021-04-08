//
// Created by User on 10-Feb-20.
//

#pragma once

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Batch.h"
#include "Recipe.h"
#include "Processing.h"


//Класс интерфейс


class Machine
{
    friend class Flow_Processing;
    friend class Group_Processing;
    friend class Stack_Processing;

public:

    Machine();//конструктор без параметров

    //Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, bool state = true, std::list<Batch*> batches = {}, Recipe l_rcp=NULL);
    Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, unsigned int count, bool state = true, std::list<Batch*> batches = {}, Recipe l_rcp = NULL);
    Machine(const Machine & p);//конструктор копирования
    ~Machine() = default;//деструктор

    //virtual unsigned int push_ev()=0;//метод возвращает время события
    //virtual void execute(std::ostream *log) =0;//метод выполняет событие

    unsigned int get_ID();//возвращает ID машины
    void insert_batch(Batch* btc, unsigned int pos);//вставляет партию в очередь
    void insert_batch(std::deque <Batch*> &container, unsigned int pos=0);//вставляет несколько партий в очередь
    void replace_queue(std::deque <Batch*> &container);//заменяет очередь
    bool check_queue();//проверяет на нулевую очередь
	void addRecipe(Recipe newRecipe);

    friend void to_json(json& j, const Machine& mch);
    friend void from_json(const json& j, Machine& mch);

    friend std::ostream& operator<<(std::ostream& os, Machine& p);//перегрузка оператора <<

private:
    unsigned int _ID;//имя
    bool _state;//состояние
    unsigned int _time;//время смены рецепта
    std::deque <Recipe> _recipes;//рецепты на машине
    std::list <Batch*> _batches;// входная очередь в виде ссылок на партии
    Recipe _last_resipe;//последний рецепт
    IProcessing* _processor;



    //json to_json() const;
};
