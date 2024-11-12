// PREORDER, NLR, NRL, прямой обход дерева
// INORDER,  // LNR, RNL, симметричный обход дерева
// POSTORDER // LRN, RLN, обратный обход дерева
// модуль Обходы
#pragma once
#include "ClassBinTreeNode.h"

// **********************************************************************************
// Функция для применения данной функции function<void(int)>& func к каждому узлу дерева прямого обхода NLR 
// Лямбда-выражение может передаваться в качестве значения параметру функции,
// который представляет указатель на функцию function<void(int)>&
// func - параметр функции NLRapplyFunctionToEachNode,
// который представляет указатель на функцию function<void(int)>& (это наша лямбда) 
// ничего не возвращает ()
template <typename T>
void NLRapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // Если узел пустой, выходим
    }
    // Применяем функцию к текущему узлу
    // вызываем лямбда-выражение "auto printNodeValue = [](int value) {}"
    // где root->value - узел нашего дерева
    // а это [](int value) переменная (узел) с которой мы заходим в лямбду
    func(root->value);
    // Рекурсивно применяем функцию к левому и правому поддеревьям
    NLRapplyFunctionToEachNode(root->left, func);
    NLRapplyFunctionToEachNode(root->right, func);
};

// Функция для применения данной функции к каждому узлу дерева прямого обхода NRL
template <typename T>
void NRLapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // Если узел пустой, выходим
    }
    // Применяем функцию к текущему узлу
    func(root->value);
    // Рекурсивно применяем функцию к правому и левому поддеревьям
    NRLapplyFunctionToEachNode(root->right, func);
    NRLapplyFunctionToEachNode(root->left, func);
};

// Функция для применения данной функции к каждому узлу дерева симметричного обхода LNR
template <typename T>
void LNRapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // Если узел пустой, выходим
    }
    // Рекурсивно применяем функцию к левому поддереву
    LNRapplyFunctionToEachNode(root->left, func);
    // Применяем функцию к текущему узлу
    func(root->value);
    // Рекурсивно применяем функцию к правому поддереву
    LNRapplyFunctionToEachNode(root->right, func);
};

// Функция для применения данной функции к каждому узлу дерева симметричного обхода RNL
template <typename T>
void RNLapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // Если узел пустой, выходим
    }
    // Рекурсивно применяем функцию к правому поддереву
    RNLapplyFunctionToEachNode(root->right, func);
    // Применяем функцию к текущему узлу
    func(root->value);
    // Рекурсивно применяем функцию к левому поддереву
    RNLapplyFunctionToEachNode(root->left, func);
};

// Функция для применения данной функции к каждому узлу дерева обратного обхода LRN
template <typename T>
void LRNapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // Если узел пустой, выходим
    }
    // Рекурсивно применяем функцию к левому и правому поддеревьям
    LRNapplyFunctionToEachNode(root->left, func);
    LRNapplyFunctionToEachNode(root->right, func);
    // Применяем функцию к текущему узлу
    func(root->value);
};

// Функция для применения данной функции к каждому узлу дерева обратного обхода RLN
template <typename T>
void RLNapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // Если узел пустой, выходим
    }
    // Рекурсивно применяем функцию к правому и левому поддеревьям
    RLNapplyFunctionToEachNode(root->right, func);
    RLNapplyFunctionToEachNode(root->left, func);
    // Применяем функцию к текущему узлу
    func(root->value);
};
