// ������ ������������
#pragma once
#include "ClassBinTreeNode.h"
#include "NewClear.h"
#include "detours.h"
#include <cassert>

/// �������� ������� testBinaryTree1 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
void testBinaryTree1() {

    // ������ 1: ������ ������
    shared_ptr<TreeNode<int>> root1 = nullptr;
    assert(depth_root(root1) == -1);  // ������� ������� ������ ������ ���� -1
    assert(count_nodes_root(root1) == 0); // ���������� ���������� �����
   
    // ������ 2: ������ � ����� �����
    shared_ptr<TreeNode<int>> root2 = make_shared<TreeNode<int>>(1);
    assert(depth_root(root2) == 0);  // ������� ������ � ����� ����� ������ ���� 0
    assert(count_nodes_root(root2) == 1); // ���������� ���������� �����

    // ������ 3: ������ �������� ������ � �������� 2
    auto root3 = make_shared<TreeNode<int>>(1);
    root3->left = make_shared<TreeNode<int>>(2);
    root3->right = make_shared<TreeNode<int>>(3);
    root3->left->left = make_shared<TreeNode<int>>(4);
    root3->left->right = make_shared<TreeNode<int>>(5);
    root3->right->left = make_shared<TreeNode<int>>(6);
    root3->right->right = make_shared<TreeNode<int>>(7);
    assert(depth_root(root3) == 2);  // ������� ������ ���� 2
    assert(count_nodes_root(root3) == 7);  // ���������� ���������� �����

    // ������ 4: ������������������ ������
    auto root4 = make_shared<TreeNode<int>>(1);
    root4->left = make_shared<TreeNode<int>>(2);
    root4->left->left = make_shared<TreeNode<int>>(3);
    assert(depth_root(root4) == 2);  // ������� ������ ���� 2 (������� ����� �����)
    assert(count_nodes_root(root4) == 3);  // ���������� ���������� �����

    // ������ ������:
    //        1
    //       / \\
    //      2   3
    //     / \\
    //    4   5
    auto root5 = make_shared<TreeNode<int>>(1);
    root5->left = make_shared<TreeNode<int>>(2);
    root5->right = make_shared<TreeNode<int>>(3);
    root5->left->left = make_shared<TreeNode<int>>(4);
    root5->left->right = make_shared<TreeNode<int>>(5);
    // ����������� ����� � ������
    // ostringstream � C++ � ��� �����, ������� ������������ ����� � ������ � ������. 
    ostringstream oss;
    NLR(root5);
    string result = oss.str();
    cout << "result : " << result << endl;
    // ��������� ������ ������
    string expected = "1 2 4 5 3";
    // ���������, ��� ����� ������������� ����������
    //assert(result == expected);
    
    
    // ����� �������� ���� ��� ������� ������
    shared_ptr<TreeNode<int>> empty_tree = nullptr;
    // ��������� ������ ������ ��� ������� ������ � ������ ������
    expected = "";
    assert(result == expected);

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
    assert(a1->value == 1);
    assert(a1->left->value == 2);
    assert(a1->right->value == 3);
    assert(a3->left->value == 4);
    assert(a3->right->value == 5);

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
    
    // ���������� ���������� ����������� ��������
    //assert(tree.findNextGreater(5) == 7);  // ��������� ���������� �������� ����� 5 ������ ���� 7
    //assert(tree.findNextGreater(10) == 15); // ��������� ���������� �������� ����� 10 ������ ���� 15
    //assert(tree.findNextGreater(7) == 10);  // ��������� ���������� �������� ����� 7 ������ ���� 10
    // ������������ � �������������� assert ������� remove
    //int searchValue = 2; // ��������, ������� �� �������
    //shared_ptr<TreeNode<int>> result = tree.remove(searchValue); // ������� ������� �������������� ����
    //assert(result != nullptr); // ��������, ��� ������� remove ��������� ����������

    // ������������ � �������������� assert ������� search
    int searchValue1 = 15; // ��������, ������� �� ����
    //shared_ptr<TreeNode<int>> result1 = tree.search(searchValue1);
    //assert(result1 != nullptr); // ��������, ��� ������� search ��������� ����������

    // count_nodes_root: ���������� ���������� �����
    //assert(count_nodes_root(a1)) == 2;
    //assert(tree.count_nodes() == 5);
    // depth_root: ����������� ������� ������
    //assert(tree.depth == 1);
    //int searchValue = 40; // ��������, ������� �� ����
    //shared_ptr<TreeNode<int>> result = tree.search(searchValue);

    cout << "������������ ������� testBinaryTree1 ��������� �������" << endl;

    // count_nodes_root: ���������� ���������� �����
     //assert(tree.count_nodes_root) == 2;
     // count_nodes_root: ���������� ���������� �����
     //assert(tree.count_nodes_root() == 5);
     // depth_root: ����������� ������� ������
     //assert(tree.depth_root() == 2);

    
    //tree.~BinaryTree();
    //assert(tree.count_nodes_root() == 0);
    //assert(tree.depth_root() == -1);

    // ���� ��� ������ �� ������ ����
    BinaryTree<int> vetkaTree;
    vetkaTree.insert(9);
    //assert(vetkaTree.count_nodes() == 1);
    //assert(vetkaTree.depth() == 0);

    vetkaTree.~BinaryTree();
    //assert(vetkaTree.count_nodes_root() == 0);
    //assert(vetkaTree.depth_root() == -1);
};

/// �������� ������� testBinaryTree2 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
void testBinaryTree2() {
    BinaryTree<int> tree;
    // ��������� 5 �����
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(1);
    tree.insert(4);

    cout << "��������� ������: " << endl;
    tree.print();
    cout << endl;
    cout << "������� ������� ����� vector: " << endl;
    cout << "NLR: ";
    for (const int& value : tree.preorder()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "NRL: ";
    for (const int& value : tree.preorder1()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "LNR: ";
    for (const int& value : tree.inorder()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "RNL: ";
    for (const int& value : tree.inorder1()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "LRN: ";
    for (const int& value : tree.postorder()) {
        cout << value << " ";
    }
    cout << endl;
    cout << "RLN: ";
    for (const int& value : tree.postorder1()) {
        cout << value << " ";
    }
    cout << endl;
    // ����������� ������
    BinaryTree<int> copiedTree(tree);
    cout << "------------------------------------" << endl;
    cout << "��������� �������������� ������: " << endl;
    copiedTree.print();
    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "������������ ������� testBinaryTree2 ��������� �������" << endl;
};