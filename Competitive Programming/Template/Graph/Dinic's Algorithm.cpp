#include<bits/stdc++.h>
using namespace std;

/*
Used for Max-flow/min-cut
Time Complexity:- O(n^2*m)

Alternatively can be used for:-
Minimum number of edges required to be removed to disconnect source from sink i.e. capacity=1 for all edges.
Time Complexity:- O(m*root(m))  [Only when all edges have same/unit capacity]

Link:- https://cp-algorithms.com/graph/dinic.html

How to give input?
As shown in the main function.
*/

struct Edge {
    int to, capacity, flow, rev_index;
};

void addEdge(vector<vector<Edge>> &graph, int from, int to, int capacity) {
    Edge forward_edge = {to, capacity, 0, static_cast<int>(graph[to].size())};
    Edge reverse_edge = {from, 0, 0, static_cast<int>(graph[from].size())};

    graph[from].push_back(forward_edge);
    graph[to].push_back(reverse_edge);
}

bool BFS(vector<vector<Edge>> &graph, vector<int> &level, int source, int sink) {
    fill(level.begin(), level.end(), -1);
    level[source] = 0;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (const Edge &edge : graph[current]) {
            if (level[edge.to] < 0 && edge.flow < edge.capacity) {
                level[edge.to] = level[current] + 1;
                q.push(edge.to);
            }
        }
    }

    return (level[sink] >= 0);
}

int DFS(vector<vector<Edge>> &graph, vector<int> &next_edge, vector<int> &level, int current, int sink, int min_capacity) {
    if (current == sink)
        return min_capacity;

    for (int &i = next_edge[current]; i < graph[current].size(); ++i) {
        Edge &edge = graph[current][i];

        if (level[edge.to] == level[current] + 1 && edge.flow < edge.capacity) {
            int new_min_capacity = min(min_capacity, edge.capacity - edge.flow);
            int flow = DFS(graph, next_edge, level, edge.to, sink, new_min_capacity);

            if (flow > 0) {
                edge.flow += flow;
                graph[edge.to][edge.rev_index].flow -= flow;
                return flow;
            }
        }
    }

    return 0;
}

int dinicMaxFlow(vector<vector<Edge>> &graph, int source, int sink) {
    int vertices = graph.size();
    vector<int> level(vertices, 0);
    vector<int> next_edge(vertices, 0);

    int max_flow = 0;

    while (BFS(graph, level, source, sink)) {
        fill(next_edge.begin(), next_edge.end(), 0);

        int flow;
        while ((flow = DFS(graph, next_edge, level, source, sink, INT_MAX)) > 0) {
            max_flow += flow;
        }
    }

    return max_flow;
}

int main() {
    int n,m;
    cin >> m >> m;

    vector<vector<Edge>> graph(n);

    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        addEdge(graph, from, to, capacity);
    }

    int source, sink;
    cin >> source >> sink;

    int maxFlow = dinicMaxFlow(graph, source, sink);

    cout << "Maximum Flow: " << maxFlow << endl;

    return 0;
}

