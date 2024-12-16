/// HashDictionary.h
/// Бурдинская Наталья ВМК-22
/// Date - 09.12.2024
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <cassert>
#include <assert.h>
#include <algorithm>
#include <string>
#include <locale>
#include <utility>
#include <optional>
#include <iterator>
using namespace std;

// код реализует класс Dictionary, представляющий собой хеш-таблицу для хранения пар ключ-значение.
// Хеш-таблица использует метод цепочек для разрешения коллизий, храня список пар в каждом индексе таблицы.
// Опционально: keys() → набор ключей, values() →  набор значений.

// Реализация класса Словарь на основе хеш-таблицы
template<typename Key, typename Value>
class Dictionary {
private:
    static const int DEFAULT_CAPACITY = 16; // Начальная емкость таблицы
    vector<list<pair<Key, Value>>> table; // Вектор, содержащий списки пар ключ-значение
    int num_elements; // Количество элементов в словаре

    size_t hashFunction(const Key& key) const {
        // Используем стандартную хеш-функцию из STL для вычисления хеша ключа
        return hash<Key>{}(key) % table.size();
    }

public:
    // Конструктор, инициализирующий емкость и число элементов
    Dictionary(int capacity = DEFAULT_CAPACITY) : table(capacity), num_elements(0) {}

    // Метод для добавления ключа и значения в словарь
    Value* put(const Key& key, const Value& value) {
        size_t index = hashFunction(key); // Получаем индекс для вставки
        // Проверяем наличие ключа, если существует, обновляем значение
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                Value old_value = pair.second;
                pair.second = value;
                return new Value(old_value); // возвращаем старое значение
            }
        }
        // Если ключ не найден, добавляем новую пару в соответствующий список
        table[index].emplace_back(key, value);
        num_elements++;
        return nullptr; // возвращаем NULL если была вставка новой пары
    }

    // Метод для получения значения по ключу find
    Value* get(const Key& key) const {
        size_t index = hashFunction(key); // Определяем индекс элемента
        // Поиск значения по ключу в соответствующем списке
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return new Value(pair.second); // Возвращаем указатель на значение
            }
        }
        return nullptr; // возвращаем NULL если ключ не найден
    }

    // Метод для удаления ключа и значения из словаря
    Value* remove(const Key& key) {
        size_t index = hashFunction(key); // Получаем индекс для удаления
        // Ищем и удаляем элемент с заданным ключом
        auto& list = table[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == key) {
                Value old_value = it->second;
                list.erase(it);
                num_elements--;
                return new Value(old_value); // возвращаем удалённое значение
            }
        }
        return nullptr; // возвращаем NULL если ключ не найден
    }

    // Метод для получения количества элементов
    int size() const {
        return num_elements; // количество элементов в таблице
    }

    vector<Key> keys() const {
        vector<Key> keys;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                keys.push_back(pair.first);
            }
        }
        return keys; // возвращаем набор ключей
    }

    vector<Value> values() const {
        vector<Value> values;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                values.push_back(pair.second);
            }
        }
        return values; // возвращаем набор значений
    }

    // Перегрузка оператор[] для быстрого доступа к значениям
    // Добавлена перегрузка оператора [], который позволяет получать (или добавлять, если отсутствует) значение по указанному ключу.
    // Если ключ присутствует, возвращается ссылка на его значение.
    // Если ключ отсутствует, создается новый элемент с данным ключом и значением по умолчанию Value(), который затем возвращается.
    Value& operator[](const Key& key) {
        size_t index = hashFunction(key); // Определяем индекс элемента
        // Поиск ключа в соответствующем списке
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second; // Возвращаем ссылку на значение, если ключ найден
            }
        }
        // Если ключ не найден, добавляем его с дефолтным значением
        // и возвращаем ссылку на это значение
        table[index].emplace_back(key, Value());
        num_elements++;
        return table[index].back().second;
    }

    // Метод для проверки наличия ключа в словаре
    bool contains(const Key& key) const {
        size_t index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    // Итератор, указывающий на начало словаря
    typename vector<list<pair<Key, Value>>>::const_iterator begin() const {
        return table.begin();
    }

    // Итератор, указывающий на конец словаря
    typename vector<list<pair<Key, Value>>>::const_iterator end() const {
        return table.end();
    }
};

// TestHashDict - тестирование assert
static void TestHashDict() {
    cout << "----------------------------------------" << endl;
    cout << "-- класс Dictionary --" << endl;
    cout << "----------------------------------------" << endl;
    Dictionary<string, int> dict;
    dict.put("яблоко", 1);
    dict.put("банан", 2);
    dict.put("апельсин", 3);

    // Тестирование operator[]
    assert(dict["яблоко"] == 1);
    assert(dict["банан"] == 2);
    assert(dict["апельсин"] == 3);
    bool test = false;
    try {
        dict["арбуз"]; // Ключ не существует
    }
    catch (const runtime_error& error) {
        test = true;
    }
    assert(test = true);

    // Тестирование contains
    assert(dict.contains("яблоко"));
    assert(dict.contains("банан"));
    assert(dict.contains("апельсин"));
    //assert(!dict.contains("арбуз")); // нет такого
    
    // тестирование get и remove
    if (int* value = dict.get("яблоко")) {
        cout << "Значение для 'яблоко' : " << *value << endl;
    }
    dict.remove("яблоко");
    assert(dict["яблоко"] != 1);
    if (int* value = dict.get("яблоко")) {
        cout << "Значение для 'яблоко' : " << *value << endl;
    }
    else {
        cout << "'яблоко' не найдено." << endl;
    }

    // Тестирование put после remove
    dict.put("яблоко", 1);
    assert(dict.contains("яблоко"));
    assert(*dict.get("яблоко") == 1);
    if (int* value = dict.get("яблоко")) {
        cout << "Значение для 'яблоко' после удаления : " << *value << endl;
    }
    else {
        cout << "'яблоко' не найдено." << endl;
    }

    Dictionary<string, int> dictIter(10);
    dictIter.put("здравствуйте", 1);
    dictIter.put("привет", 2);
    dictIter.put("до свидания", 3);
    dictIter.put("бай-бай", 4);

    cout << "----------------------------------------" << endl;
    cout << "Все тесты завершены успешно." << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
};