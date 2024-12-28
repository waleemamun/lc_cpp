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

// LC :: 148

ListNode* mergeList(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode();
    ListNode* prev = dummy;
    while(l1 && l2) {
        if(l1->val <= l2->val){
            prev->next = l1;
            l1 = l1->next;
        } else {
            prev->next = l2;
            l2 = l2->next;
        }
        prev = prev->next;
    }
    prev->next = (l1 == nullptr) ? l2:l1;
    return dummy->next; 
}

ListNode* mergeSort(ListNode* head){
    if(head == nullptr || head->next == nullptr)
        return head;
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* nextHead = slow->next;
    slow->next = nullptr;
    ListNode *l1 = mergeSort(head);
    ListNode *l2 = mergeSort(nextHead);
    return mergeList(l1, l2);
}

ListNode* sortList(ListNode* head) {
    return mergeSort(head);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* l1, ListNode* l2) {return l1->val > l2->val;};
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minHeap(cmp);
    for (auto ls : lists){
        if(ls)
            minHeap.push(ls);
    }
    ListNode *dummy = new ListNode();
    ListNode *cur = dummy;
    while(!minHeap.empty()){
        ListNode* temp = minHeap.top();
        minHeap.pop();
        if (temp->next)
            minHeap.push(temp->next);
        cur->next = temp;
        cur = cur->next;
    }
    return dummy->next;
}

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList(Node* head) {
    Node* dummy = new Node(-1);
    Node* cp = dummy;
    Node* cur = head;
    // stich orig node next to point to the copy list node
    // each orig node next pointer points to their deep copy 
    // and the new deep copy node points to the orig next node
    while(cur) {
        Node* n = new Node(cur->val);
        n->next = cur->next;
        cur->next = n;
        cur = n->next;
    }

    cur = head;
    // now adjust the random pointers
    while (cur) {
        if (cur->random) {
            cur->next->random = cur->random->next;
        }
        cur = cur->next->next;
    }
    cur = head;
    while(cur) {
        Node *nc = cur->next->next;
        cp->next = cur->next;
        cp = cp->next;
        cur->next = nc;
        cur = nc;
    }

    return dummy->next;

    
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *cur = head;
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    while(cur && n) {
        cur = cur->next;
        n--;
    }
    ListNode *prev = cur ? head : dummy;
    while(cur && cur->next) {
        prev = prev->next;
        cur = cur->next;
    }
    ListNode *nx = prev->next;
    prev->next = nx->next;
    
    return dummy->next;
}

ListNode* rotateRight(ListNode* head, int k) {
    int n = 0;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *cur = head, *end = dummy; 
    while(cur) {
        n++;
        cur = cur->next;
        end = end->next;
    }
    if (n == 0 || k%n == 0) return head;
    k = k % n;
    k = n - k -1;
    cur = head;
    while(cur && k--) {
        cur = cur->next;
    }
    end->next = dummy->next;
    dummy->next = cur->next;
    cur->next = nullptr;
    return dummy->next;    
}

ListNode* partition(ListNode* head, int x) {
    ListNode* dmSm = new ListNode();
    ListNode* dmBg = new ListNode();
    ListNode *psm = dmSm, *pbg = dmBg;
    ListNode *cur = head;
    while (cur) {
        if (cur->val < x) {
            psm->next = cur;
            psm = psm->next;
        } else {
            pbg->next = cur;
            pbg = pbg->next;
        }
        cur = cur->next;
    }
    pbg->next = nullptr;
    psm->next = dmBg->next;
    return dmSm->next; 
}

// LC :: 237

void deleteNode(ListNode* node) {
    ListNode *nn = node->next;
    node->val = nn->val;
    node->next = nn->next;
    delete nn;
}

// LC :: 725

vector<ListNode*> splitListToParts2(ListNode* head, int k) {
    ListNode *cur = head;
    int n = 0;
    while (cur) {
        n++;
        cur = cur->next;
    }
    cur = head;
    int rem  = n % k;
    int div = n / k;

    vector<int> counts(k, div);
    vector<ListNode*> res(k,nullptr);
    int i = 0;
    while(rem-- != 0) counts[i++]++;
    i = 0;
    for (int c : counts) {
        if (c == 0) break;
        ListNode dummy;
        dummy.next = cur;
        while (--c && cur) cur = cur->next;
        res[i++] = dummy.next;
        if (cur){
            ListNode* nn = cur;
            cur = cur->next;
            nn->next = nullptr;
        }
    }
    return res;
}

vector<ListNode*> splitListToParts(ListNode* head, int k) {
    ListNode *cur = head;
    int n = 0;
    while (cur) {
        n++;
        cur = cur->next;
    }
    cur = head;
    int rem  = n % k;
    int div = n / k;
    vector<ListNode*> res;
    int i = 0;
    while(k) {
        ListNode dummy;
        dummy.next = cur;
        int sz = div;
        if (rem-- > 0)
            sz++;
        while (--sz && cur) cur = cur->next;
        res.push_back(dummy.next);
        if (cur){
            ListNode* nn = cur;
            cur = cur->next;
            nn->next = nullptr;
        }
        k--;
    }
    return res;
}

// LC :: 2058
vector<int> nodesBetweenCriticalPoints(ListNode* head) {
    vector<int> res = {-1,-1};
    if(!head) return res;
    ListNode* prev = head;
    ListNode* cur = head->next;
    int i = 1;
    #define CRT_MAX_VAL 200000
    int low = CRT_MAX_VAL;
    int high = 0;
    int minDist = CRT_MAX_VAL;
    int lastIdx = -1;
    while(cur){
        if(cur->next) {
            if((prev->val < cur->val && cur->val > cur->next->val) ||
                (prev->val > cur->val && cur->val < cur->next->val)) {
                low = std::min(low, i);
                high = std::max(high, i);
                if(lastIdx != -1) {
                    minDist = std::min(minDist, i -lastIdx);
                }
                lastIdx = i;
            }
        }
        prev = prev->next;
        cur = cur->next;
        i++;
    }
    if (low == high || minDist == CRT_MAX_VAL) return res;

    res[1] = high - low;
    res[0] = minDist;

    return res;
}


int main(){
    return 0;
}