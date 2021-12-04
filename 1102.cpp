#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
struct Point{
    int x,y;
}p[20],f;
int n;
double calc(Point const &a,Point const &b,Point const &c){
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
bool checkin(Point const &f,Point const &a,Point const &b,Point const &c){
    double t1,t2;
    t1=calc(a,f,b); t2=calc(a,f,c);
    // cout<<t1<<" "<<t2<<" ~" <<endl;
    if(t1*t2>0) return false;
    t1=calc(b,f,a); t2=calc(b,f,c);
    // cout<<t1<<" "<<t2<<" ~" <<endl;
    if(t1*t2>0) return false;
    t1=calc(c,f,a); t2=calc(c,f,b);
    // cout<<t1<<" "<<t2<<" ~" <<endl;
    if(t1*t2>0) return false;
    return true;
}
int main()
{
    while(1){
        scanf("%d",&n);
        double ans=0;
        int rem[3];
        if(n==0) break;
        for(int i=0;i<n;i++){
            char c=getchar();
            while(c<'A'||c>'Z') c=getchar();
            scanf("%d%d",&p[i].x,&p[i].y);
        }
        for(int i=0;i<n;i++){
            f=p[i];
            for(int j=i+1;j<n;j++){
                for(int k=j+1;k<n;k++){
                    double tans=fabs(calc(f,p[j],p[k]))/2;
                    // printf("%d %d %d %lf/%lf\n",i,j,k,tans,ans);
                    if(tans<ans) continue;
                    int flag=1;
                    for(int l=0;l<n&&flag;l++) if(l!=i&&l!=j&&l!=k){
                        if(checkin(p[l],p[i],p[j],p[k])) {
                            flag=0;
                            // printf("NOT OK IN %d\n",l);
                            }
                    }
                    if(flag){
                        rem[0]=i; rem[1]=j; rem[2]=k;
                        ans=tans;
                        // printf("OK\n");
                    }
                }
            }
        }
        printf("%c%c%c\n",'A'+rem[0],'A'+rem[1],'A'+rem[2]);
    }
    return 0;
}