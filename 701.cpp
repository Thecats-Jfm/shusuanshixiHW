#include<iostream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;
const int NX = 105;
#define For(i_,step,n) for(int i=i_;i<=n;i+=step)
double money[NX];
struct Edge{
    double r,c;
    int to,next;
}e[NX*2];
int n,m,s,change,head[NX],pos;
void addE(int u,int v,double r,double c){
    e[pos].to=v; e[pos].r=r; e[pos].c=c; e[pos].next=head[u]; head[u]=pos++;
}
int main()
{
    double y;
    scanf("%d%d%d%lf",&n,&m,&s,&y);
    For(1,1,n){
        money[i]=0;
        head[i]=-1;
    }
    For(1,1,m){
        int u,v;
        double c1,r1,c2,r2;
        scanf("%d%d%lf%lf%lf%lf",&u,&v,&r1,&c1,&r2,&c2);
        addE(u,v,r1,c1);
        addE(v,u,r2,c2);
    }
    money[s]=y;
    For(1,1,n*8){
        change = 0;
        for(int j=1;j<=n;j++) if(money[j]!=0){
            for(int ei=head[j];ei!=-1;ei=e[ei].next){
                if(e[ei].c>=money[j]) continue;
                if(e[ei].r*(money[j]-e[ei].c)>money[e[ei].to]){
                    money[e[ei].to] = e[ei].r*(money[j]-e[ei].c);
                    change = 1;
                }
            }
        }
    }
    if(change==1) puts("YES");
    else puts("NO");
    return 0;
}