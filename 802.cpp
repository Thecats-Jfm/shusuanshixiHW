#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int NX = 255,St=252,Tt=253,MX=606666,INF=974321;
int head[NX],dis[NX][NX],pos,M,K,C,dep[NX];
struct edge{
    int to,next,w;
}e[MX];
void ATE(int u,int v,int w){
    e[pos].to=v; e[pos].w=w; e[pos].next=head[u]; head[u]=pos++;
    e[pos].to=u; e[pos].w=0; e[pos].next=head[v]; head[v]=pos++;
}
int Q[NX],ql,qr,vis[NX];
bool BFS(){

    ql=qr=0; Q[qr++]=St;
    memset(vis,0,sizeof(vis)); dep[St]=0; dep[Tt]=0;
 vis[St]=1;

    while(ql<qr){
        int u=Q[ql++];
        for(int i=head[u];~i;i=e[i].next)if(e[i].w){
            int v=e[i].to;
            if(vis[v])continue;
            vis[v]=1;
            dep[v]=dep[u]+1;
            Q[qr++]=v;
        }
    }
    return dep[Tt]!=0;
}
int DFS(int u,int now){
    if(u==Tt) return now;
    int arg,pre=now;
    for(int i=head[u];~i&&now;i=e[i].next)if(e[i].w){
        int v=e[i].to;
        if(dep[v]==dep[u]+1){
            arg=DFS(v,min(now,e[i].w));
            e[i].w-=arg;
            e[i^1].w+=arg;
            now-=arg;
        }
    }
    return pre-now;
}
bool check(int m){
    pos=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=K;i++) ATE(i,Tt,M);
    for(int i=K+1;i<=K+C;i++) ATE(St,i,1);
    for(int i=K+1;i<=K+C;i++) for(int j=1;j<=K;j++){
        if(i!=j&&dis[i][j]<=m) ATE(i,j,INF);
    }
    int ans=0;
    while(BFS()){
        ans+=DFS(St,C);
    }
    // cout<<ans<<endl;
    return ans==C;
}
int main()
{
    scanf("%d%d%d",&K,&C,&M);
    for(int i=1;i<=K+C;i++){
        for(int j=1;j<=K+C;j++){
            int u;
            scanf("%d",&u);
            if(i==j) dis[i][j]=0;
            else if(u==0) dis[i][j]=INF;
            else dis[i][j]=u;
        }
    }
    int R=0;
    for(int k=1;k<=K+C;k++){
        for(int i=1;i<=K+C;i++){
            for(int j=1;j<=K+C;j++){
                dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
            }
        }
    }
    for(int i=1;i<=K+C;i++) {for(int j=1;j<=K+C;j++) R=max(R,dis[i][j]);}
    int l=0,r=INF;
    while(l<r){
        int m=(l+r)>>1;
        if(check(m)) r=m;
        else l=m+1;
    }
    printf("%d\n",l);
    return 0;
}