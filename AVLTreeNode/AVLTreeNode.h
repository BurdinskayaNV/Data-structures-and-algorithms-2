#pragma once
#include "BinarySearchTree.h"
// Шаблонный класс AVLTreeNode, который наследует другой класс TreeNode.
// Класс AVLTreeNode используется для представления узла AVL-дерева,
// которое является самобалансирующимся двоичным деревом поиска.
// Узлы AVL-дерева дополнительно хранят фактор баланса, который помогает поддерживать
// сбалансированность дерева после каждой операции вставки или удаления.
// Класс AVLTreeNode наследуется от TreeNode и имеет дополнительное поле для коэффициента баланса.
template<typename T>
class AVLTreeNode : public TreeNode<T> {
public:
    // Конструктор по умолчанию, инициализирует базовый класс TreeNode и устанавливает фактор баланса в 0.
    AVLTreeNode() : TreeNode<T>(), balanceFactor(0) {}
    // Конструктор, который инициализирует узел с данными и устанавливает фактор баланса в 0.
    AVLTreeNode(const T& data) : TreeNode<T>(data), balanceFactor(0) {}
    // Конструктор, который инициализирует узел с данными вместе с указателями на левого и правого потомков и устанавливает фактор баланса в 0.
    AVLTreeNode(const T& data, TreeNode<T>* getLeft(), TreeNode<T>* getRight()) : TreeNode<T>(data, getLeft(), getRight()), balanceFactor(0) {}
    // Деструктор.
    ~AVLTreeNode() {}
    // Конструктор копирования, который копирует другой узел и его фактор баланса.
    AVLTreeNode(const AVLTreeNode& other) : TreeNode<T>(other), balanceFactor(other.balanceFactor) {}
    // Конструктор перемещения, который передаёт другой узел и его фактор баланса.
    AVLTreeNode(AVLTreeNode&& other) : TreeNode<T>(move(other)), balanceFactor(other.balanceFactor) {}
    // Оператор копирующего присваивания, копирующий данные и фактор баланса от другого узла.
    AVLTreeNode& operator=(const AVLTreeNode& other) {
        TreeNode<T>::operator=(other);
        balanceFactor = other.balanceFactor;
        return *this;
    }
    // Оператор перемещающего присваивания, перемещающий данные и фактор баланса от другого узла.
    AVLTreeNode& operator=(AVLTreeNode&& other) {
        TreeNode<T>::operator=(move(other));
        balanceFactor = other.balanceFactor;
        return *this;
    }

    // Методы доступа(геттеры) для левого и правого потомков :
    // Преобразователь указателя на (на левый) TreeNode в указатель на AVLTreeNode
    AVLTreeNode<T>* getLeft() { return static_cast<AVLTreeNode<T>*>(this->n_left); }
    // Преобразователь указателя на (на правый) TreeNode в указатель на AVLTreeNode
    AVLTreeNode<T>* getRight() { return static_cast<AVLTreeNode<T>*>(this->n_right); }

    // Константные версии геттеров.
    // Преобразователь указателя на (на левый) TreeNode в указатель на AVLTreeNode
    const AVLTreeNode<T>* getLeft() const { return static_cast<const AVLTreeNode<T>*>(this->n_left); }
    // Преобразователь указателя на (на правый) TreeNode в указатель на AVLTreeNode
    const AVLTreeNode<T>* getRight() const { return static_cast<const AVLTreeNode<T>*>(this->n_right); }

    // Коэффициент баланса узла. Поле, которое хранит фактор баланса для узла.
    short int balanceFactor;
};

// Класс AVLTree представляет собой само сбалансированное бинарное дерево поиска.
template<typename T>
class AVLTree {
private:
    // Указатель на корень дерева.
    AVLTreeNode<T>* root;

    // Функция для обновления коэффициента баланса узла.
    // Обновляет балансировочный фактор для текущего узла.
    // Балансировочный фактор узла вычисляется как разница в высоте его левого и правого поддеревьев.
    void updateBalanceFactor(AVLTreeNode<T>* node) {
        if (node == nullptr) { return; }
        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());
        node->balanceFactor = leftHeight - rightHeight;
    }

    // Функция для получения высоты узла.
    // Возвращает высоту дерева или поддерева с данным корнем.
    int getHeight(AVLTreeNode<T>* node) {
        if (node == nullptr) { return 0; }
        return 1 + max(getHeight(node->getLeft()), getHeight(node->getRight()));
    }

    // rotateRight и rotateLeft: Выполняют правый и левый повороты соответственно.
    // Эти операции необходимы для поддержания сбалансированности дерева.
    // Функция для правого поворота.
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getLeft(); // левый дочерний узел становится новым корнем
        node->n_left = temp->getRight(); // перенос поддерева
        temp->n_right = node; // текущий узел становится правым потомком нового корня
        updateBalanceFactor(node); // обновление балансировочных факторов
        updateBalanceFactor(temp); // обновление балансировочных факторов нового кореня
        return temp; // возвращает новый корень после вращения
    }
    // Функция для левого поворота.
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getRight(); // правый дочерний узел становится новым корнем
        node->n_right = temp->getLeft(); // перенос поддерева
        temp->n_left = node; // текущий узел становится левым потомком нового корня
        updateBalanceFactor(node); // обновление балансировочных факторов
        updateBalanceFactor(temp); // обновление балансировочных факторов нового кореня
        return temp; // возвращает новый корень после вращения
    }

    // balanceTree: Проверяет балансировочный фактор и выполняет соответствующие повороты, если дерево несбалансировано.
    // Функция для балансировки дерева.
    AVLTreeNode<T>* balanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) { return nullptr; }
        updateBalanceFactor(node);
        if (node->balanceFactor > 1) { // если левое поддерево тяжелее
            if (getHeight(node->getLeft()->getLeft()) >= getHeight(node->getLeft()->getRight())) {
                node = rotateRight(node); // Одинарный правый поворот
            }
            else {
                //Большой правый поворот
                node->n_left = rotateLeft(node->getLeft()); // левый правый поворот
                node = rotateRight(node);
            }
        }
        else if (node->balanceFactor < -1) { // правое поддерево тяжелее
            if (getHeight(node->getRight()->getRight()) >= getHeight(node->getRight()->getLeft())) {
                node = rotateLeft(node); //Одинарный левый поворот
            }
            else {
                //Большой левый поворот
                node->n_right = rotateRight(node->getRight()); // правый левый поворот
                node = rotateLeft(node);
            }
        }
        return node; // возвращает сбалансированное корневое поддерево
    }

    // Функция для вставки нового узла в дерево.
    // insertNode: Реализует вставку элемента в AVL-дерево. После вставки вызывается balanceTree для поддержания сбалансированности.
    AVLTreeNode<T>* insertNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) { return new AVLTreeNode<T>(data); }
        if (data < node->n_data) {
            node->n_left = insertNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = insertNode(node->getRight(), data);
        }
        return balanceTree(node); // балансировка после вставки
    }

    // Функция для удаления узла из дерева.
    // deleteNode: Удаляет элемент из AVL-дерева и перераспределяет его узлы, если это необходимо, для поддержания сбалансированной структуры.
    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) { return nullptr; }
        if (data < node->n_data) {
            node->n_left = deleteNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = deleteNode(node->getRight(), data);
        }
        else {
            if (node->getLeft() == nullptr) { // если нет левого потомка
                AVLTreeNode<T>* temp = node->getRight(); // замена правым потомком
                delete node;
                return temp;
            }
            else if (node->getRight() == nullptr) { // если нет правого потомка
                AVLTreeNode<T>* temp = node->getLeft(); // замена левым потомком
                delete node;
                return temp;
            }
            AVLTreeNode<T>* temp = node->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft(); // находим минимальный узел в правом поддереве
            }
            node->n_data = temp->n_data; // копирование данных
            node->n_right = deleteNode(node->getRight(), temp->n_data); // удаление узла
        }
        return balanceTree(node); // балансировка после удаления
    }
public:
    // Конструктор по умолчанию.
    // конструктор, инициализирующий корень root как nullptr.
    AVLTree() : root(nullptr) {}

    // Деструктор.
    // вызывает метод clear для очистки дерева перед удалением объекта.
    ~AVLTree() { clear(); }

    // Функция для вставки элемента в дерево.
    // Метод insert: метод для вставки нового элемента в дерево.
    // Он вызывает приватный метод insertNode, который выполняет вставку
    // и балансировку узлов.
    void insert(const T& data) {
        root = insertNode(root, data);
    }

    // Функция для удаления элемента из дерева.
    // Метод remove: метод для удаления элемента из дерева,
    // вызывающий приватный метод deleteNode.
    void remove(const T& data) {
        root = deleteNode(root, data);
    }

    // Метод для вывода дерева в виде строки.
    // Метод toString: метод для преобразования дерева в строку.
    // Использует вспомогательный метод toStringHelper.
    // template<typename T>
    string toString() {
        string result = "";
        toStringHelper(root, result);
        return result;
    }

    // Метод для вывода дерева в виде дерева.
    // Метод printTree: метод для печати дерева на экран.
    // Он вызывает printTreeHelper для отображения дерева начиная с корневого узла.
    void printTree() {
        if (root) printTreeHelper(root, 0);
    }

    // Метод для поиска элемента в дереве.
    // Метод find: метод поиска узла с заданным значением. Использует метод findHelper.
    AVLTreeNode<T>* find(const T& data) {
        return findHelper(root, data);
    }

    // Метод поиска узла в дереве
    // Метод findNode: метод для поиска узла и возвращения указателя на него.
    // Возвращает nullptr, если узел не найден.
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
              return current; // Найдено
          }
        }
        return nullptr; // Не найдено
    }

    // Метод для доступа к коэффициенту баланса узла по узлу.
    // Метод getBalanceFactorNode: возвращает балансировочный фактор для определенного узла.
    int getBalanceFactorNode(AVLTreeNode<T>* node) {
        if (node == nullptr) { return 0; }
        return node->balanceFactor;
    }

    // Метод getBalanceFactor: возвращает балансировочный фактор для узла
    // с заданным значением или генерирует исключение out_of_range, если узел не найден.
    int getBalanceFactor(T val) {
        AVLTreeNode<T>* node = find(val);
        if (node) { return getBalanceFactorNode(node); }
        else
            throw out_of_range("Значение не найдено");
    }

    // класс Iterator, предназначенный для последовательного обхода AVL-дерева.
    // Итератор использует стек для сохранения состояния обхода, осуществляя итерацию по дереву в порядке "слева-направо".
    // В конечном итоге итератор реализует паттерн обхода "in-order", позволяя получить отсортированный набор данных из дерева.
    class Iterator {
    private:
        AVLTreeNode<T>* root; // Корневой узел
        stack<AVLTreeNode<T>*> nodeStack; // Стек для обхода узлов
    public:
        // Конструктор итератора, инициализирует начальный узел
        Iterator(AVLTreeNode<T>* n_root) {
            root = n_root;
            pushLeftBranch(n_root);
        }
        // Оператор проверки на неравенства
        bool operator!=(const Iterator& other) const {
            return !(hasNext() == false && other.hasNext() == false);
        }
        // Оператор проверки на равенства
        bool operator==(const Iterator& other) const {
            return nodeStack.empty() == other.nodeStack.empty();
        }
        // Проверка есть ли следующий элемент
        bool hasNext() const {
            return !nodeStack.empty();
        }
        // Оператор разыменования для доступа к данным текущего узла
        T& operator*() const {
            return nodeStack.top()->n_data;
        }
        // Возвращает ссылку на данные текущего узла
        T& data() {
            return nodeStack.top()->n_data;
        }
        // Оператор инкремента, перемещается к следующему узлу
        Iterator& operator++() {
            return next();
        }
        // Сбрасывает итератор в начало дерева
        void reset() {
            while (!nodeStack.empty())
                nodeStack.pop();
            pushLeftBranch(root);
        }
        // Переход к следующему узлу
        Iterator& next() {
            AVLTreeNode<T>* currentNode;
            if (!hasNext()) {
                throw out_of_range("В итераторе больше нет элементов");
            }
            currentNode = nodeStack.top();
            nodeStack.pop();
            pushLeftBranch(currentNode->getRight());
            return *this;
        }
    private:
        // Вспомогательный метод для добавления всех левых дочерних узлов в стек
        void pushLeftBranch(AVLTreeNode<T>* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = node->getLeft();
            }
        }
    };

    // возвращает итератор на начало дерева
    Iterator begin() const {
        return Iterator(root);
    };
    // Переносит итератор на конец дерева
    Iterator end() const {
        return Iterator(nullptr);
    };
    // Метод для очистки AVL-дерева
    void clear() {
        if (root)
        {
            clearNode(root);
            root = nullptr;
        }
    };

    // функция тестирования для AVL-дерева
    // - Вставка элементов: Код систематически вставляет значения в дерево и проверяет, корректно ли они находятся с помощью функции find().
    // - Удаление элементов: Код также проверяет, что элементы корректно удаляются из дерева.
    // - Итерация: Используется итератор для прохода по всем элементам дерева, чтобы убедиться,
    //   что они в порядке(в возрастающем порядке, как должно быть в бинарном дереве поиска).
    // - Балансировка: Для каждого элемента дерева проверяется баланс, чтобы убедиться, что дерево AVL остается сбалансированным.
    // - Очистка дерева: Проверяется, что после очистки уже вставленные значения не найдены в дереве.
    static void AVLTreeTest() {
        AVLTree<int> tree;

        // Тестирование вставки в пустое дерево
        tree.insert(10);
        assert(tree.find(10) != nullptr); // Должен найти 10
        assert(tree.find(20) == nullptr); // Не должен найти 20

        // Тестирование вставки нескольких элементов
        tree.insert(20);
        tree.insert(5);
        tree.insert(15);
        tree.printTree();
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        assert(tree.find(5) != nullptr);  // Должен найти 5
        assert(tree.find(15) != nullptr); // Должен найти 15
        assert(tree.find(25) == nullptr); // Не должен найти 25

        // Тестирование удаления элемента
        tree.remove(20);
        assert(tree.find(20) == nullptr); // 20 должен быть удален

        // Тестирование удаления корня
        tree.remove(10);
        assert(tree.find(10) == nullptr); // 10 должен быть удален

        // Тестирование удаления элемента, которого нет
        tree.remove(100); // Ничего не произойдет, дерево остается корректным

        // Тестирование итератора
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
        assert(it != tree.end()); // Должен иметь хотя бы один элемент
        assert(*it == 3);         // Первый элемент должен быть 3
        ++it;
        assert(*it == 5);         // Второй элемент должен быть 5
        ++it;
        assert(*it == 7);         // Третий элемент должен быть 7
        ++it;
        assert(*it == 8);         // Четвертый элемент должен быть 8
        ++it;
        assert(*it == 15);         // Четвертый элемент должен быть 
        ++it;
        assert(it == tree.end()); // Достигнуть конца
        cout << endl;
        cout << "----------------------------" << endl;
        cout << endl;
        // Тестирование функции очистки дерева
        tree.clear();
        assert(tree.find(5) == nullptr);  // Все элементы должны быть удалены
        assert(tree.begin() == tree.end()); // Итератор должен быть пустым

        // Тестирование поворотов дерева
        size_t i;
        // Поворот право право (малый правый поворот)
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
            assert(abs(tree.getBalanceFactor(value)) < 2); // tree.getBalanceFactor(value) по модулю < 2
            i++;
        }
        tree.clear();

        // Поворот лево лево (малый левый поворот)
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
            assert(abs(tree.getBalanceFactor(value)) < 2); // tree.getBalanceFactor(value) по модулю < 2
            i++;
        }
        tree.clear();

        // Поворот лево право
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
            assert(abs(tree.getBalanceFactor(value)) < 2); // tree.getBalanceFactor(value) по модулю < 2
            i++;
        }
        tree.clear();

        // Поворот право лево
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
        cout << "Все тесты прошли успешно !!!" << endl;
        cout << "----------------------------" << endl;
        cout << endl;
    }
};

// Вспомогательный метод для поиска элемента в дереве.
// findHelper: Эта функция ищет узел с указанными данными в AVL-дереве.
template<typename T>
AVLTreeNode<T>* findHelper(AVLTreeNode<T>* node, const T& data) {
    // Если текущий узел равен nullptr, это означает, что искомый элемент отсутствует, и функция возвращает nullptr.
    if (node == nullptr) { return nullptr; } 
    // Если данные меньше данных текущего узла (node->n_data), поиск продолжается в левом поддереве.
    if (data < node->n_data) {
        return findHelper(node->getLeft(), data);
    }
    // Если данные больше, то в правом поддереве.
    else if (data > node->n_data) {
        return findHelper(node->getRight(), data);
    }
    // Если нашли совпадение, возвращается текущий узел.
    else {
        return node;
    }
};

// Функция для уничтожения дерева.
// функция рекурсивно удаляет все узлы дерева
template<typename T>
void clearNode(AVLTreeNode<T>* node) {
    // Если текущий узел равен nullptr, ничего не делается.
    if (node == nullptr) { return; }
    // Сначала функция рекурсивно удаляет левое и правое поддерево.
    clearNode(node->getLeft());
    clearNode(node->getRight());
    // Затем удаляет сам текущий узел
    delete node;
};

// Вспомогательный метод для вывода дерева в виде дерева.
// printTreeHelper: Эта функция рекурсивно печатает дерево в консоль с отступами,
// которые показывают уровень вложенности узлов.
template<typename T>
void printTreeHelper(AVLTreeNode<T>* node, int level) {
    // Если текущий узел равен nullptr, ничего не делается.
    if (node == nullptr) { return; }
    // Функция сначала рекурсивно обращается к правому поддереву, увеличивая уровень.
    printTreeHelper(node->getRight(), level + 1);
    // Затем выводит текущие данные узла с отступами.
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    // Печатаем данные узла
    cout << node->n_data << endl;
    // После этого обрабатывает левое поддерево.
    printTreeHelper(node->getLeft(), level + 1);
};

// Вспомогательный метод для вывода дерева в виде строки.
// toStringHelper: Эта функция преобразует дерево в строку,
// представляющую обход в симметричном порядке (in-order traversal).
template<typename T>
void toStringHelper(AVLTreeNode<T>* node, std::string& result) {
    // Если текущий узел равен nullptr, ничего не делается.
    if (node == nullptr) { return; }
    // Сначала рекурсивно добавляется информация из левого поддерева.
    toStringHelper(node->getLeft(), result);
    // Затем добавляются данные текущего узла в строку результата.
    result += to_string(node->n_data) + " ";
    // После чего обрабатывается правое поддерево.
    toStringHelper(node->getRight(), result);
};
