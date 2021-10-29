#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int NX = 100666;
int n,m;
int q[NX];
class node{
    public:
    node(){
        val = 0;
        memset(next,0,sizeof(next));
    }
    int fa,val,next[26],fail;
}d[NX];
void insert(char *s){
    static int pos=0;
    int l =strlen(s);
    int u = 0;
    for(int i=0;i<l;i++){
        int to = s[i]-'a';
        if(d[u].next[to]==0) d[u].next[to]=++pos;
        u = d[u].next[to];
    }
    d[u].val = 1;
}
void calc_fail(){
    int ql,qr;
    ql=qr=0; q[qr++]=0;
    while(ql<qr){
        int u = q[ql++];
        for(int i=0;i<26;i++){
            if(d[u].next[i]!=0){
                int t=d[u].next[i];
                q[qr++]=t;
                if(u==0) continue;
                int f = d[u].fail;
                while(f!=0&&d[f].next[i]==0) f=d[f].fail;
                d[t].fail=d[f].next[i];
                d[t].val|=d[d[t].fail].val;
            }
        }
    }
}
int Query(char *s){
    int u=0;
    int l = strlen(s);
    for(int i=0;i<l;i++){
        int t = s[i]-'a';
        while(u!=0&&d[u].next[t]==0) u = d[u].fail;
        u = d[u].next[t];
        if(d[u].val) return 1;
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    char s[1440];
    for(int i=0;i<n;i++){
        scanf("%s",s);
        insert(s);
    }
    calc_fail();
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s",s);
        if(Query(s)) puts("YES");
        else puts("NO");
    }
    return 0;
}