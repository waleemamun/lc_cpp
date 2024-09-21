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
#include <cstdlib>
#include "list.h"
using namespace std;

// revlist from [start,end)
ListNode* revFromTo(ListNode *st, ListNode* end){
    ListNode* cur = st->next;
    ListNode* prev = st;
    while (cur!=end) {
        ListNode* nextNode = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nextNode;
    }
    st->next = end;
    return prev;
}

// revlist from [start,end)
// this will reverse node from start untill end, so end is not inclusive
// the pointer refernce *&p and *&c are use to point the prev and cur pointer of the called 
// to the new prev and cur after reverse
ListNode* revFromTo(ListNode *st, ListNode* end, ListNode *&p, ListNode *&c){
    ListNode* cur = st->next;
    ListNode* prev = st;
    while (cur!=end) {
        ListNode* nextNode = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nextNode;
    }
    st->next = end;
    c = end;
    p = st;
    return prev;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1) return head;
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* cur = head;
    ListNode* prev = dummy, *bStart = nullptr; // this is the node that points before start
    int count = 0;
    while (cur!=nullptr) {
        count = count % k;
        if (count == k-1){ //last node
            bStart->next = revFromTo(bStart->next, cur->next, prev, cur);
        } else {
            if (count == 0) // fast node
                bStart = prev;
            prev = prev->next;
            cur = cur->next;
        }
        count++;
    }
    return dummy->next;
}

// LC 82
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* dummy = new ListNode(-101);
    dummy->next = head;
    ListNode* cur = head, *prev = dummy;
    while(cur!=nullptr){
        int count = 0;
        int cval = cur->val;
        while(cur!= nullptr && cval == cur->val){
            count++;
            cur = cur->next;
        }
        if (count == 1){
            prev = prev->next;
        } else {
            prev->next = cur;
        }
    }
    return dummy->next;
}

// same solution as above only difference is we are actually deleting the nodes that was removed from the list 
// for C/C++ we need our own memory management to delete this nodes;
ListNode* deleteDuplicates2(ListNode* head) {
    ListNode* dummy = new ListNode(-101);
    dummy->next = head;
    ListNode* cur = head, *prev = dummy;
    while(cur!=nullptr){
        int count = 0;
        while(cur->next!= nullptr && cur->next->val == cur->val){
            count++;
            ListNode* dn = cur;
            cur = cur->next;
            delete dn;
        }
        if (count == 0){
            prev = prev->next;
        } else {
            prev->next = cur->next;
        }
        cur = cur->next;
    }
    return dummy->next;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* prev = dummy, *cur = head;
    ListNode *bStart = nullptr, *end = nullptr;
    int count = 1;
    while (cur!=nullptr && count<=right){
        if (count>=left) {    
            if (count == left) {
                bStart = prev;
            }
            ListNode* nn = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nn;
        } else {
            cur = cur->next;
            prev = prev->next;
        }
        count++;
    }
    end = bStart->next;
    end->next = cur;
    bStart->next = prev;
    return dummy->next;    
}

// The idea here is find the middle of the list and then for the 2nd half reverse the list by adding it 
// to another dummy2 head (adding to dummy head reverse a list)
// after the we have the 1st half pointed by dummy1 & reversed 2nd half pointed by dummy2
// now the next step is to stich the node of dummy1 & dummy2 one at a time
void reorderList(ListNode* head) {
    if (!head) return;
    ListNode* dummy1 = new ListNode();
    ListNode* dummy2 = new ListNode();
    dummy1->next = head;
    ListNode* slow = head, *fast = head->next;
    // find mid node
    while(fast!=nullptr && fast->next!=nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = nullptr;
    // reverse the second half
    while(fast != nullptr){
        ListNode* ls = dummy2->next;
        dummy2->next = fast;
        fast = fast->next;
        dummy2->next->next = ls;
    }
    //stich the node from dummy1 and dummy2
    slow = dummy1->next;
    fast = dummy2->next;
    while (slow != nullptr) {
        ListNode *s1= slow->next;
        ListNode *f1 = fast->next;
        slow->next = fast;
        fast->next = s1;
        slow = s1;
        fast = f1;
    }
}

ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
    ListNode* dummy = new ListNode(0);
    ListNode* prev = dummy, *cur = list1;
    ListNode* last = list2, *aPrev = nullptr; // last will point to end list2
    dummy->next = list1;
    int count = 0;
    
    while(last->next!=nullptr) {
        last = last->next;
    }
    
    while (cur!=nullptr && count <=b) {
        if (count == a)
            aPrev = prev;
        cur = cur->next;
        prev = prev->next;
        count++;
    }
    
    aPrev->next = list2;
    last->next = cur;
    return dummy->next;
}


int main(){
    return 0;
}