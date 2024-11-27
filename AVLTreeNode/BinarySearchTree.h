// PREORDER, NLR, NRL, прямой обход дерева
// INORDER,  // LNR, RNL, симметричный обход дерева
// POSTORDER // LRN, RLN, обратный обход дерева
#pragma once
#include <iostream>  /// объявляет cin cout
#include <memory>    /// умные указатели и функции shared_ptr make_shared
#include <cassert>   /// для assert
#include <queue>     /// класс queue представляет очередь 
#include <functional>  /// набор шаблонов классов для работы с функциональными объектами
#include <vector>    /// шаблоны вектора
#include <string>    /// работа со строками
#include <stack>     /// Stack имеет три основные операции: push, pop, а также peek.
#include <locale>    /// определяет функцию setlocale для установки русской локали
#include <algorithm> /// содержит набор функций для выполнения алгоритмических
                     /// операций над контейнерами и над другими последовательностями
#include <sstream>   /// для организации работы со строками через интерфейс потоков 
using namespace std;

// Класс TreeNode представляет собой узел двусвязного списка.
// шаблонный класс TreeNode, который реализует узел бинарного дерева
template<typename T>
class TreeNode {
public:
    T n_data;  // Данные, хранящиеся в узле.
    TreeNode<T>* n_left;  // Указатель на левый дочерний узел.
    TreeNode<T>* n_right; // Указатель на правый дочерний узел.
    // TreeNode(): конструктор по умолчанию, инициализирует данные узла значением
    // по умолчанию для типа T и устанавливает указатели на дочерние узлы в nullptr.
    TreeNode() : n_data(T()), n_left(nullptr), n_right(nullptr) {}
    // TreeNode(const T& data): конструктор, инициализирующий узел заданными данными
    // и оставляющий указатели на дочерние узлы в nullptr.
    TreeNode(const T& data) : n_data(data), n_left(nullptr), n_right(nullptr) {}
    // TreeNode(const T& data, TreeNode<T>* prev, TreeNode<T>* next): конструктор, который
    // инициализирует данные и задаёт указатели на левого и правого дочерние узлы явно.
    TreeNode(const T& data, TreeNode<T>* prev, TreeNode<T>* next) : n_data(data), n_left(prev), n_right(next) {}
    // Деструктор: ~TreeNode(): пока лишь обнуляет указатели на дочерние узлы без явного освобождения памяти.
    ~TreeNode() {
        // Удаляем указатели на предыдущий и следующий узлы
        if (n_left != nullptr) n_left = nullptr;
        if (n_right != nullptr) n_right = nullptr;
    }
    // Конструктор копирования : Создаёт новый объект, копируя данные и создавая новые узлы для всех дочерних узлов.
    // Таким образом, происходит глубокое копирование только самых прямых дочерних узлов.
    TreeNode(const TreeNode& other) : n_data(other.n_data), n_left(nullptr), n_right(nullptr) {
        // Копируем указатели на предыдущий и следующий узлы
        if (other.n_left != nullptr) {
            n_left = new TreeNode(other.n_left->n_data);
        }
        if (other.n_right != nullptr) {
            n_right = new TreeNode(other.n_right->n_data);
        }
    }
    // Конструктор перемещения : Перемещает данные и указатели из другого узла в текущий.
    // Обнуляет указатели другого узла.
    TreeNode(TreeNode&& other) : n_data(other.n_data), n_left(other.n_left), n_right(other.n_right) {
        // Перемещаем указатели на предыдущий и следующий узлы
        other.n_left = nullptr;
        other.n_right = nullptr;
    }
    // Оператор присваивания копированием : Проверяет самоприсваивание,
    // удаляет существующие дочерние узлы и копирует данные и дочерние узлы из другого узла.
    // применено глубокое копирование.
    TreeNode& operator=(const TreeNode& other) {
        // Проверяем самоприсваивание
        if (this == &other) { return *this; }
        // Удаляем текущие указатели на предыдущий и следующий узлы
        delete n_left;
        delete n_right;
        // Копируем данные и указатели из другого узла - глубокое копирование
        n_data = other.n_data;
        if (other.n_left != nullptr) {
            n_left = new TreeNode(other.n_left->n_data);
        }
        if (other.n_right != nullptr) {
            n_right = new TreeNode(other.n_right->n_data);
        }
        return *this;
    }
    // Оператор присваивания перемещением : 
    // Аналогично перемещающему конструктору, только в форме оператора присваивания. 
    TreeNode& operator=(TreeNode&& other) {
        // Проверяем самоприсваивание
        if (this == &other) { return *this; }
        // Перемещаем данные и указатели из другого узла
        n_data = other.n_data;
        n_left = other.n_left;
        n_right = other.n_right;
        // Очищаем указатели в перемещаемом узле
        other.n_left = nullptr;
        other.n_right = nullptr;
        return *this;
    }
};

// Рекурсивная функция подсчета узлов (препорядковый обход). N | N | N
template<typename T>
// countNodesRecursive : функция рекурсивно подсчитывает количество узлов в бинарном дереве.
// Начав с заданного узла, она возвращает число, равное количеству узлов в его левом поддереве
// плюс количество узлов в правом поддереве, плюс один (сам узел).
size_t countNodesRecursive(const TreeNode<T>* node) {
    if (node == nullptr) return 0; // если узел пустой, возвращаем 0
    //Возвращаем количество узлов слева и справа + сам узел
    return 1 + countNodesRecursive(node->n_left) + countNodesRecursive(node->n_right);
}

// Добавить значение к узлу в виде нового узла. N | N | N
template<typename T>
// addNodeBST : функция добавляет новый узел в бинарное дерево поиска.
// Она сравнивает значение, которое надо вставить, с данными текущего узла.
// Если значение меньше, то оно добавляется в левое поддерево.
// Если там уже есть узел, то функция рекурсивно вызывается для этого узла.
// Если узла нет, создается новый узел.
// То же самое делается и для правого поддерева, если значение больше или равно данному текущего узла.
static void addNodeBST(TreeNode<T>* node, T value) {
    if (value < node->n_data) { // если значение меньше текущего узла
        if (node->n_left) { // если левый дочерний узел существует, добавляем рекурсивно туда
            addNodeBST(node->n_left, value);
        }
        else
        { // иначе создаем новый узел слева
            node->n_left = new TreeNode<T>(value);
        }
    }
    else
    { // если значение больше или равно текущему узлу
        if (node->n_right) { // если правый дочерний узел существует, добавляем рекурсивно туда
            addNodeBST(node->n_right, value);
        }
        else
        { // иначе создаем новый узел справа
            node->n_right = new TreeNode<T>(value);
        }
    }
}

// Рекурсивная функция копирования из бинарного поиска дерева одного (node)
// в корень бинарного поиска дерева другого (root)
template<typename T>
// copyRecursive : функция рекурсивно создает копию данного дерева.
// Она копирует узел за узлом, начиная с корня, и возвращает указатель на корень нового дерева.
TreeNode<T>* copyRecursive(TreeNode<T>* root) {
    if (root == nullptr) return nullptr; // если узел пустой, возвращаем nullptr
    TreeNode<T>* newNode = new TreeNode<T>(root->n_data); // создаем новый узел, копируя текущий
    // рекурсивно копируем левое и правое поддеревья
    newNode->n_left = copyRecursive(root->n_left);
    newNode->n_right = copyRecursive(root->n_right);
    return newNode;
}

// Рекурсивная функция определения глубины (инордерный обход).
template<typename T>
// getDepthRecursive : функция вычисляет глубину дерева, используя инордерный обход.
// Глубина пустого дерева равна -1. 
// Глубина дерева — это 1 плюс максимальная глубина между левым и правым поддеревьями.
int getDepthRecursive(const TreeNode<T>* node) {
    if (node == nullptr) return -1; // пустое дерево имеет глубину -1
    int leftDepth = getDepthRecursive(node->n_left); // Рекурсивный вызов для левого поддерева
    int rightDepth = getDepthRecursive(node->n_right); // Рекурсивный вызов для правого поддерева
    // Возвращаем 1 плюс максимальная глубина левого и правого поддеревьев
    return 1 + max(leftDepth, rightDepth); 
}

// Рекурсивный вывод дерева.
template<typename T>
// printTreeRecursive : функция рекурсивно выводит дерево на экран.
// Она сначала печатает правое поддерево, затем текущий узел
// (с отступами, соответствующими его уровню в дереве), и затем левое поддерево. 
void printTreeRecursive(const TreeNode<T>* node, int level) {
    if (node == nullptr) return; // если узел пустой, ничего не делаем
    // Печатаем правое поддерево с увеличением уровня
    printTreeRecursive(node->n_right, level + 1);
    // Печать текущего узла. Число пропусков определяется уровнем
    for (int i = 0; i < level; i++) {
        cout << "    "; 
    }
    cout << node->n_data << endl; // Печатаем данные текущего узла
    // Печатаем левое поддерево с увеличением уровня
    printTreeRecursive(node->n_left, level + 1);
}

// Удалеяет дерево.
template<typename T>
// deleteTree : функция рекурсивно удаляет все узлы дерева, освобождая память.
void deleteTree(TreeNode<T>* node) {
    if (node) {
        deleteTree(node->n_left);  // Рекурсивно удаляем левое поддерево
        deleteTree(node->n_right); // Рекурсивно удаляем правое поддерево
        delete node; // Удаляем текущий узел
    }
}

// Вспомогательный метод для рекурсивного поиска узла. 
template<typename T>
// searchRecursive : функция рекурсивно ищет узел с заданным значением.
// Она сравнивает значение с данными узла и рекурсивно ищет в левом или правом поддереве,
// если значение не совпадает. Если значение найдено, возвращает указатель на найденный узел,
// иначе возвращает nullptr.
TreeNode<T>* searchRecursive(TreeNode<T>* node, const T& value) {
    if (node == nullptr) { return nullptr; } // Если узел пуст, возвращаем nullptr, значение не найдено.
    if (node->n_data == value) { return node; } // Значение найдено, возвращаем узел
    else if (value < node->n_data) {
        return searchRecursive(node->n_left, value); // Ищем в левом поддереве
    }
    else {
        return searchRecursive(node->n_right, value); // Ищем в правом поддереве
    }
}

template<typename T>
// preorder : Выполняет препорядковый обход (последовательность "узел, левый, правый").
// Если узел не нулевой, добавляет его данные в результат
// и рекурсивно повторяется для левого и правого поддерева.
void preorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    result.push_back(node->n_data);  // Добавляем данные текущего узла
    preorder(node->n_left, result);  // Рекурсивный вызов для левого поддерева
    preorder(node->n_right, result); // Рекурсивный вызов для правого поддерева
}

template<typename T>
// preorder1 : Выполняет препорядковый обход (последовательность "узел, правый, левый").
// Если узел не нулевой, добавляет его данные в результат
// и рекурсивно повторяется для правого и левого поддерева.
void preorder1(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    result.push_back(node->n_data);
    preorder1(node->n_right, result);
    preorder1(node->n_left, result);
}

// inorder : Выполняет инордерный обход (последовательность "левый, узел, правый").
// Если узел не нулевой, рекурсивно обрабатывает левое поддерево, 
// добавляет текущий узел в результат, затем обрабатывает правое поддерево.
template<typename T>
void inorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    inorder(node->n_left, result);
    result.push_back(node->n_data);
    inorder(node->n_right, result);
}

// inorder1 : Выполняет инордерный обход (последовательность "правый, узел, левый").
// Если узел не нулевой, рекурсивно обрабатывает правое поддерево, 
// добавляет текущий узел в результат, затем обрабатывает левое поддерево.
template<typename T>
void inorder1(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    inorder1(node->n_right, result);
    result.push_back(node->n_data);
    inorder1(node->n_left, result);
}

template<typename T>
// postorder : Выполняет постпорядковый обход (последовательность "левый, правый, узел").
// Рекурсивно проходит левое, затем правое поддерево и добавляет текущий узел в результат.
void postorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    postorder(node->n_left, result);
    postorder(node->n_right, result);
    result.push_back(node->n_data);
}

template<typename T>
// postorder1 : Выполняет постпорядковый обход (последовательность "правый, левый, узел").
// Рекурсивно проходит правое, затем левое поддерево и добавляет текущий узел в результат.
void postorder1(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    postorder1(node->n_right, result);
    postorder1(node->n_left, result);
    result.push_back(node->n_data);
}

template<typename T>
// inorderStack : функция использует стек для хранения узлов в последовательности,
// обратной инордерному обходу. Поначалу рекурсивно обрабатывает правое поддерево,
// затем добавляет текущий узел в стек, после чего рекурсивно обрабатывает левое поддерево.
void inorderStack(TreeNode<T>* node, stack<TreeNode<T>*>& stack)
{
    if (node == nullptr) return;
    inorderStack(node->n_right, stack);
    stack.push(node);
    inorderStack(node->n_left, stack);
}

template<typename T>
// applyFunction: Применяет указанную функцию к данным каждого узла в порядке прямого обхода (NLR). 
void applyFunction(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    func(node->n_data);
    applyFunction(node->n_left, func);
    applyFunction(node->n_right, func);
}

template<typename T>
// applyPreorder: Подобно applyFunction, применяет функцию в порядке препорядкового обхода (NLR).
void applyPreorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    func(node->n_data);
    applyPreorder(node->n_left, func);
    applyPreorder(node->n_right, func);
}

template<typename T>
// applyInorder: Применяет функцию в порядке инордерного обхода (LNR).
void applyInorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    applyInorder(node->n_left, func);
    func(node->n_data);
    applyInorder(node->n_right, func);
}

template<typename T>
// applyPostorder: Применяет функцию в порядке постпорядкового обхода (LRN).
void applyPostorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    applyPostorder(node->n_left, func);
    applyPostorder(node->n_right, func);
    func(node->n_data);
}

template<typename T>
// Поиск следующего наибольшего элемента, возвращает узел, иначе нуллптр. 
TreeNode<T>* searchSucc(TreeNode<T>* current, const T& value) {
    TreeNode<T>* prev = nullptr;
    // Найдем узел с заданным значением и сохраним путь в переменную
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
        return nullptr; // Значение не найдено
    }
    // Если у текущего узла есть правый потомок, то следующий наибольший элемент
    // - это наименьший элемент в правом поддереве
    if (current->n_right != nullptr) {
        current = current->n_right;
        while (current->n_left != nullptr) {
            current = current->n_left;
        }
        return current;
    }
    // Иначе ищем следующий наибольший элемент, поднимаясь вверх по дереву
    if (prev)
        return prev;
    else
        return nullptr;
}

// Процедура обхода дерева с помощью стека. LNR
template<typename T>
void inOrderTraversalIterative(TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode<T>*> stack;
    TreeNode<T>* current = root;
    while (!stack.empty() || current != nullptr) {
        // Идем вниз по левому поддереву, сохраняя узлы в стеке
        while (current != nullptr) {
            stack.push(current);
            current = current->n_left;
        }
        // Берем верхний узел из стека, выводим его и переходим к правому поддереву
        current = stack.top();
        stack.pop();
        cout << current->n_data << " ";
        current = current->n_right;
    }
}

// Процедура обхода дерева с помощью стека. NLR
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

// Процедура обхода дерева с помощью стека. LRN
template<typename T>
void postOrderTraversalIterative(TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode<T>*> stack;
    TreeNode<T>* current = root;
    TreeNode<T>* lastVisited = nullptr;
    //Если текущий элемент не пустой и стек не пуст -- 
    while (!stack.empty() || current != nullptr) {
        // заносим левый узел в стек
        if (current != nullptr) {
            stack.push(current);
            current = current->n_left;
        }
        // переносим элемент дерева в стек
        else {
            TreeNode<T>* peekNode = stack.top();
            // переход в правый узел
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
// Удаление узла рекурсивно. Не функция, так как тут используется.
// Передается адрес узла по ссылке 
void deleteNodeRecursive(TreeNode<T>** node, const T& value) {
    if (*node == nullptr) {
        return; // Узел не найден
    }
    // Если значение меньше, чем значение в текущем узле, идем влево
    if (value < (*node)->n_data) {
        deleteNodeRecursive(&(*node)->n_left, value);
    }
    // Если значение больше, чем значение в текущем узле, идем вправо
    else if (value > (*node)->n_data) {
        deleteNodeRecursive(&(*node)->n_right, value);
    }
    // Найден узел для удаления
    else {
        TreeNode<T>* nodeToDelete = *node;
        // Если у узла нет дочерних узлов, просто удаляем его
        if ((*node)->n_left == nullptr && (*node)->n_right == nullptr) {
            *node = nullptr;
            delete nodeToDelete;
        }
        // Если у узла есть только левый дочерний узел, присоединяем его к родителю
        else if ((*node)->n_left != nullptr && (*node)->n_right == nullptr) {
            *node = (*node)->n_left;
            nodeToDelete->n_left = nullptr;
            delete nodeToDelete;
        }
        // Если у узла есть только правый дочерний узел, присоединяем его к родителю
        else if ((*node)->n_left == nullptr && (*node)->n_right != nullptr) {
            *node = (*node)->n_right;
            nodeToDelete->n_right = nullptr;
            delete nodeToDelete;
        }
        // Если у узла есть оба дочерних узла, ищем следующий наибольший элемент и меняем местами
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

    // Копировать древо из other
    void copy(BinarySearchTree& other)
    {
        clear();
        root = copyRecursive(other.get_root());
    }

    // Очистка древа
    void clear() {
        deleteTree(root);   // Очищаем дерево
        root = nullptr; // Обнуляем корень дерева
    }

    // Применить функцию к элементам древа
    void apply(const function<void(T&)>& func) {
        applyFunction(root, func);
    }

    // Добавить значение дереву. 
    void insert(const T& value) {
        if (!root) {
            root = new TreeNode<T>(value);
        }
        else
        {
            addNodeBST(root, value);
        }
    }

    // Вывести значение узла на экран
    void printNode(TreeNode<T>* node) const {
        if (node) {
            cout << node->n_data << endl;
        }
        else {
            cout << "Пусто" << endl;
        }
    }

    // Создание массива на основе препорядкового обхода (NLR)
    vector<T> toArrayPreOrder() const {
        vector<T> result;
        preorder(root, result);
        return result;
    }

    // Создание массива на основе инордерного обхода (LNR). 
    vector<T> toArrayInOrder() const {
        vector<T> result;
        inorder(root, result);
        return result;
    }

    // Создание массива на основе постпорядкового обхода (LRN). 
    vector<T> toArrayPostOrder() const {
        vector<T> result;
        postorder(root, result);
        return result;
    }
    // Печать дерева NLR. 
    void printPreOrder() const {
        vector<T> result = toArrayPreOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Вывод содержимого узлов дерева в порядке LNR.
    void printInOrder() const {
        vector<T> result = toArrayInOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Вывод содержимого узлов дерева в порядке LRN. 
    void printPostOrder() const {
        vector<T> result = toArrayPostOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Функция печати дерева в виде дерева. 
    void printTree() const {
        printTreeRecursive(root, 0);
    }

    // Удаляет узел из дерева. 
    void remove(T value)
    {
        if (isEmpty())
        {
            throw out_of_range("Дерево пустое");
        }
        deleteNodeRecursive(&root, value);
    }

    // Функция определения глубины дерева. 
    int getDepth() const {
        return getDepthRecursive(root);
    }

    // Функция подсчета числа узлов. 
    size_t countNodes() const {
        return countNodesRecursive(root);
    }

    // Проверка на пустоту дерева
    bool isEmpty() const {
        if (root != nullptr)
            return false;
        else
            return true;
    }

    // Поиск следующего наибольшего элемента, возвращает значение, иначе бросает исключение 
    T succesor(const T& value) {
        if (isEmpty())
            throw std::out_of_range("Дерево пустое");
        TreeNode<T>* nextNode = searchSucc(root, value);
        if (nextNode == nullptr) {
            throw std::out_of_range("Значение не найдено в дереве");
        }
        return nextNode->n_data;
    }

    // Метод для поиска узла по значению 
    TreeNode<T>* search(const T& value) const {
        return searchRecursive(root, value); // Запускаем поиск с корневого узла
    }

    // Получить указатель на корень
    TreeNode<T>* get_root() const {
        return root;
    }

    // Функция тестирования
    static void runTests() {
        // Дерево для копий
        BinarySearchTree<int> copyTree;

        // Тест для обычного дерева
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
        //Проверка работы перехода по дереву и получения значений
        vector<int> inorderbst = bst.toArrayInOrder();
        int i = 0;
        for (int value : bst) {

            assert(value, inorderbst[i]);
            i++;
        }
        //Проверка работы неравенства итераторов
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
            // Перехват исключения out_of_range
            cerr << "Ошибка перехвачена" << e.what() << endl;
        }

        //Используя не корневой узел, найденный через поиск мы можем применять функции к поддеревьям
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

        // Тест для вырожденного дерева (слева)
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
            // Перехват исключения out_of_range
            cerr << "Ошибка перехвачена" << e.what() << endl;
        }

        //Используя не корневой узел, найденный через поиск мы можем применять функции к поддеревьям
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

        // Тест для вырожденного дерева (справа)
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
            // Перехват исключения out_of_range
            cerr << "Ошибка перехвачена" << e.what() << endl;
        }

        //Используя не корневой узел, найденный через поиск мы можем применять функции к поддеревьям
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

        // Тест для пустого дерева
        BinarySearchTree<int> emptyTree;
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);
        try {
            int successor = emptyTree.succesor(1);
        }
        catch (const out_of_range& e) {
            // Перехват исключения out_of_range
            cerr << "Ошибка перехвачена" << e.what() << endl;
        }

        copyTree.copy(emptyTree);
        assert(copyTree.toArrayInOrder() == emptyTree.toArrayInOrder());

        try {
            emptyTree.remove(10);
        }
        catch (const exception e) {
            // Перехват исключения out_of_range
            cerr << "Ошибка перехвачена" << e.what() << endl;
        }
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);

        assert(emptyTree.search(5) == nullptr);

        emptyTree.clear();
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);

        // Тест для дерева из одного узла
        BinarySearchTree<int> singleNodeTree;
        singleNodeTree.insert(10);
        assert(singleNodeTree.countNodes() == 1);
        assert(singleNodeTree.getDepth() == 0);
        try {
            int successor = singleNodeTree.succesor(11);
        }
        catch (const out_of_range& e) {
            // Перехват исключения out_of_range
            cerr << "Ошибка перехвачена" << e.what() << endl;
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
        // Тест для создания массива на основе обхода
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

        // Тест для применения функции к узлам дерева
        arrayTree.apply([](int& val) { val *= 2; });

        vector<int> updatedInorderArray = arrayTree.toArrayInOrder();
        vector<int> expectedUpdatedInorderArray = { 4, 10, 14, 20, 24, 30, 40 };
        assert(updatedInorderArray == expectedUpdatedInorderArray);


        // Тест для применения функции к узлам дерева
        arrayTree.apply([](int& val) { val *= 2; });
        // Тест для вырожденного дерева

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

        // Тест для пустого дерева
        emptyTree.apply([](int& val) { val *= 2; });

        vector<int> emptyArray = emptyTree.toArrayInOrder();
        vector<int> expectedEmptyArray = {};
        assert(emptyArray == expectedEmptyArray);

        emptyTree.clear();

        // Тест для дерева с одним узлом
        singleNodeTree.insert(10);

        singleNodeTree.apply([](int& val) { val *= 2; });

        vector<int> singleNodeArray = singleNodeTree.toArrayInOrder();
        vector<int> expectedSingleNodeArray = { 20 };
        assert(singleNodeArray == expectedSingleNodeArray);

        singleNodeTree.clear();
        cout << "Все тесты пройдены!" << endl;
    }
};


