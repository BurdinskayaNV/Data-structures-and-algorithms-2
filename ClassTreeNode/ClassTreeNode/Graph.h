#pragma once
#include "ClassBinTreeNode.h"

// ����� Graph ������������ ����� ��������� ������ "����"
// ����� 84
class Graph {
private:
    // ����� ������ � �����
    int vertices;
    // ������ ��������� ��� �������� ����� �����
    vector<vector<int>> adjList;

public:
    // ����������� ����� ��������� �� ���� ���������� ������
    Graph(int V) : vertices(V), adjList(V) {}

    // ����� ��� ���������� ����� ����� ����� ��������� u � v
    void addEdge(int u, int v) {
        // ��������� ������� v � ������ ��������� ������� u
        adjList[u].push_back(v);

        // ��������� �� ������������� ����������������� ����, 
        // ��������� ������� u � ������ ��������� ������� v
        adjList[v].push_back(u);
    }

    // ����� ��� �������� ������� ����� ����� ����� ��������� u � v
    bool hasEdge(int u, int v) {
        for (int i : adjList[u]) {
            if (i == v) {
                return true;
            }
        }
        return false;
    }

    // ����� ��� ��������� ���������� ������ � �����
    int getVerticesCount() const {
        return vertices;
    }

    // ����� ��� ������ �����
    void printGraph() const {
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (auto v : adjList[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

// ������� ������������ � �������������� assert
void testGraph() {
    // �������� ����� � 5 ���������
    Graph g(5);

    // ���������� ����� � ����
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // �������� ������� �����
    assert(g.hasEdge(0, 1) == true);
    assert(g.hasEdge(0, 2) == false);
    assert(g.hasEdge(1, 4) == true);
    assert(g.hasEdge(3, 4) == true);

    // �������� ���������� ������
    assert(g.getVerticesCount() == 5);

    // ����� ����� ��� ���������� ��������
    g.printGraph();

    cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "������������ ������� testGraph ��������� �������" << endl;
};
