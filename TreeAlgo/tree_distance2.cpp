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
        int n;cin>>n;
        vector<vector<int>> adj(n,vector<int>());

        for(int i = 1;i<n;i++){
            int a,b;
            cin>>a>>b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        vector<int>count(n,0);
        vector<ll>subtree(n,0);

        dfs(0,adj,count,subtree,-1);

        vector<ll>res(n,0);

        // for(int i = 0;i<n;i++){
        //     cout<<count[i]<<" "<<subtree[i]<<endl;
        // }

        dfs1(0,0,adj,count,subtree,res,-1);

        for(int i = 0;i<n;i++){
            cout<<res[i]<<" ";
        }cout<<endl;

    }
    return 0;
}