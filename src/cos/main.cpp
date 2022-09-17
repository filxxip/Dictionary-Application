#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <vector>

int sqrt(int value){
    return value*value;
}

int main(){
    int v[4] = {1, 2, 3, 5};
    int v11[4];
    std::vector<int> v1 = {44, 11, 22, 33};
    // v1.reserve(8);
    auto s = &v1.at(0);
    std::vector<int> v2 = {5, 6, 7, 8};
    for(auto &x: v){std::cout<<&x<<std::endl;}
    std::cout<<std::endl;
    // auto output = std::insert_iterator<int[4] >(v, &v);
    auto y = std::transform(v, v+4, v11, [](auto x){return x*x;});
    for(auto &x: v11){std::cout<<x<<std::endl;}
    // std::cout<<&(*y);
    // std::cout<<std::endl<<*(s+2);//najpierw zwalnia i lokuje nowe miejsce dla iteratora przez co odwolujac sie do poprzedniego jest problem
    // std::for_each(a.begin(), a.end(), [](auto x){std::cout<<tolower(x);});
}