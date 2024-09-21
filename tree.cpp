#include <stdio.h>
#include "tree.h"
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

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> rlist;
    stack<TreeNode*> stk;
    TreeNode* node = root;
    
    while(!stk.empty() || node != nullptr){
        if (node != nullptr){
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