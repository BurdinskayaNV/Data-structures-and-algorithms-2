/// HashFunction.h
/// Бурдинская Наталья ВМК-22
/// Date - 04.12.2024
#pragma once
#include "HashTable.h"

// DJB2 — простая хеш-функция, разработанная Дэниелом Дж. Бернстайном.  
// Часто используется для строк и обеспечивает хорошее распределение.  
// Не предназначена для криптографических целей. 
// Вероятность равномерного распределения низкая. Эта функция подвержена проблемам с кластеризацией. 
// Key - тип ключа, key - ключ для хеширования.
// return - хеш-значение для данного ключа.
template <typename Key>
size_t djb2Hash(const Key& key) {
    unsigned int hash = 5381; // Начальное значение хеша
    // reinterpret_cast в C++ — это оператор приведения типов, который позволяет выполнять 
    // преобразование указателей и ссылок между несовместимыми типами. 
    // Он используется, когда необходимо интерпретировать данные одного типа 
    // как данные другого типа без проверки на безопасность преобразования.
    const char* str = reinterpret_cast<const char*>(&key); // Приводим ключ к строке
    int c;
    while ((c = *str++)) { // Пока не достигнут конец строки
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash; // Возвращаем окончательный хеш
};

// FNV (англ. Fowler–Noll–Vo) — простая хеш-функция для общего применения,  
// разработанная Гленом Фаулером, Лондоном Керт Нолом и Фогном Во.  
// Не является криптографической функцией. Вероятность равномерного распределения средняя.
// Key - тип ключа, key - ключ для хеширования. 
// return - хеш-значение для данного ключа.
template <typename Key>
size_t fnv1aHash(const Key& key) {
    size_t hash = 2166136261u; // Начальное значение FNV-1a хеша
    auto key_hash = std::hash<Key>{}(key); // Получаем стандартный хеш для ключа
    hash = (hash ^ key_hash) * 16777619u; // Применяем XOR и умножение для обновления хеша
    return hash; // Возвращаем окончательный хеш
};

// MurmurHash — это не криптографическая хеш-функция,  
// которая обеспечивает хорошую производительность и равномерное распределение. 
// Подходит для использования в хеш-таблицах и других структурах данных. 
// Key - тип ключа, key - ключ для хеширования.
// return - хеш-значение для данного ключа.
template <typename Key>
size_t murmurHash(const Key& key) {
    unsigned int seed = 0; // Сид для генерации хеша
    unsigned int hash = seed ^ (sizeof(Key) * 0x5bd1e995); // Начинаем с сидированного значения
    const unsigned char* data = reinterpret_cast<const unsigned char*>(&key);
    size_t len = sizeof(Key);
    for (size_t i = 0; i < len; i++) {
        hash ^= data[i]; // XOR с каждым байтом
        hash *= 0x5bd1e995; // Умножаем на константу
        hash ^= hash >> 15; // Сдвиг и XOR для разброса битов
    }
    return hash; // Возвращаем окончательный хеш
};

// TestHashTable - тестирование assert
static void TestHashTable() {
    // Тестирование с типом int и хеш-функцией DJB2
    HashTable<int> hashTableDJB2(djb2Hash<int>);
    hashTableDJB2.insert(1);
    hashTableDJB2.insert(2);
    hashTableDJB2.insert(3);

    // Проверка наличия элементов
    assert(hashTableDJB2.contains(1)); // 1 должен присутствовать в таблице
    assert(!hashTableDJB2.contains(4)); // 4 не должен присутствовать в таблице

    // Проверка коллизий
    hashTableDJB2.insert(11); // 11 может вызвать коллизию с 1
    assert(hashTableDJB2.contains(11)); // 11 должен присутствовать в таблице

    // Удаление элемента
    hashTableDJB2.remove(2);
    assert(!hashTableDJB2.contains(2)); // 2 не должен присутствовать в таблице после удаления

    // Проверка переполнения
    for (int i = 4; i < 11; ++i) {
        hashTableDJB2.insert(i);
    }

    assert(hashTableDJB2.size() == 20); // Проверка общего количества элементов после вставки

    // Тестирование с типом string и хеш-функцией FNV-1a
    HashTable<string> hashTableFNV(fnv1aHash<string>);
    hashTableFNV.insert("здравствуйте");
    hashTableFNV.insert("привет");
    hashTableFNV.insert("бай-бай");
    hashTableFNV.insert("до свидания");

    assert(hashTableFNV.contains("здравствуйте")); // "здравствуйте" должен присутствовать в таблице
    assert(!hashTableFNV.contains("hello")); // "hello" не должен присутствовать в таблице

    // Удаление элемента
    hashTableFNV.remove("бай-бай");
    assert(!hashTableFNV.contains("бай-бай")); // "бай-бай" не должен присутствовать в таблице после удаления

    // Проверка переполнения
    hashTableFNV.insert("test1");
    hashTableFNV.insert("test2");
    hashTableFNV.insert("test3");
    assert(hashTableFNV.size() == 10); // Проверка общего количества элементов после вставки

    // Тестирование с пользовательским типом (например, Простая структура)
    struct CustomObject {
        int value;
        // Оператор равенства для сравнения
        bool operator==(const CustomObject& other) const {
            return value == other.value;
        }
    };

    HashTable<CustomObject> hashTableCustom(djb2Hash<CustomObject>);
    CustomObject obj1{ 10 }, obj2{ 20 }, obj3{ 30 };

    hashTableCustom.insert(obj1);
    hashTableCustom.insert(obj2);
    hashTableCustom.insert(obj3);

    assert(hashTableCustom.contains(obj1)); // obj1 = 10 должен присутствовать в таблице
    assert(hashTableCustom.contains(obj2)); // obj2 = 20 должен присутствовать в таблице
    assert(!hashTableCustom.contains(CustomObject{ 40 })); // Объект со значением 40 не должен присутствовать

    // Удаление пользовательского объекта
    hashTableCustom.remove(obj2);
    assert(!hashTableCustom.contains(obj2)); // obj2 не должен присутствовать в таблице после удаления

    cout << "----------------------------------------" << endl;
    cout << "Использование Итератора для целых чисел" << endl;
    cout << "----------------------------------------" << endl;
    HashTable<int> hashTableIter(djb2Hash<int>);
    hashTableIter.insert(1);
    hashTableIter.insert(2);
    hashTableIter.insert(3);

    // Тесты итератора
    for (auto it = hashTableIter.begin(); it != hashTableIter.end(); ++it) {
        cout << "Итератор целых чисел " << *it << endl; // Выводит все элементы в хеш-таблице
    }
    cout << "---------------------------------------" << endl;
    cout << "Использование Итератора для строковых" << endl;
    cout << "---------------------------------------" << endl;
    HashTable<string> hashTableIterSt(djb2Hash<string>);
    hashTableIterSt.insert("здравствуйте");
    hashTableIterSt.insert("привет");
    hashTableIterSt.insert("до свидания");
    hashTableIterSt.insert("бай-бай");

    // for (const auto& element : hashTableIterSt) {
    for (auto it = hashTableIterSt.begin(); it != hashTableIterSt.end(); ++it) {
        cout << "Итератор строковых " << *it << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Все тесты завершены успешно." << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
};


