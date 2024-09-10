/// ���������� ������� ���-22
/// Date - 03.09.2024
#pragma once
#include <iostream>  /// ��������� cin cout
#include <memory>
#include <vector>
#include <locale>   /// ���������� ������� setlocale ��� ��������� ������� ������
using namespace std;

/// ����� TreeNode : ��������� �����, �������������� ���� ��������� ������.
/// ������ ���� �������� �������� � ��������� �� ������ � ������� ��������.
template<typename T>
class TreeNode {
public:
    T value;

    /// shared_ptr ����� ���������
    /// ��������������, ����� ������ ������ ������ ���� �����������
    /// (������� � ����, ��� ����� �� ���� � �� �� ������� ������ �����
    /// ��������� ��������� ���������� ������ shared_ptr ���� <TreeNode<T>>).
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};

// ����� BinaryTree : ��������� �������� ������.�� �������� ������ ���
// ������� �����, ������ ������(inorder), ������� ������ � ��������� �����.
template<typename T>
class BinaryTree {
private:
    shared_ptr<TreeNode<T>> root;
    void insert(shared_ptr<TreeNode<T>>& node, T value) {
        if (!node) {
            node = make_shared<TreeNode<T>>(value);
            /// make_shared() � ��� �������, ������� ������������ ��� ��������� ������
            /// ��� ��������� ������������� ������� � ����������������� ��������� � 
            /// ������������ ����������, � ������� �� ������ ��������� shared_ptr ����� �����������.
            /// ���� node ������, make_shared �������� ������ ���� <TreeNode<T>> ��� ���� �� ��������� value
            return;
        }
        if (value < node->value) {
            insert(node->left, value);
        }
        else {
            insert(node->right, value);
        }
    }

    // ����� inorderTraversal : ���������� ����� ������ � ������� �������� �����.
    void inorderTraversal(shared_ptr<TreeNode<T>> node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    // ����� clear : ����������� ������, ������� ������ ������.
    void clear(shared_ptr<TreeNode<T>>& node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            node.reset();
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    // ����� insert : ���������� ��������� �������� � ������, ����������� �� ���������.
    void insert(T value) {
        insert(root, value);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }

    // ����� clear : ����������� ������, ������� ������ ������.
    void clear() {
        clear(root);
    }

    shared_ptr<TreeNode<T>> getRoot() {
        return root;
    }
};

/// �������� ������� testBinaryTree : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.

void testBinaryTree() {
    BinaryTree<int> tree;
    // ��������� 5 �����
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    // ������� ������
    cout << "���������� ������ : ";
    tree.display();
    // ����������� ������
    tree.clear();
    cout << "������ �������." << endl;
}