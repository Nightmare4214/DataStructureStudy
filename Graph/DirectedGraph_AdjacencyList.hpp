#pragma once
#include "Graph_AdjacenecyList.hpp"
//基于邻接表的有向图
class DirectedGraph_AdjacencyList:public Graph_AdjacencyList{
private:
    bool _dfs_top_sort(const size_t& u,int visit[],int top_sort[],int& cnt)const;
public:
    explicit DirectedGraph_AdjacencyList(const int &n);

    void graph_add(const size_t &i, const size_t &j, const int &weight) override;

    void graph_delete(const size_t &i, const size_t &j) override;

    size_t degree(const size_t &n) const override;

    bool topological_sort_kahn(int top_sort[])const;

    bool topological_sort_dfs(int top_sort[])const;

    bool DAG_shortest(size_t start, int *dist)const;

    bool DAG_longest(size_t start,int dist[])const;
};