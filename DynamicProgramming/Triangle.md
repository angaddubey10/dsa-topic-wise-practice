# Triangle
[120. Triangle](https://leetcode.com/problems/triangle/description/)

```cpp
class Solution {
public:
    int minimumTotalRec(vector<vector<int>>& triangle, int row, int col){
        if(row>=triangle.size() || col>=triangle[row].size()) return INT_MAX;
        if(row==triangle.size()-1) return triangle[row][col];
        int bottom, bottomright;
        bottom = minimumTotalRec(triangle, row+1, col);
        bottomright = minimumTotalRec(triangle, row+1, col+1);
        return triangle[row][col] + min(bottom, bottomright);
    }

    int minimumTotalMemo(vector<vector<int>>& triangle, vector<vector<int>>& dp, int row, int col){
        if(row>=triangle.size() || col>=triangle[row].size()) return INT_MAX;
        if(row==triangle.size()-1) return triangle[row][col];
        if(dp[row][col]!=-1) return dp[row][col];
        int bottom, bottomright;
        bottom = minimumTotalMemo(triangle, dp, row+1, col);
        bottomright = minimumTotalMemo(triangle, dp, row+1, col+1);
        return dp[row][col] = triangle[row][col] + min(bottom, bottomright);
    }

    int minimumTotalTab(vector<vector<int>>& triangle){
        int n = triangle.size();
        vector<vector<int>>dp(n, vector<int>(n,-1));
        for(int i=0; i<triangle[n-1].size(); i++){
            dp[n-1][i] = triangle[n-1][i];
        }

        for(int row=n-2; row>=0; row--){
            for(int col=0; col<triangle[row].size(); col++){
                 int bottom, bottomright;
                bottom = dp[row+1][col]; //minimumTotalMemo(triangle, dp, row+1, col);
                bottomright =  dp[row+1][col+1]; //minimumTotalMemo(triangle, dp, row+1, col+1);
                dp[row][col] = triangle[row][col] + min(bottom, bottomright);
            }           
        }
        return dp[0][0]; 
    }


    int minimumTotalSpaceOpt(vector<vector<int>>& triangle){
        int n = triangle.size();
        vector<int>curr(n,-1), prev(n,-1);
        for(int i=0; i<triangle[n-1].size(); i++){
            prev[i] = triangle[n-1][i];
        }

        for(int row=n-2; row>=0; row--){
            for(int col=0; col<triangle[row].size(); col++){
                int bottom, bottomright;
                bottom = prev[col]; //minimumTotalMemo(triangle, dp, row+1, col);
                bottomright =  prev[col+1]; //minimumTotalMemo(triangle, dp, row+1, col+1);
                curr[col] = triangle[row][col] + min(bottom, bottomright);
            }  
            prev = curr;         
        }
        return prev[0]; 
    }

    int minimumTotalSpaceOptFinal(vector<vector<int>>& triangle){
        int n = triangle.size();
        vector<int>dp(triangle[n-1].begin(), triangle[n-1].end());
        for(int row=n-2; row>=0; row--)
            for(int col=0; col<triangle[row].size(); col++)
                dp[col] = triangle[row][col] + min(dp[col], dp[col+1]);

        return dp[0]; 
    }


    int minimumTotal(vector<vector<int>>& triangle) {

        return minimumTotalSpaceOptFinal(triangle);

        return minimumTotalSpaceOpt(triangle);

        return minimumTotalTab(triangle);

        int n = triangle.size();
        vector<vector<int>>dp(n, vector<int>(n,-1));
        return minimumTotalMemo(triangle, dp, 0, 0);

        return minimumTotalRec(triangle, 0, 0);
    }
};
```