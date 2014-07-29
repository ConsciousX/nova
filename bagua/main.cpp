#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <assert.h>
#include <stdio.h>

int func(){
    int init = 49;
    int left, right, left_mod, right_mod;
    int mod_sum;

    for (size_t i = 0;i < 3;++i){
        left =  rand() % (init - 1);
        left+=1;
        right = init - left;

        --right;

        left_mod = left % 4;
        if (left_mod == 0) left_mod = 4;

        if (right == 0){
            right_mod = 0;
        }
        else{
            right_mod = right % 4;
            if (right_mod == 0) right_mod = 4;
        }

        mod_sum = left_mod + right_mod + 1;
        //std::cout<<(i + 1)<<":mod sum = "<<mod_sum<<std::endl;

        init -= mod_sum;
    }

    //std::cout<<"remain = "<<init<<std::endl;
    //std::cout<<"ans = "<<(init /= 4)<<std::endl;
    init /= 4;

    return init;
}

int main(){
    int result;
    std::vector<int> results, results_trans, changes;
    //size_t a = 0,b = 0,c =0,d = 0;
    srand(time(NULL));

    /*for (size_t i = 0;i< 100000;++i){
        result = func();
        switch(result){
            case 6:
            ++a;
            break;
            case 7:
            ++b;
            break;
            case 8:
            ++c;
            break;
            case 9:
            ++d;
            break;
            default:
            printf("err = %d",result);
            assert(0);
        }
    }

    printf("%f %f %f %f\n",a/1000.0,b/1000.0,c/1000.0,d/1000.0);*/

    for (size_t i = 0;i<6;++i){
        result = func();
        results.push_back(result);
        if (result == 6){
            results_trans.push_back(9);
            changes.push_back(1);
        }
        else if (result == 9){
            results_trans.push_back(6);
            changes.push_back(1);
        }
        else{
            results_trans.push_back(result);
            changes.push_back(0);
        }
    }

    for (int i = 5;i >= 0;--i){
        std::cout<<results[i]<<"  "<<results_trans[i]<<std::endl;
    }

    std::cout<<"Total number of changes = "<<std::accumulate(changes.begin(), changes.end(), 0)<<std::endl;
    std::cout<<"Changes: ";
    for(size_t i= 0;i<6;++i){
        if (changes[i] == 1){
            std::cout<<i +1 <<" ";
        }
    }

    std::cout<<std::endl;
    
    return 0;
}
