// Test_Model.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include"pch.h"
#include "Recipe.h"
#include "Batch.h"
#include "Machine.h"
#include "Environment.h"
#include <nlohmann/json.hpp>

int main()
{
    Recipe *r1 = new Recipe(1, 100);
    json j{
        {"Recipe_ID", 2},
        {"Recipe_time", 200}
    };
    Recipe *r2 = new Recipe (j.get<Recipe>());
    

    Batch& b1 = *new Batch(1, 10, { *r1, *r2 });
    Batch& b2 = *new Batch(2, 20, { *r1, *r2 });
    Batch& b3 = *new Batch(3, 30, { *r1, *r2 });
    


    //Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, bool state = true, std::list<Batch*> batches = {}, Recipe l_rcp = NULL);
    //Machine(int ID, ProcessingType type, std::deque<Recipe> recipes, unsigned int time, unsigned int count, bool state = true, std::list<Batch*> batches = {}, Recipe l_rcp = NULL);

    Machine& mch1 = *new Machine(1, ProcessingType::FLOW, {*r1, *r2 }, 10, 0);
    Machine& mch2 = *new Machine(2, ProcessingType::GROUP, { *r1, *r2 }, 10, 100);
    Machine& mch3 = *new Machine(1, ProcessingType::STACK, { *r1, *r2 }, 10, 100);

    json j1 = mch1;
    json j2 = mch2;
    json j3 = mch3;

    Machine mch4 = Machine(j1.get<Machine>());
    Machine mch5 = Machine(j2.get<Machine>());
    Machine mch6 = j3.get<Machine>();

    std::list<Batch> bt_list = { b1, b2, b3 };
    std::list<Machine> mch_list = { mch1, mch1, mch3, mch4, mch5, mch6 };

    Environment& env = *new Environment("env1", bt_list, mch_list);

    json j5 = env;

    Environment env2 = j5.get<Environment>();
    std::cout << j5 <<'\n';
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
