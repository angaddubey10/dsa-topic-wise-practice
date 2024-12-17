# Subset Sum Problem
[Subset Sum Problem](https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1)
```cpp
class Solution{   
public:
    bool isSubsetSumRec(vector<int>&arr, int& targetSum, int currSum, int idx){
        // Plain Recursive Solution
        if(idx>=arr.size()){
            return currSum==targetSum;
        }
        int take = isSubsetSumRec(arr, targetSum, currSum+arr[idx], idx+1);
        int leave = isSubsetSumRec(arr, targetSum, currSum, idx+1);
        return take || leave;
    }
    
    bool isSubsetSumMemo(vector<int>&arr, vector<vector<int>>&dp, int& targetSum, int currSum, int idx){
        if(idx>=arr.size()){
            return currSum==targetSum;
        }
        if(dp[idx][currSum]!=-1)return dp[idx][currSum];
        int take = isSubsetSumMemo(arr, dp,  targetSum, currSum+arr[idx], idx+1);
        int leave = isSubsetSumMemo(arr, dp, targetSum, currSum, idx+1);
        return dp[idx][currSum] = take || leave;
    }
    
    bool isSubsetSumMemo2(vector<int>&arr, vector<vector<int>>&dp, int target, int n){
        //Base Cases
        if(target==0) return true;
        if(n==0){
            return target==arr[0];
        }
        //Recursive Case
        if(dp[n][target]!=-1)return dp[n][target];
        bool leave = isSubsetSumMemo2(arr, dp, target, n-1);
        bool take = false;
        if(target>=arr[n])
            take = isSubsetSumMemo2(arr, dp,  target-arr[n], n-1);
        
        return dp[n][target] = take || leave;
    }
    
    bool isSubsetSumTab(vector<int>&arr,int& target){
        int n=arr.size(); 
        vector<vector<bool>>dp(n, vector<bool>(target+1, false));
        for(int i=0; i<n; i++)dp[i][0]=true; // when target is ZERO
        //for(int i=0; i<target+1; i++)dp[0][target]=fase; //not needed as it's already false
        if(arr[0]<=target)
            dp[0][arr[0]]=true; // when index is ZERO
        for(int i=1; i<n; i++){
            for(int j=1; j<target+1; j++){
                bool leave = dp[i-1][j];
                bool take = false;
                if(j>=arr[i])
                    take = dp[i-1][j-arr[i]];
                dp[i][j] = take || leave;
            }
        }

        return dp[n-1][target];
    }

    bool isSubsetSum(vector<int>arr, int sum){
        return isSubsetSumTab(arr, sum);
        // code here 
        vector<vector<int>>dp(arr.size()+1, vector<int>(10e4+1, -1));
        return isSubsetSumMemo2(arr, dp, sum, arr.size()-1);
        
        return isSubsetSumMemo(arr, dp, sum, 0, 0);
        //Plain Recursion
        return isSubsetSumRec(arr, sum, 0, 0);
    }
};
```