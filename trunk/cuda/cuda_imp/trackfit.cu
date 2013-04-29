
#include <stdio.h>  
#include <assert.h>  
#include <cuda.h>  
#include <cutil.h>
#include <trackfit_kernel.cu>
#include "HitTrk.h"



extern "C" void CircleFitG(double X[HIT], double Y[HIT], double Z[HIT], double Zerr[HIT], double *Mx,double *My,double *M0,double *result)
{
//   printf(" Now in Cuda :  Mx =  %g  :  My =  %g  \n", Mx[0],My[0] );
 
 /*  for(int i=0; i<50; i++){
       printf(" Zerr[%i] =  %g  :  Z[%i] =  %g  \n", i, Zerr[i],i ,Z[i]  );
   }
*/
   double *d_X;
   double *d_Y;
   double *d_Z;
   double *d_Zerr;
   double *d_Mx;
   double *d_My;
   double *d_M0;
   double *d_result;
   
/*   result[0]=1;
   result[1]=1;
   result[2]=1;*/
   
   size_t size  =sizeof(double);
   //allocate memory for arrays on device 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_X,        size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Y,        size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Z,        size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Zerr,     size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Mx,       size)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_My,       size)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_M0,       size)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_result,   size*8)); 
  


   CUDA_SAFE_CALL( cudaMemcpy(d_X,          X,   size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Y,          Y,   size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Z,          Z,   size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Zerr,       Zerr,size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Mx,         Mx,  size,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_My,         My,  size,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_M0,         M0,  size,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_result, result,  size*8,    cudaMemcpyHostToDevice));  
  

   dim3 dimBlock2(HIT, 1);
   dim3 dimGrid2(1,1);

   Fit<<< dimGrid2, dimBlock2 >>> (d_X, d_Y,d_Z, d_Zerr,d_Mx,d_My,d_M0, d_result);


   CUDA_SAFE_CALL(cudaMemcpy(result, d_result, size*8, cudaMemcpyDeviceToHost) );
 
 //  printf(" %f      %f      %f  %   f      %f     %f     %f       %f \n", result[0], result[1],result[2], result[3] ,result[4],result[5] ,result[6],result[7]);

   CUDA_SAFE_CALL( cudaFree(d_X)); 
   CUDA_SAFE_CALL( cudaFree(d_Y)); 
   CUDA_SAFE_CALL( cudaFree(d_Z)); 
   CUDA_SAFE_CALL( cudaFree(d_Zerr)); 
   CUDA_SAFE_CALL( cudaFree(d_Mx)); 
   CUDA_SAFE_CALL( cudaFree(d_My)); 
   CUDA_SAFE_CALL( cudaFree(d_M0)); 
   CUDA_SAFE_CALL( cudaFree(d_result)); 

}


extern "C" void CircleFitGAllD(double X[TRK*HIT], double Y[TRK*HIT], double Z[TRK*HIT], double Zerr[TRK*HIT], double Mx[TRK],double My[TRK],double M0[TRK],double result[TRK*8])
{
//   printf(" Now in Cuda :  Mx =  %g  :  My =  %g  \n", Mx[0],My[0] );
/* for(int j=0; j<100; j++){
   for(int i=0; i<HIT; i++){
       printf("%d  Zerr[%i] =  %g  :  Z[%i] =  %g  \n", j ,i, Zerr[i+HIT*j],i ,Z[i+HIT*j]  );
   }
 }
*/
   double *d_X;
   double *d_Y;
   double *d_Z;
   double *d_Zerr;
   double *d_Mx;
   double *d_My;
   double *d_M0;
   double *d_result;
   
/*   result[0]=1;
   result[1]=1;
   result[2]=1;*/
   
   size_t size  =sizeof(double);
   //allocate memory for arrays on device 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_X,        size*HIT*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Y,        size*HIT*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Z,        size*HIT*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Zerr,     size*HIT*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Mx,       size*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_My,       size*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_M0,       size*TRK)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_result,   size*8*TRK)); 
  


   CUDA_SAFE_CALL( cudaMemcpy(d_X,          X,   size*HIT*TRK, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Y,          Y,   size*HIT*TRK, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Z,          Z,   size*HIT*TRK, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Zerr,       Zerr,size*HIT*TRK, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Mx,         Mx,  size*TRK,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_My,         My,  size*TRK,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_M0,         M0,  size*TRK,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_result, result,  size*8*TRK,    cudaMemcpyHostToDevice));  
  
   
   int threads=HIT;
   int tracks=TRK;
   dim3 dimBlock2(threads, 1);
   dim3 dimGrid2(tracks,1);
 
  // FitAllD<<< dimGrid2, dimBlock2 >>> (d_X, d_Y,d_Z, d_Zerr,d_Mx,d_My,d_M0, d_result);
   
  // cudaThreadSynchronize();
   printf(" Now calling the device  \n");
   CUDA_SAFE_CALL(cudaMemcpy(result, d_result, size*8*TRK, cudaMemcpyDeviceToHost) );
 
 /*  for(int j=0; j<tracks; j++){
     printf("%d   ",j);
     for(int i=0; i<8; i++){
        printf("  %f ", result[i+8*j]);
     }
     printf(" \n");
   }
*/
//   printf(" Now cleaning device memory  \n");
   CUDA_SAFE_CALL( cudaFree(d_X)); 
   CUDA_SAFE_CALL( cudaFree(d_Y)); 
   CUDA_SAFE_CALL( cudaFree(d_Z)); 
   CUDA_SAFE_CALL( cudaFree(d_Zerr)); 
   CUDA_SAFE_CALL( cudaFree(d_Mx)); 
   CUDA_SAFE_CALL( cudaFree(d_My)); 
   CUDA_SAFE_CALL( cudaFree(d_M0)); 
   CUDA_SAFE_CALL( cudaFree(d_result)); 
//   printf(" Finish cleaning device memory  \n");
}



extern "C" void CircleFitGAllF(float X[TRK*HIT], float Y[TRK*HIT], float Z[TRK*HIT], float Zerr[TRK*HIT], float Mx[TRK],float My[TRK],float M0[TRK],float result[8*TRK])
{
//   printf(" Now in Cuda :  Mx =  %g  :  My =  %g  \n", Mx[0],My[0] );
/* for(int j=0; j<100; j++){
   for(int i=0; i<HIT; i++){
       printf("%d  Zerr[%i] =  %g  :  Z[%i] =  %g  \n", j ,i, Zerr[i+HIT*j],i ,Z[i+HIT*j]  );
   }
 }
*/
   float *d_X;
   float *d_Y;
   float *d_Z;
   float *d_Zerr;
   float *d_Mx;
   float *d_My;
   float *d_M0;
   float *d_result;
   
/*   result[0]=1;
   result[1]=1;
   result[2]=1;*/
   
   size_t size  =sizeof(float);
   //allocate memory for arrays on device 
   cudaMalloc((void **) &d_X,        size*HIT*TRK); 
   cudaMalloc((void **) &d_Y,        size*HIT*TRK); 
   cudaMalloc((void **) &d_Z,        size*HIT*TRK); 
   cudaMalloc((void **) &d_Zerr,     size*HIT*TRK); 
   cudaMalloc((void **) &d_Mx,       size*TRK); 
   cudaMalloc((void **) &d_My,       size*TRK); 
   cudaMalloc((void **) &d_M0,       size*TRK); 
   cudaMalloc((void **) &d_result,   size*8*TRK); 
  


   cudaMemcpy(d_X,          X,   size*HIT*TRK, cudaMemcpyHostToDevice);  
   cudaMemcpy(d_Y,          Y,   size*HIT*TRK, cudaMemcpyHostToDevice);  
   cudaMemcpy(d_Z,          Z,   size*HIT*TRK, cudaMemcpyHostToDevice);  
   cudaMemcpy(d_Zerr,       Zerr,size*HIT*TRK, cudaMemcpyHostToDevice);  
   cudaMemcpy(d_Mx,         Mx,  size*TRK,    cudaMemcpyHostToDevice);  
   cudaMemcpy(d_My,         My,  size*TRK,    cudaMemcpyHostToDevice);  
   cudaMemcpy(d_M0,         M0,  size*TRK,    cudaMemcpyHostToDevice);  
   cudaMemcpy(d_result, result,  size*8*TRK,  cudaMemcpyHostToDevice);  
  
   
   int threads=HIT;
   int tracks=TRK;
   dim3 dimBlock2(threads, 1);
   dim3 dimGrid2(tracks,1);

  // FitAllF<<< dimGrid2, dimBlock2 >>> (d_X, d_Y,d_Z, d_Zerr,d_Mx,d_My,d_M0, d_result);
   
//   cudaThreadSynchronize();

   cudaMemcpy(result, d_result, size*8*TRK, cudaMemcpyDeviceToHost);
 
 /*  for(int j=0; j<tracks; j++){
     printf("%d   ",j);
     for(int i=0; i<8; i++){
        printf("  %f ", result[i+8*j]);
     }
     printf(" \n");
   }
*/
  // printf(" Now cleaning device memory  \n");
   CUDA_SAFE_CALL( cudaFree(d_X)); 
   CUDA_SAFE_CALL( cudaFree(d_Y)); 
   CUDA_SAFE_CALL( cudaFree(d_Z)); 
   CUDA_SAFE_CALL( cudaFree(d_Zerr)); 
   CUDA_SAFE_CALL( cudaFree(d_Mx)); 
   CUDA_SAFE_CALL( cudaFree(d_My)); 
   CUDA_SAFE_CALL( cudaFree(d_M0)); 
   CUDA_SAFE_CALL( cudaFree(d_result)); 
 //   printf(" Finish cleaning device memory  \n");
}




extern "C" void CircleFitGF(float X[HIT], float Y[HIT], float Z[HIT], float Zerr[HIT], float *Mx,float *My,float *M0,float *result)
{
//   printf(" Now in Cuda :  Mx =  %g  :  My =  %g  \n", Mx[0],My[0] );
 
 /*  for(int i=0; i<50; i++){
       printf(" Zerr[%i] =  %g  :  Z[%i] =  %g  \n", i, Zerr[i],i ,Z[i]  );
   }
*/
   float *d_X;
   float *d_Y;
   float *d_Z;
   float *d_Zerr;
   float *d_Mx;
   float *d_My;
   float *d_M0;
   float *d_result;
   
/*   result[0]=1;
   result[1]=1;
   result[2]=1;*/
   
   size_t size  =sizeof(float);
   //allocate memory for arrays on device 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_X,        size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Y,        size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Z,        size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Zerr,     size*HIT)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_Mx,       size)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_My,       size)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_M0,       size)); 
   CUDA_SAFE_CALL( cudaMalloc((void **) &d_result,   size*8)); 
  


   CUDA_SAFE_CALL( cudaMemcpy(d_X,          X,   size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Y,          Y,   size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Z,          Z,   size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Zerr,       Zerr,size*HIT, cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_Mx,         Mx,  size,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_My,         My,  size,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_M0,         M0,  size,    cudaMemcpyHostToDevice));  
   CUDA_SAFE_CALL( cudaMemcpy(d_result, result,  size*8,    cudaMemcpyHostToDevice));  
  

   dim3 dimBlock2(HIT, 1);
   dim3 dimGrid2(1,1);

   FitF<<< dimGrid2, dimBlock2 >>> (d_X, d_Y,d_Z, d_Zerr,d_Mx,d_My,d_M0, d_result);


   CUDA_SAFE_CALL(cudaMemcpy(result, d_result, size*8, cudaMemcpyDeviceToHost) );
 
 //  printf(" %f      %f      %f  %   f      %f     %f     %f       %f \n", result[0], result[1],result[2], result[3] ,result[4],result[5] ,result[6],result[7]);

   CUDA_SAFE_CALL( cudaFree(d_X)); 
   CUDA_SAFE_CALL( cudaFree(d_Y)); 
   CUDA_SAFE_CALL( cudaFree(d_Z)); 
   CUDA_SAFE_CALL( cudaFree(d_Zerr)); 
   CUDA_SAFE_CALL( cudaFree(d_Mx)); 
   CUDA_SAFE_CALL( cudaFree(d_My)); 
   CUDA_SAFE_CALL( cudaFree(d_M0)); 
   CUDA_SAFE_CALL( cudaFree(d_result)); 

}
















