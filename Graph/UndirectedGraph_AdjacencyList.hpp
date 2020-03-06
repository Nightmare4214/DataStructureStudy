#pragma once
#include "Graph_AdjacenecyList.hpp"
//基于邻接表的无向图
class UndirectedGraph_AdjacencyList:public Graph_AdjacencyList{
public:
    explicit UndirectedGraph_AdjacencyList(const int &n);

    void graph_add(const size_t &i, const size_t &j, const int &weight) override;

    void graph_delete(const size_t &i, const size_t &j) override;

    size_t degree(const size_t &n) const override;
};