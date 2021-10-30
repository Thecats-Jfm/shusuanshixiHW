#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
const int NX = 1005,MX=2001001;
class Edge{
    public:
    int to,next,w;
}e[MX];
int pos,n,m,ans,head[NX],instk[NX],dfn[NX],low[NX];
stack<int> S;
void addE(int u,int v,int w){
    e[pos].to=v; e[pos].w=w; e[pos].next=head[u]; head[u]=pos++;
}
void dfs(int u,int id){
    S.push(u); instk[u]=1; dfn[u]=low[u]=++pos;
    for(int i = head[u];~i;i=e[i].next){
        if(i==(id^1)) continue;
        int to = e[i].to;
        if(dfn[to]==0){
            dfs(to,i);
            // if(dfn[u]<low[to]) ans = min(ans,e[i].w);
        }
        if(instk[to]==1) low[u]=min(low[u],low[to]);
    }
    if(low[u]==dfn[u]){
        if(id!=-1) ans=min(ans,e[id].w);
        while(S.top()!=u){
            instk[S.top()]=0; S.pop();
        }
        instk[S.top()]=0; S.pop();
    }
}
int main()
{
    while(true){
        scanf("%d%d",&n,&m);
        if(n==0&&m==0) break;
        pos=0; ans=MX; memset(head,-1,sizeof(head));
        while(!S.empty()) S.pop();
        memset(dfn,0,sizeof(dfn));
        for(int i=0;i<m;i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            addE(u,v,w);
            addE(v,u,w);
        }
        pos=0;
        dfs(1,-1);
        for(int i=1;i<=n;i++) if(dfn[i]==0) ans=-2;
        if(ans==MX) puts("-1");
        else if(ans==-2) puts("0");
        else if(ans==0) puts("1");
        else printf("%d\n",ans);
    }
    return 0;
}