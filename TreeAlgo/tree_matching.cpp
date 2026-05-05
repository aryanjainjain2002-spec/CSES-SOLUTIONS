#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<int> dfs(int node,vector<vector<int>> &adj,int parent){
    vector<int> res (2,0); //taken , notTaken

    vector<vector<int>> childs;

    int notTaken = 0;

    for(int child : adj[node]){
        if(child == parent)continue;
        vector<int> temp = dfs(child , adj,node);

        childs.push_back(temp);
        notTaken += temp[1];
    }
    res[0] = notTaken + 1;

    for(vector<int> child : childs){
        res[1] = max(res[1],child[0] + notTaken - child[1]);
    }
    return res;
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        int n;cin>>n;

        vector<vector<int>> adj(n,vector<int>());

        for(int i = 1;i<n;i++){
            int a,b;
            cin>>a>>b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        vector<int> res = dfs(0,adj,-1);

        cout<<max(res[0]-1,res[1])<<endl;
    }
    return 0;
}