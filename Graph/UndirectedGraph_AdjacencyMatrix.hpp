#pragma once
#include "DirectedGraph_AdjacencyMatrix.hpp"
//基于邻接矩阵的无向图
class UndirectedGraph_AdjacencyMatrix:public Graph_AdjacencyMatrix{
public:
    explicit UndirectedGraph_AdjacencyMatrix(const int &n);

    void graph_add(const size_t &i, const size_t &j, const int &weight) override;

    void graph_delete(const size_t &i, const size_t &j) override;

    size_t degree(const size_t &n) const override;
};