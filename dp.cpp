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
using namespace std;

// LC :: 53
// Kadane's algo
int maxSubArray(vector<int>& nums) {
    int runningSum = 0;
    int maxSum = 0;
    for (const auto &n : nums){
        runningSum = std::max(n, runningSum + n);
        maxSum = std::max(maxSum, runningSum);
    }
    return maxSum;
}

int maxSubArrayWithLimit(vector<int>& nums, int k){
    int runningSum = 0;
    int maxSum = 0;
    for (const auto &n : nums){
        runningSum = std::max(n, runningSum + n);
        if(maxSum > runningSum && k >= runningSum){
            maxSum = runningSum;
        }
    }
    return maxSum;
}

int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int mSum = INT_MIN;
    for (int i = 0; i < matrix.size(); i++){
        vector<int> sums(matrix[0].size(), 0);
        for(int r = i; r < matrix.size(); r++){
            for (int c = 0; c < matrix[0].size(); c++){
                sums[c]+= matrix[r][c];
            }
            mSum = std::max(mSum, maxSubArrayWithLimit(sums, k));
        }
    }
    return mSum;    
}
// LC :: 1143
int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp(text1.size()+1, vector<int> (text2.size()+1, 0));
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j <dp[0].size(); j++) {
            if (text1[i-1] == text2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[text1.size()][text2.size()];
}

// LC :: 120 
// Triangle minimum path sum
// this is a bottom up approach
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> res(triangle[n -1].size(), 0);
    for (int i = n - 1; i>=0; i--) {
        int sz = triangle[i].size();
        for (int j = 0; j < sz; j++){
            if (i == n-1)
                res[j] = triangle[i][j];
            else {
                res[j] = triangle[i][j] +std::min(res[j], res[j+1]);
            }
        }
    }
    return res[0];    
}

// LC :: 377 
// Combination Sum IV
// The idea is to use dynamic programming to count the number of ways to reach the target sum
// by using the numbers in the given array.
// We dont need a 2D array, we can use a 1D array to store the number of ways to reach each sum.
// We create a dp array where dp[i] represents the number of ways to reach the target i.
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned int> ways(target +1,0);
    ways[0] = 1;
    for (int i = 1; i <= target; i++){
        for(int n: nums){
            if (i >= n) {
                ways[i] += ways[i-n];
            }
        }
    }
    return ways[target];   
}

// LC :: 322 
// Coin Change
// The idea is to use dynamic programming to find the minimum number of coins needed to make up a given amount.
// We create a dp array where dp[i] represents the minimum number of coins needed to make up the amount i.
// We initialize the dp array with a value greater than the maximum possible number of coins (amount + 1).
// We set dp[0] = 0 because no coins are needed to make up the amount 0. and when consider a patricular coin
// we minus that from the amount to get the number of coins needed without that coin and + 1 for the current coin.
// The other option is not consider this coin
// so the dp equation will be dp[i, j] = min(dp[i,j-coins[j]] + 1, dp[i-1,j])
int coinChange(vector<int>& coins, int amount) {
    int max = amount +1;
    vector<int> dp(amount+1, max);
    dp[0] = 0;
    for (int cn : coins) {
        for (int j = cn; j <= amount; j++) {
            dp[j] = std::min(dp[j-cn] + 1, dp[j]);
        }
    }
    return dp[amount] == amount + 1? -1 : dp[amount];       
}
int main(){
    return 0;
}

// LC :: 300
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 0);
    //dp[0] = 1;
    int len = 0;
    for (int i = 0; i < nums.size(); i++){
        for (int j = 0; j<i; j++) {
            if( nums[j] < nums[i]){
                dp[i] = std::max(dp[i], dp[j]);
            }
        }
        dp[i]+=1;
        len = std::max(len, dp[i]);

    }
    return len;
    
}