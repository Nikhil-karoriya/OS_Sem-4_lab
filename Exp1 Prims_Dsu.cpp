#include<bits/stdc++.h>
#define ll long long int
#define pp pair<int,int>
using namespace std;

class Dsu{      
    vector<int> parent;
    vector<int> rank;       
public:
    Dsu(int n){
        parent.resize(n+1);    
        rank.resize(n+1,0);
        for(int i=1;i<=n;i++){     
            parent[i]= i;
        }
    }
    bool Union(int a,int b);
    int find(int x); 
};
int Dsu::find(int x){       
    return parent[x]= (x == parent[x])? x : find(parent[x]);        
}
bool Dsu::Union(int a,int b){          
    a= find(a);     
    b= find(b);
    if(a == b) return false;        // cycle detected 
    if(rank[a] >= rank[b]){     
        rank[a]++;          
        parent[b]= a;
    }  else{
        rank[b]++;
        parent[a]= b;
    }
    return true;        // no cycle
}
vector<list<pp>> graph;     // src-> (dst,wt)
int v;
void add_edge(int src,int dst, int wt,bool bidir= true){
    graph[src].push_back({dst,wt});     
    if(bidir) graph[dst].push_back({src,wt});
}

ll prims(int src){          
    priority_queue<pp,vector<pp>,greater<pp>> pq;       //{wt, vertice}
    unordered_set<int> vis;
    vector<int> parent(v+1);        
    unordered_map<int,int> mp;   

    Dsu D(v);   
    for(int i=0; i<=v; i++){   
        mp[i]= INT_MAX;         
    }
    mp[src]= 0;     //weight of src is 0
    ll ans=0;
    int totalNodes= 0;    // total nodes = v
    pq.push({0,src});   //weight of src is 0
    while(totalNodes < v and ! pq.empty()){     
        auto curr= pq.top();        //{wt,vertice}
        pq.pop();
        if(vis.count(curr.second)) continue;    

        vis.insert(curr.second);        //mark visited
        ans += curr.first;      //add the weight of current vertice
        totalNodes++;        // increment node count
        
        for(auto neighbor: graph[curr.second]){     
            if(! vis.count(neighbor.first) and mp[neighbor.first] > neighbor.second){
                //skip if union of two vertices results in cycle in MST
                if(D.Union(curr.second,neighbor.first) == false) continue;

                pq.push({neighbor.second,neighbor.first});  // add in pq to visit later
                mp[neighbor.first] = neighbor.second;       //update the distance of neighbor
                parent[neighbor.first] = curr.second;

            }
        }
    }
    return ans;
}
int main(){
    int e;
    cin>>v>>e;
    graph.resize(v+1,list<pp>());
    while(e--){
        int src,dst,wt;
        cin>>src>>dst>>wt;
        add_edge(src,dst,wt);
    }
    int src;
    cin>>src;
    cout<<prims(src);
    return 0;
}