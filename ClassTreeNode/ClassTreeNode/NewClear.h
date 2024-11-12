// PREORDER, NLR, NRL, прямой обход дерева
// INORDER,  // LNR, RNL, симметричный обход дерева
// POSTORDER // LRN, RLN, обратный обход дерева
#pragma once
#include "ClassBinTreeNode.h"

// Класс для представления бинарного дерева, хранящего узлы в векторе
class BinaryTreeVec {
public:
    vector<int> nodes;

    // Вставка элемента в бинарное дерево
    void insert(int value) {
        nodes.push_back(value);
    }
};

// Функция для вывода элементов бинарного дерева
void printNodes(int node) {
    cout << node << " ";
};

// algorithms : применить 
// for_each, any_of, all_of, none_of, transform и copy_if для работы с данными внутри контейнера.
void algorithms() {
    BinaryTreeVec tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(8);

    // Применяем алгоритм for_each для вывода всех узлов дерева
    cout << "Узлы в дереве : ";
    for_each(tree.nodes.begin(), tree.nodes.end(), printNodes);
    cout << endl;

    // Проверяем, существуют ли в дереве узлы, большие чем 12, с помощью any_of
    bool anyGreaterThan12 = any_of(tree.nodes.begin(), tree.nodes.end(), [](int node) {
        return node > 12;
        });
    cout << "Узел, размер которого превышает 12 : " << (anyGreaterThan12 ? "Yes" : "No") << endl;

    // Проверяем, все ли узлы меньше 20, с помощью all_of
    bool allLessThan20 = all_of(tree.nodes.begin(), tree.nodes.end(), [](int node) {
        return node < 20;
        });
    cout << "Все узлы размером менее 20 : " << (allLessThan20 ? "Yes" : "No") << endl;

    // Проверяем, нет ли в дереве узлов, равных 100, с помощью none_of
    bool noneEqual100 = none_of(tree.nodes.begin(), tree.nodes.end(), [](int node) {
        return node == 100;
        });
    cout << "Нет узлов, равных 100 : " << (noneEqual100 ? "Yes" : "No") << endl;

    // Трансформируем узлы дерева, увеличивая каждый на 1
    vector<int> transformedNodes(tree.nodes.size());
    transform(tree.nodes.begin(), tree.nodes.end(), transformedNodes.begin(), [](int node) {
        return node + 1;
        });

    cout << "Преобразованные узлы (каждый увеличен на 1) : ";
    for_each(transformedNodes.begin(), transformedNodes.end(), printNodes);
    cout << endl;

    // Копируем только четные узлы в новый вектор copy_if
    vector<int> evenNodes;
    copy_if(tree.nodes.begin(), tree.nodes.end(), back_inserter(evenNodes), [](int node) {
        return node % 2 == 0;
        });

    cout << "Четные узлы : ";
    for_each(evenNodes.begin(), evenNodes.end(), printNodes);
    cout << endl; cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "Тестирование функции Algorithms выполнено успешно" << endl;
};


// clear : Освобождает память, занятую узлами дерева. LRN очистка
template <typename T>
void clearLRN(shared_ptr<TreeNode<T>>& node) {
    if (node) {
        clearLRN(node->left);
        clearLRN(node->right);
        node.reset();
    }
};

// clear : Освобождает память, занятую узлами дерева. RLN очистка
template <typename T>
void clearRLN(shared_ptr<TreeNode<T>>& node) {
    if (node) {
        clearRLN(node->right);
        clearRLN(node->left);
        node.reset();
    }
};

// depth_root : Определение глубины дерева
template <typename T>
int depth_root(shared_ptr<TreeNode<T>>& node) {
    if (node == nullptr) return -1;
    else { return max(depth_root(node->left), depth_root(node->right)) + 1; }
};

// count_nodes: Возвращает количество узлов
template <typename T>
unsigned int count_nodes_root(shared_ptr<TreeNode<T>>& node) {
    if (node == nullptr) return 0;
    else { return 1 + count_nodes_root(node->left) + count_nodes_root(node->right); }
};