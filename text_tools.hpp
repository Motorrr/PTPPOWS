#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <cctype>

using namespace std;

inline string toLowerCp1251(const string& src) {
    string res = src;
    for (char& ch : res) {
        unsigned char u = static_cast<unsigned char>(ch);
        if (u < 0x80) {
            ch = static_cast<char>(tolower(u));
        }
        else if (u >= 0xC0 && u <= 0xDF) {
            ch = static_cast<char>(u + 0x20);
        }
        else if (u == 0xA8) {
            ch = static_cast<char>(0xB8);
        }
    }
    return res;
}

inline bool isCyrLetter(unsigned char c) {
    if (c < 0x80) return isalpha(c) != 0;
    return (c >= 0xC0) || c == 0xA8 || c == 0xB8;
}

inline string loadText(const string& fileName) {
    ifstream fin(fileName, ios::binary);
    if (!fin.is_open())
        throw runtime_error("не открывается файл " + fileName);
    ostringstream buf;
    buf << fin.rdbuf();
    return buf.str();
}

inline vector<string> splitWords(const string& source, size_t* wordsCount = nullptr) {
    string s = toLowerCp1251(source);
    vector<string> words;
    string cur;
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (isCyrLetter(c)) {
            cur.push_back(s[i]);
        }
        else if (!cur.empty()) {
            words.push_back(cur);
            cur.clear();
        }
    }
    if (!cur.empty()) words.push_back(cur);
    if (wordsCount) *wordsCount = words.size();
    return words;
}

inline void showWordFrequency(const string& text) {
    vector<string> words = splitWords(text);

    map<string, int> freq;
    for (const auto& w : words) ++freq[w];

    cout << "\n== Частотный словарь ==\n";
    for (const auto& kv : freq)
        cout << kv.first << " - " << kv.second << '\n';
    cout << "Всего уникальных слов: " << freq.size() << '\n';
}

inline void showWordPositions(const string& text) {
    vector<string> words = splitWords(text);

    map<string, vector<int>> idx;
    for (size_t k = 0; k < words.size(); ++k)
        idx[words[k]].push_back(static_cast<int>(k));

    cout << "\n== Индекс позиций ==\n";
    for (const auto& kv : idx) {
        cout << kv.first << " -- ";
        for (size_t i = 0; i < kv.second.size(); ++i) {
            if (i) cout << ", ";
            cout << kv.second[i];
        }
        cout << '\n';
    }
}

inline bool isPrimeNumber(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int d = 3; d * 1LL * d <= n; d += 2)
        if (n % d == 0) return false;
    return true;
}

inline vector<int> inputNumbers() {
    int n;
    cout << "Размер массива: ";
    cin >> n;
    if (n < 0) n = 0;

    vector<int> data(static_cast<size_t>(n));
    if (n > 0) {
        cout << "Введите " << n << " целых чисел: ";
        for (int i = 0; i < n; ++i) cin >> data[i];
    }
    return data;
}

inline void showNumbers(const string& title, const vector<int>& v) {
    cout << title;
    for (int x : v) cout << x << ' ';
    cout << '\n';
}

inline void runTaskA() {
    cout << "\n== 3a: простые числа в квадрат ==\n";
    vector<int> v = inputNumbers();
    showNumbers("Было:   ", v);

    for_each(v.begin(), v.end(), [](int& x) {
        if (isPrimeNumber(x)) x *= x;
        });

    showNumbers("Стало:  ", v);
}

inline void runTaskB() {
    cout << "\n== 3b: нечётные ?, чётные ? ==\n";
    vector<int> v = inputNumbers();
    showNumbers("Было:   ", v);

    auto it = partition(v.begin(), v.end(), [](int x) { return x % 2 != 0; });
    sort(v.begin(), it, less<int>());
    sort(it, v.end(), greater<int>());

    showNumbers("Стало:  ", v);
}

inline void runTaskC() {
    cout << "\n== 3c: уникальные в диапазоне ==\n";
    vector<int> v = inputNumbers();

    int lo, hi;
    cout << "Левая граница  : "; cin >> lo;
    cout << "Правая граница : "; cin >> hi;

    showNumbers("Исходный:  ", v);

    set<int> uniqueInRange;
    for (int x : v)
        if (x >= lo && x <= hi) uniqueInRange.insert(x);

    vector<int> result(uniqueInRange.begin(), uniqueInRange.end());
    cout << "Диапазон [" << lo << "; " << hi << "]\n";
    showNumbers("Уникальные: ", result);
}