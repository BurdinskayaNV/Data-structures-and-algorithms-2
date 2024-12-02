/// GraphModul.h - создаем класс графа с использованием матриц смежности для представления рёбер между вершинами. 
#pragma once
#include <iostream>   /// объявляет cin cout.
#include <vector>     /// шаблоны вектора.
#include <string>     /// для работы со строками.
#include <limits>     /// определяет числовые ограничения целочисленных типов.
#include <queue>      /// очередь — контейнер, который работает по принципу FIFO («первый вошёл — первым вышел»).
#include <functional> /// набор шаблонов классов для работы с функциональными объектами.
#include <iomanip>    /// позволяет управлять процессами форматирования вывода.
#include <sstream>    /// для организации работы со строками через интерфейс потоков.
#include <fstream>    /// определяет базовые типы для чтения и записи файлов.
#include <cassert>    /// для assert.
#include <locale>     /// определяет функцию setlocale для установки русской локали.
#include <algorithm>  /// Для remove, find, distance.
#include <stack>      /// реализация stack имеет три основные операции: push, pop, а также peek.
using namespace std;

// Максимальное количество вершин в графе (определяется созданием графа)
//const int MaxGraphSize = 25;
// Шаблонный класс взвешенного графа
template <typename T>
class Graph {
private:
  vector<T> vertexList; // список вершин графа
  vector<vector<double>> edge; // Матрица смежности. показывает наличие и вес ребра между вершинами.
  int graphsize; // текущее количество вершин в графе
public:

  // конструктор класса Graph
  Graph() {}
  
  // Деструктор
  ~Graph() {}
  
  // Метод поиска вершины в списке.
  // Если элемент найден, возвращаем его индекс, иначе -1.
  int FindVertex(const T& vertex) const {
     for (int i = 0; i < vertexList.size(); ++i) {
        if (vertexList[i] == vertex) { return i; }
     }
     return -1; // Вершина не найдена.
  }
  
  // Метод поиска позиции вершины в списке
  int GetVertexPos(const T& vertex) const {
     return FindVertex(vertex);
  }

  // GraphEmpty: проверка на пустоту
  int GraphEmpty() const { return graphsize == 0; }

  // GraphFull: проверка на полность
  int GraphFull() const { return graphsize == vertexList.size(); }

  // GetWeight: получение веса ребра между двумя вершинами в графе
  int GetWeight(const T& vertex1, const T& vertex2) {
    int i = FindVertex(vertex1); // осуществляем поиск индекса первой вершины в графе
    int j = FindVertex(vertex2); // осуществляем поиск индекса второй вершины в графе
    // проверяем, что обе вершины найдены в графе и возвращаем вес ребра между найденными вершинами
    if (i != -1 && j != -1) return edge[i][j];
    return 0; // если хотя бы одна из вершин не найдена, возвращаем 0
  }

  // InsertVertex: добавляет новую вершину.
  // Бросает исключение out_of_range если вершина существует.
  void InsertVertex(const T& vertex) {
    if (FindVertex(vertex) != -1) {
       throw out_of_range("Вершина уже существует в графе.");
    }
    int newSize = vertexList.size() + 1;
    vertexList.push_back(vertex);
    // Обновление матрицы смежности
    if (edge.empty()) {
      edge.resize(newSize, vector<double>(newSize, 0.0));
    }
    else {
      for (auto& row : edge) { row.resize(newSize, 0.0); }
      edge.resize(newSize, vector<double>(newSize, 0.0));
    }
  }

  // DeleteVertex: удаляет вершину, а также все связанные с ней рёбра.
  // Бросает исключение out_of_range если вершина не существует.
  void DeleteVertex(const T& vertex) {
    int position = FindVertex(vertex);
    if (position == -1) {
      throw out_of_range("Вершина не найдена в графе.");
    }
    vertexList.erase(vertexList.begin() + position);
    // Обновление матрицы смежности
    edge.erase(edge.begin() + position);
    for (int i = 0; i < vertexList.size(); ++i) {
       edge[i].erase(edge[i].begin() + position);
    }
  }

  // InsertEdge: добавляет новое ребро между двумя вершинами
  // Бросает исключение out_of_range если вершина не существует 
  void InsertEdge(const T& vertex1, const T& vertex2, double weight) {
    int position1 = FindVertex(vertex1);
    int position2 = FindVertex(vertex2);
    if (position1 == -1 || position2 == -1) {
      throw out_of_range("Одна или обе вершины не найдены в графе.");
    }
    if (position1 > position2) { swap(position1, position2); }
    edge[position2][position1] = weight;
  }

  // DeleteEdge: удаляет ребро между двумя вершинами.
  // Бросает исключение out_of_range если вершина не существует 
  void DeleteEdge(const T& vertex1, const T& vertex2) {
    int position1 = FindVertex(vertex1);
    int position2 = FindVertex(vertex2);
    if (position1 == -1 || position2 == -1) {
      throw out_of_range("Одна или обе вершины не найдены в графе.");
    }
    if (position1 > position2) { swap(position1, position2); }
    edge[position2][position1] = 0.0;
  }

  // GetAdjacentvertexList: Метод возврата списка смежных вершин.
  // Бросает исключение out_of_range если вершина не существует 
  vector<T> GetAdjacentvertexList(const T& vertex) const {
    int position = FindVertex(vertex);
    if (position == -1) {
      throw out_of_range("Одна или обе вершины не найдены в графе.");
    }
    vector<T> adjacentvertexList;
    for (int i = 0; i < vertexList.size(); ++i) {
      if (edge[position][i] != 0.0) {
         adjacentvertexList.push_back(vertexList[i]);
      }
    }
    return adjacentvertexList;
  }

  // Метод вывода списка вершин
  void printvertexList() const {
     cout << "Список вершин: ";
     for (const auto& vertex : vertexList) { cout << vertex << " "; }
     cout << endl;
  }

  // Метод вывода списка ребер
  void printEdges() const {
    cout << "Список ребер: ";
    for (int i = 0; i < vertexList.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (edge[i][j] != 0.0) {
          cout << vertexList[i] << " - " << vertexList[j] << " (вес: " << edge[i][j] << ") ";
        }
      }
    }
    cout << endl;
  }

  // Метод возвращения количества ребер
  int NumberOfEdges() const {
    int edgeCount = 0;
    for (int i = 0; i < vertexList.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (edge[i][j] != 0.0) { edgeCount++; }
      }
    }
    return edgeCount;
  }

  // Метод возвращения количества вершин
  int NumberOfVertices() const { return vertexList.size(); }
  
  // DepthFirstSearch: алгоритм поиска в глубину (DFS) для графа,
  // начиная с указанной вершины.
  // Бросает исключение out_of_range если вершина не существует 
  void DepthFirstSearch(const T& startVertex) const {
    // Находим позицию стартовой вершины в графе
    int startPosition = FindVertex(startVertex);
    // Если вершина не найдена, бросаем исключение
    if (startPosition == -1) {
       throw out_of_range("Вершина не найдена в графе.");
    }
    // Создаем массив для отслеживания посещенных вершин
    vector<bool> visited(vertexList.size(), false);
    // Определяем функцию dfs, которая принимает позицию вершины
    function<void(int)> dfs = [&](int position) {
      // Помечаем вершину как посещенную
      visited[position] = true;
      // Выводим вершину на экран
      cout << vertexList[position] << " ";
      // Для всех соседних вершин, которые еще не были посещены, вызываем функцию dfs рекурсивно
      for (int i = 0; i < vertexList.size(); ++i) {
         if (!visited[i]) {
            double weight = 0.0;
            if (position > i) { weight = edge[position][i]; }
            else if (position < i) { weight = edge[i][position]; }
            if (weight != 0.0) { dfs(i); }
         }
      }
    };
    // Вызываем функцию dfs для стартовой вершины
    dfs(startPosition);
    cout << endl;
  }

  // BreadthFirstSearch: алгоритм обхода в ширину (Breadth-First Search, BFS) для графа.
  // Бросает исключение out_of_range если вершина не существует 
  void BreadthFirstSearch(const T& startVertex) const {
     // Находим позицию стартовой вершины в графе
     int startPosition = FindVertex(startVertex);
     // Если вершина не найдена, бросаем исключение
     if (startPosition == -1) {
        throw out_of_range("Вершина не найдена в графе.");
     }
     // Создаем массив для отслеживания посещенных вершин и очередь для хранения вершин,
     // которые нужно посетить.
     vector<bool> visited(vertexList.size(), false);
     queue<int> queue;
     // Помечаем стартовую вершину как посещенную и добавляем ее в очередь
     queue.push(startPosition);
     visited[startPosition] = true;
     // Пока очередь не пуста, выполняем следующие действия
     while (!queue.empty()) {
       // Извлекаем вершину из очереди и выводим ее на экран
       int position = queue.front();
       queue.pop();
       cout << vertexList[position] << " ";
       // Для всех соседних вершин, которые еще не были посещены, помечаем их как посещенные и добавляем их в очередь
         for (int i = 0; i < vertexList.size(); ++i) {
            if (!visited[i]) {
               double weight = 0.0;
               if (position > i) { weight = edge[position][i]; }
               else if (position < i) { weight = edge[i][position]; }
               if (weight != 0.0) {
                   queue.push(i);
                   visited[i] = true;
               }
            }
         }
     }
     cout << endl;
  }

  // Алгоритм Дейкстры применяется для поиска кратчайшего пути между двумя вершинами
  // в графе с невзвешенными или положительно взвешенными ребрами. 
  // Бросает исключение out_of_range если вершина не существует.
  vector<double> MinimumPath1(const T& startVertex, const T& endVertex) const {
     // Находим позиции стартовой и конечной вершин в графе
     int startPosition = FindVertex(startVertex);
     int endPosition = FindVertex(endVertex);
     // Если одна или обе вершины не найдены, бросаем исключение
     if (startPosition == -1 || endPosition == -1) {
        throw out_of_range("Одна или обе вершины не найдены в графе.");
     }
     // Инициализируем расстояния до всех вершин как бесконечность
     vector<double> distances(vertexList.size(), numeric_limits<double>::infinity());
     // Исключение: расстояние до стартовой вершины равно 0
     distances[startPosition] = 0.0;
     // Создаем приоритетную очередь (тип хранимого значения, в чем хранить, компаратор (по возрастанию))
     // для хранения вершин с минимальным расстоянием.
     priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> queue;
     // Добавляем стартовую вершину в очередь
     queue.push({ 0.0, startPosition });
     // Повторяем следующие шаги до тех пор, пока не будут посещены все вершины
     while (!queue.empty()) {
       // Извлекаем вершину с минимальным расстоянием из очереди
       double distance = queue.top().first;
       int position = queue.top().second;
       queue.pop();
       // Если мы достигли конечной вершины, возвращаем расстояния
       if (position == endPosition) { return distances; }
       // Для всех соседних вершин рассчитываем новое расстояние
       for (int j = 0; j < vertexList.size(); ++j) {
          // Получаем вес ребра между текущей вершиной и соседней вершиной
          double weight = 0.0;
          if (position > j) { weight = edge[position][j]; }
          else if (position < j) { weight = edge[j][position]; }
          // Если ребро существует (т.е. вес не равен 0)
          if (weight != 0.0) {
             // Рассчитываем новое расстояние до соседней вершины
             double newDistance = distance + weight;
             // Если новое расстояние меньше текущего расстояния, обновляем его
             if (newDistance < distances[j]) {
                distances[j] = newDistance;
                // Добавляем соседнюю вершину в очередь
                queue.push({ newDistance, j });
             }
          }
       }
     }
     // Если мы не смогли найти путь до конечной вершины, бросаем исключение
     throw out_of_range("Путь между вершинами не найден.");
  }

  // Метод печати матрицы смежности
  void printedge() const {
    cout << " " << setw(9);
    for (const T& name : vertexList) { cout << name << setw(8) << " "; }
    cout << endl;
    for (size_t i = 0; i < edge.size(); i++) {
       cout << vertexList[i] << setw(8) << " ";
       for (size_t j = 0; j < i; j++) { cout << edge[i][j] << setw(8) << " "; }
       for (size_t j = i; j < edge[i].size(); j++) { cout << "0" << setw(8) << " "; }
       cout << endl;
    }
  }

  // Метод обновления ребра между вершинами.
  // Бросает исключение out_of_range если вершина не существует 
  void updateEdge(const T& startVertex, const T& endVertex, double weight) {
    int startPosition = FindVertex(startVertex);
    int endPosition = FindVertex(endVertex);
    if (startPosition == -1 || endPosition == -1) {
       throw out_of_range("Одна или обе вершины не найдены в графе.");
    }
    if (startPosition > endPosition) { swap(startPosition, endPosition); }
    edge[endPosition][startPosition] = weight;
  }

  // Метод поиска всех путей между двумя вершинами.
  // Бросает исключение out_of_range если вершина не существует 
  void findAllPaths(const T& startVertex, const T& endVertex) const {
    // Находим позиции стартовой и конечной вершин в графе
    int startPosition = FindVertex(startVertex);
    int endPosition = FindVertex(endVertex);
    // Если одна или обе вершины не найдены, бросаем исключение
    if (startPosition == -1 || endPosition == -1) {
       throw out_of_range("Одна или обе вершины не найдены в графе.");
    }
    // Создаем массив для отслеживания посещенных вершин
    vector<bool> visited(vertexList.size(), false);
    // Создаем вектор для хранения пути
    vector<T> path;
    // Определяем функцию dfs, которая выполняет поиск в глубину
    function<void(int)> dfs = [&](int position) {
       // Помечаем вершину как посещенную
       visited[position] = true;
       // Добавляем вершину в путь
       path.push_back(vertexList[position]);
       // Если вершина является конечной, выводим путь
       if (position == endPosition) {
         for (const auto& vertex : path) { cout << vertex << " "; }
            cout << endl;
       }
       else {
          // Для всех соседних вершин, которые еще не были посещены, вызываем функцию dfs
          for (int i = 0; i < vertexList.size(); ++i) {
             if (!visited[i]) {
                double weight = 0.0;
                if (position > i) { weight = edge[position][i]; }
                else if (position < i) { weight = edge[i][position]; }
                if (weight != 0.0) { dfs(i); }
             }
          }
       }
       // Удаляем вершину из пути и помечаем ее как непосещенную
       path.pop_back();
       visited[position] = false;
    };
    // Вызываем функцию dfs для стартовой вершины
    dfs(startPosition);
  }

  // Метод вычисления степени вершины
  int getVertexDegree(const T& vertex) const {
     int position = FindVertex(vertex);
     if (position == -1) {
        throw out_of_range("Вершина не найдена в графе.");
     }
     int degree = 0;
     for (int i = 0; i < vertexList.size(); ++i) {
        if (i != position) {
           double weight = 0.0;
           if (position > i) { weight = edge[position][i]; }
           else if (position < i) { weight = edge[i][position]; }
           if (weight != 0.0) { degree++; }
        }
     }
     return degree;
  }

  // Метод вычисления суммы весов ребер
  double getEdgesWeightSum() const {
     double sum = 0.0;
     for (int i = 0; i < vertexList.size(); ++i) {
        for (int j = 0; j < i; ++j) { sum += edge[i][j]; }
     }
     return sum;
  }

  // Функция сохраняет граф в GraphML-формате в указанный файл Graph.GraphML
  void SaveGraph(const string& filename) const {
     ofstream file(filename);
     if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи.");
     }
     file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
     file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"" << endl;
     file << "         xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl;
     file << "         xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns" << endl;
     file << "         http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">" << endl;
     file << "  <key id=\"weight\" for=\"edge\" attr.name=\"weight\" attr.type=\"double\"\/>" << endl;
     file << "  <key id=\"label\" for=\"node\" attr.name=\"label\" attr.type=\"string\"\/>" << endl;
     // Описание графа
     file << "  <graph id=\"graph\" edgedefault=\"undirected\">" << endl;
     // Вершины
     for (size_t i = 0; i < vertexList.size(); ++i) {
        file << "    <node id=\"" << i << "\">" << endl;
        file << "      <data key=\"label\">" << vertexList[i] << "</data>" << endl;
        file << "    </node>" << endl;
     }
     // Ребра
     for (size_t i = 0; i < vertexList.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
           if (edge[i][j] != 0.0) {
              file << "    <edge id=\"" << i << "_" << j << "\" source=\"" << i << "\" target=\"" << j << "\" weight=\"" << edge[i][j] << "\">" << endl;
              file << "      <data key=\"weight\">" << edge[i][j] << "</data>" << endl;
              file << "    </edge>" << endl;
           }
        }
     }
     file << "  </graph>" << endl;
     file << "</graphml>" << endl;
     file.close();
  }
  
  //Тестирование класса Graph
  static void testGraph() {
     // Тестирование пустого графа
     Graph<string> emptyGraph;
     emptyGraph.printvertexList();
     emptyGraph.printEdges();
     assert(emptyGraph.NumberOfEdges() == 0);
     assert(emptyGraph.NumberOfVertices() == 0);
     try {
         emptyGraph.updateEdge("A", "B", 3.0);
         assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
       // Если исключение было отправлено, assert не сработает
     }
     try {
        emptyGraph.findAllPaths("A", "B");
        assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
       // Если исключение было отправлено, assert не сработает
     }
     try {
        emptyGraph.getVertexDegree("A") == 1;
        assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
        // Если исключение было отправлено, assert не сработает
     }
     emptyGraph.getEdgesWeightSum() == 0;
     try {
        emptyGraph.MinimumPath1("A", "B");
        assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
        // Если исключение было отправлено, assert не сработает
     }
     try {
        emptyGraph.DepthFirstSearch("A");
        assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
        // Если исключение было отправлено, assert не сработает
     }
     try {
        emptyGraph.BreadthFirstSearch("A");
        assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
        // Если исключение было отправлено, assert не сработает
     }
     // Тестирование несвязного графа
     Graph<string> disconnectedGraph;
     disconnectedGraph.InsertVertex("A");
     disconnectedGraph.InsertVertex("B");
     disconnectedGraph.InsertVertex("C");
     disconnectedGraph.InsertVertex("D");
     assert(disconnectedGraph.NumberOfEdges() == 0);
     assert(disconnectedGraph.NumberOfVertices() == 4);
     try {
        disconnectedGraph.MinimumPath1("A", "C");
        assert(false); // Если исключение не было отправлено, assert сработает
     }
     catch (const out_of_range& e) {
        // Если исключение было отправлено, assert не сработает
     }
     disconnectedGraph.DepthFirstSearch("A");
     disconnectedGraph.BreadthFirstSearch("A");
     disconnectedGraph.findAllPaths("A", "C");
     assert(disconnectedGraph.getVertexDegree("A") == 0);
     assert(disconnectedGraph.getEdgesWeightSum() == 0);
     // Тестирование связного графа
     Graph<string> connectedGraph;
     connectedGraph.InsertVertex("A");
     connectedGraph.InsertVertex("B");
     connectedGraph.InsertVertex("C");
     connectedGraph.InsertVertex("D");
     connectedGraph.InsertEdge("A", "B", 2.0);
     connectedGraph.InsertEdge("B", "C", 3.0);
     connectedGraph.InsertEdge("C", "D", 1.0);
     connectedGraph.InsertEdge("D", "A", 4.0);
     assert(connectedGraph.NumberOfEdges() == 4);
     assert(connectedGraph.NumberOfVertices() == 4);
     // Должен вызываться без исключений
     try {
        connectedGraph.MinimumPath1("A", "C");
     }
     catch (const out_of_range& e) {
        assert(false); // Если исключение было отправлено, assert сработает
     }
     try {
        connectedGraph.DepthFirstSearch("A");
     }
     catch (const out_of_range& e) {
        assert(false); // Если исключение было отправлено, assert сработает
     }
     try {
        connectedGraph.BreadthFirstSearch("A");
     }
     catch (const out_of_range& e) {
        assert(false); // Если исключение было отправлено, assert сработает
     }
     connectedGraph.updateEdge("A", "B", 3.0);
     connectedGraph.findAllPaths("A", "C");
     assert(connectedGraph.getVertexDegree("A") == 2);
     assert(connectedGraph.getEdgesWeightSum() == 11.0);
     cout << "------------------------------------" << endl;
     cout << "Все тесты пройдены успешно." << endl;
  }
};