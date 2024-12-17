# Longest Common Subsequence
[1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/description/)
```cpp
class Solution {
public:
    int lcsRec(string &text1, string &text2, int i, int j){
        if(i<0 || j<0) return 0;
        if(text1[i]==text2[j]) return 1 + lcsRec(text1, text2, i-1, j-1);
        return max(lcsRec(text1, text2, i, j-1), lcsRec(text1, text2, i-1, j));
    }

    int lcsMemo(string &text1, string &text2, int i, int j, vector<vector<int>>&dp){
        if(i<0 || j<0) return 0;
        if(dp[i][j]!=-1) return dp[i][j];
        if(text1[i]==text2[j]) return dp[i][j] = 1 + lcsMemo(text1, text2, i-1, j-1, dp);
        return dp[i][j] = max(lcsMemo(text1, text2, i, j-1, dp), lcsMemo(text1, text2, i-1, j, dp));
    }

    //We have moved the indexes 1 step right to handle <0 Case(Index Shifting)
    int lcsMemoIdx(string &text1, string &text2, int i, int j, vector<vector<int>>&dp){
        if(i==0 || j==0) return 0;
        if(dp[i][j]!=-1) return dp[i][j];
        if(text1[i-1]==text2[j-1]) return dp[i][j] = 1 + lcsMemoIdx(text1, text2, i-1, j-1, dp);
        return dp[i][j] = max(lcsMemoIdx(text1, text2, i, j-1, dp), lcsMemoIdx(text1, text2, i-1, j, dp));
    }

    int lcsTab(string &text1, string &text2){
        int m=text1.size(), n=text2.size();
        vector<vector<int>>dp(m+1, vector<int>(n+1,-1));
        for(int j=0; j<=n; j++) dp[0][j] = 0;
        for(int i=0; i<=m; i++) dp[i][0] = 0;
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(text1[i-1]==text2[j-1])  dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i][j-1], dp[i-1][j]); 
            }
        }
        return dp[m][n];
    }

    int lcsSpaceOpt(string &text1, string &text2){
        int m=text1.size(), n=text2.size();
        vector<int>prev(n+1, 0), curr(n+1, 0);
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(text1[i-1]==text2[j-1])  curr[j] = 1 + prev[j-1];
                else curr[j] = max(curr[j-1], prev[j]); 
            }
            swap(prev, curr);
        }
        return prev[n];
    }


    int longestCommonSubsequence(string text1, string text2) {
        return lcsSpaceOpt(text1, text2);

        return lcsTab(text1, text2);

        int m=text1.size(), n=text2.size();

        vector<vector<int>>dp2(m+1, vector<int>(n+1,-1));
        return lcsMemoIdx(text1, text2, m, n, dp2);
        
        vector<vector<int>>dp(m, vector<int>(n,-1));
        return lcsMemo(text1, text2, m-1, n-1, dp);

        return lcsRec(text1, text2, m-1, n-1);
    }
};
```