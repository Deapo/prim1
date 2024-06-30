//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

const int maxn = 1001;

int n, m;
vector<pair<int, int>> a[maxn]; // danh sach ke
bool used[maxn]; // used[i] = true: i thuoc  V(MST), used[i] = false: i thuoc V()
int parent[maxn], d[maxn]; // parent: luu dinh goc, d: luu trong so cua dinh chua duoc them vao MST

struct canh {
    int x, y, w;
};

void readFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> n >> m;
        for (int i = 0; i < m; i++) {
            int x, y, w;
            file >> x >> y >> w;
            a[x].push_back({ y, w });
            a[y].push_back({ x, w });
        }
        file.close();
    }
    else {
        cerr << "Mo file that bai";
        exit(1);
    }
    memset(used, false, sizeof(used)); // Dat tat ca cac dinh thuoc V
    for (int i = 0; i <= n; i++) 
    {
        d[i] = INT_MAX;
    }
}

void prim(int u) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> T;
    vector<canh> MST;
    int cd = 0;
    T.push({ 0, u });

    while (!T.empty()) {
        pair<int, int> top = T.top();
        T.pop();
        int v = top.second;
        int w = top.first;

        if (used[v]) 
        {
            continue;
        }

        cd += w;
        used[v] = true;

        if (u != v) {
            MST.push_back({ v, parent[v], w });
        }

        // duyet tat ca cac canh ke 
        for (auto ck : a[v]) {
            int u = ck.first, weight = ck.second;
            if (!used[u] && weight < d[u]) {
                T.push({ weight, u });
                d[u] = weight;
                parent[u] = v;
            }
        }
    }
    cout << cd << endl;
    for (auto ck : MST) {
        cout << ck.x << " " << ck.y << " " << ck.w << endl;
    }
}

int main() {
    string filename;
    int x, y;
    cout << "Nhap ten file: ";
    cin >> filename;
    cout << "Nhap canh(x, y) can dua vao MST: ";
    cin >> x >> y;

    readFile(filename);
    prim(6);

    return 0;
}
