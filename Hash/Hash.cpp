/// Hash.cpp
/// Бурдинская Наталья ВМК-22
/// Date - 04.12.2024
#include "HashTable.h"
#include "HashFunction.h"

int main() {
    setlocale(LC_ALL, "russian");
    TestHashTable();
    // Пример использования хеш-таблицы с DJB2 хеш-функцией
    HashTable<int> hashTable(djb2Hash<int>);

    // Вставляем достаточно элементов, чтобы вызвать resize
    for (int i = 0; i < 10; ++i) {
        hashTable.insert(i);
        cout << "Максимальный коэффициент нагрузки : " << hashTable.get_maxLoadFactor() << ", Коэффициент текущей нагрузки : " << hashTable.get_loadFactor() << endl;
        cout << "Вставленный : " << i << ", Размер : " << hashTable.size() << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
    cout << "Окончательный размер : " << hashTable.size() << endl;
    cout << "-----------------------------------------------------------" << endl;

    // Проверка наличия элементов после вставки
    cout << "Содержит 5 : " << hashTable.contains(5) << endl;
    // Удаление элемента
    hashTable.remove(5);
    cout << "Содержит 5 после удаления : " << hashTable.contains(5) << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
    return 0;
}