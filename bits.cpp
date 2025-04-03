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
using namespace std;

// LC :: 201
// The idea is to find the common prefix of left and right
// we need to move all the bits to the right until left and right are equal
// thaty way all the bit that are different will be removed
// and the common prefix will be left
// then we need to move the common prefix back to the left 
int rangeBitwiseAnd(int left, int right) {
    int shift = 0;
    while (left<right){
        left>>=1;
        right>>=1;
        shift++;
    }
    return left << shift;
}

// LC :: 137
int singleNumber(vector<int>& nums) {
    int single = 0;
    for (int i = 0; i < 32; i++) {
        int sum = 0;
        for (int n : nums) {
            sum+= ((n>>i) & 0x1);
        }
        single = single | (sum%3) << i;
    }
    return single;    
}

// LC :: 136
// The idea is to use the fact that the xor of a number with itself is 0
// and the xor of a number with 0 is the number itself
// so we can xor all the numbers in the array and the result will be the single number
// for example 1^1^2^2^3 = 3
// 1^1 = 0
int singleNumber2(vector<int>& nums) {
    int single =0;
    for (int n:nums){
        single^=n;
    
    }
    return single;
        
}

// LC:: 191
// The idea is to use the fact that n & (n-1) will remove the last 1 bit
// for example 1010 & 1001 = 1000
// 1000 & 0111 = 0000
// so we can keep removing the last 1 bit until n is 0
// and count the number of times we do that
// this will give us the number of 1 bits in n
// this is also known as Brian Kernighan's algorithm
int hammingWeight(int n) {
    int count = 0;
    while (n) {
        n = n & n-1;
        count++; 
    }
    return count;
    
}

// XOR based swap
void swap(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}
// The idea is to use the fact that the msb of a number is the highest bit set
int isPowerOfTwo(int n) {
    if (n == 0)
        return 0;
    return (n & (n-1)) == 0;
}

int getMSBPosition(int n) {
    if (n == 0)
        return -1;
    return std::log2(n);
}
// The idea is to use the fact that the lsb of a number is the lowest bit set
// AND n with its 2's complement will give us the lsb bit
int getLSBPosition(int n) {
    if (n == 0)
        return -1;
    return std::log2(n & -n);
}

// n & -n will give us the lsb of n
int getLSB(int n) {
    if (n == 0)
        return 0;
    return n & -n;
}

// LC :: 190
// The idea is to use the fact that the reverse of a number is the same as the reverse of its bits
// for example 1010 = 0101

uint32_t reverseBits(uint32_t n) {
    n = ((n & 0xffff0000) >> 16) | ((n & 0xffff) << 16);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    return n;
    
}



int main() {
    vector<int> nums = {1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,7};
    int left = 5;
    int right = 7;
    cout << "rangeBitwiseAnd: " << rangeBitwiseAnd(left, right) << endl;
    cout << "singleNumber: " << singleNumber(nums) << endl;
    cout << "hammingWeight: " << hammingWeight(11) << endl;
    for (int i = 1; i < 10; i++) {
       cout<<i << " : msb =  " << static_cast<int>(log2(i)) << endl;
       cout<<i << " : lsb =  " << static_cast<int>(log2(i & -i)) << endl;
    }
    return 0;
}