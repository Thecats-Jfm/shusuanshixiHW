#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int NX = 500006;
int n,m,pos;
int q[NX];
bool sa[268];
class node{
    public:
    node(){    }
    void cl(){
        fail=sur=0;
        memset(next,0,sizeof(next));
        memset(val,0,sizeof(val));
    }
    int val[4],next[26],fail,sur;
}d[NX];
void insert(char *s,int key){
    int l =strlen(s);
    int u = 0;
    for(int i=0;i<l;i++){
        int to = s[i]-'A';
        if(d[u].next[to]==0){
            // d[pos].cl();
            d[u].next[to]=++pos;

        }
        u = d[u].next[to];
    }

    d[u].sur = 1;
    if(d[u].val[0]==0) d[u].val[0] = key;
    else d[u].val[1]=key;

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
                d[t].sur|=d[d[t].fail].sur;
                // d[t].sur = 1;
            }
        }
    }
}
int query(char *s){
    int u=0;
    int l = strlen(s);
    for(int i=0;i<l;i++){
        int t = s[i]-'A';
        while(u!=0&&d[u].next[t]==0) u = d[u].fail;
        u = d[u].next[t];
        if(d[u].sur){
            int v=u;
            while(v!=0&&d[v].sur){
                sa[d[v].val[0]]=true;
                sa[d[v].val[1]]=true;
                d[v].sur = 0;
                v=d[v].fail;
            }
        }
    }
    return 0;
}
char ss[5206000];
void decompress(char *s){
    int l=strlen(s);
    int cur = 0;
    for(int i=0;i<l;i++){
        if(s[i]>='A'&&s[i]<='Z') ss[cur++] = s[i];
        else if(s[i]=='['){
            int f = 0;
            i++;
            while(s[i]>='0'&&s[i]<='9'){
                f=f*10+s[i]-'0';
                i++;
            }
            char c = s[i];
            i++;
            for(int j=0;j<f;j++) ss[cur++]=c;
        }
    }
    ss[cur++]='\0';
    for(int i=0;i<cur;i++) s[i]=ss[i];

}
void strrev_(char *s){
    int l =strlen(s);
    for(int i=0;i<l;i++) ss[i]=s[l-i-1];
    for(int i=0;i<l;i++) s[i]=ss[i];
    s[l]='\0';
}
char s[5260000];
char q1[255][1005];
int main()
{
    scanf("%d",&m);
    for(int T=0;T<m;T++){
        while(pos>=0) d[pos--].cl();
        pos+=1;
        d[0].cl();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",q1[i]);
            insert(q1[i],i);
            sa[i]=false;
        }
        for(int i=1;i<=n;i++){
            strrev_(q1[i]);
            insert(q1[i],i);
        }
        calc_fail();
        scanf("%s",s);
        decompress(s);
        // cout<<"dec:  "<<s<<endl;
        int ans=0;
        // cout<<s<<endl;
        query(s);
        for(int i=1;i<=n;i++) ans+=sa[i];
        printf("%d\n",ans);
    }
    return 0;
}