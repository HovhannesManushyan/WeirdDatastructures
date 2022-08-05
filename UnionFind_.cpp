#include <bits/stdc++.h>
#define ll long long int
#define printvec(v) for(auto x: v){std::cout<<x<<" ";}std::cout<<std::endl;

class UnionFind{
    private:
        std::vector<int> uset;
        std::vector<int> rank;
    public:
        UnionFind(int n){for(int i = 0; i < n; ++i){uset.push_back(i);rank.push_back(0);}};

        int find(int pos){
            if(uset[pos]==pos){
                return pos;
            }else{return uset[pos]=find(uset[pos]);}
        }

        void unify(int pos1, int pos2){
            int l1 = find(pos1);
            int l2 = find(pos2);
            if(l1!=l2){
                if(rank[l1]>rank[l2]){
                    uset[l2]=l1;
                    rank[l1]=std::max(rank[l1],rank[l2]+1);
                }else{
                    uset[l1]=l2;
                    rank[l2]=std::max(rank[l1]+1,rank[l2]);
                }
            }
        }
        

};

struct vertex{
    int first;
    int second;
    int third;
    vertex(int f, int s, int t): first(f), second(s), third(t){};
    bool operator<(const vertex& other){return third < other.third;}
};

std::ostream& operator<<(std::ostream& os, const vertex& v)
{
    os <<"("<<v.first << ' ' << v.second << ' ' << v.third<<") ";
    return os;
}

int main(){

    int n,m;
    std::cin>>n>>m;
    std::vector<vertex> v;
    for(int i = 0; i < m; ++i){
        int a,b,c;
        std::cin>>a>>b>>c;
        v.push_back(vertex(a,b,c));
    }

    std::sort(v.begin(),v.end());
    UnionFind uf = UnionFind(n);
    ll result = 0;
    for(int i = 0; i < m; ++i){
        if(uf.find(v[i].first-1)!=uf.find(v[i].second-1)){
            result+=v[i].third;
            uf.unify(v[i].first-1,v[i].second-1);
        }
    }
    std::cout<<result<<std::endl;
}