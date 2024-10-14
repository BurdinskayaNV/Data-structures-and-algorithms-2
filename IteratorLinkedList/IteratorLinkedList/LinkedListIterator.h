#pragma once
#include <iostream>  /// ��������� cin cout
#include <cassert>  /// ��� assert
#include <list> /// ��� ������
#include <stack>  /// Stack ����� ��� �������� ��������: push, pop, � ����� peek.
#include <locale>   /// ���������� ������� setlocale ��� ��������� ������� ������
using namespace std;

// Node - ��� ��������� ���������, �������������� ���� ����������� ������.
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    // ����������� ��� ����������
    Node() { prev = nullptr; next = nullptr; }

    // ����������� � ����������, ��� val �������� ����
    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

// ����� LinkedList ����������� ������ � ����������� ������� ����
template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // ����������
    ~LinkedList() {
        clear();
    }

    // ����������� �����������
    LinkedList(const LinkedList& other) {
        copyFrom(other);
    }

    // �������� ������������ ������������
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // ����������� �����������
    LinkedList(LinkedList&& other) noexcept
        : head(other.head), tail(other.tail) {
        other.head = nullptr;
        other.tail = nullptr;
    }

    // �������� ������������ ������������
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

// ��� ��������� �����, �������������� �������� ��� ���������� �������.
class LinkedListIterator {
public:
    LinkedListIterator(Node<T>* node) : current(node) {}

    // ���������� ��������� ������������� - ������ � ������
    T& operator*() {
        return current->data;
    }
    // ���������� ��������� ���������� (����������) ��������� �� ���������� �������� (next)
    LinkedListIterator& operator++() {
        current = current->next;
        return *this;
    }
    // ���������� ��������� ���������� (����������) ��������� �� ����������� �������� (prev)
    LinkedListIterator& operator--() {
        current = current->prev;
        return *this;
    }
    // ���������� ��������� ��������� �� ���������
    bool operator==(const LinkedListIterator& other) const {
        return current == other.current;
    }
    // ���������� ��������� ��������� �� ����������� - ��� �������� ����, �� ������� �� ��������� ����
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
// ����� clear ������� ��� �������� � ������
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

// �������� ������� test1 
void test1() {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // ������������ ���������
    auto it = list.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);

    // ������������ �����������
    LinkedList<int> listCopy = list;
    auto itCopy = listCopy.begin();
    assert(*itCopy == 1);
    ++itCopy;
    assert(*itCopy == 2);
    ++itCopy;
    assert(*itCopy == 3);

    // ������������ �����������
    LinkedList<int> listMove = std::move(listCopy);
    auto itMove = listMove.begin();
    assert(*itMove == 1);
    ++itMove;
    assert(*itMove == 2);
    ++itMove;
    assert(*itMove == 3);

    cout << "������������ test1 ��������� ������� !" << endl;
};
