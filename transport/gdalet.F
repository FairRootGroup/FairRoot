c------------------------------------------------------------------------------
	real function vdmform(x,rmas,isw) ! VDM formfactor
	real*4 x, rmas, dalit, rhom	  ! masses in MeV
        real*4 f, delta
	parameter (rhom=770.0)
C
	vdmform = 0.0
	if (x.ge.rmas) return
        if (x.lt.2.0*0.511) return

        f = sqrt(1.-4.*(0.511/x)**2) * (1.+2.*(0.511/x)**2)
        if (isw.eq.1) then       ! pseudo-scalar meson -> gamma e+ e-
	   dalit = ((1.-(x/rmas)**2)**3/(x/rmas))*1./(1.-(x/rhom)**2)**2
	   vdmform = 8.2e-4*dalit*f
        else if (isw.eq.2) then  ! vector meson -> pi0 e+ e-
           delta = (135.0/rmas)**2
           bracket = (1.+(x/rmas)**2/(1.-delta))**2
     +                - 4.*(x/rmas)**2/(1.-delta)**2
           if(bracket.le.0.0) return
           ff2 = 0.64**4/((0.65**2-(x/1000.)**2)**2 + (0.042*0.65)**2)
           dalit = (bracket**1.5)/(x/rmas)*ff2
           vdmform = 8.2e-4*dalit*f
        end if
C
        return
	end
c------------------------------------------------------------------------------
	real function qedform(x,rmas,isw) ! QED formfactor
	real*4 x, rmas, dalit		  ! masses in MeV
        real*4 f, delta
C
	qedform = 0.0
	if (x.ge.rmas) return
        if (x.lt.2.0*0.511) return

        f = sqrt(1.-4.*(0.511/x)**2) * (1.+2.*(0.511/x)**2)
        if (isw.eq.1) then       ! pseudo-scalar meson
	   dalit = ((1.-(x/rmas)**2)**3/(x/rmas))
	   qedform = 8.2e-4*dalit*f
        else if (isw.eq.2) then  ! vector meson
           delta = (135.0/rmas)**2
           bracket = (1.+(x/rmas)**2/(1.-delta))**2
     +                - 4.*(x/rmas)**2/(1.-delta)**2
           if(bracket.le.0.0) return
           dalit = (bracket**1.5)/(x/rmas)
           qedform = 8.2e-4*dalit*f
        end if
C
        return
	end
c------------------------------------------------------------------------------

      SUBROUTINE GDALET(XM0,XM1,XM2,XM3,PCM,IDH)
C.
C.    ******************************************************************
C.    *                                                                *
C.    *   Dalitz decay of pi0, eta                                     *
C.    *                                                                *
C.    *                                                                *
C.    *    ==>Called by : GDECAY                                       *
C.    *       mod. from gdec3; including eta formfactor calc. in VDM)  *
C.    *       W.Schoen 12.8.96                                         *
C.    *       tritouille par R.H. 24.3.97 and 28.8.97 and 22.8.2000    *
C.    ******************************************************************
      IMPLICIT NONE
      REAL FMASS, PI2, CT1, ST1, GINV, XINV, YINV
      REAL BETINV, RC, Q1, Q2, Q3, G1, G2, EM, XM0, XM1, XM2, XM3
      REAL GAM, E1, E2, E3, PGSQ, CTST, STST, F1, F2
      REAL PCM(4,3)
      REAL XMETA, RNDM(4)
      INTEGER IDH
      REAL dalitz_evgen
*

      PI2 = 2.*3.141592654
C--------------------------------------------------------
C     SIMULATION OF SECONDARY PARTICLE MOMENTA
C     IN THE REST FRAME OF PARENT PARTICLE
C--------------------------------------------------------
      RC = (2.*XM2/(XM0-XM1))**2
C      XINV = HRNDM1(IDH)/1000.     ! convert to GeV here

      CALL GRNDM(RNDM,4)
      XINV = dalitz_evgen(IDH)
      XINV = (XINV/(XM0-XM1))**2
      YINV = SQRT(ABS(1. - RC/XINV))*(2.*RNDM(2) - 1.)
      IF(RNDM(1).LT.0.5) YINV = -YINV
      E2 = (XM0-XM1)*(XINV+1.+YINV*(1.-XINV))/4.
      E3 = (XM0-XM1)*(XINV+1.-YINV*(1.-XINV))/4.
      E1 = XM0-E2-E3
 
      Q3 = SQRT(E3*E3-XM2*XM3)
      Q2 = SQRT(E2*E2-XM2*XM3)
      Q1 = SQRT(E1*E1-XM1*XM1)
      PGSQ = ( (XM0**2-XM1**2)*(1.-XINV)/(2.*XM0) )**2
      CTST = (PGSQ-Q3**2-Q2**2)/(2.*Q3*Q2)
      STST = SQRT(ABS(1.-CTST**2))
 
      CT1 = 2.*RNDM(2)-1.
      ST1 = SQRT(ABS(1.-CT1*CT1))
 
      F1 = PI2*RNDM(3)
 
      PCM(1,3) = Q3*ST1*COS(F1)
      PCM(2,3) = Q3*ST1*SIN(F1)
      PCM(3,3) = Q3*CT1
      PCM(4,3) = E3
      F2 = PI2*RNDM(4)
 
      PCM(1,2) = Q2*( STST*SIN(F2)*CT1*COS(F1) + STST*COS(F2)*SIN(F1)
     &             + CTST*ST1*COS(F1))
      PCM(2,2) = Q2*( STST*SIN(F2)*CT1*SIN(F1) - STST*COS(F2)*COS(F1)
     &             + CTST*ST1*SIN(F1))
      PCM(3,2) = Q2*(-STST*SIN(F2)*ST1 + CTST*CT1)
      PCM(4,2) = E2
 
      PCM(1,1) = -PCM(1,3)-PCM(1,2)
      PCM(2,1) = -PCM(2,3)-PCM(2,2)
      PCM(3,1) = -PCM(3,3)-PCM(3,2)
      PCM(4,1) =  E1

      RETURN
      END









