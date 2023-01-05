#include <iostream>
#include "Graph.h"

void test_addVertex() {
    Graph<int> g(4);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    if (g.getVertices() == vector<int>({1, 2, 3, 4})) {
        cout << "addVertex test passed" << endl;
    } else {
        cout << "addVertex test failed" << endl;
    }
}

void test_addEdge() {
    Graph<int> g(4);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 4);
    if (g.getAdjList() == vector<vector<pair<int, int>>>{{{1, 1}}, {{2, 2}}, {{3, 3}}, {{0, 4}}}) {
        cout << "addEdge test passed" << endl;
    } else {
        cout << "addEdge test failed" << endl;
    }
}

void test_dijkstra() {
    Graph<char> g(5);
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 4);
    vector<pair<int, int>> res = g.dijkstra(0);
    bool passed = res[0].second == -1 && res[1].second == 0 && res[2].second == 0 && res[3].second == 2 && res[4].second == 3;
    cout << "dijkstra test " << (passed ? "passed" : "failed") << endl;
}

void test_bellmanFord() {
    Graph<char> g(5);
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 4);
    vector<int> res = g.bellmanFord(0);
    bool passed = res[0] == 0 && res[1] == 3 && res[2] == 1 && res[3] == 2 && res[4] == 6;
    cout << "bellmanFord test " << (passed ? "passed" : "failed") << endl;
}

void test_floydWarshall() {
    Graph<char> g(5);
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 4);
    vector<vector<int>> res = g.floydWarshall();
    bool passed = res[0][1] == 3 && res[0][2] == 1 && res[1][3] == 2 && res[2][3] == 1 && res[3][4] == 4;
    cout << "floydWarshall test " << (passed ? "passed" : "failed") << endl;
}

void test_topologicalSort() {
    Graph<int> g(6);
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addEdge(5, 2, 1);
    g.addEdge(5, 0, 1);
    g.addEdge(4, 0, 1);
    g.addEdge(4, 1, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 1, 1);
    vector<int> sortedVertices = g.topologicalSort();
    if (sortedVertices == vector<int>({5, 4, 2, 3, 1, 0})) {
        cout << "topologicalSort test passed" << endl;
    } else {
        cout << "topologicalSort test failed" << endl;
    }
}

int main() {
    test_addEdge();
    test_addVertex();
    test_dijkstra();
    test_bellmanFord();
    test_floydWarshall();
    test_topologicalSort();
    return 0;
}