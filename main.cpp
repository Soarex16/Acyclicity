#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#define UNVISITED 0
#define PROCESSING 1
#define VISITED 2

using namespace std;

long long counter = 0;

bool dfs(const std::vector<std::vector<int>>& graph, vector<int>& colors, int v) {
    counter += 2;
    if (colors[v] == PROCESSING) {
        return true;
    }

    counter += 2;
    colors[v] = PROCESSING;
    for (int i = 0; i < graph[v].size(); ++i) {
        counter += 4;
        if (colors[graph[v][i]] != VISITED) {
            counter += 3;
            if (dfs(graph, colors, graph[v][i]))
                return true;
            counter += 4;
            colors[graph[v][i]] = VISITED;
        }
    }

    counter += 2;
    colors[v] = VISITED;
    return false;
}

bool acyclic(const std::vector<std::vector<int>>& graph) {
    vector<int> colors(graph.size(), UNVISITED);

    int i;
    for (i = 0; i < graph.size(); ++i) {
        if (dfs(graph, colors, i))
            break;
        colors.resize(graph.size(), UNVISITED);
    }

    counter += 1;
    return (i == graph.size());
}

int main() {
    vector<vector<int>> graph;

    cout << "Enter file path: ";
    std::string path;
    cin >> path;
    ifstream f(path);

    if (!f) {
        cout << "Error while opening file!" << endl;
        return -1;
    }

    clock_t fileReadBegin = clock();

    int n, e;
    //cout << "Enter number of vertices in graph: ";
    f >> n;
    graph.resize(n);

    //cout << "Enter number of edges in graph: ";
    f >> e;
    //cout << "Enter edges (Vi, Vj): " << endl;
    for (int i = 0; i < e; ++i) {
        int a, b;
        f >> a >> b;

        graph[a].push_back(b);
    }

    clock_t fileReadEnd = clock();

    cout << "Graph was successfully read from file. Reading time: " << double(fileReadEnd - fileReadBegin) /
        CLOCKS_PER_SEC << " secs." << endl;

    clock_t begin = clock();
    cout << "Is graph acyclic: " << acyclic(graph) << " (1 - y, 0 - n)" << endl;
    clock_t end = clock();
    cout << "Elapsed time in second: " << double(end - begin) / CLOCKS_PER_SEC << endl;

    cout << "Total operations: " << counter << endl;
    system("pause");
}