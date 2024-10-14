// PREORDER, NLR, NRL, прямой обход дерева
// INORDER,  // LNR, RNL, симметричный обход дерева
// POSTORDER // LRN, RLN, обратный обход дерева
// модуль Обходы
#pragma once
#include "ClassBinTreeNode.h"

// NLR прямой : Производит обход дерева и выводит значения узлов. 
template <typename T>
void NLR(shared_ptr<TreeNode<T>> node) {
    if (node) {
        cout << node->value << " ";
        NLR(node->left);
        NLR(node->right);
    }
};

// NRL прямой : Производит обход дерева и выводит значения узлов. 
template <typename T>
void NRL(shared_ptr<TreeNode<T>> node) {
    if (node) {
        cout << node->value << " ";
        NRL(node->right);
        NRL(node->left);
    }
};

// LNR симметричный : Производит обход дерева и выводит значения узлов.
template <typename T>
void LNR(shared_ptr<TreeNode<T>> node) {
    if (node) {
        LNR(node->left);
        cout << node->value << " ";
        LNR(node->right);
    }
};

// RNL симметричный: Производит обход дерева и выводит значения узлов.
template <typename T>
void RNL(shared_ptr<TreeNode<T>> node) {
    if (node) {
        RNL(node->right);
        cout << node->value << " ";
        RNL(node->left);
    }
};

// LRN обратный : Производит обход дерева и выводит значения узлов.
template <typename T>
void LRN(shared_ptr<TreeNode<T>> node) {
    if (node) {
        LRN(node->left);
        LRN(node->right);
        cout << node->value << " ";
    }
};

// RLN обратный : Производит обход дерева и выводит значения узлов.
template <typename T>
void RLN(shared_ptr<TreeNode<T>> node) {
    if (node) {
        RLN(node->right);
        RLN(node->left);
        cout << node->value << " ";
    }
};

// Обходы через вектры
// Push_back — это функция в C++ для добавления элементов в вектор.
// Она принимает элемент типа вектора и добавляет его в конец вектора.
// Если в векторе не хватает места, он автоматически управляет памятью,
// чтобы добавить новый элемент.
// Функция push_back проста, эффективна и довольно безопасна.

// NLR прямой через вектры
template <typename T>
void preOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        result.push_back(node->value);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }
};

// NRL прямой через вектры
template <typename T>
void preOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        result.push_back(node->value);
        preOrder1(node->right, result);
        preOrder1(node->left, result);
    }
};

// LNR симметричный через вектры
template <typename T>
void inOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        inOrder(node->left, result);
        result.push_back(node->value);
        inOrder(node->right, result);
    }
};

// RNL симметричный через вектры
template <typename T>
void inOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        inOrder1(node->right, result);
        result.push_back(node->value);
        inOrder1(node->left, result);
    }
};

// LRN обратный через вектры
template <typename T>
void postOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.push_back(node->value);
    }
};

// RLN обратный через вектры
template <typename T>
void postOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        postOrder1(node->right, result);
        postOrder1(node->left, result);
        result.push_back(node->value);
    }
};
