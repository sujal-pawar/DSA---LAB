#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// Class to represent graph using adjacency matrix for DFS and adjacency list for BFS
class Graph {
public:
    map<char, vector<char>> adjList; // For BFS (Adjacency list)
    int adjMatrix[5][5];  // For DFS (Adjacency matrix)
    map<char, int> nodeIndex; // Map landmarks to index for matrix

    // Constructor to initialize the node indices for the adjacency matrix
    Graph() {
        nodeIndex['A'] = 0;
        nodeIndex['B'] = 1;
        nodeIndex['C'] = 2;
        nodeIndex['D'] = 3;
        nodeIndex['E'] = 4;
    }

    // Add edge for adjacency list (BFS)
    void addEdgeList(char u, char v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // Undirected graph
    }

    // Add edge for adjacency matrix (DFS)
    void addEdgeMatrix(char u, char v) {
        adjMatrix[nodeIndex[u]][nodeIndex[v]] = 1;
        adjMatrix[nodeIndex[v]][nodeIndex[u]] = 1; // Undirected graph
    }

    // Depth First Search (DFS) using adjacency matrix
    void DFS(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << char(node + 'A') << " ";  // Convert index back to character

        // Visit all adjacent nodes
        for (int i = 0; i < 5; ++i) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    // Breadth First Search (BFS) using adjacency list
    void BFS(char start) {
        map<char, bool> visited;
        queue<char> q;
        
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            char node = q.front();
            q.pop();
            cout << node << " ";

            for (auto neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    Graph g;

    // Add edges for adjacency matrix (DFS)
    g.addEdgeMatrix('A', 'B');
    g.addEdgeMatrix('A', 'C');
    g.addEdgeMatrix('B', 'D');
    g.addEdgeMatrix('C', 'E');

    // Add edges for adjacency list (BFS)
    g.addEdgeList('A', 'B');
    g.addEdgeList('A', 'C');
    g.addEdgeList('B', 'D');
    g.addEdgeList('C', 'E');

    // DFS starting from 'A' (College Gate)
    cout << "DFS Traversal starting from College Gate (A): ";
    vector<bool> visited(5, false);
    g.DFS(0, visited); // 'A' is index 0 in the matrix
    cout << endl;

    // BFS starting from 'A' (College Gate)
    cout << "BFS Traversal starting from College Gate (A): ";
    g.BFS('A');
    cout << endl;

    return 0;
}
