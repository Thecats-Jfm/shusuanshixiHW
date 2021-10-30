#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
const int NX = 1005,MX=6005;
stack<int> S;
int instk[NX],n,m,dfn[NX],low[NX],pos;
class Edge{
    public:
    int to;
    Edge* next;
    Edge(int to_,Edge* next_):to(to_),next(next_){}
};
Edge* head[NX];
bool dfs(int u){

    S.push(u);
    instk[u]=1;
    dfn[u]=low[u]=++pos;
    for(Edge* e=head[u];e!=NULL;e=e->next){
        int v=e->to;
        if(dfn[v]==0){
            if(dfs(v)==false) return false;
        }
        if(instk[v]){
            low[u]=min(low[u],low[v]);
        }
    }
    if(low[u]==dfn[u]){
        int cnt=0;
        while(S.top()!=u){
            int v=S.top();
            S.pop(); ++cnt; instk[v]=0;
        }
        S.pop(); ++cnt; instk[u]=0;
        if(cnt!=n) return false;
    }
    return true;
}
int main()
{
    int T ;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        int u,v;
        // 懒得做内存管理了
        pos=0;
        memset(head,0,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(instk,0,sizeof(instk));
        while(!S.empty()) S.pop();
        for(int i=0;i<m;i++){
            scanf("%d%d",&u,&v);
            head[u]=new Edge(v,head[u]);
        }
        if(dfs(1)) puts("Yes");
        else puts("No");
    }
    return 0;
}