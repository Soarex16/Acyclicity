// main.cpp
// Created by Soarex16 on 25.11.2018.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

enum Colors {
  UNVISITED,
  PROCESSING,
  VISITED
};

using namespace std;

long long counter = 0;

/**
 * Depth first search for checking graph acyclicity
 * @param graph adjacency list of graph
 * @param colors vector of graph colors
 * @param v vertex considered in the current step
 * @return true if during the traversal the already visited vertex was not met
 */
bool dfs(const std::vector<std::vector<long>> &graph, vector<long> &colors, long v) {
    counter += 2;
    if (colors[v] == PROCESSING) {
        return true;
    }

    counter += 2;
    colors[v] = PROCESSING;
    for (long i = 0; i < graph[v].size(); ++i) {
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

/**
 *
 * @param graph adjacency list of graph
 * @return is graph acyclic
 */
bool acyclic(const std::vector<std::vector<long>> &graph) {
    vector<long> colors(graph.size(), UNVISITED);

    long i;
    for (i = 0; i < graph.size(); ++i) {
        if (dfs(graph, colors, i))
            break;
    }

    counter += 1;
    // if all iterations of the loop are executed, then the graph is acyclic
    return (i == graph.size());
}

int main() {
    vector<vector<long>> graph;

    cout << "Enter file path: ";
    std::string path;
    cin >> path;
    ifstream f(path);

    if (!f) {
        cout << "Error while opening file!" << endl;
        return -1;
    }

    clock_t fileReadBegin = clock();

    long n, e;
    f >> n;
    graph.resize(n);

    f >> e;
    for (long i = 0; i < e; ++i) {
        long a, b;
        f >> a >> b;

        graph[a].push_back(b);
    }

    f.close();
    clock_t fileReadEnd = clock();

    cout << "Graph was successfully read from file. Reading time: " <<
            double(fileReadEnd - fileReadBegin) / CLOCKS_PER_SEC << " secs." << endl;

    clock_t begin = clock();
    cout << "Is graph acyclic: " << acyclic(graph) << " (1 - y, 0 - n)" << endl;
    clock_t end = clock();
    cout << "Elapsed time in second: " << double(end - begin) / CLOCKS_PER_SEC << endl;

    cout << "Total operations: " << counter << endl;

    system("pause");
}