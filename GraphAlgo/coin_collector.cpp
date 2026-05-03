#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void dfs(int node, vector<vector<ll>> &adj,stack<int>&st,vector<bool>&visited){


    visited[node] = true;

    for(ll child : adj[node]){
        if(visited[child])continue;

        dfs(child,adj,st,visited);
    }

    st.push(node);//push as per the end time
}

void dfs1(int node,int compId,vector<vector<ll>> &adj,vector<bool>&visited,vector<int>&compIds,vector<ll>&coinInComp,vector<ll>&coins){
    visited[node] = true;

    compIds[node] = compId;

    coinInComp[compId]+= coins[node];

    for(int child : adj[node]){
        if(visited[child])continue;

        dfs1(child,compId,adj,visited,compIds,coinInComp,coins);

    }
}

void solve(int node,vector<vector<ll>> & dag,vector<ll>&coinInComp,vector<ll>&dp){
    if(dp[node] != -1)return ;

    dp[node] = coinInComp[node];

    ll mx = 0;
    for(int child : dag[node]){
       solve(child , dag,coinInComp,dp);
       mx = max(mx,dp[child]);
    }
    dp[node] += mx;
}

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        ll n,m;
        cin>>n>>m;
        vector<ll>coins(n,0);

        vector<vector<ll>> adj(n,vector<ll>());
        vector<vector<ll>> radj(n,vector<ll>());

        for(int i = 0;i<n;i++)cin>>coins[i];

        for(int i = 0;i<m;i++){
            int u,v;
            cin>>u>>v;

            adj[u-1].push_back(v-1);
            radj[v-1].push_back(u-1);
        }

        vector<bool>visited(n,false);
        stack<int>order;

        for(int i = 0;i<n;i++){
            if(!visited[i]){
                dfs(i,adj,order,visited);
            }
        }

        vector<int>compIds(n,0);

        vector<ll>coinInComp(n,0);

        int compId = 0;

        visited.assign(n,false);


        while(!order.empty()){
            int node = order.top();
            order.pop();

            if(visited[node])continue;

            dfs1(node,compId,radj,visited,compIds,coinInComp,coins);
            compId++;
        }
        
        // cout<<"COMP IDS:"<<endl;

        // for(int i = 0;i<n;i++){
        //     cout<<compIds[i]<<endl;
        // }

        // cout<<"COMP COINS:\n";

        // for(int i = 0;i<n;i++){
        //     cout<<coinInComp[i]<<endl;
        // }

        // cout<<"\n\n\n";

        vector<vector<ll>> dag(n,vector<ll>());

        for(int i = 0;i<n;i++){
            vector<ll>childs = adj[i];

            int compId1 = compIds[i];
            // cout<<i<<"( "<<compId1<<" )"<<"  --->  ";

            for(ll child : childs){
                int compId2 = compIds[child];

                if(compId1 != compId2){
                    dag[compId1].push_back(compId2);
                    // cout<<compId2<<" ,";
                }
                
            }   
            // cout<<endl;
        }

        // cout<<"\n";

        vector<ll>dp(n,-1);

        ll res = 0;

        for(int i = 0;i<n;i++){
           solve(compIds[i] , dag,coinInComp,dp);

           res = max(res,dp[compIds[i]]);
        }

        cout<<res<<endl;
    }
    return 0;
}