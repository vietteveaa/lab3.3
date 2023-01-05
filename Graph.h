#include <iostream>
#include <algorithm> // for reverse
#include <functional> // for function
#include <limits> // for numeric_limits
#include <set> // for set and pair comparison function
#include <utility> // for pair
#include <vector> // for vector

using namespace std;

template <typename T>
class Graph {
    int numVertices;
    vector<vector<pair<int, int>>> adjList;
    vector<T> vertices;
public:
    Graph(int numVertices) : numVertices(numVertices), adjList(numVertices) {}

    void addVertex(const T &vertex) {
        vertices.push_back(vertex);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(v, weight));
    }

    int getNumVertices() const {
        return numVertices;
    }

    T getVertex(int index) const {
        if (index < 0 || index >= vertices.size()) {
            throw invalid_argument("Vertex not found");
        }
        return vertices[index];
    }

    pair<int, int> getEdge(int u, int v) const {
        for (pair<int, int> p: adjList[u]) {
            if (p.first == v) {
                return p;
            }
        }
        throw invalid_argument("Edge not found");
    }

    const vector<vector<pair<int, int>>> &getAdjList() const {
        return adjList;
    }

    const vector<T> &getVertices() const {
        return vertices;
    }

    void print() const {
        for (int i = 0; i < numVertices; i++) {
            cout << vertices[i] << ": ";
            for (pair<int, int> p: adjList[i]) {
                cout << "(" << vertices[p.first] << ", " << p.second << ") ";
            }
            cout << endl;
        }
    }

    vector<pair<int, int>> dijkstra(int source) {
        set<pair<int, int>> vertexSet;
        vector<int> dist(numVertices, numeric_limits<int>::max());
        vector<int> pred(numVertices, -1);
        dist[source] = 0;
        vertexSet.insert(make_pair(0, source));
        while (!vertexSet.empty()) {
            int u = vertexSet.begin()->second;
            vertexSet.erase(vertexSet.begin());
            for (pair<int, int> p: adjList[u]) {
                int v = p.first;
                int weight = p.second;
                if (dist[v] > dist[u] + weight) {
                    vertexSet.erase(make_pair(dist[v], v));
                    dist[v] = dist[u] + weight;
                    pred[v] = u;
                    vertexSet.insert(make_pair(dist[v], v));
                }
            }
        }
        vector<pair<int, int>> res;
        for (int i = 0; i < pred.size(); i++) {
            res.push_back(make_pair(i, pred[i]));
        }
        return res;
    }

    vector<int> bellmanFord(int source) {
        vector<int> dist(numVertices, numeric_limits<int>::max());
        vector<int> pred(numVertices, -2);
        dist[source] = 0;
        pred[source] = -1;
        for (int i = 0; i < numVertices - 1; i++) {
            for (int u = 0; u < numVertices; u++) {
                for (pair<int, int> p: adjList[u]) {
                    int v = p.first;
                    int weight = p.second;
                    if (dist[v] > dist[u] + weight) {
                        dist[v] = dist[u] + weight;
                        pred[v] = u;
                    }
                }
            }
        }
        for (int u = 0; u < numVertices; u++) {
            for (pair<int, int> p: adjList[u]) {
                int v = p.first;
                int weight = p.second;
                if (dist[v] > dist[u] + weight) {
                    cout << "Graph contains a negative weight cycle" << endl;
                    return {};
                }
            }
        }
        return dist;
    }

    vector<vector<int>> floydWarshall() {
        vector<vector<int>> dist(numVertices, vector<int>(numVertices, numeric_limits<int>::max()));
        for (int i = 0; i < numVertices; i++) {
            dist[i][i] = 0;
        }
        for (int u = 0; u < numVertices; u++) {
            for (pair<int, int> p: adjList[u]) {
                int v = p.first;
                int weight = p.second;
                dist[u][v] = weight;
            }
        }
        for (int k = 0; k < numVertices; k++) {
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max()) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }

    vector<int> topologicalSort() {
        vector<int> topologicalOrder;
        set<int> visited;
        function<void(int)> dfs = [&](int u) {
            visited.insert(u);
            for (pair<int, int> p : adjList[u]) {
                int v = p.first;
                if (visited.find(v) == visited.end()) {
                    dfs(v);
                }
            }
            topologicalOrder.push_back(u);
        };
        for (int i = 0; i < numVertices; i++) {
            if (visited.find(i) == visited.end()) {
                dfs(i);
            }
        }
        reverse(topologicalOrder.begin(), topologicalOrder.end());
        return topologicalOrder;
    }
};