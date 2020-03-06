#pragma once
#include "Graph.hpp"
#include "VNode.hpp"
//基于邻接表的图
class Graph_AdjacencyList:public Graph{
protected:
    //顶点数
    int vertex_cnt;
    //边数
    int edge_cnt;
    //邻接表
    VNode* adjacency_list;

    void bfs(const size_t& start,bool* visit,size_t* path,size_t* cnt)const;

    void dfs(const size_t& start,bool* visit,size_t* path,size_t* cnt)const;
public:
    Graph_AdjacencyList();

    explicit Graph_AdjacencyList(const size_t& n);

    void destroy();

    ~Graph_AdjacencyList();

    void graph_init(const size_t &n) override;

    bool graph_exist(const size_t &i, const size_t &j) const override;

    size_t graph_edges() const override;

    size_t graph_vertices() const override;

    size_t out_degree(const size_t &n) const override;

    size_t in_degree(const size_t &n) const override;

    void bfs_search() const override;

    void dfs_search() const override;

    void dijkstra(const size_t& s, int* dist) const override;

    bool bellman_ford(const size_t& s,int* dist) const override;

    bool spfa(const size_t &s, int *dist) const override;

    void floyd(int **dist) const override;
};