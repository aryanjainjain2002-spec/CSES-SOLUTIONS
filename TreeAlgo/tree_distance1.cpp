#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int dfs(int node, vector<vector<int>> &adj, vector<vector<int>>&heights,int parent){

    int mx1 = INT_MIN;
    int mx2 = INT_MIN;

    for(int child : adj[node]){
        if(child == parent)continue;

        int h = dfs(child , adj,heights,node);

        if(h > mx1){
            mx2 = mx1;
            mx1 = h;
        }else if(h == mx1){
            mx2 = h;
        }else if(h > mx2){
            mx2 = h;
        }
    }

    heights[node] = {mx1,mx2};

    return mx1 == INT_MIN ? 0 : 1 + mx1;
}


int check(int node,vector<vector<int>> & heights){
    if(heights[node][0] == INT_MIN && heights[node][1] == INT_MIN)return 0;
    return 1 + heights[node][0];
}
void dfs1(int node,vector<vector<int>> &adj,vector<vector<int>> & heights ,vector<int>&res,int parent,int fromParent){

    int mx1 = heights[node][0];
    int mx2 = heights[node][1];

    int dist = mx1 == INT_MIN ? 0 : 1 + mx1;
    dist = max(dist , fromParent);

    res[node] = dist;
    

    for(int child : adj[node]){
        if(child == parent)continue;

        int parentDistance = 1 + fromParent;

        if(check(child,heights) == mx1){
            int val = mx2 == INT_MIN ? 0 : 2 + mx2;
            parentDistance = max(parentDistance,val);
        }else{
            int val = mx1 == INT_MIN ? 0 : 2 + mx1;
            parentDistance = max(parentDistance,val);
        }

        dfs1(child,adj,heights,res,node,parentDistance);
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

        vector<vector<int>> heights(n,vector<int>(2,0));

        dfs(0,adj,heights,-1);

        // for(int i = 0;i<n;i++){
        //     cout<<heights[i][0]<<" ";
        // }cout<<endl;

        vector<int> res(n,0);

        dfs1(0,adj,heights,res,-1,0);

        for(int i = 0;i < n;i++){
            cout<<res[i]<<" ";
        }cout<<endl;
        
    }
    return 0;
}