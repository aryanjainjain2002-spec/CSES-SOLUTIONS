#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);


class DSU{
    private:
        vector<int>parent;
        vector<int>rank;
    public:
        DSU(int n){
            for(int i = 0;i<n;i++){
                parent.push_back(i);
                rank.push_back(1);
            }
        }

        int find(int u){
            return parent[u] = (parent[u] == u ? u : find(parent[u]));
        }

        bool unite(int u,int v){
            u = find(u);
            v = find(v);

            if(u == v)return false;

            if(rank[v] > rank[u])swap(u,v);

            rank[u]+=rank[v];
            parent[v] = u;
            return true;
        }

        int getRank(int node){
            return rank[node];
        }
};

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        ll n, m;

        cin>>n>>m;

        DSU dsu(n);

        int count = n;
        int mx = 1;

        for(int i  = 1 ; i <= m ;i++){
            int a,b;
            cin>>a>>b;
            
            bool isUnited = dsu.unite(a-1,b-1);

            if(isUnited){
                --count;
                int parent =  dsu.find(a-1);
                mx = max(mx,dsu.getRank(parent));
            }

            cout<<count<<" "<<mx<<endl;

        }

    }
    return 0;
}