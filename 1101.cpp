#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct line{
    double a,b,c;
}l1,l2;
const double eps=1e-8;
bool equal(double a,double b) { return fabs(a-b)<eps; }
void mkline(double x1,double y1,double x2,double y2,line& l){
    if(x1==x2){
        l.a=1;
        l.b=0;
        l.c=-x1;
    }
    else {
        double k=(y2-y1)/(x2-x1),b=y1-k*x1;
        l.a=k;
        l.b=-1;
        l.c=b;
    }
}
int main()
{
    puts("INTERSECTING LINES OUTPUT");
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        double x1,x2,x3,x4,y1,y2,y3,y4;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        mkline(x1,y1,x2,y2,l1);
        mkline(x3,y3,x4,y4,l2);
        if(equal(l1.a,l2.a)&&equal(l1.b,l2.b)&&equal(l1.c,l2.c)){
            puts("LINE");
        }
        else if (equal(l1.a,l2.a)&&equal(l1.b,l2.b)){
            puts("NONE");
        }
        else{
            if(equal(l1.a,0.0)) swap(l1,l2);
            double p = l2.a/l1.a;
            l2.a=l1.a*p-l2.a;
            l2.b=l1.b*p-l2.b;
            l2.c=l1.c*p-l2.c;
            double y=-l2.c/l2.b,x=(-l1.b*y-l1.c)/l1.a;
            printf("POINT %.2lf %.2lf\n",x,y);
        }
    }
    puts("END OF OUTPUT");
    return 0;
}