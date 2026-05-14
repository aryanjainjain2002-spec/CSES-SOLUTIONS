// #include "bits/stdc++.h"
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<vector<int>> adj;
vector<int> subtree;

int subtree_size(int node,int parent){
    subtree[node] = 1;

    for(int child : adj[node]){
        if(child == parent)continue;

        subtree[node] += subtree_size(child,node);
    }

    return subtree[node];
}

int centroid(int node, int treesize,int p = -1){

    //check the conditions

    for(int u : adj[node]){
        if(u == p)continue;

        if(2*subtree[u] > treesize) return centroid(u,treesize,node);
    }
    return node;
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {

        int n;cin>>n;
        adj.assign(n,vector<int>());
        subtree.assign(n,0);

        // for(int i = 0;i<n;i++)adj[i].clear();

        for(int i = 1;i<n;i++){
            int a,b;cin>>a>>b;

            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        int tree_size = subtree_size(0,-1);


        cout<<centroid(0,tree_size) + 1<<endl;

    }
    return 0;
}