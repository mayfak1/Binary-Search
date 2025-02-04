#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

int lover_bound(int *,int ,int );
enum h{
    N=1<<23
};
int main(){
    struct timeval start,end;

    int x=N;
    int *v=malloc(sizeof(*v) *N);
    for(int i=0;i<N;i++){
        v[i]=i+1;
    }
    gettimeofday(&start,NULL);
    lover_bound(v,N,x);
    gettimeofday(&end,NULL);
    


    printf("size:%d time:%d\n",N,end.tv_usec-start.tv_usec);


    

    free(v);
    return 0;
}
int lover_bound(int *t,int n,int x){
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (t[m] >= x)
            r = m;
        else
            l = m + 1;
    }
    return t[l];
}