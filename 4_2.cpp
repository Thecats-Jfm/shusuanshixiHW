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
class QWQ{
public:
    QWQ(int _l,int _r,int _f):l(_l),r(_r),f(_f){}
    int l,r,f;
};
vector<QWQ> s[20010],S[20010],d[20010],D[20010];
int n,val[NX],cur[NX],sum[NX],bias =10001;
void Build(int u,int l,int r){
    if(l==r){
        cur[u]=sum[u]=val[u]=0;
        return;
    }
    int m = (l+r)>>1;
    Build(L(u),l,m);
    Build(R(u),m+1,r);
    cur[u]=sum[u]=val[u]=0;
    return ;
}
int Query(int u,int l,int r);
void Updata(int u,int l,int r){
    int m = (l+r)>>1;
    cur[L(u)]+=cur[u];
    cur[R(u)]+=cur[u];
    sum[u]=Query(L(u),l,m)+Query(R(u),m+1,r);
    cur[u]=0;
}
int Query(int u,int l,int r){
    if(cur[u]>0) return r-l+1;
    if(cur[u]==0) return sum[u];
    if(l==r){
        sum[u]=sum[u]+cur[u];
        cur[u]=0;
        return sum[u]>0;
    }
    int m = (l+r)/2;
    Updata(u,l,r);
    cout<<"Q:"<<sum[u]<<endl;
    return sum[u];
}
void Change(int u,int l,int r,int L,int R,int f){
    int m = (l+r)/2;
    if(l==L&&r==R){
        cur[u]+=f;
    }
    else if(L<=m&&R>m){
        Change(L(u),l,m,L,m,f);
        Change(R(u),m+1,r,m+1,R,f);
    }
    else if(R<=m){
        Change(L(u),l,m,L,R,f);
    }
    else if(L>m){
        Change(R(u),m+1,r,L,R,f);
    }
    if(l!=r) sum[u]=Query(L(u),l,m)+Query(R(u),m+1,r);
    // cout<<"C:"<<sum[u]<<endl;
}
int main()
{
    scanf("%d",&n);
    int x,y,z,w;
    for(int i=1;i<=n;i++) {
        scanf("%d%d%d%d",&x,&y,&z,&w);
        x+=bias; y+=bias; z+=bias; w+=bias;
        QWQ  tmp1(y,w-1,1),tmp2(y,w-1,-1);
        s[x].push_back(tmp1);
        d[z].push_back(tmp2);
        QWQ tmp3(x,z-1,1),tmp4(x,z-1,-1);
        S[y].push_back(tmp3);
        D[w].push_back(tmp4);
    }
    n =2*bias;
    Build(0,1,n);
    int lst = 0,ans=0;
    for(int i=0;i<n;i++){
        if(s[i].empty()&&d[i].empty()) continue;
        for(auto j = s[i].begin();j!=s[i].end();j++){
            Change(0,1,n,(*j).l,(*j).r,(*j).f);
            ans+=abs(lst-Query(0,1,n));
            lst = Query(0,1,n);
        }
        for(auto j = d[i].begin();j!=d[i].end();j++){
            Change(0,1,n,(*j).l,(*j).r,(*j).f);
            ans+=abs(lst-Query(0,1,n));
            lst = Query(0,1,n);
        }
    }
    Build(0,1,n); lst =0;
    for(int i=0;i<n;i++){
            if(S[i].empty()&&D[i].empty()) continue;
            for(auto j = S[i].begin();j!=S[i].end();j++){
                Change(0,1,n,(*j).l,(*j).r,(*j).f);
                ans+=abs(lst-Query(0,1,n));
                lst = Query(0,1,n);
            }
            for(auto j = D[i].begin();j!=D[i].end();j++){
                Change(0,1,n,(*j).l,(*j).r,(*j).f);
                ans+=abs(lst-Query(0,1,n));
                lst = Query(0,1,n);
            }
        }

    printf("%d\n",ans);
    return 0;
}