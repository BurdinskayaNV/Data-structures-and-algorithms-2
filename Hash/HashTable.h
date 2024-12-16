/// HashTable.h
/// Бурдинская Наталья ВМК-22
/// Date - 04.12.2024
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <string>
#include <locale>
using namespace std;

// Шаблонный класс Хеш таблицы.
// Хеш-таблица — структура данных, реализующая интерфейс ассоциативного массива, 
// а именно, она позволяет хранить пары (ключ, значение) и выполнять три операции:
// операцию добавления новой пары, операцию удаления пары, операцию поиска пары по ключу.
// Возможно задание произвольной хеш-функции.
template <typename Key>
class HashTable {
private:
    vector<list<Key>> table; // Вектор, в котором хранятся ключи
    // таблица представлена в виде вектора, где каждый элемент представляет собой связный список
    // Каждый связный список будет хранить ключи, которые имеют одинаковый хеш-индекс (то есть произошло совпадение хешей).
    function<size_t(const Key&)> hashFunction; // Хеш-функция и адрес элемента данных, к которому обращались последний раз.
    size_t _size; // Количество элементов в таблице
    double loadFactor; // Коэффициент заполнения
    double maxLoadFactor; // Максимальный коэффициент загрузки

    // Вычисляет индекс в таблице на основе хеш-значения ключа. 
    // параметр key - ключ, для которого необходимо вычислить индекс. 
    // return - Индекс в таблице, соответствующий данному ключу.
    size_t defaultHash(const Key& key) const {
        return hashFunction(key) % table.size();
    }

    // Изменяет размер таблицы, увеличивая её емкость в два раза. 
    // Переносит все элементы из текущей таблицы в новую таблицу с увеличенной емкостью. 
    // Это необходимо для оптимизации хранения элементов при превышении максимального коэффициента загрузки. 
    void resize() {
        size_t newCapacity = table.size() * 2;
        vector<list<Key>> newTable(newCapacity);
        // Переносим все элементы в новую таблицу
        for (const auto& bucket : table) {
            for (const auto& key : bucket) {
                size_t newIndex = hashFunction(key) % newCapacity;
                newTable[newIndex].push_back(key);
            }
        }
        table.swap(newTable); // Обновляем таблицу
    }

public:
    // Конструктор HashTable, инициализирует таблицу заданной емкостью и хеш-функцией. 
    // hashFunc - функция, используемая для вычисления хеша ключей.
    // capacity - начальная емкость таблицы (по умолчанию 10).
    // maxLoad - максимальный коэффициент загрузки (по умолчанию 0.7).
    HashTable(function<size_t(const Key&)> hashFunc, size_t capacity = 10, double maxLoad = 0.7)
        : _size(0), maxLoadFactor(maxLoad), hashFunction(hashFunc) { table.resize(capacity); }
    
    // Добавляет новый элемент в таблицу. 
    // key - ключ, который необходимо добавить в таблицу.
    // Если таблица заполнена до максимально допустимого коэффициента загрузки, 
    // происходит изменение размера таблицы. 
    void insert(const Key& key) {
        // Проверяем необходимость увеличения размера таблицы
        if (loadFactor >= maxLoadFactor) { resize(); }
        size_t index = defaultHash(key);
        table[index].push_back(key);
        _size++;
        loadFactor = static_cast<double>(_size) / table.size();
    }

    // Проверяет, существует ли указанный элемент в таблице. 
    // key - ключ, который необходимо проверить на наличие.
    // return - возвращает true, если элемент существует, в противном случае false.
    bool contains(const Key& key) const {
        size_t index = defaultHash(key);
        for (const auto& item : table[index]) {
            if (item == key) {
                return true;
            }
        }
        return false;
    }

    // Удаляет указанный элемент из таблицы. 
    // key - ключ, который необходимо удалить.
    // Если элемент не найден, будет сгенерировано исключение runtime_error. 
    void remove(const Key& key) {
        size_t index = defaultHash(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == key) {
                bucket.erase(it);
                _size--;
                loadFactor = static_cast<double>(_size) / table.size();
                return;
            }
        }
        throw runtime_error("Ключ не найден");
    }

    // Возвращает текущее количество элементов в таблице. 
    size_t size() const { return table.size(); }

    // Возвращает текущий коэффициент заполнения таблицы. 
    double get_loadFactor() const { return loadFactor; }

    // Возвращает максимальный коэффициент загрузки таблицы. 
    double get_maxLoadFactor() const { return maxLoadFactor; }

    // Проверяет равенство двух ключей. 
    // key1 - первый ключ для сравнения.
    // key2 - второй ключ для сравнения.
    // return - возвращает true, если ключи равны, иначе false.
    bool key_equality(const Key& key1, const Key& key2) const {
        return key1 == key2;
    }

    // **********************************************************
    // Итератор, имеющий доступ к данным-членам HashTable
    class Iterator {
    private:
        HashTable& hashTable; // Ссылка на хеш-таблицу, к которой относится итератор 
        size_t bucketIndex; // Индекс текущего table
        typename list<Key>::iterator listIterator; // Итератор по table на связанный список
       
        // Ищет следующий непустой table и обновляет индексы. 
        // Этот метод помогает убедиться, что итератор указывает на действительный элемент, 
        // если текущий table пуст или итератор достиг конца текущего table. 
        void findNext() {
            while (bucketIndex < hashTable.table.size() && (hashTable.table[bucketIndex].empty() || listIterator == hashTable.table[bucketIndex].end())) {
                bucketIndex++;
                if (bucketIndex < hashTable.table.size()) {
                    listIterator = hashTable.table[bucketIndex].begin();
                }
            }
        }

    public:
        // Конструктор итератора, инициализирует итератор для заданной хеш-таблицы и индекса table. 
        // ht - ссылка на хеш-таблицу, которую нужно итератору обходить.
        // index - начальный индекс table, откуда начинается итерация.
        // Конструктор сразу ищет первый элемент, чтобы установить начальное состояние итератора. 
        Iterator(HashTable& ht, size_t index)
            : hashTable(ht), bucketIndex(index), listIterator(ht.table[index].begin()) {
            findNext(); // Ищем первый элемент
        }

        // Доступ к текущему элементу, на который указывает итератор. 
        // return - текущий ключ, на который указывает итератор.
        Key operator*() const { return *listIterator; }

        // Перемещает итератор к следующему элементу. 
        // return - ссылку на текущий итератор после перемещения.
        // Увеличивает итератор на следующую позицию в текущем table и ищет следующий непустой table. 
        Iterator& operator++() {
            ++listIterator; // Переходим к следующему элементу в текущем table
            findNext();     // Находим следующее непустое table
            return *this;
        }

        // Проверяет не равны ли два итератора. 
        // other - итератор для сравнения.
        // return - возвращает true, если итераторы не равны, иначе false.
        bool operator!=(const Iterator& other) const {
            return (bucketIndex != other.bucketIndex || listIterator != other.listIterator);
        }
    };

    // Возвращает итератор на начало хеш-таблицы. 
    Iterator begin() { return Iterator(*this, 0); };

    // Возвращает итератор на конец хеш-таблицы. 
    Iterator end() { return Iterator(*this, table.size() - 1); };
};
