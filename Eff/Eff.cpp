#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <random>

struct ListNode { // ListNode модифицировать нельзя
    ListNode* prev = nullptr; // указатель на предыдущий элемент или nullptr
    ListNode* next = nullptr;
    ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr` 
    std::string data; // произвольные пользовательские данные 
};


std::vector<ListNode> fn(std::vector<std::string>& vec0) {
    std::vector<ListNode> list0;
    int max = 0;
    std::vector<int> a0, a1, a2;
    std::vector<std::map<int, std::string>> aa, aa0;
    for (auto x : vec0) {
        size_t pos = x.find(';');
        if (pos == std::string::npos) {
            std::cout << "Разделитель не найден!\n";
            
        }
        std::string str_part =x.substr(0, pos);
        std::string num_part = x.substr(pos + 1);
        int number = std::stoi(num_part);
        std::map<int, std::string> t0 = { { number, str_part } };
        aa.push_back(t0);
        a0.push_back(number);
    }
    //сортировка
    a1 = a0;
    sort(a1.begin(), a1.end());
    a2 = a1;
    a1.erase(std::unique(a1.begin(), a1.end()),  a1.end()); //удаляем дубликаты
    for (auto x : a1) {
        for (auto y : aa) {if(y.find(x)!=y.end()) aa0.push_back(y); }        
    }
    //переделываем вектор в listNode
    int l1 =a2.size();
    list0.resize(l1);
    for (int i = 0; i < l1; i++ ) {
        
        if (a2[i] < 0) {
            // 1. Создаём источник случайности
            std::random_device rd;
            // 2. Создаём генератор случайных чисел
            std::mt19937 gen(rd());
            // 3. Создаём «распределение» для чисел от 0 до 10
            std::uniform_int_distribution<int> distrib(0, l1);
            // Получаем случайный индекс
            size_t random_index = distrib(gen);

            list0[i].rand = &list0[random_index];
        }
        else if (i < l1 - 1 && a2[i] == a2[i + 1] - 1) {
            list0[i].next = &list0[i+1];
            list0[i + 1].prev = &list0[i];
        }
        list0[i].data = aa[i][a2[i]];

    }
    return list0;
}

int main()
{
    std::vector<std::string> str0;
    std::ifstream inlet_str("inlet.in");
    if(!inlet_str.is_open()) {
        std::cerr << "Ошибка открытия файла!\n";
        return 1;
    }
    std::string line;
    while (std::getline(inlet_str, line)) {
        std::cout << line << "\n";
        str0.push_back(line);
    }
   
    inlet_str.close();
    std::vector<ListNode> li = fn(str0);


    // Открываем файл в бинарном режиме для записи
     std::ofstream out_str0("outlet.out", std::ios::binary);
    if (!out_str0) {
       // std::cerr << "Ошибка открытия файла для записи!\n";
        return 1;
    }

    // Записываем количество строк (опционально, упрощает чтение)
    size_t numStrings = str0.size();
   out_str0.write(reinterpret_cast<const char*>(&numStrings), sizeof(numStrings));

    // Построчная запись: сначала длина строки, затем данные
    for (const auto& str : str0) {
        size_t strLength = str.size();
        // Записываем длину строки
       out_str0.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
        // Записываем сами данные строки
       out_str0.write(str.c_str(), strLength);
    }

   out_str0.close();
  //  std::cout << "Строки успешно записаны в бинарный файл!\n";
    return 0;
}
