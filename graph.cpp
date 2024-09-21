#include <stdio.h>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include "tree.h"
using namespace std;

unordered_map<int, vector<int>> buildGraph(vector<vector<int>> &edges){
    unordered_map<int, vector<int>> graph;
    for (auto &edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    return graph;
}

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};
    queue<int> q;
    vector<int> res;

    unordered_map<int, unordered_set<int>> graph;
    for (auto &edge : edges) {
        graph[edge[0]].insert(edge[1]);
        graph[edge[1]].insert(edge[0]);
    }
    for (auto &[u, adjU] : graph) {
        if(adjU.size() == 1)
            q.push(u);
    }
    while (n>2 && q.size()!=0) {
        int sz = q.size();
        n -= sz;
        for (int i = 0; i<sz; i++) {
            int u = q.front();
            q.pop();
            if (!graph[u].empty()){
                int v = *(graph[u].begin());
                graph[v].erase(u);
                if (graph[v].size()==1) 
                    q.push(v);
            }
        }
    }

    while (!q.empty()){
        res.push_back(q.front());
        q.pop();
    }
    return res;
    
}

int main(){
    return 0;
}