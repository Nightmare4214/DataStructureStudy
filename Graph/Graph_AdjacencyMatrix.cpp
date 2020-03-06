#include "Graph_AdjacencyMatrix.hpp"
#include <iostream>
#include <queue>
/**
 * 广度遍历
 * @param start 开始起点
 * @param visit 访问过了没有
 * @param path 遍历序列
 * @param cnt 遍历了几个顶点
 */
void Graph_AdjacencyMatrix::bfs(const size_t& start,bool* visit,size_t* path,size_t* cnt)const {
    std::queue<size_t> q;
    q.push(start);
    visit[start]=true;
    while(!q.empty()){
        size_t cur=q.front();
        q.pop();
        path[*cnt]=cur;
        ++(*cnt);
        for(size_t i=0;i<vertex_cnt;++i){
            if(visit[i]||adjacency_matrix[cur][i]==0||adjacency_matrix[cur][i]==inf){
                continue;
            }
            visit[i]=true;
            q.push(i);
        }
    }
}
/**
 * 深度遍历
 * @param start 开始起点
 * @param path 遍历序列
 * @param cnt 遍历了几个顶点
 * @param visit 访问过了没有
 */
void Graph_AdjacencyMatrix::dfs(const size_t& start, size_t *path, size_t *cnt, bool *visit) const {
    visit[start]=true;
    path[*cnt]=start;
    ++(*cnt);
    for(size_t i=0;i<vertex_cnt;++i){
        if(visit[start]||adjacency_matrix[start][i]==0||adjacency_matrix[start][i]==inf){
            continue;
        }
        dfs(i,path,cnt,visit);
    }
}

Graph_AdjacencyMatrix::Graph_AdjacencyMatrix(): vertex_cnt(0), edge_cnt(0), adjacency_matrix(nullptr){}

Graph_AdjacencyMatrix::Graph_AdjacencyMatrix(const size_t &n): vertex_cnt(n), edge_cnt(0) {
    if(n>0){
        adjacency_matrix=new int*[n];
        for(size_t i=0;i<n;++i){
            adjacency_matrix[i]=new int[n];
            memset(adjacency_matrix[i],inf,sizeof(int)*n);
        }
        for(size_t i=0;i<n;++i){
            adjacency_matrix[i][i]=0;
        }
    }
}
/**
 * 销毁图
 */
void Graph_AdjacencyMatrix::destroy() {
    if(adjacency_matrix!= nullptr){
        for(size_t i=0;i<vertex_cnt;++i){
            delete[] adjacency_matrix[i];
            adjacency_matrix[i]= nullptr;
        }
        delete[] this->adjacency_matrix;
        adjacency_matrix= nullptr;
        vertex_cnt=0;
        edge_cnt=0;
    }
}

Graph_AdjacencyMatrix::~Graph_AdjacencyMatrix() {
    destroy();
}
/**
 * 创建n个顶点的图
 * @param n 顶点数
 */
void Graph_AdjacencyMatrix::graph_init(const size_t &n) {
    destroy();
    vertex_cnt=n;
    edge_cnt=0;
    if(n>0){
        adjacency_matrix=new int*[n];
        for(size_t i=0;i<n;++i){
            adjacency_matrix[i]=new int[n];
            memset(adjacency_matrix[i],inf,sizeof(int)*n);
        }
        for(size_t i=0;i<n;++i){
            adjacency_matrix[i][i]=0;
        }
    }
}
/**
 * 是否存在边<i,j>
 * @param i 顶点1
 * @param j 顶点2
 * @return 是否存在这条边
 */
bool Graph_AdjacencyMatrix::graph_exist(const size_t &i, const size_t &j) const {
    if(adjacency_matrix== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return false;
    }
    return this->adjacency_matrix[i][j]!=0&&this->adjacency_matrix[i][j]!=inf;
}
/**
 * 图中边的数量
 * @return 边的数量
 */
size_t Graph_AdjacencyMatrix::graph_edges() const {
    return this->edge_cnt;
}
/**
 * 图中顶点的数量
 * @return 顶点的数量
 */
size_t Graph_AdjacencyMatrix::graph_vertices() const {
    return this->vertex_cnt;
}
/**
 * 获得顶点的出度
 * @param n 顶点
 * @return 顶点的出度
 */
size_t Graph_AdjacencyMatrix::out_degree(const size_t &n) const {
    if(adjacency_matrix== nullptr||vertex_cnt<=n){
        return 0;
    }
    size_t cnt=0;
    for(size_t i=0;i<vertex_cnt;++i){
        if(adjacency_matrix[n][i]!=0&&adjacency_matrix[n][i]!=inf){
            ++cnt;
        }
    }
    return cnt;
}
/**
 * 获得顶点的入度
 * @param n 顶点
 * @return 顶点的入度
 */
size_t Graph_AdjacencyMatrix::in_degree(const size_t &n) const {
    if(adjacency_matrix== nullptr||vertex_cnt<=n){
        return 0;
    }
    size_t cnt=0;
    for(size_t i=0;i<vertex_cnt;++i){
        if(adjacency_matrix[i][n]!=0&&adjacency_matrix[i][n]!=inf){
            ++cnt;
        }
    }
    return cnt;
}
/**
 * 广度优先搜索
 */
void Graph_AdjacencyMatrix::bfs_search() const {
    if(adjacency_matrix== nullptr||vertex_cnt<=0){
        return;
    }
    auto* path=new size_t[vertex_cnt];
    bool* visit=new bool[vertex_cnt];
    memset(visit,false,sizeof(bool)*vertex_cnt);
    size_t cnt=0;
    for(size_t start=0;start<vertex_cnt;++start){
        if(visit[start]){
            continue;
        }
        bfs(start,visit,path,&cnt);
    }
    for(size_t i=0;i<cnt;++i){
        std::cout<<path[i]<<' ';
    }
    std::cout<<std::endl;
    delete[] path;
    delete[] visit;
    path=nullptr;
    visit=nullptr;
}
/**
 * 深度优先搜索
 */
void Graph_AdjacencyMatrix::dfs_search() const {
    auto* path=new size_t[vertex_cnt];
    bool* visit=new bool[vertex_cnt];
    memset(visit, false,sizeof(bool)*vertex_cnt);
    size_t cnt=0;
    for(size_t start=0;start<vertex_cnt;++start){
        if(visit[start]){
            continue;
        }
        dfs(start,path,&cnt,visit);
    }
    for(size_t i=0;i<cnt;++i){
        std::cout<<path[i]<<' ';
    }
    std::cout<<std::endl;
    delete[] path;
    delete[] visit;
    path=nullptr;
    visit=nullptr;
}
/**
 * dijkstra算法(要保证边>=0)
 * @param s 起点
 * @param dist 起点到其他顶点的最短路径
 */
void Graph_AdjacencyMatrix::dijkstra(const size_t& s, int* dist) const {
    //初始化为正无穷，代表不可到达
    memset(dist,0x3f,sizeof(int)*vertex_cnt);
    dist[s]=0;
    //是否访问过
    bool* visit=new bool[vertex_cnt];
    memset(visit,false,sizeof(bool)*vertex_cnt);
    for(size_t i=1;i<vertex_cnt;++i){
        int pos=-1;
        for(size_t j=1;j<=vertex_cnt;++j){
            //找一个尚未访问过的，且是最小的
            if(!visit[j]&&(pos==-1||dist[j]<dist[pos])) {
                pos = j;
            }
        }
        //都访问过了
        if(pos==-1){
            break;
        }
        for(size_t j=1;j<=vertex_cnt;++j){
            if(!visit[j]){
                int temp=dist[pos]+adjacency_matrix[pos][j];
                //松弛
                if(dist[j]<temp){
                    dist[j]=temp;
                }
            }
        }
    }
    delete[] visit;
    visit=nullptr;
}
/**
 * bellman-ford算法
 * @param s 起点
 * @param dist 从起点到对应点的距离
 * @return 是否有负环,没有返回true，有返回false
 */
bool Graph_AdjacencyMatrix::bellman_ford(const size_t& s, int* dist) const {
    memset(dist,0x3f,sizeof(int)*vertex_cnt);
    dist[s]=0;
    for(int i=1;i<vertex_cnt;++i){
        bool flag=false;
        for(size_t u=0;u<vertex_cnt;++u){
            for(size_t v=0;v<vertex_cnt;++v) {
                int temp = dist[u] + adjacency_matrix[u][v];
                if (temp < dist[v]) {
                    dist[v] = temp;
                    flag = true;
                }
            }
        }
        if(!flag){
            break;
        }
    }
    //测试能不能继续更新，来确认有没有负环
    for(size_t u=0;u<vertex_cnt;++u){
        for(size_t v=0;v<vertex_cnt;++v) {
            if (dist[u] + adjacency_matrix[u][v] < dist[v]) {
                //负环
                return false;
            }
        }
    }
    return true;
}
/**
 * spfa算法
 * @param s 起点
 * @param dist 从起点到对应点的距离
 * @return 是否有负环,没有返回true，有返回false
 */
bool Graph_AdjacencyMatrix::spfa(const size_t& s, int* dist) const {
    std::queue<size_t> q;
    int* cnt=new int[vertex_cnt]{};
    memset(dist,0x3f,sizeof(int)*vertex_cnt);
    bool* inq=new bool[vertex_cnt]{};
    cnt[s]=0;
    dist[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inq[u]=false;
        for(size_t v=0;v<vertex_cnt;++v){
            int temp=dist[u]+adjacency_matrix[u][v];
            if(temp<dist[v]){
                dist[v]=temp;
                if(inq[v]){
                    continue;
                }
                ++cnt[v];
                if(cnt[v]>=vertex_cnt){
                    return false;
                }
                inq[v]=true;
                q.push(v);
            }
        }
    }
    return true;
}
/**
 * floyd算法
 * @param dist 距离矩阵
 */
void Graph_AdjacencyMatrix::floyd(int** dist) const {
    memcpy(dist,adjacency_matrix,sizeof(int)*vertex_cnt*vertex_cnt);
    for(size_t k=0;k<vertex_cnt;++k){
        for(size_t i=0;i<vertex_cnt;++i){
            for(size_t j=0;j<vertex_cnt;++j){
                int temp=dist[i][k]+dist[k][j];
                if(temp<dist[i][j]){
                    dist[i][j]=temp;
                }
            }
        }
    }
}
