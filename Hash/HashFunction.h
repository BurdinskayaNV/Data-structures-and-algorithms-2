/// HashFunction.h
/// ���������� ������� ���-22
/// Date - 04.12.2024
#pragma once
#include "HashTable.h"

// DJB2 � ������� ���-�������, ������������� �������� ��. �����������.  
// ����� ������������ ��� ����� � ������������ ������� �������������.  
// �� ������������� ��� ����������������� �����. 
// ����������� ������������ ������������� ������. ��� ������� ���������� ��������� � ��������������. 
// Key - ��� �����, key - ���� ��� �����������.
// return - ���-�������� ��� ������� �����.
template <typename Key>
size_t djb2Hash(const Key& key) {
    unsigned int hash = 5381; // ��������� �������� ����
    // reinterpret_cast � C++ � ��� �������� ���������� �����, ������� ��������� ��������� 
    // �������������� ���������� � ������ ����� �������������� ������. 
    // �� ������������, ����� ���������� ���������������� ������ ������ ���� 
    // ��� ������ ������� ���� ��� �������� �� ������������ ��������������.
    const char* str = reinterpret_cast<const char*>(&key); // �������� ���� � ������
    int c;
    while ((c = *str++)) { // ���� �� ��������� ����� ������
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash; // ���������� ������������� ���
};

// FNV (����. Fowler�Noll�Vo) � ������� ���-������� ��� ������ ����������,  
// ������������� ������ ��������, �������� ���� ����� � ������ ��.  
// �� �������� ����������������� ��������. ����������� ������������ ������������� �������.
// Key - ��� �����, key - ���� ��� �����������. 
// return - ���-�������� ��� ������� �����.
template <typename Key>
size_t fnv1aHash(const Key& key) {
    size_t hash = 2166136261u; // ��������� �������� FNV-1a ����
    auto key_hash = std::hash<Key>{}(key); // �������� ����������� ��� ��� �����
    hash = (hash ^ key_hash) * 16777619u; // ��������� XOR � ��������� ��� ���������� ����
    return hash; // ���������� ������������� ���
};

// MurmurHash � ��� �� ����������������� ���-�������,  
// ������� ������������ ������� ������������������ � ����������� �������������. 
// �������� ��� ������������� � ���-�������� � ������ ���������� ������. 
// Key - ��� �����, key - ���� ��� �����������.
// return - ���-�������� ��� ������� �����.
template <typename Key>
size_t murmurHash(const Key& key) {
    unsigned int seed = 0; // ��� ��� ��������� ����
    unsigned int hash = seed ^ (sizeof(Key) * 0x5bd1e995); // �������� � ������������� ��������
    const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
    size_t len = sizeof(Key);
    for (size_t i = 0; i < len; i++) {
        hash ^= data[i]; // XOR � ������ ������
        hash *= 0x5bd1e995; // �������� �� ���������
        hash ^= hash >> 15; // ����� � XOR ��� �������� �����
    }
    return hash; // ���������� ������������� ���
};

// TestHashTable - ������������ assert
static void TestHashTable() {
    // ������������ � ����� int � ���-�������� DJB2
    HashTable<int> hashTableDJB2(djb2Hash<int>);
    hashTableDJB2.insert(1);
    hashTableDJB2.insert(2);
    hashTableDJB2.insert(3);

    // �������� ������� ���������
    assert(hashTableDJB2.contains(1)); // 1 ������ �������������� � �������
    assert(!hashTableDJB2.contains(4)); // 4 �� ������ �������������� � �������

    // �������� ��������
    hashTableDJB2.insert(11); // 11 ����� ������� �������� � 1
    assert(hashTableDJB2.contains(11)); // 11 ������ �������������� � �������

    // �������� ��������
    hashTableDJB2.remove(2);
    assert(!hashTableDJB2.contains(2)); // 2 �� ������ �������������� � ������� ����� ��������

    // �������� ������������
    for (int i = 4; i < 11; ++i) {
        hashTableDJB2.insert(i);
    }

    assert(hashTableDJB2.size() == 20); // �������� ������ ���������� ��������� ����� �������

    // ������������ � ����� string � ���-�������� FNV-1a
    HashTable<string> hashTableFNV(fnv1aHash<string>);
    hashTableFNV.insert("������������");
    hashTableFNV.insert("������");
    hashTableFNV.insert("���-���");
    hashTableFNV.insert("�� ��������");

    assert(hashTableFNV.contains("������������")); // "������������" ������ �������������� � �������
    assert(!hashTableFNV.contains("hello")); // "hello" �� ������ �������������� � �������

    // �������� ��������
    hashTableFNV.remove("���-���");
    assert(!hashTableFNV.contains("���-���")); // "���-���" �� ������ �������������� � ������� ����� ��������

    // �������� ������������
    hashTableFNV.insert("test1");
    hashTableFNV.insert("test2");
    hashTableFNV.insert("test3");
    assert(hashTableFNV.size() == 10); // �������� ������ ���������� ��������� ����� �������

    // ������������ � ���������������� ����� (��������, ������� ���������)
    struct CustomObject {
        int value;
        // �������� ��������� ��� ���������
        bool operator==(const CustomObject& other) const {
            return value == other.value;
        }
    };

    HashTable<CustomObject> hashTableCustom(djb2Hash<CustomObject>);
    CustomObject obj1{ 10 }, obj2{ 20 }, obj3{ 30 };

    hashTableCustom.insert(obj1);
    hashTableCustom.insert(obj2);
    hashTableCustom.insert(obj3);

    assert(hashTableCustom.contains(obj1)); // obj1 = 10 ������ �������������� � �������
    assert(hashTableCustom.contains(obj2)); // obj2 = 20 ������ �������������� � �������
    assert(!hashTableCustom.contains(CustomObject{ 40 })); // ������ �� ��������� 40 �� ������ ��������������

    // �������� ����������������� �������
    hashTableCustom.remove(obj2);
    assert(!hashTableCustom.contains(obj2)); // obj2 �� ������ �������������� � ������� ����� ��������

    cout << "----------------------------------------" << endl;
    cout << "������������� ��������� ��� ����� �����" << endl;
    cout << "----------------------------------------" << endl;
    HashTable<int> hashTableIter(djb2Hash<int>);
    hashTableIter.insert(1);
    hashTableIter.insert(2);
    hashTableIter.insert(3);

    // ����� ���������
    for (auto it = hashTableIter.begin(); it != hashTableIter.end(); ++it) {
        cout << "�������� ����� ����� " << *it << endl; // ������� ��� �������� � ���-�������
    }
    cout << "---------------------------------------" << endl;
    cout << "������������� ��������� ��� ���������" << endl;
    cout << "---------------------------------------" << endl;
    HashTable<string> hashTableIterSt(djb2Hash<string>);
    hashTableIterSt.insert("������������");
    hashTableIterSt.insert("������");
    hashTableIterSt.insert("�� ��������");
    hashTableIterSt.insert("���-���");

    // for (const auto& element : hashTableIterSt) {
    for (auto it = hashTableIterSt.begin(); it != hashTableIterSt.end(); ++it) {
        cout << "�������� ��������� " << *it << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "��� ����� ��������� �������." << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
};


