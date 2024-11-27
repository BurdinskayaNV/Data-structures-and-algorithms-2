#pragma once
#include "BinarySearchTree.h"
// ��������� ����� AVLTreeNode, ������� ��������� ������ ����� TreeNode.
// ����� AVLTreeNode ������������ ��� ������������� ���� AVL-������,
// ������� �������� ������������������� �������� ������� ������.
// ���� AVL-������ ������������� ������ ������ �������, ������� �������� ������������
// ������������������ ������ ����� ������ �������� ������� ��� ��������.
// ����� AVLTreeNode ����������� �� TreeNode � ����� �������������� ���� ��� ������������ �������.
template<typename T>
class AVLTreeNode : public TreeNode<T> {
public:
    // ����������� �� ���������, �������������� ������� ����� TreeNode � ������������� ������ ������� � 0.
    AVLTreeNode() : TreeNode<T>(), balanceFactor(0) {}
    // �����������, ������� �������������� ���� � ������� � ������������� ������ ������� � 0.
    AVLTreeNode(const T& data) : TreeNode<T>(data), balanceFactor(0) {}
    // �����������, ������� �������������� ���� � ������� ������ � ����������� �� ������ � ������� �������� � ������������� ������ ������� � 0.
    AVLTreeNode(const T& data, TreeNode<T>* getLeft(), TreeNode<T>* getRight()) : TreeNode<T>(data, getLeft(), getRight()), balanceFactor(0) {}
    // ����������.
    ~AVLTreeNode() {}
    // ����������� �����������, ������� �������� ������ ���� � ��� ������ �������.
    AVLTreeNode(const AVLTreeNode& other) : TreeNode<T>(other), balanceFactor(other.balanceFactor) {}
    // ����������� �����������, ������� ������� ������ ���� � ��� ������ �������.
    AVLTreeNode(AVLTreeNode&& other) : TreeNode<T>(move(other)), balanceFactor(other.balanceFactor) {}
    // �������� ����������� ������������, ���������� ������ � ������ ������� �� ������� ����.
    AVLTreeNode& operator=(const AVLTreeNode& other) {
        TreeNode<T>::operator=(other);
        balanceFactor = other.balanceFactor;
        return *this;
    }
    // �������� ������������� ������������, ������������ ������ � ������ ������� �� ������� ����.
    AVLTreeNode& operator=(AVLTreeNode&& other) {
        TreeNode<T>::operator=(move(other));
        balanceFactor = other.balanceFactor;
        return *this;
    }

    // ������ �������(�������) ��� ������ � ������� �������� :
    // ��������������� ��������� �� (�� �����) TreeNode � ��������� �� AVLTreeNode
    AVLTreeNode<T>* getLeft() { return static_cast<AVLTreeNode<T>*>(this->n_left); }
    // ��������������� ��������� �� (�� ������) TreeNode � ��������� �� AVLTreeNode
    AVLTreeNode<T>* getRight() { return static_cast<AVLTreeNode<T>*>(this->n_right); }

    // ����������� ������ ��������.
    // ��������������� ��������� �� (�� �����) TreeNode � ��������� �� AVLTreeNode
    const AVLTreeNode<T>* getLeft() const { return static_cast<const AVLTreeNode<T>*>(this->n_left); }
    // ��������������� ��������� �� (�� ������) TreeNode � ��������� �� AVLTreeNode
    const AVLTreeNode<T>* getRight() const { return static_cast<const AVLTreeNode<T>*>(this->n_right); }

    // ����������� ������� ����. ����, ������� ������ ������ ������� ��� ����.
    short int balanceFactor;
};

// ����� AVLTree ������������ ����� ���� ���������������� �������� ������ ������.
template<typename T>
class AVLTree {
private:
    // ��������� �� ������ ������.
    AVLTreeNode<T>* root;

    // ������� ��� ���������� ������������ ������� ����.
    // ��������� ��������������� ������ ��� �������� ����.
    // ��������������� ������ ���� ����������� ��� ������� � ������ ��� ������ � ������� �����������.
    void updateBalanceFactor(AVLTreeNode<T>* node) {
        if (node == nullptr) { return; }
        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());
        node->balanceFactor = leftHeight - rightHeight;
    }

    // ������� ��� ��������� ������ ����.
    // ���������� ������ ������ ��� ��������� � ������ ������.
    int getHeight(AVLTreeNode<T>* node) {
        if (node == nullptr) { return 0; }
        return 1 + max(getHeight(node->getLeft()), getHeight(node->getRight()));
    }

    // rotateRight � rotateLeft: ��������� ������ � ����� �������� ��������������.
    // ��� �������� ���������� ��� ����������� ������������������ ������.
    // ������� ��� ������� ��������.
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getLeft(); // ����� �������� ���� ���������� ����� ������
        node->n_left = temp->getRight(); // ������� ���������
        temp->n_right = node; // ������� ���� ���������� ������ �������� ������ �����
        updateBalanceFactor(node); // ���������� ��������������� ��������
        updateBalanceFactor(temp); // ���������� ��������������� �������� ������ ������
        return temp; // ���������� ����� ������ ����� ��������
    }
    // ������� ��� ������ ��������.
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getRight(); // ������ �������� ���� ���������� ����� ������
        node->n_right = temp->getLeft(); // ������� ���������
        temp->n_left = node; // ������� ���� ���������� ����� �������� ������ �����
        updateBalanceFactor(node); // ���������� ��������������� ��������
        updateBalanceFactor(temp); // ���������� ��������������� �������� ������ ������
        return temp; // ���������� ����� ������ ����� ��������
    }

    // balanceTree: ��������� ��������������� ������ � ��������� ��������������� ��������, ���� ������ ����������������.
    // ������� ��� ������������ ������.
    AVLTreeNode<T>* balanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) { return nullptr; }
        updateBalanceFactor(node);
        if (node->balanceFactor > 1) { // ���� ����� ��������� �������
            if (getHeight(node->getLeft()->getLeft()) >= getHeight(node->getLeft()->getRight())) {
                node = rotateRight(node); // ��������� ������ �������
            }
            else {
                //������� ������ �������
                node->n_left = rotateLeft(node->getLeft()); // ����� ������ �������
                node = rotateRight(node);
            }
        }
        else if (node->balanceFactor < -1) { // ������ ��������� �������
            if (getHeight(node->getRight()->getRight()) >= getHeight(node->getRight()->getLeft())) {
                node = rotateLeft(node); //��������� ����� �������
            }
            else {
                //������� ����� �������
                node->n_right = rotateRight(node->getRight()); // ������ ����� �������
                node = rotateLeft(node);
            }
        }
        return node; // ���������� ���������������� �������� ���������
    }

    // ������� ��� ������� ������ ���� � ������.
    // insertNode: ��������� ������� �������� � AVL-������. ����� ������� ���������� balanceTree ��� ����������� ������������������.
    AVLTreeNode<T>* insertNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) { return new AVLTreeNode<T>(data); }
        if (data < node->n_data) {
            node->n_left = insertNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = insertNode(node->getRight(), data);
        }
        return balanceTree(node); // ������������ ����� �������
    }

    // ������� ��� �������� ���� �� ������.
    // deleteNode: ������� ������� �� AVL-������ � ���������������� ��� ����, ���� ��� ����������, ��� ����������� ���������������� ���������.
    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) { return nullptr; }
        if (data < node->n_data) {
            node->n_left = deleteNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = deleteNode(node->getRight(), data);
        }
        else {
            if (node->getLeft() == nullptr) { // ���� ��� ������ �������
                AVLTreeNode<T>* temp = node->getRight(); // ������ ������ ��������
                delete node;
                return temp;
            }
            else if (node->getRight() == nullptr) { // ���� ��� ������� �������
                AVLTreeNode<T>* temp = node->getLeft(); // ������ ����� ��������
                delete node;
                return temp;
            }
            AVLTreeNode<T>* temp = node->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft(); // ������� ����������� ���� � ������ ���������
            }
            node->n_data = temp->n_data; // ����������� ������
            node->n_right = deleteNode(node->getRight(), temp->n_data); // �������� ����
        }
        return balanceTree(node); // ������������ ����� ��������
    }
public:
    // ����������� �� ���������.
    // �����������, ���������������� ������ root ��� nullptr.
    AVLTree() : root(nullptr) {}

    // ����������.
    // �������� ����� clear ��� ������� ������ ����� ��������� �������.
    ~AVLTree() { clear(); }

    // ������� ��� ������� �������� � ������.
    // ����� insert: ����� ��� ������� ������ �������� � ������.
    // �� �������� ��������� ����� insertNode, ������� ��������� �������
    // � ������������ �����.
    void insert(const T& data) {
        root = insertNode(root, data);
    }

    // ������� ��� �������� �������� �� ������.
    // ����� remove: ����� ��� �������� �������� �� ������,
    // ���������� ��������� ����� deleteNode.
    void remove(const T& data) {
        root = deleteNode(root, data);
    }

    // ����� ��� ������ ������ � ���� ������.
    // ����� toString: ����� ��� �������������� ������ � ������.
    // ���������� ��������������� ����� toStringHelper.
    // template<typename T>
    string toString() {
        string result = "";
        toStringHelper(root, result);
        return result;
    }

    // ����� ��� ������ ������ � ���� ������.
    // ����� printTree: ����� ��� ������ ������ �� �����.
    // �� �������� printTreeHelper ��� ����������� ������ ������� � ��������� ����.
    void printTree() {
        if (root) printTreeHelper(root, 0);
    }

    // ����� ��� ������ �������� � ������.
    // ����� find: ����� ������ ���� � �������� ���������. ���������� ����� findHelper.
    AVLTreeNode<T>* find(const T& data) {
        return findHelper(root, data);
    }

    // ����� ������ ���� � ������
    // ����� findNode: ����� ��� ������ ���� � ����������� ��������� �� ����.
    // ���������� nullptr, ���� ���� �� ������.
    AVLTreeNode<T>* findNode(const T& data) {
        AVLTreeNode<T>* current = root;
        while (current != nullptr) {
          if (data < current->n_data) {
              current = current->getLeft();
          }
          else if (data > current->n_data) {
              current = current->getRight();
          }
          else {
              return current; // �������
          }
        }
        return nullptr; // �� �������
    }

    // ����� ��� ������� � ������������ ������� ���� �� ����.
    // ����� getBalanceFactorNode: ���������� ��������������� ������ ��� ������������� ����.
    int getBalanceFactorNode(AVLTreeNode<T>* node) {
        if (node == nullptr) { return 0; }
        return node->balanceFactor;
    }

    // ����� getBalanceFactor: ���������� ��������������� ������ ��� ����
    // � �������� ��������� ��� ���������� ���������� out_of_range, ���� ���� �� ������.
    int getBalanceFactor(T val) {
        AVLTreeNode<T>* node = find(val);
        if (node) { return getBalanceFactorNode(node); }
        else
            throw out_of_range("�������� �� �������");
    }

    // ����� Iterator, ��������������� ��� ����������������� ������ AVL-������.
    // �������� ���������� ���� ��� ���������� ��������� ������, ����������� �������� �� ������ � ������� "�����-�������".
    // � �������� ����� �������� ��������� ������� ������ "in-order", �������� �������� ��������������� ����� ������ �� ������.
    class Iterator {
    private:
        AVLTreeNode<T>* root; // �������� ����
        stack<AVLTreeNode<T>*> nodeStack; // ���� ��� ������ �����
    public:
        // ����������� ���������, �������������� ��������� ����
        Iterator(AVLTreeNode<T>* n_root) {
            root = n_root;
            pushLeftBranch(n_root);
        }
        // �������� �������� �� �����������
        bool operator!=(const Iterator& other) const {
            return !(hasNext() == false && other.hasNext() == false);
        }
        // �������� �������� �� ���������
        bool operator==(const Iterator& other) const {
            return nodeStack.empty() == other.nodeStack.empty();
        }
        // �������� ���� �� ��������� �������
        bool hasNext() const {
            return !nodeStack.empty();
        }
        // �������� ������������� ��� ������� � ������ �������� ����
        T& operator*() const {
            return nodeStack.top()->n_data;
        }
        // ���������� ������ �� ������ �������� ����
        T& data() {
            return nodeStack.top()->n_data;
        }
        // �������� ����������, ������������ � ���������� ����
        Iterator& operator++() {
            return next();
        }
        // ���������� �������� � ������ ������
        void reset() {
            while (!nodeStack.empty())
                nodeStack.pop();
            pushLeftBranch(root);
        }
        // ������� � ���������� ����
        Iterator& next() {
            AVLTreeNode<T>* currentNode;
            if (!hasNext()) {
                throw out_of_range("� ��������� ������ ��� ���������");
            }
            currentNode = nodeStack.top();
            nodeStack.pop();
            pushLeftBranch(currentNode->getRight());
            return *this;
        }
    private:
        // ��������������� ����� ��� ���������� ���� ����� �������� ����� � ����
        void pushLeftBranch(AVLTreeNode<T>* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = node->getLeft();
            }
        }
    };

    // ���������� �������� �� ������ ������
    Iterator begin() const {
        return Iterator(root);
    };
    // ��������� �������� �� ����� ������
    Iterator end() const {
        return Iterator(nullptr);
    };
    // ����� ��� ������� AVL-������
    void clear() {
        if (root)
        {
            clearNode(root);
            root = nullptr;
        }
    };

    // ������� ������������ ��� AVL-������
    // - ������� ���������: ��� �������������� ��������� �������� � ������ � ���������, ��������� �� ��� ��������� � ������� ������� find().
    // - �������� ���������: ��� ����� ���������, ��� �������� ��������� ��������� �� ������.
    // - ��������: ������������ �������� ��� ������� �� ���� ��������� ������, ����� ���������,
    //   ��� ��� � �������(� ������������ �������, ��� ������ ���� � �������� ������ ������).
    // - ������������: ��� ������� �������� ������ ����������� ������, ����� ���������, ��� ������ AVL �������� ����������������.
    // - ������� ������: �����������, ��� ����� ������� ��� ����������� �������� �� ������� � ������.
    static void AVLTreeTest() {
        AVLTree<int> tree;

        // ������������ ������� � ������ ������
        tree.insert(10);
        assert(tree.find(10) != nullptr); // ������ ����� 10
        assert(tree.find(20) == nullptr); // �� ������ ����� 20

        // ������������ ������� ���������� ���������
        tree.insert(20);
        tree.insert(5);
        tree.insert(15);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        assert(tree.find(5) != nullptr);  // ������ ����� 5
        assert(tree.find(15) != nullptr); // ������ ����� 15
        assert(tree.find(25) == nullptr); // �� ������ ����� 25

        // ������������ �������� ��������
        tree.remove(20);
        assert(tree.find(20) == nullptr); // 20 ������ ���� ������

        // ������������ �������� �����
        tree.remove(10);
        assert(tree.find(10) == nullptr); // 10 ������ ���� ������

        // ������������ �������� ��������, �������� ���
        tree.remove(100); // ������ �� ����������, ������ �������� ����������

        // ������������ ���������
        tree.insert(7);
        tree.insert(3);
        tree.insert(8);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        AVLTree<int>::Iterator it = tree.begin();
        for (int val : tree) {
            cout << val << " ";
        }
        cout << endl;
        assert(it != tree.end()); // ������ ����� ���� �� ���� �������
        assert(*it == 3);         // ������ ������� ������ ���� 3
        ++it;
        assert(*it == 5);         // ������ ������� ������ ���� 5
        ++it;
        assert(*it == 7);         // ������ ������� ������ ���� 7
        ++it;
        assert(*it == 8);         // ��������� ������� ������ ���� 8
        ++it;
        assert(*it == 15);         // ��������� ������� ������ ���� 
        ++it;
        assert(it == tree.end()); // ���������� �����
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        // ������������ ������� ������� ������
        tree.clear();
        assert(tree.find(5) == nullptr);  // ��� �������� ������ ���� �������
        assert(tree.begin() == tree.end()); // �������� ������ ���� ������

        // ������������ ��������� ������
        size_t i;
        // ������� ����� ����� (����� ������ �������)
        vector<int> right;
        tree.insert(7);
        tree.insert(8);
        tree.insert(5);
        tree.insert(6);
        tree.insert(3);
        tree.insert(4);
        tree.insert(1);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        right = { 1, 3, 4, 5, 6, 7, 8 };
        i = 0;
        for (int value : tree)
        {
            assert(abs(tree.getBalanceFactor(value)) < 2); // tree.getBalanceFactor(value) �� ������ < 2
            i++;
        }
        tree.clear();

        // ������� ���� ���� (����� ����� �������)
        vector<int> left;
        tree.insert(2);
        tree.insert(1);
        tree.insert(4);
        tree.insert(3);
        tree.insert(6);
        tree.insert(5);
        tree.insert(7);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        left = { 1, 2, 3, 4, 5, 6, 7 };
        i = 0;
        for (int value : tree)
        {
            assert(abs(tree.getBalanceFactor(value)) < 2); // tree.getBalanceFactor(value) �� ������ < 2
            i++;
        }
        tree.clear();

        // ������� ���� �����
        vector<int> leftright;
        tree.insert(6);
        tree.insert(7);
        tree.insert(2);
        tree.insert(1);
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        leftright = { 1, 2, 3, 4, 5, 6, 7 };
        i = 0;
        for (int value : tree)
        {
            assert(abs(tree.getBalanceFactor(value)) < 2); // tree.getBalanceFactor(value) �� ������ < 2
            i++;
        }
        tree.clear();

        // ������� ����� ����
        vector<int> rightleft;
        tree.insert(2);
        tree.insert(1);
        tree.insert(6);
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        tree.insert(7);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        AVLTree<int>::Iterator it5 = tree.begin();
        rightleft = { 1, 2, 3, 4, 5, 6, 7 };
        i = 0;
        for (int value : tree)
        {
            assert(*it5 == rightleft[i]);
            ++it5;
            i++;
        }
        tree.clear();
        cout << "��� ����� ������ ������� !!!" << endl;
        cout << "----------------------------" << endl;
        cout << endl;
    }
};

// ��������������� ����� ��� ������ �������� � ������.
// findHelper: ��� ������� ���� ���� � ���������� ������� � AVL-������.
template<typename T>
AVLTreeNode<T>* findHelper(AVLTreeNode<T>* node, const T& data) {
    // ���� ������� ���� ����� nullptr, ��� ��������, ��� ������� ������� �����������, � ������� ���������� nullptr.
    if (node == nullptr) { return nullptr; } 
    // ���� ������ ������ ������ �������� ���� (node->n_data), ����� ������������ � ����� ���������.
    if (data < node->n_data) {
        return findHelper(node->getLeft(), data);
    }
    // ���� ������ ������, �� � ������ ���������.
    else if (data > node->n_data) {
        return findHelper(node->getRight(), data);
    }
    // ���� ����� ����������, ������������ ������� ����.
    else {
        return node;
    }
};

// ������� ��� ����������� ������.
// ������� ���������� ������� ��� ���� ������
template<typename T>
void clearNode(AVLTreeNode<T>* node) {
    // ���� ������� ���� ����� nullptr, ������ �� ��������.
    if (node == nullptr) { return; }
    // ������� ������� ���������� ������� ����� � ������ ���������.
    clearNode(node->getLeft());
    clearNode(node->getRight());
    // ����� ������� ��� ������� ����
    delete node;
};

// ��������������� ����� ��� ������ ������ � ���� ������.
// printTreeHelper: ��� ������� ���������� �������� ������ � ������� � ���������,
// ������� ���������� ������� ����������� �����.
template<typename T>
void printTreeHelper(AVLTreeNode<T>* node, int level) {
    // ���� ������� ���� ����� nullptr, ������ �� ��������.
    if (node == nullptr) { return; }
    // ������� ������� ���������� ���������� � ������� ���������, ���������� �������.
    printTreeHelper(node->getRight(), level + 1);
    // ����� ������� ������� ������ ���� � ���������.
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    // �������� ������ ����
    cout << node->n_data << endl;
    // ����� ����� ������������ ����� ���������.
    printTreeHelper(node->getLeft(), level + 1);
};

// ��������������� ����� ��� ������ ������ � ���� ������.
// toStringHelper: ��� ������� ����������� ������ � ������,
// �������������� ����� � ������������ ������� (in-order traversal).
template<typename T>
void toStringHelper(AVLTreeNode<T>* node, std::string& result) {
    // ���� ������� ���� ����� nullptr, ������ �� ��������.
    if (node == nullptr) { return; }
    // ������� ���������� ����������� ���������� �� ������ ���������.
    toStringHelper(node->getLeft(), result);
    // ����� ����������� ������ �������� ���� � ������ ����������.
    result += to_string(node->n_data) + " ";
    // ����� ���� �������������� ������ ���������.
    toStringHelper(node->getRight(), result);
};
