// ������ ������������
#pragma once
#include "ClassBinTreeNode.h"

/// �������� ������� testBinaryTree1 : ������� �������� ������,
/// ��������� � ���� 5 �����, � ������� �� ����������.
void testBinaryTree1() {
    // ��������� 5 �����
    shared_ptr<TreeNode<int>> a1 = make_shared<TreeNode<int>>(1);
    shared_ptr<TreeNode<int>> a2 = make_shared<TreeNode<int>>(2);
    assert(count_nodes_root(a1) == 1);
    shared_ptr<TreeNode<int>> a3 = make_shared<TreeNode<int>>(3);
    shared_ptr<TreeNode<int>> a4 = make_shared<TreeNode<int>>(4);
    shared_ptr<TreeNode<int>> a5 = make_shared<TreeNode<int>>(5);
    assert(count_nodes_root(a4) == 1);

    BinaryTree<int> tree;
    // ������� ����� � �������� ������
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    // ���������� ���������� ����������� ��������
    assert(tree.findNextGreater(5) == 7);  // ��������� ���������� �������� ����� 5 ������ ���� 7
    assert(tree.findNextGreater(10) == 15); // ��������� ���������� �������� ����� 10 ������ ���� 15
    assert(tree.findNextGreater(7) == 10);  // ��������� ���������� �������� ����� 7 ������ ���� 10
    // ������������ � �������������� assert ������� remove
    //int searchValue = 2; // ��������, ������� �� �������
    //shared_ptr<TreeNode<int>> result = tree.remove(searchValue); // ������� ������� �������������� ����
    //assert(result != nullptr); // ��������, ��� ������� remove ��������� ����������

    // ������������ � �������������� assert ������� search
    int searchValue1 = 15; // ��������, ������� �� ����
    shared_ptr<TreeNode<int>> result1 = tree.search(searchValue1);
    assert(result1 != nullptr); // ��������, ��� ������� search ��������� ����������

    // count_nodes_root: ���������� ���������� �����
    //assert(count_nodes_root(a1)) == 2;
    //assert(tree.count_nodes() == 5);
    // depth_root: ����������� ������� ������
    //assert(tree.depth == 1);
    //int searchValue = 40; // ��������, ������� �� ����
    //shared_ptr<TreeNode<int>> result = tree.search(searchValue);

    cout << "������������ ������� testBinaryTree1 ��������� �������" << endl;

    /* // count_nodes_root: ���������� ���������� �����
     assert(tree.count_nodes_root) == 2;
     // count_nodes_root: ���������� ���������� �����
     assert(tree.count_nodes_root() == 5);
     // depth_root: ����������� ������� ������
     assert(tree.depth_root() == 2); */

     // ���� ��� ������� ������
    BinaryTree<int> nullTree;
    //assert(nullTree.count_nodes_root() == 0);
    //assert(nullTree.depth_root() == -1);

    tree.~BinaryTree();
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