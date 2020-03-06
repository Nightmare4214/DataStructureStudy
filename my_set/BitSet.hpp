#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
class BitSet{
private:
    //集合大小
    size_t set_size;
    //位数组大小
    size_t array_size;
    //位数组,0-15在第0个数组，16-31在第1个数组.....
    unsigned short* v;
    void adjust_size(const size_t& size);
    static void adjust_set(BitSet& A,const size_t& size);
    static int array_index(const size_t& x);
    static unsigned short bit_mask(const size_t& x);
public:
    BitSet(const size_t& size);
    BitSet(const BitSet& A);
    ~BitSet();
    void set_union(const BitSet& A);
    void set_intersection(const BitSet& A);
    void set_difference(const BitSet& A);
    void set_assign(const BitSet& A);
    bool set_equal(const BitSet& A)const;
    bool set_member(const size_t& x)const;
    bool set_insert(const size_t& x);
    bool set_delete(const size_t& x);

    static BitSet set_union(const BitSet& A,const BitSet& B);
    static BitSet set_intersection(const BitSet& A,const BitSet& B);
    static BitSet set_difference(const BitSet& A,const BitSet& B);
    static void set_assign(BitSet& A,const BitSet& B);
    static bool set_equal(const BitSet& A,const BitSet& B);
    static bool set_member(const size_t& x,const BitSet& A);
    static bool set_insert(const size_t& x,BitSet& A);
    static bool set_delete(const size_t& x,BitSet& A);

    void print()const;
};