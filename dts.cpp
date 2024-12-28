#include <stdio.h>
#include "dts.h"
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <algorithm>

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
        int val;
        std::shared_ptr<DblLinkList> next;
        std::weak_ptr<DblLinkList> prev;
        DblLinkList() : val(0){}
        DblLinkList(int v) : val(v){}
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

int main()
{
    MedianFinder mc;
    for (int i = 1; i<10;i++){
        mc.addNum(i);
        printf("i = %d median = %f\n", i, mc.findMedian());
    }
    return 0;

}
