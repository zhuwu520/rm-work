#include <iostream>
#include <vector>

using namespace std;
vector<int> Zk={51,48,47,52,51,48,49,53,48,49,52,53,51,52,49,50};
vector<double>result;
int eM=3;
double hat_x=40,k,eE=5;
int main()
{
    auto j=Zk.begin();
    while(j!=Zk.end())
    {
        k=eE/(eE+eM);
        hat_x=hat_x+k*(*j-hat_x);
        eE*=(1-k);
        result.push_back(hat_x);
        ++j;
    }
    for (auto x:result)
        cout<<x<<" ";
}