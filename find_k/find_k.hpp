#pragma once
#include <iostream>
#include <cstring>
/**
 * 插入排序
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void insert_sort(T arr[], const int& left, const int& right, _Pr cmp) {
    for (int i = left + 1; i <= right; ++i) {
        T temp = arr[i];
        int index = i - 1;
        while (index >= left && cmp(temp, arr[index])) {
            arr[index + 1] = arr[index];
            --index;
        }
        arr[index + 1] = temp;
    }
}
/**
 * 找到中位数
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 * @return 中位数下标
 */
template<typename T,typename _Pr>
int find_mid(T *arr, const int& left, const int& right, _Pr cmp) {
    int i;
    for (i = left; i + 4 <= right; i += 5) {
        insert_sort(arr, i, i + 4, cmp);
        std::swap(arr[i + 2], arr[left + (i - left) / 5]);
    }
    if (i <= right) {
        insert_sort(arr, i, right, cmp);
        std::swap(arr[(i + right) / 2], arr[left + (i - left) / 5]);
    }
    else {
        i -= 5;
    }
    int remain = left + (i - left) / 5;
    if (remain == left) {
        return left;
    }
    return find_mid(arr, left, remain, cmp);
}
/**
 * 找基准
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 * @return 基准位置
 */
template<typename T,typename _Pr>
int partition(T arr[], const int& left, const int& right,  _Pr cmp) {
    int i = left;
    int j = right;
    T temp = arr[left];
    while (i < j) {
        while (i < j && !cmp(arr[j], temp)) {
            --j;
        }
        if (i < j) {
            arr[i] = arr[j];
            ++i;
        }
        while (i < j && !cmp(temp, arr[i])) {
            ++i;
        }
        if (i < j) {
            arr[j] = arr[i];
            --j;
        }
    }
    arr[i] = temp;
    return i;
}
/**
 * bfprt算法，找第k小数字
 * @param arr 数组
 * @param left 开始位置
 * @param right 结束位置
 * @param k 第k个数字
 * @param cmp 小于
 * @return 第k小数字
 */
template<typename T,typename _Pr>
T bfprt(T *arr, const int& left, const int& right, const int& k,  _Pr cmp) {
    int mid_id = find_mid(arr, left, right, cmp);
    if (mid_id != left) {
        std::swap(arr[left], arr[mid_id]);
    }
    int pivot = partition(arr, left, right, cmp);
    int num = pivot - left + 1;
    if (num == k) {
        return arr[pivot];
    }
    else if (num > k) {
        return bfprt(arr, left, pivot - 1, k, cmp);
    }
    return bfprt(arr, pivot + 1, right, k - num, cmp);
}
/*
#include <random>
#include <algorithm>
#include "find_k/find_k.hpp"
using namespace std;
bool cmp(const int& a, const int& b) {
    return a < b;
}
int main() {
    random_device rd;
    const int n= static_cast<int>(rd()%100+50);
    int a[n];
    for(int& c:a) {
        c = static_cast<int>(rd() % 1000);
    }
    int b[n];
    memcpy(b,a,sizeof(int)*n);
    sort(b,b+n,cmp);
    for(int& c:b)cout<<c<<' ';
    cout<<endl;
    cout<<bfprt(a,0,n-1,(n+1)/2,cmp)<<endl;
    cout<<b[(n-1)/2]<<endl;
    return 0;
}
 */