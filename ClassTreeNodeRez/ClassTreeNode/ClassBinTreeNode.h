/// ���������� ������� ���-22
/// Date - 03.09.2024
#pragma once
#include "ClassTreeNode.h"

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
	
	// ��������� ����� ������, ����� � ���������� ��������� ����� � ������ ��� �������������� ������.
    void copyHelper(shared_ptr<TreeNode<T>>& thisNode, shared_ptr<TreeNode<T>>& otherNode) {
        if (otherNode) {
            thisNode = std::make_shared<TreeNode<T>>(otherNode->data);
            copyHelper(thisNode->left, otherNode->left);
            copyHelper(thisNode->right, otherNode->right);
        }
    }

public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(T value) {
        root = new TreeNode<T>(value);
    }
    ~BinaryTree() {
        clearLRN(root);
    }

    // ����� insert : ���������� ��������� �������� � ������, ����������� �� ���������.
    void insert(T value) {
        insert(root, value);
    }

    // ����� display : 
    void display() {
        NLR(root);
        cout << endl;
    }

    // ����� clear : ����������� ������, ������� ������ ������.
    void clear() {
        clearLRN(root);
    }

    // ����� print : ��� ����������� ����������� ������ � �������
    void print() {
        printTree(root, 0);
    }
     
    // ����� getRoot: ���������� ������
    shared_ptr<TreeNode<T>> getRoot() {
        return root;
    }

    vector<T> preorder() {
        vector<T> result;
        preOrder(root, result);
        return result;
    }

    vector<T> inorder() {
        vector<T> result;
        inOrder(root, result);
        return result;
    }

    vector<T> postorder() {
        vector<T> result;
        postOrder(root, result);
        return result;
    }

    vector<T> preorder1() {
        vector<T> result;
        preOrder1(root, result);
        return result;
    }

    vector<T> inorder1() {
        vector<T> result;
        inOrder1(root, result);
        return result;
    }

    vector<T> postorder1() {
        vector<T> result;
        postOrder1(root, result);
        return result;
    }
};
    
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

    // RNL ������������: ���������� ����� ������ � ������� �������� �����.
    template <typename T>
    void RNL(shared_ptr<TreeNode<T>> node) {
        if (node) {
            RNL(node->right);
            cout << node->value << " ";
            RNL(node->left);
        }
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

    // depth: ����������� ������� ������
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
    
    // Push_back � ��� ������� � C++ ��� ���������� ��������� � ������.
    // ��� ��������� ������� ���� ������� � ��������� ��� � ����� �������.
    // ���� � ������� �� ������� �����, �� ������������� ��������� �������,
    // ����� �������� ����� �������.
    // ������� push_back ������, ���������� � �������� ���������.
    
    // NLR ������
    template <typename T>
    void preOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            result.push_back(node->value);
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
    };

    // NRL ������
    template <typename T>
    void preOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            result.push_back(node->value);
            preOrder(node->right, result);
            preOrder(node->left, result);
        }
    };

    // LNR ������������
    template <typename T>
    void inOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            inOrder(node->left, result);
            result.push_back(node->value);
            inOrder(node->right, result);
        }
    };

    // RNL ������������
    template <typename T>
    void inOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            inOrder(node->right, result);
            result.push_back(node->value);
            inOrder(node->left, result);
        }
    };

    // LRN ��������
    template <typename T>
    void postOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            postOrder(node->left, result);
            postOrder(node->right, result);
            result.push_back(node->value);
        }
    };

    // RLN ��������
    template <typename T>
    void postOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            postOrder(node->right, result);
            postOrder(node->left, result);
            result.push_back(node->value);
        }
    };
	
	// ����������� �����������
	template <typename T>
    BinaryTree(const BinaryTree<T>& other) {
        copyHelper(root, other.root);
    };

    // ���������� ���� (������� ������)
	template <typename T>
    void insert(const T& value) {
        auto newNode = make_shared<TreeNode<T>>(value);
        if (!root) {
            root = newNode;
            return;
        }
        queue<shared_ptr<TreeNode<T>>> queue;
        queue.push(root);
        while (!queue.empty()) {
            auto current = queue.front();
            queue.pop();
            if (!current->left) {
                current->left = newNode;
                return;
            } else {
                queue.push(current->left);
            }
            if (!current->right) {
                current->right = newNode;
                return;
            } else {
                queue.push(current->right);
            }
        }
    };

    // ����� � ������
	template <typename T>
    void breadthFirstTraversal() const {
        if (!root) return;
        queue<shared_ptr<TreeNode<T>>> queue;
        queue.push(root);
        while (!queue.empty()) {
            auto current = queue.front();
            queue.pop();
            cout << current->data << " ";
            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
    };

/// �������� ������� testBinaryTree1 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
    void testBinaryTree1() {
        BinaryTree<int> tree;
        // ��������� 5 �����
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);

        // ������� ������
        cout << "���������� ������: ";
        tree.display();
        cout << endl;
        // ����������� ������
        tree.clear();
        cout << "������ �������." << endl;
    };

/// �������� ������� testBinaryTree2 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
    void testBinaryTree2() {
        BinaryTree<int> tree;
        // ��������� 5 �����
        tree.insert(5);
        tree.insert(3);
        tree.insert(8);
        tree.insert(1);
        tree.insert(4);

        cout << "��������� ������:\n";
        tree.print();
        cout << endl;
        
        cout << "Preorder: ";
        for (const int& value : tree.preorder()) {
            cout << value << " ";
        }
        cout << endl;

        cout << "Preorder1: ";
        for (const int& value : tree.preorder1()) {
            cout << value << " ";
        }
        cout << endl;

        cout << "Inorder: ";
        for (const int& value : tree.inorder()) {
            cout << value << " ";
        }
        cout << endl;

        cout << "Inorder1: ";
        for (const int& value : tree.inorder1()) {
            cout << value << " ";
        }
        cout << endl;

        cout << "Postorder: ";
        for (const int& value : tree.postorder()) {
            cout << value << " ";
        }
        cout << endl;

        cout << "Postorder1: ";
        for (const int& value : tree.postorder1()) {
            cout << value << " ";
        }
        cout << endl;
    };
	
	/// �������� ������� testBinaryTree3 : ������� �������� ������,
    /// ��������� � ���� 5 �����, � ������� �� ����������.
	void testBinaryTree3() {
        BinaryTree<int> tree;
        // ��������� 5 �����
		tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);

        cout << "����� � ������ (�����): ";
        tree.breadthFirstTraversal(); // ��������� �����: 1 2 3 4 5
        cout << endl;

       // ����������� ������
       BinaryTree<int> copiedTree(tree);
       cout << "����� � ������ �������������� ������: ";
       copiedTree.breadthFirstTraversal(); // ��������� �����: 1 2 3 4 5
       cout << endl;
    };
		