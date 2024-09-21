#include <stdio.h>
#include "dts.h"
#include <iostream>
#include <queue>
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

int main()
{
    MedianFinder mc;
    for (int i = 1; i<10;i++){
        mc.addNum(i);
        printf("i = %d median = %f\n", i, mc.findMedian());
    }
    return 0;

}
