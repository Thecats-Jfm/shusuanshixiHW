#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#define L(u) u*2+1
#define R(u) u*2+2
using namespace std;
const int NX = 100005;
int color[NX],n,cur[NX],posl[NX],posr[NX],alive[NX];
map<int,int> ys;
set<int> pos;
void Build(int u,int l,int r){
    if(l==r){
        cur[u]=0;
        color[u]=0; return;
    }
    int m = (l+r)/2;
    Build(u*2+1,l,m);
    Build(u*2+2,m+1,r);
    cur[u]=0;
    return;
}

int Query(int u,int l,int r,int q){
    if(l==r){
        if(cur[u]) color[u]=cur[u],cur[u]=0;
        return color[u];
    }
    int m = (l+r)/2;
    if(cur[u]){
        cur[L(u)]=cur[u];
        cur[R(u)]=cur[u];
        cur[u]=0;
    }
    if(q>m) return Query(R(u),m+1,r,q);
    else return Query(L(u),l,m,q);
}
void Change(int u,int l,int r,int cl,int cr,int c){
    if(l==r){
        if(cur[u]) color[u]=cur[u],cur[u]=0;
        color[u]=c;
        return ;
    }
    if(cl==l&&cr==r){
        cur[u]=c;
        return ;
    }
    if(cur[u]){
        cur[L(u)]=cur[u];
        cur[R(u)]=cur[u];
        cur[u]=0;
    }
    int m = (l+r)/2;
    if(cr<=m){
        Change(L(u),l,m,cl,cr,c);
    }
    else if(cl>m){
        Change(R(u),m+1,r,cl,cr,c);
    }
    else{
        Change(L(u),l,m,cl,m,c);
        Change(R(u),m+1,r,m+1,cr,c);
    }
    return;
}
int main()
{
    int T;
    scanf("%d",&T);

    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            alive[i]=0;
            scanf("%d%d",posl+i,posr+i);
            pos.insert(posl[i]);
            pos.insert(posr[i]);
        }
        // sort(pos.begin(),pos.end());
        int now_pos=0;
        for(auto i=pos.begin();i!=pos.end();i++){
            ys[*i]=++now_pos;
        }
        pos.clear();
        Build(0,1,now_pos);
        for(int i=1;i<=n;i++){
            Change(0,1,now_pos,ys[posl[i]],ys[posr[i]],i);
        }
        for(int i=1;i<=now_pos;i++){
            alive[Query(0,1,now_pos,i)]=1;
            // printf("%d %d\n",i,Query(0,1,now_pos,i));
        }
        int ans=0;
        for(int i=1;i<=n;i++) ans+=alive[i];
        printf("%d\n",ans);
    }

    return 0;
}