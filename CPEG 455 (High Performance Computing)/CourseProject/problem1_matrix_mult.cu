#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BLOCK_SIZE 16

//This program can be compiled in the terminal with the command: nvcc problem1_matrix_mult.cu
//This program can be ran by running the executable a.out with the command: ./a.out

/*
    Computes dot product of two matrices in GPU

    a = GPU device pointer to a m X n matrix
    b = GPU device pointer to a n X k matrix
    c = an m X k matrix to store the result

    assigns one thread to compute one element of matrix C. Each thread loads one row of matrix A and one column of matrix B from global memory, 
	
    stores the result back to matrix C in the global memory

    the amount of computation = 2 * m * n * k flops

    the amount of global memory accesses = 2 * m * n * k
*/

__global__ void gpu_matrix_mult(int *a, int *b, int *c, int m, int n, int k){ 

    int row = blockIdx.y * blockDim.y + threadIdx.y; 

    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int sum = 0;

    if( col < k && row < m) {
        for(int i = 0; i < n; i++) {
            sum += a[row * n + i] * b[i * k + col];
        }

        c[row * k + col] = sum;
    }
} 



/*
    Tiled version of above for GPU

    only for square matrix mutiplication

    d_a = GPU pointer to a m X n matrix
    d_b = GPU pointer to a n X k matrix
    d_result = an m X k matrix to store the result

    the amount of computation is 2 x M x N x K flop. 
    
    Using tile size of B, the amount of global memory access is 2 x M x N x K / B

    
*/


__global__ void gpu_square_matrix_mult(int *d_a, int *d_b, int *d_result, int n) {

    __shared__ int tile_a[BLOCK_SIZE][BLOCK_SIZE];

    __shared__ int tile_b[BLOCK_SIZE][BLOCK_SIZE];

    int row = blockIdx.y * BLOCK_SIZE + threadIdx.y;

    int col = blockIdx.x * BLOCK_SIZE + threadIdx.x;

    int tmp = 0;

    int idx;

    for(int j = 0; j < gridDim.x; j++){

        idx = row * n + j * BLOCK_SIZE + threadIdx.x;

        if(idx >= n*n){
           tile_a[threadIdx.y][threadIdx.x] = 0;
        }

        else{
            tile_a[threadIdx.y][threadIdx.x] = d_a[idx];
        }

        idx = (j * BLOCK_SIZE + threadIdx.y) * n + col;
        
	if(idx >= n*n){
            tile_b[threadIdx.y][threadIdx.x] = 0;
        }  
        else{
            tile_b[threadIdx.y][threadIdx.x] = d_b[idx];
        }
        
	__syncthreads();

        for (int k = 0; k < BLOCK_SIZE; ++k){
            tmp += tile_a[threadIdx.y][k] * tile_b[k][threadIdx.x];
        }
        __syncthreads();
    }

    if(row < n && col < n){
        d_result[row * n + col] = tmp;
    }
}


int main(int argc, char const *argv[]){

    int m, n, k;

    srand(3333);

    printf("What is m n and k ? (Square matricies only)\n");

    scanf("%d %d %d", &m, &n, &k);

    // allocate memory in host RAM
    int *h_a, *h_b, *h_c, *h_cc;

    cudaMallocHost((void **) &h_a, sizeof(int)*m*n);

    cudaMallocHost((void **) &h_b, sizeof(int)*n*k);

    cudaMallocHost((void **) &h_c, sizeof(int)*m*k);

    cudaMallocHost((void **) &h_cc, sizeof(int)*m*k);

    
    //making a random matrix h_a
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j) {
            h_a[i * n + j] = rand() % 1024;
        }
    }
    

    //making a random matrix h_b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            h_b[i * k + j] = rand() % 1024;
        }
    }

    float gpu_elapsed_time_ms, gpu_square_elapsed_time_ms;

    //Used to calculate execution time
    cudaEvent_t start, stop;

    cudaEventCreate(&start);

    cudaEventCreate(&stop);


    // Allocate memory space on the device 
    int *d_a, *d_b, *d_c, *d_cc;
    cudaMalloc((void **) &d_a, sizeof(int)*m*n);
    cudaMalloc((void **) &d_b, sizeof(int)*n*k);
    cudaMalloc((void **) &d_c, sizeof(int)*m*k);
    cudaMalloc((void **) &d_cc, sizeof(int)*m*k);

    // copy matrix A and B from host to device memory
    cudaMemcpy(d_a, h_a, sizeof(int)*m*n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, sizeof(int)*n*k, cudaMemcpyHostToDevice);

    unsigned int grid_rows = (m + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned int grid_cols = (k + BLOCK_SIZE - 1) / BLOCK_SIZE;
    dim3 dimGrid(grid_cols, grid_rows);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
   
    

    //Can only run if the matrices are square because we need to compare the regular time to the square time
    if(m == n && n == k){

        // start to count execution time of tiled GPU version
        cudaEventRecord(start, 0);

        //running it 100 times to get an average
        for(int i = 0; i <100; i++){
            gpu_square_matrix_mult<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, n);
        }
            
        //Stop recording time
        cudaEventRecord(stop, 0);
        cudaEventSynchronize(stop);

        // compute time elapse on GPU function
        cudaEventElapsedTime(&gpu_square_elapsed_time_ms, start, stop);


        // start to count execution time of regular GPU version
        cudaEventRecord(start, 0);

        //Non-tiled version, again run it 100 times
        for(int i = 0; i <100; i++){
            gpu_matrix_mult<<<dimGrid, dimBlock>>>(d_a, d_b, d_cc, m, n, k);
        }    

        //Stop recording time
        cudaEventRecord(stop, 0);
        cudaEventSynchronize(stop);

        // compute time elapse on standard GPU function
        cudaEventElapsedTime(&gpu_elapsed_time_ms, start, stop);
         

        // Transfer results from device to host 
        cudaMemcpy(h_c, d_c, sizeof(int)*m*k, cudaMemcpyDeviceToHost);
        cudaMemcpy(h_cc, d_cc, sizeof(int)*m*k, cudaMemcpyDeviceToHost);
        cudaThreadSynchronize();
    }

    else{
        printf("Error: Please use a square matrix\n");
        exit(0);
    }

    //divide by 100 because we ran 100 times
    printf("Average time elapsed on standard matrix multiplication of %dx%d . %dx%d on GPU: %f ms.\n\n", m, n, n, k, gpu_elapsed_time_ms/100);
    //divide by 100 because we ran 100 times
    printf("Average time elapsed on tiled matrix multiplication of %dx%d . %dx%d on GPU: %f ms.\n\n", m, n, n, k, gpu_square_elapsed_time_ms/100);

    printf("Average speedup Percentage from nontiled to tiled algorithim = %f%s\n", 100*gpu_elapsed_time_ms / gpu_square_elapsed_time_ms, "%");


    // validate results
    int all_ok = 1;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {      
            if(h_cc[i*k + j] != h_c[i*k + j])
            {
                all_ok = 0;
            }
            
        }   
    }
    printf("\n");

    if(all_ok)
    {
        printf("all results are correct!!!\n");
    }
    else
    {
        printf("incorrect results\n");
    }



    // free memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    cudaFree(d_cc);
    cudaFreeHost(h_a);
    cudaFreeHost(h_b);
    cudaFreeHost(h_c);
    cudaFreeHost(h_cc);
    return 0;
}
