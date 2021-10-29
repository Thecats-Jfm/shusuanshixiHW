#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
const int NX = 1000006;
int border[NX];
char s[NX],m[NX];
int main()
{
    scanf("%s%s",s+1,m+1);
    border[1]=0;
    int l1 = strlen(s+1),l2=strlen(m+1);
    for(int i=2;i<=l2;i++){
        int j = border[i-1];
        while(j!=0&&m[j+1]!=m[i]) j = border[j];
        if(m[j+1]==m[i]) border[i]=j+1;
        else border[i]=0;
    }
    int j = 0;
    for(int i=1;i<=l1;i++){
        while(j!=0&&m[j+1]!=s[i]) j = border[j];
        if(m[j+1]==s[i]) j++;
        if(j==l2){
            printf("%d\n",i-j+1);
        }
    }
    for(int i=1;i<=l2;i++) printf("%d ",border[i]);
    return 0;
}