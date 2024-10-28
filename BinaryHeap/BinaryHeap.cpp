/// BinaryHeap.cpp
/// Бурдинская Наталья ВМК-22
/// Date - 19.10.2024
/// Шаблонный класс Бинарная куча (min-heap или max-heap).
/// Для хранения данных использован массив. 

#include "ModBinaryHeap.h"

int main() {
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    // Тестовая функция testHeap 
    cout << "---------------------------------------" << endl;
    testHeap();
    // Тестовая функция testHeapSort 
    cout << "---------------------------------------" << endl;
    testHeapSort();
    cout << "---------------------------------------" << endl;
    cout << endl;

    // Пример использования: создание min-heap
    BinaryHeap<int> minHeap; // Min-heap по умолчанию
    minHeap.insert(10);
    minHeap.insert(4);
    minHeap.insert(15);
    minHeap.insert(1);
    minHeap.insert(6);
    minHeap.insert(5);

    cout << "Min-Heap:" << endl;
    while (!minHeap.empty()) {
        cout << minHeap.extract() << " ";
    }
    cout << endl;

    // Пример использования: создание max-heap
    BinaryHeap<int, false> maxHeap;  // Max-heap
    maxHeap.insert(10);
    maxHeap.insert(4);
    maxHeap.insert(15);
    maxHeap.insert(1);
    maxHeap.insert(6);
    maxHeap.insert(5);

    cout << "Max-Heap:" << endl;
    while (!maxHeap.empty()) {
        cout << maxHeap.extract() << " ";
    }
    cout << endl;

    vector<int> array = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    heapSort(array, true);  // Сортировка по возрастанию
    cout << "Отсортированный массив (по возрастанию): ";
    for (int el : array) {
        cout << el << " ";
    }
    cout << endl;

    heapSort(array, false);  // Сортировка по убыванию
    cout << "Отсортированный массив (по убыванию): ";
    for (int el : array) {
        cout << el << " ";
    }
    cout << endl;

    return 0;

}

