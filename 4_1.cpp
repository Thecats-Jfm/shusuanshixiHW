#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<iostream>
#define L(u) u*2+1
#define R(u) u*2+2
using namespace std;
const int NX = 2000008;
vector<int> DATA[NX];
int sorted[NX],n,m,val[NX];
void Build(int u,int l,int r){
    if(l==r){
        DATA[u].clear();
        DATA[u].push_back(val[l]);
        return;
    }
    int m = (l+r)>>1;
    Build(L(u),l,m);
    Build(R(u),m+1,r);
    DATA[u].clear();
    int i=0,j=0,I=DATA[L(u)].size(),J=DATA[R(u)].size();
    while(i<I&&j<J){
        if(DATA[L(u)][i]<DATA[R(u)][j]){
            DATA[u].push_back(DATA[L(u)][i++]);
        }
        else
            DATA[u].push_back(DATA[R(u)][j++]);
    }
    while(i<I) DATA[u].push_back(DATA[L(u)][i++]);
    while(j<J) DATA[u].push_back(DATA[R(u)][j++]);
    return ;
}
int Query(int u,int l,int r,int L,int R,int val){
    int ret = 0;
    if( l==L&&r==R ){
        return upper_bound(DATA[u].begin(),DATA[u].end(),val)-DATA[u].begin();
    }
    int m = (l+r)/2;
    if(L<=m&&R>m){
        ret = Query(L(u),l,m,L,m,val);
        ret += Query(R(u),m+1,r,m+1,R,val);
    }
    else if(R<=m){
        ret = Query(L(u),l,m,L,R,val);
    }
    else if(L>m){
        ret = Query(R(u),m+1,r,L,R,val);
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",sorted+i),val[i]=sorted[i];
    sort(sorted+1,sorted+n+1);
    Build(0,1,n);
    for(int i=0;i<m;i++){
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int L=1,R=n;
        while(L<R){
            int m = (L+R)>>1;
            // cout<<L<<"---"<<R<<endl;
            // cout<< sorted[m]<<"      "<<Query(0,1,n,l,r,sorted[m])<<endl;
            if(Query(0,1,n,l,r,sorted[m])<k) L=m+1;
            else R = m;
        }
        printf("%d\n",sorted[L]);
    }
    return 0;
}