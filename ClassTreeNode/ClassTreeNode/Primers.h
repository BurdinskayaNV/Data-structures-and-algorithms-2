// ������ � ���������
#pragma once
#include "ClassBinTreeNode.h"
#include "functions.h"

/// ������� Primer1 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
/// ������� �������, ������� ������, ���������� �����.
/// ����������� ������ � ����� � �������.
void Primer1() {
	// ���������� ���������� - ������ �������� ��������� ������
	// shared_ptr ����� ���������
	// make_shared() � ��� �������, ������� ������������ ��� ��������� ������
	shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
	shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
	shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
	shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
	shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
	// ����������� ������
	a1->left = a2;
	a1->right = a3;
	a3->left = a4;
	a3->right = a5;
	// ������� ��������� � ��������� ���� TreeNode
	cout << "------------------------------------" << endl;
	cout << "������� ��������� � ��������� ���� TreeNode" << endl;
	cout << "a1->value  " << a1->value << endl;
	cout << "a1->left->value  " << a1->left->value << endl;
	cout << "a1->right->value  " << a1->right->value << endl;
	cout << "a3->left->value  " << a3->left->value << endl;
	cout << "a3->right->value  " << a3->right->value << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "������� �������" << endl;
	cout << "NLR : "; NLR(a1); cout << endl;
	cout << "NRL : "; NRL(a1); cout << endl;
	cout << "RNL : "; RNL(a1); cout << endl;
	cout << "RLN : "; RLN(a1); cout << endl;
	cout << "LNR : "; LNR(a1); cout << endl;
	cout << "LRN : "; LRN(a1); cout << endl;
	cout << endl;
	cout << "������� ������  " << depth_root(a1) << endl;
	cout << endl;
	cout << "���������� �����  " << count_nodes_root(a1) << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "��������� ������ (����������� ����������� � �������): " << endl;
	printTree(a1, 0);
	cout << "------------------------------------" << endl;
	cout << "��������� ������ (������ ������ � preOrder NRL ������): " << endl;
	printTree1(a1);
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
	cout << "------------------------------------" << endl;
	cout << "����������� ������ � ����� � �������: " << endl;
	shared_ptr<TreeNode<int>> copiedTree = copyTree(a1);
	printTree(copiedTree, 0);
	cout << "------------------------------------" << endl;
	cout << endl;
	clearLRN(a1);
	clearLRN(copiedTree);
	//clearRLN(a1);
};

/// ������� Primer2 : ������� �������� ������,
/// ��������� � ���� 7 �����, � ������� �� ����������.
/// ����� ���� ������ � ����� � �������.
void Primer2() {
	cout << "------------------------------------" << endl;
	cout << "����� ���� ������ � ����� � �������: " << endl;
	BinaryTree<int> tree;
	// ������� ����� � �������� ������
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	// ��������� ��� �������� ������ � ������� inorder
	cout << "�������� ����� ������ : " << endl;
	tree.print();
	cout << "------------------------------------" << endl;
	cout << endl;
	int searchValue = 40; // ��������, ������� �� ����
	shared_ptr<TreeNode<int>> result = tree.search(searchValue);
	if (result != nullptr) {
		cout << "���� � ��������� " << searchValue << " ������." << endl;
	}
	else {
		cout << "���� � ��������� " << searchValue << " �� ������." << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;
	tree.~BinaryTree();
};

/// ������� Primer3 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
/// ������� ��� ���������� ������ ������� � ������� ���� ������.
void Primer3() {
	// ���������� ���������� - ������ �������� ��������� ������
	// shared_ptr ����� ���������
	// make_shared() � ��� �������, ������� ������������ ��� ��������� ������
	shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
	shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
	shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
	shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
	shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
	// ����������� ������
	a1->left = a2;
	a1->right = a3;
	a3->left = a4;
	a3->right = a5;
	cout << "------------------------------------" << endl;
	cout << "������� ��� ���������� ������ ������� � ������� ���� ������: " << endl;
	// ****************************************************************************
	// ���������� �������, ������� �� �������� � ������� ����
	// ������-��������� ���������� � ���������� ������.
	// �����, ��� � ������� �������, � ������� ������� ���� ������������ ���������� - ���� � �� �����.
	// �� ������� ����������, ��� � � ������� �������, � �������� ������� ���������� ��������,
	// ����������� ������-����������.
	// ���������� printNodeValue ������������ ������������ ������-��������� 
	auto printNodeValue = [](int value) {
		// ���� �����
		//cout << value << " ";
		//cout << value + 1 << " ";
		cout << value * 5 << " ";
	};
	// ��������� ������� � ������� ���� ������ 6 �� apply
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

/// ������� Primer4 : ������� �������� ������,
/// ��������� � ���� 7 �����, � ������� �� ����������.
/// �������� ���� �� ������.
/// ���������� ���������� ����������� �������� ����.
void Primer4() {
	cout << "------------------------------------" << endl;
	BinaryTree<int> tree;
	// ������� ����� � �������� ������
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	// ********************************************************
	// ��������� ��� �������� ������ � ������� inorder
	cout << "�������� ����� ������ (�� �������� ����): " << endl;
	tree.print();
	// ������� ���� (��������, � ��������� 70)
	tree.remove(80);
	cout << "�������� ����� ������ (����� �������� ���� 70): " << endl;
	tree.print();

	int searchValue1 = 20; // ��������, ������� �� ����
	shared_ptr<TreeNode<int>> result1 = tree.search(searchValue1);
	if (result1 != nullptr) {
		cout << "���� � ��������� " << searchValue1 << " ������." << endl;
	}
	else {
		cout << "���� � ��������� " << searchValue1 << " �� ������." << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;

	// ������ ���������� ���������� ����������� �������� ����
	try {
		int value = 20;
		int nextGreater = tree.findNextGreater(value);
		cout << "��������� ���������� �������� ��� " << value << " ����� " << nextGreater << endl;
	}
	// ������ cerr � C++. �C� � �err �������� ������� � �err� �������� ��������,
	// ������ Cerr �������� ������� ��������.
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;
	tree.~BinaryTree();
};

/// ������� Primer5 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
/// �������� ���� �� ������.
void Primer5() {
	// ���������� ���������� - ������ �������� ��������� ������
	// shared_ptr ����� ���������
	// make_shared() � ��� �������, ������� ������������ ��� ��������� ������
	shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
	shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
	shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
	shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
	shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
	// ����������� ������
	a1->left = a2;
	a1->right = a3;
	a3->left = a4;
	a3->right = a5;
	cout << "------------------------------------" << endl;
	cout << "��������� ����������� ��������� (����� �� �������) : " << endl;
	cout << "NLR : "; NLR(a1); cout << endl;
	printTree(a1, 0);
	cout << "������ ����� �������� ���� �� ��������� 3 (����� �������� ���������) : " << endl;
	// ������ �������� ��������� (���������� ���� � ���� ��������).
	deleteSubtree(a1, 3);
	cout << "NLR : "; NLR(a1); cout << endl;
	printTree(a1, 0);
	cout << endl;
	// ���������� ���������� - ��������������� ��������� ������
	cout << "------------------------------------" << endl;
	shared_ptr<TreeNode<int>> a6 = make_shared<TreeNode<int>>(6);
	shared_ptr<TreeNode<int>> a7 = make_shared<TreeNode<int>>(7);
	shared_ptr<TreeNode<int>> a8 = make_shared<TreeNode<int>>(8);
	shared_ptr<TreeNode<int>> a9 = make_shared<TreeNode<int>>(9);
	shared_ptr<TreeNode<int>> a10 = make_shared<TreeNode<int>>(10);
	// ����������� ������
	a6->left = a7;
	a6->right = a8;
	a8->left = a9;
	a8->right = a10;
	cout << "------------------------------------" << endl;
	cout << "��������� ����������� ��������� (����� �� �������) : " << endl;
	cout << "NLR : "; NLR(a6); cout << endl;
	printTree(a6, 0);
	cout << "������ ����� �������� ���� �� ��������� 7 (����� ������ ����) : " << endl;
	// ������ ���� ��� �������� (���� ���� ����� �����, ��� ���������� ������ ������������� ����).
	deleteNodeByReplacing(a6, 8);
	cout << "NLR : "; NLR(a6); cout << endl;
	printTree(a6, 0);
	cout << endl;
	clearLRN(a1);
	clearLRN(a6);
	//clearRLN(a1);
};

/// ������� Primer6 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
/// ���������� ���������� ����������� �������� ����.
/// ����� ������������ �� Inorder. �������������� ����� ��������� ����.
void Primer6() {
	cout << "------------------------------------" << endl;
	BinaryTree<int> tree;
	// ������� ����� � �������� ������
	tree.insert(50);
	tree.insert(30);
	tree.insert(10);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	// ��������� ��� �������� ������ � ������� inorder
	cout << "��������� ��������� ������ : " << endl;
	tree.print();
	cout << "------------------------------------" << endl;
	int searchValue = 20; // ��������, ������� �� ����
	shared_ptr<TreeNode<int>> result = tree.search(searchValue);
	if (result != nullptr) {
		cout << "���� � ��������� " << searchValue << " ������." << endl;
	}
	else {
		cout << "���� � ��������� " << searchValue << " �� ������." << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;

	// ���������� ���������� ����������� �������� ��� ���� �� ��������� 10 ����� ���������
	int successor1 = tree.findInorderSuccessor(searchValue);
	int successor2 = tree.findInorderSuccessorIterative(searchValue);
	//shared_ptr<TreeNode<int>> successor2 = tree.findInorderSuccessorIterative(searchValue);

	if (successor1) {
		cout << "��������� ���������� �������� (����� 1 - ����������� �� Inorder) : " << successor1 << endl;
	}
	else {
		cout << "��������� ���������� �������� (����� 1 - ����������� �� Inorder) �� �������." << endl;
	}

	if (successor2) {
		cout << "��������� ���������� �������� (����� 2 - ���� ��� �������� ������������ ������) : " << successor2 << endl;
	}
	else {
		cout << "��������� ���������� �������� (����� 2 - ���� ��� �������� ������������ ������) �� �������." << endl;
	}

	// ������ ���������� ���������� ����������� �������� ����
	// ��� ��� ������ ������
	try {
		int nextGreater = tree.findNextGreater(searchValue);
		cout << "��������� ���������� �������� ��� " << searchValue << " ����� " << nextGreater << endl;
	}
	// ������ cerr � C++. �C� � �err �������� ������� � �err� �������� ��������,
	// ������ Cerr �������� ������� ��������.
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
	}
	cout << "------------------------------------" << endl;
	cout << endl;
	tree.~BinaryTree();
};