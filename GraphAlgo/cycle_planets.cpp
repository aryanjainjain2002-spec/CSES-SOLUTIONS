#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int32_t main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) {
        int n;
        cin>>n;
        vector<int> childs(n,0);

        for(int i  = 0;i<n;i++){
            cin>>childs[i];
            childs[i]--;
        }

        vector<bool> visited(n,false);

        vector<int> dist(n,0);

        for(int i = 0;i<n;i++){
            if(!visited[i]){
                vector<int> order;
                vector<bool> inPath(n,false);
                int curr = i;
                while(!visited[curr]){
                    order.push_back(curr);
                    visited[curr] = true;
                    inPath[curr] = true;
                    curr = childs[curr];
                }
                if(inPath[curr]){
                    auto it = find(order.begin(), order.end(), curr);
                    int idx = distance(order.begin(), it);
                    int cycle_length = order.size() - idx;

                    bool flag = false;

                    while(!order.empty()){
                        int node = order.back();
                        order.pop_back();
                        if(!flag){
                            dist[node] = cycle_length;
                            if(node == curr)flag = true;
                        }else{
                            dist[node] = 1 + dist[childs[node]];
                        }
                        
                    }
                }else{// part of old visited node
                    while(!order.empty()){
                        int node = order.back();
                        order.pop_back();
                        dist[node] = 1 + dist[childs[node]];
                    }
                }
            }
        }

        for(int i = 0;i<n;i++){
            cout<<dist[i]<<" ";
        }cout<<endl;
    }
    return 0;
}