#include <bits/stdc++.h>
using namespace std;

// A structure to represent a weighted edge in the graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a connected, directed, and weighted graph
struct Graph {
    int V, E;          // Number of vertices and edges
    struct Edge* edge; // Array of edges
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// A utility function to print the solution
void printArr(int dist[], int n) {
    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < n; ++i) {
        cout << i << "\t\t" << dist[i] << endl;
    }
}

// The Bellman-Ford algorithm
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    // Print the calculated shortest distances
    printArr(dist, V);
}

int main() {
    int V, E;
    // User input for number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Create a graph with V vertices and E edges
    struct Graph* graph = createGraph(V, E);

    // User input for each edge
    for (int i = 0; i < E; i++) {
        cout << "Enter source, destination, and weight of edge " << i + 1 << ": ";
        cin >> graph->edge[i].src >> graph->edge[i].dest >> graph->edge[i].weight;
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    // Function call
    BellmanFord(graph, src);

    // Clean up memory
    delete[] graph->edge;
    delete graph;

    return 0;
}
