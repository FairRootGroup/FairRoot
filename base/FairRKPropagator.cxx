#include "FairRKPropagator.h"


#include "TMath.h"
#include "TVector3.h"

ClassImp(FairRKPropagator);

//______________________________________________________________________________
FairRKPropagator::FairRKPropagator(FairField* field)
  : TObject(),
    fMaxStep(10.0),
    fMagField (field)
{
  //  fMaxStep=10.0;
}
//______________________________________________________________________________
FairRKPropagator::~FairRKPropagator()
{
  // Destructor.
}
//______________________________________________________________________________
void FairRKPropagator::PropagatToPlane(Double_t Charge, Double_t* vecRKIn, Double_t* vec1, Double_t* vec2, Double_t* vec3, Double_t* vecOut)
{
  /**
  vec1 & vec2 are vectors on the plane
  vec3 a point on the plane
  */
  Double_t Norm[3];
  Double_t Mag;
  Double_t dist[3];
  Double_t distance[3];
  Double_t vecRKoutT[7];

  Norm[0]=vec1[1]*vec2[2] - vec2[2] * vec2[1]; // a2b3 − a3b2,
  Norm[1]=vec1[2]*vec2[0] - vec1[0] * vec2[2]; // a3b1 − a1b3;
  Norm[2]=vec1[0]*vec2[1] - vec1[1] * vec2[0];

  Mag=TMath::Sqrt(Norm[0]*Norm[0]+Norm[1]*Norm[1]+Norm[2]*Norm[2]);

  // printf(" Mag = %f   \n ", Mag);

  Norm[0]=Norm[0]/Mag;
  Norm[1]=Norm[1]/Mag;
  Norm[2]=Norm[2]/Mag;
  //   printf(" after normalization : Normal = %f %f %f  \n ", Norm[0],Norm[1],Norm[2]);

  dist[0]=vecRKIn[0]-vec3[0];
  dist[1]=vecRKIn[1]-vec3[1];
  dist[2]=vecRKIn[2]-vec3[2];

  distance[0]=Norm[0]*dist[0];
  distance[1]=Norm[1]*dist[1];
  distance[2]=Norm[2]*dist[2];
//   printf(" distance = %f %f %f  \n ", distance[0],distance[1],distance[2]);
  Double_t diff = TMath::Abs(distance[0]+distance[1]+distance[2]);
  fMaxStep = diff;
  Double_t res = 100.0;
  Double_t res_old = 100.0;

  Double_t vecRKOut[7];
  // for (Int_t i=0; i< 7; i++) {vecRKOut[i]=0;}
  Int_t nIter=0;

  //  printf("I am in CPU code  %f %f  %f  res= %f  diff = %f \n ", vecRKIn[0], vecRKIn[1],vecRKIn[2], res, diff);

  do {
    Step(Charge,vecRKIn,vecRKOut);
    dist[0]=(vecRKOut[0]-vec3[0])*Norm[0];
    dist[1]=(vecRKOut[1]-vec3[1])*Norm[1];
    dist[2]=(vecRKOut[2]-vec3[2])*Norm[2];
    fMaxStep=TMath::Sqrt(dist[0]*dist[0]+dist[1]*dist[1]+dist[2]*dist[2]);
    res=TMath::Abs(fMaxStep/diff);
    //   printf("After %i step %f %f %f  res = %f \n", nIter ,vecRKOut[0], vecRKOut[1],vecRKOut[2] , res);
    if( res< 0.001 || res >res_old ) {
      break;
    } else {
      for (Int_t i=0; i< 3; i++) {
        vecRKIn[i]=vecRKOut[i];
        vecRKoutT[i]=vecRKOut[i];
      }
      res_old=res;
    }
    if(nIter++>1000) { break; }
  } while(1);
//  printf("The results is  %f %f %f  , no of iter %i \n", vecRKOut[0],vecRKOut[1],vecRKOut[2], nIter);
//  printf("\n");
  for (Int_t i=0; i< 3; i++) {
    if (res > res_old) { vecOut[i]=vecRKoutT[i]; }
    else { vecOut[i]=vecRKOut[i]; }
  }
}
//______________________________________________________________________________
void FairRKPropagator::Propagat(Double_t Charge, Double_t* vecRKIn, Double_t* Pos)
{
  Double_t diff = Pos[2] - vecRKIn[2];
  fMaxStep = diff/25;
  Double_t res_old= diff;
  Double_t res = 100.0;
  Double_t vecRKOut[7];
  Double_t vecRKOutT[7];
  for (Int_t i=0; i< 7; i++) {vecRKOut[i]=0; vecRKOutT[i]=0;}

  Int_t nIter=0;
  do {
    Step(Charge,vecRKIn,vecRKOut);
    res=(vecRKOut[2]-Pos[2])/diff;
    if( TMath::Abs(res)< 0.01 || res >res_old ) {
      break;
    } else {
      for (Int_t i=0; i< 3; i++) {
        vecRKOutT[i]=vecRKOut[i];
        vecRKIn[i]=vecRKOut[i];
      }
    }
    if(nIter++>1000) { break; }
  } while(1);
  if (res > res_old) for (Int_t k=0; k< 7; k++) { vecRKOut[k]=vecRKOutT[k]; }
  for (Int_t k=0; k< 3; k++) { printf(" vecRKOut[%i] =%f ", k, vecRKOut[k] ); }
  printf("\n");
}
//______________________________________________________________________________
void FairRKPropagator::Step(Double_t Charge, Double_t* vecRKIn, Double_t* vecOut)
{

  Double_t vecRKOut[7];
  for (Int_t i=0; i< 7; i++) { vecRKOut[i]=0; }
//  for (Int_t i=0; i< 7; i++) printf( "vectRKIn(%i)=%f  \n",i ,vecRKIn[i]);
//  printf(" ---------------------------------------------------------------- \n");
  OneStepRungeKutta(Charge,fMaxStep, vecRKIn, vecRKOut);
  //  printf(" now at     x=%f  y=%f  z=%f \n", vecRKOut[0],vecRKOut[1],vecRKOut[2]);
  vecOut[0] = vecRKOut[0];
  vecOut[1] = vecRKOut[1];
  vecOut[2] = vecRKOut[2];
  vecOut[6] = vecRKOut[6];
  vecOut[3] = vecRKOut[3]/vecOut[6];
  vecOut[4] = vecRKOut[4]/vecOut[6];
  vecOut[5] = vecRKOut[5]/vecOut[6];

}

//______________________________________________________________________________
void FairRKPropagator::OneStepRungeKutta(Double_t charge, Double_t step,
    Double_t* vect, Double_t* vout)
{

  // Wrapper to step with method RungeKutta.

  /// ******************************************************************
  /// *                *
  /// *  Runge-Kutta method for tracking a particle through a magnetic *
  /// *  field. Uses Nystroem algorithm (See Handbook Nat. Bur. of   *
  /// *  Standards, procedure 25.5.20)         *
  /// *                *
  /// *  Input parameters            *
  /// * CHARGE    Particle charge        *
  /// * STEP    Step size          *
  /// * VECT    Initial co-ords,direction cosines,momentum   *
  /// *  Output parameters             *
  /// * VOUT    Output co-ords,direction cosines,momentum  *
  /// *  User routine called             *
  /// * CALL GUFLD(X,F)            *
  /// *                *
  /// *    ==>Called by : <USER>, GUSWIM         *
  /// * Authors    R.Brun, M.Hansroul  *********     *
  /// *      V.Perevoztchikov (CUT STEP implementation)  *
  /// *                *
  /// *                *
  /// ******************************************************************

  Double_t h2, h4, f[4];
  Double_t xyzt[3], a=0, b=0, c=0, ph,ph2;
  Double_t secxs[4],secys[4],seczs[4]; //hxp[3];
  Double_t /*g1 , g2, g3, g4, g5, g6,*/ ang2, dxt, dyt, dzt;
  Double_t est, at, bt, ct, cba;
//  Double_t /*f1, f2, f3, f4, rho, tet, hnorm, hp, rho1, sint, cost*/;

  Double_t x=0;
  Double_t y=0;
  Double_t z=0;

  Double_t xt;
  Double_t yt;
  Double_t zt;

//  Double_t maxit = 1992;
  Double_t maxit = 10;
  Double_t maxcut = 11;

  const Double_t hmin   = 1e-4; // !!! MT ADD,  should be member
  const Double_t kdlt   = 1e-3; // !!! MT CHANGE from 1e-4, should be member
  const Double_t kdlt32 = kdlt/32.;
  const Double_t kthird = 1./3.;
  const Double_t khalf  = 0.5;
  const Double_t kec    = 2.9979251e-3;
  const Double_t kpisqua = 9.86960440109;
  /*  const Int_t kix  = 0;
    const Int_t kiy  = 1;
    const Int_t kiz  = 2;
    const Int_t kipx = 3;
    const Int_t kipy = 4;
    const Int_t kipz = 5;
  */
  // *.
  // *.    ------------------------------------------------------------------
  // *.
  // *             this constant is for units cm,gev/c and kgauss
  // *
  Int_t iter = 0;
  Int_t ncut = 0;
  for(Int_t j = 0; j < 7; j++) {
    vout[j] = vect[j];
  }

  Double_t pinv   = kec * charge / vect[6];
  Double_t tl = 0.;
  Double_t h = step;
  Double_t rest;

  do {
    rest  = step - tl;
    printf(" Step  no. %i  x=%f  y=%f  z=%f  px/p = %f  py/p =%f  pz/p= %f \n", iter, x,y,z,a,b,c);
    if (TMath::Abs(h) > TMath::Abs(rest)) {
      h = rest;
    }


    fMagField->GetFieldValue( vout, f);
    f[0] = -1.0*f[0];
    f[1] = -1.0*f[1];
    f[2] = -1.0*f[2];


//    printf(" Field Values     x=%f  y=%f  z=%f \n", f[0],f[1],f[2]);
//    f[0] = -fH.fB.fX;
//    f[1] = -fH.fB.fY;
//    f[2] = -fH.fB.fZ;

    // * start of integration
    x      = vout[0];
    y      = vout[1];
    z      = vout[2];
    a      = vout[3];
    b      = vout[4];
    c      = vout[5];

    h2     = khalf * h;
    h4     = khalf * h2;
    ph     = pinv * h;
    ph2    = khalf * ph;

//   printf(" -------------------------------------------  h2 = %f\n",h2);

    secxs[0] = (b * f[2] - c * f[1]) * ph2;
    secys[0] = (c * f[0] - a * f[2]) * ph2;
    seczs[0] = (a * f[1] - b * f[0]) * ph2;
    ang2 = (secxs[0]*secxs[0] + secys[0]*secys[0] + seczs[0]*seczs[0]);
    if (ang2 > kpisqua) { break; }

    dxt    = h2 * a + h4 * secxs[0];
    dyt    = h2 * b + h4 * secys[0];
    dzt    = h2 * c + h4 * seczs[0];
    xt     = x + dxt;
    yt     = y + dyt;
    zt     = z + dzt;
//   printf(" Position 1 at  xt=%f  yt=%f  zt=%f  \n", xt, yt, zt);
//   printf(" differance     dxt=%f  dyt=%f  dzt=%f  \n", dxt, dyt, dzt);
    // * second intermediate point
    est = TMath::Abs(dxt) + TMath::Abs(dyt) + TMath::Abs(dzt);
    if (est > h) {
      if (ncut++ > maxcut) { break; }
      h *= khalf;
      continue;
    }

    xyzt[0] = xt;
    xyzt[1] = yt;
    xyzt[2] = zt;

    fMagField->GetFieldValue( xyzt, f);

    f[0] = -f[0];
    f[1] = -f[1];
    f[2] = -f[2];


//    printf(" Field Values  at  x=%f  y=%f  z=%f ,  Bx=%f By=%f Bz=%f  \n", xyzt[0], xyzt[1], xyzt[2] ,f[0],f[1],f[2]);
//    fH.fB = fMagFieldObj->GetField(xt, yt, zt);
//    f[0] = -fH.fB.fX;
//    f[1] = -fH.fB.fY;
//    f[2] = -fH.fB.fZ;




    at     = a + secxs[0];
    bt     = b + secys[0];
    ct     = c + seczs[0];

    secxs[1] = (bt * f[2] - ct * f[1]) * ph2;
    secys[1] = (ct * f[0] - at * f[2]) * ph2;
    seczs[1] = (at * f[1] - bt * f[0]) * ph2;
    at     = a + secxs[1];
    bt     = b + secys[1];
    ct     = c + seczs[1];
    secxs[2] = (bt * f[2] - ct * f[1]) * ph2;
    secys[2] = (ct * f[0] - at * f[2]) * ph2;
    seczs[2] = (at * f[1] - bt * f[0]) * ph2;
    dxt    = h * (a + secxs[2]);
    dyt    = h * (b + secys[2]);
    dzt    = h * (c + seczs[2]);
    xt     = x + dxt;
    yt     = y + dyt;
    zt     = z + dzt;
    at     = a + 2.*secxs[2];
    bt     = b + 2.*secys[2];
    ct     = c + 2.*seczs[2];
    //  printf(" Position 2 at  xt=%f  yt=%f  zt=%f  \n", xt, yt, zt);

    est = TMath::Abs(dxt)+TMath::Abs(dyt)+TMath::Abs(dzt);
    if (est > 2.*TMath::Abs(h)) {
      if (ncut++ > maxcut) { break; }
      h *= khalf;
      continue;
    }

    xyzt[0] = xt;
    xyzt[1] = yt;
    xyzt[2] = zt;

    fMagField->GetFieldValue( xyzt, f);
    f[0] = -1.0*f[0];
    f[1] = -1.0*f[1];
    f[2] = -1.0*f[2];

    //  fH.fB = fMagFieldObj->GetField(xt, yt, zt);
    //  f[0] = -fH.fB.fX;
    //  f[1] = -fH.fB.fY;
    //  f[2] = -fH.fB.fZ;

    z      = z + (c + (seczs[0] + seczs[1] + seczs[2]) * kthird) * h;
    y      = y + (b + (secys[0] + secys[1] + secys[2]) * kthird) * h;
    x      = x + (a + (secxs[0] + secxs[1] + secxs[2]) * kthird) * h;
    //  printf(" Position 3 at  x=%f  y=%f  z=%f  \n", x, y, z);
    secxs[3] = (bt*f[2] - ct*f[1])* ph2;
    secys[3] = (ct*f[0] - at*f[2])* ph2;
    seczs[3] = (at*f[1] - bt*f[0])* ph2;
    a      = a+(secxs[0]+secxs[3]+2. * (secxs[1]+secxs[2])) * kthird;
    b      = b+(secys[0]+secys[3]+2. * (secys[1]+secys[2])) * kthird;
    c      = c+(seczs[0]+seczs[3]+2. * (seczs[1]+seczs[2])) * kthird;

    est    = TMath::Abs(secxs[0]+secxs[3] - (secxs[1]+secxs[2]))
             + TMath::Abs(secys[0]+secys[3] - (secys[1]+secys[2]))
             + TMath::Abs(seczs[0]+seczs[3] - (seczs[1]+seczs[2]));

    if (est > kdlt && TMath::Abs(h) > hmin) {
      if (ncut++ > maxcut) { break; }
      h *= khalf;
      continue;
    }

    ncut = 0;
    // * if too many iterations, go to helix
    if (iter++ > maxit) { break; }

    tl += h;
    if (est < kdlt32) {
      h *= 2.;
    }
    cba    = 1./ TMath::Sqrt(a*a + b*b + c*c);
    vout[0] = x;
    vout[1] = y;
    vout[2] = z;
    vout[3] = cba*a;
    vout[4] = cba*b;
    vout[5] = cba*c;


    rest = step - tl;
    //  printf(" Position 4 at  x=%f  y=%f  z=%f  Step = %f  \n", x, y, z, step );

    if (step < 0.) { rest = -rest; }
    if (rest < 1.e-5*TMath::Abs(step)) { return; }

  } while(1);

  // angle too big, use helix
  /*
    f1  = f[0];
    f2  = f[1];
    f3  = f[2];
    f4  = TMath::Sqrt(f1*f1+f2*f2+f3*f3);
    rho = -f4*pinv;
    tet = rho * step;

    hnorm = 1./f4;
    f1 = f1*hnorm;
    f2 = f2*hnorm;
    f3 = f3*hnorm;

    hxp[0] = f2*vect[kipz] - f3*vect[kipy];
    hxp[1] = f3*vect[kipx] - f1*vect[kipz];
    hxp[2] = f1*vect[kipy] - f2*vect[kipx];

    hp = f1*vect[kipx] + f2*vect[kipy] + f3*vect[kipz];

    rho1 = 1./rho;
    sint = TMath::Sin(tet);
    cost = 2.*TMath::Sin(khalf*tet)*TMath::Sin(khalf*tet);

    g1 = sint*rho1;
    g2 = cost*rho1;
    g3 = (tet-sint) * hp*rho1;
    g4 = -cost;
    g5 = sint;
    g6 = cost * hp;

    vout[kix] = vect[kix] + g1*vect[kipx] + g2*hxp[0] + g3*f1;
    vout[kiy] = vect[kiy] + g1*vect[kipy] + g2*hxp[1] + g3*f2;
    vout[kiz] = vect[kiz] + g1*vect[kipz] + g2*hxp[2] + g3*f3;

    vout[kipx] = vect[kipx] + g4*vect[kipx] + g5*hxp[0] + g6*f1;
    vout[kipy] = vect[kipy] + g4*vect[kipy] + g5*hxp[1] + g6*f2;
    vout[kipz] = vect[kipz] + g4*vect[kipz] + g5*hxp[2] + g6*f3;
  */

}
