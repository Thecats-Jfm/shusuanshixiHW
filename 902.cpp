#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int NX = 605,MX = 40005,INF=~0U>>2,bias=250,S=602,T=603;
int dep[NX],head[NX],n,m,cur,q[NX],ql,qr,ans;
bool inq[NX];
struct Edge{
    int to,next,r;
}e[MX];
bool BFS(){
    for(int i=0;i<NX;i++) dep[i]=-1;
    ql=qr=0;
    dep[S]=0; q[qr++]=S;
    while(ql!=qr){
        int u=q[ql++];
        for(int i=head[u];~i;i=e[i].next){
            int v=e[i].to;
            if(e[i].r&&dep[v]==-1){
                dep[v]=dep[u]+1;
                q[qr++]=v;
            }
        }
    }
    return dep[T]!=-1;
}
int DFS(int u,int f){
    if(u==T) return f;
    // if(dep[u]>=dep[T]) return 0;
    int now = f;
    for(int i=head[u];~i&&now;i=e[i].next){
        int v=e[i].to;
        if(e[i].r&&dep[v]==dep[u]+1){
            int re=DFS(v,min(e[i].r,now));
            e[i].r-=re;
            e[i^1].r+=re;
            now-=re;
        }
    }
    return f-now;
}
int Dinic(){
    ans=0;
    while(BFS()){
        ans+=DFS(S,INF);
    }
    return ans;
}
void addE(int u,int v,int r){
    e[cur].to=v; e[cur].r=r; e[cur].next=head[u]; head[u]=cur++;
    e[cur].to=u; e[cur].r=0; e[cur].next=head[v]; head[v]=cur++;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF){
    cur=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        int s,u;
        scanf("%d",&s);
        for(int j=0;j<s;j++){
            scanf("%d",&u);
            addE(i,u+bias,1);
        }
        addE(S,i,1);
    }
    for(int i=1;i<=m;i++){
        addE(i+bias,T,1);
    }
    printf("%d\n",Dinic());
    }
    return 0;
}