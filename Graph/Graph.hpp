#pragma once
#include <cstring>
#include <cassert>
class Graph{
public:
    /**
     * 创建n个顶点的图
     * @param n 顶点数
     */
    virtual void graph_init(const size_t& n)=0;
    /**
     * 是否存在边<i,j>
     * @param i 顶点1
     * @param j 顶点2
     * @return 是否存在这条边
     */
    virtual bool graph_exist(const size_t &i,const size_t &j)const=0;
    /**
     * 图中边的数量
     * @return 边的数量
     */
    virtual size_t graph_edges()const=0;
    /**
     * 图中顶点的数量
     * @return 顶点的数量
     */
    virtual size_t graph_vertices()const=0;
    /**
     * 图中增加一个边<i,j>，weight
     * @param i 顶点1
     * @param j 顶点2
     * @param weight 权值
     */
    virtual void graph_add(const size_t& i,const size_t& j,const int& weight)=0;
    /**
     * 删除边<i,j>
     * @param i 顶点1
     * @param j 顶点2
     */
    virtual void graph_delete(const size_t& i,const size_t& j)=0;
    /**
     * 获得顶点的度
     * @param n 顶点
     * @return 顶点的度
     */
    virtual size_t degree(const size_t& n)const=0;
    /**
     * 获得顶点的出度
     * @param n 顶点
     * @return 顶点的出度
     */
    virtual size_t out_degree(const size_t& n)const=0;
    /**
     * 获得顶点的入度
     * @param n 顶点
     * @return 顶点的入度
     */
    virtual size_t in_degree(const size_t& n)const=0;
    /**
     * 广度优先搜索
     */
    virtual void bfs_search()const=0;
    /**
     * 深度优先搜索
     */
    virtual void dfs_search()const=0;
    /**
     * dijkstra算法(要保证边>=0)
     * @param s 起点
     * @param dist 起点到其他顶点的最短路径
     */
    virtual void dijkstra(const size_t& s,int dist[])const=0;
    /**
     * bellman-ford算法
     * @param s 起点
     * @param dist 从起点到对应点的距离
     * @return 是否有负环,没有返回true，有返回false
     */
    virtual bool bellman_ford(const size_t& s,int dist[])const=0;
    /**
     * spfa算法
     * @param s 起点
     * @param dist 从起点到对应点的距离
     * @return 是否有负环,没有返回true，有返回false
     */
    virtual bool spfa(const size_t& s,int dist[])const=0;
    /**
     * floyd算法
     * @param dist 距离矩阵
     */
    virtual void floyd(int** dist)const=0;
};