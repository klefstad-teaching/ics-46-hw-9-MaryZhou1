#include "dijkstras.h"


int main() {
    Graph G;
    string filename = "small.txt";
    file_to_graph(filename, G);


    int source;
    cout << "Enter source: ";
    cin >> source;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    // cout << "Shortest distances from vertex " << source << ":\n";
    // for (size_t i = 0; i < distances.size(); i++) {
    //     cout << "To " << i << ": " << (distances[i] == INF ? "INF" : to_string(distances[i])) << endl;
    // }
    int destination;
    cout << "Enter destination vertex: ";
    cin >> destination;

    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}
