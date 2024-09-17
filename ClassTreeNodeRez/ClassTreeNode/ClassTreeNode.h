/// Бурдинская Наталья ВМК-22
/// Date - 03.09.2024
#pragma once
#include <iostream>  /// объявляет cin cout
#include <memory>
#include <queue>
#include <cassert>
#include <functional>
#include <vector>
#include <stack>
#include <locale>   /// определяет функцию setlocale для установки русской локали
using namespace std;

/// Класс TreeNode : Шаблонный класс, представляющий узел бинарного дерева.
/// Каждый узел содержит значение и указатели на левого и правого потомков.
template<typename T>
class TreeNode {
public:
    T value;

    /// shared_ptr умные указатели
    /// использоваться, когда ресурс памяти должен быть разделяемым
    /// (имеется в виду, что когда на одну и ту же область памяти может
    /// указывать несколько указателей именно shared_ptr типа <TreeNode<T>>).
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;

    /// Конструктор без параметров
    TreeNode() { left = nullptr; right = nullptr; }

    /// Конструктор с параметром, где val значение узла
    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};
