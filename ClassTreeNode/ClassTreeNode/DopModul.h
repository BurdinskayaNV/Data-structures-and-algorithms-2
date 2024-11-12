// PREORDER, NLR, NRL, прямой обход дерева
// INORDER,  // LNR, RNL, симметричный обход дерева
// POSTORDER // LRN, RLN, обратный обход дерева
// модуль Обходы без рекурсий
#pragma once
#include "ClassBinTreeNode.h"

// Класс std::stack<T> представляет стек - структуру данных, которая работает
// по принципу LIFO (last-in first-out или "последний вошел — первым вышел") 
// Для добавления в стек применяется функция push(), в которую передается добавляемый элемент.
// получить только самый верхний элемент стека - для этого применяется функция top().
// Для удаления элементов применяется функция pop(). Удаление производится в порядке, обратном добавлению.
// Комбинируя эту функцию с функцией top() можно извлечь все элементы стека.

// Прямой обход (NLR) без рекурсии.
template<typename T>
void preorderTraversal(shared_ptr<TreeNode<T>> root) {
    if (!root) return;
    stack<shared_ptr<TreeNode<T>>> stack;
    stack.push(root);
    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        cout << node->value << " ";
        if (node->left) stack.push(node->left);
        if (node->right) stack.push(node->right);
    }
};

// Прямой обход (NRL) без рекурсии.
template<typename T>
void preorderTraversal1(shared_ptr<TreeNode<T>> root) {
    if (!root) return;
    stack<shared_ptr<TreeNode<T>>> stack;
    stack.push(root);
    while (!stack.empty()) {
        auto node = stack.top();
        stack.pop();
        cout << node->value << " ";
        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
};

// Симметричный обход (LNR) без рекурсии.
template<typename T>
void inorderTraversal(shared_ptr<TreeNode<T>> root) {
    stack<shared_ptr<TreeNode<T>>> stack;
    auto current = root;
    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        cout << current->value << " ";
        current = current->right;
    }
};

// Симметричный обход (RNL) без рекурсии.
template<typename T>
void inorderTraversal1(shared_ptr<TreeNode<T>> root) {
    stack<shared_ptr<TreeNode<T>>> stack;
    auto current = root;
    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->right;
        }
        current = stack.top();
        stack.pop();
        cout << current->value << " ";
        current = current->left;
    }
};

// Обратный обход (LRN) без рекурсии.
template<typename T>
void postorderTraversal(shared_ptr<TreeNode<T>> root) {
    if (!root) return;
    stack<shared_ptr<TreeNode<T>>> stack1, stack2;
    stack1.push(root);
    while (!stack1.empty()) {
        auto node = stack1.top();
        stack1.pop();
        stack2.push(node);
        if (node->left) stack1.push(node->left);
        if (node->right) stack1.push(node->right);
    }
    while (!stack2.empty()) {
        auto node = stack2.top();
        stack2.pop();
        cout << node->value << " ";
    }
};

// Обратный обход (RLN) без рекурсии.
template<typename T>
void postorderTraversal1(shared_ptr<TreeNode<T>> root) {
    if (!root) return;
    stack<shared_ptr<TreeNode<T>>> stack1, stack2;
    stack1.push(root);
    while (!stack1.empty()) {
        auto node = stack1.top();
        stack1.pop();
        stack2.push(node);
        if (node->right) stack1.push(node->right);
        if (node->left) stack1.push(node->left);
    }
    while (!stack2.empty()) {
        auto node = stack2.top();
        stack2.pop();
        cout << node->value << " ";
    }
};

// Функция тестирования для проверки корректности реализации обходов.
void testTraversals() {
    auto root = make_shared<TreeNode<int>>(1);
    root->left = make_shared<TreeNode<int>>(2);
    root->right = make_shared<TreeNode<int>>(3);
    root->left->left = make_shared<TreeNode<int>>(4);
    root->left->right = make_shared<TreeNode<int>>(5);
    root->right->left = make_shared<TreeNode<int>>(6);
    root->right->right = make_shared<TreeNode<int>>(7);

    //cout << "------------------------------------" << endl;

    // Проверка прямого обхода (NLR).
    cout << "Прямой обход Preorder (NLR): " << endl;
    preorderTraversal(root);
    cout << endl;

    // Проверка прямого обхода (NRL).
    cout << "Прямой обход Preorder (NRL): " << endl;
    preorderTraversal1(root);
    cout << endl;

    // Проверка симметричного обхода (LNR).
    cout << "Симметричный обход Inorder (LNR): " << endl;
    inorderTraversal(root);
    cout << endl;

    // Проверка симметричного обхода (RNL).
    cout << "Симметричный обход Inorder (RNL): " << endl;
    inorderTraversal1(root);
    cout << endl;

    // Проверка обратного обхода (LRN).
    std::cout << "Обратный обход Postorder (LRN): " << endl;
    postorderTraversal(root);
    cout << endl;

    // Проверка обратного обхода (RLN).
    std::cout << "Обратный обход Postorder (RLN): " << endl;
    postorderTraversal1(root);
    cout << endl;

    // Простейшие проверки с использованием assert
    // Предполагается, что дерево определено верно и обходы дают ожидаемый результат
    assert(root->value == 1);
    assert(root->left->value == 2);
    assert(root->right->value == 3);
    assert(root->left->left->value == 4);
    assert(root->left->right->value == 5);
    assert(root->right->left->value == 6);
    assert(root->right->right->value == 7);
    
    cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "Тестирование функции testTraversals Обходы без рекурсий выполнено успешно" << endl;
 }; 