#pragma once
#include <iostream>
#include <random>
#include <cstring>
#include <stack>
/**
 * 选择排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void select_sort(T arr[], const int& n, _Pr cmp) {
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        //选择最小的
        for (int j = i + 1; j < n; ++j) {
            if (cmp(arr[j], arr[min_index])) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[min_index], arr[i]);
        }
    }
}
/**
 * 选择排序优化(每次选择最大的和最小的)
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void select_sort2(T arr[], const int& n, _Pr cmp) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int min_index = left;
        int max_index = right;
        for (int i = left; i <= right; ++i) {
            if (cmp(arr[i], arr[min_index])) {
                min_index = i;
            }
            if (cmp(arr[max_index], arr[i])) {
                max_index = i;
            }
        }
        if (min_index != left) {
            std::swap(arr[min_index], arr[left]);
        }
        //最小值的位置已经发生了改变
        if (max_index == left) {
            max_index = min_index;
        }
        if (max_index != right) {
            std::swap(arr[max_index], arr[right]);
        }
        ++left;
        --right;
    }
}
/**
 * 插入排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void insert_sort(T arr[], const int& n, _Pr cmp) {
    for (int i = 1; i < n; ++i) {
        T temp = arr[i];
        int index = i - 1;
        //找插入位置
        while (index >= 0 && cmp(temp, arr[index])) {
            arr[index + 1] = arr[index];
            --index;
        }
        arr[index + 1] = temp;
    }
}
/**
 * 二分插入排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void binary_insert_sort(T arr[], const int& n, _Pr cmp) {
    for (int i = 1; i < n; ++i) {
        T temp = arr[i];
        int low = 0;
        int high = i - 1;
        //二分找插入位置
        while (low <= high) {
            int mid = (low + high) / 2;
            if (!cmp(temp, arr[mid])) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        for (int j = i - 1; j >= high + 1; --j) {
            arr[j + 1] = arr[j];
        }
        arr[high + 1] = temp;
    }
}
/**
 * 希尔排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 * @param gap 间隔
 */
template<typename T,typename _Pr>
void shell_sort(T arr[], const int& n, _Pr cmp, int gap) {
    for (; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            T temp = arr[i];
            int j = i - gap;
            while (j >= 0 && !cmp(arr[j], temp)) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = temp;
        }
    }
}
/**
 * 冒泡排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void bubble_sort(T arr[], const int& n, _Pr cmp) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (cmp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
/**
 * 冒泡排序优化（没发生交换就退出）
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void bubble_sort2(T arr[], const int& n, _Pr cmp) {
    for (int i = 0; i < n - 1; ++i) {
        //是否发生交换
        bool is_swap = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (cmp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
                //交换
                is_swap = true;
            }
        }
        if (!is_swap) {
            //没发生交换
            break;
        }
    }
}
/**
 * 冒泡排序优化2（没发生交换就退出,交换只交换到最后发生交换的位置）
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于(想要稳定排序就传小于等于)
 */
template<typename T,typename _Pr>
void bubble_sort3(T arr[], const int& n, _Pr cmp) {
    bool flag;
    //交换进行到的位置（后面的都是已经排过序的）
    int sort_bound = n - 1;
    for (int i = 0; i < n - 1; ++i) {
        flag = false;
        //最后一次发生交换
        int last_exchanged = sort_bound - 1;
        for (int j = 0; j < sort_bound; ++j) {
            if (cmp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
                flag = true;
                last_exchanged = j;
            }
        }
        sort_bound = last_exchanged;
        if (!flag) {
            break;
        }
    }
}
/**
 * 双向冒泡排序(鸡尾酒排序)
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void cock_tail_sort(T arr[], const int& n, _Pr cmp) {
    int low = 0;
    int high = n - 1;
    while (low < high) {
        //大的交换到右边
        for (int i = low; i < high; ++i) {
            if (cmp(arr[i + 1], arr[i])) {
                std::swap(arr[i], arr[i + 1]);
            }
        }
        --high;
        //小的交换到左边
        for (int i = high; i > low; --i) {
            if (cmp(arr[i], arr[i - 1])) {
                std::swap(arr[i - 1], arr[i]);
            }
        }
        ++low;
    }
}
/**
 * 找到哨兵
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 * @return 快排分界线
 */
template<typename T,typename _Pr>
int partition(T arr[], const int& left, const int& right, _Pr cmp) {
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
 * 快速排序
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    if (left < right) {
        //分界线
        int pivot = partition(arr, left, right, cmp);
        //左边快排
        quick_sort(arr, left, pivot - 1, cmp);
        //右边快排
        quick_sort(arr, pivot + 1, right, cmp);
    }
}

/**
 * 随机选择基准
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 */
template<typename T>
void random_partition(T arr[], const int& left, const int& right) {
    static std::random_device _rd;
    int i = static_cast<int>(_rd() % (right - left + 1) + left);
    std::swap(arr[i], arr[left]);
}
/**
 * 快速排序优化(随机选择基准)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort2(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    if (left < right) {
        random_partition(arr, left, right);
        //分界线
        int pivot = partition(arr, left, right, cmp);
        //左边快排
        quick_sort2(arr, left, pivot - 1, cmp);
        //右边快排
        quick_sort2(arr, pivot + 1, right, cmp);
    }
}
/**
 * 快速排序优化(随机选择基准，优化递归栈空间)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort3(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    if (left < right) {
        random_partition(arr, left, right);
        //分界线
        int pivot = partition(arr, left, right, cmp);
        //哪边比较少就先排哪边
        if (pivot - left > right - pivot) {
            //右边快排
            quick_sort3(arr, pivot + 1, right, cmp);
            //左边快排
            quick_sort3(arr, left, pivot - 1, cmp);
        }
        else {
            //左边快排
            quick_sort3(arr, left, pivot - 1, cmp);
            //右边快排
            quick_sort3(arr, pivot + 1, right, cmp);
        }
    }
}
/**
 * 非递归快排(随机选择基准，优化递归栈空间)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort4(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    std::stack<int> s;
    s.push(right);
    s.push(left);
    while (!s.empty()) {
        int left_pos = s.top();
        s.pop();
        int right_pos = s.top();
        s.pop();
        if (right_pos <= left_pos) {
            continue;
        }
        //分界线
        int pivot = partition(arr, left_pos, right_pos, cmp);
        //哪边比较少就先排哪边
        if (pivot - left > right - pivot) {
            //左边快排
            s.push(pivot - 1);
            s.push(left_pos);

            //右边快排
            s.push(right_pos);
            s.push(pivot + 1);
        }
        else {
            //右边快排
            s.push(right_pos);
            s.push(pivot + 1);

            //左边快排
            s.push(pivot - 1);
            s.push(left_pos);
        }
    }
}
/**
 * 三数取中
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void select_mid_of_three(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0 || left >= right) {
        return;
    }
    else if (left + 1 == right) {
        if (cmp(arr[right], arr[left])) {
            std::swap(arr[left], arr[right]);
        }
        return;
    }
    int mid = (left + right) / 2;
    if (cmp(arr[mid], arr[left])) {
        std::swap(arr[mid], arr[left]);
    }
    if (cmp(arr[right], arr[left])) {
        std::swap(arr[right], arr[left]);
    }
    if (cmp(arr[right], arr[mid])) {
        std::swap(arr[right], arr[mid]);
    }
    std::swap(arr[mid], arr[left + 1]);
}
/**
 * 快速排序优化(三数取中，优化递归栈空间)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort5(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    if (left < right) {
        select_mid_of_three(arr, left, right, cmp);
        //分界线
        int pivot = partition(arr, left + 1, right - 1, cmp);
        //哪边比较少就先排哪边
        if (pivot - left > right - pivot) {
            //右边快排
            quick_sort5(arr, pivot + 1, right, cmp);
            //左边快排
            quick_sort5(arr, left, pivot - 1, cmp);
        }
        else {
            //左边快排
            quick_sort5(arr, left, pivot - 1, cmp);
            //右边快排
            quick_sort5(arr, pivot + 1, right, cmp);
        }
    }
}
/**
 * 快速排序优化(三数取中，聚集相等元素，优化递归栈空间)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort6(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    if (left < right) {
        //三数取中
        int mid = (left + right) / 2;
        if (cmp(arr[right], arr[left])) {
            std::swap(arr[right], arr[left]);
        }
        if (cmp(arr[right], arr[mid])) {
            std::swap(arr[right], arr[mid]);
        }
        if (cmp(arr[left], arr[mid])) {
            std::swap(arr[left], arr[mid]);
        }
        //先把基准值调到两侧，然后一起交换到中间

        //左边基准值位置
        int left_gather_pos = left;
        //右边基准值位置
        int right_gather_pos = right;
        int i = left;
        int j = right;
        //基准值
        T temp = arr[left];
        while (i < j) {
            //交换右边的
            while (i < j && !cmp(arr[j], temp)) {
                //遇到基准值，交换到右侧
                if (arr[j] == temp) {
                    std::swap(arr[j], arr[right_gather_pos]);
                    --right_gather_pos;
                }
                --j;
            }
            arr[i] = arr[j];
            //交换左边的
            while (i < j && !cmp(temp, arr[i])) {
                //遇到基准值，交换到左侧
                if (arr[i] == temp) {
                    std::swap(arr[i], arr[left_gather_pos]);
                    ++left_gather_pos;
                }
                ++i;
            }
            arr[j] = arr[i];
        }
        arr[i] = temp;

        //把左边的基准值调到中间
        --i;
        --left_gather_pos;
        while (left_gather_pos >= left) {
            std::swap(arr[i], arr[left_gather_pos]);
            --i;
            --left_gather_pos;
        }

        //把右边的基准值调到中间
        ++j;
        ++right_gather_pos;
        while (right_gather_pos <= right) {
            std::swap(arr[j], arr[right_gather_pos]);
            ++j;
            ++right_gather_pos;
        }
        //哪边比较少就先排哪边
        if (i - left > right - j) {
            //右边快排
            quick_sort6(arr, j, right, cmp);
            //左边快排
            quick_sort6(arr, left, i, cmp);
        }
        else {
            //左边快排
            quick_sort6(arr, left, i, cmp);
            //右边快排
            quick_sort6(arr, j, right, cmp);
        }
    }
}
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
        //找插入位置
        while (index >= left && cmp(temp, arr[index])) {
            arr[index + 1] = arr[index];
            --index;
        }
        arr[index + 1] = temp;
    }
}
/**
 * 快速排序优化(元素个数较少时使用插入排序，三数取中，聚集相等元素，优化递归栈空间)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 * @param M 元素个数小于M时，使用插入排序
 */
template<typename T,typename _Pr>
void quick_sort7(T arr[], const int& left, const int& right, _Pr cmp, const size_t& M = 25) {
    if (left < 0 || right < 0) {
        return;
    }
    if (right - left + 1 < M) {
        insert_sort(arr, left, right, cmp);
    }
    if (left < right) {
        //三数取中
        int mid = (left + right) / 2;
        if (cmp(arr[right], arr[left])) {
            std::swap(arr[right], arr[left]);
        }
        if (cmp(arr[right], arr[mid])) {
            std::swap(arr[right], arr[mid]);
        }
        if (cmp(arr[left], arr[mid])) {
            std::swap(arr[left], arr[mid]);
        }
        //先把基准值调到两侧，然后一起交换到中间

        //左边基准值位置
        int left_gather_pos = left;
        //右边基准值位置
        int right_gather_pos = right;
        int i = left;
        int j = right;
        //基准值
        T temp = arr[left];
        while (i < j) {
            //交换右边的
            while (i < j && !cmp(arr[j], temp)) {
                //遇到基准值，交换到右侧
                if (arr[j] == temp) {
                    std::swap(arr[j], arr[right_gather_pos]);
                    --right_gather_pos;
                }
                --j;
            }
            arr[i] = arr[j];
            //交换左边的
            while (i < j && !cmp(temp, arr[i])) {
                //遇到基准值，交换到左侧
                if (arr[i] == temp) {
                    std::swap(arr[i], arr[left_gather_pos]);
                    ++left_gather_pos;
                }
                ++i;
            }
            arr[j] = arr[i];
        }
        arr[i] = temp;

        //把左边的基准值调到中间
        --i;
        --left_gather_pos;
        while (left_gather_pos >= left) {
            std::swap(arr[i], arr[left_gather_pos]);
            --i;
            --left_gather_pos;
        }

        //把右边的基准值调到中间
        ++j;
        ++right_gather_pos;
        while (right_gather_pos <= right) {
            std::swap(arr[j], arr[right_gather_pos]);
            ++j;
            ++right_gather_pos;
        }
        //哪边比较少就先排哪边
        if (i - left > right - j) {
            //右边快排
            quick_sort7(arr, j, right, cmp);
            //左边快排
            quick_sort7(arr, left, i, cmp);
        }
        else {
            //左边快排
            quick_sort7(arr, left, i, cmp);
            //右边快排
            quick_sort7(arr, j, right, cmp);
        }
    }
}
/**
 * 快速排序优化(三数取中.尾递归)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void quick_sort8(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    int pivot;
    int low = left;
    int high = right;
    while (low < high) {
        select_mid_of_three(arr, low, high, cmp);
        //分界线
        pivot = partition(arr, low + 1, high - 1, cmp);
        quick_sort8(arr, low, pivot - 1, cmp);
        low = pivot + 1;
    }
}
/**
 * 快速排序优化(非递归，元素个数较少时使用插入排序，三数取中，聚集相等元素，优化递归栈空间)
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 * @param M 元素个数小于M时，使用插入排序
 */
template<typename T,typename _Pr>
void quick_sort9(T arr[], const int& left, const int& right, _Pr cmp, const size_t& M = 25) {
    if (left < 0 || right < 0) {
        return;
    }
    std::stack<int> s;
    s.push(right);
    s.push(left);
    while (!s.empty()) {
        int left_pos = s.top();
        s.pop();
        int right_pos = s.top();
        s.pop();
        if (right_pos <= left_pos) {
            continue;
        }
        if (right_pos - left_pos + 1 < M) {
            insert_sort(arr, left_pos, right_pos, cmp);
            continue;
        }
        //三数取中
        int mid = (left_pos + right_pos) / 2;
        if (cmp(arr[right_pos], arr[left_pos])) {
            std::swap(arr[right_pos], arr[left_pos]);
        }
        if (cmp(arr[right_pos], arr[mid])) {
            std::swap(arr[right_pos], arr[mid]);
        }
        if (cmp(arr[left_pos], arr[mid])) {
            std::swap(arr[left_pos], arr[mid]);
        }
        //先把基准值调到两侧，然后一起交换到中间

        //左边基准值位置
        int left_gather_pos = left_pos;
        //右边基准值位置
        int right_gather_pos = right_pos;
        int i = left_pos;
        int j = right_pos;
        //基准值
        T temp = arr[left_pos];
        while (i < j) {
            //交换右边的
            while (i < j && !cmp(arr[j], temp)) {
                //遇到基准值，交换到右侧
                if (arr[j] == temp) {
                    std::swap(arr[j], arr[right_gather_pos]);
                    --right_gather_pos;
                }
                --j;
            }
            arr[i] = arr[j];
            //交换左边的
            while (i < j && !cmp(temp, arr[i])) {
                //遇到基准值，交换到左侧
                if (arr[i] == temp) {
                    std::swap(arr[i], arr[left_gather_pos]);
                    ++left_gather_pos;
                }
                ++i;
            }
            arr[j] = arr[i];
        }
        arr[i] = temp;

        //把左边的基准值调到中间
        --i;
        --left_gather_pos;
        while (left_gather_pos >= left_pos) {
            std::swap(arr[i], arr[left_gather_pos]);
            --i;
            --left_gather_pos;
        }

        //把右边的基准值调到中间
        ++j;
        ++right_gather_pos;
        while (right_gather_pos <= right_pos) {
            std::swap(arr[j], arr[right_gather_pos]);
            ++j;
            ++right_gather_pos;
        }
        //哪边比较少就先排哪边
        if (i - left_pos > right_pos - j) {
            //左边快排
            s.push(i);
            s.push(left_pos);

            //右边快排
            s.push(right_pos);
            s.push(j);
        }
        else {
            //右边快排
            s.push(right_pos);
            s.push(j);

            //左边快排
            s.push(i);
            s.push(left_pos);
        }
    }
}
/**
 * 调整大根堆
 * @param arr 堆
 * @param cur 要调整的节点
 * @param n 堆长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void heap_adjust(T arr[], int cur, const int& n, _Pr cmp) {
    T temp = arr[cur];
    //从0编号的左孩子
    int child = 2 * cur + 1;
    while (child < n) {
        //右孩子比较大，就选择右孩子
        if (child + 1 < n && cmp(arr[child], arr[child + 1])) {
            ++child;
        }
        //已经比两个孩子都大了，就结束调整
        if (!cmp(temp, arr[child])) {
            break;
        }
        arr[cur] = arr[child];
        cur = child;
        child = 2 * cur + 1;
    }
    arr[cur] = temp;
}
/**
 * 堆排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void heap_sort(T arr[], const int& n, _Pr cmp) {
    //建立一个大根堆
    for (int i = n / 2 - 1; i >= 0; --i) {
        heap_adjust(arr, i, n, cmp);
    }
    for (int i = n - 1; i >= 0; --i) {
        //最大的元素换到最后面
        std::swap(arr[0], arr[i]);
        //调整堆
        heap_adjust(arr, 0, i, cmp);
    }
}
/**
 * 归并
 * @param arr 待排序数组
 * @param low 开始位置
 * @param mid 中间位置
 * @param high 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge(T arr[], const int& low, const int& mid, const int& high, _Pr cmp) {
    int i = low;
    int j = mid + 1;
    int k = 0;
    //临时存放
    T* temp = new T[high - low + 1];
    while (i <= mid && j <= high) {
        if (!cmp(arr[j], arr[i])) {
            temp[k] = arr[i];
            ++i;
        }
        else {
            temp[k] = arr[j];
            ++j;
        }
        ++k;
    }
    while (i <= mid) {
        temp[k] = arr[i];
        ++i;
        ++k;
    }
    while (j <= high) {
        temp[k] = arr[j];
        ++j;
        ++k;
    }
    //拷贝回原数组
    memcpy(arr + low, temp, sizeof(T) * (high - low + 1));
    delete[] temp;
}
/**
 * 归并排序
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge_sort(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0) {
        return;
    }
    if (left < right) {
        int mid = (left + right) / 2;
        //左边归并
        merge_sort(arr, left, mid, cmp);
        //右边归并
        merge_sort(arr, mid + 1, right, cmp);
        //归并
        merge(arr, left, mid, right, cmp);
    }
}
/**
 * 将src归并到des
 * @param src 原始数组
 * @param des 归并数组
 * @param left 开始位置
 * @param mid 中间位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge2(T src[], T des[], const int& left, const int& mid, const int& right, _Pr cmp) {
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (!cmp(src[j], src[i])) {
            des[k] = src[i];
            ++i;
        }
        else {
            des[k] = src[j];
            ++j;
        }
        ++k;
    }
    while (i <= mid) {
        des[k] = src[i];
        ++i;
        ++k;
    }
    while (j <= right) {
        des[k] = src[j];
        ++j;
        ++k;
    }
}
/**
 * 归并相邻
 * @param src 原始数组
 * @param des 归并数组
 * @param left 开始位置
 * @param right 结束位置
 * @param s 归并长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge_pass(T src[], T des[], const int& left, const int& right, const int& s, _Pr cmp) {
    int i = left;
    while (i + 2 * s <= right + 1) {
        //归并[i:i+s) [i+s:i+2s)
        merge2(src, des, i, i + s - 1, i + 2 * s - 1, cmp);
        i += 2 * s;
    }
    //还差[i:n)没有归并
    if (i + s <= right) {
        //归并[i:i+s) [i+s:n)
        merge2(src, des, i, i + s - 1, right, cmp);
    }
    else {
        //剩下一段不足s，就直接复制就可以了
        while (i <= right) {
            des[i] = src[i];
            ++i;
        }
    }
}
/**
 * 非递归归并排序
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge_sort2(T arr[], const int& left, const int& right, _Pr cmp) {
    int len = right - left + 1;
    T* temp = new T[len];
    int s = 1;
    while (s < len) {
        //归并到临时数组
        merge_pass(arr, temp, left, right, s, cmp);
        s += s;
        //临时数组归并到原数组
        merge_pass(temp, arr, left, right, s, cmp);
        s += s;
    }
    delete[] temp;
}
/**
 * 非递归归并排序
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge_sort3(T arr[], const int& left, const int& right, _Pr cmp) {
    int s = 1;
    int low, mid, high;
    int n = right - left + 1;
    while (s < n) {
        low = left;
        while (low + s < n) {
            mid = low + s - 1;
            high = mid + s;
            if (high > n - 1) {
                high = n - 1;
            }
            merge(arr, low, mid, high, cmp);
            low = high + 1;
        }
        s += s;
    }
}
/**
 * 归并排序 分sqrt(n)段
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge_sort4(T arr[], const int& left, const int& right, _Pr cmp) {
    if (left < 0 || right < 0 || left >= right) {
        return;
    }
    //根号n
    int root = static_cast<int>(sqrt(static_cast<double>(right - left + 1)));
    int i;
    for (i = left; i + root - 1 <= right; i += root) {
        merge_sort4(arr, i, i + root - 1, cmp);
    }
    if (i < right) {
        merge_sort4(arr, i, right, cmp);
    }
    for (i = left; i + 2 * root - 1 <= right; i += root) {
        //对[left,left+root)和[left+root,left+2root)
        //下次是[left,left+2root)和[left+2root,left+3root)
        //下次是[left,left+3root)和[left+3root,left+4root)
        //....
        merge(arr, left, i + root - 1, i + 2 * root - 1, cmp);
    }
    if (i + root - 1 < right) {
        //对[left,left+root*root)和[left+root*root,right]进行排序
        merge(arr, left, i + root - 1, right, cmp);
    }
    //否则left+root*root-1刚刚好是right，也就是被整除了
}
/**
 * 归并相邻
 * @param src 原始数组
 * @param des 归并数组
 * @param split 分裂数组
 * @param cnt 分裂数组长度
 * @param right 结束位置
 * @param s 归并长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void merge_pass2(T src[], T des[], const int* split, const int& cnt, const int& right,
                 const int& s, _Pr cmp) {
    int i = 0;
    while (i + 2 * s <= cnt) {
        int r = split[i + 2 * s] - 1;
        if (i + 2 * s == cnt)r = right;
        merge2(src, des, split[i], split[i + s] - 1, r, cmp);
        i += 2 * s;
    }
    if (i + s < cnt) {
        merge2(src, des, split[i], split[i + s] - 1, right, cmp);
    }
    else if (i < cnt) {
        for (int j = split[i]; j <= right; ++j) {
            des[j] = src[j];
        }
    }
}
/**
 * 自然合并排序
 * @param arr 待排序数组
 * @param left 开始位置
 * @param right 结束位置
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void natural_merge_sort(T arr[], const int& left, const int& right, _Pr cmp) {
    int n = right - left + 1;
    int* split = new int[n];
    int cnt = 0;
    split[cnt] = left;
    ++cnt;
    for (int i = left + 1; i <= right; ++i) {
        if (cmp(arr[i], arr[i - 1])) {
            split[cnt] = i;
            ++cnt;
        }
    }
    int s = 1;
    T* temp = new T[n];
    while (s < cnt) {
        //归并到临时数组
        merge_pass2(arr, temp, split, cnt, right, s, cmp);
        s += s;
        //临时数组归并到原数组
        merge_pass2(temp, arr, split, cnt, right, s, cmp);
        s += s;
    }
    delete[] temp;
    delete[] split;
}
/**
 * 地精排序
 * @param arr 待排序数组
 * @param n 数组长度
 * @param cmp 小于
 */
template<typename T,typename _Pr>
void gnome_sort(T arr[], const int& n, _Pr cmp) {
    int i = 0;
    while (i < n) {
        if (i == 0 || !cmp(arr[i], arr[i - 1])) {
            ++i;
        }
        else {
            std::swap(arr[i - 1], arr[i]);
            --i;
        }
    }
}
/**
 * 计数排序
 * @param arr 待排序数组
 * @param n 数组长度
 */
void counting_sort(size_t arr[], const int& n) {
    if (n < 0) {
        return;
    }
    size_t max_num = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_num) {
            max_num = arr[i];
        }
    }
    //全0
    int* c = new int[max_num + 1]{};
    for (int i = 0; i < n; ++i) {
        ++c[arr[i]];
    }
    for (size_t i = 1; i <= max_num; ++i) {
        c[i] += c[i - 1];
    }
    auto* b = new size_t[n];
    for (int i = n - 1; i >= 0; --i) {
        --c[arr[i]];
        b[c[arr[i]]] = arr[i];
    }
    memcpy(arr, b, sizeof(size_t) * n);
    delete[] b;
    delete[] c;
}
/**
 * 基数排序
 * @param arr 待排序数组
 * @param n 数组长度
 */
void radix_sort(size_t arr[], const int& n, size_t System = 10) {
    if (n < 0) {
        return;
    }
    int max_num = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_num) {
            max_num = arr[i];
        }
    }
    auto* b = new size_t[n];
    int* c = new int[System];
    for (int base = 1; max_num / base != 0; base *= System) {
        memset(c, 0, sizeof(int) * System);
        for (int i = 0; i < n; ++i) {
            ++c[arr[i] / base % System];
        }
        for (size_t i = 1; i < System; ++i) {
            c[i] += c[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            --c[arr[i] / base % System];
            b[c[arr[i] / base % System]] = arr[i];
        }
        memcpy(arr, b, sizeof(size_t) * n);
    }
    delete[] b;
    delete[] c;
}
/*
#include "my_sort/my_sort.hpp"
#include <iostream>
using namespace std;
bool cmp(const int& a, const int& b) {
    return a < b;
}
int main() {
    int a[] = { 7,6,5,4,3,2,1 };
//    select_sort(a, 7, cmp);
//    select_sort2(a, 7, cmp);
//    insert_sort(a, 7, cmp);
//    binary_insert_sort(a, 7, cmp);
//    shell_sort(a, 7, cmp, 7 / 2);
//    bubble_sort(a, 7, cmp);
//    bubble_sort2(a, 7, cmp);
//    bubble_sort3(a, 7, cmp);
//    cock_tail_sort(a, 7, cmp);
//    quick_sort(a, 0, 6, cmp);
//    quick_sort2(a, 0, 6, cmp);
//    quick_sort3(a, 0, 6, cmp);
//    quick_sort4(a, 0, 6, cmp);
//    quick_sort5(a, 0, 6, cmp);
//    quick_sort6(a, 0, 6, cmp);
//    quick_sort7(a, 0, 6, cmp, 4);
//    quick_sort8(a, 0, 6, cmp);
    quick_sort9(a, 0, 6, cmp, 0);
//    heap_sort(a, 7, cmp);
//    merge_sort(a, 0, 6, cmp);
//    merge_sort2(a, 0, 6, cmp);
//    merge_sort3(a, 0, 6, cmp);
//    merge_sort4(a, 0, 6, cmp);
//    natural_merge_sort(a, 0, 6, cmp);
//    gnome_sort(a, 7, cmp);
    size_t b[] = { 7,6,5,4,3,2,1 };
//    counting_sort(b, 7);
    radix_sort(b, 7);
    for (int& c : a) {
        cout << c << ' ';
    }
    cout << endl;
    for (size_t& c : b) {
        cout << c << ' ';
    }
    cout << endl;
    return 0;
}
 */