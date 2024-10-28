// � ���� ���� ���������� ��������� ����� BinaryHeap, ������� ����� ������������
// ���-���� ��� ����-���� � ����������� �� ��������� �������.
// ������������ ������ ��� �������� ���������.
// ����������� ������ ������� ��������, ���������� �������������� �������� � �����,
// ����������� ���������������� ������ ����.
// ����� ����������� ������� ���������� �����, ������� ����� ��������� ����������
// �� ����������� ��� ��������.
// � main() ��������� ����� ��� �������� ���� � ����������.

#pragma once
#include <iostream>  /// ��������� cin cout
#include <cassert>  /// ��� assert
#include <vector>  /// ��� ������ � ���������
#include <stdexcept>  /// ���������� ��� ����������� ����������
#include <locale>  /// ���������� ������� setlocale ��� ��������� ������� ������
#include <algorithm> /// �������� ����� ������� ��� ���������� ���������������
                     /// �������� ��� ������������ � ��� ������� ��������������������
using namespace std;

// ����(�������� ��� ��������) � ������, ��������������� �������� :
// - ���� ����� ����� 0, 1 � 2 �������� ����(�������� ������);
// - ���� ���� A � �������� B, ����� ���� � ����� ��������� �� ������ ��� B � �������� ����;
// - ��� �����������(complete) ������. ���� � ��� ������ ������ ���������������� ������, �.�. �������� �����������.

// template <typename T, bool MinHeap = true> ��������� �������,
// ��� ��� ������������� �������, ���� ������ ������ ������ ��������, ������ ������ �� ��������� ���� ����� true.

// ��������� ����� ��� ���������� �������� ����
template<typename T, bool MinHeap = true>
class BinaryHeap { // �������� ���� (heap)
private:
    vector<T> heapArray; // ������ ��� �������� ��������� ����. ������ ���� ����� ������� �� � �����, � � �������

    // ��������� �������� ������ � ������� ������� � ��������
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    int parent(int index) const { return (index - 1) / 2; }

    // ��������� ���������� �������������� �������� ���� - ����������� �����
    // �����������, ���� �������� ����������� �������� �����������.
    // ���� ������� ������ ������ ����, ������� ��������� ��� ����� ������, � ������ ������ ������ �� �����.
    // ����� ������� �������� ������� � �����. 
    void heapifyUp(int index) {
        // ��������������, ��� ����� ������� ����� MinHeap � MaxHeap.
        // ������� ���������, ����������� �� ����������� ����� ������� ��������� ���� � ��� ��������� 
        // (� ����������� �� ����, MinHeap ��� ��� MaxHeap). � MinHeap ������ ������� ������ ���� ������ ������ ��������,
        // � � MaxHeap ������ ������� ������ ���� ������ ������ ��������.
        if (MinHeap ? heapArray[index] < heapArray[parent(index)] : heapArray[index] > heapArray[parent(index)]) {
            // std::swap() � ��� ������� � C++, ������� ��������� �����
            // ���������� ���� ���������� ��� �����������.
            // ������� �� ���������� ������, ��� ������ ���������� �������� ���������� a � b.
            swap(heapArray[index], heapArray[parent(index)]);
            heapifyUp(parent(index));
        }
    }

    // ��������� ���������� �������������� �������� ���� - ����������� ����
    // �����������, ���� �������� ����������� �������� �������������.
    // ���� ������� ������ ����� �������, �� ��� ��������� ��� �������� �����. � ������ ������ �� ����.
    // ����� ������� �������� � ���������� �� ����� �������.

    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int smallest = index;

        // ���������� ����������� ��� ������������ ������� � ����������� �� ���� ����
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
            heapifyDown(smallest); // ��������� ���������� �������������� �������� ����
        }
    }

 public:
    // ������� push_back ������������� ��� ���������� �������� � ����� �������,
    // � �� ��� ��� ��������. ��� �������� ���������� �������� �� ������� ������������ ������� pop_back. 
    // ������� �������� � ����
    void insert(const T& value) {
        heapArray.push_back(value);
        heapifyUp(heapArray.size() - 1);
    }

    // ��������� ������������ (��� �������������) ��������
    // ��������� ��������� �������� ��� ��������
    T peek() const { //  ����� ������������� ��������� ������ �� �����, 
        // � ��� ��������� ������ ����� ������������ �������� ��������� ���� ������ � ���������� ���.
        if (heapArray.empty()) throw out_of_range("���� �����");
        return heapArray.front(); // ������� list::front() � C++
        // ������������ ��� ��������� ������ �� ������ ������� ���������� ������.
    }

    // ���������� ������������ (��� �������������) ��������
    T extract() { // ����� std::extract � C++ ��������� ������� ���� �� ����������.
        if (heapArray.empty()) throw out_of_range("���� �����");
        T root = heapArray.front(); // ��������� ������ �� ������ ������� ���������� ������.
        heapArray.front() = heapArray.back(); // ��������� ������ �� ��������� ������� ���������� ������.
        heapArray.pop_back(); // ��� �������� ���������� �������� �� �������
        heapifyDown(0);
        return root;
    }
    // ������ ����
    size_t size() const {
        return heapArray.size(); // size � ������� ���������� �����
    }
    // �������� �� �������
    bool empty() const {
        return heapArray.empty(); // empty � �������� ������ �� �������
    }
};

// ������� ���������� �����
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

// ������� ������������ � �������������� assert
void testHeap() {
    BinaryHeap<int> minHeap; // Min-heap �� ���������
    minHeap.insert(10);
    minHeap.insert(4);
    minHeap.insert(15);
    minHeap.insert(1);
    minHeap.insert(6);
    minHeap.insert(5);

    // ����������� ������� �� ������� ������ ���� 1
    assert(minHeap.peek() == 1);
    // ��������� ����������� �������
    assert(minHeap.extract() == 1);
    // ������ ����������� ������� ������ ���� 4
    assert(minHeap.peek() == 4);
    // ��������� ���������� ��������
    assert(minHeap.extract() == 4);
    assert(minHeap.size() == 4);
    assert(minHeap.extract() == 5);
    assert(minHeap.extract() == 6);
    assert(minHeap.extract() == 10);
    assert(minHeap.extract() == 15);
    // �������� �� �������
    assert(minHeap.empty());
    assert(minHeap.size() == 0);

    cout << "��� ����� testHeap �������� �������!" << endl;
 };

void testHeapSort() {
    vector<int> array1 = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    vector<int> sortedArray1Asc = { 1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9 };
    vector<int> sortedArray1Desc = { 9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1 };

    // ��������� ���������� �� �����������
    heapSort(array1, true);
    assert(array1 == sortedArray1Asc);

    // ��������� ���������� �� ��������
    heapSort(array1, false);
    assert(array1 == sortedArray1Desc);

    // ������������� ����� �������� ����� ��� ������ ����� ������ � ���������
    vector<char> array2 = { 'd', 'a', 'c', 'b' };
    vector<char> sortedArray2Asc = { 'a', 'b', 'c', 'd' };
    vector<char> sortedArray2Desc = { 'd', 'c', 'b', 'a' };

    // ��������� ���������� �� �����������
    heapSort(array2, true);
    assert(array2 == sortedArray2Asc);

    // ��������� ���������� �� ��������
    heapSort(array2, false);
    assert(array2 == sortedArray2Desc);

    cout << "��� ����� testHeapSort �������� �������!" << endl;
};