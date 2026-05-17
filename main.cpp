#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int a, b;
    long long cost;
};

class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) {
            return false;
        }

        if (rank[rootA] < rank[rootB]) {
            swap(rootA, rootB);
        }

        parent[rootB] = rootA;

        if (rank[rootA] == rank[rootB]) {
            rank[rootA]++;
        }

        return true;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    sort(edges.begin(), edges.end(), [](Edge x, Edge y) {
        return x.cost < y.cost;
    });

    DSU dsu(n);

    long long totalCost = 0;
    int selectedEdges = 0;

    for (Edge edge : edges) {
        if (dsu.unite(edge.a, edge.b)) {
            totalCost += edge.cost;
            selectedEdges++;
        }
    }

    if (selectedEdges == n - 1) {
        cout << totalCost << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}