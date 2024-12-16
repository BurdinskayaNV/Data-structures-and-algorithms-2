/// HashTable.h
/// ���������� ������� ���-22
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

// ��������� ����� ��� �������.
// ���-������� � ��������� ������, ����������� ��������� �������������� �������, 
// � ������, ��� ��������� ������� ���� (����, ��������) � ��������� ��� ��������:
// �������� ���������� ����� ����, �������� �������� ����, �������� ������ ���� �� �����.
// �������� ������� ������������ ���-�������.
template <typename Key>
class HashTable {
private:
    vector<list<Key>> table; // ������, � ������� �������� �����
    // ������� ������������ � ���� �������, ��� ������ ������� ������������ ����� ������� ������
    // ������ ������� ������ ����� ������� �����, ������� ����� ���������� ���-������ (�� ���� ��������� ���������� �����).
    function<size_t(const Key&)> hashFunction; // ���-������� � ����� �������� ������, � �������� ���������� ��������� ���.
    size_t _size; // ���������� ��������� � �������
    double loadFactor; // ����������� ����������
    double maxLoadFactor; // ������������ ����������� ��������

    // ��������� ������ � ������� �� ������ ���-�������� �����. 
    // �������� key - ����, ��� �������� ���������� ��������� ������. 
    // return - ������ � �������, ��������������� ������� �����.
    size_t defaultHash(const Key& key) const {
        return hashFunction(key) % table.size();
    }

    // �������� ������ �������, ���������� � ������� � ��� ����. 
    // ��������� ��� �������� �� ������� ������� � ����� ������� � ����������� ��������. 
    // ��� ���������� ��� ����������� �������� ��������� ��� ���������� ������������� ������������ ��������. 
    void resize() {
        size_t newCapacity = table.size() * 2;
        vector<list<Key>> newTable(newCapacity);
        // ��������� ��� �������� � ����� �������
        for (const auto& bucket : table) {
            for (const auto& key : bucket) {
                size_t newIndex = hashFunction(key) % newCapacity;
                newTable[newIndex].push_back(key);
            }
        }
        table.swap(newTable); // ��������� �������
    }

public:
    // ����������� HashTable, �������������� ������� �������� �������� � ���-��������. 
    // hashFunc - �������, ������������ ��� ���������� ���� ������.
    // capacity - ��������� ������� ������� (�� ��������� 10).
    // maxLoad - ������������ ����������� �������� (�� ��������� 0.7).
    HashTable(function<size_t(const Key&)> hashFunc, size_t capacity = 10, double maxLoad = 0.7)
        : _size(0), maxLoadFactor(maxLoad), hashFunction(hashFunc) { table.resize(capacity); }
    
    // ��������� ����� ������� � �������. 
    // key - ����, ������� ���������� �������� � �������.
    // ���� ������� ��������� �� ����������� ����������� ������������ ��������, 
    // ���������� ��������� ������� �������. 
    void insert(const Key& key) {
        // ��������� ������������� ���������� ������� �������
        if (loadFactor >= maxLoadFactor) { resize(); }
        size_t index = defaultHash(key);
        table[index].push_back(key);
        _size++;
        loadFactor = static_cast<double>(_size) / table.size();
    }

    // ���������, ���������� �� ��������� ������� � �������. 
    // key - ����, ������� ���������� ��������� �� �������.
    // return - ���������� true, ���� ������� ����������, � ��������� ������ false.
    bool contains(const Key& key) const {
        size_t index = defaultHash(key);
        for (const auto& item : table[index]) {
            if (item == key) {
                return true;
            }
        }
        return false;
    }

    // ������� ��������� ������� �� �������. 
    // key - ����, ������� ���������� �������.
    // ���� ������� �� ������, ����� ������������� ���������� runtime_error. 
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
        throw runtime_error("���� �� ������");
    }

    // ���������� ������� ���������� ��������� � �������. 
    size_t size() const { return table.size(); }

    // ���������� ������� ����������� ���������� �������. 
    double get_loadFactor() const { return loadFactor; }

    // ���������� ������������ ����������� �������� �������. 
    double get_maxLoadFactor() const { return maxLoadFactor; }

    // ��������� ��������� ���� ������. 
    // key1 - ������ ���� ��� ���������.
    // key2 - ������ ���� ��� ���������.
    // return - ���������� true, ���� ����� �����, ����� false.
    bool key_equality(const Key& key1, const Key& key2) const {
        return key1 == key2;
    }

    // **********************************************************
    // ��������, ������� ������ � ������-������ HashTable
    class Iterator {
    private:
        HashTable& hashTable; // ������ �� ���-�������, � ������� ��������� �������� 
        size_t bucketIndex; // ������ �������� table
        typename list<Key>::iterator listIterator; // �������� �� table �� ��������� ������
       
        // ���� ��������� �������� table � ��������� �������. 
        // ���� ����� �������� ���������, ��� �������� ��������� �� �������������� �������, 
        // ���� ������� table ���� ��� �������� ������ ����� �������� table. 
        void findNext() {
            while (bucketIndex < hashTable.table.size() && (hashTable.table[bucketIndex].empty() || listIterator == hashTable.table[bucketIndex].end())) {
                bucketIndex++;
                if (bucketIndex < hashTable.table.size()) {
                    listIterator = hashTable.table[bucketIndex].begin();
                }
            }
        }

    public:
        // ����������� ���������, �������������� �������� ��� �������� ���-������� � ������� table. 
        // ht - ������ �� ���-�������, ������� ����� ��������� ��������.
        // index - ��������� ������ table, ������ ���������� ��������.
        // ����������� ����� ���� ������ �������, ����� ���������� ��������� ��������� ���������. 
        Iterator(HashTable& ht, size_t index)
            : hashTable(ht), bucketIndex(index), listIterator(ht.table[index].begin()) {
            findNext(); // ���� ������ �������
        }

        // ������ � �������� ��������, �� ������� ��������� ��������. 
        // return - ������� ����, �� ������� ��������� ��������.
        Key operator*() const { return *listIterator; }

        // ���������� �������� � ���������� ��������. 
        // return - ������ �� ������� �������� ����� �����������.
        // ����������� �������� �� ��������� ������� � ������� table � ���� ��������� �������� table. 
        Iterator& operator++() {
            ++listIterator; // ��������� � ���������� �������� � ������� table
            findNext();     // ������� ��������� �������� table
            return *this;
        }

        // ��������� �� ����� �� ��� ���������. 
        // other - �������� ��� ���������.
        // return - ���������� true, ���� ��������� �� �����, ����� false.
        bool operator!=(const Iterator& other) const {
            return (bucketIndex != other.bucketIndex || listIterator != other.listIterator);
        }
    };

    // ���������� �������� �� ������ ���-�������. 
    Iterator begin() { return Iterator(*this, 0); };

    // ���������� �������� �� ����� ���-�������. 
    Iterator end() { return Iterator(*this, table.size() - 1); };
};
