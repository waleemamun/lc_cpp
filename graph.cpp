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
#include <list>
#include <functional>
#include <numeric>
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

// LC :: 200

void visitIsland(vector<vector<char>>& grid, int i, int j){
    if (i < 0 || i >= grid.size() 
        || j < 0 || j >= grid[0].size() 
        || grid[i][j] != '1')
        return;
    grid[i][j] = '*';
    visitIsland(grid, i + 1, j);
    visitIsland(grid, i - 1, j);
    visitIsland(grid, i, j - 1);
    visitIsland(grid, i, j + 1);
}

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if (grid[i][j] == '1') {
                visitIsland(grid, i, j);
                count++;
            }
        }
    }
    return count;
}

// LC :: 130
void solveRec(vector<vector<char>>& board,int i, int j){
    if (i < 0 || i >= board.size() 
        || j < 0 || j >= board[0].size() 
        || board[i][j] != 'O')
        return;
    board[i][j] = 'B';
    solveRec(board, i + 1, j);
    solveRec(board, i - 1, j);
    solveRec(board, i, j - 1);
    solveRec(board, i, j + 1);
}

void solve(vector<vector<char>>& board) {

    for (int i = 0; i < board[0].size(); i++){
        if (board[0][i] == 'O')
            solveRec(board, 0, i);
        if (board[board.size()-1][i] == 'O')
            solveRec(board, board.size() -1, i);

    }
    for (int i = 0; i < board.size(); i++){
        if (board[i][0] == 'O')
            solveRec(board, i, 0);
        if (board[i][board[0].size()-1] == 'O')
            solveRec(board, i, board[0].size()-1);
    }
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            if(board[i][j] == 'O')
                board[i][j] = 'X';
            if(board[i][j] == 'B')
                board[i][j] = 'O';
        }
    }    
}

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// LC :: 133 clone graph
Node* cloneGraph(Node* node) {
    if (node == nullptr)
        return nullptr;
    Node *start = new Node(node->val);
    queue<Node*> que;
    unordered_map<int, Node*> hmap;
    que.push(node);
    hmap[node->val] = start;
    while(!que.empty()) {
        Node *a = que.front();
        que.pop();
        Node *c = hmap[a->val];
        for (Node *n : a->neighbors){
            if (hmap.find(n->val) == hmap.end()) {
                hmap[n->val] = new Node(n->val);
                que.push(n);
            }
            c->neighbors.push_back(hmap[n->val]);   
        }
    }
    return start;
    
}

// LC :: 207
bool dfsCF(int u, unordered_map<int, vector<int>> &graph, vector<int> &color){
    vector<int> &adjacency = graph[u];
    color[u] = 1;
    for (int v: adjacency) {
        if(color[v] == 1)
            return false;
        else if(color[v] == 0) {
            if(!dfsCF(v,graph, color))
                return false;
        }
    }
    color[u] = 2;
    return true;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    unordered_map<int, vector<int>> graph;
    
    for (auto p: prerequisites){
        graph[p[1]].push_back(p[0]);
    }
    vector<int> color(numCourses, 0);
    // build the dfs forest
    for (int u = 0; u <numCourses; u++){
        if (color[u] != 0)
            continue;
        if (dfsCF(u, graph, color) == false)
            return false;
    }
    return true;
}

// LC :: 210
bool dfsFO(int u, unordered_map<int, vector<int>> &graph, vector<int> &color, list<int> &res){
    color[u] = 1;
    vector<int> adjacency = graph[u];
    for(int v : adjacency){
        if (color[v] == 1)
            return false;
        else if (color[v] == 0) {
            if (!dfsFO(v, graph, color, res))
                return false;
        }
    }
    res.push_front(u);
    color[u] = 2;
    return true;

}
vector<int> findOrder2(int numCourses, vector<vector<int>>& prerequisites) {
    unordered_map<int, vector<int>> graph; 
    for (auto p: prerequisites){
        graph[p[1]].push_back(p[0]);
    }
    vector<int> color(numCourses, 0);
    list<int> res;
    for (int u = 0; u < numCourses; u++) {
        if (color[u] == 0) {
            if (!dfsFO(u, graph, color, res)){
                return vector<int> ();
            }
        }
    }
    vector<int> order;
    for (int r: res){
        order.push_back(r);
    }
    return order;
}
// same with BFS topological sort
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    unordered_map<int, vector<int>> graph;
    vector<int> indegree(numCourses, 0);
    queue<int> que;
    for (auto p: prerequisites) {
        graph[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }
    for (int i = 0; i<numCourses; i++) {
        if (indegree[i] == 0)
            que.push(i);
    }
    int visitCount = 0;
    vector<int> res;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        visitCount++;
        res.push_back(u);
        vector<int> adjacency = graph[u];
        for (int v : adjacency) {
            indegree[v]--;
            if(indegree[v] == 0)
                que.push(v);
        }
    }
    return visitCount == numCourses ? res: vector<int> ();
}

// findset operation with path compression
int findSet(int x, vector<int> &parent) {
    if (x == parent[x])
        return x;
    parent[x] = findSet(parent[x], parent);
    return parent[x];
}
// union aka merge operation
void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
    int pu = findSet(u, parent);
    int pv = findSet(v, parent);
    if (pu != pv){
        if (rank[pu] >= rank[pv]) {
            if(rank[pu] == rank[pv])
                rank[pu]++;
            parent[pv] = pu;
        } else {
            parent[pu] = pv;
        } 
    }
} 

int countComponents(int n, vector<vector<int>>& edges) {
    vector<int> parent(n,0);
    vector<int> rank(n,0);
    // make set; make n unique set
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    // find & union
    for (auto e : edges) {
        if (findSet(e[0], parent) != findSet(e[1], parent)){
            n--;
            unionSet(e[0], e[1], parent, rank);
        }
    }
    return n;
    
}

// LC :: 1319

int makeConnected(int n, vector<vector<int>>& connections) {
    if (connections.size() < n -1)
        return -1;
    vector<int> parent(n, 0);
    vector<int> rank(n, 0);
    // make set
    for(int i = 0; i < n; i++) {
        parent[i] = i;
    }
    // find & union to create the SCC
    for (auto c : connections) {
        if (findSet(c[0], parent) != findSet(c[1], parent)) {
            n--;
            unionSet(c[0], c[1], parent, rank);
        }
    }
    return n - 1;
}

void dfsAM(string u, unordered_map<string, vector<string>> &adjacency, unordered_set<string> &visited, vector<string> &res){
    visited.insert(u);
    for (string v : adjacency[u]) {
        if (visited.count(v) == 0) {
            dfsAM(v, adjacency, visited, res);
        }
    }
    res.push_back(u);
}
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, vector<string>> graph;
    unordered_set<string> visited;

    for (vector<string> acc: accounts) {
        string  u = acc[1];
        for (int i = 2; i<acc.size(); i++) {
            graph[u].push_back(acc[i]);
            graph[acc[i]].push_back(u);
        }
    }
    vector<vector<string>> rlist;
    for (vector<string> acc: accounts) {
        string  u = acc[1];
        string name = acc[0];
        if (visited.count(u) == 0) {
            vector<string> res;
            res.push_back(name);
            dfsAM(u, graph, visited, res);
            std::sort(res.begin() + 1, res.end());
            rlist.push_back(res);
        }

    }
    return rlist;
    
}

// LC :: 332
void dfsEuler(string u, unordered_map<string, multiset<string>> &graph, list<string> &res){
    multiset<string> &adj = graph[u];
    while(adj.size()) {
        string v = *adj.begin();
        adj.erase(adj.begin());
        dfsEuler(v, graph, res);
    }
    res.push_front(u);
}

vector<string> findItinerary(vector<vector<string>>& tickets) {
    unordered_map<string, multiset<string>> graph;
    list<string> res;
    for (auto tk : tickets) {
        graph[tk[0]].insert(tk[1]);
    }
    dfsEuler("JFK", graph, res);
    vector<string> path(res.begin(), res.end());
    return path;
}

// LC :: 909 
// The idea is to use the BFS to find the src(1) to dest(n*n) distance 
// The trick here is to convert the bottom up numbering of the board to 
// actual board values as we need to start from bottom left -> bottom right 
// like snake ladder board
int snakesAndLadders(vector<vector<int>>& board) {
    int n = board.size();
    vector<pair<int, int>> cell(n*n+1);
    int val = 1;
    vector<int> col(n);
    std::iota(col.begin(), col.end(), 0);
    for (int r = n -1; r>=0; r--) {
        for (int c : col) {
            cell[val++] = {r, c};
        }
        std::reverse(col.begin(), col.end());
    }
    vector<int> dist(n*n+1, -1);
    queue<int> que;
    int u = 1;
    que.push(u);
    dist[u] = 0;
    while(!que.empty()) {
        u = que.front();
        que.pop();
        if (u == n*n)
            break;

        for (int i = u+1; i<= std::min(u+6, n*n); i++) {
            int v = i;
            auto [r,c] = cell[v];
            if (board[r][c] != -1) {
                v = board[r][c];
            }
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }

    }
    return dist[n*n];    
}

// LC :: 433

// check if the two string is one char apart
int diffCount(string s1, string s2) {
    int count = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i])
            count++;
    }
    return count;
}

// Simple BFS just need to build the graph from the bank vector 
// O(n*2) to build the graph
int minMutation(string startGene, string endGene, vector<string>& bank) {
    unordered_map<string, vector<string>> graph;
    bank.push_back(startGene);
    for (int i = 0; i < bank.size(); i++) {
        for (int j = i+1; j < bank.size(); j++) {
            if (diffCount(bank[i], bank[j]) == 1) {
                graph[bank[i]].push_back(bank[j]); 
                graph[bank[j]].push_back(bank[i]); 
            }
        }
    }
    unordered_map<string, int> dist;
    queue<string> q;
    q.push(startGene);
    dist[startGene] = 0;
    while(!q.empty()) {
        string u = q.front();
        q.pop();
        for (auto v : graph[u]) {
            if (dist.find(v) == dist.end()) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return (dist.find(endGene) != dist.end()) ? dist[endGene] : -1;    
}

int main(){
    return 0;
}