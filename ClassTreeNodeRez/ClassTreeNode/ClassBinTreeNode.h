/// Бурдинская Наталья ВМК-22
/// Date - 03.09.2024
#pragma once
#include "ClassTreeNode.h"

// Класс BinaryTree : Реализует бинарное дерево поиска.Он содержит методы для
// вставки узлов, обхода дерева(inorder), очистки дерева и получения корня.
template<typename T>
class BinaryTree {
private:
    shared_ptr<TreeNode<T>> root; // корень дерева

    void insert(shared_ptr<TreeNode<T>>& node, T value) {
        if (!node) {
            node = make_shared<TreeNode<T>>(value);
            /// make_shared() — это функция, имеющая преимущество при выделении памяти
            /// для совместно используемого объекта и интеллектуального указателя с 
            /// единственным выделением, в отличие от явного получения shared_ptr через конструктор.
            /// если node пустой, make_shared выделяет память типа <TreeNode<T>> для узла со значением value
            return;
        }
        if (value < node->value) {
            insert(node->left, value);
        }
        else {
            insert(node->right, value);
        }
    }
	
	// Создается копия дерева, чтобы в дальнейшем выполнить обход в ширину для скопированного дерева.
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

    // Метод insert : Рекурсивно вставляет значения в дерево, основываясь на сравнении.
    void insert(T value) {
        insert(root, value);
    }

    // Конструктор копирования
	BinaryTree(const BinaryTree<T>& other) {
        copyHelper(root, other.root);
    }
    // Метод display : 
    void display() {
        NLR(root);
        cout << endl;
    }

    // Метод clear : Освобождает память, занятую узлами дерева.
    void clear() {
        clearLRN(root);
    }

    // Метод print : для визуального отображения дерева в консоли
    void print() {
        printTree(root, 0);
    }
     
    // Метод getRoot: возвращает дерево
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
    
    // NLR прямой : Производит обход дерева и выводит значения узлов. 
    template <typename T>
    void NLR(shared_ptr<TreeNode<T>> node) {
        if (node) {
            cout << node->value << " ";
            NLR(node->left);
            NLR(node->right);
        }
    };

    // NRL прямой : Производит обход дерева и выводит значения узлов. 
    template <typename T>
    void NRL(shared_ptr<TreeNode<T>> node) {
        if (node) {
            cout << node->value << " ";
            NRL(node->right);
            NRL(node->left);
        }
    };

    // LNR симметричный : Производит обход дерева и выводит значения узлов.
    template <typename T>
    void LNR(shared_ptr<TreeNode<T>> node) {
        if (node) {
            LNR(node->left);
            cout << node->value << " ";
            LNR(node->right);
        }
    };

    // LRN обратный : Производит обход дерева и выводит значения узлов.
    template <typename T>
    void LRN(shared_ptr<TreeNode<T>> node) {
        if (node) {
            LRN(node->left);
            LRN(node->right);
            cout << node->value << " ";
        }
    };

    // RLN обратный : Производит обход дерева и выводит значения узлов.
    template <typename T>
    void RLN(shared_ptr<TreeNode<T>> node) {
        if (node) {
            RLN(node->right);
            RLN(node->left);
            cout << node->value << " ";
        }
    };

    // RNL симметричный: Производит обход дерева и выводит значения узлов.
    template <typename T>
    void RNL(shared_ptr<TreeNode<T>> node) {
        if (node) {
            RNL(node->right);
            cout << node->value << " ";
            RNL(node->left);
        }
    };

    // clear : Освобождает память, занятую узлами дерева. LRN очистка
    template <typename T>
    void clearLRN(shared_ptr<TreeNode<T>>& node) {
        if (node) {
            clearLRN(node->left);
            clearLRN(node->right);
            node.reset();
        }
    };

    // clear : Освобождает память, занятую узлами дерева. RLN очистка
    template <typename T>
    void clearRLN(shared_ptr<TreeNode<T>>& node) {
        if (node) {
            clearRLN(node->right);
            clearRLN(node->left);
            node.reset();
        }
	};

    // depth: Определение глубины дерева
    template <typename T>
    int depth_root(shared_ptr<TreeNode<T>>& node) {
        if (node == nullptr) return -1;
        else { return max(depth_root(node->left), depth_root(node->right)) + 1; }
    };

    // count_nodes: Возвращает количество узлов
    template <typename T>
    unsigned int count_nodes_root(shared_ptr<TreeNode<T>>& node) {
        if (node == nullptr) return 0;
        else { return 1 + count_nodes_root(node->left) + count_nodes_root(node->right); }
    };

    // printTree: Функция для визуального отображения дерева в консоли
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
    
    // Push_back — это функция в C++ для добавления элементов в вектор.
    // Она принимает элемент типа вектора и добавляет его в конец вектора.
    // Если в векторе не хватает места, он автоматически управляет памятью,
    // чтобы добавить новый элемент.
    // Функция push_back проста, эффективна и довольно безопасна.
    
    // NLR прямой
    template <typename T>
    void preOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            result.push_back(node->value);
            preOrder(node->left, result);
            preOrder(node->right, result);
        }
    };

    // NRL прямой
    template <typename T>
    void preOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            result.push_back(node->value);
            preOrder(node->right, result);
            preOrder(node->left, result);
        }
    };

    // LNR симметричный
    template <typename T>
    void inOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            inOrder(node->left, result);
            result.push_back(node->value);
            inOrder(node->right, result);
        }
    };

    // RNL симметричный
    template <typename T>
    void inOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            inOrder(node->right, result);
            result.push_back(node->value);
            inOrder(node->left, result);
        }
    };

    // LRN обратный
    template <typename T>
    void postOrder(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            postOrder(node->left, result);
            postOrder(node->right, result);
            result.push_back(node->value);
        }
    };

    // RLN обратный
    template <typename T>
    void postOrder1(shared_ptr<TreeNode<T>> node, vector<T>& result) {
        if (node) {
            postOrder(node->right, result);
            postOrder(node->left, result);
            result.push_back(node->value);
        }
    };
	
	// Добавление узла (простой пример)
	// через queue в языке програмирования C++, добавление, удаление и изменение элементов очереди,
	// получение первого и последнее элементов, функции push и pop. 
	// Класс queue<T> представляет очередь - контейнер, который работает по принципу FIFO
        // (first-in first-out или "первый вошел — первым вышел") — первым всегда извлекается первый добавленный элемент.
	template <typename T>
    void insertNode(const T& value) {
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

    // Обход в ширину
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

/// Тестовая функция testBinaryTree1 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
    void testBinaryTree1() {
        BinaryTree<int> tree;
        // Вставляем 5 узлов
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);

        // Выводим дерево
        cout << "Содержимое дерева: ";
        tree.display();
        cout << endl;
        // Освобождаем память
        tree.clear();
        cout << "Дерево очищено." << endl;
    };

/// Тестовая функция testBinaryTree2 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
    void testBinaryTree2() {
        BinaryTree<int> tree;
        // Вставляем 5 узлов
        tree.insert(5);
        tree.insert(3);
        tree.insert(8);
        tree.insert(1);
        tree.insert(4);

        cout << "Структура дерева:\n";
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
	
	/// Тестовая функция testBinaryTree3 : Создает бинарное дерево,
    /// добавляет в него 5 узлов, и выводит их содержимое.
	void testBinaryTree3() {
        BinaryTree<int> tree;
        // Вставляем 5 узлов
	tree.insertNode(1);
        tree.insertNode(2);
        tree.insertNode(3);
        tree.insertNode(4);
        tree.insertNode(5);

        cout << "Обход в ширину (далее): ";
        tree.breadthFirstTraversal(); // Ожидаемый вывод: 1 2 3 4 5
        cout << endl;

       // Копирование дерева
       BinaryTree<int> copiedTree(tree);
       cout << "Обход в ширину скопированного дерева: ";
       copiedTree.breadthFirstTraversal(); // Ожидаемый вывод: 1 2 3 4 5
       cout << endl;
    };
		
		
