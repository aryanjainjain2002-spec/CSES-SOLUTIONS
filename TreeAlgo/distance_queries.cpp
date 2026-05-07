#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void dfs(int node,vector<vector<int>> &adj,vector<int>&level,vector<vector<int>>&up,int parent){

    for(int child : adj[node]){
        if(child == parent)continue;
        up[child][0] = node;
        level[child] = 1 + level[node];
        dfs(child,adj,level,up,node);   
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
        vector<vector<int>> up(n,vector<int>(32,-1));

        vector<vector<int>> adj(n,vector<int>());

        for(int i = 1;i<n;i++){
            int a,b;cin>>a>>b;
            // dp[i][0] = a-1; 

            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        // int log = log2(n);

        vector<int>level(n,0);

        dfs(0,adj,level,up,-1);

        // for(int i = 0;i<n;i++){
        //     cout<<level[i]<<" ";
        // }cout<<endl;

        int log = log2(n) + 1;

        for(int j = 1;j<=log;j++){
            for(int i = 1;i<n;i++){
                //dp[i][j]

                int mid = up[i][j-1];
                if(mid != -1){
                    up[i][j] = up[mid][j-1];
                }else{
                    up[i][j] = -1;
                }
            }
        }

        vector<int>res(n,0);

        for(int i = 0;i<q;i++){
            int a,b;cin>>a>>b;
            a--,b--;

            int c = lca(a,b,level,up);

            cout<<level[a] + level[b] - 2*level[c]<<" ";
        }cout<<endl;
    }
    return 0;
}