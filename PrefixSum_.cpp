#include <vector>
#include <iostream>
#define ll long long int

class PrefixSum{

    private:
        std::vector<ll> prefix;
    
    public:
        PrefixSum(const std::vector<ll> &arr){
            ll cum = 0;
            prefix.push_back(0);
            for(int i = 1; i <= arr.size(); ++i){
                cum+=arr[i-1];
                prefix.push_back(cum);
            }
        }

        ll rsum(int i, int j){
            return prefix[j+1]-prefix[i];
        }

        void print_prefix(){
            for(auto x: prefix){std::cout<<x<<" ";}std::cout<<std::endl;
        }

};

