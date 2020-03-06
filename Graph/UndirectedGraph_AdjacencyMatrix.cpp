#include "UndirectedGraph_AdjacencyMatrix.hpp"

UndirectedGraph_AdjacencyMatrix::UndirectedGraph_AdjacencyMatrix(const int &n):Graph_AdjacencyMatrix(n){}
/**
 * 图中增加一个边<i,j>，weight
 * @param i 顶点1
 * @param j 顶点2
 * @param weight 权值
 */
void UndirectedGraph_AdjacencyMatrix::graph_add(const size_t &i, const size_t &j, const int &weight) {
    if(adjacency_matrix== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    this->adjacency_matrix[i][j]=weight;
    this->adjacency_matrix[j][i]=weight;
    ++edge_cnt;
}
/**
 * 删除边<i,j>
 * @param i 顶点1
 * @param j 顶点2
 */
void UndirectedGraph_AdjacencyMatrix::graph_delete(const size_t &i, const size_t &j) {
    if(adjacency_matrix== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    this->adjacency_matrix[i][j]=inf;
    this->adjacency_matrix[j][i]=inf;
    --edge_cnt;
}
/**
 * 获得顶点的度
 * @param n 顶点
 * @return 顶点的度
 */
size_t UndirectedGraph_AdjacencyMatrix::degree(const size_t &n) const {
    return in_degree(n);
}
