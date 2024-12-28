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
#include <list>
#include <functional>
#include <numeric>
using namespace std;

// LC :: 46
void permRec(vector<int>& nums, int index, vector<vector<int>> &rlist, vector<int> &tlist){
    if (index == nums.size()) {
        rlist.push_back(tlist);
        return;
    }
    for (int i = index; i < nums.size(); i++) {
        std::swap(nums[index], nums[i]);
        tlist.push_back(nums[index]);
        permRec(nums, index + 1, rlist, tlist);
        std::swap(nums[index], nums[i]);
        tlist.pop_back();
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> rlist;
    vector<int> tlist;
    permRec(nums, 0, rlist, tlist);
    return rlist;
}

// LC :: 77
void comRec(vector<int> &nums, int index, vector<vector<int>> &rlist, vector<int> &tlist, int k) {
    if (tlist.size() == k) {
        rlist.push_back(tlist);
    } 
    for (int i = index; i < nums.size(); i++){
        tlist.push_back(nums[i]);
        comRec(nums, i + 1, rlist, tlist, k);
        tlist.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<int> nums;
    for (int i = 1; i <= n; i++){
        nums.push_back(i);
    }
    vector<vector<int>> rlist;
    vector<int> tlist;
    comRec(nums, 0, rlist, tlist, k); 
    return rlist;
}

// LC :: 17
void lcRec(string &digits, unordered_map<char, string> &dmap, int index, vector<string> &res, string &str){
    if (index == digits.size()) {
        res.push_back(str);
        return;
    }
    string temp = dmap[digits[index]];
    for (char t : temp){
        str+=t;
        lcRec(digits, dmap, index + 1, res, str);
        str.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    if (digits.size() == 0)
        return {};
    unordered_map<char, string> dmap = {{'2',"abc"}, {'3', "def"}, {'4', "ghi"}, 
    {'5',"jkl"}, {'6',"mno"}, {'7',"pqrs"}, {'8',"tuv"},{'9',"wxyz"}};
    vector<string> res;
    string str = "";
    lcRec(digits, dmap, 0, res, str);
    return res;
}

// LC :: 39
void comSumRec(vector<int> &nums, int index, vector<vector<int>> &rlist, vector<int> &tlist, int target){
    if (target < 0 || index > nums.size()){
        return;
    }
    if(target == 0){
        rlist.push_back(tlist);
        return;
    }
    for (int i = index; i <nums.size(); i++) {
        tlist.push_back(nums[i]);
        comSumRec(nums, i, rlist, tlist, target-nums[i]);
        tlist.pop_back();
    }
    
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> rlist;
    vector<int> tlist;
    comSumRec(candidates, 0, rlist, tlist, target);
    return rlist;
}



bool check(int row, int col, vector<int> &colList){
    for (int r = 0; r < row; r++) {
        int c = colList[r];
        if (col == c)
            return false;
        if (std::abs(row-r) == std::abs(col - c))
            return false;
    }
    return true;
}

int nQueenRec(int row, vector<int> &colList, int n) {
    if (row == n) {
        for (int c : colList) {
            cout << c << " ";
        }
        cout << endl;
        return 1;
    }
    int count = 0;
    for (int c = 0; c < n; c++) {
        colList[row] = c;
        if (check(row, c, colList))
            count+=nQueenRec(row+1, colList, n);
    }
    return count; 
}
int totalNQueens(int n) {
    vector<int> colList(n,0);
    int count = 0;
    count = nQueenRec(0, colList, n);
    return count;
}

// LC :: 22
void genParenRec(vector<string> &rList, int lrem, int rrem, string &res, int index, int n) {
    if (lrem < 0 || lrem > rrem) {
        return;
    }
    if (lrem == 0 && rrem == 0) {
        rList.push_back(res);
        return;
    }
    res[index] = '(';
    genParenRec(rList, lrem - 1, rrem, res, index+1, n);
    res[index] = ')';
    genParenRec(rList, lrem , rrem - 1, res, index+1, n);
}

vector<string> generateParenthesis(int n) {
    string res(2*n,'\0');
    vector<string> rlist;
    genParenRec(rlist, n, n, res, 0, n);
    return rlist;
}

int main(){
    totalNQueens(8);
    return 0;
}