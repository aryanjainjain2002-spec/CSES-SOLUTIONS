#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void dfs(int node,vector<vector<int>> &adj,vector<int>&level){

    for(int child : adj[node]){
        level[child] = 1 + level[node];
        dfs(child,adj,level);   
    }
}

int lca(int a,int b,vector<int>&level,vector<vector<int>>&dp){  
    if(level[a] < level[b])swap(a,b);

    for(int i = 31;i>=0;i--){
        if(level[a] - (1<<i) >= level[b]){
            a = dp[a][i];
        }
    }

    //now at smae level

    if(a == b)return a;

    for(int i = 31;i>=0;i--){
        if(dp[a][i]!=dp[b][i]){
            a = dp[a][i];
            b = dp[b][i];
        }
    }

    return dp[a][0];
}
int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        int n,q;
        cin>>n>>q;
        vector<vector<int>> dp(n,vector<int>(32,-1));

        vector<vector<int>> adj(n,vector<int>());

        for(int i = 1;i<n;i++){
            int a;cin>>a;
            dp[i][0] = a-1; 

            adj[a-1].push_back(i);
        }

        // int log = log2(n);

        vector<int>level(n,0);

        dfs(0,adj,level);

        // for(int i = 0;i<n;i++){
        //     cout<<level[i]<<" ";
        // }cout<<endl;

        for(int j = 1;j<32;j++){
            for(int i = 1;i<n;i++){
                //dp[i][j]

                int mid = dp[i][j-1];
                if(mid != -1){
                    dp[i][j] = dp[mid][j-1];
                }else{
                    dp[i][j] = -1;
                }
            }
        }

        for(int i = 0;i<q;i++){
            int a,b;cin>>a>>b;
            a--,b--;

            cout<<lca(a,b,level,dp) + 1<<endl;
        }
    }
    return 0;
}