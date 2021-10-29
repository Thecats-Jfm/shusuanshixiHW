#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int NX = 1005;
int dp[NX][NX];
class node{
    public:
    int fail,next[4],sur;
}d[NX];
char s[NX];
int pos;
void insert(char *s){
    int u=0;
    int l = strlen(s);
    for(int i=0;i<l;i++){
        int t=s[i]-'0';
        u=d[u].next[t]?d[u].next[t]:d[u].next[t]=++pos;
    }
    d[u].sur=1;
}
void calc_fail(){
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i=0;i<4;i++){
            if(d[u].next[i]){
                int t=d[u].next[i];
                Q.push(t);
                if(u==0) continue;
                int f = d[u].fail;
                while(f!=0&&d[f].next[i]==0) f=d[f].fail;
                d[t].fail=d[f].next[i];
                d[t].sur|=d[d[t].fail].sur;
            }
            else{
                d[u].next[i]=d[d[u].fail].next[i];
            }
        }
    }
}
void change(char *s){
    int l = strlen(s);
    for(int i=0;i<l;i++){
        int t = 0;
        switch (s[i]){
            case 'T': ++t;
            case 'G': ++t;
            case 'C': ++t;
            case 'A': ;
        }
        s[i]=t+'0';
    }
}
int main()
{
    int n;
    int T=0,ans;
    while(scanf("%d",&n)!=EOF){
        if(n==0) break;
        pos=0;
        ans = NX;
        memset(d,0,sizeof(d));

        for(int i=0;i<n;i++){
            scanf("%s",s);
            change(s);
            insert(s);
        }
        calc_fail();
        scanf("%s",s);
        change(s);

        for(int i=0;i<NX;i++) for(int j=0;j<NX;j++) dp[i][j]=NX;
        dp[0][0]=0;
        int l = strlen(s);
        for(int i=0;i<l;i++){
            for(int u=0;u<=pos;u++){
                if(dp[i][u]==NX||d[u].sur==1) continue;
                for(int t=0;t<4;t++){
                    int to = d[u].next[t];
                    dp[i+1][to]=min(dp[i+1][to],dp[i][u]+(t!=s[i]-'0'));
                }
            }
        }
        for(int u=0;u<=pos;u++){
            if(dp[l][u]==NX|d[u].sur==1) continue;
            ans=min(ans,dp[l][u]);
        }
        if(ans==NX) ans=-1;
        printf("Case %d: %d\n",++T,ans);
    }
    return 0;
}