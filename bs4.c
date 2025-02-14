#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int lover_bound(int *, int, int);
int lover_bound_branchless(int *, int , int );
int lover_bound_prefetch(int *, int , int );
double search_median(double *,int);
double search_avg(double *, int , int );
void choose_alg(int ,int* , int , int );

int lover_bound_branchless(int *t, int n, int x) {
    int *base = t, len = n;
    while (len > 1) {
        int half = len / 2;
        base += (base[half - 1] < x) * half; 
        len -= half;
    }
    return *base;
}
int lover_bound_prefetch(int *t, int n, int x) {
    int k = 1;
    while (k <= n) {
        __builtin_prefetch(t + k * 16);
        k = 2 * k + (t[k] < x);
    }
    k >>= __builtin_ffs(~k);
    return t[k];
}
int compare(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    return (diff > 0) - (diff < 0); 
}


double wtime()
{
    struct timespec tsp;
    clock_gettime(CLOCK_REALTIME,&tsp);
    return (double)tsp.tv_sec + tsp.tv_nsec/1E9 ;
}

int main(int argc, char **argv)
{
    double res=0.;
    double tusec=0.;
    int N = (argc > 1) ? atoi(argv[1]) : 1<<24 ;
    int choice = (argc>2)?atoi(argv[2]):1;
    int x = N;
    int nruns = 100;
    double *times = malloc(sizeof(*times) * nruns);
    int *v = malloc(sizeof(*v) * N);
    for (int i = 0; i < N; i++) {
        v[i] = i + 1;
    }
    for(int i=0;i<nruns;i++){
        times[i] = wtime();
        //printf("%f - ",times[i]);
        choose_alg(choice,v, N,  x);
        double t=wtime();
       // printf("%f = ",times[i]);
        times[i] =t-times[i];
        res+=times[i];
     //   printf("%f!\n",times[i]);
    }
    tusec =search_median(times,nruns) ;
    res/=nruns;
    double tavg =search_avg(times,nruns,3) ;
     printf("# N         t_med [usec]   t_avg [usec]   res[usec]\n");
     printf("%-8d    %.3f  \t %.3f\t%3.f\n", N, tusec, tavg,res);

    free(v);
    free(times);
    return 0;
}

int lover_bound(int *t, int n, int x)
{
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

double search_median(double *times,int nruns){
    qsort(times,nruns,sizeof(times[0]),compare);
  
    // for(int i=0;i<nruns;i++){
    //     printf("%lf\n",times[i]/ 1E3);
    // }

    return times[nruns / 2] / 1E3;
}

double search_avg(double *times, int nruns, int k){
    double t = 0;
    int n = 0;
    for (int i = k - 1; i < nruns - k; i++) {
        t += times[i];
        n++;
    }
    return t / n;
}


void choose_alg(int choice,int *t, int n, int x){
    switch (choice)
    {
    case 2:
        lover_bound_branchless(t, n,  x);
        break;
    case 3:
        lover_bound_prefetch(t, n,  x);
        break;
    default:
        lover_bound(t, n,  x);
        break;
    }
}