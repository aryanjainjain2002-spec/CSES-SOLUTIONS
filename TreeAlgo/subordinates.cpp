#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void dfs(int node ,vector<vector<int>> &adj,vector<int> &res){
    
    for(int child : adj[node]){
        dfs(child,adj,res);
        res[node] += 1 + res[child];
    }
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        ll n;cin>>n;

        vector<vector<int>> adj(n,vector<int>());

        for(int i = 1;i<n;i++){
            int a;
            cin>>a;

            adj[a-1].push_back(i);
        }

        vector<int> res(n,0);

        dfs(0,adj,res);

        for(int i = 0;i<n;i++){
            cout<<res[i]<<" ";
        }cout<<endl;

    }
    return 0;
}