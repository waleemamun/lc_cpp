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

// 918. Maximum Sum Circular Subarray
// Use the kadane's algo to get rhe maximum sub array sum approach
// so the solution would be either Kadane's maximum subarray sum or
// if the wrapped around part can make better result
// | sub array sum| min sub array sum | sub array sum|
// if first + last portions add upto greater than the regular kadane's max sub array sum

int maxSubarraySumCircular(vector<int>& nums) {
    int curSum = 0;
    int maxSum = nums[0];
    int minSum = nums[0];
    int totSum = 0;
    int curMin = 0;
    for (int n : nums) {
        // Kadane's algo to max subarray sum
        curSum = std::max(curSum + n, n);
        maxSum = std::max(maxSum, curSum);
        // Kadane's algo to min subarray sum
        curMin = std::min(curMin + n, n);
        minSum = std::min(curMin, minSum);
        // total sum
        totSum += n;
    }
    if (totSum == minSum) // if they are equal the diff would be zero
        return maxSum;
    return std::max(maxSum, totSum - minSum);
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

// LC :: 62
int uniquePaths(int m, int n) {
    vector<int> dp(n,0);
    dp[0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[j] = dp[j] + dp[j-1];
        }
    }
    return dp[n-1];
}

// LC :: 63 

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    unsigned int n = obstacleGrid.size();
    unsigned int m = obstacleGrid[0].size();
    vector<int> dp(m, 0);

    if(n == 1 && m == 1) return !obstacleGrid[0][0];
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            if (i == 0 && j == 0)
                dp[j] = 1;
            else if (i == 0) {
                dp[j] = !obstacleGrid[i][j] & dp[j-1] & !obstacleGrid[i][j-1];
            }
            else if (j == 0) {
                dp[j] = !obstacleGrid[i][j] & dp[j] & !obstacleGrid[i-1][j];
            }
            else if (obstacleGrid[i][j] == 1)
                dp[j] = 0;
            else
                dp[j] = dp[j] + dp[j-1];
        }
    }
    return dp[m-1];
    
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
// The problem is asking if given an array of nums and a target you need reach the target with any combination from 
// the array and you are allowed to use the same number any amount of time/
// The KEY IDEA is you can use the same number any amoiunt of time then it becomes 
// you have to check if the what is the best option using the all the options from the array
// so the dp equation will be dp[i, j] = min(dp[i,j-coins[j]] + 1, dp[i-1,j])
// or optimized DP equation dp(j) = min (dp[j-cn] + 1, dp[j])
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

// LC :: 518 
// Coin Change II
// Here the difference is we are asked to find out the number of combination that makes the solution
// Because here we are asked to find # of comobination for each dp entry have to check the combinaton 
// with the current coin and without the coin and add both combnination.
// DP eqn : dp(i,j) = dp(i-1,j) + dp(i,j-coin(i)) 
// opt dp eqn dp(j) = dp (j) + dp(j-cn)
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount +1, 0);
    dp[0] = 1;
    for (int cn: coins) {
        for (int j = cn; j <= amount; j++) {
            dp[j] = dp[j] +  dp[j-cn];
        }
    }
    return dp[amount];
    
}

// LC :: 198

int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    vector<int> dp(nums.size() +1, 0);
    dp[0] = 0;
    dp[1] = nums[0];
    for (unsigned int i = 2; i <= nums.size(); i++) {
        dp[i] = std::max(dp[i-2] + nums[i-1], dp[i-1]);
    }
    return dp[nums.size()];
}

// optimized version O(1) space
int rob2(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int last = 0;
    int lastlast = 0;
    for (int n : nums) {
        int tmp = last;
        last = std::max(last, lastlast + n);
        lastlast = tmp; 
    }
    return last;
}

// LC :: 213
int rob_213(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int last = 0;
    int lastlast = 0;
    // start at the first and you cannot take the last element
    for (int i = 0; i<nums.size()-1;  i++) {
        int tmp = last;
        last = std::max(last, lastlast + nums[i]);
        lastlast = tmp;; 
    }
    int res = last;
    lastlast = 0;
    last = 0;
    // start at the second and you can take the last element
    for (int i = 1; i<nums.size();  i++) {
        int tmp = last;
        last = std::max(last, lastlast + nums[i]);
        lastlast = tmp;
    }
    return std::max(last, res);
}

// LC :: 64

int minPathSum(vector<vector<int>>& grid) {
    unsigned int n = grid.size();
    unsigned int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int> (m, 0));

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            if(i==0 && j==0)
                dp[i][j] = grid[i][j];
            else if(i == 0)
                dp[i][j] = dp[i][j-1] + grid[i][j];
            else if (j == 0)
                dp[i][j] = dp[i-1][j] + grid[i][j];
            else 
                dp[i][j] = std::min(dp[i][j-1], dp[i-1][j]) + grid[i][j];
        } 
    }
    return dp[n-1][m-1];
}

int minPathSum2(vector<vector<int>>& grid) {
    unsigned int n = grid.size();
    unsigned int m = grid[0].size();
    vector<int> dp(m, 0);

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            if(i==0 && j==0)
                dp[j] = grid[i][j];
            else if(i == 0)
                dp[j] = dp[j-1] + grid[i][j];
            else if (j == 0)
                dp[j] = dp[j] + grid[i][j];
            else 
                dp[j] = std::min(dp[j-1], dp[j]) + grid[i][j];
        } 
    }
    return dp[m-1];
}

// LC :: 63

int uniquePathsWithObstacles_63(vector<vector<int>>& obstacleGrid) {
    unsigned int n = obstacleGrid.size();
    unsigned int m = obstacleGrid[0].size();
    vector<vector<int>> dp(n, vector<int> (m, 0));
    dp[0][0] = 1;
    for (int i = 1; i<n; i++) {
        dp[0][i] = dp[0][i-1];
        if(obstacleGrid[0][i] == 1)
            dp[0][i] = 0;
    }
    for (int i = 1; i<m; i++) {
        dp[i][0] = dp[i-1][0];
        if(obstacleGrid[i][0] == 1)
            dp[i][0] = 0;
    }
    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int j = 1; j < m; j++) {
            if (obstacleGrid[i][j] == 1)
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[n-1][m-1];
    
}

// optimized version this did not pass all case look at the above solution

int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
    unsigned int n = obstacleGrid.size();
    unsigned int m = obstacleGrid[0].size();
    vector<int> dp(m, 0);
    dp[0] = 1;
    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int j = 1; j < m; j++) {
            if (obstacleGrid[i][j] == 1)
                dp[j] = 0;
            else
                dp[j] = dp[j] + dp[j-1];
        }
    }
    return dp[m-1];
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

// LC :: 788
// Using DP this problem become O(n) time and space.
// The brute force is also O(n*d) where d is the length of the digit, where d is close to 6 so O(n*d) == O(n)
// But the DP approach is nice
// The idea is to check if we can decompose the current digit to some previous digits which can be rotated
// for example if the current digit is 212 we decompose it to 21 and 2 and check if 21 and 2 are rotatable
// if true we mark this '212' as rotatable and increase count. Special case is number 0,1 and 8 where we the
// dp state 1 indicates this is rotateble but if it forms with another digit with dp state 2
// dp[i] = 2 if dp[i/10]>=1 and dp[i%10] >=1 valid rotatable number
// dp[i] = 1 if dp[i/10] == 1  and dp[i%10] == 1 valid same number
// else dp[i] = 0 invalid number
int rotatedDigits(int n) {
    vector<int> digits(n+1 , 0);
    int count = 0;
    digits[0] = 1;

    for (int i = 1; i <= n; i++){
        if (i < 10) {
            if (i == 1 || i == 8 || i == 0) 
                digits[i] = 1;
            if (i == 2 || i == 5 || i == 6 || i == 9) {
                digits[i] = 2;
                count++;
            }
        } else {
            if (digits[i/10] == 1 && digits[i%10] == 1){
                digits[i] = 1;
            }else if (digits[i/10] >= 1 && digits[i%10] >= 1) {
                digits[i] = 2;
                count++;
            }
        }
    }
    return count;
}

// non DP solution O(n*d) the DP solution is better and easy
int rotatedDigits_non_DP(int n) {
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