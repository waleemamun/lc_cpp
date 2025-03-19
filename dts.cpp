#include <stdio.h>
#include "dts.h"
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
class MedianFinder {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        if(minHeap.size()<=maxHeap.size()){
            maxHeap.push(num);
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else {
            minHeap.push(num);
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        
    }
    
    double findMedian() {
        if((minHeap.size() + maxHeap.size()) %2 == 0){
            return (double)((minHeap.top() + maxHeap.top()))/2.0;
        } else {
            return minHeap.top();
        }
        
    }
};

// LC :: 1429

class DblLinkList {
    public:
        int key;
        int val;
        std::shared_ptr<DblLinkList> next;
        std::weak_ptr<DblLinkList> prev;
        DblLinkList() : val(0){}
        DblLinkList(int v) : val(v){}
        DblLinkList(int k, int v) : key(k), val(v){}
};

class FirstUnique {
private:
    shared_ptr<DblLinkList> head;
    shared_ptr<DblLinkList> tail;
    // lets just keep trac
    unordered_map<int, shared_ptr<DblLinkList>> nmap;
    void addToTail(int val){
        shared_ptr<DblLinkList> node = make_shared<DblLinkList>(val);
        nmap[val] = node;
        node->next = tail;
        node->prev = tail->prev;
        auto tp = tail->prev.lock();
        tp->next = node;
        tail->prev = node;
    }
public:
    
    FirstUnique(vector<int>& nums) {
        head = make_shared<DblLinkList>();
        tail = make_shared<DblLinkList>();
        head->next = tail;
        tail->prev = head;
        for (int n : nums) {
            this->add(n);
        }
    }
    
    int showFirstUnique() {
        if(head->next == tail)
            return -1;
        return head->next->val;
        
    }
    
    void add(int value) {
        if(nmap.find(value) == nmap.end()){
            addToTail(value);
        } else {
            auto node = nmap[value];
            if (node) {
                auto np = node->prev.lock();
                np->next = node->next;
                node->next->prev = np;
                node->next = nullptr;
                // remember to make the nmap point to null
                nmap[value] = nullptr;
            }
        }
        
    }
};

// LC :: 146
class LRUCache {
public:
    std::shared_ptr<DblLinkList> head;
    std::shared_ptr<DblLinkList> tail;
    int capacity;
    int size = 0;
    unordered_map<int, shared_ptr<DblLinkList>> kmap;
    LRUCache(int capacity) {
        head = make_shared<DblLinkList>();
        tail = make_shared<DblLinkList>();
        head->next = tail;
        tail->prev = head;
        this->capacity = capacity;
        size = 0;
    }
    void addToHead(shared_ptr<DblLinkList> node){
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    void moveToHead(shared_ptr<DblLinkList> node) {
        if (node->prev.lock() == head && node->next == tail) return;
        node->prev.lock()->next = node->next;
        //printf("%d \n", node->val);
        node->next->prev = node->prev;
        node->next = nullptr;
        addToHead(node);
        
    }
    void deleteFromTail(){
        if(head->next == tail) return;
        auto p = tail->prev.lock();
        auto k = p->key;
        tail->prev = p->prev;
        p->prev.lock()->next = tail;
        p->next = nullptr;
        kmap.erase(k);
    }
    
    int get(int key) {
         if (kmap.find(key) != kmap.end()) {
            auto v = kmap[key];
            moveToHead(v);
            return v->val;
         }
         return -1;
        
    }
    
    void put(int key, int value) {
        if (kmap.find(key) == kmap.end()) {
            kmap[key] = make_shared<DblLinkList>(key, value);
            addToHead(kmap[key]);
            size++;
            if (size > capacity) {
                deleteFromTail();
            }
        } else {
            std::shared_ptr<DblLinkList> v = kmap[key];
            v->val = value;
            moveToHead(v);
        }
        
    }
};

// LC :: 716 MAX Stack
// The problem ask us to solve top in O(1) and the rest in O(lgn) time which indicates we need to use either a heap or balanced binary tree
// Here we use one red black tree (rbtree) for the stack and another to handle the max of stack (Here we could use a priority_queue aka max heap)
// so the rbtree give use the peekmax at any given time with O(lgn). We use a pair of <idx,value> for the stack and <value,idx> for the rbtree 
// aka maxheap. We also keep a count of entries inserted, count is always incremented never decremented so there is a chance of overflow.
// but if we dont consider a overflow like TC then decrementing count is not needed due to keeping a pair as key for our balanced trees 
class MaxStack {
public:
    set<pair<int, int>> stk;
    set<pair<int, int>> rbtree;
    int count;

    MaxStack() {
        count = 0;
    }
    
    void push(int x) {
        stk.insert({count, x});
        rbtree.insert({x,count});
        count++;
    }
    
    int pop() {
        auto p = *stk.rbegin();
        stk.erase(p);
        rbtree.erase({p.second, p.first});
        return p.second;
    }
    
    int top() {
        return stk.rbegin()->second;
    }
    
    int peekMax() {
        return rbtree.rbegin()->first;
    }
    
    int popMax() {
        int v = rbtree.rbegin()->first;
        int i = rbtree.rbegin()->second;
        stk.erase({i,v});
        rbtree.erase({v,i});
        return v;
    }
};

// LC 622

class MyCircularQueue {
public:
    int head;
    int tail;
    vector<int> que;
    int size;
    int sk;
    MyCircularQueue(int k) {
        head = 0;
        tail = 0;
        size = 0;
        sk = k;
        que = vector<int>(k); 
    }
    
    bool enQueue(int value) {
        if (size == sk)
            return false;
        que[tail] = value;
        tail = (tail +1) % sk;
        size++;
        return true;
    }
    
    bool deQueue() {
        if (size == 0)
            return false;
        que[head] = -1;
        head = (head+1) % sk;
        size--;
        return true;
    }
    
    int Front() {
        return size == 0 ? -1 : que[head];
    }
    
    int Rear() {    
        int pos = tail == 0 ? sk -1: tail - 1;    
        return size == 0 ? -1 : que[pos];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == sk;
    }
};

class TrieNode {
    public:
        char val;
        bool hasWord;
        unordered_map<char, TrieNode*> child;
        TrieNode(char ch) : val(ch), hasWord(false) {}
};

class WordDictionary {
public:
    TrieNode* root;
    WordDictionary() {
        root = new TrieNode('#');
        
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for(char w: word) {
            if(!node->child.count(w)) {
                TrieNode* nd = new TrieNode(w);
                node->child[w] = nd;
            }
            node = node->child[w];
        }
        node->hasWord = true;
    }
    bool searchRec(TrieNode* node, string word, int index) {
        if (node && index == word.size()) 
            return node->hasWord;
        char ch = word[index];
        if (ch != '.') {
            if (!node->child.count(ch)) return false;
            return searchRec(node->child[ch], word, index + 1);
        }
        for (auto &nd : node->child) {
            if (searchRec(nd.second, word, index + 1))
                return true;
        }
        return false;
    }
    bool search(string word) {

        return searchRec(root, word, 0);
    }
};

class Node {
    public:
        int val;
        vector<Node*> children;
    
        Node() {}
    
        Node(int _val) {
            val = _val;
        }
    
        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
    };

// LC :: 589
vector<int> preorder(Node* root) {
    if (!root) return {};
    stack<Node*> stk;
    vector<int> rlist;
    stk.push(root);
    while (!stk.empty()){
        root = stk.top();
        rlist.push_back(root->val);
        stk.pop();
        while(root->children.size()!=0){
            stk.push(root->children.back());
            root->children.pop_back();
        }
    }
    return rlist;
}

int main()
{
    MedianFinder mc;
    for (int i = 1; i<10;i++){
        mc.addNum(i);
        printf("i = %d median = %f\n", i, mc.findMedian());
    }
    return 0;

}
