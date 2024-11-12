// PREORDER, NLR, NRL, ������ ����� ������
// INORDER,  // LNR, RNL, ������������ ����� ������
// POSTORDER // LRN, RLN, �������� ����� ������
#pragma once
#include "ClassBinTreeNode.h"

// ����� ��� ������������� ��������� ������, ��������� ���� � �������
class BinaryTreeVec {
public:
    vector<int> nodes;

    // ������� �������� � �������� ������
    void insert(int value) {
        nodes.push_back(value);
    }
};

// ������� ��� ������ ��������� ��������� ������
void printNodes(int node) {
    cout << node << " ";
};

// algorithms : ��������� 
// for_each, any_of, all_of, none_of, transform � copy_if ��� ������ � ������� ������ ����������.
void algorithms() {
    BinaryTreeVec tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(8);

    // ��������� �������� for_each ��� ������ ���� ����� ������
    cout << "���� � ������ : ";
    for_each(tree.nodes.begin(), tree.nodes.end(), printNodes);
    cout << endl;

    // ���������, ���������� �� � ������ ����, ������� ��� 12, � ������� any_of
    bool anyGreaterThan12 = any_of(tree.nodes.begin(), tree.nodes.end(), [](int node) {
        return node > 12;
        });
    cout << "����, ������ �������� ��������� 12 : " << (anyGreaterThan12 ? "Yes" : "No") << endl;

    // ���������, ��� �� ���� ������ 20, � ������� all_of
    bool allLessThan20 = all_of(tree.nodes.begin(), tree.nodes.end(), [](int node) {
        return node < 20;
        });
    cout << "��� ���� �������� ����� 20 : " << (allLessThan20 ? "Yes" : "No") << endl;

    // ���������, ��� �� � ������ �����, ������ 100, � ������� none_of
    bool noneEqual100 = none_of(tree.nodes.begin(), tree.nodes.end(), [](int node) {
        return node == 100;
        });
    cout << "��� �����, ������ 100 : " << (noneEqual100 ? "Yes" : "No") << endl;

    // �������������� ���� ������, ���������� ������ �� 1
    vector<int> transformedNodes(tree.nodes.size());
    transform(tree.nodes.begin(), tree.nodes.end(), transformedNodes.begin(), [](int node) {
        return node + 1;
        });

    cout << "��������������� ���� (������ �������� �� 1) : ";
    for_each(transformedNodes.begin(), transformedNodes.end(), printNodes);
    cout << endl;

    // �������� ������ ������ ���� � ����� ������ copy_if
    vector<int> evenNodes;
    copy_if(tree.nodes.begin(), tree.nodes.end(), back_inserter(evenNodes), [](int node) {
        return node % 2 == 0;
        });

    cout << "������ ���� : ";
    for_each(evenNodes.begin(), evenNodes.end(), printNodes);
    cout << endl; cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "������������ ������� Algorithms ��������� �������" << endl;
};


// clear : ����������� ������, ������� ������ ������. LRN �������
template <typename T>
void clearLRN(shared_ptr<TreeNode<T>>& node) {
    if (node) {
        clearLRN(node->left);
        clearLRN(node->right);
        node.reset();
    }
};

// clear : ����������� ������, ������� ������ ������. RLN �������
template <typename T>
void clearRLN(shared_ptr<TreeNode<T>>& node) {
    if (node) {
        clearRLN(node->right);
        clearRLN(node->left);
        node.reset();
    }
};

// depth_root : ����������� ������� ������
template <typename T>
int depth_root(shared_ptr<TreeNode<T>>& node) {
    if (node == nullptr) return -1;
    else { return max(depth_root(node->left), depth_root(node->right)) + 1; }
};

// count_nodes: ���������� ���������� �����
template <typename T>
unsigned int count_nodes_root(shared_ptr<TreeNode<T>>& node) {
    if (node == nullptr) return 0;
    else { return 1 + count_nodes_root(node->left) + count_nodes_root(node->right); }
};