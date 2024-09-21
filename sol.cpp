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
#include "tree.h"
using namespace std;

int removeDuplicates(vector<int>& nums) {
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

void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin()+k);
    std::reverse(nums.begin()+k, nums.end());
    
}

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

int main(){
    return 0;
}