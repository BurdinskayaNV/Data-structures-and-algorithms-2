#pragma once
#include "ClassBinTreeNode.h"

// Класс Graph представляет собой структуру данных "граф"
// слайд 84
class Graph {
private:
    // Число вершин в графе
    int vertices;
    // Список смежности для хранения ребер графа
    vector<vector<int>> adjList;

public:
    // Конструктор графа принимает на вход количество вершин
    Graph(int V) : vertices(V), adjList(V) {}

    // Метод для добавления ребра между двумя вершинами u и v
    void addEdge(int u, int v) {
        // Добавляем вершину v в список смежности вершины u
        adjList[u].push_back(v);

        // Поскольку мы рассматриваем неориентированный граф, 
        // добавляем вершину u в список смежности вершины v
        adjList[v].push_back(u);
    }

    // Метод для проверки наличия ребра между двумя вершинами u и v
    bool hasEdge(int u, int v) {
        for (int i : adjList[u]) {
            if (i == v) {
                return true;
            }
        }
        return false;
    }

    // Метод для получения количества вершин в графе
    int getVerticesCount() const {
        return vertices;
    }

    // Метод для печати графа
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

// Простое тестирование с использованием assert
void testGraph() {
    // Создание графа с 5 вершинами
    Graph g(5);

    // Добавление ребер в граф
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Проверка наличия ребер
    assert(g.hasEdge(0, 1) == true);
    assert(g.hasEdge(0, 2) == false);
    assert(g.hasEdge(1, 4) == true);
    assert(g.hasEdge(3, 4) == true);

    // Проверка количества вершин
    assert(g.getVerticesCount() == 5);

    // Вывод графа для визуальной проверки
    g.printGraph();

    cout << endl;
    //cout << "------------------------------------" << endl;
    cout << "Тестирование функции testGraph выполнено успешно" << endl;
};
