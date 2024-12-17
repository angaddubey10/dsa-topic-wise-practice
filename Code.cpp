//{ Driver Code Starts

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function template for C++

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
    
    bool isSubsetSumRec2(vector<int>&arr, int targetSum, int i){
        // Optimized Recursion
        if(targetSum==0) return true;
        if(i<0 || targetSum<0) return false;
        return isSubsetSumRec2(arr, targetSum-arr[i], i-1) || isSubsetSumRec2(arr, targetSum, i-1);
    }
    
    bool isSubsetSumMemoR2(vector<int>&arr, int targetSum, int i, vector<vector<int>>&dp){
        if(targetSum==0) return true;
        if(i<0 || targetSum<0) return false;
        if(dp[i][targetSum] != -1) return dp[i][targetSum];
        return dp[i][targetSum] = (isSubsetSumMemoR2(arr, targetSum-arr[i], i-1, dp) || isSubsetSumMemoR2(arr, targetSum, i-1, dp));
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
    
    bool isSubsetSumMemoIdx(vector<int>&arr, int targetSum, int i, vector<vector<int>>&dp){
        if(targetSum==0) return true;
        if(i==0 || targetSum<0) return false;
        if(dp[i][targetSum] != -1) return dp[i][targetSum];
        return dp[i][targetSum] = (isSubsetSumMemoIdx(arr, targetSum-arr[i-1], i-1, dp) || isSubsetSumMemoIdx(arr, targetSum, i-1, dp));
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
    
    bool isSubsetSumTabIdx(vector<int>&arr,int& targetSum){
        int n = arr.size();
        vector<vector<bool>>dp(n+1, vector<bool>(targetSum+1, false));
        for(int i=0; i<=n; i++)dp[i][0] = true;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=targetSum; j++){                
                dp[i][j] = (j>=arr[i-1]? dp[ i-1][j-arr[i-1]] : false)  || dp[i-1][ j] ;
            }
        }
        return dp[n][targetSum];
    }
    
    bool isSubsetSumSpaceOpt(vector<int>&arr,int& targetSum){
        int n = arr.size();
        vector<bool>prev(targetSum+1, false), curr(targetSum+1, false);
        prev[0] = curr[0] = true;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=targetSum; j++){                
                curr[j] = (j>=arr[i-1]? prev[j-arr[i-1]] : false) || prev[j] ;
            }
            swap(prev, curr);
        }
        return prev[targetSum];
    }

    bool isSubsetSum(vector<int>arr, int sum){

        return isSubsetSumSpaceOpt(arr, sum);
        
        return isSubsetSumTabIdx(arr, sum);
        
        return isSubsetSumTab(arr, sum);

        int n = arr.size();
        
        vector<vector<int>>dp2(n+1, vector<int>(sum+1, -1));
        return isSubsetSumMemoIdx(arr, sum, n, dp2);
        
       
        vector<vector<int>>dp(n, vector<int>(sum+1, -1));
        return isSubsetSumMemo2(arr, dp, sum, n-1);
        
        return isSubsetSumMemoR2(arr, sum, n-1, dp);
        
        return isSubsetSumRec2(arr, sum, n-1);
        
        return isSubsetSumRec(arr, sum, 0, 0);
    }
};



//{ Driver Code Starts.

int main() {

    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        vector<int> arr;
        string input;
        getline(cin, input);
        stringstream ss(input);
        int number;
        while (ss >> number) {
            arr.push_back(number);
        }
        int sum;
        cin >> sum;
        cin.ignore();

        Solution ob;
        if (ob.isSubsetSum(arr, sum))
            cout << "true" << endl;
        else
            cout << "false" << endl;
        cout << "~" << endl;
    }
    return 0;
}

// } Driver Code Ends