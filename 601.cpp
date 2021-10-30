#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
const int NX = 10005,MX=50005;
stack<int> S;
int cnt[NX],color,low[NX],dfn[NX],reach[NX],timeStamp,col[NX],cd[NX],IN[NX];
int n,m;
class Edge{
    public:
    int to;
    Edge* next;
    Edge(int u,Edge* ori){
        to=u; next=ori;
    }
};
Edge* head[NX];
void dfs(int u){
    dfn[u]=++timeStamp;
    low[u]=dfn[u];
    IN[u]=1;
    // cout<<"In point:"<<u<<"   "<<"with Dfn:  "<<dfn[u]<<endl;
    S.push(u);
    for(Edge *e =head[u];e!=NULL;e=e->next){
        int v=e->to;
        // cout<<"visit point:   "<<v<<endl;
        if(dfn[v]==0){
            dfs(v);
        }
        if(IN[v]==1) low[u]=min(low[u],low[v]);
    }
    if(low[u]==dfn[u]){
        int t=0;
        while(S.top()!=u){
            int v=S.top();
            S.pop();
            ++t;
            col[v]=color;
            IN[v]=0;
        }
        ++t; S.pop();
        col[u]=color;
        cnt[color]=t;
        IN[u]=0;
        ++color;
    }
    // cout<<"Exit point:  "<<u<<" with low:"<<low[u]<<endl;
}
int main()
{
    scanf("%d%d",&n,&m);
    int u,v;
    for(int i=0;i<=n;i++) head[i]=NULL;
    for(int i=1;i<=n;i++) head[0]=new Edge(i,head[0]);
    for(int i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        head[u]=new Edge(v,head[u]);
    }
    color=1;
    dfs(0);
    for(int i=0;i<=n;i++){
        for(Edge* e=head[i];e!=NULL;e=e->next){
            int a=col[i],b=col[e->to];
            if(a==b||reach[b]==a) continue;
            ++cd[a];
        }
    }
    u=-1;
    for(int i=1;i<color;i++){
        if(cd[i]!=0) continue;
        if(u==-1) u=i;
        else u=-2;
    }
    if(u==-2) puts("0");
    else printf("%d\n",cnt[u]);
    return 0;
}