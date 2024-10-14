// модуль с Примерами
#pragma once
#include "ClassBinTreeNode.h"
#include "functions.h"

/// функция Primer1 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
/// Примеры обходов, Глубина дерева, Количество узлов.
/// Копирование дерева и вывод в консоль.
void Primer1() {
	// объявление переменных - Пример создания бинарного дерева
	// shared_ptr умные указатели
	// make_shared() — это функция, имеющая преимущество при выделении памяти
	shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
	shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
	shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
	shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
	shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
	// постороение дерева
	a1->left = a2;
	a1->right = a3;
	a3->left = a4;
	a3->right = a5;
	// примеры обращения к элементам узла TreeNode
	cout << "------------------------------------" << endl;
	cout << "Примеры обращения к элементам узла TreeNode" << endl;
	cout << "a1->value  " << a1->value << endl;
	cout << "a1->left->value  " << a1->left->value << endl;
	cout << "a1->right->value  " << a1->right->value << endl;
	cout << "a3->left->value  " << a3->left->value << endl;
	cout << "a3->right->value  " << a3->right->value << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "Примеры обходов" << endl;
	cout << "NLR : "; NLR(a1); cout << endl;
	cout << "NRL : "; NRL(a1); cout << endl;
	cout << "RNL : "; RNL(a1); cout << endl;
	cout << "RLN : "; RLN(a1); cout << endl;
	cout << "LNR : "; LNR(a1); cout << endl;
	cout << "LRN : "; LRN(a1); cout << endl;
	cout << endl;
	cout << "Глубина дерева  " << depth_root(a1) << endl;
	cout << endl;
	cout << "Количество узлов  " << count_nodes_root(a1) << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "Структура дерева (визуального отображения в консоли): " << endl;
	printTree(a1, 0);
	cout << "------------------------------------" << endl;
	cout << "Структура дерева (вывода дерева в preOrder NRL прямой): " << endl;
	printTree1(a1);
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "Копирование дерева и вывод в консоль: " << endl;
	shared_ptr<TreeNode<int>> copiedTree = copyTree(a1);
	printTree(copiedTree, 0);
	cout << "------------------------------------" << endl;
	cout << endl;
	clearLRN(a1);
	clearLRN(copiedTree);
	//clearRLN(a1);
};

/// функция Primer2 : Создает бинарное дерево,
/// добавляет в него 7 узлов, и выводит их содержимое.
/// Поиск узла дерева и вывод в консоль.
void Primer2() {
	cout << "------------------------------------" << endl;
	cout << "Поиск узла дерева и вывод в консоль: " << endl;
	BinaryTree<int> tree;
	// Вставка узлов в бинарное дерево
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	// выводящий все элементы дерева в порядке inorder
	cout << "Индерный обход дерева : " << endl;
	tree.print();
	cout << "------------------------------------" << endl;
	cout << endl;
	int searchValue = 40; // Значение, которое мы ищем
	shared_ptr<TreeNode<int>> result = tree.search(searchValue);
	if (result != nullptr) {
		cout << "Узел с значением " << searchValue << " найден." << endl;
	}
	else {
		cout << "Узел с значением " << searchValue << " не найден." << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;
	tree.~BinaryTree();
};

/// функция Primer3 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
/// Функция для применения данной функции к каждому узлу дерева.
void Primer3() {
	// объявление переменных - Пример создания бинарного дерева
	// shared_ptr умные указатели
	// make_shared() — это функция, имеющая преимущество при выделении памяти
	shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
	shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
	shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
	shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
	shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
	// постороение дерева
	a1->left = a2;
	a1->right = a3;
	a3->left = a4;
	a3->right = a5;
	cout << "------------------------------------" << endl;
	cout << "Функция для применения данной функции к каждому узлу дерева: " << endl;
	// ****************************************************************************
	// Определяем функцию, которую мы применим к каждому узлу
	// Лямбда-выражение начинается с квадратных скобок.
	// Затем, как в обычной функции, в круглых скобках идет перечисление параметров - типы и их имена.
	// За списком параметров, как и в обычной функции, в фигурных скобках помещаются действия,
	// выполняемые лямбда-выражением.
	// переменная printNodeValue представляет именнованную лямбда-выражение 
	auto printNodeValue = [](int value) {
		// тело лямды
		//cout << value << " ";
		//cout << value + 1 << " ";
		cout << value * 5 << " ";
	};
	// Применяем функцию к каждому узлу дерева 6 шт apply
	cout << "NLR : "; NLRapplyFunctionToEachNode(a1, printNodeValue); cout << endl;
	cout << "NRL : "; NRLapplyFunctionToEachNode(a1, printNodeValue); cout << endl;
	cout << "LNR : "; LNRapplyFunctionToEachNode(a1, printNodeValue); cout << endl;
	cout << "RNL : "; RNLapplyFunctionToEachNode(a1, printNodeValue); cout << endl;
	cout << "LRN : "; LRNapplyFunctionToEachNode(a1, printNodeValue); cout << endl;
	cout << "RLN : "; RLNapplyFunctionToEachNode(a1, printNodeValue); cout << endl;
	cout << "------------------------------------" << endl;
	clearLRN(a1);
	//clearRLN(a1);
};

/// функция Primer4 : Создает бинарное дерево,
/// добавляет в него 7 узлов, и выводит их содержимое.
/// удаление узла из дерева.
/// нахождения следующего наибольшего значения узла.
void Primer4() {
	cout << "------------------------------------" << endl;
	BinaryTree<int> tree;
	// Вставка узлов в бинарное дерево
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	// ********************************************************
	// выводящий все элементы дерева в порядке inorder
	cout << "Индерный обход дерева (до удаления узла): " << endl;
	tree.print();
	// Удаляем узел (например, с значением 70)
	tree.remove(80);
	cout << "Индерный обход дерева (после удаления узла 70): " << endl;
	tree.print();

	int searchValue1 = 20; // Значение, которое мы ищем
	shared_ptr<TreeNode<int>> result1 = tree.search(searchValue1);
	if (result1 != nullptr) {
		cout << "Узел с значением " << searchValue1 << " найден." << endl;
	}
	else {
		cout << "Узел с значением " << searchValue1 << " не найден." << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;

	// Пример нахождения следующего наибольшего значения узла
	try {
		int value = 20;
		int nextGreater = tree.findNextGreater(value);
		cout << "Следующее наибольшее значение для " << value << " равно " << nextGreater << endl;
	}
	// объект cerr в C++. ‘C’ в Сerr означает “символ” и “err” означает “ошибка”,
	// значит Cerr означает “Ошибка символа”.
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;
	tree.~BinaryTree();
};

/// функция Primer5 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
/// удаление узла из дерева.
void Primer5() {
	// объявление переменных - Пример создания бинарного дерева
	// shared_ptr умные указатели
	// make_shared() — это функция, имеющая преимущество при выделении памяти
	shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
	shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
	shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
	shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
	shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
	// постороение дерева
	a1->left = a2;
	a1->right = a3;
	a3->left = a4;
	a3->right = a5;
	cout << "------------------------------------" << endl;
	cout << "Начальная древовидная структура (обход по уровням) : " << endl;
	cout << "NLR : "; NLR(a1); cout << endl;
	printTree(a1, 0);
	cout << "Дерево после удаления узла со значением 3 (метод удаления поддерева) : " << endl;
	// Полное удаление поддерева (совмещение узла и всех потомков).
	deleteSubtree(a1, 3);
	cout << "NLR : "; NLR(a1); cout << endl;
	printTree(a1, 0);
	cout << endl;
	// объявление переменных - Восстанавливаем начальное дерево
	cout << "------------------------------------" << endl;
	shared_ptr<TreeNode<int>> a6 = make_shared<TreeNode<int>>(6);
	shared_ptr<TreeNode<int>> a7 = make_shared<TreeNode<int>>(7);
	shared_ptr<TreeNode<int>> a8 = make_shared<TreeNode<int>>(8);
	shared_ptr<TreeNode<int>> a9 = make_shared<TreeNode<int>>(9);
	shared_ptr<TreeNode<int>> a10 = make_shared<TreeNode<int>>(10);
	// постороение дерева
	a6->left = a7;
	a6->right = a8;
	a8->left = a9;
	a8->right = a10;
	cout << "------------------------------------" << endl;
	cout << "Начальная древовидная структура (обход по уровням) : " << endl;
	cout << "NLR : "; NLR(a6); cout << endl;
	printTree(a6, 0);
	cout << "Дерево после удаления узла со значением 7 (метод замены узла) : " << endl;
	// Замена узла его потомком (если узел имеет детей, они становятся детьми родительского узла).
	deleteNodeByReplacing(a6, 8);
	cout << "NLR : "; NLR(a6); cout << endl;
	printTree(a6, 0);
	cout << endl;
	clearLRN(a1);
	clearLRN(a6);
	//clearRLN(a1);
};

/// функция Primer6 : Создает бинарное дерево,
/// добавляет в него 5 узлов, и выводит их содержимое.
/// Нахождения следующего наибольшего значения узла.
/// Метод основывается на Inorder. Альтернативный метод используя стек.
void Primer6() {
	cout << "------------------------------------" << endl;
	BinaryTree<int> tree;
	// Вставка узлов в бинарное дерево
	tree.insert(50);
	tree.insert(30);
	tree.insert(10);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	// выводящий все элементы дерева в порядке inorder
	cout << "Структура бинарного дерева : " << endl;
	tree.print();
	cout << "------------------------------------" << endl;
	int searchValue = 20; // Значение, которое мы ищем
	shared_ptr<TreeNode<int>> result = tree.search(searchValue);
	if (result != nullptr) {
		cout << "Узел с значением " << searchValue << " найден." << endl;
	}
	else {
		cout << "Узел с значением " << searchValue << " не найден." << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;

	// Нахождение следующего наибольшего значения для узла со значением 10 двумя способами
	int successor1 = tree.findInorderSuccessor(searchValue);
	int successor2 = tree.findInorderSuccessorIterative(searchValue);
	//shared_ptr<TreeNode<int>> successor2 = tree.findInorderSuccessorIterative(searchValue);

	if (successor1) {
		cout << "Следующее наибольшее значение (метод 1 - основываясь на Inorder) : " << successor1 << endl;
	}
	else {
		cout << "Следующее наибольшее значение (метод 1 - основываясь на Inorder) не найдено." << endl;
	}

	if (successor2) {
		cout << "Следующее наибольшее значение (метод 2 - стек для эмуляции рекурсивного обхода) : " << successor2 << endl;
	}
	else {
		cout << "Следующее наибольшее значение (метод 2 - стек для эмуляции рекурсивного обхода) не найдено." << endl;
	}

	// Пример нахождения следующего наибольшего значения узла
	// это мой первый пример
	try {
		int nextGreater = tree.findNextGreater(searchValue);
		cout << "Следующее наибольшее значение для " << searchValue << " равно " << nextGreater << endl;
	}
	// объект cerr в C++. ‘C’ в Сerr означает “символ” и “err” означает “ошибка”,
	// значит Cerr означает “Ошибка символа”.
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;
	tree.~BinaryTree();
};