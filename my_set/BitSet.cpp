#include "BitSet.hpp"
/**
 * 调整位数组大小，如果size更小则忽略，否则调整大小
 * @param size 新的大小
 */
void BitSet::adjust_size(const size_t& size) {
    if(size>this->set_size){
        this->set_size=size;
        this->array_size=(size+15)>>4u;
        auto* temp=new unsigned short[this->array_size];
        memcpy(temp,this->v,this->array_size);
        delete[] this->v;
        this->v=temp;
    }
}
/**
 * 调整位数组大小，如果size更小则忽略，否则调整大小
 * @param A 集合
 * @param size 新的大小
 */
void BitSet::adjust_set(BitSet &A, const size_t &size) {
    if(size>A.set_size){
        A.set_size=size;
        A.array_size=(size+15)>>4u;
        auto* temp=new unsigned short[A.array_size];
        memcpy(temp,A.v,A.array_size);
        delete[] A.v;
        A.v=temp;
    }
}
/**
 * 找到在位数组中的位置
 * @param x 数字
 * @return 位置
 */
int BitSet::array_index(const size_t &x) {
    return x>>4u;
}
/**
 * 创建对应位为1，其余为0的向量
 * @param x 数字
 * @return 向量
 */
unsigned short BitSet::bit_mask(const size_t &x) {
    //取出低位，然后位移到对应位置，相当于x%16后的位
    return 1u<<(x& static_cast<size_t>(0xf));
}

BitSet::BitSet(const size_t &size):set_size(size) {
    //size/16向上取整
    this->array_size=(size+15)>>4u;
    v=new unsigned short[this->array_size]{};
}

BitSet::~BitSet() {
    if(nullptr != this->v){
        delete[] v;
        v=nullptr;
    }
}
/**
 * 求并集
 * @param A 集合
 */
void BitSet::set_union(const BitSet &A) {
    adjust_size(A.set_size);
    for(size_t i=0;i<this->array_size;++i){
        if(i<A.array_size){
            this->v[i]|=A.v[i];
        }
        else{
            break;
        }
    }
}
/**
 * 交集
 * @param A 集合
 */
void BitSet::set_intersection(const BitSet &A) {
    if(A.set_size<this->set_size){
        this->set_size=A.set_size;
        this->array_size=(A.set_size+15)>>4u;
        auto* temp=new unsigned short[this->array_size];
        memcpy(temp,this->v,sizeof(unsigned short)*this->array_size);
        delete[] this->v;
        this->v=temp;
    }
    for(size_t i=0;i<this->array_size;++i){
        this->v[i]&=A.v[i];
    }
}
/**
 * 差
 * @param A 集合
 */
void BitSet::set_difference(const BitSet &A) {
    for(size_t i=0;i<this->array_size;++i){
        if(i<A.array_size){
            this->v[i]=(this->v[i])^(this->v[i]&A.v[i]);
        }
        else{
            break;
        }
    }
}
/**
 * 赋值
 * @param A 集合
 * @return
 */
void BitSet::set_assign(const BitSet &A) {
    adjust_size(A.set_size);
    for(size_t i=0;i<this->array_size;++i){
        if(i<A.array_size){
            this->v[i]=A.v[i];
        }
        else{
            this->v[i]=0;
        }
    }
}
/**
 * 判断是否相等（set_size和每个元素都要相等）
 * @param A 集合
 * @return 是否相等
 */
bool BitSet::set_equal(const BitSet &A) const {
    if(this->set_size!=A.set_size){
        return false;
    }
    for(size_t i=0;i<this->array_size;++i){
        if(v[i]!=A.v[i]){
            return false;
        }
    }
    return true;
}
/**
 * 判断x是否在集合中
 * @param x 数字
 * @return true/false
 */
bool BitSet::set_member(const size_t &x) const {
    size_t index=array_index(x);
    if(index>this->array_size){
        return false;
    }
    return this->v[index]&bit_mask(x);
}
/**
 * 插入
 * @param x 数字
 * @return 是否插入成功
 */
bool BitSet::set_insert(const size_t &x) {
    size_t index=array_index(x);
    if(index>this->array_size){
        return false;
    }
    (this->v[index])|=bit_mask(x);
    return true;
}
/**
 * 删除
 * @param x 数字
 * @return 是否删除成功
 */
bool BitSet::set_delete(const size_t &x) {
    size_t index=array_index(x);
    if(index>this->array_size){
        return false;
    }
    (this->v[index])&=~bit_mask(x);
    return true;
}
/**
 * 求并集
 * @param C 集合
 * @param B 集合
 * @return 并集
 */
BitSet BitSet::set_union(const BitSet& C, const BitSet &B) {
    BitSet A=C;
    adjust_set(A,B.set_size);
    for(size_t i=0;i<A.array_size;++i){
        if(i<B.array_size){
            A.v[i]|=B.v[i];
        }
        else{
            break;
        }
    }
    return A;
}
/**
 * 求交集
 * @param C 集合
 * @param B 集合
 * @return 交集
 */
BitSet BitSet::set_intersection(const BitSet& C, const BitSet &B) {
    BitSet A=C;
    if(A.set_size<B.set_size){
        A.set_size=B.set_size;
        A.array_size=(A.set_size+15)>>4u;
        auto* temp=new unsigned short[A.array_size];
        memcpy(temp,A.v,sizeof(unsigned short)*A.array_size);
        delete[] A.v;
        A.v=temp;
    }
    for(size_t i=0;i<A.array_size;++i){
        A.v[i]&=B.v[i];
    }
    return A;
}
/**
 * 差
 * @param C 集合
 * @param B 集合
 * @return 差
 */
BitSet BitSet::set_difference(const BitSet& C, const BitSet &B) {
    BitSet A=C;
    for(size_t i=0;i<A.array_size;++i){
        if(i<B.array_size){
            A.v[i]=(A.v[i])^(A.v[i]&B.v[i]);
        }
        else{
            break;
        }
    }
    return A;
}
/**
 * A=B
 * @param A 集合
 * @param B 集合
 */
void BitSet::set_assign(BitSet& A, const BitSet &B) {
    adjust_set(A,B.set_size);
    for(size_t i=0;i<A.array_size;++i){
        if(i<B.array_size){
            A.v[i]=B.v[i];
        }
        else{
            A.v[i]=0;
        }
    }
}
/**
 * 判断相等
 * @param A 集合
 * @param B 集合
 * @return 判断相等
 */
bool BitSet::set_equal(const BitSet &A, const BitSet &B) {
    if(A.set_size != B.set_size){
        return false;
    }
    for(size_t i=0;i<A.array_size;++i){
        if(A.v[i] != B.v[i]){
            return false;
        }
    }
    return true;
}
/**
 * 判断数字是否在A中
 * @param x 数字
 * @param A 集合
 * @return true/false
 */
bool BitSet::set_member(const size_t &x, const BitSet &A) {
    size_t index=array_index(x);
    if(index>A.array_size){
        return false;
    }
    return A.v[index]&bit_mask(x);
}
/**
 * 插入
 * @param x 数字
 * @param A 集合
 * @return 是否插入成功
 */
bool BitSet::set_insert(const size_t &x, BitSet& A) {
    size_t index=array_index(x);
    if(index>A.array_size){
        return false;
    }
    A.v[index]|=bit_mask(x);
    return true;
}
/**
 * 删除
 * @param x 数字
 * @param A 集合
 * @return 是否删除成功
 */
bool BitSet::set_delete(const size_t &x, BitSet& A) {
    size_t index=array_index(x);
    if(index>A.array_size){
        return false;
    }
    (A.v[index])&=~bit_mask(x);
    return true;
}

void BitSet::print() const {
    int cnt=0;
    bool flag=false;
    for(size_t i=0;i<array_size;++i){
        unsigned short temp=this->v[i];
        for(size_t j=0;j<16;++j){
            if((temp&1u)==1){
                if(flag){
                    std::cout<<' ';
                }
                else{
                    flag=true;
                }
                std::cout<<cnt;
            }
            temp>>=1u;
            ++cnt;
        }
    }
}

BitSet::BitSet(const BitSet &A) {
    this->set_size=A.set_size;
    this->array_size=A.array_size;
    this->v=new unsigned short[this->array_size];
    memcpy(this->v,A.v,sizeof(unsigned short)*this->array_size);
}
/*
#include <iostream>
#include "my_set/BitSet.hpp"
using namespace std;
ostream& operator<<(ostream& out,const BitSet& A){
    A.print();
    return out;
}

int main() {
    BitSet A(5);
    for(int i=1;i<=3;++i){
        A.set_insert(i);
    }
    BitSet B(5);
    for(int i=3;i<=5;++i){
        B.set_insert(i);
    }
    cout<<A<<endl;
    cout<<B<<endl;
    cout<<BitSet::set_union(A,B)<<endl;
    cout<<BitSet::set_intersection(A,B)<<endl;
    cout<<BitSet::set_difference(A,B)<<endl;
    cout<<A.set_member(1)<<endl;
    cout<<A.set_insert(6)<<endl;
    cout<<A<<endl;
    cout<<A.set_delete(3)<<endl;
    cout<<A<<endl;

    return 0;
}
 */