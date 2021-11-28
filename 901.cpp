#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int NX = 1005,MX = 40005,INF=~0U>>2;
int dis[NX],head[NX],n,m,S=1002,T=1003,cur,q[NX],ql,qr,cost,pre[NX],ans;
bool inq[NX];
struct Edge{
    int to,next,w,r;
}e[MX];
bool SPFA(){
    for(int i=1;i<NX;i++) dis[i]=INF;
    dis[S]=0; q[qr++]=S; inq[S]=1;
    while(ql!=qr){
        int u=q[ql++]; inq[u]=0; ql%=NX;
        for(int i=head[u];~i;i=e[i].next){
            int v=e[i].to;
            if(e[i].r&&dis[u]+e[i].w<dis[v]){
                dis[v]=dis[u]+e[i].w;
                pre[v]=i;
                if(!inq[v]) inq[v]=1,q[qr++]=v,qr%=NX;
            }
        }
    }
    return dis[T]!=INF;
}
int augment(){
    int f=INF;
    for(int u=T;u!=S;u=e[1^pre[u]].to) f=min(f,e[pre[u]].r);
    for(int u=T;u!=S;u=e[1^pre[u]].to){
        e[pre[u]].r-=f; e[1^pre[u]].r+=f;
    }
    cost+=f*dis[T];
    // cout<<f<<endl;
    return f;
}
void addE(int u,int v,int r,int w){
    e[cur].to=v; e[cur].r=r; e[cur].w=w; e[cur].next=head[u]; head[u]=cur++;
    e[cur].to=u; e[cur].r=0; e[cur].w=-w; e[cur].next=head[v]; head[v]=cur++;
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addE(u,v,1,w);
        addE(v,u,1,w);
    }
    addE(S,1,2,0);
    addE(n,T,2,0);
    while(SPFA()) ans+=augment();
    printf("%d\n",cost);
    return 0;
}