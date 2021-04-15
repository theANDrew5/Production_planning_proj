// Test_Model.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

#include "Environment.h"
#include "Machine.h"
#include "Batch.h"
#include "Recipe.h"

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
       

       Machine& mch1 = *new Machine(1, ProcessingType::FLOW, {*r1, *r2 }, 10, 0);
       Machine& mch2 = *new Machine(2, ProcessingType::GROUP, { *r1, *r2 }, 10, 100);
       Machine& mch3 = *new Machine(3, ProcessingType::STACK, { *r1, *r2 }, 10, 100);

       json j1 = mch1;
       json j2 = mch2;
       json j3 = mch3;
       
       Machine mch4 = j1.get<Machine>();

       std::list<Batch> bt_list = { b1, b2, b3 };
       std::list<Machine> mch_list = { mch1, mch2, mch3};

       Environment& env = *new Environment("env1", bt_list, mch_list);

       json j5 = env;

       std::string j_str = j5.dump();

       Environment& env2 = *new Environment (j5);

       std::ofstream config("model_config.txt");
       
       config << j_str;
       config.close();
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
