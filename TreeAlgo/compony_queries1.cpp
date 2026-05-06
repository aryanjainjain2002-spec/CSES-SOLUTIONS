#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void dfs(int node,vector<vector<int>> &adj,vector<int>&count,vector<ll>&subtree,int parent){


    for(int child : adj[node]){
        if(child == parent)continue;

        dfs(child,adj,count,subtree,node);
        subtree[node] += subtree[child] + count[child];
        count[node] += count[child]; 
    }

    count[node]+=1;
}

void dfs1(int node,ll fromParent,vector<vector<int>> &adj,vector<int>&count,vector<ll>&subtree,vector<ll>&res,int parent){
    
    res[node] = fromParent + subtree[node];

    ll childSum = subtree[node];
    
    for(int child : adj[node]){
        if(child == parent)continue;
        ll parentSum = fromParent + childSum - subtree[child] - count[child] + res.size() - count[child];
        dfs1(child,parentSum,adj,count,subtree,res,node);
    }
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        int n,q;
        cin>>n>>q;
        vector<vector<int>> dp(n,vector<int>(32,-1));

        for(int i = 1;i<n;i++){
            int a;cin>>a;
            dp[i][0] = a-1; 
        }

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
            int  x,k;
            cin>>x>>k;

            --x;

            int parent = x;

            for(int bit = 0;bit<32;bit++){
                if( (k&(1<<bit)) ){
                    parent = dp[parent][bit];
                    if(parent == -1)break;
                }
            }
            if(parent == -1){
                cout<<-1<<endl;
            }else{
                cout<<1 + parent;
            }
            
        }cout<<endl;

    }
    return 0;
}