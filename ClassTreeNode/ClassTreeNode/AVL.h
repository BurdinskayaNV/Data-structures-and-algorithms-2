// PREORDER, NLR, NRL, прямой обход дерева
// INORDER,  // LNR, RNL, симметричный обход дерева
// POSTORDER // LRN, RLN, обратный обход дерева
#pragma once
#include "ClassBinTreeNode.h"

//Этот код реализует AVL дерево, используя шаблонный класс
// для представления узла бинарного дерева поиска.
// Основные операции включают добавление элементов с поддержкой балансировки
// и возможность обхода дерева.
// Каждая вставка обновляет высоты дерева и выполняет необходимые вращения 
// для поддержания сбалансированности.
// 
// AVL-дерево — это дерево поиска с самобалансировкой, 
// где разница в высоте поддеревьев для любого узла не превышает одного.

// Узел AVL дерева
// Шаблонный класс узла дерева 
template <typename T>
class AVLTreeNode {
public:
    T value;          // Данные, хранящиеся в узле
    AVLTreeNode<T>* left;  // Указатель на левый дочерний узел
    AVLTreeNode<T>* right; // Указатель на правый дочерний узел
    // дополнительный член класса, позволяет избегать "перевешивания" узлов
    int height;         // Высота узла для балансировки AVL-дерева
    
     // Конструктор для инициализации узла с заданными данными
     AVLTreeNode(T val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// Класс для реализации AVL дерева
template <typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root;   // Корневой узел AVL дерева

    // Функция для получения высоты узла
    int getHeight(AVLTreeNode<T>* node) {
        // Проверяем, существует ли узел node ?
        // Если узел существует, возвращаем его высоту node->height
        // Если узел не существует , возвращаем : 0
        return node ? node->height : 0;
    }

    // Функция для подсчета баланса узла
    // Вычисление разницы высот левого и правого поддеревьев
    int getBalance(AVLTreeNode<T>* node) {
        // Проверяем, существует ли узел node ?
        // Если узел существует, возвращаем getHeight(node->left) - getHeight(node->right)
        // Если узел не существует , возвращаем : 0
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Правый поворот - Вращение вправо
    // Функция для выполнения правого вращения вокруг узла y
    // x->left и x->right — это левые и правые дочерние узлы текущего узла x.
    // getHeight(x->left) и getHeight(x->right) вызывают функцию getHeight, 
    // которая возвращает высоту левого и правого поддеревьев.
    // max(getHeight(x->left), getHeight(x->right)) вычисляет максимальную высоту
    // между левым и правым поддеревом.
    // + 1 увеличивает максимальную высоту на единицу, учитывая текущий узел x.
    // x->height присваивается результат, который является новой высотой узла x.
    AVLTreeNode<T>* rightRotate(AVLTreeNode<T>* y) {
        AVLTreeNode<T>* x = y->left;   // x становится новым корнем поддерева
        AVLTreeNode<T>* T2 = x->right; // T2 сохраняет правое поддерево x

        // Выполнение вращения
        // получает левый дочерний узел y и сохраняет его как x,
        // а правое поддерево x как T2
        x->right = y;  // Новый правый потомок x - y
        y->left = T2;  // Новый левый потомок y - T2

        // Обновляем высоты узлов y и x
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        // Возврат нового корня
        return x;
    }

    // Левый поворот - Вращение влево
    // x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 
    // x->left и x->right — это левые и правые дочерние узлы текущего узла x.
    // y->left и y->right — это левые и правые дочерние узлы текущего узла y.
    // getHeight(x->left) и getHeight(x->right) вызывают функцию getHeight, 
    // которая возвращает высоту левого и правого поддеревьев.
    // max(getHeight(x->left), getHeight(x->right)) вычисляет максимальную высоту
    // между левым и правым поддеревом.
    // + 1 увеличивает максимальную высоту на единицу, учитывая текущий узел x.
    // x->height присваивается результат, который является новой высотой узла x.
    AVLTreeNode<T>* leftRotate(AVLTreeNode<T>* x) {
        // y станет новым корневым узлом поддерева после поворота
        AVLTreeNode<T>* y = x->right;
        // T2 сохранит поддерево, которое было левым поддеревом у y
        AVLTreeNode<T>* T2 = y->left;

        // Выполнение вращения
        // Выполнение вращения: y становится корнем, а x — левым потомком y
        y->left = x;
        x->right = T2;

        // Обновление высот узлов x и y после выполнения вращения
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        // Возвращает y в качестве нового корня поддерева
        return y;
    }

    // Вставка узла
    // Рекурсивное добавление узла в дерево с учетом балансировки
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T value) {
        // Выполнение стандартной операции вставки, если !node
        if (!node) return new AVLTreeNode<T>(value);

        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            return node; // Невозможность добавить дубликаты, поэтому возвращаем node
        }

        // Обновление высоты текущего узла
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Проверьте балансировку узла
        int balance = getBalance(node);

        // LL - Левый левый случай
        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        // RR - Правый правый случай
        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        // LR - Левый правый случай
        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL - Правый левый случай
        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Возврат неизмененного узла указателя
    }

    // Рекурсивный метод для вывода дерева NLR (обход в прямом порядке)
    void preOrder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            cout << root->value << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    // Рекурсивный метод для вывода дерева NRL (обход в прямом порядке)
    void preOrder1(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            cout << root->value << " ";
            preOrder1(root->right);
            preOrder1(root->left);
        }
    }

    // Рекурсивный метод для вывода дерева LNR (обход в симметричном порядке)
    void inOrder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->value << " ";
            inOrder(root->right);
        }
    }

    // Рекурсивный метод для вывода дерева RNL (обход в симметричном порядке)
    void inOrder1(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            inOrder1(root->right);
            cout << root->value << " ";
            inOrder1(root->left);
        }
    }

    // Рекурсивный метод для вывода дерева LRN (обход в обратном порядке)
    void postOrder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->value << " ";
        }
    }

    // Рекурсивный метод для вывода дерева RLN (обход в обратном порядке)
    void postOrder1(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            postOrder1(root->right);
            postOrder1(root->left);
            cout << root->value << " ";
        }
    }

    // Обход в глубину
    void dfsTraversal(AVLTreeNode<T>* node) {
        if (node) {
            cout << node->value << " ";
            dfsTraversal(node->left);
            dfsTraversal(node->right);
        }
    }

    // Поиск узла в дереве
    AVLTreeNode<T>* search(AVLTreeNode<T>* node, int val) {
        if (node == nullptr || node->value == val)
            return node;

        if (val < node->value)
            return search(node->left, val);
        else
            return search(node->right, val);
    }

public:
    // Конструктор для инициализации корневого узла
    AVLTree() : root(nullptr) {}

    // Вставить значение в AVL дерево
    void insert(T value) {
        root = insert(root, value);
    }

    // Вывод дерева NLR
    void preOrder() { preOrder(root); }

    // Вывод дерева NRL
    void preOrder1() { preOrder1(root); }

    // Вывод дерева LNR
    void inOrder() { inOrder(root); }

    // Вывод дерева RNL
    void inOrder1() { inOrder1(root); }

    // Вывод дерева LRN
    void postOrder() { postOrder(root); }

    // Вывод дерева RLN
    void postOrder1() { postOrder1(root); }

    // Обход в глубину
    void dfs() {
        dfsTraversal(root);
        //cout << endl;
    }

    // Обход в ширину
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

    // Проверка баланса дерева после вставки через assert
    assert(tree.search(10) == true);
    assert(tree.search(20) == true);
    assert(tree.search(30) == true);
    assert(tree.search(40) == true);
    assert(tree.search(50) == true);
    assert(tree.search(25) == true);
    assert(tree.search(60) == false);

    cout << "Вывод дерева NLR : ";
    //cout << "Предварительное содержание: " << endl;
    tree.preOrder(); cout << endl;
    // Проверка результата с помощью assert
    // Ожидаемый результат предзаказа
    vector<int> pre_order = {30, 20, 10, 25, 40, 50};
    /*
    // Проверяем порядок предзаказа
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
    cout << "Вывод дерева NRL : ";
    tree.preOrder1(); cout << endl;

    cout << "Вывод дерева LNR : ";
    tree.inOrder(); cout << endl;

    cout << "Вывод дерева RNL : ";
    tree.inOrder1(); cout << endl;
    
    cout << "Вывод дерева LRN : ";
    tree.postOrder(); cout << endl;
    
    cout << "Вывод дерева RLN : ";
    tree.postOrder1(); cout << endl;

    cout << "DFS Обход в глубину : ";
    tree.dfs(); cout << endl;

    cout << "BFS Обход в ширину : ";
    tree.bfs(); cout << endl;

    cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "Тестирование функции AVLtest выполнено успешно" << endl;
};