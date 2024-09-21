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


template<typename T>
void printSet(const std::set<T>& s) {
    printf("print tree set\n");
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void printContainer(const T& container, const std::string& name) {
    std::cout << name << " contents: ";
    auto temp = container;
    while (!temp.empty()) {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}

int height(TreeNode* root){
    if (root==nullptr) return 0;
    return 1+std::max(height(root->left), height(root->right)); 
}

void levelBottomRec(TreeNode* root, vector<vector<int>> &rlist, int level){
    if (root == nullptr)
        return;
    rlist.at(level).push_back(root->val);
    levelBottomRec(root->left, rlist, level-1);
    levelBottomRec(root->right, rlist, level -1);
}
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    int h = height(root);
    vector<vector<int>> rlist(h,vector<int>{});
    if (root == nullptr)
        return rlist;
    levelBottomRec(root, rlist, h-1);
    return rlist;
}

void pathSumRec(TreeNode* root, int targetSum, vector<vector<int>> &rlist, vector<int> &tlist){
    if(root == nullptr) // we cannot use the check targetSum < 0 as targetSum can be negative for this problem
        return;
    tlist.push_back(root->val);
    if (root->left ==nullptr && root->right==nullptr && targetSum - root->val == 0) {        
        rlist.push_back(vector<int>(tlist));
        tlist.pop_back();
        return;
    }
    pathSumRec(root->left, targetSum - root->val, rlist, tlist);
    pathSumRec(root->right, targetSum - root->val, rlist, tlist);
    tlist.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

    vector<vector<int>> rlist;
    vector<int> tlist;
    pathSumRec(root, targetSum, rlist, tlist);
    return rlist;
}

int main() {

    array<int, 6> arr = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) {
        printf("%d\n", arr[i]);
    }
    int n = 6;
    vector<int> vec(n);
    vec.insert(vec.begin() ,1);
    for (int i = 0; i < n; i++) {
        vec[i] = i;
        printf("%d\n", vec[i]);
    }
    vec.pop_back();
    printf("vec pop\n");
    for (int a: vec) {
        printf("vc = %d\n", a);
    }
    // Define an ordered map with a lambda function as custom comparator
    auto caseInsensitiveCompare = [](const std::string& a, const std::string& b) {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](char c1, char c2) { return std::tolower(c1) > std::tolower(c2); }
        );
    };
    
    map<string, int, decltype(caseInsensitiveCompare)> treeMap(caseInsensitiveCompare);
    treeMap["one"] = 1;
    treeMap["two"] = 2;
    treeMap["THree"] = 3;
    for (const auto& key: treeMap) {
        cout << key.first << " :: " << key.second << endl;
    }

    unordered_map<string, int> hashMap;
    hashMap["apple"] = 1;
    hashMap["orrange"] = 2;
    hashMap["ice"] = 3;

    for (const auto& key: hashMap) {
        cout << key.first << " == " << key.second << endl;
    }
    if (hashMap.find("apple") != hashMap.end()) {
        cout << "apple found" << endl;
    }
    if (treeMap.find("three")!= treeMap.end()) {
        cout << "three found" << endl;
    }

    if (hashMap.find("kaka") == hashMap.end()) {
        cout << "kaka not found" << endl;
    }
    hashMap.insert({"kaka",4});
    if (hashMap.find(("kaka"))!= hashMap.end() ) {
        cout << "kaka found" << endl;
    }
    int tArray[] = {5, 2, 18, 1, 9, 20, 8}; 
    int hArray[] = {5, 2, 8, 1, 9, 2, 8}; 

    auto revcmp = [](int a, int b) { return a > b; };
    set<int> treeSet(begin(tArray), end(tArray));
    set<int, decltype(revcmp)> treeSet1(vec.begin(), vec.end(), revcmp);
    unordered_set<int> hashSet(begin(hArray), end(hArray));
    printSet(treeSet);
    printf("tree set rev \n");
    for (auto& elem: treeSet1) {
        cout << elem << " ";
    }
    printf("\nhash set\n");
    for (auto& elem: hashSet) {
        cout << elem << " ";
    }
    stack<int> stk;
    for (int i = 0; i < 5; i++) {
        stk.push(i);
    }
    printf("\nstack\n");
    while(!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }

    queue<int> que;
    
    for (int i = 0; i < 5; i++) {
        que.push(i);
    }
    printf("\nqueue\n");
    while(!que.empty()) {
        cout << que.front() << " ";
        que.pop();
    }

    deque<int> deq;
    for (int i = 0; i < 5; i++) {
        deq.push_back(i);

    }

    for (int i = 10; i < 15; i++) {
        deq.push_front(i);
    }
    printf("\ndeque\n");
    for (const auto& elem: deq) {
        cout << elem << " ";
    }
    printf("\ndeque pop\n");
    while(!deq.empty()) {
        cout << deq.front() << " " << deq.back() << " ";
        deq.pop_front();
        deq.pop_back();
    }

    printf("array vec sort\n");
    vector<int> vc1(begin(tArray), end(tArray));
    sort(vc1.begin(), vc1.end(), [](int a, int b) { return a > b; });
    for (const auto& v: vc1) {
        cout << v << " ";
    }
    printf("\npriority queue\n");
    priority_queue<int> pq (vc1.begin(), vc1.end());
    pq.push(200);

    while(!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    printf("\npriority queue min heap\n");
    priority_queue<int, vector<int>, greater<int>> minHeap(vc1.begin(), vc1.end());
    minHeap.push(0);
    while(!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    // vc1.insert(vc1.begin() + 20, -100);
    // cout<<vc1[20]<< " res"<< endl;

    printf("\nHello World\n"); 
    return 0;
}