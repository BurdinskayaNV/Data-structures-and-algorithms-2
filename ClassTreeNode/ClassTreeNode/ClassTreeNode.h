/// ���������� ������� ���-22
/// Date - 03.09.2024
#pragma once
#include <iostream> /// ��������� cin cout
#include <memory>   /// ����� ��������� � ������� shared_ptr make_shared
#include <cassert>  /// ��� assert
#include <queue>    /// ����� queue ������������ ������� 
#include <functional>  /// ����� �������� ������� ��� ������ � ��������������� ���������
#include <vector>   /// ������� �������
#include <stack>    /// Stack ����� ��� �������� ��������: push, pop, � ����� peek.
#include <locale>   /// ���������� ������� setlocale ��� ��������� ������� ������
#include <algorithm> /// �������� ����� ������� ��� ���������� ���������������
                     /// �������� ��� ������������ � ��� ������� ��������������������
#include <sstream>  /// ��� ����������� ������ �� �������� ����� ��������� ������� 
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

