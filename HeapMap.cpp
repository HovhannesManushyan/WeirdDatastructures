#include <ostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#define ll long long int
#define printvec(v) for(auto x: v){std::cout<<x<<" ";}std::cout<<std::endl;

struct vertex{
    int vid;
    int parent;
    int val;
    vertex(){};
    vertex(int vid, int parent, int val):vid(vid),val(val), parent(parent){};
    bool operator==(const vertex &other) const{return ((val==other.val)&&(vid == other.vid)&&(parent==other.parent));}
    bool operator<(const vertex &other) const{return (val < other.val);}
    bool operator<=(const vertex &other) const{return (val <= other.val);}
    bool operator>(const vertex &other) const{return (val > other.val);}
    bool operator>=(const vertex &other) const{return (val >= other.val);}
};

std::ostream& operator<<(std::ostream& os, const vertex& inp){
    return os << "(" << inp.parent << " " <<inp.vid<< " " <<inp.val<<")";
};

namespace std {
    template <>
    struct hash<vertex> {
        auto operator()(const vertex &other) const -> size_t {
            return hash<int>{}(other.vid)^hash<int>{}(other.parent)^hash<int>{}(other.val);
        }
    };
}

template <typename T>
class HeapMap{
    private:
        std::vector<T> heap;
        std::unordered_map<T, int> bt;
    public:


        void swap(int pos1, int pos2){
            T tmp = heap[pos1];
            bt[heap[pos1]]=pos2;
            bt[heap[pos2]]=pos1;
            heap[pos1]=heap[pos2];
            heap[pos2]=tmp;

        }

        void shiftup(int pos){
            if(pos!=0 && heap[(pos-1)/2]>heap[pos]){
                swap((pos-1)/2,pos);
                shiftup((pos-1)/2);
            }
        }

        bool isleaf(int pos){
            if(2*pos+2>heap.size()){
                return true;
            }else{
                return false;
            }
        }


        void shiftdown(int pos){
            T cur = heap[pos];
            if(!isleaf(pos)){
                if(2*pos+3>heap.size()){
                    if(heap[pos]>heap[2*pos+1]){
                        swap(pos,2*pos+1);
                        shiftdown(2*pos+1);
                    }
                }else{
                    T r1 = heap[2*pos+1];
                    T r2 = heap[2*pos+2];
                    if(r1<cur && r1<=r2){
                        swap(pos,2*pos+1);
                        shiftdown(2*pos+1);
                    }else if(r2<cur && r2<=r1){
                        swap(pos,2*pos+2);
                        shiftdown(2*pos+2);
                    }
                }
            }
            
        }

        void remove(int pos){
            swap(pos,heap.size()-1);
            bt.erase(heap[heap.size()-1]);
            heap.pop_back();
            shiftdown(0);
        }

        T gmin(){
            T tmp = heap[0];
            remove(0);
            return tmp;
        }

        void insert(T val){
            if(bt.find(val)!=bt.end()){
                if(heap[bt[val]] > val){
                    heap[bt[val]]=val;
                    shiftup(bt[val]);
                }
            }else{ 
                heap.push_back(val);
                shiftup(heap.size()-1);
            }
        }

        int hsize(){
            return heap.size();
        }

        void print_heap(){printvec(heap)}

        HeapMap(){}
        HeapMap(std::vector<T> &arr){
            heap = arr;
            for(int i = arr.size()/2-1; i>=0; --i){
                shiftdown(i);
            }
        }

};


// Prim's algorithm example
int main(){

    while(true){
        int n,m;
        std::cin>>n>>m;
        if(n==0 && m == 0){break;}
        std::vector<std::vector<std::pair<int,int>>> graph(n,std::vector<std::pair<int,int>>());
        std::vector<std::pair<int,int>> result;
        
        for(int i = 0; i < m; ++i){
            int a,b,c;
            std::cin>>a>>b>>c;
            graph[a].push_back(std::make_pair(b,c));
            graph[b].push_back(std::make_pair(a,c));
        }

        std::vector<int> visited(n,0);
        HeapMap<vertex> hp;

        for(int i = 0; i < n; ++i){
            if(graph[i].size()!=0){
                for(auto x: graph[i]){
                    hp.insert(vertex(x.first,i,x.second));
                }
                visited[i]=1;
                break;
            }
        }


        ll cost = 0;
        while(hp.hsize()!=0){
            vertex cmin = hp.gmin();
            if(visited[cmin.vid]==0){
                // update start;
                cost+=(ll)cmin.val;
                if(cmin.parent>cmin.vid){
                    result.push_back(std::make_pair(cmin.vid,cmin.parent));
                }else{result.push_back(std::make_pair(cmin.parent,cmin.vid));}

                visited[cmin.vid]=1;
                for(auto x: graph[cmin.vid]){
                    if(visited[x.first]==0){
                        hp.insert(vertex(x.first,cmin.vid,x.second));
                    }
                }
            }

        }

        std::sort(result.begin(),result.end());
        if(result.size()+1!=n){
            std::cout<<"Impossible"<<std::endl;
        }else{
            std::cout<<cost<<std::endl;
            for(auto x: result){
                std::cout<<x.first<<" "<<x.second<<std::endl;
            }
        }

    }
}
