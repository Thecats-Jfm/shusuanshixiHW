#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
using namespace std;
const int NX = 30050;
class node{
    public:
    int next[2],sur,fail,instk;
}d[NX];
char s[NX];
void insert(char *s){
    static int pos=0;
    int u = 0,l = strlen(s);
    for(int i=0;i<l;i++){
        int t = s[i]-'0';
        if(d[u].next[t]==0){
            d[u].next[t]=++pos;
        }
        u = d[u].next[t];
    }
    d[u].sur = 1;
}
void get_fail(){
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()){
        int u=Q.front(); Q.pop();
        for(int i=0;i<2;i++){
            if(d[u].next[i]!=0){
                int t = d[u].next[i];
                Q.push(t);
                if(u==0) continue;
                int f = d[u].fail;
                while(f!=0&&d[f].next[i]==0) f = d[f].fail;
                d[t].fail = d[f].next[i];
                d[t].sur|=d[d[t].fail].sur;
            }
            else{
                d[u].next[i]=d[d[u].fail].next[i];
            }
        }
    }
}
bool DFS(int u){
    for(int i=0;i<2;i++){
        int t=d[u].next[i];
        if(d[t].sur==1) continue;
        else if(d[t].instk==1) {
            return true;
        }
        else {
            // cout<<"GOTO: "<<t<<" "<<"by val:"<<i<<endl;
            d[t].instk=1;
            if(DFS(t)) return true;
            // cout<<"Ret from:"<<t<<endl;
        }
    }
    d[u].instk = 0;
    return false;
}
bool check(){
    d[0].instk = 1;
    return DFS(0);
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s",s);
        insert(s);
    }
    get_fail();
    if(check()) puts("TAK");
    else puts("NIE");
    return 0;
}