// #include<stdio.h>
// #include<cuda.h>

// __global__ void arrAdd(int *x,int *y,int *z)
// {
//     int id = blockIdx.x;
//     z[id] = x[id] + y[id];
// }

// int main()
// {
//     int a[6],b[6],c[6];
//     int *d,*e,*f,i;
//     for(i=0;i<6;i++)
//     {
//         scanf("%d",&a[i]);
//     }
//     for(i=0;i<6;i++)
//     {
//         scanf("%d",&b[i]);
//     }
//     cudaMalloc((void **)&d,6*sizeof(int));
//     cudaMalloc((void **)&e,6*sizeof(int));
//     cudaMalloc((void **)&f,6*sizeof(int));
//     cudaMemcpy(d,a,6*sizeof(int),cudaMemcpyHostToDevice);
//     cudaMemcpy(e,b,6*sizeof(int),cudaMemcpyHostToDevice);
//     arrAdd<<<6,1>>(d,e,f);
//     cudaMemcpy(c,f,6*sizeof(int),cudaMemcpyDeviceToHost);
//     for(i=0;i<6;i++)
//     {
//         printf("%d",c[i]);
//     }
//     cudaFree(d);
//     cudaFree(e);
//     cudaFree(f);
//     return 0;
// }


#include<stdio.h>
#include<cuda.h>
#include<ctime>

__global__ void arrAdd(int *x,int *y,int *z)
{
    int id = blockIdx.x;
    z[id] = x[id] + y[id];
}

int main()
{
    int a[6],b[6],c[6];
    int *d,*e,*f;
    int size = 6*sizeof(int);
    cudaMalloc((void **)&d,size);
    cudaMalloc((void **)&e,size);
    cudaMalloc((void **)&f,size);
    cudaMemcpy(d,a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(e,b,size,cudaMemcpyHostToDevice);
    cudaEvent_t start,stop;
    double elapsed_time;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);
    arrAdd<<<6,1>>>(d,e,f);
    cudaEventRecord(stop);
    cudaEventSyncronize(stop);
    cudaEventElapsedTime(&elapsed_time,start,stop);
    cudaMemcpy(c,e,size,cudaMemcpyDeviceToHost);
    printf("%d ",c[i]);
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);
    retrun 0;
}















