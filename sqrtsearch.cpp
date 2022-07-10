#include <vector>
#include <assert.h>
#include <math.h>
#include <iostream>

class SqrtSearch{

private:
    unsigned int n;
    std::vector<int> row_data;
    std::vector<int> row_counter;
    std::vector<int> col_data;
    std::vector<int> col_counter;
    unsigned int sq;

    void update_data_add(bool is_row, unsigned int value){
        int until = sq*(value/sq);
        std::vector<int> *data = (is_row) ? &row_data : &col_data;
        std::vector<int> *data_counter = (is_row) ? &row_counter : &col_counter;

        (*data_counter)[value]++;
        if((value+1)%sq==0){(*data)[value]=1;}
        else{(*data)[value]=(*data)[value+1]+1;}

        for(int i = value-1; i >= until; --i){
            if((*data)[i]>0){
                (*data)[i]=((*data)[i+1]+1);
            }else{
                break;
            }
        }
    }

    void update_data_remove(bool is_row, unsigned int value){
        int until = sq*(value/sq);
        std::vector<int> *data = (is_row) ? &row_data : &col_data;
        std::vector<int> *data_counter = (is_row) ? &row_counter : &col_counter;
        (*data_counter)[value]--;
        (*data)[value] = 0;
        for(int i = value-1; i >= until; --i){
            if((*data)[i]>0){
                (*data)[i]=((*data)[i+1]+1);
            }else{
                break;
            }
        }
    }

    bool check_in_sq_range(unsigned int val1, unsigned int val2){
        assert (val1 < n && val2 < n);
        assert(val1<=val2);
        return ((val1/sq)==(val2/sq));
    }

    bool sq_range_iterator(bool is_row, unsigned int val1, unsigned int val2){
        bool trys = true;
        std::vector<int> *data = (is_row) ? &row_data : &col_data;
        while(!check_in_sq_range(val1, val2)){
            if((*data)[val1]+(val1%sq)==sq){
                val1+=(*data)[val1];
            }else{
                trys = false;
                break;
            }
        }
        if(trys){
            if((*data)[val1]>=(val2-val1+1)){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    }

public:
    SqrtSearch(int n): n(n){
        row_data = std::vector<int>(n+1,0);
        row_counter = std::vector<int>(n+1,0);
        col_data = std::vector<int>(n+1,0);
        col_counter = std::vector<int>(n+1,0);
        sq = std::sqrt(n);
    }

    void insert(unsigned int row, unsigned int col){
        row = row-1;
        col = col-1;

        assert (row < n && col < n);
        if(row_data[row]==0) {
            update_data_add(true, row);
        }else{row_counter[row]++;}
        if(col_data[col]==0) {
            update_data_add(false, col);
        }else{ col_counter[col]++;}
    }

    void remove(unsigned int row, unsigned int col){
        row = row-1;
        col = col-1;
        assert (row < n && col < n);
        assert (row_counter[row]!=0);
        assert (col_counter[col]!=0);

        if(row_counter[row]>1){row_counter[row]--;}
        else{update_data_remove(true,row);}
        if(col_counter[col]>1){col_counter[col]--;}
        else{update_data_remove(false, col);}

    }

    bool check_range(unsigned int row1, unsigned int row2, unsigned int col1, unsigned int col2){
        row1 = row1-1;
        row2 = row2-1;
        col1 = col1-1;
        col2 = col2-1;
        assert (row1 < n && col1 < n && row2 < n && col2 <n);
        assert(row1<=row2 && col1<=col2);
        return (sq_range_iterator(true, row1, row2) || sq_range_iterator(false, col1, col2));
    }

    void print_data(){
        for(auto x: row_data){
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
        for(auto x: col_data){
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
    }


};

int main(){

    int n,m;
    std::cin>>n>>m;
    SqrtSearch sq(n);
    for(int i = 0; i < m; ++i){
        int tmp;
        std::cin>>tmp;
        if(tmp==1){
            unsigned int a,b;
            std::cin>>a>>b;
            sq.insert(a,b);
//            sq.print_data();
        }else if(tmp == 2){
            unsigned int a,b;
            std::cin>>a>>b;
            sq.remove(a,b);
//            sq.print_data();
        }else{
            unsigned int a,b,c,d;
            std::cin>>a>>b>>c>>d;
            if(sq.check_range(a,c,b,d)){
                std::cout<<"Yes"<<std::endl;
            }else{
                std::cout<<"No"<<std::endl;
            }

        }
    }


}