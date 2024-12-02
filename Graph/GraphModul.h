/// GraphModul.h - ������� ����� ����� � �������������� ������ ��������� ��� ������������� ���� ����� ���������. 
#pragma once
#include <iostream>   /// ��������� cin cout.
#include <vector>     /// ������� �������.
#include <string>     /// ��� ������ �� ��������.
#include <limits>     /// ���������� �������� ����������� ������������� �����.
#include <queue>      /// ������� � ���������, ������� �������� �� �������� FIFO (������� ����� � ������ �����).
#include <functional> /// ����� �������� ������� ��� ������ � ��������������� ���������.
#include <iomanip>    /// ��������� ��������� ���������� �������������� ������.
#include <sstream>    /// ��� ����������� ������ �� �������� ����� ��������� �������.
#include <fstream>    /// ���������� ������� ���� ��� ������ � ������ ������.
#include <cassert>    /// ��� assert.
#include <locale>     /// ���������� ������� setlocale ��� ��������� ������� ������.
#include <algorithm>  /// ��� remove, find, distance.
#include <stack>      /// ���������� stack ����� ��� �������� ��������: push, pop, � ����� peek.
using namespace std;

// ������������ ���������� ������ � ����� (������������ ��������� �����)
//const int MaxGraphSize = 25;
// ��������� ����� ����������� �����
template <typename T>
class Graph {
private:
  vector<T> vertexList; // ������ ������ �����
  vector<vector<double>> edge; // ������� ���������. ���������� ������� � ��� ����� ����� ���������.
  int graphsize; // ������� ���������� ������ � �����
public:

  // ����������� ������ Graph
  Graph() {}
  
  // ����������
  ~Graph() {}
  
  // ����� ������ ������� � ������.
  // ���� ������� ������, ���������� ��� ������, ����� -1.
  int FindVertex(const T& vertex) const {
     for (int i = 0; i < vertexList.size(); ++i) {
        if (vertexList[i] == vertex) { return i; }
     }
     return -1; // ������� �� �������.
  }
  
  // ����� ������ ������� ������� � ������
  int GetVertexPos(const T& vertex) const {
     return FindVertex(vertex);
  }

  // GraphEmpty: �������� �� �������
  int GraphEmpty() const { return graphsize == 0; }

  // GraphFull: �������� �� ��������
  int GraphFull() const { return graphsize == vertexList.size(); }

  // GetWeight: ��������� ���� ����� ����� ����� ��������� � �����
  int GetWeight(const T& vertex1, const T& vertex2) {
    int i = FindVertex(vertex1); // ������������ ����� ������� ������ ������� � �����
    int j = FindVertex(vertex2); // ������������ ����� ������� ������ ������� � �����
    // ���������, ��� ��� ������� ������� � ����� � ���������� ��� ����� ����� ���������� ���������
    if (i != -1 && j != -1) return edge[i][j];
    return 0; // ���� ���� �� ���� �� ������ �� �������, ���������� 0
  }

  // InsertVertex: ��������� ����� �������.
  // ������� ���������� out_of_range ���� ������� ����������.
  void InsertVertex(const T& vertex) {
    if (FindVertex(vertex) != -1) {
       throw out_of_range("������� ��� ���������� � �����.");
    }
    int newSize = vertexList.size() + 1;
    vertexList.push_back(vertex);
    // ���������� ������� ���������
    if (edge.empty()) {
      edge.resize(newSize, vector<double>(newSize, 0.0));
    }
    else {
      for (auto& row : edge) { row.resize(newSize, 0.0); }
      edge.resize(newSize, vector<double>(newSize, 0.0));
    }
  }

  // DeleteVertex: ������� �������, � ����� ��� ��������� � ��� ����.
  // ������� ���������� out_of_range ���� ������� �� ����������.
  void DeleteVertex(const T& vertex) {
    int position = FindVertex(vertex);
    if (position == -1) {
      throw out_of_range("������� �� ������� � �����.");
    }
    vertexList.erase(vertexList.begin() + position);
    // ���������� ������� ���������
    edge.erase(edge.begin() + position);
    for (int i = 0; i < vertexList.size(); ++i) {
       edge[i].erase(edge[i].begin() + position);
    }
  }

  // InsertEdge: ��������� ����� ����� ����� ����� ���������
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  void InsertEdge(const T& vertex1, const T& vertex2, double weight) {
    int position1 = FindVertex(vertex1);
    int position2 = FindVertex(vertex2);
    if (position1 == -1 || position2 == -1) {
      throw out_of_range("���� ��� ��� ������� �� ������� � �����.");
    }
    if (position1 > position2) { swap(position1, position2); }
    edge[position2][position1] = weight;
  }

  // DeleteEdge: ������� ����� ����� ����� ���������.
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  void DeleteEdge(const T& vertex1, const T& vertex2) {
    int position1 = FindVertex(vertex1);
    int position2 = FindVertex(vertex2);
    if (position1 == -1 || position2 == -1) {
      throw out_of_range("���� ��� ��� ������� �� ������� � �����.");
    }
    if (position1 > position2) { swap(position1, position2); }
    edge[position2][position1] = 0.0;
  }

  // GetAdjacentvertexList: ����� �������� ������ ������� ������.
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  vector<T> GetAdjacentvertexList(const T& vertex) const {
    int position = FindVertex(vertex);
    if (position == -1) {
      throw out_of_range("���� ��� ��� ������� �� ������� � �����.");
    }
    vector<T> adjacentvertexList;
    for (int i = 0; i < vertexList.size(); ++i) {
      if (edge[position][i] != 0.0) {
         adjacentvertexList.push_back(vertexList[i]);
      }
    }
    return adjacentvertexList;
  }

  // ����� ������ ������ ������
  void printvertexList() const {
     cout << "������ ������: ";
     for (const auto& vertex : vertexList) { cout << vertex << " "; }
     cout << endl;
  }

  // ����� ������ ������ �����
  void printEdges() const {
    cout << "������ �����: ";
    for (int i = 0; i < vertexList.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (edge[i][j] != 0.0) {
          cout << vertexList[i] << " - " << vertexList[j] << " (���: " << edge[i][j] << ") ";
        }
      }
    }
    cout << endl;
  }

  // ����� ����������� ���������� �����
  int NumberOfEdges() const {
    int edgeCount = 0;
    for (int i = 0; i < vertexList.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (edge[i][j] != 0.0) { edgeCount++; }
      }
    }
    return edgeCount;
  }

  // ����� ����������� ���������� ������
  int NumberOfVertices() const { return vertexList.size(); }
  
  // DepthFirstSearch: �������� ������ � ������� (DFS) ��� �����,
  // ������� � ��������� �������.
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  void DepthFirstSearch(const T& startVertex) const {
    // ������� ������� ��������� ������� � �����
    int startPosition = FindVertex(startVertex);
    // ���� ������� �� �������, ������� ����������
    if (startPosition == -1) {
       throw out_of_range("������� �� ������� � �����.");
    }
    // ������� ������ ��� ������������ ���������� ������
    vector<bool> visited(vertexList.size(), false);
    // ���������� ������� dfs, ������� ��������� ������� �������
    function<void(int)> dfs = [&](int position) {
      // �������� ������� ��� ����������
      visited[position] = true;
      // ������� ������� �� �����
      cout << vertexList[position] << " ";
      // ��� ���� �������� ������, ������� ��� �� ���� ��������, �������� ������� dfs ����������
      for (int i = 0; i < vertexList.size(); ++i) {
         if (!visited[i]) {
            double weight = 0.0;
            if (position > i) { weight = edge[position][i]; }
            else if (position < i) { weight = edge[i][position]; }
            if (weight != 0.0) { dfs(i); }
         }
      }
    };
    // �������� ������� dfs ��� ��������� �������
    dfs(startPosition);
    cout << endl;
  }

  // BreadthFirstSearch: �������� ������ � ������ (Breadth-First Search, BFS) ��� �����.
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  void BreadthFirstSearch(const T& startVertex) const {
     // ������� ������� ��������� ������� � �����
     int startPosition = FindVertex(startVertex);
     // ���� ������� �� �������, ������� ����������
     if (startPosition == -1) {
        throw out_of_range("������� �� ������� � �����.");
     }
     // ������� ������ ��� ������������ ���������� ������ � ������� ��� �������� ������,
     // ������� ����� ��������.
     vector<bool> visited(vertexList.size(), false);
     queue<int> queue;
     // �������� ��������� ������� ��� ���������� � ��������� �� � �������
     queue.push(startPosition);
     visited[startPosition] = true;
     // ���� ������� �� �����, ��������� ��������� ��������
     while (!queue.empty()) {
       // ��������� ������� �� ������� � ������� �� �� �����
       int position = queue.front();
       queue.pop();
       cout << vertexList[position] << " ";
       // ��� ���� �������� ������, ������� ��� �� ���� ��������, �������� �� ��� ���������� � ��������� �� � �������
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

  // �������� �������� ����������� ��� ������ ����������� ���� ����� ����� ���������
  // � ����� � ������������� ��� ������������ ����������� �������. 
  // ������� ���������� out_of_range ���� ������� �� ����������.
  vector<double> MinimumPath1(const T& startVertex, const T& endVertex) const {
     // ������� ������� ��������� � �������� ������ � �����
     int startPosition = FindVertex(startVertex);
     int endPosition = FindVertex(endVertex);
     // ���� ���� ��� ��� ������� �� �������, ������� ����������
     if (startPosition == -1 || endPosition == -1) {
        throw out_of_range("���� ��� ��� ������� �� ������� � �����.");
     }
     // �������������� ���������� �� ���� ������ ��� �������������
     vector<double> distances(vertexList.size(), numeric_limits<double>::infinity());
     // ����������: ���������� �� ��������� ������� ����� 0
     distances[startPosition] = 0.0;
     // ������� ������������ ������� (��� ��������� ��������, � ��� �������, ���������� (�� �����������))
     // ��� �������� ������ � ����������� �����������.
     priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> queue;
     // ��������� ��������� ������� � �������
     queue.push({ 0.0, startPosition });
     // ��������� ��������� ���� �� ��� ���, ���� �� ����� �������� ��� �������
     while (!queue.empty()) {
       // ��������� ������� � ����������� ����������� �� �������
       double distance = queue.top().first;
       int position = queue.top().second;
       queue.pop();
       // ���� �� �������� �������� �������, ���������� ����������
       if (position == endPosition) { return distances; }
       // ��� ���� �������� ������ ������������ ����� ����������
       for (int j = 0; j < vertexList.size(); ++j) {
          // �������� ��� ����� ����� ������� �������� � �������� ��������
          double weight = 0.0;
          if (position > j) { weight = edge[position][j]; }
          else if (position < j) { weight = edge[j][position]; }
          // ���� ����� ���������� (�.�. ��� �� ����� 0)
          if (weight != 0.0) {
             // ������������ ����� ���������� �� �������� �������
             double newDistance = distance + weight;
             // ���� ����� ���������� ������ �������� ����������, ��������� ���
             if (newDistance < distances[j]) {
                distances[j] = newDistance;
                // ��������� �������� ������� � �������
                queue.push({ newDistance, j });
             }
          }
       }
     }
     // ���� �� �� ������ ����� ���� �� �������� �������, ������� ����������
     throw out_of_range("���� ����� ��������� �� ������.");
  }

  // ����� ������ ������� ���������
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

  // ����� ���������� ����� ����� ���������.
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  void updateEdge(const T& startVertex, const T& endVertex, double weight) {
    int startPosition = FindVertex(startVertex);
    int endPosition = FindVertex(endVertex);
    if (startPosition == -1 || endPosition == -1) {
       throw out_of_range("���� ��� ��� ������� �� ������� � �����.");
    }
    if (startPosition > endPosition) { swap(startPosition, endPosition); }
    edge[endPosition][startPosition] = weight;
  }

  // ����� ������ ���� ����� ����� ����� ���������.
  // ������� ���������� out_of_range ���� ������� �� ���������� 
  void findAllPaths(const T& startVertex, const T& endVertex) const {
    // ������� ������� ��������� � �������� ������ � �����
    int startPosition = FindVertex(startVertex);
    int endPosition = FindVertex(endVertex);
    // ���� ���� ��� ��� ������� �� �������, ������� ����������
    if (startPosition == -1 || endPosition == -1) {
       throw out_of_range("���� ��� ��� ������� �� ������� � �����.");
    }
    // ������� ������ ��� ������������ ���������� ������
    vector<bool> visited(vertexList.size(), false);
    // ������� ������ ��� �������� ����
    vector<T> path;
    // ���������� ������� dfs, ������� ��������� ����� � �������
    function<void(int)> dfs = [&](int position) {
       // �������� ������� ��� ����������
       visited[position] = true;
       // ��������� ������� � ����
       path.push_back(vertexList[position]);
       // ���� ������� �������� ��������, ������� ����
       if (position == endPosition) {
         for (const auto& vertex : path) { cout << vertex << " "; }
            cout << endl;
       }
       else {
          // ��� ���� �������� ������, ������� ��� �� ���� ��������, �������� ������� dfs
          for (int i = 0; i < vertexList.size(); ++i) {
             if (!visited[i]) {
                double weight = 0.0;
                if (position > i) { weight = edge[position][i]; }
                else if (position < i) { weight = edge[i][position]; }
                if (weight != 0.0) { dfs(i); }
             }
          }
       }
       // ������� ������� �� ���� � �������� �� ��� ������������
       path.pop_back();
       visited[position] = false;
    };
    // �������� ������� dfs ��� ��������� �������
    dfs(startPosition);
  }

  // ����� ���������� ������� �������
  int getVertexDegree(const T& vertex) const {
     int position = FindVertex(vertex);
     if (position == -1) {
        throw out_of_range("������� �� ������� � �����.");
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

  // ����� ���������� ����� ����� �����
  double getEdgesWeightSum() const {
     double sum = 0.0;
     for (int i = 0; i < vertexList.size(); ++i) {
        for (int j = 0; j < i; ++j) { sum += edge[i][j]; }
     }
     return sum;
  }

  // ������� ��������� ���� � GraphML-������� � ��������� ���� Graph.GraphML
  void SaveGraph(const string& filename) const {
     ofstream file(filename);
     if (!file.is_open()) {
        throw runtime_error("�� ������� ������� ���� ��� ������.");
     }
     file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
     file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"" << endl;
     file << "         xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl;
     file << "         xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns" << endl;
     file << "         http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">" << endl;
     file << "  <key id=\"weight\" for=\"edge\" attr.name=\"weight\" attr.type=\"double\"\/>" << endl;
     file << "  <key id=\"label\" for=\"node\" attr.name=\"label\" attr.type=\"string\"\/>" << endl;
     // �������� �����
     file << "  <graph id=\"graph\" edgedefault=\"undirected\">" << endl;
     // �������
     for (size_t i = 0; i < vertexList.size(); ++i) {
        file << "    <node id=\"" << i << "\">" << endl;
        file << "      <data key=\"label\">" << vertexList[i] << "</data>" << endl;
        file << "    </node>" << endl;
     }
     // �����
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
  
  //������������ ������ Graph
  static void testGraph() {
     // ������������ ������� �����
     Graph<string> emptyGraph;
     emptyGraph.printvertexList();
     emptyGraph.printEdges();
     assert(emptyGraph.NumberOfEdges() == 0);
     assert(emptyGraph.NumberOfVertices() == 0);
     try {
         emptyGraph.updateEdge("A", "B", 3.0);
         assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
       // ���� ���������� ���� ����������, assert �� ���������
     }
     try {
        emptyGraph.findAllPaths("A", "B");
        assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
       // ���� ���������� ���� ����������, assert �� ���������
     }
     try {
        emptyGraph.getVertexDegree("A") == 1;
        assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
        // ���� ���������� ���� ����������, assert �� ���������
     }
     emptyGraph.getEdgesWeightSum() == 0;
     try {
        emptyGraph.MinimumPath1("A", "B");
        assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
        // ���� ���������� ���� ����������, assert �� ���������
     }
     try {
        emptyGraph.DepthFirstSearch("A");
        assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
        // ���� ���������� ���� ����������, assert �� ���������
     }
     try {
        emptyGraph.BreadthFirstSearch("A");
        assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
        // ���� ���������� ���� ����������, assert �� ���������
     }
     // ������������ ���������� �����
     Graph<string> disconnectedGraph;
     disconnectedGraph.InsertVertex("A");
     disconnectedGraph.InsertVertex("B");
     disconnectedGraph.InsertVertex("C");
     disconnectedGraph.InsertVertex("D");
     assert(disconnectedGraph.NumberOfEdges() == 0);
     assert(disconnectedGraph.NumberOfVertices() == 4);
     try {
        disconnectedGraph.MinimumPath1("A", "C");
        assert(false); // ���� ���������� �� ���� ����������, assert ���������
     }
     catch (const out_of_range& e) {
        // ���� ���������� ���� ����������, assert �� ���������
     }
     disconnectedGraph.DepthFirstSearch("A");
     disconnectedGraph.BreadthFirstSearch("A");
     disconnectedGraph.findAllPaths("A", "C");
     assert(disconnectedGraph.getVertexDegree("A") == 0);
     assert(disconnectedGraph.getEdgesWeightSum() == 0);
     // ������������ �������� �����
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
     // ������ ���������� ��� ����������
     try {
        connectedGraph.MinimumPath1("A", "C");
     }
     catch (const out_of_range& e) {
        assert(false); // ���� ���������� ���� ����������, assert ���������
     }
     try {
        connectedGraph.DepthFirstSearch("A");
     }
     catch (const out_of_range& e) {
        assert(false); // ���� ���������� ���� ����������, assert ���������
     }
     try {
        connectedGraph.BreadthFirstSearch("A");
     }
     catch (const out_of_range& e) {
        assert(false); // ���� ���������� ���� ����������, assert ���������
     }
     connectedGraph.updateEdge("A", "B", 3.0);
     connectedGraph.findAllPaths("A", "C");
     assert(connectedGraph.getVertexDegree("A") == 2);
     assert(connectedGraph.getEdgesWeightSum() == 11.0);
     cout << "------------------------------------" << endl;
     cout << "��� ����� �������� �������." << endl;
  }
};