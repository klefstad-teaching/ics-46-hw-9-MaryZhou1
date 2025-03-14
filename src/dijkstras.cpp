#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF); // Initialize distances with INF
    previous.assign(n, -1); // Stores the previous node in the shortest path

    // Min-heap priority queue (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distance[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.emplace(distance[v], v);
            }
        }
    }

    return distance;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path; // No path exists
    }

    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end()); // Reverse to get correct order
    return path;
}


void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found" << endl;
        return;
    }
    cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal cost: " << total << endl;
}


