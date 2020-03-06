#include "Graph_AdjacenecyList.hpp"
#include <iostream>
#include <queue>
using namespace std;
/**
 * 广度遍历
 * @param start 开始起点
 * @param visit 访问过了没有
 * @param path 遍历序列
 * @param cnt 遍历了几个顶点
 */
void Graph_AdjacencyList::bfs(const size_t& start,bool* visit,size_t* path,size_t* cnt)const{
    queue<size_t> q;
    q.push(start);
    visit[start]=true;
    while(!q.empty()){
        size_t cur=q.front();
        q.pop();
        path[*cnt]=cur;
        ++(*cnt);
        ArcNode* p=adjacency_list[cur].first_arc->next;
        while(p!=nullptr){
            size_t to=p->adj_vex;
            p=p->next;
            if(visit[to]){
                continue;
            }
            visit[to]=true;
            q.push(to);
        }
    }
}
/**
 * 深度遍历
 * @param start 开始起点
 * @param visit 访问过了没有
 * @param path 遍历序列
 * @param cnt 遍历了几个顶点
 */
void Graph_AdjacencyList::dfs(const size_t& start, bool *visit, size_t *path, size_t *cnt) const {
    visit[start]=true;
    path[*cnt]=start;
    ++(*cnt);

    ArcNode* p=adjacency_list[start].first_arc->next;
    while(p!=nullptr){
        size_t to=p->adj_vex;
        p=p->next;
        if(visit[to]){
            continue;
        }
        dfs(to,visit,path,cnt);
    }
}

Graph_AdjacencyList::Graph_AdjacencyList():vertex_cnt(0),edge_cnt(0),adjacency_list(nullptr){}

Graph_AdjacencyList::Graph_AdjacencyList(const size_t &n):vertex_cnt(n),edge_cnt(0) {
    if(n>0){
        vertex_cnt=n;
        edge_cnt=0;
        adjacency_list=new VNode[n];
        for(size_t i=0;i<n;++i){
            adjacency_list[i].first_arc=new ArcNode;
        }
    }
}
/**
 * 销毁图
 */
void Graph_AdjacencyList::destroy() {
    if(adjacency_list!= nullptr){
        for(size_t i=0;i<vertex_cnt;++i){
            while(adjacency_list[i].first_arc->next!= nullptr){
                ArcNode* temp=adjacency_list[i].first_arc->next;
                adjacency_list[i].first_arc->next=temp->next;
                delete temp;
                temp= nullptr;
            }
            delete  adjacency_list[i].first_arc;
            adjacency_list[i].first_arc= nullptr;
        }
        delete[] adjacency_list;
        adjacency_list= nullptr;
    }
}

Graph_AdjacencyList::~Graph_AdjacencyList() {
    destroy();
}
/**
 * 创建n个顶点的图
 * @param n 顶点数
 */
void Graph_AdjacencyList::graph_init(const size_t &n) {
    destroy();
    if(n>0){
        vertex_cnt=n;
        edge_cnt=0;
        adjacency_list=new VNode[n];
        for(size_t i=0;i<n;++i){
            adjacency_list[i].first_arc=new ArcNode;
        }
    }
}
/**
 * 是否存在边<i,j>
 * @param i 顶点1
 * @param j 顶点2
 * @return 是否存在这条边
 */
bool Graph_AdjacencyList::graph_exist(const size_t &i, const size_t &j) const {
    if(adjacency_list== nullptr||vertex_cnt<=i||vertex_cnt<=j){
        return false;
    }
    ArcNode* p=adjacency_list[i].first_arc->next;
    while(p!= nullptr&&p->adj_vex!=j){
        p=p->next;
    }
    return p!= nullptr;
}
/**
 * 图中边的数量
 * @return 边的数量
 */
size_t Graph_AdjacencyList::graph_edges() const {
    return this->edge_cnt;
}
/**
 * 图中顶点的数量
 * @return 顶点的数量
 */
size_t Graph_AdjacencyList::graph_vertices() const {
    return this->vertex_cnt;
}

/**
 * 获得顶点的出度
 * @param n 顶点
 * @return 顶点的出度
 */
size_t Graph_AdjacencyList::out_degree(const size_t &n) const {
    if(adjacency_list== nullptr||vertex_cnt<=n){
        return 0;
    }
    size_t cnt=0;
    ArcNode* p=adjacency_list[n].first_arc->next;
    while(p!= nullptr){
        ++cnt;
        p=p->next;
    }
    return cnt;
}
/**
 * 获得顶点的入度
 * @param n 顶点
 * @return 顶点的入度
 */
size_t Graph_AdjacencyList::in_degree(const size_t &n) const {
    if(adjacency_list== nullptr||vertex_cnt<=n){
        return 0;
    }
    size_t cnt=0;
    for(size_t i=0;i<vertex_cnt;++i){
        if(i==n){
            continue;
        }
        ArcNode* p=adjacency_list[i].first_arc->next;
        while(p!= nullptr){
            if(p->adj_vex==n){
                ++cnt;
            }
            p=p->next;
        }
    }
    return cnt;
}
/**
 * 广度优先搜索
 */
void Graph_AdjacencyList::bfs_search() const {
    if(adjacency_list== nullptr||vertex_cnt<=0){
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
        cout<<path[i]<<' ';
    }
    cout<<endl;
    delete[] path;
    delete[] visit;
}
/**
 * 深度优先搜索
 */
void Graph_AdjacencyList::dfs_search() const {
    if(adjacency_list== nullptr||vertex_cnt<=0){
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
        dfs(start,visit,path,&cnt);
    }
    for(size_t i=0;i<cnt;++i){
        cout<<path[i]<<' ';
    }
    cout<<endl;
    delete[] path;
    delete[] visit;
}
/**
 * dijkstra算法(要保证边>=0)
 * @param s 起点
 * @param dist 起点到其他顶点的最短路径
 */
void Graph_AdjacencyList::dijkstra(const size_t& s, int* dist) const {
    //（负的代价，点）
    priority_queue<pair<int,size_t> > q;
    q.push(make_pair(-dist[s],s));

    //初始化为正无穷，代表不可到达
    memset(dist,0x3f,sizeof(int)*vertex_cnt);
    dist[s]=0;
    //是否访问过
    bool* visit=new bool[vertex_cnt];
    memset(visit,false,sizeof(bool)*vertex_cnt);
    int cnt=0;
    while(!q.empty()){
        size_t now=q.top().second;
        int cost=-q.top().first;
        if(!visit[now]){
            visit[now]=true;
            ++cnt;
            if(cnt==vertex_cnt){
                break;
            }
        }
        q.pop();
        if(cost>dist[now]){
            continue;
        }
        ArcNode* p=adjacency_list[now].first_arc->next;
        while(p!=nullptr){
            int v=p->adj_vex;
            int temp=dist[now]+p->weight;
            if(dist[v]>temp){
                dist[v]=temp;
                q.push(make_pair(-dist[v],v));
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
bool Graph_AdjacencyList::bellman_ford(const size_t& s,int* dist) const {
    memset(dist,0x3f,sizeof(int)*vertex_cnt);
    dist[s]=0;
    for(size_t i=1;i<vertex_cnt;++i){
        //是否更新过
        bool flag=false;
        for(size_t u=0; u < vertex_cnt; ++u){
            ArcNode* p=adjacency_list[u].first_arc->next;
            while(p!=nullptr){
                size_t v=p->adj_vex;
                int temp=dist[u]+p->weight;
                //松弛
                if(temp<dist[v]){
                    dist[v]=temp;
                    flag=true;
                }
                p=p->next;
            }
        }
        //没有更新过，提前退出
        if(!flag){
            break;
        }
    }
    //测试能不能继续更新，来确认有没有负环
    for(size_t u=0; u < vertex_cnt; ++u){
        ArcNode* p=adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            size_t v=p->adj_vex;
            if(dist[u]+p->weight<dist[v]){
                //负环
                return false;
            }
            p=p->next;
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
bool Graph_AdjacencyList::spfa(const size_t& s, int* dist) const {
    queue<size_t> q;
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
        ArcNode* p=adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            size_t v=p->adj_vex;
            int temp=dist[u]+p->weight;
            p=p->next;
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
void Graph_AdjacencyList::floyd(int **dist) const {
    for(size_t u=0;u<vertex_cnt;++u){
        ArcNode* p=adjacency_list[u].first_arc->next;
        while(p!=nullptr){
            dist[u][p->adj_vex]=p->weight;
            p=p->next;
        }
    }
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
