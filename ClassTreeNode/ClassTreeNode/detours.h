// PREORDER, NLR, NRL, ������ ����� ������
// INORDER,  // LNR, RNL, ������������ ����� ������
// POSTORDER // LRN, RLN, �������� ����� ������
// ������ ������
#pragma once
#include "ClassBinTreeNode.h"

// NLR ������ : ���������� ����� ������ � ������� �������� �����. 
template <typename T>
void NLR(shared_ptr<TreeNode<T>> node) {
    if (node) {
        cout << node->value << " ";
        NLR(node->left);
        NLR(node->right);
    }
};

// NRL ������ : ���������� ����� ������ � ������� �������� �����. 
template <typename T>
void NRL(shared_ptr<TreeNode<T>> node) {
    if (node) {
        cout << node->value << " ";
        NRL(node->right);
        NRL(node->left);
    }
};

// LNR ������������ : ���������� ����� ������ � ������� �������� �����.
template <typename T>
void LNR(shared_ptr<TreeNode<T>> node) {
    if (node) {
        LNR(node->left);
        cout << node->value << " ";
        LNR(node->right);
    }
};

// RNL ������������: ���������� ����� ������ � ������� �������� �����.
template <typename T>
void RNL(shared_ptr<TreeNode<T>> node) {
    if (node) {
        RNL(node->right);
        cout << node->value << " ";
        RNL(node->left);
    }
};

// LRN �������� : ���������� ����� ������ � ������� �������� �����.
template <typename T>
void LRN(shared_ptr<TreeNode<T>> node) {
    if (node) {
        LRN(node->left);
        LRN(node->right);
        cout << node->value << " ";
    }
};

// RLN �������� : ���������� ����� ������ � ������� �������� �����.
template <typename T>
void RLN(shared_ptr<TreeNode<T>> node) {
    if (node) {
        RLN(node->right);
        RLN(node->left);
        cout << node->value << " ";
    }
};

// ������ ����� ������
// Push_back � ��� ������� � C++ ��� ���������� ��������� � ������.
// ��� ��������� ������� ���� ������� � ��������� ��� � ����� �������.
// ���� � ������� �� ������� �����, �� ������������� ��������� �������,
// ����� �������� ����� �������.
// ������� push_back ������, ���������� � �������� ���������.

// NLR ������ ����� ������
template <typename T>
void preOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        result.push_back(node->value);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }
};

// NRL ������ ����� ������
template <typename T>
void preOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        result.push_back(node->value);
        preOrder1(node->right, result);
        preOrder1(node->left, result);
    }
};

// LNR ������������ ����� ������
template <typename T>
void inOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        inOrder(node->left, result);
        result.push_back(node->value);
        inOrder(node->right, result);
    }
};

// RNL ������������ ����� ������
template <typename T>
void inOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        inOrder1(node->right, result);
        result.push_back(node->value);
        inOrder1(node->left, result);
    }
};

// LRN �������� ����� ������
template <typename T>
void postOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.push_back(node->value);
    }
};

// RLN �������� ����� ������
template <typename T>
void postOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
    if (node) {
        postOrder1(node->right, result);
        postOrder1(node->left, result);
        result.push_back(node->value);
    }
};
