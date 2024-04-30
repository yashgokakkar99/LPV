// #include<stdio.h>
// #include<cuda.h>
// #define N 3

// __global__ void matMul(int *a,int *b,int *c)
// {
//     int row = blockIdx.y * blockDim.y + threadIdx.y;
//     int col = blockIdx.x * blockDim.x + threadIdx.x;
//     int sum = 0;
//     for(int i=0;i<N;++i)
//     {
//         sum+=a[row*N+i]*b[i*N+col];
//     }
//     c[row*N+col] = sum;
// }

// int main()
// {
//     int a[N][N],b[N][N],c[N][N];
//     int *d,*e,*f;
//     int size = N*N*sizeof(int);
//     for(int i=0;i<N;++i)
//     {
//         for(int j=0;j<N;++j)
//         {
//             scanf("%d",&a[i][j])
//         }
//     }
//     for(int i=0;i<N;++i)
//     {
//         for(int j=0;j<N;++j)
//         {
//             scanf("%d",&b[i][j])
//         }
//     }
//     cudaMalloc((void **)&d,size);
//     cudaMalloc((void **)&e,size);
//     cudaMalloc((void **)&f,size);
//     cudaMemcpy(d,a,size,cudaMemcpyHostToDevice);
//     cudaMemcpy(e,b,size,cudaMemcpyHostToDevice);
//     dim3 threadsPerBlock(N,N);
//     dim3 numBlocks(1,1);
//     matMul<<<numBlocks,threadsPerBlock>>>(d,e,f);
//     cudaMemcpy(c,f,size,cudaMemcpyDeviceToHost);
//     for(int i=0;i<N;++i)
//     {
//         for(int j=0;j<N;++j)
//         {
//             printf("%d",c[i][j]);
//         }
//     }
//     return 0;
// }




#include<stdio.h>
#include<cuda.h>
#define N 3

__global__ void matMul(int *a,int *b,int *c)
{
    int row = blockIdx.y* blockDim.y+ threadIdx.y;
    int col = blockIdx.x* blockDim.x+ threadIdx.x;
    int sum = 0;
    for(int i=0;i<N;i++)
    {
        sum += a[N*row+i]*b[i*N+col];
        c[N*row+col] = sum;
    }
} 

dim3 threadsPerBlock(N,N)
dim3 numBlocks(1,1)