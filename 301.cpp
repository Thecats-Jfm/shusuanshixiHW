#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#define L(u) u*2+1
#define R(u) u*2+2
using namespace std;
const int NX = 200005;
int sum[NX],da[NX],n,ans[NX];
void Build(int u,int l,int r){
    if(l==r){
        sum[u]=1; return;
    }
    int m = (l+r)/2;
    Build(u*2+1,l,m);
    Build(u*2+2,m+1,r);
    sum[u]=sum[u*2+1]+sum[R(u)];
    return;
}
int Query(int u,int l,int r,int num){
    int ret;
    if(l==r){
        sum[u]=0;
        return l;
    }
    int m = (l+r)/2;
    if(num>sum[L(u)]) ret=Query(R(u),m+1,r,num-sum[L(u)]);
    else ret=Query(L(u),l,m,num);
    sum[u]=sum[L(u)]+sum[R(u)];
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d",da+i);
    }
    Build(0,1,n);
    for(int i=n-1;i>=0;i--){
        ans[i]=Query(0,1,n,da[i]+1);
    }
    for(int i=0;i<n;i++) printf("%d\n",ans[i]);
    return 0;
}