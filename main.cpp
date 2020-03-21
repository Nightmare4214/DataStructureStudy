#include "BigInteger/BigInteger.hpp"
#include <iostream>
using namespace std;
int main(){
    BigInteger A(1);
    cout<<1<<' '<<A<<endl;
    //卡特兰数
    for(int i=2;i<=200;++i){
        A= A * BigInteger(4 * i - 2) / BigInteger(i + 1);
        cout<<i<<' '<<A<<endl;
    }
    return 0;
}