// В этом коде реализован шаблонный класс BinaryHeap, который может представлять
// мин-кучу или макс-кучу в зависимости от параметра шаблона.
// Используется вектор для хранения элементов.
// Реализованы методы вставки элемента, извлечения экстремального элемента и тесты,
// проверяющие функциональность класса кучи.
// Также реализована функция сортировки кучей, которая может выполнять сортировку
// по возрастанию или убыванию.
// В main() выполнены тесты для проверки кучи и сортировки.

#pragma once
#include <iostream>  /// объявляет cin cout
#include <cassert>  /// для assert
#include <vector>  /// для работы с векторами
#include <stdexcept>  /// определяет ряд стандартных исключений
#include <locale>  /// определяет функцию setlocale для установки русской локали
#include <algorithm> /// содержит набор функций для выполнения алгоритмических
                     /// операций над контейнерами и над другими последовательностями
using namespace std;

// Куча(двоичная или бинарная) – дерево, удовлетворяющее условиям :
// - Узлы могут иметь 0, 1 и 2 дочерних узла(бинарное дерево);
// - Если узел A – родитель B, тогда узел А имеет приоритет не меньше чем B — свойство кучи;
// - Это законченное(complete) дерево. Куча – это всегда хорошо сбалансированное дерево, т.к. является законченным.

// template <typename T, bool MinHeap = true> позволяет указать,
// что при инициализации шаблона, если указан только первый параметр, второй должен по умолчанию быть равен true.

// Шаблонный класс для реализации бинарной кучи
template<typename T, bool MinHeap = true>
class BinaryHeap { // Двоичная куча (heap)
private:
    vector<T> heapArray; // Массив для хранения элементов кучи. Данные кучи можно хранить не в узлах, а в массиве

    // Получение индексов левого и правого потомка и родителя
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    int parent(int index) const { return (index - 1) / 2; }

    // Процедура Восходящее восстановление свойства кучи - просеивание вверх
    // Применяется, если значение измененного элемента уменьшается.
    // Если элемент больше своего отца, условие соблюдено для всего дерева, и больше ничего делать не нужно.
    // Иначе элемент меняется местами с отцом. 
    void heapifyUp(int index) {
        // предполагается, что можно выбрать между MinHeap и MaxHeap.
        // Условие проверяет, соблюдается ли неравенство между текущим элементом кучи и его родителем 
        // (в зависимости от того, MinHeap это или MaxHeap). В MinHeap каждый элемент должен быть меньше своего родителя,
        // а в MaxHeap каждый элемент должен быть больше своего родителя.
        if (MinHeap ? heapArray[index] < heapArray[parent(index)] : heapArray[index] > heapArray[parent(index)]) {
            // std::swap() — это функция в C++, которая выполняет обмен
            // значениями двух переменных или контейнеров.
            // Функция не возвращает ничего, она только обменивает значения переменных a и b.
            swap(heapArray[index], heapArray[parent(index)]);
            heapifyUp(parent(index));
        }
    }

    // Процедура Нисходящее восстановление свойства кучи - просеивание вниз
    // Применяется, если значение измененного элемента увеличивается.
    // Если элемент меньше своих сыновей, то все поддерево уже является кучей. и ничего делать не надо.
    // Иначе элемент меняется с наименьшим из своих сыновей.

    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int smallest = index;

        // Определяем минимальный или максимальный элемент в зависимости от типа кучи
        if (MinHeap) {
            if (left < heapArray.size() && heapArray[left] < heapArray[smallest])
                smallest = left;
            if (right < heapArray.size() && heapArray[right] < heapArray[smallest])
                smallest = right;
        }
        else {
            if (left < heapArray.size() && heapArray[left] > heapArray[smallest])
                smallest = left;
            if (right < heapArray.size() && heapArray[right] > heapArray[smallest])
                smallest = right;
        }

        if (smallest != index) {
            swap(heapArray[index], heapArray[smallest]);
            heapifyDown(smallest); // процелура Нисходящее восстановление свойства кучи
        }
    }

 public:
    // Функция push_back предназначена для добавления элемента в конец вектора,
    // а не для его удаления. Для удаления последнего элемента из вектора используется функция pop_back. 
    // Вставка элемента в кучу
    void insert(const T& value) {
        heapArray.push_back(value);
        heapifyUp(heapArray.size() - 1);
    }

    // Получение минимального (или максимального) элемента
    // Получение корневого элемента без удаления
    T peek() const { //  можно «просмотреть» следующий символ на входе, 
        // и при следующем вызове любой потребляющей операции прочитает этот символ и использует его.
        if (heapArray.empty()) throw out_of_range("Куча пуста");
        return heapArray.front(); // Функция list::front() в C++
        // используется для получения ссылки на первый элемент контейнера списка.
    }

    // Извлечение минимального (или максимального) элемента
    T extract() { // Метод std::extract в C++ позволяет извлечь ноду из контейнера.
        if (heapArray.empty()) throw out_of_range("Куча пуста");
        T root = heapArray.front(); // получение ссылки на первый элемент контейнера списка.
        heapArray.front() = heapArray.back(); // получение ссылки на последний элемент контейнера списка.
        heapArray.pop_back(); // Для удаления последнего элемента из вектора
        heapifyDown(0);
        return root;
    }
    // Размер кучи
    size_t size() const {
        return heapArray.size(); // size – подсчёт количества узлов
    }
    // Проверка на пустоту
    bool empty() const {
        return heapArray.empty(); // empty – проверка дерева на пустоту
    }
};

// Функция сортировки кучей
template<typename T>
void heapSort(vector<T>& array, bool ascending = true) {
    BinaryHeap<T, true> minHeap;
    BinaryHeap<T, false> maxHeap;

    if (ascending) {
        for (const T& el : array) {
            minHeap.insert(el);
        }
        for (size_t i = 0; i < array.size(); ++i) {
            array[i] = minHeap.extract();
        }
    }
    else {
        for (const T& el : array) {
            maxHeap.insert(el);
        }
        for (size_t i = 0; i < array.size(); ++i) {
            array[i] = maxHeap.extract();
        }
    }
};

// Функции тестирования с использованием assert
void testHeap() {
    BinaryHeap<int> minHeap; // Min-heap по умолчанию
    minHeap.insert(10);
    minHeap.insert(4);
    minHeap.insert(15);
    minHeap.insert(1);
    minHeap.insert(6);
    minHeap.insert(5);

    // Минимальный элемент на вершине должен быть 1
    assert(minHeap.peek() == 1);
    // Извлекаем минимальный элемент
    assert(minHeap.extract() == 1);
    // Теперь минимальный элемент должен быть 4
    assert(minHeap.peek() == 4);
    // Извлекаем оставшиеся элементы
    assert(minHeap.extract() == 4);
    assert(minHeap.size() == 4);
    assert(minHeap.extract() == 5);
    assert(minHeap.extract() == 6);
    assert(minHeap.extract() == 10);
    assert(minHeap.extract() == 15);
    // Проверка на пустоту
    assert(minHeap.empty());
    assert(minHeap.size() == 0);

    cout << "Все тесты testHeap пройдены успешно!" << endl;
 };

void testHeapSort() {
    vector<int> array1 = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    vector<int> sortedArray1Asc = { 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 };
    vector<int> sortedArray1Desc = { 9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1 };

    // Проверяем сортировку по возрастанию
    heapSort(array1, true);
    assert(array1 == sortedArray1Asc);

    // Проверяем сортировку по убыванию
    heapSort(array1, false);
    assert(array1 == sortedArray1Desc);

    // Дополнительно можно добавить тесты для других типов данных и сценариев
    vector<char> array2 = { 'd', 'a', 'c', 'b' };
    vector<char> sortedArray2Asc = { 'a', 'b', 'c', 'd' };
    vector<char> sortedArray2Desc = { 'd', 'c', 'b', 'a' };

    // Проверяем сортировку по возрастанию
    heapSort(array2, true);
    assert(array2 == sortedArray2Asc);

    // Проверяем сортировку по убыванию
    heapSort(array2, false);
    assert(array2 == sortedArray2Desc);

    cout << "Все тесты testHeapSort пройдены успешно!" << endl;
};