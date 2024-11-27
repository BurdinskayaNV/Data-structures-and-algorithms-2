// PREORDER, NLR, NRL, ������ ����� ������
// INORDER,  // LNR, RNL, ������������ ����� ������
// POSTORDER // LRN, RLN, �������� ����� ������
#pragma once
#include <iostream>  /// ��������� cin cout
#include <memory>    /// ����� ��������� � ������� shared_ptr make_shared
#include <cassert>   /// ��� assert
#include <queue>     /// ����� queue ������������ ������� 
#include <functional>  /// ����� �������� ������� ��� ������ � ��������������� ���������
#include <vector>    /// ������� �������
#include <string>    /// ������ �� ��������
#include <stack>     /// Stack ����� ��� �������� ��������: push, pop, � ����� peek.
#include <locale>    /// ���������� ������� setlocale ��� ��������� ������� ������
#include <algorithm> /// �������� ����� ������� ��� ���������� ���������������
                     /// �������� ��� ������������ � ��� ������� ��������������������
#include <sstream>   /// ��� ����������� ������ �� �������� ����� ��������� ������� 
using namespace std;

// ����� TreeNode ������������ ����� ���� ����������� ������.
// ��������� ����� TreeNode, ������� ��������� ���� ��������� ������
template<typename T>
class TreeNode {
public:
    T n_data;  // ������, ���������� � ����.
    TreeNode<T>* n_left;  // ��������� �� ����� �������� ����.
    TreeNode<T>* n_right; // ��������� �� ������ �������� ����.
    // TreeNode(): ����������� �� ���������, �������������� ������ ���� ���������
    // �� ��������� ��� ���� T � ������������� ��������� �� �������� ���� � nullptr.
    TreeNode() : n_data(T()), n_left(nullptr), n_right(nullptr) {}
    // TreeNode(const T& data): �����������, ���������������� ���� ��������� �������
    // � ����������� ��������� �� �������� ���� � nullptr.
    TreeNode(const T& data) : n_data(data), n_left(nullptr), n_right(nullptr) {}
    // TreeNode(const T& data, TreeNode<T>* prev, TreeNode<T>* next): �����������, �������
    // �������������� ������ � ����� ��������� �� ������ � ������� �������� ���� ����.
    TreeNode(const T& data, TreeNode<T>* prev, TreeNode<T>* next) : n_data(data), n_left(prev), n_right(next) {}
    // ����������: ~TreeNode(): ���� ���� �������� ��������� �� �������� ���� ��� ������ ������������ ������.
    ~TreeNode() {
        // ������� ��������� �� ���������� � ��������� ����
        if (n_left != nullptr) n_left = nullptr;
        if (n_right != nullptr) n_right = nullptr;
    }
    // ����������� ����������� : ������ ����� ������, ������� ������ � �������� ����� ���� ��� ���� �������� �����.
    // ����� �������, ���������� �������� ����������� ������ ����� ������ �������� �����.
    TreeNode(const TreeNode& other) : n_data(other.n_data), n_left(nullptr), n_right(nullptr) {
        // �������� ��������� �� ���������� � ��������� ����
        if (other.n_left != nullptr) {
            n_left = new TreeNode(other.n_left->n_data);
        }
        if (other.n_right != nullptr) {
            n_right = new TreeNode(other.n_right->n_data);
        }
    }
    // ����������� ����������� : ���������� ������ � ��������� �� ������� ���� � �������.
    // �������� ��������� ������� ����.
    TreeNode(TreeNode&& other) : n_data(other.n_data), n_left(other.n_left), n_right(other.n_right) {
        // ���������� ��������� �� ���������� � ��������� ����
        other.n_left = nullptr;
        other.n_right = nullptr;
    }
    // �������� ������������ ������������ : ��������� ����������������,
    // ������� ������������ �������� ���� � �������� ������ � �������� ���� �� ������� ����.
    // ��������� �������� �����������.
    TreeNode& operator=(const TreeNode& other) {
        // ��������� ����������������
        if (this == &other) { return *this; }
        // ������� ������� ��������� �� ���������� � ��������� ����
        delete n_left;
        delete n_right;
        // �������� ������ � ��������� �� ������� ���� - �������� �����������
        n_data = other.n_data;
        if (other.n_left != nullptr) {
            n_left = new TreeNode(other.n_left->n_data);
        }
        if (other.n_right != nullptr) {
            n_right = new TreeNode(other.n_right->n_data);
        }
        return *this;
    }
    // �������� ������������ ������������ : 
    // ���������� ������������� ������������, ������ � ����� ��������� ������������. 
    TreeNode& operator=(TreeNode&& other) {
        // ��������� ����������������
        if (this == &other) { return *this; }
        // ���������� ������ � ��������� �� ������� ����
        n_data = other.n_data;
        n_left = other.n_left;
        n_right = other.n_right;
        // ������� ��������� � ������������ ����
        other.n_left = nullptr;
        other.n_right = nullptr;
        return *this;
    }
};

// ����������� ������� �������� ����� (������������� �����). N | N | N
template<typename T>
// countNodesRecursive : ������� ���������� ������������ ���������� ����� � �������� ������.
// ����� � ��������� ����, ��� ���������� �����, ������ ���������� ����� � ��� ����� ���������
// ���� ���������� ����� � ������ ���������, ���� ���� (��� ����).
size_t countNodesRecursive(const TreeNode<T>* node) {
    if (node == nullptr) return 0; // ���� ���� ������, ���������� 0
    //���������� ���������� ����� ����� � ������ + ��� ����
    return 1 + countNodesRecursive(node->n_left) + countNodesRecursive(node->n_right);
}

// �������� �������� � ���� � ���� ������ ����. N | N | N
template<typename T>
// addNodeBST : ������� ��������� ����� ���� � �������� ������ ������.
// ��� ���������� ��������, ������� ���� ��������, � ������� �������� ����.
// ���� �������� ������, �� ��� ����������� � ����� ���������.
// ���� ��� ��� ���� ����, �� ������� ���������� ���������� ��� ����� ����.
// ���� ���� ���, ��������� ����� ����.
// �� �� ����� �������� � ��� ������� ���������, ���� �������� ������ ��� ����� ������� �������� ����.
static void addNodeBST(TreeNode<T>* node, T value) {
    if (value < node->n_data) { // ���� �������� ������ �������� ����
        if (node->n_left) { // ���� ����� �������� ���� ����������, ��������� ���������� ����
            addNodeBST(node->n_left, value);
        }
        else
        { // ����� ������� ����� ���� �����
            node->n_left = new TreeNode<T>(value);
        }
    }
    else
    { // ���� �������� ������ ��� ����� �������� ����
        if (node->n_right) { // ���� ������ �������� ���� ����������, ��������� ���������� ����
            addNodeBST(node->n_right, value);
        }
        else
        { // ����� ������� ����� ���� ������
            node->n_right = new TreeNode<T>(value);
        }
    }
}

// ����������� ������� ����������� �� ��������� ������ ������ ������ (node)
// � ������ ��������� ������ ������ ������� (root)
template<typename T>
// copyRecursive : ������� ���������� ������� ����� ������� ������.
// ��� �������� ���� �� �����, ������� � �����, � ���������� ��������� �� ������ ������ ������.
TreeNode<T>* copyRecursive(TreeNode<T>* root) {
    if (root == nullptr) return nullptr; // ���� ���� ������, ���������� nullptr
    TreeNode<T>* newNode = new TreeNode<T>(root->n_data); // ������� ����� ����, ������� �������
    // ���������� �������� ����� � ������ ����������
    newNode->n_left = copyRecursive(root->n_left);
    newNode->n_right = copyRecursive(root->n_right);
    return newNode;
}

// ����������� ������� ����������� ������� (���������� �����).
template<typename T>
// getDepthRecursive : ������� ��������� ������� ������, ��������� ���������� �����.
// ������� ������� ������ ����� -1. 
// ������� ������ � ��� 1 ���� ������������ ������� ����� ����� � ������ ������������.
int getDepthRecursive(const TreeNode<T>* node) {
    if (node == nullptr) return -1; // ������ ������ ����� ������� -1
    int leftDepth = getDepthRecursive(node->n_left); // ����������� ����� ��� ������ ���������
    int rightDepth = getDepthRecursive(node->n_right); // ����������� ����� ��� ������� ���������
    // ���������� 1 ���� ������������ ������� ������ � ������� �����������
    return 1 + max(leftDepth, rightDepth); 
}

// ����������� ����� ������.
template<typename T>
// printTreeRecursive : ������� ���������� ������� ������ �� �����.
// ��� ������� �������� ������ ���������, ����� ������� ����
// (� ���������, ���������������� ��� ������ � ������), � ����� ����� ���������. 
void printTreeRecursive(const TreeNode<T>* node, int level) {
    if (node == nullptr) return; // ���� ���� ������, ������ �� ������
    // �������� ������ ��������� � ����������� ������
    printTreeRecursive(node->n_right, level + 1);
    // ������ �������� ����. ����� ��������� ������������ �������
    for (int i = 0; i < level; i++) {
        cout << "    "; 
    }
    cout << node->n_data << endl; // �������� ������ �������� ����
    // �������� ����� ��������� � ����������� ������
    printTreeRecursive(node->n_left, level + 1);
}

// �������� ������.
template<typename T>
// deleteTree : ������� ���������� ������� ��� ���� ������, ���������� ������.
void deleteTree(TreeNode<T>* node) {
    if (node) {
        deleteTree(node->n_left);  // ���������� ������� ����� ���������
        deleteTree(node->n_right); // ���������� ������� ������ ���������
        delete node; // ������� ������� ����
    }
}

// ��������������� ����� ��� ������������ ������ ����. 
template<typename T>
// searchRecursive : ������� ���������� ���� ���� � �������� ���������.
// ��� ���������� �������� � ������� ���� � ���������� ���� � ����� ��� ������ ���������,
// ���� �������� �� ���������. ���� �������� �������, ���������� ��������� �� ��������� ����,
// ����� ���������� nullptr.
TreeNode<T>* searchRecursive(TreeNode<T>* node, const T& value) {
    if (node == nullptr) { return nullptr; } // ���� ���� ����, ���������� nullptr, �������� �� �������.
    if (node->n_data == value) { return node; } // �������� �������, ���������� ����
    else if (value < node->n_data) {
        return searchRecursive(node->n_left, value); // ���� � ����� ���������
    }
    else {
        return searchRecursive(node->n_right, value); // ���� � ������ ���������
    }
}

template<typename T>
// preorder : ��������� ������������� ����� (������������������ "����, �����, ������").
// ���� ���� �� �������, ��������� ��� ������ � ���������
// � ���������� ����������� ��� ������ � ������� ���������.
void preorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    result.push_back(node->n_data);  // ��������� ������ �������� ����
    preorder(node->n_left, result);  // ����������� ����� ��� ������ ���������
    preorder(node->n_right, result); // ����������� ����� ��� ������� ���������
}

template<typename T>
// preorder1 : ��������� ������������� ����� (������������������ "����, ������, �����").
// ���� ���� �� �������, ��������� ��� ������ � ���������
// � ���������� ����������� ��� ������� � ������ ���������.
void preorder1(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    result.push_back(node->n_data);
    preorder1(node->n_right, result);
    preorder1(node->n_left, result);
}

// inorder : ��������� ���������� ����� (������������������ "�����, ����, ������").
// ���� ���� �� �������, ���������� ������������ ����� ���������, 
// ��������� ������� ���� � ���������, ����� ������������ ������ ���������.
template<typename T>
void inorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    inorder(node->n_left, result);
    result.push_back(node->n_data);
    inorder(node->n_right, result);
}

// inorder1 : ��������� ���������� ����� (������������������ "������, ����, �����").
// ���� ���� �� �������, ���������� ������������ ������ ���������, 
// ��������� ������� ���� � ���������, ����� ������������ ����� ���������.
template<typename T>
void inorder1(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    inorder1(node->n_right, result);
    result.push_back(node->n_data);
    inorder1(node->n_left, result);
}

template<typename T>
// postorder : ��������� �������������� ����� (������������������ "�����, ������, ����").
// ���������� �������� �����, ����� ������ ��������� � ��������� ������� ���� � ���������.
void postorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    postorder(node->n_left, result);
    postorder(node->n_right, result);
    result.push_back(node->n_data);
}

template<typename T>
// postorder1 : ��������� �������������� ����� (������������������ "������, �����, ����").
// ���������� �������� ������, ����� ����� ��������� � ��������� ������� ���� � ���������.
void postorder1(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    postorder1(node->n_right, result);
    postorder1(node->n_left, result);
    result.push_back(node->n_data);
}

template<typename T>
// inorderStack : ������� ���������� ���� ��� �������� ����� � ������������������,
// �������� ����������� ������. �������� ���������� ������������ ������ ���������,
// ����� ��������� ������� ���� � ����, ����� ���� ���������� ������������ ����� ���������.
void inorderStack(TreeNode<T>* node, stack<TreeNode<T>*>& stack)
{
    if (node == nullptr) return;
    inorderStack(node->n_right, stack);
    stack.push(node);
    inorderStack(node->n_left, stack);
}

template<typename T>
// applyFunction: ��������� ��������� ������� � ������ ������� ���� � ������� ������� ������ (NLR). 
void applyFunction(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    func(node->n_data);
    applyFunction(node->n_left, func);
    applyFunction(node->n_right, func);
}

template<typename T>
// applyPreorder: ������� applyFunction, ��������� ������� � ������� �������������� ������ (NLR).
void applyPreorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    func(node->n_data);
    applyPreorder(node->n_left, func);
    applyPreorder(node->n_right, func);
}

template<typename T>
// applyInorder: ��������� ������� � ������� ����������� ������ (LNR).
void applyInorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    applyInorder(node->n_left, func);
    func(node->n_data);
    applyInorder(node->n_right, func);
}

template<typename T>
// applyPostorder: ��������� ������� � ������� ��������������� ������ (LRN).
void applyPostorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    applyPostorder(node->n_left, func);
    applyPostorder(node->n_right, func);
    func(node->n_data);
}

template<typename T>
// ����� ���������� ����������� ��������, ���������� ����, ����� �������. 
TreeNode<T>* searchSucc(TreeNode<T>* current, const T& value) {
    TreeNode<T>* prev = nullptr;
    // ������ ���� � �������� ��������� � �������� ���� � ����������
    while (current != nullptr) {
        if (current->n_data == value) {
            break;
        }
        else if (value < current->n_data) {
            prev = current;
            current = current->n_left;
        }
        else {
            prev = current;
            current = current->n_right;
        }
    }
    if (current == nullptr) {
        return nullptr; // �������� �� �������
    }
    // ���� � �������� ���� ���� ������ �������, �� ��������� ���������� �������
    // - ��� ���������� ������� � ������ ���������
    if (current->n_right != nullptr) {
        current = current->n_right;
        while (current->n_left != nullptr) {
            current = current->n_left;
        }
        return current;
    }
    // ����� ���� ��������� ���������� �������, ���������� ����� �� ������
    if (prev)
        return prev;
    else
        return nullptr;
}

// ��������� ������ ������ � ������� �����. LNR
template<typename T>
void inOrderTraversalIterative(TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode<T>*> stack;
    TreeNode<T>* current = root;
    while (!stack.empty() || current != nullptr) {
        // ���� ���� �� ������ ���������, �������� ���� � �����
        while (current != nullptr) {
            stack.push(current);
            current = current->n_left;
        }
        // ����� ������� ���� �� �����, ������� ��� � ��������� � ������� ���������
        current = stack.top();
        stack.pop();
        cout << current->n_data << " ";
        current = current->n_right;
    }
}

// ��������� ������ ������ � ������� �����. NLR
template<typename T>
void preOrderTraversalIterative(TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode<T>*> stack;
    stack.push(root);
    while (!stack.empty()) {
        TreeNode<T>* current = stack.top();
        cout << current->n_data << " ";
        stack.pop();
        if (current->n_right != nullptr) {
            stack.push(current->n_right);
        }
        if (current->n_left != nullptr) {
            stack.push(current->n_left);
        }
    }
}

// ��������� ������ ������ � ������� �����. LRN
template<typename T>
void postOrderTraversalIterative(TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode<T>*> stack;
    TreeNode<T>* current = root;
    TreeNode<T>* lastVisited = nullptr;
    //���� ������� ������� �� ������ � ���� �� ���� -- 
    while (!stack.empty() || current != nullptr) {
        // ������� ����� ���� � ����
        if (current != nullptr) {
            stack.push(current);
            current = current->n_left;
        }
        // ��������� ������� ������ � ����
        else {
            TreeNode<T>* peekNode = stack.top();
            // ������� � ������ ����
            if (peekNode->n_right != nullptr && lastVisited != peekNode->n_right) {
                current = peekNode->n_right;
            }
            else {
                cout << peekNode->n_data << " ";
                lastVisited = peekNode;
                stack.pop();
            }
        }
    }
}

template<typename T>
// �������� ���� ����������. �� �������, ��� ��� ��� ������������.
// ���������� ����� ���� �� ������ 
void deleteNodeRecursive(TreeNode<T>** node, const T& value) {
    if (*node == nullptr) {
        return; // ���� �� ������
    }
    // ���� �������� ������, ��� �������� � ������� ����, ���� �����
    if (value < (*node)->n_data) {
        deleteNodeRecursive(&(*node)->n_left, value);
    }
    // ���� �������� ������, ��� �������� � ������� ����, ���� ������
    else if (value > (*node)->n_data) {
        deleteNodeRecursive(&(*node)->n_right, value);
    }
    // ������ ���� ��� ��������
    else {
        TreeNode<T>* nodeToDelete = *node;
        // ���� � ���� ��� �������� �����, ������ ������� ���
        if ((*node)->n_left == nullptr && (*node)->n_right == nullptr) {
            *node = nullptr;
            delete nodeToDelete;
        }
        // ���� � ���� ���� ������ ����� �������� ����, ������������ ��� � ��������
        else if ((*node)->n_left != nullptr && (*node)->n_right == nullptr) {
            *node = (*node)->n_left;
            nodeToDelete->n_left = nullptr;
            delete nodeToDelete;
        }
        // ���� � ���� ���� ������ ������ �������� ����, ������������ ��� � ��������
        else if ((*node)->n_left == nullptr && (*node)->n_right != nullptr) {
            *node = (*node)->n_right;
            nodeToDelete->n_right = nullptr;
            delete nodeToDelete;
        }
        // ���� � ���� ���� ��� �������� ����, ���� ��������� ���������� ������� � ������ �������
        else {
            TreeNode<T>* nextLargest = searchSucc(*node, (*node)->n_data);
            (*node)->n_data = nextLargest->n_data;
            deleteNodeRecursive(&(*node)->n_right, nextLargest->n_data);
        }
    }
}

template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;
public:
    BinarySearchTree() :root(nullptr) {}
    BinarySearchTree(T value) {
        root = new TreeNode<T>(value);
    }
    BinarySearchTree(TreeNode<T>* n_root) {
        root = n_root;
    }
    ~BinarySearchTree() {
        deleteTree(root);
    }
    
    class Iterator {
    private:
        stack<TreeNode<T>*> nodeStack;
    public:
        Iterator(TreeNode<T>* root) {
            pushLeftBranch(root);
        }
        bool operator!=(const Iterator& other) const {
            return !(hasNext() == false && other.hasNext() == false);
        }
        bool hasNext() const {

            return !nodeStack.empty();
        }
        T& operator*() const {
            return nodeStack.top()->n_data;
        }
        T& data() {
            return nodeStack.top()->n_data;
        }
        Iterator& operator++() {
            return next();
        }
        void reset() {
            while (!nodeStack.empty())
                nodeStack.pop();
            inorderStack(root, nodeStack);
        }
        Iterator& next() {
            TreeNode<T>* currentNode;
            if (!hasNext()) {
                throw out_of_range("No more elements in the iterator");
            }
            currentNode = nodeStack.top();
            nodeStack.pop();
            pushLeftBranch(currentNode->n_right);
            return *this;
        }

    private:
        void pushLeftBranch(TreeNode<T>* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = node->n_left;
            }
        }
    };

    Iterator begin() const {
        return Iterator(root);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    // ���������� ����� �� other
    void copy(BinarySearchTree& other)
    {
        clear();
        root = copyRecursive(other.get_root());
    }

    // ������� �����
    void clear() {
        deleteTree(root);   // ������� ������
        root = nullptr; // �������� ������ ������
    }

    // ��������� ������� � ��������� �����
    void apply(const function<void(T&)>& func) {
        applyFunction(root, func);
    }

    // �������� �������� ������. 
    void insert(const T& value) {
        if (!root) {
            root = new TreeNode<T>(value);
        }
        else
        {
            addNodeBST(root, value);
        }
    }

    // ������� �������� ���� �� �����
    void printNode(TreeNode<T>* node) const {
        if (node) {
            cout << node->n_data << endl;
        }
        else {
            cout << "�����" << endl;
        }
    }

    // �������� ������� �� ������ �������������� ������ (NLR)
    vector<T> toArrayPreOrder() const {
        vector<T> result;
        preorder(root, result);
        return result;
    }

    // �������� ������� �� ������ ����������� ������ (LNR). 
    vector<T> toArrayInOrder() const {
        vector<T> result;
        inorder(root, result);
        return result;
    }

    // �������� ������� �� ������ ��������������� ������ (LRN). 
    vector<T> toArrayPostOrder() const {
        vector<T> result;
        postorder(root, result);
        return result;
    }
    // ������ ������ NLR. 
    void printPreOrder() const {
        vector<T> result = toArrayPreOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // ����� ����������� ����� ������ � ������� LNR.
    void printInOrder() const {
        vector<T> result = toArrayInOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // ����� ����������� ����� ������ � ������� LRN. 
    void printPostOrder() const {
        vector<T> result = toArrayPostOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // ������� ������ ������ � ���� ������. 
    void printTree() const {
        printTreeRecursive(root, 0);
    }

    // ������� ���� �� ������. 
    void remove(T value)
    {
        if (isEmpty())
        {
            throw out_of_range("������ ������");
        }
        deleteNodeRecursive(&root, value);
    }

    // ������� ����������� ������� ������. 
    int getDepth() const {
        return getDepthRecursive(root);
    }

    // ������� �������� ����� �����. 
    size_t countNodes() const {
        return countNodesRecursive(root);
    }

    // �������� �� ������� ������
    bool isEmpty() const {
        if (root != nullptr)
            return false;
        else
            return true;
    }

    // ����� ���������� ����������� ��������, ���������� ��������, ����� ������� ���������� 
    T succesor(const T& value) {
        if (isEmpty())
            throw std::out_of_range("������ ������");
        TreeNode<T>* nextNode = searchSucc(root, value);
        if (nextNode == nullptr) {
            throw std::out_of_range("�������� �� ������� � ������");
        }
        return nextNode->n_data;
    }

    // ����� ��� ������ ���� �� �������� 
    TreeNode<T>* search(const T& value) const {
        return searchRecursive(root, value); // ��������� ����� � ��������� ����
    }

    // �������� ��������� �� ������
    TreeNode<T>* get_root() const {
        return root;
    }

    // ������� ������������
    static void runTests() {
        // ������ ��� �����
        BinarySearchTree<int> copyTree;

        // ���� ��� �������� ������
        BinarySearchTree<int> normalTree;
        normalTree.insert(10);
        normalTree.insert(5);
        normalTree.insert(15);
        normalTree.insert(2);
        normalTree.insert(7);
        normalTree.insert(12);
        normalTree.insert(20);
        BinarySearchTree<int> bst;
        bst.insert(3);
        bst.insert(5);
        bst.insert(2);
        bst.insert(4);
        bst.insert(1);
        //�������� ������ �������� �� ������ � ��������� ��������
        vector<int> inorderbst = bst.toArrayInOrder();
        int i = 0;
        for (int value : bst) {

            assert(value, inorderbst[i]);
            i++;
        }
        //�������� ������ ����������� ����������
        auto it = bst.begin();
        it.next();
        auto it2 = bst.begin();
        assert(it != it2);

        assert(normalTree.countNodes() == 7);
        assert(normalTree.getDepth() == 2);
        assert(normalTree.succesor(5) == 7);
        try {

            int successor = normalTree.succesor(21);
        }
        catch (const out_of_range& e) {
            // �������� ���������� out_of_range
            cerr << "������ �����������" << e.what() << endl;
        }

        //��������� �� �������� ����, ��������� ����� ����� �� ����� ��������� ������� � �����������
        assert(countNodesRecursive(normalTree.search(15)) == 3);
        assert(getDepthRecursive(normalTree.search(15)) == 1);

        copyTree.copy(normalTree);
        assert(copyTree.toArrayInOrder() == normalTree.toArrayInOrder());

        normalTree.remove(10);
        assert(normalTree.get_root()->n_data == 12);
        assert(normalTree.countNodes() == 6);
        assert(normalTree.getDepth() == 2);

        normalTree.clear();
        assert(normalTree.countNodes() == 0);
        assert(normalTree.getDepth() == -1);

        // ���� ��� ������������ ������ (�����)
        BinarySearchTree<int> leftSkewedTree;
        leftSkewedTree.insert(10);
        leftSkewedTree.insert(5);
        leftSkewedTree.insert(2);
        assert(leftSkewedTree.countNodes() == 3);
        assert(leftSkewedTree.getDepth() == 2);
        assert(leftSkewedTree.succesor(5) == 10);
        try {

            int successor = leftSkewedTree.succesor(11);
        }
        catch (const out_of_range& e) {
            // �������� ���������� out_of_range
            cerr << "������ �����������" << e.what() << endl;
        }

        //��������� �� �������� ����, ��������� ����� ����� �� ����� ��������� ������� � �����������
        assert(countNodesRecursive(leftSkewedTree.search(5)) == 2);
        assert(getDepthRecursive(leftSkewedTree.search(5)) == 1);

        copyTree.copy(leftSkewedTree);
        assert(copyTree.toArrayInOrder() == leftSkewedTree.toArrayInOrder());

        leftSkewedTree.remove(10);
        assert(leftSkewedTree.get_root()->n_data == 5);
        assert(leftSkewedTree.countNodes() == 2);
        assert(leftSkewedTree.getDepth() == 1);

        leftSkewedTree.clear();
        assert(leftSkewedTree.countNodes() == 0);
        assert(leftSkewedTree.getDepth() == -1);

        // ���� ��� ������������ ������ (������)
        BinarySearchTree<int> rightSkewedTree;
        rightSkewedTree.insert(10);
        rightSkewedTree.insert(15);
        rightSkewedTree.insert(20);

        assert(rightSkewedTree.countNodes() == 3);
        assert(rightSkewedTree.getDepth() == 2);
        assert(rightSkewedTree.succesor(15) == 20);
        try {

            int successor = rightSkewedTree.succesor(21);
        }
        catch (const out_of_range& e) {
            // �������� ���������� out_of_range
            cerr << "������ �����������" << e.what() << endl;
        }

        //��������� �� �������� ����, ��������� ����� ����� �� ����� ��������� ������� � �����������
        assert(countNodesRecursive(rightSkewedTree.search(15)) == 2);
        assert(getDepthRecursive(rightSkewedTree.search(15)) == 1);

        copyTree.copy(rightSkewedTree);
        assert(copyTree.toArrayInOrder() == rightSkewedTree.toArrayInOrder());

        rightSkewedTree.remove(10);
        assert(rightSkewedTree.get_root()->n_data == 15);
        assert(rightSkewedTree.countNodes() == 2);
        assert(rightSkewedTree.getDepth() == 1);

        rightSkewedTree.clear();
        assert(rightSkewedTree.countNodes() == 0);
        assert(rightSkewedTree.getDepth() == -1);

        // ���� ��� ������� ������
        BinarySearchTree<int> emptyTree;
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);
        try {
            int successor = emptyTree.succesor(1);
        }
        catch (const out_of_range& e) {
            // �������� ���������� out_of_range
            cerr << "������ �����������" << e.what() << endl;
        }

        copyTree.copy(emptyTree);
        assert(copyTree.toArrayInOrder() == emptyTree.toArrayInOrder());

        try {
            emptyTree.remove(10);
        }
        catch (const exception e) {
            // �������� ���������� out_of_range
            cerr << "������ �����������" << e.what() << endl;
        }
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);

        assert(emptyTree.search(5) == nullptr);

        emptyTree.clear();
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);

        // ���� ��� ������ �� ������ ����
        BinarySearchTree<int> singleNodeTree;
        singleNodeTree.insert(10);
        assert(singleNodeTree.countNodes() == 1);
        assert(singleNodeTree.getDepth() == 0);
        try {
            int successor = singleNodeTree.succesor(11);
        }
        catch (const out_of_range& e) {
            // �������� ���������� out_of_range
            cerr << "������ �����������" << e.what() << endl;
        }

        assert(singleNodeTree.search(10) == singleNodeTree.get_root());

        copyTree.copy(singleNodeTree);
        assert(copyTree.toArrayInOrder() == singleNodeTree.toArrayInOrder());

        singleNodeTree.remove(10);
        assert(singleNodeTree.countNodes() == 0);
        assert(singleNodeTree.getDepth() == -1);

        singleNodeTree.clear();
        assert(singleNodeTree.countNodes() == 0);
        assert(singleNodeTree.getDepth() == -1);
        // ���� ��� �������� ������� �� ������ ������
        BinarySearchTree<int> arrayTree;
        arrayTree.insert(10);
        arrayTree.insert(5);
        arrayTree.insert(15);
        arrayTree.insert(2);
        arrayTree.insert(7);
        arrayTree.insert(12);
        arrayTree.insert(20);

        vector<int> inorderArray = arrayTree.toArrayInOrder();
        vector<int> expectedInorderArray = { 2, 5, 7, 10, 12, 15, 20 };
        assert(inorderArray == expectedInorderArray);

        vector<int> preorderArray = arrayTree.toArrayPreOrder();
        vector<int> expectedPreorderArray = { 10, 5, 2, 7, 15, 12, 20 };
        assert(preorderArray == expectedPreorderArray);

        vector<int> postorderArray = arrayTree.toArrayPostOrder();
        vector<int> expectedPostorderArray = { 2, 7, 5, 12, 20, 15, 10 };
        assert(postorderArray == expectedPostorderArray);

        // ���� ��� ���������� ������� � ����� ������
        arrayTree.apply([](int& val) { val *= 2; });

        vector<int> updatedInorderArray = arrayTree.toArrayInOrder();
        vector<int> expectedUpdatedInorderArray = { 4, 10, 14, 20, 24, 30, 40 };
        assert(updatedInorderArray == expectedUpdatedInorderArray);


        // ���� ��� ���������� ������� � ����� ������
        arrayTree.apply([](int& val) { val *= 2; });
        // ���� ��� ������������ ������

        BinarySearchTree<int> degenerateTree;
        degenerateTree.insert(10);
        degenerateTree.insert(9);
        degenerateTree.insert(8);
        degenerateTree.insert(7);

        degenerateTree.apply([](int& val) { val *= 2; });

        vector<int> updatedDegenerateArray = degenerateTree.toArrayInOrder();
        vector<int> expectedUpdatedDegenerateArray = { 14, 16, 18, 20 };
        assert(updatedDegenerateArray == expectedUpdatedDegenerateArray);

        degenerateTree.clear();

        // ���� ��� ������� ������
        emptyTree.apply([](int& val) { val *= 2; });

        vector<int> emptyArray = emptyTree.toArrayInOrder();
        vector<int> expectedEmptyArray = {};
        assert(emptyArray == expectedEmptyArray);

        emptyTree.clear();

        // ���� ��� ������ � ����� �����
        singleNodeTree.insert(10);

        singleNodeTree.apply([](int& val) { val *= 2; });

        vector<int> singleNodeArray = singleNodeTree.toArrayInOrder();
        vector<int> expectedSingleNodeArray = { 20 };
        assert(singleNodeArray == expectedSingleNodeArray);

        singleNodeTree.clear();
        cout << "��� ����� ��������!" << endl;
    }
};


