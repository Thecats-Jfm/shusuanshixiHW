#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int NX = 1005,EX = 5005,MAX = ~0u>>2;
int dis[NX],head[NX],pos,vis[NX];
class Qdata{
    public:
    int id,dis;
    Qdata(int _id,int _dis):id(_id),dis(_dis){}
    bool operator < (const Qdata a)const{
        return dis>a.dis;
    }
};
class Edge{
    public:
    int to,next,w;
}e[EX];
void addTE(int u,int v,int w){
    e[pos].to=v; e[pos].w=w; e[pos].next=head[u]; head[u]=pos++;
    e[pos].to=u; e[pos].w=w; e[pos].next=head[v]; head[v]=pos++;
}
priority_queue<Qdata> Q;
int main()
{
    int n,m;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++) dis[i]=MAX;
    dis[1]=0;
    int u,v,w;
    memset(head,-1,sizeof(head));
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w);
        addTE(u,v,w);
    }
    Q.push(Qdata(1,0));
    for(int i=1;i<=n;i++){
        int id=Q.top().id;
        Q.pop();
        if(vis[id]) continue;
        if(id==n) break;
        vis[id]=1;
        for(int ei=head[id];ei!=-1;ei=e[ei].next){
            int to = e[ei].to;
            if(dis[to]>dis[id]+e[ei].w){
                dis[to]=dis[id]+e[ei].w;
                Q.push(Qdata(to,dis[to]));
            }
        }

    }
    printf("%d\n",dis[n]);
    return 0;
}