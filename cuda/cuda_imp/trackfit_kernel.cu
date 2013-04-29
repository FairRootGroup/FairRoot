#ifndef _TRACKFIT_KERNEL_H_
#define _TRACKFIT_KERNEL_H_

#include <stdio.h>  

#include <cuda.h>  
#include <cutil.h>

inline __device__ int Newton(double Mxx, double Myy, double Mxy, double Mxz, double Myz, double Mzz,double *result)

{
 
  double Mz,Mxz2,Myz2,Cov_xy; //,temp;
  double A0, A1, A2, A22, epsilon = 0.000000000001;
  double Dy, xnew, xold, ynew, yold = 100000000000.;



  Mz = Mxx + Myy;
  Cov_xy = Mxx*Myy - Mxy*Mxy;
  Mxz2 = Mxz*Mxz;
  Myz2 = Myz*Myz;

  A2 = 4.*Cov_xy - 3.*Mz*Mz - Mzz;
  A1 = Mzz*Mz + 4.*Cov_xy*Mz - Mxz2 - Myz2 - Mz*Mz*Mz;
  A0 = Mxz2*Myy + Myz2*Mxx - Mzz*Cov_xy - 2.*Mxz*Myz*Mxy + Mz*Mz*Cov_xy;

  A22 = A2 + A2;
  //  iter = 0;
  xnew = 0.;

  //    Newton's method starting at x=0

  int iter, iterMax = 20;
  for (iter=0; iter < iterMax; iter++) {
    ynew = A0 + xnew*(A1 + xnew*(A2 + 4.*xnew*xnew));

    if (fabs(ynew)>fabs(yold)) {
      //          printf("Newton2 goes wrong direction: ynew=%f
      //          yold=%f\n",ynew,yold);
      xnew = 0.;
      break;
    }

    Dy = A1 + xnew*(A22 + 16.*xnew*xnew);
    xold = xnew;
    xnew = xold - ynew/Dy;
    
    if (fabs(xnew) < epsilon) break;  
    if (fabs((xnew-xold)/xnew) < epsilon) break;
  }

  if (iter == iterMax-1) {
    //      printf("Newton2 does not converge in %d
    //      iterations\n",iterMax);
    xnew = 0.;
  }

  if (xnew < 0.) {
    iter=30;
         // printf("Negative root: x=%f\n",xnew);
  }

  //    computing the circle parameters

  double GAM,DET;
 // double Xcenter,Ycenter,Radius;

  GAM = - Mz - xnew - xnew;
  DET = xnew*xnew - xnew*Mz + Cov_xy;
  if (DET==0) return 0;

  result[0] = (Mxz*(Myy-xnew) - Myz*Mxy)/DET/2.;
  result[1] = (Myz*(Mxx-xnew) - Mxz*Mxy)/DET/2.;
  if ((result[0]*result[0]+result[1]*result[1]-GAM) < 0.) return 0;

  result[2] = sqrt(result[0]*result[0]+result[1]*result[1]-GAM);
   
 
   return 1;
 
}



__global__ void 
 
Fit(double *X, double *Y,double *Z1, double *Z1err, double *Mx,double *My,double *M0,double *result)
{
   unsigned int x = blockDim.x * blockIdx.x + threadIdx.x;
  // unsigned int y = blockDim.y * blockIdx.y + threadIdx.y;

   // printf("Negative root: x=%f\n");

   __shared__ double Xs[30];
   __shared__ double Ys[30];
   __shared__ double Xis[30];
   __shared__ double Yis[30];
   __shared__ double Zis[30];
   __shared__ double Z1s[30];
   __shared__ double Z1Errs[30];
   __shared__ double rho[30];
   __shared__ double fZWeight[30]; 

   if(x < 30){
           Xs[x]    = X[x];
           Ys[x]    = Y[x];
           Z1s[x]   = Z1[x];
           Z1Errs[x]= Z1err[x];
        //   printf("Z1Errs(%d) = %g \n",x , Z1Errs[x]);
   }

   Xis[x] = Xs[x]- Mx[0];
   Yis[x] = Ys[x]- My[0];
   
   __syncthreads();
   
   Zis[x] = Xis[x]*Xis[x] + Yis[x]*Yis[x];
   rho[x] = sqrt(Xis[x]*Xis[x] + Yis[x]*Yis[x]);
 //  printf("rho(%d) = %g \n",x , rho[x]); 
   if(Z1Errs[x]>0.001)fZWeight[x] = 1/(Z1Errs[x]*Z1Errs[x]);
   else {
   //  printf("Z1Err(%d) = %g \n",x , Z1Errs[x]); 
     fZWeight[x] = 0.0;
   
   }
  
   __syncthreads();

  if(x<1) { 
   double Mxx=0;
   double Myy=0;
   double Mxy=0;
   double Mxz=0;
   double Myz=0;
   double Mzz=0;



   double wsum  = 0. ;
   double wx  = 0. ;
   double wy  = 0. ;
   double wxx = 0.;
   double wxy = 0. ;

   for(int i=0; i<30; i++){
     Mxy += Xis[i]*Yis[i];
     Mxx += Xis[i]*Xis[i];
     Myy += Yis[i]*Yis[i];
     Mxz += Xis[i]*Zis[i];
     Myz += Yis[i]*Zis[i];
     Mzz += Zis[i]*Zis[i];
     
     wsum+= fZWeight[i];
     wx  += fZWeight[i]*rho[i];
     wy  += fZWeight[i]*Z1s[i];
     wxx += fZWeight[i]*rho[i]*rho[i];
     wxy += fZWeight[i]*rho[i]*Z1s[i];
  //   printf("Weights    =%f   %f  %f  \n" ,fZWeight[i],rho[i],Z1s[i] );
   }
    
   Mxx /= M0[0];
   Myy /= M0[0];
   Mxy /= M0[0];
   Mxz /= M0[0];
   Myz /= M0[0];
   Mzz /= M0[0];
   
//  printf("Result =%f   %f  %f %f  %f  \n" ,wsum, wxy, wxx, wx, wy );
   int t= Newton(Mxx, Myy, Mxy, Mxz, Myz, Mzz, result);
   

  double mm = 0.;
  double qq = 0.;  
  double det = wsum * wxx - wx * wx;
   if (det>0.00001) {
      mm = (wxy * wsum - wy * wx) / det;
      qq = (wy * wxx - wxy * wx) / det;
   }else {mm=1000.; qq=1000.;} 

   result[3]=-mm;
   result[4]=qq;
 

   double r1 ;
   double chi2 = 0.;
  
   for(int i=0; i < 30; i++) {
     r1   = Z1s[i] + result[3] * rho[i] - result[4];
     chi2 += fZWeight[i] * (r1 * r1);
   }
   result[5]=chi2;


   if (det>0.00001){
     double varsq = sqrt(chi2/30.);
     result[6] = varsq * sqrt( wsum / det );
     result[7] = varsq * sqrt( wxx / det );
   }else{
     result[6] = 0;
     result[7] = 0;
   }

  }
  
  
}



//--------------------------------------------------------------------------------------------------------------//



inline __device__ int NewtonF(float Mxx, float Myy, float Mxy, float Mxz, float Myz, float Mzz,float *result)

{
 
  float Mz,Mxz2,Myz2,Cov_xy; //,temp;
  float A0, A1, A2, A22, epsilon = 0.000000000001;
  float Dy, xnew, xold, ynew, yold = 100000000000.;



  Mz = Mxx + Myy;
  Cov_xy = Mxx*Myy - Mxy*Mxy;
  Mxz2 = Mxz*Mxz;
  Myz2 = Myz*Myz;

  A2 = 4.*Cov_xy - 3.*Mz*Mz - Mzz;
  A1 = Mzz*Mz + 4.*Cov_xy*Mz - Mxz2 - Myz2 - Mz*Mz*Mz;
  A0 = Mxz2*Myy + Myz2*Mxx - Mzz*Cov_xy - 2.*Mxz*Myz*Mxy + Mz*Mz*Cov_xy;

  A22 = A2 + A2;
  //  iter = 0;
  xnew = 0.;

  //    Newton's method starting at x=0

  int iter, iterMax = 20;
  for (iter=0; iter < iterMax; iter++) {
    ynew = A0 + xnew*(A1 + xnew*(A2 + 4.*xnew*xnew));

    if (fabs(ynew)>fabs(yold)) {
      //          printf("Newton2 goes wrong direction: ynew=%f
      //          yold=%f\n",ynew,yold);
      xnew = 0.;
      break;
    }

    Dy = A1 + xnew*(A22 + 16.*xnew*xnew);
    xold = xnew;
    xnew = xold - ynew/Dy;
    
    if (fabs(xnew) < epsilon) break;  
    if (fabs((xnew-xold)/xnew) < epsilon) break;
  }

  if (iter == iterMax-1) {
    //      printf("Newton2 does not converge in %d
    //      iterations\n",iterMax);
    xnew = 0.;
  }

  if (xnew < 0.) {
    iter=30;
         // printf("Negative root: x=%f\n",xnew);
  }

  //    computing the circle parameters

  float GAM,DET;
 // float Xcenter,Ycenter,Radius;

  GAM = - Mz - xnew - xnew;
  DET = xnew*xnew - xnew*Mz + Cov_xy;
  if (DET==0) return 0;

  result[0] = (Mxz*(Myy-xnew) - Myz*Mxy)/DET/2.;
  result[1] = (Myz*(Mxx-xnew) - Mxz*Mxy)/DET/2.;
  if ((result[0]*result[0]+result[1]*result[1]-GAM) < 0.) return 0;

  result[2] = sqrt(result[0]*result[0]+result[1]*result[1]-GAM);
   
 
   return 1;
 
}



__global__ void 
 
FitF(float *X, float *Y,float *Z1, float *Z1err, float *Mx1,float *My1,float *M01,float *result)
{
   unsigned int x = blockDim.x * blockIdx.x + threadIdx.x;
  // unsigned int y = blockDim.y * blockIdx.y + threadIdx.y;

   // printf("Negative root: x=%f\n");

   __shared__ float Xs[15];
   __shared__ float Ys[15];
   __shared__ float Xis[15];
   __shared__ float Yis[15];
   __shared__ float Zis[15];
   __shared__ float Z1s[15];
   __shared__ float Z1Errs[15];
   __shared__ float rho[15];
   __shared__ float fZWeight[15]; 
   __shared__ float Mx[1]; 
   __shared__ float My[1]; 
   __shared__ float M0[1]; 

//   if(x < 30){
           Xs[x]    = X[x];
           Ys[x]    = Y[x];
           Z1s[x]   = Z1[x];
           Z1Errs[x]= Z1err[x];
        //   printf("Z1Errs(%d) = %g \n",x , Z1Errs[x]);
//   }
   if(x<1){
      Mx[0]=Mx1[0]; 
      My[0]=My1[0]; 
      M0[0]=M01[0]; 
   }
   __syncthreads();
   Xis[x] = Xs[x]- Mx[0];
   Yis[x] = Ys[x]- My[0];
   Zis[x] = Xis[x]*Xis[x] + Yis[x]*Yis[x];
   rho[x] = sqrt(Xis[x]*Xis[x] + Yis[x]*Yis[x]);
 //  printf("rho(%d) = %g \n",x , rho[x]); 
   if(Z1Errs[x]>0.001)fZWeight[x] = 1/(Z1Errs[x]*Z1Errs[x]);
   else {
   //  printf("Z1Err(%d) = %g \n",x , Z1Errs[x]); 
     fZWeight[x] = 0.0;
   }

   __syncthreads();

  if(x<1) { 
   float Mxx=0;
   float Myy=0;
   float Mxy=0;
   float Mxz=0;
   float Myz=0;
   float Mzz=0;



   float wsum  = 0. ;
   float wx  = 0. ;
   float wy  = 0. ;
   float wxx = 0.;
   float wxy = 0. ;

   for(int i=0; i<15; i++){
     Mxy += Xis[i]*Yis[i];
     Mxx += Xis[i]*Xis[i];
     Myy += Yis[i]*Yis[i];
     Mxz += Xis[i]*Zis[i];
     Myz += Yis[i]*Zis[i];
     Mzz += Zis[i]*Zis[i];
     
     wsum+= fZWeight[i];
     wx  += fZWeight[i]*rho[i];
     wy  += fZWeight[i]*Z1s[i];
     wxx += fZWeight[i]*rho[i]*rho[i];
     wxy += fZWeight[i]*rho[i]*Z1s[i];
  //   printf("Weights    =%f   %f  %f  \n" ,fZWeight[i],rho[i],Z1s[i] );
   }
    
   Mxx /= M0[0];
   Myy /= M0[0];
   Mxy /= M0[0];
   Mxz /= M0[0];
   Myz /= M0[0];
   Mzz /= M0[0];
   
//  printf("Result =%f   %f  %f %f  %f  \n" ,wsum, wxy, wxx, wx, wy );
   int t= NewtonF(Mxx, Myy, Mxy, Mxz, Myz, Mzz, result);
   

  float mm = 0.;
  float qq = 0.;  
  float det = wsum * wxx - wx * wx;
   if (det>0.00001) {
      mm = (wxy * wsum - wy * wx) / det;
      qq = (wy * wxx - wxy * wx) / det;
   }else {mm=1000.; qq=1000.;} 

   result[3]=-mm;
   result[4]=qq;
 

   float r1 ;
   float chi2 = 0.;
  
   for(int i=0; i < 15; i++) {
     r1   = Z1s[i] + result[3] * rho[i] - result[4];
     chi2 += fZWeight[i] * (r1 * r1);
   }
   result[5]=chi2;


   if (det>0.00001){
     float varsq = sqrt(chi2/13.);
     result[6] = varsq * sqrt( wsum / det );
     result[7] = varsq * sqrt( wxx / det );
   }else{
     result[6] = 0;
     result[7] = 0;
   }

  }
  
  
}





inline __device__ int NewtonAllF(float Mxx, float Myy, float Mxy, float Mxz, float Myz, float Mzz,float *result)

{
  unsigned int y = blockIdx.x;
  float Mz,Mxz2,Myz2,Cov_xy; //,temp;
  float A0, A1, A2, A22, epsilon = 0.000000000001;
  float Dy, xnew, xold, ynew, yold = 100000000000.;



  Mz = Mxx + Myy;
  Cov_xy = Mxx*Myy - Mxy*Mxy;
  Mxz2 = Mxz*Mxz;
  Myz2 = Myz*Myz;

  A2 = 4.*Cov_xy - 3.*Mz*Mz - Mzz;
  A1 = Mzz*Mz + 4.*Cov_xy*Mz - Mxz2 - Myz2 - Mz*Mz*Mz;
  A0 = Mxz2*Myy + Myz2*Mxx - Mzz*Cov_xy - 2.*Mxz*Myz*Mxy + Mz*Mz*Cov_xy;

  A22 = A2 + A2;
  //  iter = 0;
  xnew = 0.;

  //    Newton's method starting at x=0

  int iter, iterMax = 20;
  for (iter=0; iter < iterMax; iter++) {
    ynew = A0 + xnew*(A1 + xnew*(A2 + 4.*xnew*xnew));

    if (fabs(ynew)>fabs(yold)) {
      //          printf("Newton2 goes wrong direction: ynew=%f
      //          yold=%f\n",ynew,yold);
      xnew = 0.;
      break;
    }

    Dy = A1 + xnew*(A22 + 16.*xnew*xnew);
    xold = xnew;
    xnew = xold - ynew/Dy;
    
    if (fabs(xnew) < epsilon) break;  
    if (fabs((xnew-xold)/xnew) < epsilon) break;
  }

  if (iter == iterMax-1) {
    //      printf("Newton2 does not converge in %d
    //      iterations\n",iterMax);
    xnew = 0.;
  }

  if (xnew < 0.) {
    iter=30;
         // printf("Negative root: x=%f\n",xnew);
  }

  //    computing the circle parameters

  float GAM,DET;
 // float Xcenter,Ycenter,Radius;

  GAM = - Mz - xnew - xnew;
  DET = xnew*xnew - xnew*Mz + Cov_xy;
  if (DET==0) return 0;

  result[8*y] = (Mxz*(Myy-xnew) - Myz*Mxy)/DET/2.;
  result[1+8*y] = (Myz*(Mxx-xnew) - Mxz*Mxy)/DET/2.;
  if ((result[8*y]*result[8*y]+result[1+8*y]*result[1+8*y]-GAM) < 0.) return 0;

  result[2+8*y] = sqrt(result[8*y]*result[8*y]+result[1+8*y]*result[1+8*y]-GAM);
   
 
   return 1;
 
}









__global__ void 
FitAllF(float *X, float *Y,float *Z1, float *Z1err, float *Mx1,float *My1,float *M01,float *result)
{
//   unsigned int x = blockDim.x * blockIdx.x + threadIdx.x;
   unsigned int y = blockIdx.x;
   unsigned int x = threadIdx.x;
  // unsigned int y = blockDim.y * blockIdx.y + threadIdx.y;
 //   printf("Block No: =%d , threadId.x =%d \n",y,x);
   __shared__ float Xs[30];
   __shared__ float Ys[30];
   __shared__ float Xis[30];
   __shared__ float Yis[30];
   __shared__ float Zis[30];
   __shared__ float Z1s[30];
   __shared__ float Z1Errs[30];
   __shared__ float rho[30];
   __shared__ float fZWeight[30];   
   __shared__ float Mx[100]; 
   __shared__ float My[100]; 
   __shared__ float M0[100]; 

   float Mxx=0.;
   float Myy=0.;
   float Mxy=0.;
   float Mxz=0.;
   float Myz=0.;
   float Mzz=0.;
   float wsum= 0. ;
   float wx  = 0. ;
   float wy  = 0. ;
   float wxx = 0.;
   float wxy = 0. ;


   Xs[x]    = X[x+30*y];
   Ys[x]    = Y[x+30*y];
   Z1s[x]   = Z1[x+30*y];
   Z1Errs[x]= Z1err[x+30*y];
  //         printf("blockid = %d  Z1Errs(%d) = %g \n",y, x , Z1Errs[x]);
  //   if(x < 8) result[x+8*y]=0.000;
   
   if(x<1){
      Mx[y]=Mx1[y]; 
      My[y]=My1[y]; 
      M0[y]=M01[y]; 
   }
   __syncthreads();

   Xis[x] = Xs[x]- Mx[y];
   Yis[x] = Ys[x]- My[y];
   Zis[x] = Xis[x]*Xis[x] + Yis[x]*Yis[x];
   rho[x] = sqrt(Zis[x]);

   Mxy+= Xis[x]*Yis[x]/M0[y];
   Mxx+= Xis[x]*Xis[x]/M0[y];
   Myy+= Yis[x]*Yis[x]/M0[y];
   Mxz+= Xis[x]*Zis[x]/M0[y];
   Myz+= Yis[x]*Zis[x]/M0[y];
   Mzz+= Zis[x]*Zis[x]/M0[y];

 
 //  printf("rho(%d) = %g \n",x , rho[x]); 
   if(Z1Errs[x]>0.001)fZWeight[x] = 1/(Z1Errs[x]*Z1Errs[x]);
   else {
   //  printf("Z1Err(%d) = %g \n",x , Z1Errs[x]); 
     fZWeight[x] = 0.0;
   
   }
 
   wsum+= fZWeight[x];
   wx  += fZWeight[x]*rho[x];
   wy  += fZWeight[x]*Z1s[x];
   wxx += fZWeight[x]*Z1s[x];
   wxy += fZWeight[x]*rho[x]*Z1s[x];

 
   __syncthreads();

  if(x<1) { 
//  printf("Result =%f   %f  %f %f  %f  \n" ,wsum, wxy, wxx, wx, wy );
   int t= NewtonAllF(Mxx, Myy, Mxy, Mxz, Myz, Mzz, result);
  float mm = 0.;
  float qq = 0.;  
  float det = wsum * wxx - wx * wx;
   if (det>0.00001) {
      mm = (wxy * wsum - wy * wx) / det;
      qq = (wy * wxx - wxy * wx) / det;
   }else {mm=1000.; qq=1000.;} 

   result[3+8*y]=-mm;
   result[4+8*y]=qq;
 
   float r1 ;
   float chi2 = 0.;
  
   for(int i=0; i < 30; i++) {
     r1   = Z1s[i] + result[3+8*y] * rho[i] - result[4+8*y];
     chi2 += fZWeight[i] * (r1 * r1);
   }
   result[5+8*y]=chi2;

   if (det>0.00001){
     float varsq = sqrt(chi2/25.);
     result[6+8*y] = varsq * sqrt( wsum / det );
     result[7+8*y] = varsq * sqrt( wxx / det );
   }else{
     result[6+8*y] = 0;
     result[7+8*y] = 0;
   }

  }
  
  
}



inline __device__ int NewtonAllD(double Mxx, double Myy, double Mxy, double Mxz, double Myz, double Mzz,double *result)

{
  unsigned int y = blockIdx.x;
  double Mz,Mxz2,Myz2,Cov_xy; //,temp;
  double A0, A1, A2, A22, epsilon = 0.000000000001;
  double Dy, xnew, xold, ynew, yold = 100000000000.;



  Mz = Mxx + Myy;
  Cov_xy = Mxx*Myy - Mxy*Mxy;
  Mxz2 = Mxz*Mxz;
  Myz2 = Myz*Myz;

  A2 = 4.*Cov_xy - 3.*Mz*Mz - Mzz;
  A1 = Mzz*Mz + 4.*Cov_xy*Mz - Mxz2 - Myz2 - Mz*Mz*Mz;
  A0 = Mxz2*Myy + Myz2*Mxx - Mzz*Cov_xy - 2.*Mxz*Myz*Mxy + Mz*Mz*Cov_xy;

  A22 = A2 + A2;
  //  iter = 0;
  xnew = 0.;

  //    Newton's method starting at x=0

  int iter, iterMax = 20;
  for (iter=0; iter < iterMax; iter++) {
    ynew = A0 + xnew*(A1 + xnew*(A2 + 4.*xnew*xnew));

    if (fabs(ynew)>fabs(yold)) {
      //          printf("Newton2 goes wrong direction: ynew=%f
      //          yold=%f\n",ynew,yold);
      xnew = 0.;
      break;
    }

    Dy = A1 + xnew*(A22 + 16.*xnew*xnew);
    xold = xnew;
    xnew = xold - ynew/Dy;
    
    if (fabs(xnew) < epsilon) break;  
    if (fabs((xnew-xold)/xnew) < epsilon) break;
  }

  if (iter == iterMax-1) {
    //      printf("Newton2 does not converge in %d
    //      iterations\n",iterMax);
    xnew = 0.;
  }

  if (xnew < 0.) {
    iter=30;
         // printf("Negative root: x=%f\n",xnew);
  }

  //    computing the circle parameters

  double GAM,DET;
 // double Xcenter,Ycenter,Radius;

  GAM = - Mz - xnew - xnew;
  DET = xnew*xnew - xnew*Mz + Cov_xy;
  if (DET==0) return 0;

  result[8*y] = (Mxz*(Myy-xnew) - Myz*Mxy)/DET/2.;
  result[1+8*y] = (Myz*(Mxx-xnew) - Mxz*Mxy)/DET/2.;
  if ((result[8*y]*result[8*y]+result[1+8*y]*result[1+8*y]-GAM) < 0.) return 0;

  result[2+8*y] = sqrt(result[8*y]*result[8*y]+result[1+8*y]*result[1+8*y]-GAM);
   
 
   return 1;
 
}









__global__ void 
FitAllD(double *X, double *Y,double *Z1, double *Z1err, double *Mx,double *My,double *M0,double *result)
{
//   unsigned int x = blockDim.x * blockIdx.x + threadIdx.x;
   unsigned int y = blockIdx.x;
   unsigned int x = threadIdx.x;
  // unsigned int y = blockDim.y * blockIdx.y + threadIdx.y;
 //   printf("Block No: =%d , threadId.x =%d \n",y,x);
   __shared__ double Xs[30];
   __shared__ double Ys[30];
   __shared__ double Xis[30];
   __shared__ double Yis[30];
   __shared__ double Zis[30];
   __shared__ double Z1s[30];
   __shared__ double Z1Errs[30];
   __shared__ double rho[30];
   __shared__ double fZWeight[30];   
 
   double Mxx=0.;
   double Myy=0.;
   double Mxy=0.;
   double Mxz=0.;
   double Myz=0.;
   double Mzz=0.;
   double wsum= 0. ;
   double wx  = 0. ;
   double wy  = 0. ;
   double wxx = 0.;
   double wxy = 0. ;


   Xs[x]    = X[x+30*y];
   Ys[x]    = Y[x+30*y];
   Z1s[x]   = Z1[x+30*y];
   Z1Errs[x]= Z1err[x+30*y];
  //         printf("blockid = %d  Z1Errs(%d) = %g \n",y, x , Z1Errs[x]);
  //   if(x < 8) result[x+8*y]=0.000;
   
  
   __syncthreads();

   Xis[x] = Xs[x]- Mx[y];
   Yis[x] = Ys[x]- My[y];
   Zis[x] = Xis[x]*Xis[x] + Yis[x]*Yis[x];
   rho[x] = sqrt(Zis[x]);

   Mxy+= Xis[x]*Yis[x]/M0[y];
   Mxx+= Xis[x]*Xis[x]/M0[y];
   Myy+= Yis[x]*Yis[x]/M0[y];
   Mxz+= Xis[x]*Zis[x]/M0[y];
   Myz+= Yis[x]*Zis[x]/M0[y];
   Mzz+= Zis[x]*Zis[x]/M0[y];

 
 //  printf("rho(%d) = %g \n",x , rho[x]); 
   if(Z1Errs[x]>0.001)fZWeight[x] = 1/(Z1Errs[x]*Z1Errs[x]);
   else {
   //  printf("Z1Err(%d) = %g \n",x , Z1Errs[x]); 
     fZWeight[x] = 0.0;
   
   }
 
   wsum+= fZWeight[x];
   wx  += fZWeight[x]*rho[x];
   wy  += fZWeight[x]*Z1s[x];
   wxx += fZWeight[x]*Z1s[x];
   wxy += fZWeight[x]*rho[x]*Z1s[x];

 
   __syncthreads();

  if(x<1) { 
//  printf("Result =%f   %f  %f %f  %f  \n" ,wsum, wxy, wxx, wx, wy );
   int t= NewtonAllD(Mxx, Myy, Mxy, Mxz, Myz, Mzz, result);
  double mm = 0.;
  double qq = 0.;  
  double det = wsum * wxx - wx * wx;
   if (det>0.00001) {
      mm = (wxy * wsum - wy * wx) / det;
      qq = (wy * wxx - wxy * wx) / det;
   }else {mm=1000.; qq=1000.;} 

   result[3+8*y]=-mm;
   result[4+8*y]=qq;
 
   double r1 ;
   double chi2 = 0.;
  
   for(int i=0; i < 30; i++) {
     r1   = Z1s[i] + result[3+8*y] * rho[i] - result[4+8*y];
     chi2 += fZWeight[i] * (r1 * r1);
   }
   result[5+8*y]=chi2;

   if (det>0.00001){
     double varsq = sqrt(chi2/25.);
     result[6+8*y] = varsq * sqrt( wsum / det );
     result[7+8*y] = varsq * sqrt( wxx / det );
   }else{
     result[6+8*y] = 0;
     result[7+8*y] = 0;
   }

  }
  
  
}




#endif // #ifndef _TRACKFIT_KERNEL_H_ 










