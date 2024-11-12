/// Бурдинская Наталья ВМК-22
/// Date - 03.09.2024
#pragma once
#include "ClassTreeNode.h"
#include "detours.h"

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

    // *******************************************************
    // removeRecursively: Рекурсивная функция удаления узла************************************
    shared_ptr<TreeNode<T>> removeRecursively(shared_ptr<TreeNode<T>> node, T val) {
       if (!node) return nullptr;

       if (val < node->value) {
           node->left = removeRecursively(node->left, val);
       }
       else if (val > node->value) {
           node->right = removeRecursively(node->right, val);
       }
       else {
           // Узел найден - значит =
           if (!node->left) return move(node->right);
           if (!node->right) return move(node->left);
           // move - двигать, это функция - своего рода конвертер между способами,
           // которыми компилятор учитывает значение выражения.
           // Move семантика позволяет переместить объект вместо его копирования
           // для увеличения производительности. 
           // Узел с двумя дочерними
           node->value = minValueNode(node->right)->value;
           node->right = removeRecursively(move(node->right), node->value);
       }
       return node;
    }

    // *******************************************************
    // removeRecursively: Рекурсивная функция удаления узла************************************
    shared_ptr<TreeNode<T>> removeRecursively1(shared_ptr<TreeNode<T>> node, T val) {
        if (!node) return nullptr;

        if (val < node->value) {
            node->left = removeRecursively1(node->left, val);
        }
        else if (val > node->value) {
            node->right = removeRecursively1(node->right, val);
        }
        else {
            // Узел найден - значит =
            if (!node->left) return move(node->right);
            if (!node->right) return move(node->left);
            // move - двигать, это функция - своего рода конвертер между способами,
            // которыми компилятор учитывает значение выражения.
            // Move семантика позволяет переместить объект вместо его копирования
            // для увеличения производительности. 
            // Узел с двумя дочерними
            node->value = minValueNode(node->left)->value;
            node->left = removeRecursively1(move(node->left), node->value);
        }
        return node;
    }

    // *******************************************************
    // minValueNode: Вспомогательная функция для нахождения узла с минимальным значением.
    shared_ptr<TreeNode<T>> minValueNode(shared_ptr<TreeNode<T>> node) {
        while (node && node->left) {
            node = node->left; // Перейдите влево, чтобы найти меньшее значение
        }
        return node;
    }

    // *******************************************************
    // находит следующий наибольший по величине узел по сравнению с заданным значением
    shared_ptr<TreeNode<T>> findNextGreaterRec(shared_ptr<TreeNode<T>> node, T val) {
        shared_ptr<TreeNode<T>> successor = nullptr;
        while (node) {
            if (val < node->value) {
                successor = node;
                node = node->left; // Перейдите влево, чтобы найти меньшее значение
            }
            else {
                node = node->right; // Перейдите вправо, чтобы найти большее значение
            }
        }
        return successor;
    }

    // *********************************************************************
    // Функция для нахождения следующего наибольшего значения узла (основываясь на Inorder)
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
    // Альтернативный метод: нахождение следующего наибольшего значения
    // используя стек для эмуляции рекурсивного обхода
    // Класс std::stack<T> представляет стек - структуру данных, которая работает
    // по принципу LIFO (last-in first-out или "последний вошел — первым вышел") 
    // Для добавления в стек применяется функция push(), в которую передается добавляемый элемент.
    // получить только самый верхний элемент стека - для этого применяется функция top().
    // Для удаления элементов применяется функция pop(). Удаление производится в порядке, обратном добавлению.
    // Комбинируя эту функцию с функцией top() можно извлечь все элементы стека.
    shared_ptr<TreeNode<T>> findInorderSuccessorIterativeRec(shared_ptr<TreeNode<T>> node, T target) {
        stack<shared_ptr<TreeNode<T>>> nodeStack;
        auto currentNode = node;
        shared_ptr<TreeNode<T>> previous = nullptr;// предыдущий
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
    // Конструктор по умолчанию
    BinaryTree() : root(nullptr) {}
    // Конструктор с значением корня
    // value Значение корня
    BinaryTree(T value) {
        root = new TreeNode<T>(value);
    }
    // Деструктор, 
    // производится при помощи вспомогательной функции clearLRN или clearRLN
    ~BinaryTree() {
        clearLRN(root);
        //clearRLN(root);
    }
    // Метод insert : Рекурсивно вставляет значения в дерево, основываясь на сравнении.
    void insert(T value) {
        insert(root, value);
    }
    // ************************************************************
    // Метод remove : удаляет узел Node со значением val
    void remove(T val) {
        //root = removeRecursively(move(root), val);
        root = removeRecursively(move(root), val);
    }
    // ************************************************************
    // Метод findNextGreater : 
    // находит следующий по величине узел по сравнению с заданным значением.
    T findNextGreater(T val) {
        shared_ptr<TreeNode<T>> nextGreater = findNextGreaterRec(root, val);
        if (nextGreater) {
            return nextGreater->value;
        }
        else {
            throw runtime_error("Следующее наибольшее значение не найдено");
        }
    }
    // ************************************************************
    // Метод findInorderSuccessor : 
    // находит следующий по величине узел по сравнению с заданным значением.
    T findInorderSuccessor(T val) {
        shared_ptr<TreeNode<T>> nextGreater = findInorderSuccessorRec(root, val);
        if (nextGreater) {
            return nextGreater->value;
        }
        else {
            throw runtime_error("Следующее наибольшее значение не найдено");
        }
    }
    // ************************************************************
    // Метод findInorderSuccessorIterative : 
    // находит следующий по величине узел по сравнению с заданным значением.
    T findInorderSuccessorIterative(T val) {
        shared_ptr<TreeNode<T>> nextGreater = findInorderSuccessorIterativeRec(root, val);
        if (nextGreater) {
            return nextGreater->value;
        }
        else {
            throw runtime_error("Следующее наибольшее значение не найдено");
        }
    }
    // Метод display : 
    void display() {
        NLR(root);
        cout << endl;
    }
    // Метод clear : Освобождает память, занятую узлами дерева.
    void clear() {
        clearLRN(root);
        // clearRLN(root);
    }
    // Метод print : для визуального отображения дерева в консоли
    void print() {
        printTree(root, 0);
    }
    // Метод getRoot: возвращает дерево
    shared_ptr<TreeNode<T>> getRoot() {
        return root;
    }
    // Метод preorder: производит обход дерева через вектор
    vector<T> preorder() {
        vector<T> result;
        preOrder(root, result);
        return result;
    }
    // Метод inorder: производит обход дерева через вектор
    vector<T> inorder() {
        vector<T> result;
        inOrder(root, result);
        return result;
    }
    // Метод postorder: производит обход дерева через вектор
    vector<T> postorder() {
        vector<T> result;
        postOrder(root, result);
        return result;
    }
    // Метод preorder1: производит обход дерева через вектор
    vector<T> preorder1() {
        vector<T> result;
        preOrder1(root, result);
        return result;
    }
    // Метод inorder1: производит обход дерева через вектор
    vector<T> inorder1() {
        vector<T> result;
        inOrder1(root, result);
        return result;
    }
    // Метод postorder1: производит обход дерева через вектор
    vector<T> postorder1() {
        vector<T> result;
        postOrder1(root, result);
        return result;
    }
    // Метод search : Ищет узел с заданным значением.
    shared_ptr<TreeNode<T>> search(int data) {
        return searchRec(root, data);
    }
    // Метод depth : Ищет узел с заданным значением.
    shared_ptr<TreeNode<T>> depth() {
        return depth_root(root);
    }
};

// Функция для копирования дерева
// Функция copyTree: Рекурсивно создает копию бинарного дерева.
// Если узел равен nullptr, возвращает nullptr.
// Иначе создает новый узел и рекурсивно копирует его левого и правого детей.
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

// Функция для вывода дерева (в preOrder NLR прямой)
// preorder (сначала корень, затем левое поддерево, затем правое поддерево)
template <typename T>
void printTree1(shared_ptr<TreeNode<T>> node) {
    if (node == nullptr) {
        return;
    }
    cout << node->value << " ";
    printTree1(node->left);
    printTree1(node->right);
};

// Функция осуществляет поиск узла с определенным значением
template <typename T>
shared_ptr<TreeNode<T>> searchRec(shared_ptr<TreeNode<T>> node, T data) {
    // Если узел пустой или значение узла равно искомому, вернуть узел
    if (node == nullptr || node->value == data) {
        return node;
    }
    // Иначе, продолжить поиск в левом или правом поддереве
    if (data < node->value) {
        return searchRec(node->left, data); //
    }
    return searchRec(node->right, data); // 
};

// *********************************************************************
// Функции удаления узла из дерева
// Первый способ удаления узла: обход в глубину с удалением поддерева
// совмещение узла и всех потомков
template<typename T>
void deleteSubtree(shared_ptr<TreeNode<T>>& node, T val) {
    if (!node) return;
    if (node->value == val) {
        node = nullptr;  // Удаляем узел и поддерево
        return;
    }
    deleteSubtree(node->left, val);
    deleteSubtree(node->right, val);
};

// *********************************************************************
// Второй способ удаления узла: замена узла его потомком
// если узел имеет детей, они становятся детьми родительского узла.
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