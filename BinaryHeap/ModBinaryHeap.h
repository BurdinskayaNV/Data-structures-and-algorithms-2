#pragma once
#include <iostream>  /// объявляет cin cout
#include <cassert>  /// для assert
#include <vector>
#include <stdexcept>
#include <locale>   /// определяет функцию setlocale для установки русской локали
using namespace std;

// Шаблонный класс Бинарной кучи. По умолчанию реализует min-heap.
template <typename T, typename Compare = less<T>>
class BinaryHeap {
private:
    vector<T> data;
    Compare comp;
    // Восходящее восстановление свойства кучи
    void heapifyUp(int index) {
        while (index > 0 && comp(data[index], data[parent(index)])) {
            swap(data[index], data[parent(index)]);
            index = parent(index);
        }
    }
    // Нисходящее восстановление свойства кучи
    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int smallest = index;
        if (left < data.size() && comp(data[left], data[smallest])) {
            smallest = left;
        }
        if (right < data.size() && comp(data[right], data[smallest])) {
            smallest = right;
        }
        if (smallest != index) {
            swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }
    // Индекс родительского элемента
    int parent(int index) const {
        return (index - 1) / 2;
    }
    // Индекс левого ребенка
    int leftChild(int index) const {
        return 2 * index + 1;
    }
    // Индекс правого ребенка
    int rightChild(int index) const {
        return 2 * index + 2;
    }
public:
    // Вставка элемента в кучу
    void insert(const T& value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }
    // Получение минимального (или максимального) элемента
    T peek() const {
        if (data.empty()) throw out_of_range("Куча пуста");
        return data.front();
    }
    // Извлечение минимального (или максимального) элемента
    T extract() {
        if (data.empty()) throw out_of_range("Куча пуста");
        T root = data.front();
        data.front() = data.back();
        data.pop_back();
        heapifyDown(0);
        return root;
    }
    // Размер кучи
    size_t size() const {
        return data.size();
    }
    // Проверка на пустоту
    bool empty() const {
        return data.empty();
    }
};

// Функция тестирования с использованием assert
void testHeap() {
    BinaryHeap<int> minHeap;
    minHeap.insert(10);
    minHeap.insert(4);
    minHeap.insert(15);
    minHeap.insert(1);
    // Минимальный элемент на вершине должен быть 1
    assert(minHeap.peek() == 1);
    // Извлекаем минимальный элемент
    assert(minHeap.extract() == 1);
    // Теперь минимальный элемент должен быть 4
    assert(minHeap.peek() == 4);
    // Извлекаем оставшиеся элементы
    assert(minHeap.extract() == 4);
    assert(minHeap.extract() == 10);
    assert(minHeap.extract() == 15);
    // Проверка на пустоту
    assert(minHeap.empty());

    cout << "Все тесты пройдены успешно!" << endl;
    cout << "---------------------------------------" << endl;
    cout << endl;
};
