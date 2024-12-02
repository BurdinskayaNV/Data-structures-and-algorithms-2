/// Бурдинская Наталья ВМК-22
/// Graph.cpp Date - 18.11.2024
#include "GraphModul.h"

int main() {
    // «Rus» локализация произойдёт на русский язык
    setlocale(LC_ALL, "russian");
    // Тестовая функция testGraph : 
    cout << "------------------------------------" << endl;
    cout << "Тестирование функции testGraph" << endl;
    Graph<string>::testGraph();
    cout << "------------------------------------" << endl;
    cout << endl;
    cout << "------------------------------------" << endl;
    cout << "---------- Основной блок -----------" << endl;
    cout << "------------------------------------" << endl;
 
    Graph<string> g;
    cout << "Ручной граф: " << endl;
    g.InsertVertex("A");
    g.InsertVertex("B");
    g.InsertVertex("C");
    g.InsertVertex("D");
    g.InsertVertex("E");
    g.InsertEdge("E", "A", 4.0);
    g.InsertEdge("B", "E", 4.0);
    g.InsertEdge("A", "B", 2.0);
    g.InsertEdge("A", "A", 1.0);
    g.InsertEdge("B", "C", 3.0);
    g.InsertEdge("C", "D", 1.0);
    g.InsertEdge("D", "A", 4.0);
    g.printvertexList();
    g.printEdges();
    cout << "Количество ребер: " << g.NumberOfEdges() << endl;
    cout << "Количество вершин: " << g.NumberOfVertices() << endl;
    cout << "Минимально возможный путь между вершинами А и С: " << endl;
    vector<double> distances = g.MinimumPath1("A", "C");
    for (double val : distances)
    { cout << val << "   "; }
    cout << endl;
    cout << "Размер дистанции: " << distances.size() << endl;
    cout << "Обход в глубину: " << endl;
    g.DepthFirstSearch("A");
    cout << "Обход в ширину: " << endl;
    g.BreadthFirstSearch("A");
    cout << "Матрица смежности: " << endl;
    g.printedge();
    g.SaveGraph("graph.graphml"); // запись в файл graph.xml
    return 0;
}