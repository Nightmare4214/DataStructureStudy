#include "UndirectedGraph_AdjacencyList.hpp"

UndirectedGraph_AdjacencyList::UndirectedGraph_AdjacencyList(const int &n):Graph_AdjacencyList(n){}
/**
 * 图中增加一个边<i,j>，weight
 * @param i 顶点1
 * @param j 顶点2
 * @param weight 权值
 */
void UndirectedGraph_AdjacencyList::graph_add(const size_t &i, const size_t &j, const int &weight) {
    if(adjacency_list== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    auto* temp=new ArcNode(j,weight);
    temp->next=adjacency_list[i].first_arc->next;
    adjacency_list[i].first_arc->next=temp;

    temp=new ArcNode(i,weight);
    adjacency_list[j].first_arc->next=temp;
    ++edge_cnt;
}

/**
 * 删除边<i,j>
 * @param i 顶点1
 * @param j 顶点2
 */
void UndirectedGraph_AdjacencyList::graph_delete(const size_t &i, const size_t &j) {
    if(adjacency_list== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    ArcNode* p,*q;
    p=adjacency_list[i].first_arc;
    while(p->next!= nullptr&&p->next->adj_vex!=j){
        p=p->next;
    }
    if(p->next== nullptr){
        return;
    }
    q=p->next;
    p->next=q->next;
    delete q;

    p=adjacency_list[j].first_arc;
    while(p->next!= nullptr&&p->next->adj_vex!=i){
        p=p->next;
    }
    if(p->next== nullptr){
        return;
    }
    q=p->next;
    p->next=q->next;
    delete q;
    q= nullptr;
}
/**
 * 获得顶点的度
 * @param n 顶点
 * @return 顶点的度
 */
size_t UndirectedGraph_AdjacencyList::degree(const size_t& n) const {
    return out_degree(n);
}
