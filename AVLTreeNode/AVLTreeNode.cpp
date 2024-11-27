/// Бурдинская Наталья ВМК-22
/// Date - 11.11.2024
#pragma once
#include "AVLTreeNode.h"
#include "BinarySearchTree.h"

int main() {
    setlocale(LC_ALL, "russian");
    AVLTree<int>::AVLTreeTest();

    AVLTree<int> tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(1);
    tree.insert(2);
    cout << "AVL-дерево:" << endl;
    tree.printTree();
    cout << endl;

    tree.insert(3);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    cout << "AVL-дерево:" << endl;
    tree.printTree();
    cout << endl;

    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    cout << "AVL-дерево:" << endl;
    tree.printTree();
    cout << endl;

    cout << "Поиск ключа 4:" << endl;
    if (tree.find(4)) {
        cout << "Ключ найден " << endl;
    }
    else {
        cout << "Ключ не найден " << endl;
    }
    cout << endl;

    cout << tree.find(4)->balanceFactor << endl;
    cout << tree.find(5)->balanceFactor << endl;
    cout << tree.find(15)->balanceFactor << endl;
    tree.remove(4);
    tree.clear();
    cout << endl;

    cout << "AVL-дерево после удаления ключа 4:" << endl;
    tree.printTree();
    cout << endl;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << *it << " ";
    }
    return 0;
}