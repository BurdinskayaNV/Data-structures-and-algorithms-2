/// Бурдинская Наталья ВМК-22
/// Date - 03.09.2024
#pragma once
#include <iostream>  /// объявляет cin cout
#include <memory>
#include <vector>
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
    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};

// Класс BinaryTree : Реализует бинарное дерево.Он содержит методы для
// вставки узлов, обхода дерева(inorder), очистки дерева и получения корня.
template<typename T>
class BinaryTree {
private:
    shared_ptr<TreeNode<T>> root;
    void insert(shared_ptr<TreeNode<T>>& node, T value) {
        if (!node) {
            node = make_shared<TreeNode<T>>(value);
            /// make_shared() — это функция, имеющая преимущество при выделении памяти
            /// для совместно используемого объекта и интеллектуального указателя с 
            /// единственным выделением, в отличие от явного получения shared_ptr через конструктор.
            /// если node пустой, make_shared выделяет память типа <TreeNode<T>> для узла со значением value
            return;
        }
        if (value < node->value) {
            insert(node->left, value);
        }
        else {
            insert(node->right, value);
        }
    }

    // Метод inorderTraversal : Производит обход дерева и выводит значения узлов.
    void inorderTraversal(shared_ptr<TreeNode<T>> node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    // Метод clear : Освобождает память, занятую узлами дерева.
    void clear(shared_ptr<TreeNode<T>>& node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            node.reset();
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    // Метод insert : Рекурсивно вставляет значения в дерево, основываясь на сравнении.
    void insert(T value) {
        insert(root, value);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }

    // Метод clear : Освобождает память, занятую узлами дерева.
    void clear() {
        clear(root);
    }

    shared_ptr<TreeNode<T>> getRoot() {
        return root;
    }
};

/// Тестовая функция testBinaryTree : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.

void testBinaryTree() {
    BinaryTree<int> tree;
    // Вставляем 5 узлов
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    // Выводим дерево
    cout << "Содержимое дерева : ";
    tree.display();
    // Освобождаем память
    tree.clear();
    cout << "Дерево очищено." << endl;
}