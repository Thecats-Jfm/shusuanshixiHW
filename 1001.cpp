#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
const int NX = 500005,MX=1000005;
int fa[20][NX],mx[20][NX],n,head[NX],pos,dep[NX];
struct  Edge{
    int to,next,w;
}e[MX];
void addE(int u,int v,int w){
    e[pos].to=v; e[pos].next=head[u]; e[pos].w=w; head[u]=pos++;
    e[pos].to=u; e[pos].next=head[v]; e[pos].w=w; head[v]=pos++;
}
void DFS(int u){
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(dep[v]==0){
            dep[v]=dep[u]+1;
            fa[0][v]=u;
            mx[0][v]=e[i].w;
            DFS(v);
        }
    }
}
int Query(int a,int b){
    int ans=0;
    if(dep[a]<dep[b]) swap(a,b);
    int de=dep[a]-dep[b];
    // for(int i=0;i<de;i++){
    //     ans=max(ans,mx[0][a]);
    //     a=fa[0][a];
    // }
    // while(a!=b){
    //     ans=max(mx[0][a],ans);
    //     ans=max(mx[0][b],ans);
    //     a=fa[0][a];
    //     b=fa[0][b];
    // }
    for(int i=18;i>=0;i--){
        if(de&(1<<i)){
            ans=max(ans,mx[i][a]);
            a=fa[i][a];
        }
    }
    for(int i=18;i>=0;i--){
        if(fa[i][a]!=fa[i][b]){
            ans=max(mx[i][a],ans);
            ans=max(mx[i][b],ans);
            a=fa[i][a];
            b=fa[i][b];
        }
    }
    if(a!=b) ans=max(ans,mx[0][a]),ans=max(ans,mx[0][b]);
    return ans;
}
int main()
{
    scanf("%d",&n);
    memset(head,-1,sizeof(head));
    for(int i=1;i<n;i++){
        int s,e,w;
        scanf("%d%d%d",&s,&e,&w);
        addE(s,e,w);
    }
    dep[1]=1;
    DFS(1);
    for(int i=1;i<=18;i++){
        for(int u=1;u<=n;u++){
            fa[i][u]=fa[i-1][fa[i-1][u]];
            mx[i][u]=max(mx[i-1][u],mx[i-1][fa[i-1][u]]);
        }
    }
    int q;
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",Query(a,b));
    }
    return 0;
}