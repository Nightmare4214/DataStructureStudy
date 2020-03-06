#include "DirectedGraph_AdjacencyMatrix.hpp"
#include <queue>
/**
 * dfs拓扑排序
 * @param u 现在在访问的点
 * @param visit 访问，0没访问过，1正在访问，-1没访问过
 * @param top_sort 逆拓扑排序
 * @param cnt 逆拓扑排序长度
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyMatrix::_dfs_top_sort(const size_t &u, int *visit, int *top_sort, int &cnt) const {
    visit[u]=1;
    for(size_t v=0;v<this->vertex_cnt;++v){
        int w=this->adjacency_matrix[u][v];
        if(w==inf||w==0){
            continue;
        }
        if(visit[v]==1){
            return false;
        }
        else if(visit[v]==0&&!_dfs_top_sort(v,visit,top_sort,cnt)){
            return false;
        }
    }
    visit[u]=-1;
    top_sort[cnt]=u;
    ++cnt;
    return true;
}

DirectedGraph_AdjacencyMatrix::DirectedGraph_AdjacencyMatrix(const int &n):Graph_AdjacencyMatrix(n) {}
/**
 * 图中增加一个边<i,j>，weight
 * @param i 顶点1
 * @param j 顶点2
 * @param weight 权值
 */
void DirectedGraph_AdjacencyMatrix::graph_add(const size_t &i, const size_t &j, const int &weight) {
    if(adjacency_matrix== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    this->adjacency_matrix[i][j]=weight;
    ++edge_cnt;
}
/**
 * 删除边<i,j>
 * @param i 顶点1
 * @param j 顶点2
 */
void DirectedGraph_AdjacencyMatrix::graph_delete(const size_t &i, const size_t &j) {
    if(adjacency_matrix== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return;
    }
    this->adjacency_matrix[i][j]=inf;
    --edge_cnt;
}
/**
 * 获得顶点的度
 * @param n 顶点
 * @return 顶点的度
 */
size_t DirectedGraph_AdjacencyMatrix::degree(const size_t &n) const {
    return in_degree(n)+out_degree(n);
}

bool DirectedGraph_AdjacencyMatrix::topological_sort_kahn(int *top_sort) const {
    int* in=new int[this->vertex_cnt]{};
    for(size_t u=0;u<this->vertex_cnt;++u){
        for(size_t v=0;v<this->vertex_cnt;++v){
            int w=this->adjacency_matrix[u][v];
            if(w==inf||w==0){
                continue;
            }
            ++in[v];
        }
    }
    std::queue<size_t> q;
    for(size_t u=0;u<this->vertex_cnt;++u){
        if(in[u]==0){
            q.push(u);
        }
    }
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        top_sort[cnt]=u;
        ++cnt;
        for(int v=0;v<this->vertex_cnt;++v){
            int w=this->adjacency_matrix[u][v];
            if(w==inf||w==0){
                continue;
            }
            --in[v];
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    delete[] in;
    in=nullptr;
    return cnt==this->vertex_cnt;
}

bool DirectedGraph_AdjacencyMatrix::topological_sort_dfs(int *top_sort) const {
    int* visit=new int[this->vertex_cnt]{};
    int cnt=0;
    for(size_t u=0;u<this->vertex_cnt;++u){
        if(visit[u]==0&&!_dfs_top_sort(u,visit,top_sort,cnt)){
            delete[] visit;
            visit=nullptr;
            return false;
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
bool DirectedGraph_AdjacencyMatrix::DAG_shortest(size_t start, int *dist) const {
    if(start>=vertex_cnt){
        return false;
    }
    int* in=new int[this->vertex_cnt]{};
    for(size_t u=0;u<this->vertex_cnt;++u){
        for(size_t v=0;v<this->vertex_cnt;++v){
            int w=this->adjacency_matrix[u][v];
            if(w==inf||w==0){
                continue;
            }
            ++in[v];
        }
    }
    std::queue<size_t> q;
    for(size_t u=0;u<this->vertex_cnt;++u){
        if(in[u]==0){
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
        for(int v=0;v<this->vertex_cnt;++v){
            int w=this->adjacency_matrix[u][v];
            if(w==inf||w==0){
                continue;
            }
            --in[v];
            if(in[v]==0){
                q.push(v);
            }
            if(dist[u]>=inf){
                continue;
            }
            int temp=dist[u]+w;
            if(temp<dist[v]){
                dist[v]=temp;
            }
        }
    }
    delete[] in;
    in=nullptr;
    return cnt==this->vertex_cnt;
}
/**
 * DAG求最长路径
 * @param start 起点
 * @param dist 距离
 * @return 是否成功
 */
bool DirectedGraph_AdjacencyMatrix::DAG_longest(size_t start, int *dist) const {
    if(start>=vertex_cnt){
        return false;
    }
    int* in=new int[this->vertex_cnt]{};
    for(size_t u=0;u<this->vertex_cnt;++u){
        for(size_t v=0;v<this->vertex_cnt;++v){
            int w=this->adjacency_matrix[u][v];
            if(w==inf||w==0){
                continue;
            }
            ++in[v];
        }
    }
    std::queue<size_t> q;
    for(size_t u=0;u<this->vertex_cnt;++u){
        if(in[u]==0){
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
        for(int v=0;v<this->vertex_cnt;++v){
            int w=this->adjacency_matrix[u][v];
            if(w==inf||w==0){
                continue;
            }
            --in[v];
            if(in[v]==0){
                q.push(v);
            }
            if(dist[u]<=0xfefefefe){
                continue;
            }
            int temp=dist[u]+w;
            if(temp>dist[v]){
                dist[v]=temp;
            }
        }
    }
    delete[] in;
    in=nullptr;
    return cnt==this->vertex_cnt;
}
