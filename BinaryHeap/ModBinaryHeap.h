#pragma once
#include <iostream>  /// ��������� cin cout
#include <cassert>  /// ��� assert
#include <vector>
#include <stdexcept>
#include <locale>   /// ���������� ������� setlocale ��� ��������� ������� ������
using namespace std;

// ��������� ����� �������� ����. �� ��������� ��������� min-heap.
template <typename T, typename Compare = less<T>>
class BinaryHeap {
private:
    vector<T> data;
    Compare comp;
    // ���������� �������������� �������� ����
    void heapifyUp(int index) {
        while (index > 0 && comp(data[index], data[parent(index)])) {
            swap(data[index], data[parent(index)]);
            index = parent(index);
        }
    }
    // ���������� �������������� �������� ����
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
    // ������ ������������� ��������
    int parent(int index) const {
        return (index - 1) / 2;
    }
    // ������ ������ �������
    int leftChild(int index) const {
        return 2 * index + 1;
    }
    // ������ ������� �������
    int rightChild(int index) const {
        return 2 * index + 2;
    }
public:
    // ������� �������� � ����
    void insert(const T& value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }
    // ��������� ������������ (��� �������������) ��������
    T peek() const {
        if (data.empty()) throw out_of_range("���� �����");
        return data.front();
    }
    // ���������� ������������ (��� �������������) ��������
    T extract() {
        if (data.empty()) throw out_of_range("���� �����");
        T root = data.front();
        data.front() = data.back();
        data.pop_back();
        heapifyDown(0);
        return root;
    }
    // ������ ����
    size_t size() const {
        return data.size();
    }
    // �������� �� �������
    bool empty() const {
        return data.empty();
    }
};

// ������� ������������ � �������������� assert
void testHeap() {
    BinaryHeap<int> minHeap;
    minHeap.insert(10);
    minHeap.insert(4);
    minHeap.insert(15);
    minHeap.insert(1);
    // ����������� ������� �� ������� ������ ���� 1
    assert(minHeap.peek() == 1);
    // ��������� ����������� �������
    assert(minHeap.extract() == 1);
    // ������ ����������� ������� ������ ���� 4
    assert(minHeap.peek() == 4);
    // ��������� ���������� ��������
    assert(minHeap.extract() == 4);
    assert(minHeap.extract() == 10);
    assert(minHeap.extract() == 15);
    // �������� �� �������
    assert(minHeap.empty());

    cout << "��� ����� �������� �������!" << endl;
    cout << "---------------------------------------" << endl;
    cout << endl;
};
