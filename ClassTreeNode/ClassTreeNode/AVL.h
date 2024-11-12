// PREORDER, NLR, NRL, ������ ����� ������
// INORDER,  // LNR, RNL, ������������ ����� ������
// POSTORDER // LRN, RLN, �������� ����� ������
#pragma once
#include "ClassBinTreeNode.h"

//���� ��� ��������� AVL ������, ��������� ��������� �����
// ��� ������������� ���� ��������� ������ ������.
// �������� �������� �������� ���������� ��������� � ���������� ������������
// � ����������� ������ ������.
// ������ ������� ��������� ������ ������ � ��������� ����������� �������� 
// ��� ����������� ������������������.
// 
// AVL-������ � ��� ������ ������ � �����������������, 
// ��� ������� � ������ ����������� ��� ������ ���� �� ��������� ������.

// ���� AVL ������
// ��������� ����� ���� ������ 
template <typename T>
class AVLTreeNode {
public:
    T value;          // ������, ���������� � ����
    AVLTreeNode<T>* left;  // ��������� �� ����� �������� ����
    AVLTreeNode<T>* right; // ��������� �� ������ �������� ����
    // �������������� ���� ������, ��������� �������� "�������������" �����
    int height;         // ������ ���� ��� ������������ AVL-������
    
     // ����������� ��� ������������� ���� � ��������� �������
     AVLTreeNode(T val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// ����� ��� ���������� AVL ������
template <typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root;   // �������� ���� AVL ������

    // ������� ��� ��������� ������ ����
    int getHeight(AVLTreeNode<T>* node) {
        // ���������, ���������� �� ���� node ?
        // ���� ���� ����������, ���������� ��� ������ node->height
        // ���� ���� �� ���������� , ���������� : 0
        return node ? node->height : 0;
    }

    // ������� ��� �������� ������� ����
    // ���������� ������� ����� ������ � ������� �����������
    int getBalance(AVLTreeNode<T>* node) {
        // ���������, ���������� �� ���� node ?
        // ���� ���� ����������, ���������� getHeight(node->left) - getHeight(node->right)
        // ���� ���� �� ���������� , ���������� : 0
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // ������ ������� - �������� ������
    // ������� ��� ���������� ������� �������� ������ ���� y
    // x->left � x->right � ��� ����� � ������ �������� ���� �������� ���� x.
    // getHeight(x->left) � getHeight(x->right) �������� ������� getHeight, 
    // ������� ���������� ������ ������ � ������� �����������.
    // max(getHeight(x->left), getHeight(x->right)) ��������� ������������ ������
    // ����� ����� � ������ ����������.
    // + 1 ����������� ������������ ������ �� �������, �������� ������� ���� x.
    // x->height ������������� ���������, ������� �������� ����� ������� ���� x.
    AVLTreeNode<T>* rightRotate(AVLTreeNode<T>* y) {
        AVLTreeNode<T>* x = y->left;   // x ���������� ����� ������ ���������
        AVLTreeNode<T>* T2 = x->right; // T2 ��������� ������ ��������� x

        // ���������� ��������
        // �������� ����� �������� ���� y � ��������� ��� ��� x,
        // � ������ ��������� x ��� T2
        x->right = y;  // ����� ������ ������� x - y
        y->left = T2;  // ����� ����� ������� y - T2

        // ��������� ������ ����� y � x
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        // ������� ������ �����
        return x;
    }

    // ����� ������� - �������� �����
    // x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 
    // x->left � x->right � ��� ����� � ������ �������� ���� �������� ���� x.
    // y->left � y->right � ��� ����� � ������ �������� ���� �������� ���� y.
    // getHeight(x->left) � getHeight(x->right) �������� ������� getHeight, 
    // ������� ���������� ������ ������ � ������� �����������.
    // max(getHeight(x->left), getHeight(x->right)) ��������� ������������ ������
    // ����� ����� � ������ ����������.
    // + 1 ����������� ������������ ������ �� �������, �������� ������� ���� x.
    // x->height ������������� ���������, ������� �������� ����� ������� ���� x.
    AVLTreeNode<T>* leftRotate(AVLTreeNode<T>* x) {
        // y ������ ����� �������� ����� ��������� ����� ��������
        AVLTreeNode<T>* y = x->right;
        // T2 �������� ���������, ������� ���� ����� ���������� � y
        AVLTreeNode<T>* T2 = y->left;

        // ���������� ��������
        // ���������� ��������: y ���������� ������, � x � ����� �������� y
        y->left = x;
        x->right = T2;

        // ���������� ����� ����� x � y ����� ���������� ��������
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        // ���������� y � �������� ������ ����� ���������
        return y;
    }

    // ������� ����
    // ����������� ���������� ���� � ������ � ������ ������������
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T value) {
        // ���������� ����������� �������� �������, ���� !node
        if (!node) return new AVLTreeNode<T>(value);

        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            return node; // ������������� �������� ���������, ������� ���������� node
        }

        // ���������� ������ �������� ����
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // ��������� ������������ ����
        int balance = getBalance(node);

        // LL - ����� ����� ������
        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        // RR - ������ ������ ������
        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        // LR - ����� ������ ������
        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL - ������ ����� ������
        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // ������� ������������� ���� ���������
    }

    // ����������� ����� ��� ������ ������ NLR (����� � ������ �������)
    void preOrder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            cout << root->value << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    // ����������� ����� ��� ������ ������ NRL (����� � ������ �������)
    void preOrder1(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            cout << root->value << " ";
            preOrder1(root->right);
            preOrder1(root->left);
        }
    }

    // ����������� ����� ��� ������ ������ LNR (����� � ������������ �������)
    void inOrder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->value << " ";
            inOrder(root->right);
        }
    }

    // ����������� ����� ��� ������ ������ RNL (����� � ������������ �������)
    void inOrder1(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            inOrder1(root->right);
            cout << root->value << " ";
            inOrder1(root->left);
        }
    }

    // ����������� ����� ��� ������ ������ LRN (����� � �������� �������)
    void postOrder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->value << " ";
        }
    }

    // ����������� ����� ��� ������ ������ RLN (����� � �������� �������)
    void postOrder1(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            postOrder1(root->right);
            postOrder1(root->left);
            cout << root->value << " ";
        }
    }

    // ����� � �������
    void dfsTraversal(AVLTreeNode<T>* node) {
        if (node) {
            cout << node->value << " ";
            dfsTraversal(node->left);
            dfsTraversal(node->right);
        }
    }

    // ����� ���� � ������
    AVLTreeNode<T>* search(AVLTreeNode<T>* node, int val) {
        if (node == nullptr || node->value == val)
            return node;

        if (val < node->value)
            return search(node->left, val);
        else
            return search(node->right, val);
    }

public:
    // ����������� ��� ������������� ��������� ����
    AVLTree() : root(nullptr) {}

    // �������� �������� � AVL ������
    void insert(T value) {
        root = insert(root, value);
    }

    // ����� ������ NLR
    void preOrder() { preOrder(root); }

    // ����� ������ NRL
    void preOrder1() { preOrder1(root); }

    // ����� ������ LNR
    void inOrder() { inOrder(root); }

    // ����� ������ RNL
    void inOrder1() { inOrder1(root); }

    // ����� ������ LRN
    void postOrder() { postOrder(root); }

    // ����� ������ RLN
    void postOrder1() { postOrder1(root); }

    // ����� � �������
    void dfs() {
        dfsTraversal(root);
        //cout << endl;
    }

    // ����� � ������
    void bfs() {
        if (!root) return;
        queue<AVLTreeNode<T>*> queue;
        queue.push(root);

        while (!queue.empty()) {
            AVLTreeNode<T>* current = queue.front();
            cout << current->value << " ";
            queue.pop();

            if (current->left) queue.push(current->left);
            if (current->right) queue.push(current->right);
        }
        //cout << endl;
    }

    bool search(int val) {
        return search(root, val) != nullptr;
    }
};

void AVLtest() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // �������� ������� ������ ����� ������� ����� assert
    assert(tree.search(10) == true);
    assert(tree.search(20) == true);
    assert(tree.search(30) == true);
    assert(tree.search(40) == true);
    assert(tree.search(50) == true);
    assert(tree.search(25) == true);
    assert(tree.search(60) == false);

    cout << "����� ������ NLR : ";
    //cout << "��������������� ����������: " << endl;
    tree.preOrder(); cout << endl;
    // �������� ���������� � ������� assert
    // ��������� ��������� ����������
    vector<int> pre_order = {30, 20, 10, 25, 40, 50};
    /*
    // ��������� ������� ����������
    int i = 0;
    for (int value : tree)
    {
        assert(*i == pre_order[i]);
        i++;
    }

    int i = 0;
    for (int value : tree)
    {
        assert(abs(tree.getBalance(value)) < 2);
        i++;
    }
  */
    cout << "����� ������ NRL : ";
    tree.preOrder1(); cout << endl;

    cout << "����� ������ LNR : ";
    tree.inOrder(); cout << endl;

    cout << "����� ������ RNL : ";
    tree.inOrder1(); cout << endl;
    
    cout << "����� ������ LRN : ";
    tree.postOrder(); cout << endl;
    
    cout << "����� ������ RLN : ";
    tree.postOrder1(); cout << endl;

    cout << "DFS ����� � ������� : ";
    tree.dfs(); cout << endl;

    cout << "BFS ����� � ������ : ";
    tree.bfs(); cout << endl;

    cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "������������ ������� AVLtest ��������� �������" << endl;
};