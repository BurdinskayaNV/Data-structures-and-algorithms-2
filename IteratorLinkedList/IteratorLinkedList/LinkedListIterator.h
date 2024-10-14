#pragma once
#include <iostream>  /// объявляет cin cout
#include <cassert>  /// для assert
#include <list> /// для списка
#include <stack>  /// Stack имеет три основные операции: push, pop, а также peek.
#include <locale>   /// определяет функцию setlocale для установки русской локали
using namespace std;

// Node - это шаблонная структура, представляющая узел двусвязного списка.
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    // Конструктор без параметров
    Node() { prev = nullptr; next = nullptr; }

    // Конструктор с параметром, где val значение узла
    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

// Класс LinkedList двусвязного списка с применением правила пяти
template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Деструктор
    ~LinkedList() {
        clear();
    }

    // Конструктор копирования
    LinkedList(const LinkedList& other) {
        copyFrom(other);
    }

    // Оператор присваивания копированием
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Конструктор перемещения
    LinkedList(LinkedList&& other) noexcept
        : head(other.head), tail(other.tail) {
        other.head = nullptr;
        other.tail = nullptr;
    }

    // Оператор присваивания перемещением
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            other.head = nullptr;
            other.tail = nullptr;
        }
        return *this;
    }

// это вложенный класс, представляющий итератор над двусвязным списком.
class LinkedListIterator {
public:
    LinkedListIterator(Node<T>* node) : current(node) {}

    // Перегрузка оператора разыменования - доступ к данным
    T& operator*() {
        return current->data;
    }
    // Перегрузка оператора инкремента (префиксный) итератора до следующего элемента (next)
    LinkedListIterator& operator++() {
        current = current->next;
        return *this;
    }
    // Перегрузка оператора инкремента (префиксный) итератора до предыдущего элемента (prev)
    LinkedListIterator& operator--() {
        current = current->prev;
        return *this;
    }
    // Перегрузка оператора сравнения на равенство
    bool operator==(const LinkedListIterator& other) const {
        return current == other.current;
    }
    // Перегрузка оператора сравнения на неравенство - для проверки того, не следует ли завершить цикл
    bool operator!=(const LinkedListIterator& other) const {
        return current != other.current;
    }
private:
    Node<T>* current;
};
   
LinkedListIterator begin() {
    return LinkedListIterator(head);
}
LinkedListIterator end() {
    return LinkedListIterator(nullptr);
}

void push_back(T value) {
   Node<T>* newNode = new Node<T>(value);
   if (!tail) {
      head = tail = newNode;
   }
   else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
   }
}
// Метод clear удаляет все элементы в списке
void clear() {
   Node<T>* current = head;
   while (current) {
      Node<T>* next = current->next;
      delete current;
      current = next;
   }
   head = tail = nullptr;
}

private:
   void copyFrom(const LinkedList& other) {
      Node<T>* current = other.head;
      while (current) {
         push_back(current->data);
         current = current->next;
      }
   }
Node<T>* head;
Node<T>* tail;
};

// Тестовая функция test1 
void test1() {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Тестирование итератора
    auto it = list.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);

    // Тестирование копирования
    LinkedList<int> listCopy = list;
    auto itCopy = listCopy.begin();
    assert(*itCopy == 1);
    ++itCopy;
    assert(*itCopy == 2);
    ++itCopy;
    assert(*itCopy == 3);

    // Тестирование перемещения
    LinkedList<int> listMove = std::move(listCopy);
    auto itMove = listMove.begin();
    assert(*itMove == 1);
    ++itMove;
    assert(*itMove == 2);
    ++itMove;
    assert(*itMove == 3);

    cout << "Тестирование test1 выполнено успешно !" << endl;
};
