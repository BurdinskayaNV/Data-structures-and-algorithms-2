// модуль Тестирования
#pragma once
#include "ClassBinTreeNode.h"

/// Тестовая функция testBinaryTree1 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
void testBinaryTree1() {
    // Вставляем 5 узлов
    shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
    shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
    assert(count_nodes_root(a1) == 1);
    shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
    shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
    shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
    assert(count_nodes_root(a4) == 1);

    BinaryTree<int> tree;
    // Вставка узлов в бинарное дерево
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    // Нахождение следующего наибольшего значения
    assert(tree.findNextGreater(5) == 7);  // Следующее наибольшее значение после 5 должно быть 7
    assert(tree.findNextGreater(10) == 15); // Следующее наибольшее значение после 10 должно быть 15
    assert(tree.findNextGreater(7) == 10);  // Следующее наибольшее значение после 7 должно быть 10
    // Тестирование с использованием assert функции remove
    //int searchValue = 2; // Значение, которое мы удаляем
    //shared_ptr<TreeNode<int>> result = tree.remove(searchValue); // Попытка удалить несуществующий узел
    //assert(result != nullptr); // Убедимся, что функция remove корректно отработала

    // Тестирование с использованием assert функции search
    int searchValue1 = 15; // Значение, которое мы ищем
    shared_ptr<TreeNode<int>> result1 = tree.search(searchValue1);
    assert(result1 != nullptr); // Убедимся, что функция search корректно отработала

    // count_nodes_root: Возвращает количество узлов
    //assert(count_nodes_root(a1)) == 2;
    //assert(tree.count_nodes() == 5);
    // depth_root: Определение глубины дерева
    //assert(tree.depth == 1);
    //int searchValue = 40; // Значение, которое мы ищем
    //shared_ptr<TreeNode<int>> result = tree.search(searchValue);

    cout << "Тестирование функции testBinaryTree1 выполнено успешно" << endl;

    /* // count_nodes_root: Возвращает количество узлов
     assert(tree.count_nodes_root) == 2;
     // count_nodes_root: Возвращает количество узлов
     assert(tree.count_nodes_root() == 5);
     // depth_root: Определение глубины дерева
     assert(tree.depth_root() == 2); */

     // Тест для пустого дерева
    BinaryTree<int> nullTree;
    //assert(nullTree.count_nodes_root() == 0);
    //assert(nullTree.depth_root() == -1);

    tree.~BinaryTree();
    //assert(tree.count_nodes_root() == 0);
    //assert(tree.depth_root() == -1);

    // Тест для дерева из одного узла
    BinaryTree<int> vetkaTree;
    vetkaTree.insert(9);
    //assert(vetkaTree.count_nodes() == 1);
    //assert(vetkaTree.depth() == 0);

    vetkaTree.~BinaryTree();
    //assert(vetkaTree.count_nodes_root() == 0);
    //assert(vetkaTree.depth_root() == -1);
};

/// Тестовая функция testBinaryTree2 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
void testBinaryTree2() {
    BinaryTree<int> tree;
    // Вставляем 5 узлов
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(1);
    tree.insert(4);

    cout << "Структура дерева: " << endl;
    tree.print();
    cout << endl;
    cout << "Примеры обходов через vector: " << endl;
    cout << "NLR: ";
    for (const int& value : tree.preorder()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "NRL: ";
    for (const int& value : tree.preorder1()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "LNR: ";
    for (const int& value : tree.inorder()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "RNL: ";
    for (const int& value : tree.inorder1()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "LRN: ";
    for (const int& value : tree.postorder()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "RLN: ";
    for (const int& value : tree.postorder1()) {
        cout << value << " ";
    }
    cout << endl;
    // Копирование дерева
    BinaryTree<int> copiedTree(tree);
    cout << "------------------------------------" << endl;
    cout << "Структура скопированного дерева: " << endl;
    copiedTree.print();
    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "Тестирование функции testBinaryTree2 выполнено успешно" << endl;
};