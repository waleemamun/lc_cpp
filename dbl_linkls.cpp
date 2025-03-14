#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Node {
    public:
        int data;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
    public:
    Node() : data(0) {}
    Node(int val) : data(val) {}
};

class DblLinkList {
    public:
        std::shared_ptr<Node> head;
        std::shared_ptr<Node> tail;
        DblLinkList() {
            head = std::make_shared<Node>();
            tail = std::make_shared<Node>();
            head->next = tail;
            tail->prev = head;
        }
        void addToHead(int val) {
            auto node = std::make_shared<Node>(val);
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
        }
        void addToTail(int val) {
            auto node = std::make_shared<Node>(val);
            node->next = tail;
            node->prev = tail->prev;
            auto p = tail->prev.lock();
            p->next = node;
            tail->prev = node;
        }
        void deleteFromHead() {
            if (head->next == tail) return;
            auto node = head->next;
            head->next = node->next;
            node->next->prev = head;
            node->next = nullptr;   
        }
        void deleteFromTail() {
            if (head->next == tail) return;
            auto node = tail->prev.lock();
            tail->prev = node->prev;
            node->prev.lock()->next = tail;
            node->next = nullptr;
        }
        void deleteNode(int val) {
            auto cur = head->next;
            while(cur != tail) {
                if (cur->data == val) {
                    cur->prev.lock()->next = cur->next;
                    cur->next->prev = cur->prev;
                    cur->next = nullptr;
                    return;
                }
                cur = cur->next;
            }
        }
        void printList() {
            auto cur = head->next;
            while(cur != tail) {
                cout << cur->data << " ";
                cur = cur->next;
            }
            cout << endl;
        }
        void printReverse() {
            auto cur = tail->prev.lock();
            while(cur != head) {
                cout << cur->data << " ";
                cur = cur->prev.lock();
            }
            cout << endl;
        }
        void moveToHead(std::shared_ptr<Node> node) {
            if (node->prev.lock() == head && node->next == tail) return;
            node->prev.lock()->next = node->next;
            node->next->prev = node->prev;
        }
};

int main(){
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    DblLinkList dll;
    for (int a : arr) {
        dll.addToTail(a);
    }
    dll.printList();
    dll.printReverse();
    dll.deleteFromHead();
    dll.printList();
    dll.deleteFromTail();
    dll.printList();
    dll.deleteNode(3);
    dll.printList();
    return 0;
}
