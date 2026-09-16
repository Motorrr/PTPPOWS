#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "text_tools.hpp"

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    const string dataFile = "WAP.txt";

    int key = -1;
    while (key != 0) {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1 - Частотный словарь (уникальные)\n";
        cout << "2 - Индекс позиций слов\n";
        cout << "3 - Задание 3a: простые -> квадрат\n";
        cout << "4 - Задание 3b: спец. сортировка\n";
        cout << "5 - Задание 3c: уникальные в [a,b]\n";
        cout << "0 - Завершить работу\n";
        cout << "Пункт меню > ";
        cin >> key;

        switch (key) {
        case 1:
            try {
                showWordFrequency(loadText(dataFile));
            }
            catch (const exception& ex) {
                cerr << "[Ошибка] " << ex.what() << '\n';
            }
            break;

        case 2:
            try {
                showWordPositions(loadText(dataFile));
            }
            catch (const exception& ex) {
                cerr << "[Ошибка] " << ex.what() << '\n';
            }
            break;

        case 3:
            runTaskA();
            break;

        case 4:
            runTaskB();
            break;

        case 5:
            runTaskC();
            break;

        case 0:
            cout << "Работа завершена.\n";
            break;

        default:
            cout << "Неверный пункт. Допустимо 0..5.\n";
        }

        if (key != 0) {
            cout << "\n<Enter> — вернуться в меню...";
            cin.ignore();
            cin.get();
        }
    }
    return 0;
}