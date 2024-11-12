// PREORDER, NLR, NRL, ������ ����� ������
// INORDER,  // LNR, RNL, ������������ ����� ������
// POSTORDER // LRN, RLN, �������� ����� ������
// ������ ������
#pragma once
#include "ClassBinTreeNode.h"

// **********************************************************************************
// ������� ��� ���������� ������ ������� function<void(int)>& func � ������� ���� ������ ������� ������ NLR 
// ������-��������� ����� ������������ � �������� �������� ��������� �������,
// ������� ������������ ��������� �� ������� function<void(int)>&
// func - �������� ������� NLRapplyFunctionToEachNode,
// ������� ������������ ��������� �� ������� function<void(int)>& (��� ���� ������) 
// ������ �� ���������� ()
template <typename T>
void NLRapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // ���� ���� ������, �������
    }
    // ��������� ������� � �������� ����
    // �������� ������-��������� "auto printNodeValue = [](int value) {}"
    // ��� root->value - ���� ������ ������
    // � ��� [](int value) ���������� (����) � ������� �� ������� � ������
    func(root->value);
    // ���������� ��������� ������� � ������ � ������� �����������
    NLRapplyFunctionToEachNode(root->left, func);
    NLRapplyFunctionToEachNode(root->right, func);
};

// ������� ��� ���������� ������ ������� � ������� ���� ������ ������� ������ NRL
template <typename T>
void NRLapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // ���� ���� ������, �������
    }
    // ��������� ������� � �������� ����
    func(root->value);
    // ���������� ��������� ������� � ������� � ������ �����������
    NRLapplyFunctionToEachNode(root->right, func);
    NRLapplyFunctionToEachNode(root->left, func);
};

// ������� ��� ���������� ������ ������� � ������� ���� ������ ������������� ������ LNR
template <typename T>
void LNRapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // ���� ���� ������, �������
    }
    // ���������� ��������� ������� � ������ ���������
    LNRapplyFunctionToEachNode(root->left, func);
    // ��������� ������� � �������� ����
    func(root->value);
    // ���������� ��������� ������� � ������� ���������
    LNRapplyFunctionToEachNode(root->right, func);
};

// ������� ��� ���������� ������ ������� � ������� ���� ������ ������������� ������ RNL
template <typename T>
void RNLapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // ���� ���� ������, �������
    }
    // ���������� ��������� ������� � ������� ���������
    RNLapplyFunctionToEachNode(root->right, func);
    // ��������� ������� � �������� ����
    func(root->value);
    // ���������� ��������� ������� � ������ ���������
    RNLapplyFunctionToEachNode(root->left, func);
};

// ������� ��� ���������� ������ ������� � ������� ���� ������ ��������� ������ LRN
template <typename T>
void LRNapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // ���� ���� ������, �������
    }
    // ���������� ��������� ������� � ������ � ������� �����������
    LRNapplyFunctionToEachNode(root->left, func);
    LRNapplyFunctionToEachNode(root->right, func);
    // ��������� ������� � �������� ����
    func(root->value);
};

// ������� ��� ���������� ������ ������� � ������� ���� ������ ��������� ������ RLN
template <typename T>
void RLNapplyFunctionToEachNode(shared_ptr<TreeNode<T>> root, const function<void(int)>& func) {
    if (root == nullptr) {
        return; // ���� ���� ������, �������
    }
    // ���������� ��������� ������� � ������� � ������ �����������
    RLNapplyFunctionToEachNode(root->right, func);
    RLNapplyFunctionToEachNode(root->left, func);
    // ��������� ������� � �������� ����
    func(root->value);
};
