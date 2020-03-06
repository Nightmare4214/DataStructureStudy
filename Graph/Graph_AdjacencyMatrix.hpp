#pragma once
#include "Graph.hpp"
//基于邻接矩阵的图
class Graph_AdjacencyMatrix: public Graph{
protected:
    //顶点数
    int vertex_cnt;
    //边数
    int edge_cnt;
    //邻接矩阵
    int** adjacency_matrix;

    void bfs(const size_t& start,bool* visit,size_t* path,size_t* cnt)const;

    void dfs(const size_t& start,size_t * path,size_t* cnt,bool* visit)const;
public:
    //无穷，表示没有边
    static const int inf=0x3f3f3f3f;

    Graph_AdjacencyMatrix();

    explicit Graph_AdjacencyMatrix(const size_t& n);

    void destroy();

    ~Graph_AdjacencyMatrix();

    void graph_init(const size_t &n) override;

    bool graph_exist(const size_t &i, const size_t &j) const override;

    size_t graph_edges() const override;

    size_t graph_vertices() const override;

    size_t out_degree(const size_t &n) const override;

    size_t in_degree(const size_t &n) const override;

    void bfs_search() const override;

    void dfs_search() const override;

    void dijkstra(const size_t& s, int* dist) const override;

    bool bellman_ford(const size_t &s, int *dist) const override;

    bool spfa(const size_t &s, int *dist) const override;

    void floyd(int **dist) const override;
};