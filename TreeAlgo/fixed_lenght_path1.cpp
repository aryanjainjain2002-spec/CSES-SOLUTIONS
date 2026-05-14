#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

vector<vector<int>> adj;
vector<int> subtree;
vector<bool>removed;
int K;

ll ans = 0;

int subtree_size(int node,int p = -1){
    subtree[node] = 1;

    for(int child : adj[node]){
        if(child == p || removed[child])continue;

        subtree[node] += subtree_size(child,node);
    }

    return subtree[node];
}

int get_centroid(int node, int treesize,int p = -1){

    //check the conditions

    for(int u : adj[node]){
        if(u == p || removed[u])continue;

        if(2*subtree[u] > treesize) return get_centroid(u,treesize,node);
    }
    return node;
}

void dfs(int node,int dist,vector<int>&distances,int p = -1){
    if(dist > K)return;

    distances.push_back(dist);

    for(int child : adj[node]){
        if(child == p || removed[child])continue;

        dfs(child,dist + 1,distances,node);
    }
}

void calculate_distance(int node,int p = -1){
    vector<ll> um(K+1);
    um[0] = 1;

   
    for(int u : adj[node]){
        if(u == p || removed[u])continue;

        vector<int>distances;
        dfs(u,1,distances,node);

        for(int d : distances){
           
            if(K>=d)ans += um[K - d];
            
        }

        for(int d : distances){
            
            if(d <= K)um[d] += 1;
        }  
    }
}

void decompose(int node,int p = -1){
    int treesize = subtree_size(node);
    int centroid = get_centroid(node,treesize);

    calculate_distance(centroid);
    removed[centroid] = true;

    for(int u : adj[centroid]){
        if(u == p || removed[u])continue;

        decompose(u);
    }
    
}


int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {

        int n,k;cin>>n>>k;
        K = k;
        adj.assign(n,vector<int>());
        subtree.assign(n,0);
        removed.assign(n,false);
        ans = 0;

        // for(int i = 0;i<n;i++)adj[i].clear();

        for(int i = 1;i<n;i++){
            int a,b;cin>>a>>b;

            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }

        decompose(0);

        cout<<ans<<endl;

    }
    return 0;
}