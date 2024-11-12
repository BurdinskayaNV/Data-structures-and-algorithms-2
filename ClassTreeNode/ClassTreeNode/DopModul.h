// PREORDER, NLR, NRL, ������ ����� ������
// INORDER,  // LNR, RNL, ������������ ����� ������
// POSTORDER // LRN, RLN, �������� ����� ������
// ������ ������ ��� ��������
#pragma once
#include "ClassBinTreeNode.h"

// ����� std::stack<T> ������������ ���� - ��������� ������, ������� ��������
// �� �������� LIFO (last-in first-out ��� "��������� ����� � ������ �����") 
// ��� ���������� � ���� ����������� ������� push(), � ������� ���������� ����������� �������.
// �������� ������ ����� ������� ������� ����� - ��� ����� ����������� ������� top().
// ��� �������� ��������� ����������� ������� pop(). �������� ������������ � �������, �������� ����������.
// ���������� ��� ������� � �������� top() ����� ������� ��� �������� �����.

// ������ ����� (NLR) ��� ��������.
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

// ������ ����� (NRL) ��� ��������.
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

// ������������ ����� (LNR) ��� ��������.
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

// ������������ ����� (RNL) ��� ��������.
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

// �������� ����� (LRN) ��� ��������.
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

// �������� ����� (RLN) ��� ��������.
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

// ������� ������������ ��� �������� ������������ ���������� �������.
void testTraversals() {
    auto root = make_shared<TreeNode<int>>(1);
    root->left = make_shared<TreeNode<int>>(2);
    root->right = make_shared<TreeNode<int>>(3);
    root->left->left = make_shared<TreeNode<int>>(4);
    root->left->right = make_shared<TreeNode<int>>(5);
    root->right->left = make_shared<TreeNode<int>>(6);
    root->right->right = make_shared<TreeNode<int>>(7);

    //cout << "------------------------------------" << endl;

    // �������� ������� ������ (NLR).
    cout << "������ ����� Preorder (NLR): " << endl;
    preorderTraversal(root);
    cout << endl;

    // �������� ������� ������ (NRL).
    cout << "������ ����� Preorder (NRL): " << endl;
    preorderTraversal1(root);
    cout << endl;

    // �������� ������������� ������ (LNR).
    cout << "������������ ����� Inorder (LNR): " << endl;
    inorderTraversal(root);
    cout << endl;

    // �������� ������������� ������ (RNL).
    cout << "������������ ����� Inorder (RNL): " << endl;
    inorderTraversal1(root);
    cout << endl;

    // �������� ��������� ������ (LRN).
    std::cout << "�������� ����� Postorder (LRN): " << endl;
    postorderTraversal(root);
    cout << endl;

    // �������� ��������� ������ (RLN).
    std::cout << "�������� ����� Postorder (RLN): " << endl;
    postorderTraversal1(root);
    cout << endl;

    // ���������� �������� � �������������� assert
    // ��������������, ��� ������ ���������� ����� � ������ ���� ��������� ���������
    assert(root->value == 1);
    assert(root->left->value == 2);
    assert(root->right->value == 3);
    assert(root->left->left->value == 4);
    assert(root->left->right->value == 5);
    assert(root->right->left->value == 6);
    assert(root->right->right->value == 7);
    
    cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "������������ ������� testTraversals ������ ��� �������� ��������� �������" << endl;
 }; 