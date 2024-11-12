/// ���������� ������� ���-22
/// Date - 03.09.2024
#pragma once
#include "ClassTreeNode.h"
#include "detours.h"

// ����� BinaryTree : ��������� �������� ������ ������.�� �������� ������ ���
// ������� �����, ������ ������(inorder), ������� ������ � ��������� �����.
template<typename T>
class BinaryTree {
private:
    shared_ptr<TreeNode<T>> root; // ������ ������

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

    // *******************************************************
    // removeRecursively: ����������� ������� �������� ����************************************
    shared_ptr<TreeNode<T>> removeRecursively(shared_ptr<TreeNode<T>> node, T val) {
       if (!node) return nullptr;

       if (val < node->value) {
           node->left = removeRecursively(node->left, val);
       }
       else if (val > node->value) {
           node->right = removeRecursively(node->right, val);
       }
       else {
           // ���� ������ - ������ =
           if (!node->left) return move(node->right);
           if (!node->right) return move(node->left);
           // move - �������, ��� ������� - ������ ���� ��������� ����� ���������,
           // �������� ���������� ��������� �������� ���������.
           // Move ��������� ��������� ����������� ������ ������ ��� �����������
           // ��� ���������� ������������������. 
           // ���� � ����� ���������
           node->value = minValueNode(node->right)->value;
           node->right = removeRecursively(move(node->right), node->value);
       }
       return node;
    }

    // *******************************************************
    // removeRecursively: ����������� ������� �������� ����************************************
    shared_ptr<TreeNode<T>> removeRecursively1(shared_ptr<TreeNode<T>> node, T val) {
        if (!node) return nullptr;

        if (val < node->value) {
            node->left = removeRecursively1(node->left, val);
        }
        else if (val > node->value) {
            node->right = removeRecursively1(node->right, val);
        }
        else {
            // ���� ������ - ������ =
            if (!node->left) return move(node->right);
            if (!node->right) return move(node->left);
            // move - �������, ��� ������� - ������ ���� ��������� ����� ���������,
            // �������� ���������� ��������� �������� ���������.
            // Move ��������� ��������� ����������� ������ ������ ��� �����������
            // ��� ���������� ������������������. 
            // ���� � ����� ���������
            node->value = minValueNode(node->left)->value;
            node->left = removeRecursively1(move(node->left), node->value);
        }
        return node;
    }

    // *******************************************************
    // minValueNode: ��������������� ������� ��� ���������� ���� � ����������� ���������.
    shared_ptr<TreeNode<T>> minValueNode(shared_ptr<TreeNode<T>> node) {
        while (node && node->left) {
            node = node->left; // ��������� �����, ����� ����� ������� ��������
        }
        return node;
    }

    // *******************************************************
    // ������� ��������� ���������� �� �������� ���� �� ��������� � �������� ���������
    shared_ptr<TreeNode<T>> findNextGreaterRec(shared_ptr<TreeNode<T>> node, T val) {
        shared_ptr<TreeNode<T>> successor = nullptr;
        while (node) {
            if (val < node->value) {
                successor = node;
                node = node->left; // ��������� �����, ����� ����� ������� ��������
            }
            else {
                node = node->right; // ��������� ������, ����� ����� ������� ��������
            }
        }
        return successor;
    }

    // *********************************************************************
    // ������� ��� ���������� ���������� ����������� �������� ���� (����������� �� Inorder)
    shared_ptr<TreeNode<T>> findInorderSuccessorRec(shared_ptr<TreeNode<T>> node, T target) {
        shared_ptr<TreeNode<T>> successor = nullptr;
        auto currentNode = node;
        while (currentNode) {
            if (target < currentNode->value) {
                successor = currentNode;
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }
        }
        return successor;
    }

    // *********************************************************************
    // �������������� �����: ���������� ���������� ����������� ��������
    // ��������� ���� ��� �������� ������������ ������
    // ����� std::stack<T> ������������ ���� - ��������� ������, ������� ��������
    // �� �������� LIFO (last-in first-out ��� "��������� ����� � ������ �����") 
    // ��� ���������� � ���� ����������� ������� push(), � ������� ���������� ����������� �������.
    // �������� ������ ����� ������� ������� ����� - ��� ����� ����������� ������� top().
    // ��� �������� ��������� ����������� ������� pop(). �������� ������������ � �������, �������� ����������.
    // ���������� ��� ������� � �������� top() ����� ������� ��� �������� �����.
    shared_ptr<TreeNode<T>> findInorderSuccessorIterativeRec(shared_ptr<TreeNode<T>> node, T target) {
        stack<shared_ptr<TreeNode<T>>> nodeStack;
        auto currentNode = node;
        shared_ptr<TreeNode<T>> previous = nullptr;// ����������
        bool found = false;
        while (currentNode || !nodeStack.empty()) {
            while (currentNode) {
                nodeStack.push(currentNode);
                currentNode = currentNode->left;
            }
            currentNode = nodeStack.top();
            nodeStack.pop();
            if (found) {
                return currentNode;
            }
            if (target == currentNode->value) {
                found = true;
            }
            currentNode = currentNode->right;
        }
        return nullptr;
    }
public:
    // ����������� �� ���������
    BinaryTree() : root(nullptr) {}
    // ����������� � ��������� �����
    // value �������� �����
    BinaryTree(T value) {
        root = new TreeNode<T>(value);
    }
    // ����������, 
    // ������������ ��� ������ ��������������� ������� clearLRN ��� clearRLN
    ~BinaryTree() {
        clearLRN(root);
        //clearRLN(root);
    }
    // ����� insert : ���������� ��������� �������� � ������, ����������� �� ���������.
    void insert(T value) {
        insert(root, value);
    }
    // ************************************************************
    // ����� remove : ������� ���� Node �� ��������� val
    void remove(T val) {
        //root = removeRecursively(move(root), val);
        root = removeRecursively(move(root), val);
    }
    // ************************************************************
    // ����� findNextGreater : 
    // ������� ��������� �� �������� ���� �� ��������� � �������� ���������.
    T findNextGreater(T val) {
        shared_ptr<TreeNode<T>> nextGreater = findNextGreaterRec(root, val);
        if (nextGreater) {
            return nextGreater->value;
        }
        else {
            throw runtime_error("��������� ���������� �������� �� �������");
        }
    }
    // ************************************************************
    // ����� findInorderSuccessor : 
    // ������� ��������� �� �������� ���� �� ��������� � �������� ���������.
    T findInorderSuccessor(T val) {
        shared_ptr<TreeNode<T>> nextGreater = findInorderSuccessorRec(root, val);
        if (nextGreater) {
            return nextGreater->value;
        }
        else {
            throw runtime_error("��������� ���������� �������� �� �������");
        }
    }
    // ************************************************************
    // ����� findInorderSuccessorIterative : 
    // ������� ��������� �� �������� ���� �� ��������� � �������� ���������.
    T findInorderSuccessorIterative(T val) {
        shared_ptr<TreeNode<T>> nextGreater = findInorderSuccessorIterativeRec(root, val);
        if (nextGreater) {
            return nextGreater->value;
        }
        else {
            throw runtime_error("��������� ���������� �������� �� �������");
        }
    }
    // ����� display : 
    void display() {
        NLR(root);
        cout << endl;
    }
    // ����� clear : ����������� ������, ������� ������ ������.
    void clear() {
        clearLRN(root);
        // clearRLN(root);
    }
    // ����� print : ��� ����������� ����������� ������ � �������
    void print() {
        printTree(root, 0);
    }
    // ����� getRoot: ���������� ������
    shared_ptr<TreeNode<T>> getRoot() {
        return root;
    }
    // ����� preorder: ���������� ����� ������ ����� ������
    vector<T> preorder() {
        vector<T> result;
        preOrder(root, result);
        return result;
    }
    // ����� inorder: ���������� ����� ������ ����� ������
    vector<T> inorder() {
        vector<T> result;
        inOrder(root, result);
        return result;
    }
    // ����� postorder: ���������� ����� ������ ����� ������
    vector<T> postorder() {
        vector<T> result;
        postOrder(root, result);
        return result;
    }
    // ����� preorder1: ���������� ����� ������ ����� ������
    vector<T> preorder1() {
        vector<T> result;
        preOrder1(root, result);
        return result;
    }
    // ����� inorder1: ���������� ����� ������ ����� ������
    vector<T> inorder1() {
        vector<T> result;
        inOrder1(root, result);
        return result;
    }
    // ����� postorder1: ���������� ����� ������ ����� ������
    vector<T> postorder1() {
        vector<T> result;
        postOrder1(root, result);
        return result;
    }
    // ����� search : ���� ���� � �������� ���������.
    shared_ptr<TreeNode<T>> search(int data) {
        return searchRec(root, data);
    }
    // ����� depth : ���� ���� � �������� ���������.
    shared_ptr<TreeNode<T>> depth() {
        return depth_root(root);
    }
};

// ������� ��� ����������� ������
// ������� copyTree: ���������� ������� ����� ��������� ������.
// ���� ���� ����� nullptr, ���������� nullptr.
// ����� ������� ����� ���� � ���������� �������� ��� ������ � ������� �����.
template <typename T>
shared_ptr<TreeNode<T>> copyTree(shared_ptr<TreeNode<T>> node) {
    if (node == nullptr) {
        return nullptr;
    }
    shared_ptr<TreeNode<T>> newNode = make_shared<TreeNode<T>>(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
};

// printTree: ������� ��� ����������� ����������� ������ � �������
template <typename T>
void printTree(shared_ptr<TreeNode<T>> node, int space) {
    if (node != nullptr) {
        space += 10;
        printTree(node->right, space);
        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << node->value << "\n";
        printTree(node->left, space);
    }
};

// ������� ��� ������ ������ (� preOrder NLR ������)
// preorder (������� ������, ����� ����� ���������, ����� ������ ���������)
template <typename T>
void printTree1(shared_ptr<TreeNode<T>> node) {
    if (node == nullptr) {
        return;
    }
    cout << node->value << " ";
    printTree1(node->left);
    printTree1(node->right);
};

// ������� ������������ ����� ���� � ������������ ���������
template <typename T>
shared_ptr<TreeNode<T>> searchRec(shared_ptr<TreeNode<T>> node, T data) {
    // ���� ���� ������ ��� �������� ���� ����� ��������, ������� ����
    if (node == nullptr || node->value == data) {
        return node;
    }
    // �����, ���������� ����� � ����� ��� ������ ���������
    if (data < node->value) {
        return searchRec(node->left, data); //
    }
    return searchRec(node->right, data); // 
};

// *********************************************************************
// ������� �������� ���� �� ������
// ������ ������ �������� ����: ����� � ������� � ��������� ���������
// ���������� ���� � ���� ��������
template<typename T>
void deleteSubtree(shared_ptr<TreeNode<T>>& node, T val) {
    if (!node) return;
    if (node->value == val) {
        node = nullptr;  // ������� ���� � ���������
        return;
    }
    deleteSubtree(node->left, val);
    deleteSubtree(node->right, val);
};

// *********************************************************************
// ������ ������ �������� ����: ������ ���� ��� ��������
// ���� ���� ����� �����, ��� ���������� ������ ������������� ����.
template<typename T>
void deleteNodeByReplacing(shared_ptr<TreeNode<T>>& node, T val) {
    if (!node) return;
    if (node->left && node->left->value == val) {
        node->left = (node->left->left) ? node->left->left : node->left->right;
        return;
    }
    if (node->right && node->right->value == val) {
        node->right = (node->right->right) ? node->right->right : node->right->left;
        return;
    }
    deleteNodeByReplacing(node->left, val);
    deleteNodeByReplacing(node->right, val);
};