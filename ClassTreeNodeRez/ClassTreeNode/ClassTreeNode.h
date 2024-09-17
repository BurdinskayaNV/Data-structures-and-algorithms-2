/// ���������� ������� ���-22
/// Date - 03.09.2024
#pragma once
#include <iostream>  /// ��������� cin cout
#include <memory>
#include <queue>
#include <cassert>
#include <functional>
#include <vector>
#include <stack>
#include <locale>   /// ���������� ������� setlocale ��� ��������� ������� ������
using namespace std;

/// ����� TreeNode : ��������� �����, �������������� ���� ��������� ������.
/// ������ ���� �������� �������� � ��������� �� ������ � ������� ��������.
template<typename T>
class TreeNode {
public:
    T value;

    /// shared_ptr ����� ���������
    /// ��������������, ����� ������ ������ ������ ���� �����������
    /// (������� � ����, ��� ����� �� ���� � �� �� ������� ������ �����
    /// ��������� ��������� ���������� ������ shared_ptr ���� <TreeNode<T>>).
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;

    /// ����������� ��� ����������
    TreeNode() { left = nullptr; right = nullptr; }

    /// ����������� � ����������, ��� val �������� ����
    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};
