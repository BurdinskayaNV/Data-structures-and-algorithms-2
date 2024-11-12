﻿/// ClassTreeNode.cpp : Этот файл содержит функцию "main".
/// Бурдинская Наталья ВМК-22
/// Date - 03.09.2024
///            1
///          /   \
///        2      3
///             /  \
///            4     5

#include "ClassBinTreeNode.h"
#include "Primers.h"
#include "testing.h"
#include "detours.h"
#include "functions.h"
#include "dopmodul.h"
#include "NewClear.h"
#include "AVL.h"
#include "Graph.h"

int main() {
	// «Rus» локализация произойдёт на русский язык
	setlocale(LC_ALL, "russian");

	// Тестовая функция testTraversals : Создает бинарное дерево, добавляет в него 7 узлов и обход без рекурсий.
	//cout << "------------------------------------" << endl;
	//cout << "Тестирование функции testTraversals Обходы без рекурсий" << endl;
	//testTraversals();
	//cout << "------------------------------------" << endl;
	//cout << endl;

	// for_each, any_of, all_of, none_of, transform и copy_if для работы с данными внутри контейнера.
	//cout << "------------------------------------" << endl;
	//cout << "Тестирование функции Algorithms" << endl;
	//algorithms();
	//cout << "------------------------------------" << endl;
	//cout << endl;

	//Тестовая функция testBinaryTree1 : Создает бинарное дерево, добавляет в него 5 узлов и выводит их содержимое.
	//cout << "------------------------------------" << endl;
	//cout << "Тестирование функции testBinaryTree1" << endl;
	//testBinaryTree1();
	//cout << "------------------------------------" << endl;
	//cout << endl;

	// Тестовая функция testBinaryTree2 : Создает бинарное дерево, добавляет в него 5 узлов и выводит их содержимое.
	//cout << "------------------------------------" << endl;
	//cout << "Тестирование функции testBinaryTree2" << endl;
	//testBinaryTree2();
	//cout << "------------------------------------" << endl;
	//cout << endl;

	// Тестовая функция AVLtest : Создает дерево AVL, добавляет в него 5 узлов и выводит их содержимое.
	cout << "------------------------------------" << endl;
	cout << "Тестирование функции AVLtest" << endl;
	AVLtest();
	cout << "------------------------------------" << endl;
	cout << endl;
	
	// Тестовая функция testGraph : Класс Graph представляет собой структуру данных "граф".
	cout << "------------------------------------" << endl;
	cout << "Тестирование функции testGraph" << endl;
	testGraph();
	cout << "------------------------------------" << endl;
	cout << endl;

	//Primer1(); // Примеры обходов, Глубина дерева, Количество узлов. Копирование дерева и вывод в консоль.
	//Primer2(); // Поиск узла дерева и вывод в консоль.
	//Primer3(); // Функция для применения данной функции к каждому узлу дерева.
	//Primer4(); // Удаление узла из дерева. Нахождения следующего наибольшего значения узла.
	//Primer5(); // Удаление узла из дерева. Обход по уровням. Метод замены узла.
	//Primer6(); // Нахождения следующего наибольшего значения узла. Метод основывается на Inorder. Альтернативный метод используя стек.
	return 0;
}