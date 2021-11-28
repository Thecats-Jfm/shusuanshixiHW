#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int NX = 550*2,MX=655360,INF=66666666,bias=50,Tt=1005,St=1004;
int p,n,m;
int Q[NX],D[NX][15],S[NX][15],head[NX],pos,dep[NX];
struct Edge{
    int to,next,w;
}e[MX];
void addTE(int u,int v,int w){
    // cout<<u<<"-"<<v<<"-"<<w<<endl;
    e[pos].to=v; e[pos].w=w; e[pos].next = head[u]; head[u]=pos++;
    e[pos].to=u; e[pos].w=0; e[pos].next = head[v]; head[v]=pos++;
}
bool BFS(){
    int Qu[NX],vis[NX],ql,qr;
    memset(vis,0,sizeof(vis)); ql=qr=0;
    memset(dep,0,sizeof(dep));
    Q[qr++]=St;
    vis[St]=1;
    while(ql<qr){
        int u=Q[ql++];
        for(int i=head[u];~i;i=e[i].next)if(e[i].w){
            int v=e[i].to;
            if(vis[v]) continue;
            dep[v]=dep[u]+1;
            vis[v]=1;
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
            arg=DFS(v,min(e[i].w,now));
            e[i].w-=arg;
            now-=arg;
            e[i^1].w+=arg;
        }
    }
    return pre-now;
}
int main()
{
    scanf("%d%d",&p,&n);
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        scanf("%d",Q+i);
        addTE(i,i+bias,Q[i]);
        for(int j=1;j<=p;j++) scanf("%d",&S[i][j]);
        for(int j=1;j<=p;j++) scanf("%d",&D[i][j]);
    }
    for(int i=1;i<=p;i++) S[Tt][i]=1;
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n+1;j++)if(i!=j){
            int flag=1;
            for(int k=1;k<=p&&flag;k++){
                if((D[i][k]==1&&S[j][k]==0)||(D[i][k]==0&&S[j][k]==1)) flag=0;
            }
            if(flag){
                addTE(i+bias,j,INF);
            }
        }
    }
    for(int i=1;i<=n;i++){
        int flag=1;
        for(int k=1;k<=p&&flag;k++){
            if(S[i][k]==1) flag=0;
        }
        if(flag) addTE(St,i,INF);
    }
    for(int i=1;i<=n;i++){
        int flag=1;
        for(int k=1;k<=p&&flag;k++){
            if(D[i][k]==0) flag=0;
        }
        if(flag) addTE(i+bias,Tt,INF);
    }

    int ans=0;
    while(BFS()){
        ans+=DFS(St,INF);
        // cout<<ans;
    }
    // cout<<ans<<endl;
    int cnt=0;
    for(int i=1+bias;i<=n+bias;i++){
        for(int j=head[i];~j;j=e[j].next)if(   e[j^1].w!=0 &&   ((e[j].to!=i-bias)&&e[j].to!=Tt) ){
            ++cnt;
        }
    }
    printf("%d %d\n",ans,cnt);
    for(int i=1+bias;i<=n+bias;i++){
        for(int j=head[i];~j;j=e[j].next)if(((e[j].to!=i-bias)&&e[j].to!=Tt)&&e[j^1].w!=0      ){
            printf("%d %d %d\n",i-bias,e[j].to,e[j^1].w);
        }
    }
    return 0;
}