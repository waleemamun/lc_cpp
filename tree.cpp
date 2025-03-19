#include <stdio.h>
#include "tree.h"
#include "list.h"
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <regex>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
using namespace std;

void printHelper(TreeNode* root, string padding, string arrow, bool hasSibling) 
{
    if(root!= nullptr){
        string st = padding + arrow + to_string(root->val);
        printf("%s\n",st.c_str());
        if (hasSibling)
            padding += "|  ";
        else
            padding += "   ";
        printHelper(root->left, padding, "|--",root->right!=nullptr);
        printHelper(root->right, padding, "|->", false);
    }
}
void print(TreeNode* root)
{
    if (root==nullptr)
        return;
    printf("%d\n", root->val);
    string lArrow = "|--";
    string rArrow = "|->";
    printHelper(root->left, "", lArrow, root->right!=nullptr);
    printHelper(root->right, "", rArrow, false);
    
}

// LC :: 104

int maxDepth(TreeNode* root) {
    if (root==nullptr) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right)); 
    
}

// LC :: 226

TreeNode* invertTree(TreeNode* root) {
    if(!root)
        return nullptr;
    TreeNode* l = invertTree(root->left);
    TreeNode* r = invertTree(root->right);
    root->left  = r;
    root->right = l;
    return root;
}

TreeNode* createBSTRec(int arr[], int low, int high) {
    if (low>high) 
        return nullptr;
    int mid = low + (high - low)/2;
    TreeNode* node = new TreeNode(arr[mid]);
    node->left = createBSTRec(arr,low, mid-1);
    node->right = createBSTRec(arr, mid+1, high);
    return node; 
}

void deleteTree(TreeNode* root){
    if(root==nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void inorder(TreeNode* root)
{
    if(root == nullptr)
        return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);

}

// LC:: 98
// This is the correct solution for the problem
// To check a tree is BST or not we need to check the inorder traversal of the tree is sorted or not
bool isValidBST(TreeNode* root) {
    TreeNode* node = root;
    stack<TreeNode*> stk;
    TreeNode* lastPopNode = nullptr;

    while(!stk.empty() || node) {
        if(node) {
            stk.push(node);
            node = node->left;
        } else {
            node = stk.top();
            stk.pop();
            if (lastPopNode && lastPopNode->val >= node->val) {
                return false;
            }
            lastPopNode = node;
            node = node->right;
        }
    }
    return true;
}

// LC :: 230
int kthSmallest(TreeNode* root, int k) {
    TreeNode* node = root;
    stack<TreeNode*> stk;

    while(!stk.empty() || node) {
        if(node) {
            stk.push(node);
            node = node->left;
        } else {
            node = stk.top();
            stk.pop();
            k--;
            if (k == 0)
                return node->val;
            node = node->right;
        }
    }
    return INT_MAX;
}
// LC :: 108

TreeNode* arr2BSTRec(vector<int>& nums, int low, int high){
    if (low > high)
        return nullptr;
    int mid = low + (high-low)/2;
    TreeNode* node = new TreeNode(nums[mid]);
    node->left = arr2BSTRec(nums, low, mid - 1);
    node->right = arr2BSTRec(nums, mid + 1, high);
    return node; 
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return arr2BSTRec(nums, 0, nums.size() - 1);
}

// LC::530
int getMinimumDifference(TreeNode* root) {
    TreeNode* lastPopNode = nullptr;
    TreeNode* node = root;
    stack<TreeNode*> stk;
    int diff = INT_MAX;
    while(!stk.empty() || node) {
        if(node) {
            stk.push(node);
            node = node->left;
        } else {
            node = stk.top();
            stk.pop();
            if (lastPopNode) {
                diff = std::min(diff, std::abs(lastPopNode->val - node->val));
            }
            lastPopNode = node;
            node = node->right;
        }
    }
    return diff;
    
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> rlist;
    stack<TreeNode*> stk;
    TreeNode* node = root;
    
    while(!stk.empty() || node){
        if (node){
            stk.push(node);
            node = node->left;
        } else {
            node = stk.top();
            rlist.push_back(node->val);
            stk.pop();
            node = node->right;
        }
    }
    return rlist;    
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> rlist;
    stack<TreeNode*> stk;
    TreeNode* node = root;
    if (root == nullptr)
        return rlist;
    stk.push(node);
    while(!stk.empty()){
        node = stk.top();
        rlist.push_back(node->val);
        stk.pop();
        if (node->right != nullptr)
            stk.push(node->right);
        if (node->left != nullptr)
            stk.push(node->left);
    }
    return rlist;
}

vector<int> postorderTraversal(TreeNode* root) {

    vector<int> rlist;
    stack<TreeNode*> stk;
    TreeNode* node = root;
    TreeNode* sn = nullptr;
    
    while(!stk.empty() || node != nullptr){
        if (node != nullptr){
            stk.push(node);
            node = node->left;
        } else {
            node = stk.top();
            if (node->right == nullptr || node->right == sn) {
                sn = node;
                rlist.push_back(node->val);
                stk.pop();
                node = nullptr;
            } else {
                node = node->right;

            }            
        }
    }
    return rlist;   
}

vector<TreeNode*> genBST(int start, int end) {
    vector<TreeNode*> rlist;
    if (start > end){
        rlist.push_back(nullptr);
        return rlist;
    }
    if (start == end) {
        TreeNode* node = new TreeNode(start);
        rlist.push_back(node);
        return rlist;
    }

    for (int i = start; i <= end; i++){
        vector<TreeNode*> leftList = genBST(start, i -1);
        vector<TreeNode*> righList = genBST(i+1,end);

        for (const auto& left : leftList){
            for (const auto& right: righList){
                TreeNode* root = new TreeNode(i);
                root->left = left;
                root->right= right;
                rlist.push_back(root);
            }
        }
    }
    return rlist;
}

vector<TreeNode*> generateTrees(int n) {
    return genBST(1,n);
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> rlist;
    if (root == nullptr) return rlist;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> tlist;
        for (int i=0; i<size;i++){
            TreeNode* node = q.front();
            tlist.push_back(node->val);
            q.pop();
            if (node->left!=nullptr) 
                q.push(node->left);
            if (node->right!=nullptr) 
                q.push(node->right);
        }
        rlist.push_back(tlist);
    }
    return rlist;
    
}

int pIdx = -1;
std::unordered_map<int, int> inMap;
TreeNode* bldTree(vector<int>& preorder, vector<int>& inorder, int st, int end){
    if (st > end)
        return nullptr;
    int val = preorder[++pIdx];
    int idx = inMap[val];
    TreeNode* root = new TreeNode(val);
    root->left = bldTree(preorder, inorder, st, idx-1);
    root->right = bldTree(preorder, inorder, idx+1, end);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (int i = 0; i < inorder.size(); i++){
        inMap[inorder[i]] = i;
    }
    return bldTree(preorder, inorder, 0, inorder.size()-1);   
}

TreeNode* flattenRec(TreeNode* root)
{
    if (root == nullptr || (root->left==nullptr && root->right==nullptr)){
        return root;
    }
    TreeNode* ltail = flattenRec(root->left);
    TreeNode* rtail = flattenRec(root->right);
    if (ltail != nullptr) {
        ltail->right = root->right;
        root->right= root->left;
        root->left = nullptr;

    }
    return rtail == nullptr? ltail: rtail;
}
void flatten(TreeNode* root) {
       flattenRec(root);
}

int maxPSumRec(TreeNode* root, int &maxSum){
    if(root==nullptr) 
        return 0;
    int left =  maxPSumRec(root->left, maxSum);
    int right = maxPSumRec(root->right, maxSum);
    int tmp = std::max(root->val + std::max(left, right), root->val);
    maxSum = std::max(maxSum, std::max(tmp, root->val+left+right));
    return tmp;
}
// Succesor node is if the node has right child then the right subtree's smallest aka leftmost node
// if no right child then the ancest for which the node is a left child will be the successor
// Predeceessor node is if the the node has a left child then the biggest node in the left tree aka 
// the rightmost child is the predecessor node. If no left child then the ancestor which has the node as 
// the right child is aka the rightancestor is the predecessor

TreeNode* predNode(TreeNode* root, TreeNode* node) {
    TreeNode* cur = root;
    TreeNode* pred = nullptr;
    while (cur!=nullptr) {
        if (cur->val < node->val) {
            pred = cur;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    return pred;
}

vector<int> rightSideView(TreeNode* root) {
    queue<TreeNode*> q;
    vector<int> rlist;
    if (root==nullptr)
        return rlist;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        for (int i = 0; i < size; i++){
            TreeNode* node = q.front();
            q.pop();
            if (i == 0)
                rlist.push_back(node->val);
            if (node->right!=nullptr)
                q.push(node->right);
            if (node->left!=nullptr)
                q.push(node->left);
        }
    }
    return rlist;
}

std::vector<std::string> split(const std::string& s, const std::string& regex_str) {
    std::regex regex(regex_str);
    return std::vector<std::string>(
        std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
        std::sregex_token_iterator()
    );
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


void serializeRec(TreeNode* root, ostringstream &data){
    if (root==nullptr) {
        data << "# ";
    } else {
        data << root->val << ' ';
        serializeRec(root->left, data);
        serializeRec(root->right, data);
    }

}

std::string serialize(TreeNode* root) {
    ostringstream data;
    serializeRec(root, data);
    return data.str();
}

TreeNode* deserializeRec(istringstream &data){
    string st;
    data>>st;
    if (st == "#")
        return nullptr;
    TreeNode* root = new TreeNode(stoi(st));
    root->left = deserializeRec(data);
    root->right = deserializeRec(data);
    return root;

}

TreeNode* deserialize(string data) {
    istringstream iData(data);
    return deserializeRec(iData);
}

int minhz;
int maxhz;

// LC :: 314
void minmaxdist(TreeNode* root, int dist){
    if (root == nullptr)
        return;
    if (dist > maxhz)
        maxhz = dist;
    if (dist < minhz)
        minhz = dist;
    minmaxdist(root->left, dist -1);
    minmaxdist(root->right, dist + 1);
}

void verticalOrderRec(TreeNode* root, int dist, int level, 
                        vector<vector<int>> &rlist,
                        vector<vector<int>> &lvlist) {
    if (root == nullptr)
        return;
    int idx = dist + abs(minhz);
    int l = 0;
    while(l<lvlist[idx].size() && level >= lvlist[idx][l])
        l++;
    lvlist[idx].insert(lvlist[idx].begin() + l, level);
    rlist[idx].insert(rlist[idx].begin() + l, root->val);
    verticalOrderRec(root->left, dist - 1, level + 1, rlist, lvlist);
    verticalOrderRec(root->right, dist + 1, level + 1, rlist, lvlist);
}

vector<vector<int>> verticalOrder(TreeNode* root) {
    minhz = INT_MAX;
    maxhz = INT_MIN;
    minmaxdist(root, 0);
    int len = maxhz - minhz + 1;
    vector<vector<int>> rlist(len);
    vector<vector<int>> lvlist(len);
    verticalOrderRec(root, 0, 0, rlist, lvlist);
    return rlist;
}

vector<vector<int>> verticalOrderV2(TreeNode* root) {
    vector<vector<int>> rlist;
    if (!root) {
        return rlist;
    }
    // we are using a oderdered map aka TreeMap so that when we iterate on 
    // the map we can iterate from lowest key to highest key
    map<int,vector<int>> hashmap;
    queue<pair<int, TreeNode*>> q;
    q.push(make_pair(0, root));
    while(!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++){
            TreeNode* node = q.front().second;
            int idx = q.front().first;
            hashmap[idx].push_back(node->val);
            q.pop();
            if (node->left!= nullptr)
                q.push(make_pair(idx-1,node->left));
            if (node->right!= nullptr)
                q.push(make_pair(idx+1,node->right));

        }
    }
    for (auto& v: hashmap) {
        rlist.push_back(v.second);
    }
    return rlist;
}
// LC :: 987
vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<vector<int>> rlist;
    if (!root)
        return rlist;
    struct Cmp {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
            return a.first == b.first ? a.second < b.second : a.first < b.first;
        }
    };
    map<int, std::multiset<pair<int,int>, Cmp>> treeMap;
    queue<pair<int, TreeNode*>> q;
    q.push({0,root});
    int level = 0;
    while(!q.empty()){
        int sz = q.size();
        for (int i = 0; i<sz; i++){
            TreeNode* nd = q.front().second;
            int idx = q.front().first;
            q.pop();
            treeMap[idx].insert({level, nd->val});
            if (nd->left)
                q.push({idx-1, nd->left});
            if(nd->right)
                q.push({idx+1,nd->right});
        }
        level++;
    }

    for (auto &[k, pairlst]:treeMap){
        vector<int> vc;
        for (auto& [a,b]: pairlst){
            vc.push_back(b);
        }
        rlist.push_back(vc);

    }

    return rlist;
}



bool isValidSerialization(string preorder) {
    vector<string> ndList = split(preorder,',');
    int leaves = 0;
    int nonleaves = 0;
    for (string nd: ndList){
        if(nd == "#")
            leaves++;
        else 
            nonleaves++;
    }
    return leaves == (nonleaves+1);
}




int maxPathSum(TreeNode* root) {
    int maxSum = 0;
    maxPSumRec(root, maxSum);
    return maxSum;
}


void pSumRec(TreeNode* root, int targetSum, unordered_map<long, int> &map, int &count, long runningSum){
    if(root == nullptr)
        return;
    runningSum+= root->val;

    if (map.find(runningSum - targetSum)!= map.end()){
        count+=map[runningSum - targetSum];
    }
    // this has to increase after the if condition above as the path involves at lease two nodes not the self node
    map[runningSum]+=1;
    pSumRec(root->left, targetSum, map, count, runningSum);
    pSumRec(root->right, targetSum, map, count, runningSum);
    map[runningSum]-=1;
}
int pathSum(TreeNode* root, int targetSum) {
    unordered_map<long, int> map;
    map[0] = 1;
    int count = 0;
    pSumRec(root, targetSum, map, count, 0);
    return count;   
}

void traverse(TreeNode* root, int high, int low, int &diff){
    if (root==nullptr)
        return;
    high = std::max(high, root->val);
    low = std::min(low, root->val);
    diff = std::max(diff, std::abs(high - low));
    traverse(root->left, high, low, diff);
    traverse(root->right, high, low, diff);
}
int maxAncestorDiff(TreeNode* root) {
    int diff = 0;
    if (root == nullptr) return diff;
    traverse(root, root->val, root->val, diff);
    return diff;
}

void getKthDistantNode(TreeNode* root, int k, vector<int> &lst){
    if (root == nullptr || k < 0) 
        return;
    if (k == 0) {
        lst.push_back(root->val);
        return;
    }
    getKthDistantNode(root->left, k - 1, lst);
    getKthDistantNode(root->right, k - 1, lst); 

}
int getKNodes(TreeNode* root, TreeNode * target, int k, vector<int> & lst){
    if (root == nullptr)
        return -1;
    if (root == target) {
        getKthDistantNode(root, k, lst);
        return 1;
    }
    int l = getKNodes(root->left, target, k, lst);
    int r = getKNodes(root->right, target, k , lst);
    if (l > 0) {
        if (l < k)
            getKthDistantNode(root->right, k - l - 1, lst);
        else if (l == k)
            lst.push_back(root->val);
        return l + 1;
    } else if (r > 0) {
        if (r < k) 
            getKthDistantNode(root->left, k - r - 1, lst);
        else if (r == k)
            lst.push_back(root->val);
        return r + 1;
    } else 
        return -1;
}
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    vector<int> rlist;
    if (!root) return rlist;
    getKNodes(root, target, k, rlist);
    return rlist;
}

TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    if (!root) return root;
    TreeNode* cur = root;
    TreeNode* leftAncestor = nullptr;
    while(cur!=nullptr) {
        if(p->val < cur->val){
            leftAncestor = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return leftAncestor;    
}

// LC :: 101
bool isSmRec(TreeNode* p, TreeNode* q) {
    if (!p && !q)
        return true;
    if (p == nullptr || q == nullptr)
        return false;
    return (p->val == q->val) && 
        isSmRec(p->left, q->right) && 
        isSmRec(p->right, q->left);
}
bool isSymmetric(TreeNode* root) {
    return isSmRec(root, root); 
}

// LC:: 100
// Recursive approach vs stack approach
bool isSameTree2(TreeNode* p, TreeNode* q) {
    if (!p && !q)
        return true;
    if (p == nullptr || q == nullptr)
        return false;
    return (p->val == q->val) && 
            isSameTree2(p->left, q->left) && 
            isSameTree2(p->right, q->right);    
}

bool isSameTree(TreeNode* p, TreeNode* q) {
    stack<TreeNode*> stk;
    stk.push(q);
    stk.push(p);
    while(!stk.empty()) {
        p = stk.top();
        stk.pop();
        q = stk.top();
        stk.pop();
        if (!p && !q)
            continue;
        if (p == nullptr || q == nullptr || p->val != q->val)
            return false;
        stk.push(q->right);
        stk.push(p->right);
        stk.push(q->left);
        stk.push(p->left);
    }
    return true;
}

int postIdx = 0;
TreeNode* bldTreeRec(vector<int>& inorder, vector<int>& postorder, int start, int end, unordered_map<int, int> &imap){
    if (start > end)
        return nullptr;
    int val = postorder[postIdx++];
    int idx = imap[val];
    TreeNode* node = new TreeNode(val);
    node->right = bldTreeRec(inorder, postorder, idx + 1, end, imap);
    node->left = bldTreeRec(inorder, postorder, start, idx - 1, imap);
    return node;
}

TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> imap;
    for (int i = 0; i < inorder.size(); i++) {
        imap[inorder[i]] = i;
    }
    std::reverse(postorder.begin(), postorder.end());
    return bldTreeRec(inorder, postorder, 0, inorder.size() -1, imap);
}

bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr)
        return false;
    if (!root->left && !root->right)
        return (targetSum - root->val) == 0;

    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);    
}
int smrTot;
void sumNumRec(TreeNode* root, int sum) {
    if (!root)
        return;
    if (!root->left && !root->right) {
        sum+= root->val;
        smrTot+= sum;
        return;
    }
    sum += root->val;
    sum *= 10;
    sumNumRec(root->left, sum);
    sumNumRec(root->right, sum);
}

class BSTIterator {
private:
    stack<TreeNode*> stk;
    TreeNode* node;
public:
    BSTIterator(TreeNode* root) {
        node = root;
        while(node) {
            stk.push(node);
            node = node->left;
        }
    }
    
    int next() {
        node = stk.top();
        stk.pop();
        int val = node->val;
        node = node->right;
        return val;
    }
    
    bool hasNext() {
        while(node){
            stk.push(node);
            node = node->left;
        }
        return !stk.empty();      
    }
};

// LC :: 222

int heightTree(TreeNode* root){
    int h = 0;
    while(root) {
        root = root->left;
        h++;
    }
    return h;
}

int countNodes(TreeNode* root) {
    if (root == nullptr)
        return 0;
    int lh = heightTree(root->left);
    int rh = heightTree(root->right);
    if(lh > rh){
        return ((1 << rh)) + countNodes(root->left);
    } else {
        return ((1 << lh)) + countNodes(root->right);
    }
    
}

// LC :: 637
vector<double> averageOfLevels(TreeNode* root) {
    queue<TreeNode*> q;
    vector<double> res;
    q.push(root);
    while(!q.empty()) {
        int sz = q.size();
        long sum = 0;
        for (int i = 0; i < sz; i++) {
            TreeNode *node = q.front();
            sum += node->val;
            q.pop();
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        double avg = static_cast<double>(sum)/static_cast<double>(sz);
        res.push_back(avg); 
    }

    return res;
}
class TrieNode {
    public:
        string val;
        bool isEnd;
        unordered_map<string, TrieNode*> children;
        TrieNode(string v) : val(v), isEnd(false) {}
        ~TrieNode() = default;
};

vector<string> removeSubfolders(vector<string>& folder) {
    vector<string> res;
    TrieNode *root = new TrieNode("*");

    // create the trie from the path
    for (string fl : folder) {
        std::istringstream ism(fl);
        string token;
        TrieNode *cur = root;
        while(std::getline(ism, token,'/')) {
            if(cur->children.find(token) == cur->children.end()) {
                cur->children[token] = new TrieNode(token);
            }
            cur = cur->children[token];
        }
        cur->isEnd = true;
    }
    // now remove the sub folders
    for (string fl : folder){
        std::istringstream ism(fl);
        string token;
        TrieNode* cur = root;
        bool isSub = false;
        while(std::getline(ism, token, '/')){
            cur = cur->children[token];
            if (cur->isEnd && ism.rdbuf()->in_avail() != 0){
                isSub=true;
                break;
            } 
        }
        if (!isSub)
            res.push_back(fl);
    }
    return res;
}


int sumNumbers(TreeNode* root) {
    smrTot = 0;
    sumNumRec(root, 0);
    return smrTot;
}

// LC :: 1367
// Lets try a dfs approach to solve this problem
// The idea is to traverse the tree and for each node we will check if the node is the start of the
// List. If it is then we will check if the List is present in the tree. If it is then we will
// return true else we will continue the search. If we reach the end of the List then we will return true
// as we have found the List in the tree. If we reach the end of the tree and the List is not found
bool dfsVisit(ListNode* node, TreeNode* root){
    if (!node) return true;
    if (!root) return false;
    if(node->val != root->val) 
        return false;
    else
        return dfsVisit(node->next, root->left) || dfsVisit(node->next, root->right);
}
bool dfs(ListNode* node, TreeNode* root){
    if (!root) return false;
    if (dfsVisit(node, root))
        return true;
    else 
        return dfs(node, root->left) || dfs(node, root->right);
}

bool isSubPath(ListNode* head, TreeNode* root) {
    if (!head||!root)
        return false;
    return dfs(head, root);
    
}

// LC :: 95 
// This is implemented using DP memoization
// we keep a memoization dp (tree root list)for (start,end) pair
vector<TreeNode*> genBST(int start, int end, unordered_map<int, vector<TreeNode*>> &dp) {
    vector<TreeNode*> rlist;
    if (start > end){
        rlist.push_back(nullptr);
        return rlist;
    }
    auto cmp = [&start, &end](){return start*100 + end;};
    if (dp.count(cmp())) {
        return dp[cmp()];
    }

    for (int i = start; i <= end; i++){
        vector<TreeNode*> leftList = genBST(start, i -1, dp);
        vector<TreeNode*> righList = genBST(i+1,end, dp);

        for (const auto& left : leftList){
            for (const auto& right: righList){
                TreeNode* root = new TreeNode(i);
                root->left = left;
                root->right= right;
                rlist.push_back(root);
            }
        }
    }
    dp[cmp()] = rlist;
    return rlist;
}

// LC :: 865
pair<TreeNode*, int> subTreeDeepRec(TreeNode* root) {
    if(!root) {
        return {nullptr, 0};
    }
    auto lsTree = subTreeDeepRec(root->left);
    auto rsTree = subTreeDeepRec(root->right);
    if (lsTree.second == rsTree.second) {
        return {root, lsTree.second + 1};
    } else {
        auto &sTree = lsTree.second > rsTree.second ? lsTree: rsTree;
        return {sTree.first, sTree.second + 1}; 
    }
}
TreeNode* subtreeWithAllDeepest(TreeNode* root) {
    auto sTree = subTreeDeepRec(root);
    return sTree.first;
}

vector<TreeNode*> generateTreesDP(int n) {
    unordered_map<int, vector<TreeNode*>> dp;
    return genBST(1,n, dp);
}

// LC :: 110

int getHeightBalancedTree(TreeNode* root) {
    if (!root)
        return 0;
    int left = getHeightBalancedTree(root->left);
    if (left == -1)
        return -1;
    int right = getHeightBalancedTree(root->right);
    if (right == -1)
        return -1;
    if(std::abs(right - left) > 1)
        return -1;
    return 1 + std::max(left, right);
}
bool isBalanced(TreeNode* root) {
    return getHeightBalancedTree(root) == -1 ? false : true;
}

// LC :: 111

int minDepth(TreeNode* root) {
    if (!root)
        return 0;
    int left = minDepth(root->left);
    int right = minDepth(root->right);
    if (left == 0) 
        return 1 + right;
    else if (right == 0)
        return 1 + left;
    else
        return 1 + std::min(left, right);

}

// LC :: 235
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || p == root || q == root)
        return root;
    if(root->val > p->val && root->val > q->val) {
        return lowestCommonAncestor(root->left, p, q);
    } else if (root->val < p->val && root->val < q->val){
        return lowestCommonAncestor(root->right, p, q);
    } else 
        return root;
    
}

TreeNode* lowestCommonAncestorV2(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    vector<int> pathP;
    vector<int> pathQ;
    TreeNode* cur = root;
    while (cur) {
        pathP.push_back(cur->val);
        if(p->val == cur->val) 
            break;
        else if (cur->val > p->val){
            cur = cur->left;
        } else 
            cur = cur->right;
    }
    cur = root;
    while (cur) {
        pathQ.push_back(cur->val);
        if(q->val == cur->val) 
            break;
        else if (cur->val > q->val){
            cur = cur->left;
        } else 
            cur = cur->right;
    }
    int sz = pathP.size() < pathQ.size() ? pathP.size() : pathQ.size();
    int last = 0;
    for (int i = 0; i < sz; i++){
        if (pathP[i] != pathQ[i])
            break;
        last = pathP[i];
    }
    cur = root;
    while (cur){
        if(cur->val == last)
            return cur;
        else if (cur->val>last)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return nullptr;
}

// LC :: 938

int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root)
        return 0;
    if (root->val > high)
        return rangeSumBST(root->left, low, high);
    else if (root->val < low)
        return rangeSumBST(root->right, low, high);
    else
        return root->val 
            + rangeSumBST(root->left, low, root->val - 1) 
            + rangeSumBST(root->right, root->val + 1, high);       
}

// LC :: 257

void binaryTreePathsRec(TreeNode* root, string path, vector<string> &rlist) {
    if(!root) return;
    string oldPath = path;
    if(!root->right && !root->left) {
        path += std::to_string(root->val);
        rlist.push_back(path);
        path = oldPath;
        return;
    }

    path += std::to_string(root->val) + "->";
    binaryTreePathsRec(root->left, path, rlist);
    binaryTreePathsRec(root->right, path, rlist);
    path = oldPath;


}
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> rlist;
    binaryTreePathsRec(root, "",rlist);
    return rlist;
}

// LC :: 331 

vector<string> split(string &s, char delim){
    istringstream tokenstrm(s);
    string token;
    vector<string> tokens;
    while(std::getline(tokenstrm, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

bool isValidSerialization(string preorder) {
    vector<string> ndList = split(preorder,',');
    int slots = 1;
    for (string nd: ndList){
        slots -= 1;
        if (slots < 0) 
            return false;
        if (nd!="#")
            slots += 2;

    }
    return slots == 0;
}

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    TreeNode* root = createBSTRec(arr, 0, 9);
    print(root);
    inorder(root);
    deleteTree(root);
    inorder(root);
    printf("\n");
    const std::string str = "1,2,3,4,6";
    vector<string> vc = split(str,",");
    for (const auto& st: vc){
        cout << st << endl;
    }
    return 0;
}