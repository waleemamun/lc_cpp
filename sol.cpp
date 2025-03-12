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
#include <sstream>
#include <list>
#include "tree.h"
using namespace std;

// LC :: 80

int removeDuplicates2(vector<int>& nums) {
    int j = 0;
    if (nums.size()== 0) return 0;
    int last = nums[0];
    nums.push_back(last);
    nums.push_back(last);
    for (int i = 0; i < nums.size(); i++){
        
        if ((nums[i] != nums[i+1] && nums[i] != nums[i+2]))
            nums[j++] = nums[i];
    }
    return j;
        
}

// use this approach as its more generic same can be used for LC :: 26
int removeDuplicates(vector<int>& nums) {
    if (nums.size()==0)
        return 0;
    int cur = 0;
    for (int i = 0; i < nums.size(); i++){
        if (i < 2 || nums[i]!= nums[cur-2])
            nums[cur++] = nums[i];
    }
    return cur;
        
}

// LC :: 26 
int removeDuplicatesEasy(vector<int>& nums) {
    int cur = 0;
    for (int i = 0; i < nums.size(); i++){
        if(i<1 ||nums[cur-1]!=nums[i])
            nums[cur++] = nums[i];
    }
    return cur;
}
// LC :: 169
int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    for (int n:nums){
        if (count == 0){
            candidate = n;
            count=1;
        } else if (candidate == n)
            count++;
        else
            count--;
    }

    count = 0;
    for (int n:nums) {
        if(n == candidate)
            count++;
    }
    if (count>nums.size()/2)
        return candidate;
    else
        return INT_MIN;
    
}

void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin()+k);
    std::reverse(nums.begin()+k, nums.end());
    
}

// LC :: 45
// Both are greedy solutions but the second one is more optimized
// just one pass solution
// The idea is to keep track of the max index we can reach from the current index
// and only update the max index when we reach the current max index and update 
// the jump count

int jump(vector<int>& nums) {
    if (nums.size()<=1) return 0;
    int jmp = 0;
    unsigned long l = 0, r;
    while(l<nums.size()){
        r = l + nums[l];
        l = l+1;
        jmp++;
        if (r>=nums.size()-1)
            break;
        int mx = 0;
        for (int j = l; j < std::min(r+1,nums.size()); j++){
            if (mx <=j+nums[j]){
                mx = j+nums[j];
                l = j;
            }
        }

    }
    return jmp;
}

int jump2(vector<int>& nums) {
    int jmpCnt = 0;
    int jmpMax = 0;
    int lstJmp = 0;
    for (int i = 0; i<nums.size()-1; i++){
        jmpMax = std::max(jmpMax, i + nums[i]);
        if (i == lstJmp){
            jmpCnt++;
            lstJmp = jmpMax;
        }
    }
    return jmpCnt;

}

// LC :: 13
int romanToInt(string s) {
    std::unordered_map<char, int> roman = {{'I',1}, {'V',5}, {'X',10},{'L',50}, {'C',100}, {'D',500}, {'M',1000}};
    std::unordered_map<char, int> index = {{'I',1}, {'V',2}, {'X',3},{'L',4}, {'C',5}, {'D',6}, {'M',7}};
    int sum = 0;
    for (int i = 0; i < s.size(); i++){
        sum += roman[s[i]];
        if(i != 0 && index[s[i-1]] < index[s[i]]) {
            sum -= roman[s[i-1]] * 2;
        }
    }
    return sum;
}

// LC :: 11
int maxArea(vector<int>& height) {
    int l = 0;
    int r = height.size() - 1;
    int area = 0;
    while (l<r) {
        area = std::max(area, std::min(height[l],height[r]) * (r - l));
        if (height[l] <= height[r])
            l++;
        else
            r--;
    }
    return area;
}

// LC :: 134
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int sum = 0;
    int pos = -1;
    for(int i = 0; i < gas.size();i++){
        sum+= gas[i] -cost[i];
    }
    if (sum < 0) return -1;
    sum = 0;
    for (int i = 0; i<gas.size(); i++) {
        sum+= gas[i] -cost[i];
        if (sum>=0) {
            if (pos == -1)
                pos = i;
        } else {  // sum is negative, so discard everything up to this point
            pos = -1;
            sum = 0; // sum was negative so discard this from our candidate starting index 
        }
    }
    return pos;
}

// LC :: 55
bool canJump(vector<int>& nums) {
    int maxCover = 0;
    for (int i = 0; i <nums.size(); i++){
        maxCover = std::max(maxCover, i + nums[i]);
        if (maxCover >= nums.size() -1) 
            return true;
        if (i <nums.size()-1 && maxCover<=i)
            return false;
    }
    return true;        
}

int hIndex(vector<int>& citations) {
    int sz = citations.size();
    vector<int> vc(sz+1, 0);
    for (int i = 0; i<citations.size(); i++){
        if(citations[i]>=sz) 
            vc[sz]++;
        else
            vc[citations[i]]++;
    }
    int cnt = 0;
    int j = 0;
    for (j = sz; j >= 0; j--){
        cnt+=vc[j];
        if(j<=cnt)
            break;
    }
    return j;    
}

class RandomizedSet {
public:
    unordered_map<int, int> hashMap;
    vector<int> list;
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if (hashMap.find(val)==hashMap.end()){
            hashMap[val]=list.size();
            list.push_back(val);
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if (hashMap.find(val)==hashMap.end()) return false;
        int spv = list[list.size()-1];
        int idx = hashMap[val];
        std::swap(list[list.size()-1],list[idx]);
        hashMap[spv] = idx;
        hashMap.erase(val);
        list.pop_back();
        return true;
    }
    
    int getRandom() {
        int randId = std::rand() % list.size();
        return list[randId];
    }
};

// LC :: 93 restore ip address
bool isValidNum(string s){
    int val = std::atoi(s.c_str());
    return val>=0 && val <=255;
}
void resIPRec(string s, string ip, int index, int dCount, vector<string> & res){
    if (index == s.size() && dCount == 4){
        res.push_back(ip);
        return;
    }
    if (index >= s.size())
        return;
    int len = s.at(index) == '0' ? 1:3;
    for (int i = 1; i <=len && i<s.size(); i++){
        string sub = s.substr(index,i);
        if(isValidNum(sub)){
            if (dCount ==3)
                resIPRec(s, ip+sub,index+i, dCount+1, res);
            else
                resIPRec(s, ip+sub+".",index+i, dCount+1, res);
        }
    }
}
vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    resIPRec(s, "", 0, 0, res);
    return res;
}

// LC :: 93 the non-recursive version  
bool check(string s){
    int n=s.size();
    //if the size of string is 1 that is always possible so return true
    if(n==1){
        return true;
    }
    //if we have length >3 or string starts with 0 return false
    if(n>3||s[0]=='0'){
        return false;
    }
    //we are converting string to integer to check if it is less than equalto 255
    int val=stoi(s);
    if(val>255){
        return false;
    }
    //return true at last
    return true;
}
vector<string> restoreIpAddresses2(string s) {
    int n=s.size();
    //we will store our ans in ans vector of strings
    vector<string>ans;
    //the max length of the ip address could be 12 as 255.255.255.255 so 
    //all the string s with size greater than 12 can have ans
    if(n>12){
        return ans;
    }
    //now we have our string of length 12 or less than 12 so now 
        //1. we have to spit the s in parts such that it satisfy the ip address conditions
        //2. if all 4 strings satisfy the condition we will push into ans vector
    
    for(int i=1;i<=3;i++){//for the length before first '.'
        for(int j=1;j<=3;j++){//for the length between first and second '.'
            for(int k=1;k<=3;k++){//for the length between second and third '.'
                //checking condition if the last segment is of length 3 or less
                if(i+j+k<n&&i+j+k+3>=n){
                    //dividing the s int substrings 
                    string a=s.substr(0,i);
                    string b=s.substr(i,j);
                    string c=s.substr(j+i,k);
                    string d=s.substr(i+j+k);
                    //if all the substring satisfy the check function condition 
                    //then we will push into ans vector 
                    if(check(a)&&check(b)&&check(c)&&check(d)){
                        ans.push_back(a+"."+b+"."+c+"."+d);
                    }
                }
            }
        }
    }
    //return the ans vector
    return ans;
}

vector<string> split(string &s, char delim){
    istringstream tokenStrm(s);
    vector<string> tokens;
    string token;
    while(std::getline(tokenStrm, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

// this is using the in built istream

string reverseWords(string s) {
    istringstream istr(s);
    vector<string> vs;
    string st;
    while(istr>>st){
        vs.push_back(st);
    }
    string res ="";
    for (int i = vs.size() -1; i>=0; i--){
        res = res+vs[i]+" ";
    }
    res.erase(res.size()-1);
    return res;
}

// this is without using the istream
string reverseWords2(string s) {
    reverse(s.begin(), s.end());
    int i = 0;
    string res= "";
    int j = 0;
    int st = 0;
    int n = s.size();
    while(i<n){
        while(i<n && s[i] == ' ')
            i++;
        if (i == n) break;

        while (i<n && s[i] !=' ')
            s[j++] = s[i++];
        reverse(s.begin()+st,s.begin()+j);
        s[j++] = ' ';
        st = j;
        i++;            
    }
    s.resize(j-1);
    return s;
}

class Trie {
public:
    struct TrieNode{
        char val;
        std::unordered_map<char,TrieNode*> children;
        bool has_word;
        TrieNode(char ch) : val(ch), has_word(false){}
    };
    TrieNode *root;
    Trie() {
        root = new TrieNode('#');
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (int i = 0; i < word.size(); i++){
            if(node->children.find(word[i]) == node->children.end()){
                node->children[word[i]] = new TrieNode(word[i]);
            }
            node = node->children[word[i]];
            if(i == word.size()-1) {
                node->has_word = true;
            }
        }
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (int i = 0; i < word.size(); i++){
            if(node->children.find(word[i]) == node->children.end())
                return false;
            node = node->children[word[i]];
            if (i == word.size()-1 && node->has_word)
                return true;

        }
        return false;      
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (int i = 0; i < prefix.size(); i++){
            if(node->children.find(prefix[i]) == node->children.end())
                return false;
            node = node->children[prefix[i]];
        }
        return true;
        
    }
};

// LC :: 647
int palindromeCount(string s , int l, int r) {
    int count = 0;
    while(l>=0 && r < s.size() && s[l--] == s[r++]){
        count++;
    }
    return count;
}
int countSubstrings(string s) {
    int count = 0;
    for (int i = 0; i<s.size(); i++){
        count += palindromeCount(s, i,i);
        count += palindromeCount(s, i,i+1);
    }
    return count;
}

class MovingAverage {
public:
    int runningSum;
    queue<int> q;
    int qSize = 0; 
    MovingAverage(int size) {
        runningSum = 0;
        qSize = 0;
    }
    
    double next(int val) {
        runningSum+=val;
        q.push(val);
        if(q.size()>qSize) {
            runningSum-=q.front();
            q.pop();
        }
        return (double) runningSum/ (double)q.size();
        
    }
};


class KthLargest {
public:

    priority_queue<int, vector<int>, greater<int>> minHeap;
    int hSize;
    KthLargest(int k, vector<int>& nums) {
        hSize = k;
        for (int &n : nums) {
            minHeap.push(n);
            if(minHeap.size()>k) minHeap.pop();
        }
    }
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size()>hSize)
            minHeap.pop();
        return minHeap.top();
        
    }
};

int rotatedDigits2(int n) {
    std::unordered_map<char, char> dict = {
        {'0','0'},
        {'1','1'},
        {'8','8'},
        {'2','5'},
        {'5','2'},
        {'6','9'},
        {'9','6'}
    };
    int count = 0;
    for (int i = 1; i<=n ; i++) {
        string s = std::to_string(i);
        string t="";
        for (int i = 0; i < s.size(); i++) {
            if (dict.find(s[i]) == dict.end())
                break;
            t.push_back(dict[s[i]]);
        }
        if (s.size() != t.size())
            continue;
        int val = std::stoi(t);
        if(i!=val)
            count++;
        
    }
    return count;    
}

int rotatedDigits(int n) {
    vector<int> digits(n+1 , 0);
    int count = 0;

    for (int i = 1; i <= n; i++){
        if (i < 10) {
            if (i == 1 || i == 8) 
                digits[i] = 1;
            if (i == 2 || i == 5 || i == 6 || i == 9) {
                digits[i] = 2;
                count++;
            }
        } else {
            int div = digits[i / 10];
            int rem = digits[i % 10];
            if (div == 1 && rem == 1){
                digits[i] = 1;
            }else if (div>=1 && rem>=1) {
                digits[i] = 2;
                count++;
            }
        }
    }
    return count;
}

int findJudge(int n, vector<vector<int>>& trust) {
    vector<int> inDegree(n+1,0);
    vector<int> outDegree(n+1,0);
    for (auto &edge: trust) {
        inDegree[edge[1]]++;
        outDegree[edge[0]]++;
    }
    int judge = -1;
    for (int i = 1; i<inDegree.size(); i++){
        if(inDegree[i] == n - 1 && outDegree[i] == 0)
            judge = i; 
    }
    return judge;
}

int missingElement(vector<int>& nums, int k) {
    // disable sync of C++ i/o stream with C i/o stream
    ios::sync_with_stdio(false);
    cin.tie(0); // break the sync of cin & cout flusing so when cin is used cout is not flushed
    // ignore the ifrst two lines they are just there to solve c++ innternal 
    // issue of slow down becasue of syncing c-style scanf & printf to cin cout
    int low = 0, high = nums.size() -1;
    int missingRange = nums[high] - nums[low] + 1 - nums.size();
    int kth = nums[nums.size() -1] + (k - missingRange);
    if (k > missingRange)
        return kth;
    while (low < high) {
        int mid = low + (high - low)/2;
        int leftMissing = (nums[mid] - nums[low] + 1) - (mid - low + 1);
        if (k > leftMissing){
            low = mid;
            k-= leftMissing;
        } else {
            high = mid;
        } 
        // found the starting number, its nums[low] so nums[low] + k is our solution
        // think how in the next iteration low == mid which indicates low is our solution starting number
        if (high - low == 1) {
            kth = nums[low] + k;
            break;
        }

    }
    return kth;
}

int maximumUnits2(vector<vector<int>>& boxTypes, int truckSize) {
    auto cmp = [](vector<int> a, vector<int> b){return a[1] > b[1];};
    int units = 0;
    std::sort(boxTypes.begin(), boxTypes.end(), cmp);
    for (auto &box : boxTypes){
        if (truckSize <= 0)
            break;
        if(truckSize >= box[0]){
            truckSize -= box[0];
            units += (box[1] * box[0]);
        } else {
            units += (box[1] * truckSize);
            truckSize = 0;
        }
    }

    return units;
}

int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    auto cmp = [](vector<int> a, vector<int> b){return  a[1]>b[1];};
    int units = 0;
    std::sort(boxTypes.begin(), boxTypes.end(), cmp);
    for (auto &box : boxTypes){
        int boxCount = std::min(box[0], truckSize);
        units += boxCount * box[1];
        truckSize -= boxCount;
        if (truckSize <= 0)
            break;
    }

    return units;
}

// LC :: 2182 

string repeatLimitedString(string s, int repeatLimit) {
    int freq[26] = {0};
    priority_queue<char> pq;
    
    for (int i = 0; i <s.size(); i++) {
        freq[s[i]-'a']++;
        if (freq[s[i]-'a'] == 1)
            pq.push(s[i]);
    }
    string res = "";
    while (!pq.empty()) {
        char ch = pq.top();
        pq.pop();
        int fr = freq[ch -'a'];
        int len = std::min(repeatLimit, fr);
        freq[ch-'a'] -= len;
        for (int i = 0; i< len; i++)
            res+=ch;
        if (fr > repeatLimit) {
            if(!pq.empty()){
                char ch2 = pq.top();
                pq.pop();
                freq[ch2-'a'] -= 1;
                res+=ch2;
                pq.push(ch);
                if (freq[ch2-'a'] != 0)
                    pq.push(ch2);
            } else {
                return res;
            }
        }

    }
    return res;
    
}

// LC :: 358
string rearrangeString(string s, int k) {
    unordered_map<char, int> fmap;
    auto cmp = [&fmap] (char a, char b){ return fmap[a] < fmap[b];};
    priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);
    for (auto c : s) {
        fmap[c]++;
    }
    for (auto [k,v] : fmap) {
        pq.push(k);
    }
    queue <char> tempQ;
    string res = "";
    int validException = 0;
    while(!pq.empty()) {
        int cnt = k;
        while(!pq.empty() && cnt) {
            char ch = pq.top();
            pq.pop();
            fmap[ch]--;
            if (fmap[ch] != 0)
                tempQ.push(ch);
            res += ch;
            cnt--;
        }
        if (cnt != 0) validException++;
        while (!tempQ.empty()) {
            pq.push(tempQ.front());
            tempQ.pop();
        } 

    }
    if (validException >1) return "";
    return res;
}

// LC :: 31
// This is the next permutation algorithm
// The idea is to find the first decreasing element from the end of the array
// and then find the first element which is greater than the decreasing element
// and swap them, then reverse the array from the next element of the decreasing element
// to the end of the array
void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i+1]) {
        i--;
    }
    if (i >= 0) {
        int j = nums.size() - 1;
        while (j > 0 && nums[j] <= nums[i]) 
            j--;
        std::swap(nums[i], nums[j]);
    }

    std::reverse(nums.begin() + i + 1, nums.end());
    
}

int partition(vector<int>& nums, int left, int right){
    int pivot = left + std::rand()%(right - left);
    int pivotVal = nums[pivot];
    //nums[pivot] = nums[right];
    //nums[right] = pivotVal;
    std::swap(nums[pivot],nums[right]);
    int i = left;
    int j = left;
    while (i < right) {
        if (nums[i] < pivotVal) {
            std::swap(nums[i], nums[j]);
            j++;
        }
        i++;
    }
    std::swap(nums[j],nums[right]);
    return j;
}

int quickSelect(vector<int>& nums, int left, int right, int k) {
    if (left == right)
        return nums[left];
    int pivotIndex = partition(nums, left, right);
    if (k == pivotIndex)
        return nums[k];
    else if (k < pivotIndex)
        return quickSelect(nums, left, pivotIndex -1, k);
    else
        return quickSelect(nums, pivotIndex+1, right, k);
}

int findKthLargest2(vector<int>& nums, int k) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int item = nums.size() - k;
    return quickSelect(nums, 0, nums.size() - 1, item);
}

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (auto &n : nums) {
        minHeap.push(n);
        if(minHeap.size()>k)
            minHeap.pop();
    }
    return minHeap.top();

}


int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> hmap;
    hmap[0] = 1;
    int runningSum = 0;
    int count = 0;
    for (int n : nums) {
        runningSum += n;
        if(hmap.find(runningSum -k) != hmap.end()) {
            count += hmap[runningSum-k];
        }
        hmap[runningSum] = hmap[runningSum] + 1;
    }
    return count;
}

int maxSubArrayLen(vector<int>& nums, int k) {
    unordered_map<int, int> hmap;
    hmap[0] = -1;
    int runningSum = 0;
    int len = 0;
    for (int i = 0; i < nums.size(); i++) {
        runningSum += nums[i];
        if(hmap.find(runningSum -k) != hmap.end()) {
            len = std::max(len, i - hmap[runningSum -k]);
        }
        hmap.emplace(runningSum, i);
    }
    return len;
    
}

bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> sets;
    for (auto &n :nums){
        if(!sets.insert(n).second)
            return true;
    }
    return false;
    
}

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> sets;
    for (int i = 0; i < nums.size(); i++){
        if(i>k)
            sets.erase(nums[i-k-1]);
        if(!sets.insert(nums[i]).second)
            return true;
    }
    return false;    
}

bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
    set<long> treeSet;
    for (int i = 0; i<nums.size(); i++) {
        auto itF = treeSet.upper_bound(nums[i] + valueDiff);
        auto itC = treeSet.lower_bound(nums[i] - valueDiff);
        if(itF != treeSet.begin() || itC!= treeSet.end()){
            if (itF != treeSet.begin()){
                --itF;
                auto floor = *itF;
                if (floor>= nums[i]) 
                    return true;
            } 
            if (itC!= treeSet.end()){
                auto ceil = *itC;
                if (ceil <= nums[i])
                    return true;
            }
        }
        treeSet.insert((long)nums[i]);
        if (i >= indexDiff){
            treeSet.erase((long)nums[i-indexDiff]);
        }
    }
    return false;    
}


string minWindow(string s, string t) {
    if (s.size()<t.size()) return "";
    unordered_map<int, int> fmap;
    for (char ch : t) {
        fmap[ch] += 1;
    }
    int left = 0, right = 0, desireCount = t.size();
    int st = 0;
    int minLen = INT_MAX;
    while (right < s.size()) {
        char ch = s[right];
        if(fmap.find(ch)!=fmap.end()){
            if (fmap[ch]>0)
                desireCount--;
            fmap[ch]--;
        }
        while(desireCount == 0) {
            char ch = s[left];
            if (fmap.find(ch) != fmap.end()) {
                if (fmap[ch] == 0)
                    desireCount++;
                fmap[ch]++;
                if (right - left + 1 <= minLen) {
                    minLen = right - left + 1;
                    st = left;
                }                
            }
            left++;
        }
        right++;
    }
    if (minLen == INT_MAX) return "";
    return s.substr(st, minLen);    
}
// the array is very small hence Binsearch prouces to much comutation and gets slow
// for such a small array Linear search is outperforming the bin search as we just do compare
int valueBinSearch(int val[], int size, int t) {
    int low = 0, high = size - 1;
    while (low < high) {
        int mid = (low + high)/2;
        if (val[mid] == t)
            return mid;
        else if (val[mid] < t) {
            low = mid +1;
        } else {
            high = mid - 1;
        }

    }
    return val[low]>t?low -1 :low;
}

// for the LC :: 12 usu this linesearch
int valueLinSearch(int nums[], int size, int t) {
    for (int i= 0; i< size; i++) {
        if (nums[i] == t)
            return i;
        else if (nums[i]>t)
            return i-1;
    }
    return 0;
}
// LC::12 simple problem, important part is how you handle the cases
string intToRoman(int num) {
    string val = std::to_string(num);
    #define A_SIZE 13
    string sym[A_SIZE] = {"I", "IV", "V", "IX","X","XL","L","XC", "C", "CD", "D","CM","M"};
    int values[A_SIZE] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    string res="";
    // handle M case
    int sz = val.size();
    int i = 0;
    if (sz == 4) {
        int k = val[0] - '0';
        for (int i = 1; i<=k;i++)
            res+='M';
        i++;
    }
    // value is less the 1000
    while (i < sz) {
        int p = sz-i;
        int v = (val[i] -'0') * std::pow(10, p -1);
        while (v != 0) {
            int sv = valueLinSearch(values, A_SIZE, v);
            res+= sym[sv];
            v -= values[sv];
        }
        i++;
    }   
    return res;
}

// this version handles the M cases inside the main loop
string intToRoman2(int num) {
    string val = std::to_string(num);
    #define A_SIZE 15
    string sym[A_SIZE] = {"I", "IV", "V", "IX","X","XL","L","XC", "C", "CD", "D","CM","M","MM","MMM"};
    int values[A_SIZE] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000, 2000, 3000};
    string res="";
    int sz = val.size();
    int i = 0;
    while (i < sz) {
        int p = sz-i;
        int v = (val[i] -'0') * std::pow(10, p -1);
        while (v != 0) {
            int sv = valueLinSearch(values, A_SIZE, v);
            res+= sym[sv];
            v -= values[sv];
        }
        i++;
    }   
    return res;
}

// LC :: 54
vector<int> spiralOrder2(vector<vector<int>>& matrix) {
    int cDir[4] = {1, 0, -1, 0};
    int rDir[4] = {0, 1, 0, -1};
    int sz = matrix.size() * matrix[0].size() - 1;
    int r = 0, c = 0;
    vector<int> res;
    int idx = 0;
    #define OFFSET 1000
    while (sz >= 0) {
        res.push_back(matrix[r][c]);
        matrix[r][c] = OFFSET; 
        int tr = r + rDir[idx];
        int tc = c + cDir[idx];
        if (tr < 0 || tr >= matrix.size() || tc < 0 ||
            tc >= matrix[0].size() || matrix[tr][tc] == OFFSET) {
            idx = (idx + 1) % 4;
        }
        r += rDir[idx];
        c += cDir[idx];
        sz--; 
    }
    return res;    
}
#define MAT_OFFSET 1000

void spiralOrderRec(vector<vector<int>>& matrix, vector<int> &res, int r, int c, int rDir[], int cDir[], int sz, int idx) {
    if (sz == 0)
        return;
    res.push_back(matrix[r][c]);
    int old = matrix[r][c];
    matrix[r][c] = MAT_OFFSET; 
    int tr = r + rDir[idx];
    int tc = c + cDir[idx];
    if (tr < 0 || tr >= matrix.size() || tc < 0 ||
        tc >= matrix[0].size() || matrix[tr][tc] == MAT_OFFSET) {
            idx = (idx + 1) % 4;
    }
    r += rDir[idx];
    c += cDir[idx];
    spiralOrderRec(matrix, res, r, c, rDir, cDir, sz -1, idx);
    matrix[r][c] = old;
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int cDir[4] = {1, 0, -1, 0};
    int rDir[4] = {0, 1, 0, -1};
    vector<int> res;
    int sz = matrix.size() * matrix[0].size();
    spiralOrderRec(matrix, res, 0, 0, rDir, cDir, sz, 0);
    return res;

}

vector<vector<int>> merge2(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    // sort by lowest start interval and if start intervals are equal sort by bigger end interval 
    // that we the interval which are fully consumed by another interval will always appear after 
    // the bigger interval and when comparing two intervals in the main loop we just check 
    // last end interval > cur start interval
    auto cmp = [](vector<int> &a, vector<int> &b){
        if(a[0] == b[0]){
            return a[1] > b[1];
        }
        return a[0] < b[0];
    };
    std::sort(intervals.begin(), intervals.end(), cmp);
    int i = 0;
    vector<int> miv(intervals[0]);
    for (i = 1; i < intervals.size(); i++) {
        if (miv[1]>=intervals[i][0]) {
            miv[0] = std::min(miv[0], intervals[i][0]);
            miv[1] = std::max(miv[1], intervals[i][1]);
        } else {
            res.push_back(miv);
            miv = intervals[i];
        }
    }
    res.push_back(miv);
    return res;
}
// more concise version as we are putting the merged intervals in the results array 
// we can basically use that last interval from the  result interval every time
// also note we can just sort by start interval it does no matter two sort when start 
// intervals are equal we will get the same result of merging 
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    auto cmp = [](vector<int> &a, vector<int> &b){
        return a[0] < b[0];
    };
    std::sort(intervals.begin(), intervals.end(), cmp);
    vector<vector<int>> res;
    for (auto &inv : intervals) {
        if(res.empty()|| res[res.size() -1][1] < inv[0]) {
            res.push_back(inv);

        } else {
            res[res.size()-1][1] = std::max(res[res.size()-1][1], inv[1]);
        }
    }
    return res;
}

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    int n = intervals.size();
    int i = 0;
    // before overlap
    while(i <n && intervals[i][1] < newInterval[0])
        res.push_back(intervals[i++]);
    // merge
    while (i < n && intervals[i][0]<=newInterval[1]) {
        newInterval[0] = std::min(intervals[i][0], newInterval[0]);
        newInterval[1] = std::max(intervals[i][1], newInterval[1]);
        i++;
    }
    res.push_back(newInterval);
    // last half
    while (i < n)
        res.push_back(intervals[i++]);
    return res; 
}

// LC::167
vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0, r = numbers.size()-1;
    while (l < r) {
        int sum = numbers[l] + numbers[r];
        if (sum == target) {
            return {l + 1, r + 1};
        } else if (sum < target){
            l++;
        } else {
            r--;
        }
    }
    return {0, 0}; 
}

bool isSubsequence(string s, string t) {
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()){
        if(s[i] == t[j]){
            i++;
        }
        j++;
    }
    return i==t.size();
}


class MinStack {
public:
    stack<int> stk;
    stack<int> minStk;
    MinStack() {
        
    }
    
    void push(int val) {

        stk.push(val);
        if(minStk.empty() || minStk.top() >= val){
            minStk.push(val);
        }
    }
    
    void pop() {
        if (!minStk.empty() && minStk.top() == stk.top()){
            minStk.pop();
        }
        stk.pop();
        
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minStk.top();
        
    }
};

// LC::383
bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> freq;
    for (auto &m : magazine){
        freq[m] += 1;
    }
    for (auto &r : ransomNote) {
        if (freq.find(r) == freq.end() || freq[r] == 0)
            return false;
        freq[r]-=1;
    }
    return true;
}

// LC :: 3
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> fmap;
    int left = 0, right = 0;
    int len = 0;
    
    while(right < s.size()){ 
        if(fmap.find(s[right])!=fmap.end()) {
            left = max(fmap[s[right]] + 1, left);
        }
        fmap[s[right]] = right;
        len = max(right - left +1, len);
        right++;
    }
    return len;
    
}

// transpose matrix
void transposeMat(vector<vector<int>>& mat){
    int n = mat.size();
    for (int i = 0; i < n; i++){
        for (int j = i +1; j < n; j++){
            swap(mat[i][j], mat[j][i]);
        }
    }
}
// reflect (reverse each row left to right)
void reflect(vector<vector<int>>& mat){
    int n = mat.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n/2; j++){
            swap(mat[i][j], mat[i][n-1 -j]);
        }
    }

}
// LC ::45
// The idea is to use linear algebra method to rotate
// rotate clockwise can be done using transpose a matrix 
// followed by a reflect (reverse each row left to right)
void rotate(vector<vector<int>>& matrix) {
    transposeMat(matrix);
    reflect(matrix);
}

// LC :: 205 
// consider the case for "bad" & "coc" results false
// we need two map to ensure no two char maps to the same char
bool isIsomorphic(string s, string t) {
    vector<char> map1(128, 0);
    vector<char> map2(128, 0);
    for (int i = 0; i < s.size(); i++){
        if (map1[s[i]] == 0)
            map1[s[i]] = t[i];
        if (map2[t[i]] == 0)
            map2[t[i]] = s[i];
        if(map1[s[i]] != t[i] || map2[t[i]]!= s[i])
            return false;            
    }
    return true;
    
}
// LC :: 125
bool isPalindrome(string s) {
    int l = 0; 
    int r = s.size()-1;
    auto isLetter = [](char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    };
    while (l <= r) {
        if (isLetter(s[l]) && isLetter(s[r])){
            if (tolower(s[l++]) != tolower(s[r--])) return false;
        } else {
            if(!isLetter(s[l])) l++;
            if(!isLetter(s[r])) r--;
        }
    }
    return true;    
}

// LC :: 58
int lengthOfLastWord(string s) {
    int i = 0;
    int len = 0;
    while (i < s.size()) {
        while (i < s.size() && s[i] == ' ')
            i++;
        if (i == s.size()) break; 
        int j = 0;
        while(i<s.size() && s[i]!= ' ') {
            j++;
            i++;
        }
        len = j;
    }
    return len;
}
// LC :: 36
bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<int> valids;
    for(int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j]=='.') continue;
            int rval = (i+1) * 10 + board[i][j] -'0';
            int cval = (j+1) * 100 + board[i][j] - '0';
            int bval = ((i/3) * 3  + j/3 +1) * 1000 + board[i][j] - '0';
            if (valids.count(rval) || valids.count(cval) || valids.count(bval))
                return false;
            valids.insert(rval);
            valids.insert(cval);
            valids.insert(bval);
        }
    }
    return true;
}

// LC :: 14
string longestCommonPrefix(vector<string>& strs) {
    std::sort(strs.begin(),strs.end());
    string st = strs[0];
    string end = strs[strs.size()-1];
    string res = "";
    for (int i = 0; i < std::min(st.size(),end.size());i++){
        if(st[i] != end[i])
            break;
        res += st[i]; 
    }
    return res;
    
}

// LC :: 209
int minSubArrayLen(int target, vector<int>& nums) {
    
    int left = 0, right = 0;
    int sum = 0;
    int minLen = INT_MAX;
    while (right < nums.size()) {
        sum += nums[right];
        while (sum >= target) {
            sum -= nums[left];
            minLen = std::min(minLen, right-left + 1);
            left++;
        }
        right++;
    }
    return minLen == INT_MAX?0:minLen;
}

// LC :: 290
// Same as the ismorphic string problem we need to maps to ensure
// no two char/string maps to the same string/char
void split2(string &s, char delim, vector<string> &tokens){
    istringstream sStreams(s);
    string token;
    while(std::getline(sStreams, token, delim)){
        tokens.push_back(token);
    }
}

bool wordPattern(string pattern, string s) {
    vector<string> tokens;
    split2(s, ' ', tokens);
    unordered_map<char, string> map1;
    unordered_map<string, char> map2;
    if (pattern.size() != tokens.size())
        return false;
    for (int i = 0; i < pattern.size(); i++) {
        if (map1.find(pattern[i]) == map1.end())
            map1[pattern[i]] = tokens[i];
        if (map2.find(tokens[i]) == map2.end())
            map2[tokens[i]] = pattern[i];
        if (map1[pattern[i]] != tokens[i] || map2[tokens[i]] != pattern[i])
            return false;
    }
    return true;
    
}

// LC:: 49
// check the V2 version for more concise code
vector<vector<string>> groupAnagrams(vector<string>& strs) {

    vector<vector<string>> res;
    unordered_map<string, vector<string>> grpMap;
    for (string st : strs) {
        int freq[26] = {0};
        for (char ch : st){
            freq[ch-'a']++;
        }
        string sb = "";
        for (int i = 0; i <26; i++){
            if (freq[i] != 0){
                char c = 'a' + i;
                sb+= c + to_string(freq[i]);
            } 
        }
        grpMap[sb].push_back(st);
    }
    
    for (auto [k,v] : grpMap){
        res.push_back(v);
    }
    
    return res;
}

vector<vector<string>> groupAnagramsV2(vector<string>& strs) {

    vector<vector<string>> res;
    unordered_map<string, vector<string>> grpMap;
    for (string st : strs) {
        string sb = st;
        sort(sb.begin(),sb.end());
        grpMap[sb].push_back(st);
    }
    
    for (auto [k,v] : grpMap){
        res.push_back(v);
    }
    
    return res;
}

// LC ::202

int nextNum(int n) {
    int res = 0;
    while(n){
        res += (n%10)*(n%10);
        n/=10;
    }
    return res;
} 
bool isHappy(int n) {
    unordered_set<int> cSet;
    while(n!=1) {
        n = nextNum(n);
        if(cSet.find(n)!=cSet.end())
            return false;
        cSet.insert(n);
    }
    return n == 1;
}

// LC :: 128

int longestConsecutive2(vector<int>& nums) {
    unordered_map<int, int> hMap;
    for (auto n : nums) {
        hMap[n] += 1;
    }
    int maxLen = 0;
    for (const auto& [k,v] : hMap) {
        if (v == 0)
            continue;
        int len = 1;
        int size =  k+nums.size();
        for (int i = k +1; i <size; i++) {
            if (hMap.find(i) != hMap.end()){
                len++;
                hMap[i] = 0;
            } else 
                break;
        }
        maxLen = std::max(maxLen, len);
        hMap[k] = 0;
    }
    return maxLen;   
}

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> hSet(nums.begin(), nums.end());
    int maxlen = 0;
    for (int n: nums){
        int len = 0;
        if (hSet.count(n-1))
            continue;
        int cur = n;
        while(hSet.count(cur)){
            cur++;
            len++;
        }
        maxlen = ::max(maxlen, len);
    }
    return maxlen;   
}


// LC :: 228
// The version 1 is more easy to read and think, same complxity though
vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int i = 0;
    while (i < nums.size()){
        int last = nums[i];
        int len = 0;
        while (i + 1 < nums.size() && nums[i+1] == 1 + nums[i]) {
            i++;
            len++;
        }
        string s = std::to_string(last);
        if (len != 0){
            s+= "->" + std::to_string(nums[i]);
        }
        res.push_back(s);
        i++;
    }
    return res;
}

vector<string> summaryRanges2(vector<int>& nums) {
        vector<string> res;
        if (nums.size() == 0) return res;
        int i = 0;
        int last = nums[0];
        for(i = 1; i <= nums.size(); i++){
            if(i==nums.size() || (nums[i] != nums[i-1] +1)){
                if (last == nums[i-1])
                    res.push_back(std::to_string(last));
                else {
                    string s = std::to_string(last)+"->"+std::to_string(nums[i-1]);
                    res.push_back(s);
                }
                if (i != nums.size())
                    last = nums[i];
            } 
        }
        return res;        
}

// LC :: 452
// The idea is very simple here, if we sort the intervals based on the end interval and then check how many 
// intervals can be covered by this end time then all the covered interval are concurrent interval and can
// be counted as one concurency, we keep counting how many concurrency possible throughout the time.
// This works here because consider one interval that is part of multple concurencey if count it in one of 
// it that is fine cause its needs to be counted once
// We are taking a greedy approach here, we are always trying to cover as many intervals as possible with the
// minimum end time possible
int findMinArrowShots(vector<vector<int>>& points) {
    auto cmp = [](vector<int> &a, vector<int> &b){ return a[1]<b[1];};
    std::sort(points.begin(), points.end(), cmp);
    int count = 0;
    int last = points[0][1];
    for (auto p : points) {
        if (last < p[0]){
            count++;
            last = p[1]; 
        }
    }
    // for the last one that is never counted in the loop
    count++;
    return count;
}

// LC :: 20 
bool isValid(string s) {
    stack<int> stk;
    unordered_map<char, char> cmap = {{')','('}, {'}', '{'}, {']','['}};
    for (char ch : s){
        if (ch == '(' || ch == '{' || ch == '['){
            stk.push(ch);
        } else {
            if(stk.empty() || stk.top() != cmap[ch])
                return false;
            stk.pop();
        }
    }
    return stk.size() == 0;    
}

// LC:: 71
string simplifyPath(string path) {
    vector<string> dirs;
    split2(path, '/', dirs);
    list<string> dStack;
    for(string s : dirs) {
        if(s == "..") {
            if (!dStack.empty())
                dStack.pop_back();
        } else {
            if (s != "" && s != ".")
                dStack.push_back(s);
        }
    }
    string res="/";
    if (dStack.empty()) return res;
    while (!dStack.empty()){
        res+= dStack.front()+"/";
        dStack.pop_front();
    }
    res.pop_back();
    return res;
}

// LC :: 150

int evalRPN(vector<string>& tokens) {
    stack<int> oprnds;
    for (string t : tokens){
        if(t == "+" || t == "-" || t == "*" || t == "/") {
            int left = 0, right = 0;
            
            if (!oprnds.empty()) {
                right = oprnds.top();
                oprnds.pop();
            } 
            if (!oprnds.empty()) {
                left = oprnds.top();
                oprnds.pop();
            }
            if (t == "+")
                oprnds.push(left + right);
            else if (t == "-")
                oprnds.push(left - right);
            else if (t == "*")
                oprnds.push(left * right);
            else
                oprnds.push(left / right);
            
        } else {
            oprnds.push(std::stoi(t));
        }
    }
    return oprnds.top();
}
// LC :: 227 

int calculate(string s) {
    int res = 0;
    int prev = 0;
    long cur = 0;
    char sign = '+';
    for (int i = 0; i <s.size(); i++){
        if(std::isdigit(s[i])){
            cur = cur * 10 + s[i] - '0';
        }
        if (!std::isdigit(s[i]) && s[i] != ' ' || i == s.size() - 1){
            if(sign == '+'){
                res+= prev;
                prev = cur;
            } else if(sign == '-'){
                res+=prev;
                prev = -cur;
            } else if(sign == '*'){
                prev = prev * cur;
            } else if(sign == '/'){
                prev = prev / cur;
            }
            cur = 0;
            sign = s[i];
        }
    }
    return res+ prev;

}
int calculate2(string s) {
    stack<int> stk;
    long val = 0;
    int res = 0;
    int prod = 1;
    char sign = '+';
    for (int i = 0; i < s.size(); i++) {
        if(std::isdigit(s[i])){
            val = val * 10 + s[i]-'0';
        } 
        if(!std::isdigit(s[i]) && s[i] != ' ' || i == s.size()-1) {
            if (sign == '+'){
                stk.push(val);
            } else if (sign == '-') {
                stk.push(-val);
            } else if (sign == '*') {
                int prd = stk.top() * val;
                stk.pop();
                stk.push(prd);
            } else if (sign =='/'){
                int prd = stk.top() / val;
                stk.pop();
                stk.push(prd);
            }
            sign = s[i];
            val = 0;
        }
    }
    while (!stk.empty()) {
        res += stk.top();
        stk.pop();
    }
    return res;
    
}

// LC :: 224
int calculate3(string s) {
    stack<int> stk;
    int res = 0;
    int val = 0;
    int sign = 1;
    for (int i = 0; i<s.size(); i++) {
        if (std::isdigit(s[i])){
            val = val *10 + s[i]-'0';
        } else if (s[i] == '+') {
            res += val * sign;
            sign = 1;
            val = 0;
        } else if (s[i] == '-') {
            res += val * sign;
            sign = -1;
            val = 0;
        } else if (s[i] == '(') {
            stk.push(res);
            stk.push(sign);
            res = 0;
            val = 0;
        } else if (s[i]==')') {
            res+= val * sign;
            res *= stk.top();
            stk.pop();
            res += stk.top();
            stk.pop();
            val = 0;
        }
    }
    res+= val * sign;
    return res;
}

// LC :: 242
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false; 
    unordered_map<char, int> fmap;
    for(auto c : s) {
        fmap[c]++;
    }
    for (auto c : t){
        if (fmap.find(c) == fmap.end()) return false;
        fmap[c]--;
        if(fmap[c] < 0) return false;
    }

    return true;
    
}

// LC :: 179

string largestNumber(vector<int>& nums) {
    vector<string> numstr;
    for (auto n : nums) {
        numstr.push_back(std::to_string(n));
    }
    auto cmp = [](string o1, string o2){ 
        string s1 = o1+o2;
        string s2 = o2+o1;
        return s2>s1;
            };
    std::sort(numstr.begin(), numstr.end(), cmp);
    if (numstr.size() > 0 && numstr[0] == "0")
        return "0";
    string res="";
    for (string ns : numstr) {
        res+= ns;
    }
    return res;
}


// LC :: 621

int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> fmap;
    for (char t : tasks) {
        fmap[t]++;
    }
    auto cmp = [&fmap](char c1, char c2){ return fmap[c1] < fmap[c2]; };
    priority_queue<char, vector<char>, decltype(cmp)> maxHeap(cmp); 
    for (auto [k,v] : fmap){
        maxHeap.push(k);
    }
    int totTime = 0;
    while (!maxHeap.empty()) {
        int idleCount = n +1;
        queue<char> tempQ; 
        while (!maxHeap.empty() && idleCount > 0) {
            char ts = maxHeap.top();
            maxHeap.pop();
            fmap[ts]--;
            idleCount--;
            totTime++;
            if (fmap[ts] > 0)
                tempQ.push(ts);
        }
        if (tempQ.size() != 0)
            totTime += idleCount;
        while (!tempQ.empty()){
            maxHeap.push(tempQ.front());
            tempQ.pop();
        } 
    }
    return totTime;
    
}

// LC :: 1055
int shortestWay(string source, string target) {
    unordered_map<char, set<int>> smap;
    for (int i = 0; i < source.size(); i++) {
        smap[source[i]].insert(i);
    }
    int sid = 0;
    int count = 1;
    int i = 0;
    while(i < target.size()) {
        if (smap.find(target[i]) == smap.end())
            return -1;
        set<int> idList = smap[target[i]];
        auto itc = idList.lower_bound(sid);
        if (itc == idList.end()) {
            count++;
            sid = 0;
        } else {
            sid = *itc + 1;
            i++;
        }
    }
    return count;
    
}

// LC :: 239
// The idea is to use a monotonic queue
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;

    for (int i = 0; i < nums.size(); i++) {
        
        if(!dq.empty() && dq.front() < i - k + 1)
            dq.pop_front();

        while(!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1)
            res.push_back(nums[dq.front()]);
    }
    return res;
}

// LC :: 739 

// Stack version this uses the same idea as monotonic queue but as we only 
// pop push at the back we can replace deque with a stack
vector<int> dailyTemperatures3(vector<int>& temperatures) {
    vector<int> ans(temperatures.size(),0);
    stack<int> dq;
    for (int i = 0; i < temperatures.size(); i++) {
        while(!dq.empty() && temperatures[dq.top()] < temperatures[i]) {
            ans[dq.top()] = i - dq.top();
            dq.pop();
        }
        dq.push(i);
    }
    return ans;
    
}

// decreasing monotonic queue version
vector<int> dailyTemperatures2(vector<int>& temperatures) {
    vector<int> ans(temperatures.size(),0);
    deque<int> dq;
    for (int i = 0; i < temperatures.size(); i++) {
        while(!dq.empty() && temperatures[dq.back()] < temperatures[i]) {
            ans[dq.back()] = i - dq.back();
            dq.pop_back();
        }
        dq.push_back(i);
    }
    return ans;    
}

//  Still sceptical about the solution rather pick mononic queu
// Using the right array to track the last big item this will give a faster result 
//
vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> ans(temperatures.size(),0);
    vector<int> right(temperatures.size(), temperatures.size());
    
    for (int i = temperatures.size() -1; i >= 0; i--) {
        int j = i + 1;
        while(j < temperatures.size() && temperatures[i] >= temperatures[j]) {
            j = right[j];
        }
        right[i] = j;
        ans[i] = right[i] == temperatures.size() ? 0:right[i] - i;
    }
    return ans;
}

// LC :: 692
// use are frequency based minheap to get the k most frequent item
vector<string> topKFrequent(vector<string>& words, int k) {
    unordered_map<string, int> freq;
    for (string w : words) {
        freq[w]++;
    }
    auto cmp = [&freq](string s1, string s2){ 
        if (freq[s1] == freq[s2])
            return s1 < s2;
        else
            return freq[s1] > freq[s2]; };
    priority_queue<string,vector<string>,decltype(cmp)> minHeap(cmp);
    for (auto [w, v]: freq) {
        minHeap.push(w);
        if (minHeap.size()> k)
            minHeap.pop();

    }
    vector<string> res;
    int j = k-1;
    while(!minHeap.empty()) {
        res[j--] = minHeap.top();
        minHeap.pop();
    }
    return res;    
}

// LC :: 373
// This is a really good problem think who many options are there once you pick a pair
// bascially you start wiht (0,0) and then options are (1,0) and (0, 1) after assume we pick 
// (1, 0) then the next options are (2, 0) and (1,1) How? The pattern is if the current pair 
// is (i,j) then you pick (i + 1, j) and (i, j+ 1) due to the sorted propoerty of the both arrays
// Now we use minheap based inmplementation to find the k smallest pairs, midheap {sum of pair, id1, id2}
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    priority_queue<pair<int, pair<int,int>>, 
                    vector<pair<int, pair<int,int>>>,
                    greater<pair<int, pair<int,int>>>> minHeap;
    int m = nums1.size();
    int n = nums2.size();
    vector<vector<int>> res;
    set<pair<int, int>> visited;
    minHeap.push({nums1[0] + nums2[0], {0,0}});
    visited.insert({0,0});

    while(!minHeap.empty() && k--) {
        auto smallest = minHeap.top();
        minHeap.pop();
        int i = smallest.second.first;
        int j = smallest.second.second;
        res.push_back({nums1[i], nums2[j]});
        if (i + 1 < m && !visited.count({i + 1, j})) {
            visited.insert({i + 1, j});
            minHeap.push({nums1[i+1] + nums2[j], {i + 1, j}});
        }
        if (j + 1 < n && !visited.count({i, j + 1})) {
            visited.insert({i, j + 1});
            minHeap.push({nums1[i] + nums2[j+1], {i , j + 1}});
        }
    }
    return res;
    
}

// LC :: 992

int subArrayCountWithAtMostK(vector<int>& nums, int k) {
    unordered_map<int, int> numMap;
    int l = 0, r = 0;
    int n = nums.size();
    int unique = 0;
    int count = 0;
    while(r < n) {
        numMap[nums[r]]++;
        if (numMap[nums[r]] == 1)
            unique++;
        while (unique == k + 1) {
            numMap[nums[l]]--;
            if (numMap[nums[l]] == 0)
                unique--;
            l++;
        }
        count += r - l +1;
        r++;
    }
    return count;

}

int subarraysWithKDistinct(vector<int>& nums, int k) {
    return subArrayCountWithAtMostK(nums, k) - subArrayCountWithAtMostK(nums, k -1);
}

// LC :: 67 
// A good idea is to always have the longer value assign to the first param
// another trick is for binary carry can be used calc both sum and carry
// sum= carry%2 carry = carry/2
string addBinary(string a, string b) {
    int n = a.size(), m = b.size();
    if (n < m)
        return addBinary(b, a);
    int carry = 0;
    int j = m - 1;
    string res;
    for (int i = n-1; i>=0; i--){
        if(a[i] == '1')
            carry++;
        if (j >= 0 &&b[j--]=='1')
            carry++;
        int sum = carry%2;
        carry /= 2;
        res.push_back(sum+'0');
    }
    // process last carry 
    if (carry == 1)
        res.push_back('1');
    std::reverse(res.begin(), res.end());
    return res;
}

// LC :: 502
// Build vector of profit & captial together to easily handle the code
// We need to use a greedy approach, first sort the new vector with ascending capital order
// we start with w capital and push as many element possible to the maxheap, then pick the 
// most profitalble one and update the capital now we can cover more items from the list.
// after inserting them we pick the best profitable option from the maxHeap
// O(nlogn + klogn) = O(nlogn)
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    vector<pair<int,int>> cap_prof;
    for (int i = 0; i < profits.size(); i++) {
        cap_prof.push_back({capital[i], profits[i]});
    }
    auto cmp = [](pair<int,int> &a, pair<int, int> &b){ return a < b;};
    std::sort(cap_prof.begin(), cap_prof.end(), cmp);
    int i = 0;
    priority_queue<int,vector<int>> maxHeap;
    // this loop is O(n+klogn)
    while (k > 0) {
        while(i<cap_prof.size() && w >= cap_prof[i].first) {
            maxHeap.push(cap_prof[i++].second);
        }
        if(maxHeap.empty())
            break;
        w += maxHeap.top();
        maxHeap.pop();
        k--;
    }
    return w;
}

// LC :: 172
// We need to find out how many factor of 5 we have for the number n 
// there are always ample factors of 2 in the factorial so just need count factors of 5
// also note for 100 25 is factor of two '5's and it needs to be counted so is all other 
// factors of 5's
int trailingZeroes(int n) {
    int res = 0;
    for (int i = 5; (n/i) >0; i*=5) {
        res += (n/i);
    }
    return res;
}

// LC :: 88

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    unsigned int l = m + n -1;
    while (n > 0){
        if(m > 0 && nums1[m-1] >= nums2[n-1]){
            nums1[l] = nums1[m-1];
            m--;
        } else {
            nums1[l] = nums2[n-1];
            n--;
        }
        l--;
    }
}

// LC :: 27

int removeElement(vector<int>& nums, int val) {
    unsigned int j = 0;
    for (unsigned int i = 0; i < nums.size(); i++) {
        if (nums[i] != val){
            nums[j++] = nums[i];
        }
    }
    return j;
}

// LC :: 480 Sliding window median
// The idea is to use two heaps to keep track of the median, we use a maxHeap for the left side
// and minHeap for the right side, we keep the size of the maxHeap always greater than the minHeap
// if the size of the maxHeap is greater than the minHeap we pop the top of the maxHeap and push it to the minHeap
// if the size of the minHeap is greater than the maxHeap we pop the top of the minHeap and push it to the maxHeap
// we also need to keep track of the deleted element from the window
// Priority queue is not a good choice here as we need to delete the element from the heap
// we need to use multiset here
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int, std::greater<int>> maxHeap;
    multiset<int> minHeap;
    vector<double> res;
    int start = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (minHeap.size() <= maxHeap.size()) {
            maxHeap.insert(nums[i]);
            minHeap.insert(*maxHeap.begin());
            maxHeap.erase(maxHeap.begin());
        } else {
            minHeap.insert(nums[i]);
            maxHeap.insert(*minHeap.begin());
            minHeap.erase(minHeap.begin());
        }
        if (i >= k -1) {
            double median = (k & 1) ? 
                *minHeap.begin() : 
                ((double)(*minHeap.begin()) + (double)(*maxHeap.begin())) * 0.5;
            res.push_back(median);

            if (minHeap.count(nums[start])) {
                auto it = minHeap.find(nums[start]);
                minHeap.erase(it);
            } else {
                auto it = maxHeap.find(nums[start]);
                maxHeap.erase(it);
            }
            start++;
        }
    }
    return res;
}

// LC :: 1910
// Basic approcah remove the occurances and keep processing
string removeOccurrences(string s, string part) {
    size_t start = s.find(part);
    while (start != string::npos) {
        s = s.substr(0,start) + s.substr(start+part.size());
        start = s.find(part); 
    }
    return s;
}


int main(){
    return 0;
}