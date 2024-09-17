/// ClassTreeNode.cpp : Этот файл содержит функцию "main".
/// Бурдинская Наталья ВМК-22
/// Date - 03.09.2024
///            1
///          /   \
///        2      3
///             /  \
///            4     5

#include "ClassTreeNode.h"
#include "ClassBinTreeNode.h"

int main() {
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    // Тестовая функция testBinaryTree1 : Создает бинарное дерево, добавляет в него 5 узлов и выводит их содержимое.
	cout << "Тестирование функции testBinaryTree1" << endl;
	testBinaryTree1();
	cout << endl;
	// Тестовая функция testBinaryTree2 : Создает бинарное дерево, добавляет в него 5 узлов и выводит их содержимое.
	cout << "Тестирование функции testBinaryTree2" << endl;
	testBinaryTree2();
	cout << endl;
    // Тестовая функция testBinaryTree3 : Создает бинарное дерево, добавляет в него 5 узлов и выводит их содержимое.
	cout << "Тестирование функции testBinaryTree3" << endl;
	testBinaryTree3();
	cout << endl;

    // объявление переменных
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

	// примеры обращения к элементам
	cout << "Примеры обращения к элементам" << endl;
	cout << a1->value << endl;
	cout << a1->left->value << endl;
	cout << a1->right->value << endl;
	cout << a3->left->value << endl;
	cout << a3->right->value << endl;
	cout << endl;
	cout << "Примеры обходов" << endl;
	cout << "NLR : "; NLR(a1); cout << endl;
	cout << "NRL : "; NRL(a1); cout << endl;
	cout << "RNL : "; RNL(a1); cout << endl;
	cout << "RLN : "; RLN(a1); cout << endl;
	cout << "LNR : "; LNR(a1); cout << endl;
	cout << "LRN : "; LRN(a1); cout << endl;
	cout << endl;
	cout << "Глубина дерева  " << depth_root(a1);
	cout << endl;
	cout << "Количество узлов  " << count_nodes_root(a1);
	cout << endl;
	printTree(a1, 0);
	clearLRN(a1);
	//clearRLN(a1);

    return 0;
}
