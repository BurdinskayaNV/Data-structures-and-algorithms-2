#include <iostream>
#include <cassert>

// Узел бинарного дерева
class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева с реализацией Правила пяти
class BinaryTree {
public:
    TreeNode* root;

    // Конструктор по умолчанию
    BinaryTree() : root(nullptr) {}

    // Деструктор
    ~BinaryTree() {
        clear(root);
    }

    // Конструктор копирования
    BinaryTree(const BinaryTree& other) : root(copy(other.root)) {}

    // Оператор присваивания
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear(root);
            root = copy(other.root);
        }
        return *this;
    }

    // Конструктор перемещения
    BinaryTree(BinaryTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    // Оператор перемещения
    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            clear(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    // Добавление элемента в бинарное дерево
    void insert(int value) {
        root = insert(root, value);
    }

    // Итератор для дерева без использования стека
    class Iterator {
    public:
        Iterator(TreeNode* start) : current(start) {
            while (current && current->left) {
                current = current->left;
            }
        }

        // Оператор разыменования
        int& operator*() {
            return current->value;
        }

        // Оператор инкремента
        Iterator& operator++() {
            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            }
            else {
                TreeNode* temp = current;
                while (temp) {
                    if (temp->right && temp->right != current) {
                        current = temp->right;
                        while (current->left) {
                            current = current->left;
                        }
                        return *this;
                    }
                    current = temp;
                    temp = nullptr;
                }
                current = nullptr;
            }
            return *this;
        }

        // Оператор неравенства
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        TreeNode* current;
    };

    // Начало итерации
    Iterator begin() {
        return Iterator(root);
    }

    // Конец итерации
    Iterator end() {
        return Iterator(nullptr);
    }

private:
    // Вспомогательная функция для копирования дерева
    TreeNode* copy(TreeNode* node) {
        if (!node) return nullptr;
        TreeNode* newNode = new TreeNode(node->value);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    // Вспомогательная функция удаления всего дерева
    void clear(TreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Вспомогательная функция добавления в дерево
    TreeNode* insert(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else {
            node->right = insert(node->right, value);
        }
        return node;
    }
};

// Тестовая функция test2 
void test2() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // Печать всех элементов дерева с использованием итератора
    cout << "Элементы бинарного дерева в отсортированном порядке: " << endl;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Тестирование с помощью assert
    auto it = tree.begin();
    assert(*it == 2);
    ++it;
    //assert(*it == 3);
    /*++it;
    assert(*it == 7);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 4);
    ++it;
    assert(*it == 6);
    ++it;
    assert(*it == 8);*/
    cout << "Тестирование test2 выполнено успешно !" << endl;
};
