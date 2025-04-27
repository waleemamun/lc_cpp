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

void genParenRec2(vector<string> &rList, int l, int r, string &res, int index, int n) {
    if (l < r || l > n || r > n) return;
    if (l == n && r == n)
        rList.push_back(res);
    res[index] = '(';
    genParenRec(rList, l + 1, r, res, index + 1, n);
    res[index] = ')';
    genParenRec(rList, l, r + 1, res, index + 1, n);


}
vector<string> generateParenthesis2(int n) {
    string res(2*n,'\0');
    vector<string> rlist;
    genParenRec2(rlist, 0, 0, res, 0, n);
    return rlist;
}

// LC :: 90
void subsetDupRec(vector<int>& nums, int index, vector<int> &tlist, vector<vector<int>>& rlist) {
    rlist.push_back(tlist);
    for (int i = index; i < nums.size(); i++) {
        if (i!=index && nums[i-1] == nums[i])
            continue;
        tlist.push_back(nums[i]);
        subsetDupRec(nums, i + 1, tlist, rlist);
        tlist.pop_back();
    }

}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> rlist;
    vector<int> tlist;
    std::sort(nums.begin(), nums.end());
    subsetDupRec(nums, 0, tlist, rlist);
    return rlist;
}

// LC :: 212
class TrieNode{
 public:   
    char val;
    bool found;
    bool seen;
    unordered_map<char, TrieNode*> child;
    TrieNode(char v): val(v),found(false),seen(false) {}
};

class Trie{
public:
    TrieNode *root;
    Trie() {
        root = new TrieNode('#');
    }
    void addword(string s) {
        TrieNode *node = root;
        for (char c : s) {
            if(node->child.count(c) == 0) {
                node->child[c] = new TrieNode(c);
            }
            node = node->child[c];
        }
        node->found = true;
    }

};

void findWordsRec(vector<vector<char>>& b, TrieNode *node, int r, int c, vector<string> &rlist, string res) {
    if (r < 0 || c < 0 || r >= b.size() || c >= b[0].size() || b[r][c] == '*')
        return;
    if (node->child.count(b[r][c]) == 0)
        return;
    node = node->child[b[r][c]];
    res += b[r][c];
    if (node->found) {
        if (!node->seen) {
            rlist.push_back(res);
            node->seen = true;
        }
    }
    b[r][c] = '*';
    findWordsRec(b, node, r + 1, c, rlist, res);
    findWordsRec(b, node, r - 1, c, rlist, res);
    findWordsRec(b, node, r, c + 1, rlist, res);
    findWordsRec(b, node, r, c - 1, rlist, res);
    b[r][c] = res.back();
    res.pop_back();
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for (auto w : words) {
            trie.addword(w);
        }
        vector<string> rlist;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                string res = "";
                findWordsRec(board, trie.root, i, j, rlist, res);
            }
        }
        return rlist;
        
}

// LC :: 301

void removeParenRec(string s, int index, int left, int right, 
                    int leftRem, int rightRem, 
                    string res, unordered_set<string> &pset) {
    if (index == s.length()) {
        if(leftRem == 0 && rightRem == 0)
            pset.insert(res);
        return;
    }
    char ch = s[index];
    if (ch == '(' && leftRem > 0) {
        removeParenRec(s, index + 1, left, right, leftRem - 1, rightRem, res, pset);
    }
    if (ch == ')' && rightRem > 0) {
        removeParenRec(s, index + 1, left, right, leftRem, rightRem - 1, res, pset);
    }
    res += ch;
    if (ch != '(' && ch != ')') {
        removeParenRec(s, index + 1, left, right, leftRem, rightRem, res, pset);
    } else if (ch == '(') {
        removeParenRec(s, index + 1, left + 1, right, leftRem, rightRem, res, pset);
    } else if (left > right) {
        removeParenRec(s, index + 1, left, right + 1, leftRem, rightRem, res, pset);
    }
    res.pop_back();

}

// LC :: 267

void generatePalRec(string &res, unordered_map<char, int> &fmap, vector<string> &rlist, int sz) {
    if (res.size() == sz){
        rlist.push_back(res);
        return;
    }
    for (auto [k,v] : fmap) {
        if (fmap[k]) {
            fmap[k] -= 2;
            string st = k+res+k;
            generatePalRec(st, fmap, rlist, sz);
            fmap[k] += 2;
        }
    }
}
vector<string> generatePalindromes(string s) {
    unordered_map<char, int> fmap;
    for (char c : s) {
        fmap[c]++;
    }
    char ch = '.';
    int count = 0;
    for (auto [k,v]: fmap) {
        if (fmap[k] % 2 != 0){
            ch = k;
            count++;
        }
    }

    if (count > 1) 
        return {};
    
    string res = "";
    vector<string> rlist;
    if (ch != '.'){
        res += ch;
        fmap[ch]--;
    }

    generatePalRec(res, fmap, rlist, s.size());
    return rlist;
}

vector<string> removeInvalidParentheses(string s) {
    int lc = 0, rc = 0;
    for (char ch : s) {
        if (ch == '(')
            lc++;
        else if(ch==')') {
            lc--;
            if(lc < 0){
                lc = 0;
                rc++;
            }
        }
    }
    string res = "";
    unordered_set<string> pset;
    removeParenRec(s, 0, 0, 0, lc, rc, res, pset);
    vector<string> rlist(pset.begin(), pset.end());
    return rlist;

}

// LC :: 131
bool isPal(string s) {
    int l = 0, r = s.size()-1;
    while (l <= r && s[l] == s[r]){
        l++;
        r--;
    }
    return l > r; 
}

void partitionRec(string s, int index, vector<string> &tlist, vector<vector<string>> &rlist) {
    if (index == s.size()) {
        rlist.push_back(tlist);
        return;
    }
    for (int i = 1; i + index < s.size(); i++) {
        string sub = s.substr(index, i);
        if (isPal(sub)) {
            tlist.push_back(sub);
            partitionRec(s, index + i, tlist, rlist);
            tlist.pop_back();
        }
    } 
}
vector<vector<string>> partition(string s) {
    vector<string> tlist;
    vector<vector<string>> rlist;
    partitionRec(s, 0, tlist, rlist);
    return rlist;
}

// LC :: 680

pair<int, int> isPal(string s, int l, int r) {
    while (l <= r && s[l] == s[r]){
        l++;
        r--;
    }
    return make_pair(l,r); 
}

bool validPalindrome(string s) {
    auto p = isPal(s, 0, s.size()-1);
    if (p.first > p.second) 
        return true;
    else {
        auto p1 = isPal(s, p.first + 1, p.second);
        auto p2 = isPal(s, p.first, p.second -1);
        return (p1.first>p1.second) || (p2.first > p2.second);
    }
}

// LC :: 934 

void dfsColorIsland(vector<vector<int>>& grid, int r , int c, int color, queue<pair<int,int>> &q) {
    if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] != 1)
        return;
    
    grid[r][c] = color;
    q.push({r,c});
    dfsColorIsland(grid, r + 1, c, color, q);
    dfsColorIsland(grid, r - 1, c, color, q);
    dfsColorIsland(grid, r, c + 1, color, q);
    dfsColorIsland(grid, r, c - 1, color, q);

}
bool expandIsland(vector<vector<int>>& grid, queue<pair<int,int>> &q, pair<int,int> u) {
    int x[4] = {-1, 1, 0, 0};
    int y[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int r = u.first + x[i];
        int c = u.second + y[i];
        if (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size()) 
            continue;
        if (grid[r][c] == 1) 
            return true;
        if (grid[r][c] == 0) {
            grid[r][c] = grid[u.first][u.second] + 1;
            q.push({r,c});
        } 
    }
    return false;
}

int shortestBridge(vector<vector<int>>& grid) {
    int i, j;
    queue<pair<int,int>> q;
    // color one of the island to 2
    for (i = 0; i < grid.size(); i++) {
        for (j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1) {
                dfsColorIsland(grid, i, j, 2, q);
                break;
            }
        }
        if (j != grid[0].size())
            break;
    }



    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        if (expandIsland(grid, q, u))
            return grid[u.first][u.second] - 2;

    }
    return -1;
    
}
// LC :: 240 
// non recusive 
bool searchMatrixV2(vector<vector<int>>& matrix, int target) {
    int r = 0, c = matrix[0].size() - 1;
    while (c >= 0 && r < matrix.size()) {
        if (matrix[r][c] == target)
            return true;
        else if (matrix[r][c] > target)
            c--;
        else
            r++; 
    }
    return false;
}
bool searchMatRec(int r, int c, vector<vector<int>>& matrix, int target) {
    if (r < 0 || c < 0 || r >= matrix.size() || c>=matrix[0].size())
        return false;
    if (matrix[r][c] == target) 
        return true;
    else if (target < matrix[r][c])
        return searchMatRec(r, c - 1, matrix, target);
    else
        return searchMatRec(r + 1, c, matrix, target);


}
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    return searchMatRec(0,matrix[0].size() -1, matrix, target);
}

// LC :: 33

int search2(vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() -1;
    while (low <= high){
        int mid = low + (high-low)/2;
        if (nums[mid] == target) 
            return mid;
        else if (nums[low] <= nums[mid]) { // left side sorted
            if (nums[low] <= target && target < nums[mid])
                high = mid - 1;
            else
                low = mid + 1;

        } else { // right side sorted
            if ( nums[mid] < target && target <= nums[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

int search(vector<int>& nums, int target) {
    int l = 0;
    int h = nums.size() - 1;
    while (l < h) {
        int mid = l + (h-l)/2;
        if (nums[mid] > nums[h])
            l = mid + 1;
        else
            h = mid; 
    }
    int splitIndex = l;
    l = 0;
    h = nums.size()-1;
    int realMid = - 1;
    while (l <= h) {
        int mid = l + (h-l)/2;
        int realMid = (splitIndex + mid) % nums.size();
        if(nums[realMid] == target)
            return realMid;
        else if(nums[realMid] < target) {
            l = mid + 1;
        } else
            h = mid - 1;
    }
    return realMid;

}

// LC :: 70

bool existRec(vector<vector<char>>& board, string word, int index, int r, int c) {
    // this should be first condition to check as in corner case 
    // we may endup matching the word in the corner/edge of the board
    if (index == word.size()) {
        return true;
    }
    if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] == '*') {
        return false;
    }
    if (board[r][c] != word[index]) {
        return false;
    }

    char ch = board[r][c];
    board[r][c] = '*';
    bool res = existRec(board, word, index+1, r-1, c) ||
                existRec(board, word, index+1, r+1, c) ||
                existRec(board, word, index+1, r, c-1) ||
                existRec(board, word, index+1, r, c+1);
    board[r][c] = ch;
    return res;

}
bool exist(vector<vector<char>>& board, string word) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++){
            if (existRec(board, word, 0, i, j))
                return true;
        }
    }
    return false;
}

// LC :: 430
class Node {
    public:
        int val;
        Node* prev;
        Node* next;
        Node* child;
    };
Node* flattenRec(Node* head) {
    if (!head) return head;
    Node* dummy = new Node();
    dummy->next = head;
    Node* cur = head;
    Node *p = nullptr;
    while(cur) {
        Node* chList = flattenRec(cur->child);
        cur->child = nullptr;
        p = cur;
        cur = cur->next;
        if(chList) {
            chList->prev->next = cur;
            p->next = chList->next;
            chList->next->prev = p;
            if(cur)
                cur->prev = chList->prev;
            p = chList->prev;
        }
    }
    dummy->prev = p;
    return dummy;
}
Node* flatten(Node* head) {
    if (!head) return head;
    Node* dummy = flattenRec(head);
    return dummy->next;
}

int main(){
    totalNQueens(8);
    return 0;
}