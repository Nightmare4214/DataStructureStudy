#include "DirectedGraph_AdjacencyList.hpp"
#include <queue>

/**
 * dfs拓扑排序
 * @param u 现在在访问的点
 * @param visit 访问，0没访问过，1正在访问，-1没访问过
 * @param top_sort 逆拓扑排序
 * @param cnt 逆拓扑排序长度
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyList::_dfs_top_sort(const size_t &u, int *visit, int *top_sort, int &cnt) const {
    visit[u]=1;
    visit[u]=-1;
    ArcNode* p=this->adjacency_list[u].first_arc->next;
    while(p!=nullptr){
        if(visit[p->adj_vex]==1){
            return false;
        }
        else if(visit[p->adj_vex]==0&&!_dfs_top_sort(p->adj_vex,visit,top_sort,cnt)){
            return false;
        }
    }
    top_sort[cnt]=u;
    ++cnt;
    return true;
}

DirectedGraph_AdjacencyList::DirectedGraph_AdjacencyList(const int &n):Graph_AdjacencyList(n){}
/**
 * 图中增加一个边<i,j>，weight
 * @param i 顶点1
 * @param j 顶点2
 * @param weight 权值
 */
void DirectedGraph_AdjacencyList::graph_add(const size_t &i, const size_t &j, const int &weight) {
    if(adjacency_list== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    auto* temp=new ArcNode(j,weight);
    temp->next=adjacency_list[i].first_arc->next;
    adjacency_list[i].first_arc->next=temp;
    ++edge_cnt;
}
/**
 * 删除边<i,j>
 * @param i 顶点1
 * @param j 顶点2
 */
void DirectedGraph_AdjacencyList::graph_delete(const size_t &i, const size_t &j) {
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
    q= nullptr;
}
/**
 * 获得顶点的度
 * @param n 顶点
 * @return 顶点的度
 */
size_t DirectedGraph_AdjacencyList::degree(const size_t &n) const {
    return in_degree(n)+out_degree(n);
}
/**
 * kahn算法获得拓扑排序
 * @param top_sort 拓扑排序
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyList::topological_sort_kahn(int *top_sort) const {
    int* in=new int[this->vertex_cnt]{};
    std::queue<size_t> q;
    for(size_t u=0; u < this->vertex_cnt; ++u){
        ArcNode* p=this->adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            ++in[p->adj_vex];
            p=p->next;
        }
    }
    for(size_t u=0; u < this->vertex_cnt; ++u){
        if(in[u] == 0){
            q.push(u);
        }
    }
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        top_sort[cnt]=u;
        ++cnt;
        ArcNode* p=this->adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            --in[p->adj_vex];
            if(in[p->adj_vex]==0){
                q.push(p->adj_vex);
            }
        }
    }
    delete[] in;
    in= nullptr;
    return cnt==this->vertex_cnt;
}
/**
 * dfs拓扑排序
 * @param top_sort 拓扑排序
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyList::topological_sort_dfs(int *top_sort) const {
    int* visit=new int[this->vertex_cnt]{};
    int cnt=0;
    for(size_t u=0;u<this->vertex_cnt;++u){
        if(visit[u]==0){
            bool flag=_dfs_top_sort(u,visit,top_sort,cnt);
            if(!flag){
                delete[] visit;
                visit=nullptr;
                return false;
            }
        }
    }
    delete[] visit;
    visit=nullptr;
    int i=0,j=vertex_cnt-1;
    while(i<j){
        std::swap(top_sort[i],top_sort[j]);
        ++i;
        --j;
    }
    return true;
}
/**
 * DAG求最短路径
 * @param start 起点
 * @param dist 距离
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyList::DAG_shortest(size_t start, int *dist) const {
    if(start>=vertex_cnt){
        return false;
    }
    int* in=new int[this->vertex_cnt]{};
    std::queue<size_t> q;
    for(size_t u=0; u < this->vertex_cnt; ++u){
        ArcNode* p=this->adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            ++in[p->adj_vex];
            p=p->next;
        }
    }
    for(size_t u=0; u < this->vertex_cnt; ++u){
        if(in[u] == 0){
            q.push(u);
        }
    }
    memset(dist,0x3f,sizeof(int)*vertex_cnt);
    dist[start]=0;
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ++cnt;
        ArcNode* p=this->adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            --in[p->adj_vex];
            if(in[p->adj_vex]==0){
                q.push(p->adj_vex);
            }
            if(dist[u]>=0x3f3f3f3f){
                continue;
            }
            int temp=dist[u]+p->weight;
            if(temp<dist[p->adj_vex]){
                dist[p->adj_vex]=temp;
            }
        }
    }
    delete[] in;
    in= nullptr;
    return cnt==this->vertex_cnt;
}
/**
 * DAG求最短路径
 * @param start 起点
 * @param dist 距离
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyList::DAG_longest(size_t start, int *dist) const {
    if(start>=vertex_cnt){
        return false;
    }
    int* in=new int[this->vertex_cnt]{};
    std::queue<size_t> q;
    for(size_t u=0; u < this->vertex_cnt; ++u){
        ArcNode* p=this->adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            ++in[p->adj_vex];
            p=p->next;
        }
    }
    for(size_t u=0; u < this->vertex_cnt; ++u){
        if(in[u] == 0){
            q.push(u);
        }
    }
    memset(dist,0xfe,sizeof(int)*vertex_cnt);
    dist[start]=0;
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ++cnt;
        ArcNode* p=this->adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            --in[p->adj_vex];
            if(in[p->adj_vex]==0){
                q.push(p->adj_vex);
            }
            if(dist[u]<=0xfefefefe){
                continue;
            }
            int temp=dist[u]+p->weight;
            if(temp>dist[p->adj_vex]){
                dist[p->adj_vex]=temp;
            }
        }
    }
    delete[] in;
    in= nullptr;
    return cnt==this->vertex_cnt;
}
