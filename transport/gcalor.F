*CMZ :  1.05/00 08/07/99  11.14.36  by  Christian Zeitnitz
*-- Author : Christian Zeitnitz
      SUBROUTINE GCALOR
********************************************************************
*                                                                  *
* PURPOSE: GEANT interface to CALOR                                *
*                                                                  *
* CALLED BY : GUHADR                                               *
*                                                                  *
* INPUT :  particle, material, and probabilities via GEANT common  *
*                                                                  *
* OUTPUT : COMMON GCKING, DESTEP                                   *
*          KCALL  = -1  : Nothing done                             *
*                 =  0  : NMTC has been called                     *
*                 =  1  : MICAP has been called                    *
*                 =  2  : HETC SKALE has been called               *
*                 =  3  : FLUKA has been called                    *
*                                                                  *
* AUTHOR : C.Zeitnitz (University of Arizona)                      *
*                                                                  *
********************************************************************
C.
C. --- GEANT Commons
*KEEP,GCBANK.
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
*KEEP,GCKING.
      INTEGER MXGKIN
      PARAMETER (MXGKIN=100)
      COMMON/GCKING/KCASE,NGKINE,GKIN(5,MXGKIN),
     +                           TOFD(MXGKIN),IFLGK(MXGKIN)
      INTEGER       KCASE,NGKINE ,IFLGK,MXPHOT,NGPHOT
      REAL          GKIN,TOFD,XPHOT
C
      PARAMETER (MXPHOT=800)
      COMMON/GCKIN2/NGPHOT,XPHOT(11,MXPHOT)
C
      COMMON/GCKIN3/GPOS(3,MXGKIN)
      REAL          GPOS
C
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
*KEEP,GCTRAK.
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,GSECTI.
      COMMON/GSECTI/ AIEL(20),AIIN(20),AIFI(20),AICA(20),ALAM,K0FLAG
      INTEGER K0FLAG
      REAL AIEL,AIIN,AIFI,AICA,ALAM
C
*KEEP,GCONST.
      COMMON/GCONST/PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      COMMON/GCONSX/EMMU,PMASS,AVO
C
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
*KEND.
C --- CALOR - GEANT Interface common
*KEEP,CALGEA.
C***************************************************************
C
C       CALOR-GEANT Interface common
C
C parameters of incident particle :
C                   IPinc   = particle type a la CALOR
C                   Einc    = kinetic energy
C                   Uinc(3) = direction cosines
C material parameters:
C                   NCEL    = number of elements in mixture (NMTC)
C                             GEANT material no. for MICAP
C                   Amed(I) = mass number
C                   Zmed(I) = charge number
C                   Dmed(I) = Atoms/cm**3 * 1E-24
C                   Hden    = Atoms/cm**3 * 1E-24
C                             of H-Atoms in mixture
C
C particle stack:
C            NPHETC           = number of particles
C            Ekinet(1:NPHETC) = kinetic energy of part.
C            IPCAL(1:NPHETC)  = particle type a la CALOR (extended)
C            UCAL(1:NPHETC,3) = direction cosines
C            CALTIM(1:NPHETC) = age of particle (nsec)
C
C            ATARGT = A no. of target nucleus
C            ZTARGT = Z no. of target nucleus
C
C return of residual nucleus information
C            NRECOL  = no. of heavy recoil products
C            Amed(I) = mass number of residual nucleus
C            Zmed(I) = charge number "          "
C            EXmed   = exitation energy of nucleus
C            ERmed(I)= recoil energy of nucleus
C            IntCal  = type of interaction (GEANT NAMEC index)
C return of cross section of hadronic interaction (CALSIG called)
C            SIG =  x-section
C
C set by CALSIG:
C            ICPROC = -1   undefined
C                   =  0   NMTC called for cross-section
C                   =  1   MICAP called for cross-section
C                   =  2   SKALE(NMTC at 3 GeV) called for cross-section
C                   =  3   FLUKA called for cross-section
C            KCALL : same coding as ICPROC, but is only valid after a
C                    call to GCALOR
C       18/8/92  C.Zeitnitz University of Arizona
C****************************************************************
C
      PARAMETER(EMAXP  = 3.495)
      PARAMETER(EMAXPI = 2.495)
C transition upper limit (GeV) NMTC-FLUKA
      PARAMETER(ESKALE = 10.0)
      PARAMETER(MXCP = 300)
C
      COMMON/ CALGEA / IPINC  , EINC       , UINC(3)   ,NCEL        ,
     +                 HDEN   , AMED(100)  , ZMED(100) ,DMED(100)   ,
     +                 NPHETC ,EKINET(MXCP),IPCAL(MXCP),UCAL(MXCP,3),
     +                 INTCAL , EXMED      , ERMED(100),SIG         ,
     +                 CALTIM(MXCP), ICPROC, NRECOL    ,KCALL       ,
     +                 ATARGT , ZTARGT
C
*KEEP,CERRCM.
      LOGICAL CERRF
      COMMON/CERRCM/CERRF,IERRU
*KEEP,CAMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
*KEND.
C
C  Avogadro number multiplied by 1.E-24
      PARAMETER(XNAVO = 0.60221367)
C
      DIMENSION NNPART(12)
      LOGICAL INIT,GOFLUK,DOSKAL,FMICAP,SKALEF,NABSOR,FSTOP
      DOUBLE PRECISION DECIN,DMASS
C
      DATA INIT /.TRUE./
      SAVE INIT
C
      IF ( INIT ) THEN
C
C     initialize CALOR
         CALL CALINI
C
         INIT = .FALSE.
C
      ENDIF
      KCALL = -1
C
C get CALOR particle type
      IPINC = -1
      IF(IPART .LE. 48 )  IPINC = IGECAL(IPART)
C
C energy in MeV

      EINC   =GEKIN * 1000.0
      UINC(1)=VECT(4)
      UINC(2)=VECT(5)
      UINC(3)=VECT(6)
      KCASE=NAMEC(12)
      NGKINE = 0
      NABSOR = .FALSE.
      FSTOP = .FALSE.
C ----- particle has to be stopped ? -------
      IF(GEKIN.LT.CUTHAD.AND.ITRTYP.EQ.4) THEN
         FSTOP = .TRUE.
         ISTOP = 2
         IF(IPART .EQ. 9) THEN
            NABSOR = .TRUE.
            ISTOP = 1
            EINC = 1.0
            IF(GEKIN.GT.EINC/1000.) DESTEP = DESTEP + GEKIN - EINC/
     +      1000.0
            GEKIN = 0.0
            VECT(7) = 0.0
            KCASE = NAMEC(18)
            NMEC = NMEC + 1
            LMEC(NMEC) = 18
         ELSE
            DESTEP = DESTEP + GEKIN
            GEKIN = 0.0
            VECT(7) = 0.0
            IF(IPART.EQ.8.OR.IPART.EQ.11.OR.IPART.EQ.12) THEN
              CALL G3DECAY
              KCASE = NAMEC(5)
              NMEC = NMEC + 1
              LMEC(NMEC) = 5
            ENDIF
            RETURN
         ENDIF
      ELSE IF(GEKIN.LT.CUTNEU.AND.IPART.EQ.13) THEN
         IF(GEKIN.LT.1.E-14) EINC=1.E-11
         ISTOP = 1
         NABSOR = .TRUE.
      ENDIF
CZZZ      IF(ISTOP.EQ.2.OR.GEKIN.EQ.0.0) RETURN
C
C ------------- check if FLUKA has to be called ---------
C ------------------------------------------------- Goto FLUKA ?
C
      DOSKAL = (IPINC.EQ.0 .OR. IPINC.EQ.1) .AND. GEKIN.GT.EMAXP
      DOSKAL = DOSKAL .OR. (GEKIN .GT. EMAXPI .AND. (IPINC .GT. 1))
      IF(ICPROC.GE.0) THEN
         GOFLUK = ICPROC.EQ.3 .OR. IPINC.EQ.-1
         DOSKAL = DOSKAL .AND. ICPROC.EQ.2
      ELSE
         GOFLUK = IPINC .EQ. -1 .OR. GEKIN .GE. ESKALE
         DOSKAL = DOSKAL .AND. .NOT.GOFLUK
         GOFLUK = GOFLUK .OR. (DOSKAL.AND.SKALEF(IPINC,GEKIN,ESKALE))
         GOFLUK = GOFLUK .AND. .NOT.FSTOP .AND. .NOT.NABSOR
      ENDIF
      ICPROC = -1
C ------------------------------------------- call FLUKA
      IF(GOFLUK) THEN
         CALL FLUFIN
         KCALL = 3
         RETURN
      ENDIF
      CERRF = .FALSE.
      IF(IPINC .EQ. 1 .AND. EINC .LE. 20.0) THEN
C MICAP needs only GEANT material number
         NCEL = NMAT
C --- low energetic neutron -> call micap
         CALL MICAP
         KCALL = 1
      ELSE
         NCEL = 1
         AMED(1) = A
         ZMED(1) = Z
         DMED(1) = DENS/A*XNAVO
         IF(INT(A) .EQ. 1) THEN
            HDEN = DMED(1)
         ELSE
            HDEN = 0.0
         ENDIF
C ------- get material parameter for a mixture---------------------
         KK=MIN1(ABS(Q(JMA+11)),100.)
         NCEL = 1
         IF(KK.GT.1) THEN
            HDEN = 0.0
            NCEL = 0
            AMOL = Q(LQ(JMIXT-1) + 2)
            DO 10 K=1,KK
               IF(NINT(Q(JMIXT+K)).EQ.1) THEN
C                           hydrogen density
                  XMOLCM = DENS/AMOL*XNAVO
                  WI = Q(JMIXT+K+2*KK)*AMOL/Q(JMIXT+K)
                  HDEN = HDEN + XMOLCM * WI
               ELSE
                  NCEL = NCEL + 1
                  AMED(NCEL) = Q(JMIXT+K)
                  ZMED(NCEL) = Q(JMIXT+K+KK)
C                                        molekuls/cm^3
                  XMOLCM = DENS/AMOL*XNAVO
C                                     number of atoms per molecule
                  WI = Q(JMIXT+K+2*KK)*AMOL/AMED(NCEL)
C                                        atoms/cm^3
                  DMED(NCEL) = XMOLCM * WI
               ENDIF
   10       CONTINUE
         ENDIF
         CALL CHETC(DOSKAL)
         KCALL = 0
         IF(DOSKAL) KCALL = 2
      ENDIF
C error ocurred in CALOR ?
      IF(CERRF) THEN
         WRITE(IERRU,'('' NEVT,IPART,Ek,NMED,ISTOP,NABSOR,FSTOP :'',   '
     +   //'          I10,I5,G15.6,2I6,2L6)') IEVENT,IPART,GEKIN,NMAT,
     +   ISTOP,NABSOR,FSTOP
      ENDIF
      ESUM =0.
      EKSUM = 0.
      PX = 0.
      PY = 0.
      PZ = 0.
      NGKINE = 0
      PSUM = 0.
C
      ZINTHA=GARNDM(6)
      SLHADR=SLENG
      STEPHA=BIG
C
      IF(NPHETC.EQ.0.AND.NABSOR) ISTOP = 2
C neutron has been absorbed -> INTCAL=18
      IF(INTCAL.EQ.18) ISTOP = 1
      IF(NPHETC.LE.0) GOTO 160
C
C too many particles in the CALOR array for GEANT
C happens sometimes with deexcitation gammas and evaporation neutrons
C simple approach to combine particles and sum up their energies, but
C forget about momentum conservation
C
      IF(NPHETC.GT.MXGKIN) THEN
   20    CONTINUE
         DO 30 I=1,12
            NNPART(I)=0
   30    CONTINUE
         NNTOT = 0
         DO 40 I=1,NPHETC
            IF(IPCAL(I).NE.-1) THEN
               NNPART(IPCAL(I)+1)=NNPART(IPCAL(I)+1)+1
               NNTOT = NNTOT + 1
            ENDIF
   40    CONTINUE
         IF(NNTOT.LE.MXGKIN) GOTO 100
         JMAX=0
         IMAX=0
         DO 50 I=1,12
            IF(JMAX.LT.NNPART(I)) THEN
               JMAX=NNPART(I)
               IPI=I-1
            ENDIF
   50    CONTINUE
         DO 60 I=1,NPHETC
            IF(IPCAL(I).EQ.IPI) GOTO 70
   60    CONTINUE
   70    I1=I
         DO 80 I=I1+1,NPHETC
            IF(IPCAL(I).EQ.IPI) GOTO 90
   80    CONTINUE
   90    I2=I
         ECINI = EKINET(I1)
         DMASS = DBLE(XMASS(IPI))*1.D3
         DECIN = DBLE(ECINI)
         PPI = SNGL(DSQRT(DECIN*DECIN + 2.D0*DECIN*DMASS))
         IPJ = IPCAL(I2)
         ECINJ = EKINET(I2)
         DECIN = DBLE(ECINJ)
         PPJ = SNGL(DSQRT(DECIN*DECIN + 2.D0*DECIN*DMASS))
         ECIN = SNGL(DBLE(ECINI)+DBLE(ECINJ)+DMASS)
         EKINET(I1) = ECIN
         PP = SNGL(DSQRT(DBLE(ECIN*ECIN) + 2.D0*DBLE(ECIN)*DMASS))
C determine new direction cosines
         UCAL(I1,1) = (PPI*UCAL(I1,1)+PPJ*UCAL(I2,1))/PP
         UCAL(I1,2) = (PPI*UCAL(I1,2)+PPJ*UCAL(I2,2))/PP
         UCAL(I1,3) = (PPI*UCAL(I1,3)+PPJ*UCAL(I2,3))/PP
         USUM = SQRT(UCAL(I1,1)**2+UCAL(I1,2)**2+UCAL(I1,3)**2)
C normalize direction cosines
         IF(USUM.LT.0.0001) THEN
C direction is isotropic distributed
            CALL AZIRN2(SINA,COSA)

            COSP = SFLRAF2(DUM)
            SINP = SQRT(1.0-COSP*COSP)
            UCAL(I1,1) = SINP * COSA
            UCAL(I1,2) = SINP * SINA
            UCAL(I1,3) = COSP
         ELSE
            UCAL(I1,1) = UCAL(I1,1)/USUM
            UCAL(I1,2) = UCAL(I1,2)/USUM
            UCAL(I1,3) = UCAL(I1,3)/USUM
         ENDIF
C particle I2 vanished
         IPCAL(I2)=-1
         GOTO 20
C end of particle combination
  100    CONTINUE
C sort particles
         I2=NPHETC
         DO 120 I = 1,NPHETC
            IF(I.GE.I2) GOTO 130
            IF(IPCAL(I).EQ.-1) THEN
               DO 110 J = I2,I,-1
                  IF(IPCAL(J).NE.-1) THEN
                     IPCAL(I) = IPCAL(J)
                     EKINET(I) = EKINET(J)
                     UCAL(I,1) = UCAL(J,1)
                     UCAL(I,2) = UCAL(J,2)
                     UCAL(I,3) = UCAL(J,3)
                     I2 = J-1
                     GOTO 120
                  ENDIF
  110          CONTINUE
            ENDIF
  120    CONTINUE
  130    CONTINUE
         NPHETC=MXGKIN
      ENDIF
C
      IF(INTCAL.LT.1.OR.INTCAL.GT.30) INTCAL=12
      KCASE = NAMEC(INTCAL)
      IF(INTCAL.NE.12) THEN
        NMEC = NMEC + 1
        LMEC(NMEC) = INTCAL
      ENDIF
      DO 140 I=1,NPHETC
         IP=IPCAL(I)
         IGPART=ICALGE(IP)
         IF ( IGPART.EQ.0 ) THEN
            PRINT*,'>>> ERROR GCALOR: Particle type ',IP, ' not '
     +      //'implemented in GEANT'
            GOTO 140
         ENDIF
C
C store particle
         ECIN = EKINET(I)/1000.0
         IF(ECIN.LT.1.E-15) GOTO 140
         DECIN = DBLE(ECIN)
         DMASS = DBLE(XMASS(IP))
         PP = SNGL(DSQRT(DECIN*DECIN + 2.0D0*DECIN*DMASS))
         PX = PX + PP*UCAL(I,1)
         PY = PY + PP*UCAL(I,2)
         PZ = PZ + PP*UCAL(I,3)
C generated particle eq incoming
         IF(NPHETC.EQ.1 .AND. IGPART.EQ.IPART) THEN
            VECT(4) = UCAL(I,1)
            VECT(5) = UCAL(I,2)
            VECT(6) = UCAL(I,3)
            VECT(7) = PP
            GEKIN = ECIN
            GETOT = SNGL(DECIN + DMASS)
            TOFG = TOFG + CALTIM(I)
            ISTOP = 0
            IF(NABSOR) ISTOP = 2
            GOTO 160
         ENDIF
C
         NGKINE=NGKINE+1
         GKIN(1,NGKINE) = PP*UCAL(I,1)
         GKIN(2,NGKINE) = PP*UCAL(I,2)
         GKIN(3,NGKINE) = PP*UCAL(I,3)
C the total energy is critical for ECIN below 1.E-8 GeV because of
C single precision of GKIN (normalization when mass is added)!!
C luckely GEANT does use only the momentum components when storing the
C particle on the stack.
         GKIN(4,NGKINE) = SNGL(DECIN+DMASS)
         GKIN(5,NGKINE) = FLOAT(IGPART)
         TOFD(NGKINE)   = CALTIM(I)
         GPOS(1,NGKINE) = VECT(1)
         GPOS(2,NGKINE) = VECT(2)
         GPOS(3,NGKINE) = VECT(3)
         IF(NGKINE.GE.MXGKIN) GOTO 150
C
  140 CONTINUE
  150 CONTINUE
C particle lost its identity
      ISTOP=1
  160 CONTINUE
C
C
      NGKINE = MIN(NGKINE,MXGKIN)
C
C score kinetic energy of recoil nucleus (given in MeV)
CZ      DESTEP = DESTEP + ERMED * 1.E-3
  170 RETURN
      END
*CMZ :  1.05/02 16/05/2000  17.18.13  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   27/05/92
      SUBROUTINE CALINI
C**************************************************************
C
C           INITIALIZATION of CALOR
C           =======================
C
C  Called by : CALSIG , GCALOR
C
C  Author: Christian Zeitnitz 27.5.92
C
C**************************************************************
C
C GEANT COMMON
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
*KEEP,GCTIME.
      COMMON/GCTIME/TIMINT,TIMEND,ITIME,IGDATE,IGTIME
      INTEGER ITIME,IGDATE,IGTIME
      REAL TIMINT,TIMEND
C
*KEEP,GCBANK.
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEND.
C CALOR COMMONS
*KEEP,CALGEA.
C***************************************************************
C
C       CALOR-GEANT Interface common
C
C parameters of incident particle :
C                   IPinc   = particle type a la CALOR
C                   Einc    = kinetic energy
C                   Uinc(3) = direction cosines
C material parameters:
C                   NCEL    = number of elements in mixture (NMTC)
C                             GEANT material no. for MICAP
C                   Amed(I) = mass number
C                   Zmed(I) = charge number
C                   Dmed(I) = Atoms/cm**3 * 1E-24
C                   Hden    = Atoms/cm**3 * 1E-24
C                             of H-Atoms in mixture
C
C particle stack:
C            NPHETC           = number of particles
C            Ekinet(1:NPHETC) = kinetic energy of part.
C            IPCAL(1:NPHETC)  = particle type a la CALOR (extended)
C            UCAL(1:NPHETC,3) = direction cosines
C            CALTIM(1:NPHETC) = age of particle (nsec)
C
C            ATARGT = A no. of target nucleus
C            ZTARGT = Z no. of target nucleus
C
C return of residual nucleus information
C            NRECOL  = no. of heavy recoil products
C            Amed(I) = mass number of residual nucleus
C            Zmed(I) = charge number "          "
C            EXmed   = exitation energy of nucleus
C            ERmed(I)= recoil energy of nucleus
C            IntCal  = type of interaction (GEANT NAMEC index)
C return of cross section of hadronic interaction (CALSIG called)
C            SIG =  x-section
C
C set by CALSIG:
C            ICPROC = -1   undefined
C                   =  0   NMTC called for cross-section
C                   =  1   MICAP called for cross-section
C                   =  2   SKALE(NMTC at 3 GeV) called for cross-section
C                   =  3   FLUKA called for cross-section
C            KCALL : same coding as ICPROC, but is only valid after a
C                    call to GCALOR
C       18/8/92  C.Zeitnitz University of Arizona
C****************************************************************
C
      PARAMETER(EMAXP  = 3.495)
      PARAMETER(EMAXPI = 2.495)
C transition upper limit (GeV) NMTC-FLUKA
      PARAMETER(ESKALE = 10.0)
      PARAMETER(MXCP = 300)
C
      COMMON/ CALGEA / IPINC  , EINC       , UINC(3)   ,NCEL        ,
     +                 HDEN   , AMED(100)  , ZMED(100) ,DMED(100)   ,
     +                 NPHETC ,EKINET(MXCP),IPCAL(MXCP),UCAL(MXCP,3),
     +                 INTCAL , EXMED      , ERMED(100),SIG         ,
     +                 CALTIM(MXCP), ICPROC, NRECOL    ,KCALL       ,
     +                 ATARGT , ZTARGT
C
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEEP,CMAGNT.
      COMMON/CMAGNT/BODGE,BFIELD(3)
C
*KEEP,CHIE.
       COMMON / CHIE / IHIE, EHIN, EHIPI
C
*KEEP,CGEOS.
C
      COMMON/CGEOS/ GEOSIG(240),SGPIMX,SGMUMX
C
*KEEP,CTNCOL.
      COMMON/ CTNCOL / NCOL
C
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,CERRCM.
      LOGICAL CERRF
      COMMON/CERRCM/CERRF,IERRU
*KEEP,CAMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
*KEND.
C
      DIMENSION IPID(0:11)
      LOGICAL INIT,OPENED,EXISTS
      CHARACTER*100 BERTF
      CHARACTER*8  VERSQQ
      CHARACTER*10 DATE
      CHARACTER*20 NAP
      CHARACTER*100 CHROOT
      DATA INIT/.TRUE./
C GEANT Particle IDs used to extract masses from GEANT
      DATA IPID /14 , 13 , 8 , 7 , 9 , 5 , 6 , 45 , 46 , 49 , 47 , 1/
C
      IF(.NOT.INIT) RETURN
      INIT = .FALSE.
*KEEP,VERSQQ.
      VERSQQ = ' 1.05/04'
      IVERSQ =  10504
*KEND.
      CALL GCDATE(IDAT,ITIM)
      IYEAR = IDAT/10000
      IMONTH= (IDAT-IYEAR*10000)/100
      IDAY  = IDAT-(IDAT/100)*100
      WRITE(DATE,'(I2,''.'',I2,''.'',I4)') IDAY,IMONTH,IYEAR
      PRINT*,'******************************************************'
      PRINT*,'*                                                    *'
      PRINT*,'*    GEANT - CALOR Interface  Version ',VERSQQ,'       *'
      PRINT*,'*    -----------------------------------------       *'
      PRINT*,'*       ',DATE,'  C.Zeitnitz, T.A.Gabriel          *'
      PRINT*,'*                                                    *'
      PRINT*,'*     NMTC is used for hadronic interactions of      *'
      PRINT*,'*        protons,neutrons and charged pions          *'
      PRINT*,'*   up to 3.5 GeV (proton,neutron), 2.5 GeV(pion)    *'
      PRINT*,'*                                                    *'
      PRINT*,'*    A Scaling Model is used for the energy range    *'
      PRINT*,'*                 up to 10 GeV.                      *'
      PRINT*,'*                                                    *'
      PRINT*,'*      MICAP is calculating the interaction of       *'
      PRINT*,'*       Neutrons with an energy below 20 MeV         *'
      PRINT*,'*                                                    *'
      PRINT*,'*   For interactions of hadrons not implemented in   *'
      PRINT*,'*        CALOR or with an energy above 10 GeV        *'
      PRINT*,'*                GEANT-FLUKA is called               *'
      PRINT*,'*                                                    *'
      PRINT*,'*  The transport of electrons, positrons and gammas  *'
      PRINT*,'*                 is done by GEANT                   *'
      PRINT*,'*                                                    *'
      PRINT*,'*     All output is written to file calor.out        *'
      PRINT*,'*                                                    *'
      PRINT*,'******************************************************'
      PRINT '('' *        Neutron cutoff energy='',G10.2,  '
     +        //' '' eV         *'')',CUTNEU*1.E9
      PRINT*,'******************************************************'
C
C fill particle mass array
      DO 10 I=0,11
         CALL G3FPART(IPID(I),NAP,ITR,AM,CH,TL,UB,NW)
         XMASS(I)=AM
   10 CONTINUE
      INIT = .FALSE.
      ICPROC = -1
      IN = 5
      EHIN = 3495.0
      EHIPI = 2495.0
      EMAX = 3500.0
      NBERTP = 30
      INQUIRE(UNIT=NBERTP,OPENED=OPENED)
      IF(OPENED) THEN
         REWIND NBERTP
      ELSE
         BERTF = 'chetc.dat'
         INQUIRE(FILE=BERTF,EXIST=EXISTS)
         IF(.NOT.EXISTS) THEN
            CHROOT = ' '
            CALL GETENVF('G3SYS',CHROOT)
            LNROOT = LNBLNK(CHROOT)
            IF(LNROOT.GT.0)BERTF = CHROOT(1:LNROOT)//'/data/chetc.dat'
         ENDIF
         INQUIRE(FILE=BERTF,EXIST=EXISTS)
         IF(.NOT.EXISTS) THEN
           PRINT*,'**********************************'
           PRINT*,'*        G C A L O R             *'
           PRINT*,'*        -----------             *'
           PRINT*,'*   File CHETC.DAT not found     *'
           PRINT*,'*         Program STOP           *'
           PRINT*,'**********************************'
           STOP
         ENDIF
         OPEN(UNIT = NBERTP,FILE=BERTF, FORM = 'FORMATTED',STATUS=
     +   'OLD')
      ENDIF
C Output unit for Neutron information and error messages
      IOUT = 32
      IERRU = IOUT
      OPEN(UNIT=IOUT,FILE='calor.out',FORM='FORMATTED',
     +     STATUS='UNKNOWN')
      IO = IOUT
      WRITE(IOUT,'(/, '
     +    //' 18X,''GEANT-CALOR INTERFACE V'',A8,'' Output File'',   '
     +    //'/,18X,''==========================================='',/)')
     +           VERSQQ
C read bert cascade and evaporation dataset
      CALL CRBERT
      CLOSE(UNIT=NBERTP)
      ELOP = AMAX1(1.0,CUTHAD * 1000.0)
      ELON = AMAX1(20.0,CUTNEU * 1000.0)
      NPOWR2 = 11
      NGROUP = 2**NPOWR2
      EMUCUT = AMAX1(1.0,CUTMUO * 1000.0)
      EPICUT = ELOP
      NPIDK =  -1
      CTOFE = 0.0
      CTOFEN = 0.0
      ANDIT = 0.0
      NEXITE = 1
      NBOGUS = NEXITE
      ELAS = 0.0
      BODGE = 0.0
      EMIN(1) = ELOP
      EMIN(2) = ELON
      EMIN(3) = EPICUT
      EMIN(4) = EPICUT
      EMIN(5) = EPICUT
      EMIN(6) = EMUCUT
      EMIN(7) = EMUCUT
C now get some cross sections
      CALL CREADG(GEOSIG)
      CALL GTHSIG(1)
C No decay cross-section needed in GEANT
C      SGPIMX = 0.001259/SQRT ((EMIN(3)/139.9+1.)**2 -1.)
C      SGMUMX = 1.587E-5/SQRT ((EMIN(6)/107.+1.)**2 -1.)
      SGPIMX = 0.0
      SGMUMX = 0.0
      NCOL = 1
C ------------ initialize MICAP ------------------------
      CALL MORINI
C perform garbage collection in constant division
      CALL MZGARB(IXCONS,0)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.36  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CREADG(GEOSIG)
C
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      DIMENSION GEOSIG(240)
C
      K=1
      DO 20 J = 1,4
CZ data already read by CRBERT called by CALINI 19.june 92 CZ
CZ changed 5-28-92  crazy number for A=240 set to GEOSIG(239)
         DO 10 I = 4,594,10
            IF(K.LT.240) THEN
               GEOSIG(K) = SNGL(CRSC(I + (J-1)*600))
               GEOSIG(K) = 3.1416 * GEOSIG(K)**2 * 1.E+24
            ELSE
               GEOSIG(K) = GEOSIG(K-1)
            ENDIF
   10    K = K + 1
   20 CONTINUE
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.36  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   06/06/92
      FUNCTION ICALGE(IP)
C*******************************************
C
C INPUT : CALOR particle type
C OUTPUT: GEANT particle type
C
C******************************************
C
C
      DIMENSION NCALGE(0:11)
C       convert CALOR particle code to GEANT
C                   p   n pi+ pi0 pi- mu+ mu- D   T   He3 Alpha Gamma
      DATA NCALGE/ 14, 13,  8,  7,  9,  5,  6, 45, 46, 49, 47,  1/
C
      IF(IP .LE. 11 .AND. IP.GE.0) THEN
         ICALGE = NCALGE(IP)
      ELSE
         ICALGE = 0
      ENDIF
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.36  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   06/06/92
      FUNCTION IGECAL(IP)
C*******************************************
C
C INPUT : GEANT particle type
C OUTPUT: CALOR particle type or -1
C
C******************************************
C
C
      DIMENSION NGECAL(48)
C
C       convert GEANT particle code to CALOR
C -1 indicates a particle not implemented in CALOR
      DATA NGECAL/ -1, -1, -1, -1, -1, -1, -1,  2,  4, -1,
     +             -1, -1,  1,  0, -1, -1, -1, -1, -1, -1,
     +             28*-1/
C
C
      IF(IP .LE. 48 .AND. IP.GT.0) THEN
         IGECAL = NGECAL(IP)
      ELSE
         IGECAL = -1
      ENDIF
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.36  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   19/06/92
      SUBROUTINE CRBERT
C*********************************************************
C
C  Read BERT Data into commons used by BERT,PCOL,GTHSIG
C  DRES
C
C*********************************************************
C
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CDRESC.
      REAL*4 FLA(6), FLZ(6), EXMASS(6),
     +       CAM4(130),CAM5(200), RMASS(300),
     +       P0(1001),P1(1001),P22(1001),RHO(6),OMEGA(6),
     +       ALPH(300),BET(300)
      COMMON/CDRESC/ IA(6),IZ(6), FLA, FLZ, EXMASS,
     +       CAM4,CAM5, RMASS,
     +       P0,P1,P22,RHO,OMEGA,
     +       ALPH,BET
C
*KEEP,CEVCM.
      COMMON / CEVCM / Y0,B0,T(4,7),CAM2(130),CAM3(200),WAPS(250,20)
C
*KEND.
C
      REWIND NBERTP
C ---- read cascade data --------------
      I1 = 1
      I2 = 600
      DO 10 J=1,4
         READ(NBERTP,10000) (CRSC(I),I=I1,I2)
         I1 = I1 + 600
         I2 = I2 + 600
   10 CONTINUE
      READ(NBERTP,10000) (TAPCRS(I),I=1,29849)
C ----- read evaporation data -----------
      DO 30 K=1,250
         DO 20 J=1,20
            WAPS(K,J) = 0.0
   20    CONTINUE
   30 CONTINUE
      READ(NBERTP,10000) (P0(J),P1(J),P22(J),J=1,1001)
      READ(NBERTP,10100) (IA(J),J=1,6),(IZ(J),J=1,6)
      READ(NBERTP,10000) (RHO(J),J=1,6),(OMEGA(J),J=1,6)
      READ(NBERTP,10000) (EXMASS(J),J=1,6)
      READ(NBERTP,10000) (CAM2(J),J=1,130)
      READ(NBERTP,10000) (CAM3(J),J=1,200)
      READ(NBERTP,10000) (CAM4(J),J=1,130)
      READ(NBERTP,10000) (CAM5(J),J=1,200)
      READ(NBERTP,10000) ((T(I,J),J=1,7),I=1,3)
      READ(NBERTP,10000) (RMASS(J),J=1,297)
      READ(NBERTP,10000) (ALPH(J),J=1,297)
      READ(NBERTP,10000) (BET(J),J=1,297)
      READ(NBERTP,10000) ((WAPS(I,J),I=1,250),J=1,20)
10000 FORMAT(5E16.8)
10100 FORMAT(6I10)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.36  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   30/10/92
      LOGICAL FUNCTION SKALEF(IP,EIP,ESKALE)
C*************************************************************
C
C  Called by: GCALOR
C  Purpose :  function is true, when scaling applies to FLUKA
C             linear transition from NMTC to FLUKA
C  Author : C.Zeitnitz
C
C*************************************************************
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      SKALEF = .TRUE.
      ENMTC = 3.495
      IF(IP.GT.1) ENMTC = 2.495
      IF(EIP.LE.ENMTC) SKALEF = .FALSE.
      IF(EIP.LT.ESKALE.AND.EIP.GT.ENMTC) THEN
         X1 = (EIP - ENMTC) / (ESKALE - ENMTC)
         X2 = SNGL(RANDC2(ISEED))
         IF(X2.GT.X1) SKALEF = .FALSE.
      ENDIF
      RETURN
      END
*CMZ :  1.02/02 28/01/94  09.09.15  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   30/07/93
*
*  simple utility to generate date and time of GCALOR version
* When running kumac file vers.kumac this file is written as fortran
* and then read again, in order to fix date and time
*
      SUBROUTINE GCDATE(IDATQQ,ITIMQQ)
*KEEP,DATEQQ.
      IDATQQ = 20051130
*KEEP,TIMEQQ.
      ITIMQQ =   1129
*KEND.
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.28  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE AZIRN2(SIN,COS)
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C       THIS ROUTINE SELECTS THE AZIMUTHAL ANGLE UNIFORMLY IN THETA
   10 R1 = SFLRAF2(DUM)
      R1SQ = R1 * R1
      R2 = RANDC2(ISEED)
      R2SQ = R2 * R2
      RSQ = R1SQ + R2SQ
      IF(1.0-RSQ) 10 ,20 ,20
   20 SIN = 2.0 * R1 * R2 / RSQ
      COS = (R2SQ-R1SQ) / RSQ
      RETURN
      END
*CMZ :  0.94/00 08/03/93  12.50.48  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE DKLOS
C
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CMAGNT.
      COMMON/CMAGNT/BODGE,BFIELD(3)
C
*KEEP,CTUCTW.
      COMMON/CTUCTW/WTCUT,NWTC
C
*KEEP,CELSTC.
      COMMON/CELSTC/ELAS, FONE, SGELS(10),TOTELS,ID(10,1),LOCF1(21),
     +              LOCSIG(21),NELSTP,NLEDIT,NOEL(1),NOELAS
C
*KEND.
C
      MT = MAT
      GOTO(10,10,20,30,20,40,40),ITYP
   10 DKWT =1.
C*************ADD MAGNET BODGE TO DELSIG********************
      DELSIG=SIGMX(ITYP,MT)+TOTELS+BODGE
C      DELSIG = SIGMX(ITYP,MT ) + TOTELS
      RETURN
   20 SIGDK= 0.001259/SQRT ((EC(NO)/139.9+1.)**2. -1.)
      GO TO 50
   30 CALL CERROR('DKLOS$')
   40 SIGDK= 1.587E-5/SQRT ((EC(NO)/107.+1.)**2. -1.)
C   50 DELSIG = SIGMX(ITYP,MT ) - SIGDK
C********ADD MAGNET BODGE TO DELSIG AND ALLOW FOR IT IN DKWT*******
   50 DELSIG = SIGMX(ITYP,MT ) - SIGDK+BODGE
C      DKWT = DELSIG/SIGMX(ITYP,MT )
      DKWT = DELSIG/(SIGMX(ITYP,MT )+BODGE)
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.28  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CESWH
C** ELASTIC SCATTERING WITH HYDROGEN,
C*  STRUCK PARTICLE AT REST.
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      CALL CAAZIO(SOPC,SOPS)
      PM(4) = DNCMS
      PT(1) = 0.
      DO 10 I=3,13
   10 PT(I) = 0.
      DO 20 I=15,48
   20 PT(I) = 0.
      DO 30 I=1,24
   30 COL(I) = 0.
      A=PM(4)*PM(4)
      COL(1)=E(1)+E(2)
C     TOTAL ENERGY PARTICLES 1 AND 2
      DO40 I=1,3
   40 COL(I+1)=PM(I)*PM(I)
C     MASS PARTICLE I SQD.
      COL(5)=COL(3)+COL(2)+2.0*(E(1)*E(2)-(PXYZ(1)*PXYZ(2)+PXYZ(5)*
     1PXYZ(6)+PXYZ(9)*PXYZ(10)))
      COL(6)=DSQRT(COL(5))
      COL(7)=COL(6)/COL(1)
C     GAM
      COL(8)=2.0*COL(6)
      COL(9)=(COL(4)+COL(5)-A)/COL(8)
      COM2 = COL(9)*COL(9)
   50 COL(10)=DSQRT(COM2-COL(4))
C     P3 PRIME
      COL(18)=PXYZ(9)*PM(2)/COL(6)
C     P(1),Z *M2/M=P(BAR PRIME)1,Z
      COL(21)=PXYZ(9)/COL(1)
C     VZ VELOCITY
      PXYZ(3)=COL(10)*SNT*SOPC
C     X COMPONENT P3 BAR =P3 PRIME X SIN THETA X COS PHI
      PXYZ(7)=COL(10)*SNT*SOPS
C     Y COMP. P3 BAR =P3 PRIME X SIN THETA X SIN PHI
      PXYZ(11)=COL(10)*CST
      Z=PXYZ(9)/COL(6)
      PXYZ(11)=PXYZ(11)+(Z*PXYZ(9)*PXYZ(11))/(COL(1)+COL(6))+Z*COL(9)
C     Z COMP. P3 BAR=P3 PRIME COS THETA+(P1Z SQ*P3Z (PRIME)COS
C     THETA/(E PRIME*(E+E PRIME))+P1Z*E3 PRIME/E PRIME
      E(3)=DSQRT(PXYZ(3)*PXYZ(3)+PXYZ(7)*PXYZ(7)+PXYZ(11)*PXYZ(11)+
     1PM(3)*PM(3))
      DO60 I=1,9,4
   60 PXYZ(I+3)=PXYZ(I)-PXYZ(I+2)
      E(4)=DSQRT(PXYZ(4)*PXYZ(4)+PXYZ(8)*PXYZ(8)+PXYZ(12)*PXYZ(12)
     1+PM(4)*PM(4))
C** KINETIC ENERGY OF 3 AND 4
      PT(3) = (E(3) - PM(3))/RCPMV
      PT(15) = (E(4) - PM(4))/RCPMV
C** MOMENTUM OF 3 AND 4, IN LAB.
      P3 = DSQRT(PXYZ(3)*PXYZ(3) + PXYZ(7)*PXYZ(7) + PXYZ(11)*PXYZ(11))
      P4 = DSQRT(PXYZ(4)*PXYZ(4) + PXYZ(8)*PXYZ(8) + PXYZ(12) *PXYZ(12))
C** DIRECT COSINES OF 3 AND 4
      PT(8) = PXYZ(3)/P3
      PT(9) = PXYZ(7)/P3
      PT(10) = PXYZ(11)/P3
      PT(20) = PXYZ(4)/P4
      PT(21) = PXYZ(8)/P4
      PT(22) = PXYZ(12) /P4
      RETURN
      END
*CMZ :  1.01/17 22/11/93  12.22.58  by  Christian Zeitnitz
*-- Author :
      FUNCTION EXPRNF2(A)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      REAL I
C
      I = 0.0
   10 X = RANDC2(ISEED)
      Z = X
   20 Y = RANDC2(ISEED)
      IF(Z-Y) 50 ,50 ,30
   30 Z = RANDC2(ISEED)
      IF(Z-Y) 20 ,40 ,40
   40 I = I + 1.0
      GO TO 10
   50 EXPRNF2 = X + I
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.28  by  Christian Zeitnitz
*-- Author :
      FUNCTION GAURN(X)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
   10 Y = EXPRNF2(X1)
      Z = EXPRNF2(X2)
      TEST = (Y-1.0)**2/2.
      IF(TEST-Z) 20,20,10
   20 R1 = 2.0 * RANDC2(ISEED) - 1.0
      IF(R1) 30,40,40
   30 Y = -Y
   40 GAURN = Y
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE GTHSIG(ISGNL)
C
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEEP,CHIE.
       COMMON / CHIE / IHIE, EHIN, EHIPI
C
*KEEP,CBERT2.
      COMMON/CBERT/ DUME(4895),CS(29850)
      REAL*8 DUME,CS,TEMP
C
*KEND.
C
C
C ** DE IS THE CONST. ENERGY SPACING COMMON T0 P-P,N-P,PI+P,PI-P XSECTS
      DIMENSION ISA(4),EMX(4)
      SAVE ISA,EMX
C
      GO TO (10,180),ISGNL
   10 CONTINUE
CZ BERT dataset already read by CRBERT called by CALINI 19.june 92
      CALL CSHXD
      DO 20 I=1,4
   20 ISA(I) = LOCX(3,I)
C**** COMPUTE TOTAL P-P AND N-P XSECTS (SINGLE PRODUCTION + DOUBLE PRODU
C****  + ELASTIC) AND STORE P-P BEGINNING AT CS(3794) ANP N-P BEGINNING
C****  CS(3970).
      ISP=995
      IDP=1153
      DO 50 IT=1,2
         IS= ISA(IT)
         DO 30 I=1,158
            TEMP= CS(IS+18+I)
   30    CS(IS+18+I) = TEMP + CS(ISP+I)
         ISP = ISP + 288
         DO 40 I=1,130
            TEMP = CS(IS+46+I)
   40    CS(IS+46+I) = TEMP + CS(IDP+I)
   50 IDP = IDP + 288
C**** COMPUTE TOTAL PI+(SNGL PROD.+ELAS) AND PI-(SNGL PROD.+EXCHNG +ELAS
C**** AND STORE PI+-P BEGINNING AT CS(3668) AND PI--P BEGINNING AT CS(35
      ISP =2009
      DO 70 IT =3,4
         IS= ISA(IT)
         DO 60 I=1,117
            TEMP = CS(IS +9+I)
   60    CS(IS+9+I) = TEMP + CS(ISP+I)
   70 ISP = ISP +234
      IEX =3415
      IS = ISA(4)
      DO 80 I=1,126
         TEMP = CS(IS+I)
   80 CS(IS+I) = TEMP + CS(IEX+I)
      DO 100 IT = 1,2
         IS = ISA(IT)
         DO 90 I=1,176
   90    NPSG(IT,I) = SNGL( CS(IS+I) )
  100 CONTINUE
      DO 120 IT = 1,2
         IS = ISA(IT+2)
         DO 110 I=1,126
  110    PIPSG(IT,I) = SNGL( CS(IS+I) )
  120 CONTINUE
C *****
C **** SELECT MAX. TOT.XSECTS FOR X ON PROT. IN ENERGY RANGE EMIN(X) TO
C **** WHERE X = PROT.,NEUT.,PI+,PI-.
      IF(EMAX.LT.EHIN)GO TO 130
      EMX(1)=EHIN
      EMX(2)=EHIN
      EMX(3)=EHIPI
      EMX(4)=EHIPI
      GO TO 140
  130 CONTINUE
      EMX(1)= EMAX
      EMX(2)= EMAX
      EMX(3)=  2500.
      EMX(4)=  2500.
  140 CONTINUE
      DO 160 ITP =1,4
         IS= ISA(ITP)
         IT = ITP + ITP/4
         CALL CALSGM(1,ITP,IS,DE,EMIN(IT),IL,EL,SL)
         CALL CALSGM(1,ITP,IS,DE,EMX(ITP),IH,EH,SH)
         HSIGMX(IT) = AMAX1(SL,SH)
         IF(IL.GE.IH) GO TO 160
         IL = IL +1
         DO 150 I= IL,IH
            SIG = SNGL(CS(I+IS))
            IF(SIG. LE. HSIGMX(IT)) GO TO 150
            HSIGMX(IT) = SIG
  150    CONTINUE
  160 CONTINUE
      HSIGMX(4)=0.0
10000 FORMAT(1H0,7HHSIGMX ,5E15.5)
  170 RETURN
  180 IT = ITYP - ITYP/5
      IS = ISA(IT)
      CALL CALSGM(2,IT,IS,DE,EC(NO),I,EI,HSIG)
      GO TO 170
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CISOB
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
C
      INTEGER*2 RANDI
      REAL*8 DCLN(80),DCIN(115),PPAC(19),POAC(19),
     + FMXSN(161),FMXDN(130),FMXSP(117),PDCI(60),PDCH(55),DCHN(143),
     + DCHNA(36),DCHNB(60),PSPCL(158),PDPCL(130),SPCLN(158),DPCLN(130),
     + FSLN(176),FRINN(161),DMIN(101),PPSCL(117),PNSCL(117),PMSCL(117),
     + PNNSL(117),PCFSL(234),FRIPN(117),PNMI(101),PNFSL(234),PNEC(126),
     + PNNEC(126),PMXC(126),PMEC(126),PPEC(126),PEC(176),ECN(176),
     + PPDC(6426),PMDD(6426),PMDX(6426),PNDD(6426)
      REAL*8 CALCIN(3)
      EQUIVALENCE (TAPCRS(1),DCLN(1))    ,(TAPCRS(81),DCIN(1))   ,
     +            (TAPCRS(196),PPAC(1))  ,(TAPCRS(215),POAC(1))  ,
     +            (TAPCRS(234),FMXSN(1)) ,(TAPCRS(395),FMXDN(1)) ,
     +            (TAPCRS(525),FMXSP(1)) ,(TAPCRS(642),PDCI(1))  ,
     +            (TAPCRS(702),PDCH(1))  ,(TAPCRS(757),DCHN(1))  ,
     +            (TAPCRS(900),DCHNA(1)) ,(TAPCRS(936),DCHNB(1)) ,
     +            (TAPCRS(996),PSPCL(1)) ,(TAPCRS(1154),PDPCL(1)),
     +            (TAPCRS(1284),SPCLN(1)),(TAPCRS(1442),DPCLN(1)),
     +            (TAPCRS(1572),FSLN(1)) ,(TAPCRS(1748),FRINN(1))
C
      EQUIVALENCE (TAPCRS(1909),DMIN(1)) ,(TAPCRS(2010),PPSCL(1)),
     +            (TAPCRS(2127),PNSCL(1)),(TAPCRS(2244),PMSCL(1)),
     +            (TAPCRS(2361),PNNSL(1)),(TAPCRS(2478),PCFSL(1)),
     +            (TAPCRS(2712),FRIPN(1)),(TAPCRS(2829),PNMI(1)) ,
     +            (TAPCRS(2930),PNFSL(1)),(TAPCRS(3164),PNEC(1)) ,
     +            (TAPCRS(3290),PNNEC(1)),(TAPCRS(3416),PMXC(1)) ,
     +            (TAPCRS(3542),PMEC(1)) ,(TAPCRS(3668),PPEC(1)) ,
     +            (TAPCRS(3794),PEC(1))  ,(TAPCRS(3970),ECN(1))  ,
     +            (TAPCRS(4146),PPDC(1)) ,(TAPCRS(10572),PMDD(1)),
     +            (TAPCRS(16998),PMDX(1)),(TAPCRS(23424),PNDD(1))
C
      SAVE
      DATA NTER/0/
      IF(NTER.NE.0) GO TO 10
      NTER =1
      JP = 0
      IK = 0
      CASESN = 1.D0
      LN=2
      PNMS=.708E13
      SQNM=2.2638564E27
      DNCMS=4.758E13
      POMS=.684E13
      RCPMV=.50613E11
   10 CONTINUE
      LOOP=0
      INPT=0
      DO20 I=1,48
   20 PT(I)=0.0
      NOF  = 0
   30 BEGRU=0.0
      NOR=0
C     NOR=NUMBER OF RECORD
      NOF=NOF+1
C     EINC=INC.PART.EN.
C     CASESN=NO.OF INC.PART.
C     ANDIT=ANG.DIST.
C     PRTIN=INC.PART.
C     TRSYM=STRUCK PART.
C     RANDI=INPUT RAND NO.
C     IP=TYPE OF REACTION(-1=S.P.,0=D.P.,1=CHOICE)
C     IK=0,STRUCK PART.AT REST--OTHERWISE ASSUME ENERGY
C     JP=0, NO PRINT OUT
      KASE=0
C SENTINEL FOR GETTING CROSS SECTIONS WHEN STRUCK PARTICLE HAS ENERGY
      DO40 I=1,3
   40 CALCIN(I)=0.0
      STRKP = -1.D0
      GOTO(50  ,50  ,60  ,70  ,60  ),NO
   50 PM(1)=DNCMS
      GOTO110
   60 PM(1)=PNMS
      GOTO80
   70 PM(1)=POMS
   80 IF(NO-4)90 ,100,100
   90 ISW(11)=1
      GOTO110
  100 ISW(11)=0
  110 PM(2)=DNCMS
      KA = 1
      E(1)=EINC*RCPMV+PM(1)
      PXYZ(1)=0.0
      PXYZ(5)=0.0
      PXYZ(9) =  DSQRT  (E(1)*E(1) -  PM(1)*PM(1) )
      RLKE=EINC
      IF(IK)140,120,140
  120 P2=0.0
      PXYZ(2)=0.0
      PXYZ(6)=0.0
      PXYZ(10)=0.0
      E(2)=DNCMS
      GOTO140
  130 CONTINUE
  140 IF(NO-3)150,160,160
  150 IF(RLKE-3500.0)230,230,190
  160 IF(RLKE-180.0)190,190,170
  170 IF(RLKE-2500.0)180,180,190
  180 IF(KASE)970 ,230,970
  190 IF(IK)200,210,200
  200 IF(KASE)220,210,220
  210 NE=3
C     RLKE IN CERROR('CISOB1')
      GOTO1050
  220 LOOP=LOOP+1
      IF(LOOP-1000)130,130,210
  230 IF(IP)240,460,460
  240 IF(NO-3)460,370,370
  250 LK=2
      I3=1
  260 CALL QRDET(1,PSPCL(1),CALCIN(1))
C     ARGUMENT=PSPCL, P-P, N-N, S.P.
      CALCIN(1)=CRDT(1)
      IF(LK-6)270,320,320
  270 CALL QRDET(1, PEC(1), RLKE)
C     ELASTIC CROSS SECTION
  280 CALCIN(3)=CRDT(1)+CALCIN(1)+CALCIN(2)
C     TOTAL
C     P-P, N-N, ELASTIC
      GO TO 630
  290 LK=3
      I3=2
  300 CALL QRDET(1, SPCLN(1),CALCIN(1))
C     ARGUMENT=NSPCL, N-P, P-N, S.P.
      CALCIN(1)=CRDT(1)
      IF(LK-6)310,320,320
  310 CALL QRDET(1, ECN(1), RLKE)
      GO TO 280
C     P-N, N-P, ELASTIC
  320 CRATIO=CALCIN(1)/(CALCIN(1)+CALCIN(2))
      VALUE1 = RANDC2(ISEED)
      IF(VALUE1-CRATIO)330 ,330 ,350
  330 IF(KA-NO)360 ,340 ,360
  340 I3=1
      GOTO270
  350 IF(KA-NO)310,270,310
  360 I3=2
      GOTO310
  370 ISW(10)=0
      ISW(9)=0
C     9 SET FOR PI0,10 SET FOR PI+-N,PI--P,PI0-P, AND PI0-N
      CALCIN(1)=RLKE-180.0
      LK=1
C     PION
      I3=0
      IF(NO-4)380,420,450
  380 GOTO(390,400),KA
  390 CALL QRDET(1, PPSCL(1),CALCIN(1))
      CALCIN(1)=CRDT(1)
      CALL QRDET(1, PPEC(1),RLKE)
      GOTO280
C     PI(PLUS)-P, S.P. OR PI(MINUS)-N
  400 CALL QRDET(1, PMSCL(1),CALCIN(1))
      CALCIN(1)=CRDT(1)
      CALL QRDET(1, PMEC(1) , RLKE)
  410 CALCIN(3)=CRDT(1)
      ISW(10)=2
      CALL QRDET(1, PMXC(1) , RLKE)
      CALCIN(3)=CALCIN(3)+CRDT(1)+CALCIN(1)+CALCIN(2)
C     PI(PLUS)-N, S.P) OR PI(MINUS)-P
      GOTO630
  420 ISW(9)=2
      GOTO(430,440),KA
  430 CALL QRDET(1, PNSCL(1),CALCIN(1))
      CALCIN(1)=CRDT(1)
      CALL QRDET(1, PNEC(1) ,RLKE)
      GOTO410
C     PI(0)-P, S.P.
  440 CALL QRDET(1,PNNSL(1) ,CALCIN(1))
      CALCIN(1)=CRDT(1)
      CALL QRDET(1,PNNEC(1) ,RLKE )
      GOTO410
C     PI(0)-N, S.P.
  450 GOTO(400,390),KA
C     PI(-)-P, PI(-)-N, S.P.
  460 IF(RLKE-920.0)470,470,530
  470 IF(IP)480,190,480
  480 IF(RLKE-360.0)190,190,490
  490 IF(KASE)970 ,500,970
  500 CALCIN(1)=RLKE-360.0
      GOTO(510,520 ),NO
  510 ISW(4)=1
      GOTO(570,600),KA
  520 ISW(4)=0
      GOTO(600,570),KA
  530 IF(KASE)970 ,540,970
  540 CALCIN(2)=RLKE-920.0
      CALCIN(1)=RLKE-360.0
      GOTO(550,620),NO
  550 ISW(4)=1
      GOTO(560,590),KA
  560 CALL QRDET(1,PDPCL(1) ,CALCIN(2))
C     ARGUMENT=PDPCL, P-P, N-N, D.P.
      CALCIN(2)=CRDT(1)
C     N-N, OR P-P, D.P.
  570 IF(IP)250,580,580
  580 LK=4+2*(IP)
      I3=3
      GOTO260
  590 CALL QRDET(1,DPCLN(1) ,CALCIN(2))
C     ARGUMENT=NDPCL, N-P, P-N, D.P.
      CALCIN(2)=CRDT(1)
  600 IF(IP)290,610,610
  610 LK=5+IP
      I3=4
      GOTO300
C     N-P, OR P-N, D.P.
  620 ISW(4)=0
      GOTO(590,560),KA
  630 IF(JP)1050,650,640
C     JP=0, NO PRINT OUT
  640 WRITE(6,10000)EINC,NO,KA,CASESN,(RANDS(I),I=2,4),(CALCIN(I),I=1,
     +3) , IP,NOF,IK
10000 FORMAT(1H1,'   EINC      NO       KA     CASESN     RANDI      CAL
     +CIN        IP          NOF        IK'/1H0,D11.3,2I8,D11.3,1X,3Z4,
     + 3D11.3,3I8)
  650 CONTINUE
      KASE=1
      IF(IK)130,660,130
  660 GOTO(990 ,990 ,680 ,680 ,680 ),NO
  670 I3=0
  680 CALL QOUT17(FRIPN(1),PNMI(1),FMXSP(1),PCFSL(1),PNFSL(1))
      IF(I3)1090,730 ,690
  690 IF(COL(15)-1.0)730 ,790 ,700
  700 IF(COL(15)-3.0)770 ,760 ,710
  710 IF(COL(15)-5.0)780 ,1020,720
  720 NE=11
      GOTO1050
  730 CALL QOLLM
      IF(PT(38))750 ,740 ,750
  740 I3=1
      GOTO800
  750 I3=2
      GOTO800
  760 I3=4
      GOTO800
  770 I3=5
      GOTO800
  780 I3=6
      GOTO800
  790 I3=3
  800 CALL QOUT18
      I3=I3
      GOTO(690 ,810 ,690 ,820 ),I3
  810 NE=12
      GOTO1050
  820 PM(4)=DNCMS
      K=IP
      J=2
      IF(IP)830 ,860 ,840
  830 NWRIT=22
      MM=26
      GO TO 870
  840 IF(PT(38))850 ,830 ,850
  850 K=K+1
  860 NWRIT=29
      MM=38
  870 OUT(1)=K
      DO900 I=2,MM,12
         M=I
         K=M+3
         DO890 N=1,2
            DO880 L=M,K
               OUT(J)=PT(L)
  880       J=J+1
            M=I+6
  890    K=M+2
  900 CONTINUE
      NOR=NOR+1
  910 IF(JP)1050,930,920
C     JP=0, NO PRINT OUT
  920 WRITE(6,10100)NOR,(OUT(I),I=1,NWRIT),E(2),(PXYZ(I),I=2,10,4)
10100 FORMAT(1H ,I7/(7D14.5))
  930 NWDS=NWRIT+4
C     NO.OF WORDS IN RECORD
  940 DO950 I=1,48
  950 PT(I)=0.0
      PGCNT=0.0
      PACNT=0.0
      LOOP=0
      BEGRU=BEGRU+1.0
      IF(CASESN-BEGRU)1050,1080,960
  960 IF(IK)130,970 ,130
  970 GOTO(670 ,980 ,1000,1010,1040,1100),LK
  980 I3=1
  990 CALL QOUT21(FRINN(1),DMIN(1),FMXSN(1),FMXDN(1),FSLN(1))
      GOTO680
 1000 I3=2
      GOTO990
 1010 I3=3
      GOTO990
 1020 CALL QOUT19
      IF(I3)1030,820 ,820
 1030 NE=13
      GOTO1050
 1040 I3=4
      GOTO990
 1050 CALL CERROR('CISOB$')
      IF(NE-3)1080,1060,1060
 1060 IF(CALCIN(1))1070,1080,1070
 1070 CONTINUE
      NOR=NOR+1
 1080 CONTINUE
      RETURN
 1090 NE=10
      GOTO1050
 1100 VALUE1 = RANDC2(ISEED)
      IF(VALUE1-CRATIO)1110,1110,1120
 1110 IF(KA-NO)1000,980 ,1000
 1120 IF(KA-NO)1130,1010,1130
 1130 GO TO 1040
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CPCOL(IB,ITYP,HSIG,EC,NOPART,KIND,EP,ALF,BET,GAM)
C
*KEEP,CINPU.
      COMMON / CINPU / ANDT, CTOF
C
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CISOBR.
      COMMON/CISOBR/AND1T,E1NC,DISO1(146),DOUT(40),DISO2(33),ISWD1(16),
     +              NNO,IIV,IPPP,ISWD2(5)
      REAL * 8 AND1T,E1NC,DISO1,DOUT,DISO2
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEEP,CRUN.
       COMMON/CRUN/KE
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL*8   DCLN(80),DCIN(115),PPAC(19),POAC(19),
     + FMXSN(161),FMXDN(130),FMXSP(117),PDCI(60),PDCH(55),DCHN(143),
     + DCHNA(36),DCHNB(60),PSPCL(158),PDPCL(130),SPCLN(158),DPCLN(130),
     + FSLN(176),FRINN(161),DMIN(101),PPSCL(117),PNSCL(117),PMSCL(117),
     + PNNSL(117),PCFSL(234),FRIPN(117),PNMI(101),PNFSL(234),PNEC(126),
     + PNNEC(126),PMXC(126),PMEC(126),PPEC(126),PEC(176),ECN(176),
     + PPDC(6426),PMDD(6426),PMDX(6426),PNDD(6426)
      EQUIVALENCE (TAPCRS(1),DCLN(1)) ,(TAPCRS(81),DCIN(1)) , (TAPCRS(1
     +96),PPAC(1)) ,(TAPCRS(215),POAC(1)) , (TAPCRS(234),FMXSN(1)) ,
     +(TAPCRS(395),FMXDN(1)) , (TAPCRS(525),FMXSP(1)) ,(TAPCRS(642),
     +PDCI(1)) , (TAPCRS(702),PDCH(1)) ,(TAPCRS(757),DCHN(1)) , (TAPCRS
     +(900),DCHNA(1)) ,(TAPCRS(936),DCHNB(1)) , (TAPCRS(996),PSPCL(1))
     +,(TAPCRS(1154),PDPCL(1)), (TAPCRS(1284),SPCLN(1)),(TAPCRS(1442),
     +DPCLN(1)), (TAPCRS(1572),FSLN(1)) ,(TAPCRS(1748),FRINN(1))
      EQUIVALENCE (TAPCRS(1909),DMIN(1)) ,(TAPCRS(2010),PPSCL(1)),
     +            (TAPCRS(2127),PNSCL(1)),(TAPCRS(2244),PMSCL(1)),
     +            (TAPCRS(2361),PNNSL(1)),(TAPCRS(2478),PCFSL(1)),
     +            (TAPCRS(2712),FRIPN(1)),(TAPCRS(2829),PNMI(1)) ,
     +            (TAPCRS(2930),PNFSL(1)),(TAPCRS(3164),PNEC(1)) ,
     +            (TAPCRS(3290),PNNEC(1)),(TAPCRS(3416),PMXC(1)) ,
     +            (TAPCRS(3542),PMEC(1)) ,(TAPCRS(3668),PPEC(1)) ,
     +            (TAPCRS(3794),PEC(1))  ,(TAPCRS(3970),ECN(1))  ,
     +            (TAPCRS(4146),PPDC(1)) ,(TAPCRS(10572),PMDD(1)),
     +            (TAPCRS(16998),PMDX(1)),(TAPCRS(23424),PNDD(1))
C
      DIMENSION KIND(60),EP(60),ALF(60),BET(60),GAM(60)
      DIMENSION ICC(12)
      SAVE
C
      KE =1
      IF(IB)30,10,30
   10 IB =1
      AND1T = DBLE(ANDT)
CZ BERT dataset already read by CRBERT called by CALINI 19.june 92
      SF = 1.D0
      RANDI(1) = 16896
      PNMS = .708D13
C     PI+ OR - MASS IN PER CM.
      DNCMS = 4.758D13
C     NUCLEON MASS IN PER CM.
      SQNM=DNCMS*DNCMS
C     NUCLEON MASS SQD.
      RCPMV = .50613D11
C     RECIPROCAL CM PER MEV.
      POMS = .684D13
C     PIO MASS IN RECIP. CM
      DO 20 I = 1,19
         POAC(I) = POAC(I) + POAC(I)
   20 PPAC(I) = PPAC(I)/SF
C     POAC(19),PPAC(19)
   30 DO 40 I =1,60
   40 IPEC(I) =0
      DO 50 I =1,2114
   50 ESPS(I) = 0.D0
      DO 60 I = 4515,4849
   60 ESPS(I) = 0.D0
      DO 70  I=1,12
   70 ICC(I)= 0
      DO 80 I = 1,4
   80 RANDS(I) = RANDI(I)
      PM(1) = DNCMS
      GO TO(110,110,100,90,100,90,90),ITYP
C           P  N  PI+ PI0 PI- MU+ MU-
   90 CALL CERROR('CPCOL1$')
      WRITE(IO,10000) ITYP
10000 FORMAT(' Wrong particle type = ',I2,' in CPCOL')
  100 PM(1) = PNMS
  110 INC =1
      CLSM = 1.D0
      PM(2) = DNCMS
      E(2) = DNCMS
      E(1) = DBLE(EC)*RCPMV + PM(1)
      PXYZ(2) = 0.
      PXYZ(6) = 0.
      PXYZ(10) = 0.
      CALL P1CLI
C     CALC'S X,Y,Z MOM COORD'S OF INC. PART.(PXYZ(1-5-9))AND P1OE1 = PZ1
      RLKE =(((E(1)*E(2)-PXYZ(1)*PXYZ(2)-PXYZ(5)*PXYZ(6)-PXYZ(9)*PXYZ(10
     +  )) /DNCMS)-PM(1))/RCPMV
      VALUE1 = RANDC2(ISEED)
      R = SNGL(VALUE1)
      VALUE1 = RLKE
      ITP = ITYP - ITYP/5
      NOPART = 2
      GO TO (170,170,200,120),ITP
  120 CONTINUE
C    TRY (PI-,P) EXCHANGE.
      R  = R  - XSECHE(4,ITP,EC)/HSIG
      IF( R.GT.0.) GO TO 200
C  A (PI-,P) EXCHANGE EVENT  HAS OCCURRED
      IT = 5
      KIND(1) = 3
C  PI 0
      KIND(2) = 1
C  NEUTRON
      PT(2) = 4.D0
      PT(14) = 2.D0
      IK = IT
      PM(3) = POMS
      IF(RLKE - 340.D0) 130,130,140
  130 CALL CALMUD(SNT,INPT)
      CALL CRDET(51,PMDX,RLKE)
C            DIF PI--P EXCHG
      GO TO 370
  140 I3 = 1
      IF(RLKE-1000.D0) 150,160,160
  150 I3 = 2
      VALUE1 = RLKE - 340.D0
  160 CALL ROUT16(PMDX)
C  DIF PI--P EXCHG 2500-1000, 1000-340,  340- 0
      GO TO 440
  170 CONTINUE
C    TRY NUCLEON - P  DBLE  PRODUCTION.
      IF(EC.LT.ETH(2,ITP)) GO TO 200
      R   = R  -  XSECHE(2,ITP,EC)/HSIG
      IF( R.GT.0. ) GO TO 200
C    DBLE PRODUCTION HAS OCCURRED.
      NOPART =4
      IPPP = 0
  180 NNO = ITYP
      E1NC  = DBLE(EC)
      CALL CISOB
      KNO = 2
      DO 190 NOO = 1,NOPART
         KIND(NOO) = IDINT( DOUT(KNO)) - 1
         EP(NOO) = SNGL ( DOUT(KNO+1))
         ALF(NOO) = SNGL ( DOUT(KNO+4))
         BET(NOO) = SNGL ( DOUT(KNO+5))
         GAM(NOO) = SNGL ( DOUT(KNO+6))
  190 KNO = KNO + 7
      GO TO 310
  200 CONTINUE
C  TRY SNGL PRODUCTION.
      IF(EC .LT. ETH(1,ITP)) GO TO 210
      R  = R -  XSECHE(1,ITP,EC)/HSIG
      IF( R.GT.0.) GO TO 210
C    NUCLEON - P ,PI+ -P, OR PI- -P  SNGL PRODUCTION HAS OCCURRED.
      NOPART =3
      IPPP = -1
      GO TO 180
  210 CONTINUE
C  AN ELASTIC EVENT HAS OCCURRED.
      GO TO (230,240,340,220,390,220,220),ITYP
  220 CALL CERROR('CPCOL2$')
      WRITE(IO,10100) ITYP
10100 FORMAT(' Wrong particle type = ',I2,' in CPCOL ')
  230 I3 =7
      IT =18
      GO TO 250
  240 I3 = 4
      IT = 15
  250 CALL ROUT20(DCIN(1),DCLN(1),DCHN(1),PDCI(1),PDCH(1))
C ELAS DIF XSECTS-NP 300-740,NP 0-300, NP 660-3500, PP 500-1000,PP 660-3
C     SETS PT(2)=1.-PROT,2.-NEUT,PT(14)=1.,PM(3)= DNCMS
C     CALC'S CST(SCAT COS) FOR EC GT (500 FOR PROT,740 FOR NEUTS)
      I3 = I3
      IGO = I3-4
      GO TO (330 ,260 ,270 ,280 ),IGO
C      I3 =   5    6    7    8
  260 SNT = DSQRT(1.D0 - CST*CST)
      GO TO 280
  270 CALL CAPOL1(CST,SNT)
  280 CALL CESWH
  290 IF(IT.EQ.5) GO TO 300
      KIND(1) = ITYP - 1
      KIND(2) = 0
C    PROTON
  300 CONTINUE
      EP(1)= SNGL( PT(3) )
      ALF(1)=SNGL( PT(8) )
      BET(1)=SNGL( PT(9) )
      GAM(1)=SNGL( PT(10))
      EP(2)= SNGL( PT(15))
      ALF(2)=SNGL( PT(20))
      BET(2)=SNGL( PT(21))
      GAM(2)=SNGL( PT(22))
  310 DO 320  I = 2,4
  320 RANDI(I) = RANDS(I)
      RETURN
  330 I3=4
      CALL ROUT15(PPDC(1))
C      CALC'S CST(SCAT COS) FOR EC LT 740 MEV
      GO TO 260
  340 I3 =1
      IT =1
C     PI+-P ELAS
  350 CALL ROUT11(PPDC (1))
C  TAPCRS(248)  PI+-P  LT 340 MEV.
      I3 = I3
      GO TO (380,360,360,370),I3
  360 CALL CERROR('CPCOL3$')
      WRITE(IO,10200) I3
10200 FORMAT(' I3 = ',I3,' IN CPCOL')
  370 CST = CRDT(2)- DABS(SNT*(CRDT(2)-CRDT(1)))
      GO TO 260
  380 I3 =1
      CALL ROUT15(PPDC(1))
C   PI+-P DIF ELAS FOR1.-2.5 GEV AT 3401,FOR .34 -1. AT 3231.
      I3 = I3
      GO TO 260
  390 IT= 3
C   PI--P ELAS
      I3= 2
      PT(2) = 5.D0
      PT(14)= 1.D0
      IK= IT
      PM(3) = PNMS
      IF(RLKE - 340.D0) 400,400,410
  400 CALL CALMUD(SNT,INPT)
      CALL CRDET(51,PMDD(1),RLKE)
      GO TO 370
  410 I3 =1
      IF(RLKE - 1000.D0) 420,430,430
  420 I3 = 2
      VALUE1 = RLKE - 340.D0
  430 CALL ROUT16(PMDD(1))
  440 I3 = I3
      IF( I3) 260,450,460
  450 I3 = 3
      CALL ROUT15(PPDC(1))
      GO TO 260
  460 CONTINUE
      GO TO 360
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALQDK
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      UNIV=PNIDK(6)*PNIDK(6)
C     M(P1) SQUARED  DECAY PION MASS SQUARED
      PNIDK(7)=(PNIDK(1)*PNIDK(1)+UNIV-SQNM)/(2.0*PNIDK(1))
C     E(PI)PRIME  DECAY PION ENERGY PRIME
      PNIDK(8)=DSQRT(PNIDK(7)*PNIDK(7)-UNIV)
C     DECAY PION MOMENTUM PRIME  P(D)
      CALL CAPOL1(PNIDK(20),PNIDK(21))
C     COS THETA, SIN THETA
      CALL CAAZIO(PNIDK(22),PNIDK(23))
C     COS PHI, SIN PHI
      PNIDK(9)=PNIDK(22)*PNIDK(21)*PNIDK(8)
C     DECAY PION X MOMENTUM COMPONENT PRIME
      PNIDK(10)=PNIDK(21)*PNIDK(23)*PNIDK(8)
C     P(P1)PRIME Y
      PNIDK(11)=PNIDK(20)*PNIDK(8)
C     P(P1)PRIME Z
      UNIV=PNIDK(9)*PNIDK(2)+PNIDK(10)*PNIDK(3)+PNIDK(11)*PNIDK(4)
C     P P1 PRIME DOT P
      PNIDK(12)=(PNIDK(7)*PNIDK(5)+UNIV)/PNIDK(1)
C     DECAY PION ENERGY  E(PI)
      PNIDK(13)=PNIDK(5)-PNIDK(12)
      UNIV=(((PNIDK(5)/PNIDK(1))-1.0)*UNIV)/(PNIDK(2)*PNIDK(2)+
     +PNIDK(3)*PNIDK(3)+PNIDK(4)*PNIDK(4))
C     (E/M-1.0)*P(P1)PRIME DOT P/P SQUARED
      UNIVE=PNIDK(7)/PNIDK(1)
C     E PI PRIME OVER MASS
      DO10 I=2,4
         PNIDK(I+12)=PNIDK(I)*(UNIV+UNIVE) +PNIDK(I+7)
   10 PNIDK(I+15)=PNIDK(I)-PNIDK(I+12)
      RETURN
C     PION MOMENTUM COMPONENTS AND NUCLEON MOMENTUM
C     COMPONENTS
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQENE(Z)
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      DIMENSION Z(380)
      SAVE
C
      CD=COM*1.0D2
      I=IDINT(CD+1.00D0)
      AZ=Z(I)
      IF(I.EQ.1)GOTO150
   10 BZ=Z(I+1)
      IF(101-(I+1))70,20,30
   20 CZ=BZ+5.0D-1*(BZ-AZ)
      GOTO40
   30 CZ=Z(I+2)
   40 XZ=CD-DFLOAT(I-1)
      SCA=CZ-AZ
C F(2)-F(0)
   50 SBA=BZ-AZ
C F(1)-F(0)
      SQA=AZ*AZ
C F(0)**2
      SQAC=SQA-CZ*CZ
C F(0)**2-F(2)**2
      SQBA=BZ*BZ-SQA
C F(1)**2-F(0)**2
      RB=SQAC+SQBA+SQBA
C (ASQ-CSQ)+2(BSQ-ASQ)
CZ
CZ  changed in order to keep exponent small 5/21/92
      RC=AZ*1.0D-20*CZ*SCA-SBA*1.0D-20*(2.0D0*AZ*BZ+XZ*(BZ-CZ)*SCA)
CZ   RC is 1E-20 smaller than it supposed to be !!!!
      RA=SCA-SBA-SBA
C (C-A)-2(B-A)
      IF(RA.NE.0.0)GOTO60
      COM=AZ+XZ*SBA
      GOTO80
   60 CONTINUE
CZ                               \/  factor 1E-20 in RC !!
      DISC=RB*1.0D-20*RB-4.0D0*RA*RC
      IF(DISC)70,90,90
C B**2-4AC
   70 CALL CERROR('CQENE1$')
   80 RETURN
CZ                      \/ correct for factor 1E-20
   90 DISC=DSQRT(DISC)*1.0D10
CZ   end of change
CZ
      PLUS=(DISC-RB)/(RA+RA)
      AMINUS=(-RB-DISC)/(RA+RA)
      IF(I.EQ.1)GOTO160
  100 IF(PLUS.GT.BZ)GOTO120
      IF(PLUS.LT.AZ)GOTO120
      IF(AMINUS.GT.BZ)GOTO110
      IF(AMINUS.GE.AZ)GOTO140
  110 COM=PLUS
      GOTO80
  120 IF(AMINUS.GT.BZ)GOTO70
      IF(AMINUS.LT.AZ)GOTO70
  130 COM=AMINUS
      GOTO80
  140 RA=XZ*SBA+AZ
      RB=DABS(RA-AMINUS)
      RC=DABS(RA-PLUS)
      IF(RB.GT.RC)GOTO110
      GOTO130
  150 CZ=Z(I+1)
      SCA=CZ-AZ
      BZ=AZ+SCA*7.071067812D-1
      XZ=CD+CD
      GOTO50
C (CZ-AZ)(CZ-AZ)=C,CZ=MASS FOR R=1,AZ=MASS FOR R=0, C=CONST.FOR PARABOLA
C (M-AZ)(M-AZ)=0.5*C,DETERMINES MASS,BZ,FOR R=1/2
  160 BZ=CZ
      XZ=XZ-CD
      SBA=CZ-AZ
      GOTO100
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQLP19
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      UNIV = RANDC2(ISEED)
      PT(2)=1.0
      PT(26)=1.0
      PT(14)=3.0
      PT(16)=POMS
      IF(ISW(12))10,10,140
   10 IF(UNIV-.25)20,20,110
   20 IF(ISW(4))40,30,40
   30 PT(2)=2.0
   40 UNIV = RANDC2(ISEED)
      IF(UNIV-.66666667)50,50,90
   50 PT(14)=4.0
   60 IF(ISW(4))80,70,80
   70 PT(26)=2.0
   80 RETURN
   90 PT(16)=PNMS
      IF(ISW(4))70,100,70
  100 PT(14)=5.0
      GOTO80
  110 IF(ISW(4))130,120,130
  120 PT(26)=2.0
      GOTO90
  130 PT(2)=2.0
      PT(16)=PNMS
      GOTO80
  140 IF(UNIV-.5)150,150,190
  150 IF(ISW(4))160,170,160
  160 PT(2)=2.0
  170 UNIV = RANDC2(ISEED)
      IF(UNIV-.33333333)90,90,180
  180 PT(14)=4.0
      GOTO60
  190 IF(ISW(4))210,200,210
  200 PT(2)=2.0
  210 UNIV = RANDC2(ISEED)
      IF(UNIV-.66666667)220,220,230
  220 PT(14)=4.0
      IF(ISW(4))70,80,70
  230 PT(16)=PNMS
      IF(ISW(4))240,70,240
  240 GO TO 100
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQLP28
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      R = RANDC2(ISEED)
      IF(ISW(13))230,10,230
   10 IF(R-.6)20,20,120
   20 PT(4)=PNMS
      R = RANDC2(ISEED)
      IF(ISW(4))30,90,30
   30 IF(R-.33333333)40,40,70
   40 PT(26)=5.0
   50 PT(28)=PNMS
   60 RETURN
   70 PT(26)=4.0
   80 PT(38)=2.0
      GOTO60
   90 PT(2)=5.0
      PT(14)=2.0
      IF(R-.33333333)100,100,110
  100 PT(28)=PNMS
      GOTO80
  110 PT(26)=4.0
      GOTO60
  120 R = RANDC2(ISEED)
      IF(ISW(4))130,180,130
  130 IF(R-.66666667)140,140,160
  140 PT(2)=4.0
  150 R = RANDC2(ISEED)
      IF(R-.66666667)110,110,100
  160 PT(14)=2.0
  170 PT(4)=PNMS
      GOTO150
  180 IF(R-.66666667)190,190,220
  190 PT(2)=4.0
  200 PT(14)=2.0
  210 R = RANDC2(ISEED)
      IF(R-.66666667)70,70,40
  220 PT(2)=5.0
      PT(4)=PNMS
      GOTO210
  230 IF(R-VALUE1)240,240,270
  240 PT(4)=PNMS
      IF(ISW(4))260,250,260
  250 PT(2)=5.0
      PT(14)=2.0
      GOTO50
  260 PT(38)=2.0
      GOTO40
  270 R = RANDC2(ISEED)
      IF(ISW(4))280,310,280
  280 IF(R-.33333333)290,290,300
  290 PT(4)=PNMS
      GOTO200
  300 PT(2)=4.0
      GOTO210
  310 IF(R-.33333333)320,320,330
  320 PT(2)=5.0
      GOTO170
  330 PT(14)=2.0
      GOTO140
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQLPHA
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      UNIV = RANDC2(ISEED)
      IF(VALUE3)300,10,140
   10 IF(UNIV-VALUE1)20,20,120
   20 IF(ISW(11))40,30,40
   30 PT(2)=5.0
      PT(26)=2.0
   40 PT(4)=PNMS
      PM(4)=PNMS
      UNIV = RANDC2(ISEED)
      IF(UNIV-VALUE2)50,50,70
   50 PT(14)=4.0
   60 RETURN
   70 IF(ISW(11))110,80,110
   80 PT(26)=1.0
   90 PT(14)=5.0
  100 PT(16)=PNMS
      GOTO60
  110 PT(26)=2.0
      GOTO100
  120 PT(2)=4.0
      IF(ISW(11))100,130,100
  130 PT(14)=5.0
      GOTO110
  140 IF(UNIV-VALUE1)150,150,200
  150 PM(4)=PNMS
      IF(ISW(11))160,190,160
  160 PT(2)=5.0
  170 PT(16)=PNMS
  180 PT(4)=PNMS
      GOTO60
  190 PT(14)=5.0
      PT(26)=2.0
      GOTO170
  200 IF(UNIV-VALUE2)210,210,250
  210 PT(2)=4.0
      UNIV = RANDC2(ISEED)
      IF(UNIV-VALUE3)240,240,220
  220 IF(ISW(11))50,230,50
  230 PT(26)=2.0
      GOTO50
  240 IF(ISW(11))110,90,110
  250 PM(4)=PNMS
      PT(4)=PNMS
      UNIV = RANDC2(ISEED)
      IF(UNIV-.66666667)260,260,280
  260 IF(ISW(11))230,270,230
  270 PT(2)=5.0
      GOTO50
  280 IF(ISW(11))90,290,90
  290 PT(26)=2.0
      GOTO160
  300 IF(UNIV-VALUE1)310,310,340
  310 PM(4)=PNMS
      PT(4)=PNMS
      UNIV = RANDC2(ISEED)
      IF(VALUE3+1.0)330,320,330
  320 IF(UNIV-.33333333)90,90,230
  330 PT(2)=5.0
      IF(UNIV-.33333333)110,110,50
  340 IF(UNIV-VALUE2)350,350,380
  350 PT(2)=4.0
      UNIV = RANDC2(ISEED)
      IF(VALUE3+1.0)370,360,370
  360 IF(UNIV-.66666667)50,50,110
  370 IF(UNIV-.66666667)230,230,90
  380 PM(4)=PNMS
      PT(4)=PNMS
      IF(VALUE3+1.0)390,160,390
  390 PT(14)=5.0
      GOTO110
      END
*CMZ :  1.01/00 03/06/93  19.40.16  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQNGID
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
C     ******************************************************************
C****    CALCULATES  COS AND SIN THETA,SIN AND COS PHI    **************
C     ******************************************************************
      ICURR= CURR(1)
      IT=0
      GO TO(10,10,30,30,30),ICURR
C****  INCIDENT PARTICLE - NUCLEON
   10 IF(IT.EQ.21.OR.IT.EQ.22)GO TO 20
C****  SINGLE  PRODUCTION
      IF(RLKE.GT.3500.0D0) CALL CERROR('CQNGID1$')
      IF(RLKE.LT.500.0D0)GO TO 70
      TESISO= 0.75D0
      IF(RLKE.LT.1000.0D0)GO TO 50
      TESISO= 0.5D0
      IF(RLKE.LT.1300.0D0)GO TO 50
      TESISO= 0.25D0
      IF(RLKE.LT.2500.0D0)GO TO 50
      GO TO 60
C****  DOUBLE PRODUCTION
   20 IF(RLKE.GT.3500.0D0) CALL CERROR('CQNGID2$')
      GO TO 60
C**** INCIDENT PARTICLE-PION
   30 R = RANDC2(ISEED)
      IF(RLKE.GT.2500.0D0) CALL CERROR('CQNGID3$')
      CST= -0.9999995D0
      SNT=  0.003162D0
      IF(IT.NE.11)GO TO 40
      IF(R.LE.0.75D0)GO TO 70
      GO TO 80
C****  (PI+)-(P),(PI-)-(N)
C****  (PI0)-(N),(PI0)-(P)
   40 IF(IT.NE.12.AND.IT.NE.28) CALL CERROR('CQNGID4$')
      IF(RLKE.LT.500.0D0)CST=-CST
      IF(R.LE.0.80D0)GO TO 70
      GO TO 80
   50 R = RANDC2(ISEED)
      IF(R.LE.TESISO)GO TO 70
C**** BACKWARD/FORWARD
   60 R = RANDC2(ISEED)
C****  TEST FOR DIRECTION
      CST= 0.9999995D0
      SNT= 0.003162D0
      IF(R.LE.0.5)GO TO 80
      CST= -0.9999995D0
      GO TO 80
C****  ISOTROPIC
   70 CALL CAPOL1(CST,SNT)
C****  CALCULATES  COS,SIN PHI
   80 CALL CAAZIO(SOPC,SOPS)
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQOLL
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      A=PM(4)*PM(4)
      COL(15)=0.0
      COL(1)=E(1)+E(2)
C     TOTAL ENERGY PARTICLES 1 AND 2
      DO10 I=1,3
   10 COL(I+1)=PM(I)*PM(I)
C     MASS PARTICLE I SQD.
      COL(5)=COL(3)+COL(2)+2.0*(E(1)*E(2)-(PXYZ(1)*PXYZ(2)+PXYZ(5)*
     1PXYZ(6)+PXYZ(9)*PXYZ(10)))
      COL(6)=DSQRT(COL(5))
      COL(7)=COL(6)/COL(1)
C     GAM
      COL(8)=2.0*COL(6)
      COL(9)=(COL(4)+COL(5)-A)/COL(8)
      COM2=COL(9)*COL(9)
   20 IF(COL(4)-2.9882156E27)30,30,50
C GT,PM(3)=ISOBAR--LTE,TEST FOR ROUNDOFF RANGE,(MIN)SQD+OR-5E23
   30 IF(COL(4)-2.9872156E27)60,40 ,40
C     LT,PION OR NUCLEON MASS=PM(3)
   40 COL(4)=2.9877156E27
      PM(3) = 5.466005D13
   50 IF(COM2-COL(4))70,90,90
   60 IF(COL(4)-SQNM)50,50,120
C     LTE,HAVE NUCLEON OR PION--GT,GO TO ERROR
   70 IF(COM2-9.9D-1*COL(4)) 90,80,80
   80 COM2 = COL(4)
      COL(9) = PM(3)
   90 COL(10)=DSQRT(COM2-COL(4))
C     P3 PRIME
      IF(IK)100,170,100
  100 COL(11)=(COL(5)+COL(2)-COL(3))/COL(8)
C     E1 PRIME
      COL(12)=DSQRT(COL(11)*COL(11)-COL(2))
C     P1 PRIME
      COL(13)=(COL(7)*E(1)-COL(11))/COL(12)
C     BETA
      COM=1.0-(COL(13)*COL(13)+COL(7)*COL(7))
      IF(COM-5.0E-6)110,150,150
  110 IF(COM+5.0E-6)120,140,140
  120 COL(15)=1.0
C     ERROR
  130 RETURN
  140 COL(14)=.002236067977
      GOTO160
  150 COL(14)=DSQRT(COM)
C     ALPHA
  160 E(3)=(COL(9)+COL(10)*(COL(13)*CST+COL(14)*SOPC*SNT))/COL(7)
      E(4)=COL(1)-E(3)
      GOTO130
  170 DO180 I=11,14
  180 COL(I)=0.0
      E(3)=0.0
      E(4)=0.0
      GOTO130
C     FOR PART AT REST E1 AND P1 PRIME,ALPHA AND BETA NOT
C     CALCULATED. E(3) ANDE(4) DONE LATER
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE QOLLM
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      IF(IK)10,60,10
   10 UNIV=E(2)+COL(6)-COL(11)
      UNIVE=E(1)+COL(11)
      UNIVER=COL(1)+COL(6)
      K=16
      DO20 I=1,9,4
         COL(K)=(PXYZ(I)*UNIV-PXYZ(I+1)*UNIVE)/UNIVER
         COL(K+3)=(PXYZ(I)+PXYZ(I+1))/COL(1)
C     VX
   20 K=K+1
      COL(22)=(-PXYZ(9)*PXYZ(6))/COL(1)
C     QX
C     ABBREVIATED FORM SINCE PXYZ(1)=PXYZ(5)=0.0
      COL(23)=(PXYZ(2)*PXYZ(9))/COL(1)
C     QY
C     ABBREVIATED FORM SINCE PXYZ(1)=PXYZ(5)=0.0
      COL(24)=0.0
C     ABBREVIATED FORM SINCE PXYZ(1)=PXYZ(5)=0.0
      A=SNT/COL(14)
      B=A*COL(10)
C     (-BETA*COS PHI*SIN THETA/ALPHA + COS THETA)/P1P*P3P
      UNIV=COL(10)*(CST-A*SOPC*COL(13))/COL(12)
      UNIVE=B*SOPS/COL(12)
C     P3P*SIN PHI*SIN THETA/P1P*ALPHA
      UNIVER=(SOPC*B)+((E(3)+COL(9))/(COL(7)+1.0))
C     COS PHI*SIN THETA*P3P/ALPHA  +  (E3+E3P)/(1.0+GAMMA)
      K=19
      DO30 I=3,11,4
         PXYZ(I)=COL(K)*UNIVER+COL(K+3)*UNIVE+COL(K-3)*UNIV
   30 K=K+1
      DO40 I=1,9,4
   40 PXYZ(I+3)=PXYZ(I)+PXYZ(I+1)-PXYZ(I+2)
   50 RETURN
   60 DO70 I=16,17
         COL(I)=0.0
   70 COL(I+3)=0.0
      COL(18)=PXYZ(9)*PM(2)/COL(6)
C     P(1),Z *M2/M=P(BAR PRIME)1,Z
      COL(21)=PXYZ(9)/COL(1)
C     VZ VELOCITY
      DO80 I=22,24
   80 COL(I)=0.0
C     CROSS PRODUCT P1 PRIME X V
      PXYZ(3)=COL(10)*SNT*SOPC
C     X COMPONENT P3 BAR =P3 PRIME X SIN THETA X COS PHI
      PXYZ(7)=COL(10)*SNT*SOPS
C     Y COMP. P3 BAR =P3 PRIME X SIN THETA X SIN PHI
      PXYZ(11)=COL(10)*CST
      Z=PXYZ(9)/COL(6)
      PXYZ(11)=PXYZ(11)+(Z*PXYZ(9)*PXYZ(11))/(COL(1)+COL(6))+Z*COL(9)
C     Z COMP. P3 BAR=P3 PRIME COS THETA+(P1Z SQ*P3Z (PRIME)COS
C     THETA/(E PRIME*(E+E PRIME))+P1Z*E3 PRIME/E PRIME
      E(3)=DSQRT(PXYZ(3)*PXYZ(3)+PXYZ(7)*PXYZ(7)+PXYZ(11)*PXYZ(11)+
     +PM(3)*PM(3))
      DO90 I=1,9,4
   90 PXYZ(I+3)=PXYZ(I)-PXYZ(I+2)
      E(4)=DSQRT(PXYZ(4)*PXYZ(4)+PXYZ(8)*PXYZ(8)+PXYZ(12)*PXYZ(12)
     ++PM(4)*PM(4))
      IF(PT(38))50,100,50
  100 PT(3)=((E(4)-PM(4))/RCPMV)+PT(3)
      GOTO50
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE QOUT17(T,B,R,W,G)
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
C
      DIMENSIONT(117),B(101),R(117),W(234),G(234)
      SAVE
C
      IF(I3)10  ,10  ,160
   10 PT(38)=0.0
C     1-ALPHA  PART.6+1
      VALUE1=RLKE-180.0
      CALL QRDET(1,T(1),VALUE1)
   20 COM2=CRDT(1)
      FTR =DNCMS*RLKE*2.0*RCPMV+2.9877156E27
C     E**2=MIN**2+NCNMS*RLKE*2*RCPMV
      UNIVER=DSQRT(FTR )
C     E
   30 VALUE2 = RANDC2(ISEED)
      COM=VALUE2*COM2
C     R-PRIME
      CALL CQENE (B(1))
      COM1=(COM*COM+FTR -.501264E26)/(2.0*UNIVER)
C     M1R PRIME)**2+E**2-2(PNMS)/2E=E ALPHA
      A=COM1*COM1-COM*COM
      IF(A)40  ,50  ,50
   40 PACNT=PACNT+1.0
      GOTO30
   50 UNIVE=(UNIVER-COM1)*COM1*(DSQRT(A)/UNIVER)
C     ((E BETA*E ALPHA*P ALPHA)/E)=F(M,TR)
      CALL QRDET(1,R(1),VALUE1)
C     (PI-NUC)FMAX(RLKE)ISOBAR SAMPLING S.P.
      COM1 = RANDC2(ISEED)
      IF((UNIVE/CRDT(1))-COM1)30  ,60  ,60
C     RANDOM NO. LESS OR EQUAL THAN F(M,TR)/FMAX(TR)
   60 CALL CQNGID
      PM(4)=POMS
      PM(3)=COM
      PT(2)=3.0
      PT(4)=POMS
      PT(14)=3.0
      PT(16)=POMS
      PT(26)=1.0
      PT(28)=DNCMS
      IF(ISW(9))80  ,70  ,80
   70 IF(ISW(10))120 ,110 ,120
   80 IF(ISW(10))130 ,90 ,130
   90 I3=-1
  100 RETURN
  110 VALUE1=.4
      VALUE2=.66666667
      VALUE3=0.0
      GOTO150
  120 CALL QRDET(2,W(1),VALUE1)
C     (PICH-P)FRACT. FIN.STA.WITH RECL. PI1 PI0 L.E.
      VALUE3=.33333333
      GOTO140
  130 CALL QRDET(2,G(1),VALUE1)
      VALUE3=STRKP
C     (PIN-P)FRACT.FIN.STA.WITH RECL.PI1 PIO L.E.
  140 VALUE1=CRDT(1)
      VALUE2=CRDT(2)
  150 CALL CQLPHA
  160 PT(3)=0.0
      PT(15)=0.0
      PT(27)=0.0
      PT(39)=0.0
  170 CALL CQOLL
      IF(COL(15))90 ,180 ,90
  180 IF(PT(38))190 ,200 ,190
  190 I3=0
      GOTO100
  200 PT(39)=0.0
      IF(IK)210 ,220 ,210
  210 PT(3)=((E(4)-PM(4))/RCPMV)+PT(3)
  220 I3=1
      GOTO100
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE QOUT18
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
      GOTO(10  ,20  ,80  ,120 ,80  ,100 ),I3
   10 I=3
      COL(15)=1.0
      K=27
      GOTO30
   20 I=3
      COL(15)=4.0
      K=15
   30 PNIDK(1)=PM(I)
      J=I
      DO40  L=2,4
         PNIDK(L)=PXYZ(J)
   40 J=J+4
      PNIDK(5)=E(I)
      PNIDK(6)=PT(K-11)
      CALL CALQDK
      IF(K-27)60  ,50  ,60
   50 PT(15)=PT(15)+((PNIDK(12)-PNIDK( 6))/RCPMV)
   60 PT(K)=PT(K)+((PNIDK(13)-DNCMS)/RCPMV)
      I3=1
   70 IV=K
      RETURN
   80 COL(15)=3.0
      K=15
      IF(PT(14)-2.0)90 ,90 ,120
   90 I3=2
      GOTO70
  100 L=14
      DO110 M=5,7
         PT(M)=PNIDK(L)
         PT(M+12)=PNIDK(L+3)
  110 L=L+1
      PT(11)=PNIDK(12)
      PT(12)=PNIDK(6)
      I=4
      K=39
      COL(15)=5.0
      GOTO30
  120 I1=3
  130 K=12*I1-33
  140 IF(I1-4)150 ,160 ,170
  150 I2=-1
      GOTO200
  160 I2=0
      GOTO200
  170 IF(I1-5)160 ,190 ,180
  180 I3=4
      GOTO70
  190 I2=1
  200 IF(PT(K))210 ,220 ,210
  210 CALL CQSTOR
  220 I1=I1+1
      GOTO130
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE QOUT19
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
   10 PT(3)=PT(3)+((PT(11)-PT(12))/RCPMV)
C     COLLISION ALLOWED
      K=3
      GOTO100
   20 I3=-1
   30 RETURN
   40 I2=2
   50 I1=(K/12)+3
   60 CALL CQSTOR
   70 IF(K-15)80  ,90  ,120
   80 K=15
      GOTO40
   90 K=27
      PT(27)=PT(27)+((PNIDK(12)-PT(K+1))/RCPMV)
  100 IF(K-15)40  ,110 ,110
  110 I2=0
      GOTO50
  120 IF(K-27)20 ,130 ,140
  130 IF(PT(39))140 ,140 ,150
  140 I3=0
      GOTO30
  150 I2=1
      K=39
      GOTO50
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE QOUT21(V,W,X,Y,Z)
      IMPLICIT REAL *8  (A-H,O-Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
C
      REAL*8 V(161),W(101),X(161),Y(130),Z(176)
      SAVE
C
      VALUE2=RLKE*4.81633308E24+9.0554256E27
C     E(TR)**2=RLKE*RCPMV*2*NCMS+4*NCMS**2
      VALUE3=DSQRT(VALUE2)
      GOTO(10  ,130 ,140 ,270 ),I3
   10 ISW(12)=0
   20 PT(38)=0.0
      I1=0
   30 ANS=RLKE
   40 VALUE1=ANS-300.0
      CALL QRDET(1,V(1),VALUE1)
C     (NUC-NUC) F(TR) ISOBAR SAMPLING
      FTR=CRDT(1)
   50 SN = RANDC2(ISEED)
      COM=SN*FTR
C     R PRIME=F(TR)*RANDOM
      CALL CQENE (W(1))
C     (NUC-NUC)MASS OF ISOBAR S.P.    M(R PRIME)
      IF(I1)160 ,60  ,170
   60 COM1=(COM*COM-SQNM+VALUE2)/(2.0*VALUE3)
C     E GAMMA
      A=COM1*COM1-COM*COM
      IF(A)70  ,80  ,80
   70 PGCNT=PGCNT+1.0
      GOTO50
   80 UNIVER=DSQRT(A)*COM1*((VALUE3-COM1)/VALUE3)
C     F(M,TR)=P GAMMA*E GAMMA*E DELTA/E
      CALL QRDET(1,X(1),VALUE1)
C     (NUC-NUC)FMAX(TR) ISOBAR SAMPLING S.P.
      COM1 = RANDC2(ISEED)
      IF(COM1-(UNIVER/CRDT(1)))90  ,90  ,50
   90 PM(4)=DNCMS
      PM(3)=COM
  100 CALL CQNGID
      PT(4)=DNCMS
      PT(28)=DNCMS
  110 CALL CQLP19
  120 RETURN
  130 ISW(12)=2
      GOTO20
  140 ISW(13)=0
  150 I1=-1
      ANS=((VALUE3-.708E13)**2-9.0554256E27)/4.81633308E24
      GOTO40
C     TR PRIME     COM1=RLKE PRIME
  160 COM1=((VALUE3+DNCMS-COM)**2-9.0554256E27)/4.81633308E24
      COM2=COM
      ANS=COM1
      COM4=FTR
      I1=1
      GOTO40
  170 COM1=(COM2*COM2-COM*COM+VALUE2)/(2.0*VALUE3)
C     E EPSILON
      A=COM1*COM1-COM2*COM2
      IF(A)180 ,190 ,190
  180 PECNT=PECNT+1.0
      GOTO200
C     F(M1,M2,TR)=P EPSILON*E EPSILON*E ZETA/E
  190 UNIVER=DSQRT(A)*COM1*((VALUE3-COM1)/VALUE3)
      VALUE1=RLKE-920.0
      CALL QRDET(1,Y(1),VALUE1)
C     (NUC-NUC)FMAX(TR) ISOBAR SAMPLING D.P.  FMAX(M1,M2,TR)
      SN = RANDC2(ISEED)
      IF(SN-(UNIVER*FTR/(CRDT(1)*COM4)))210 ,210 ,200
  200 FTR=COM4
      I1=-1
      GOTO50
  210 VALUE1 = RANDC2(ISEED)
      IF(VALUE1-.5)220 ,220 ,230
  220 PM(3)=COM2
      PM(4)=COM
      GOTO240
  230 PM(3)=COM
      PM(4)=COM2
  240 CALL CQNGID
      PT(16)=DNCMS
      PT(40)=DNCMS
      IF(ISW(13))250 ,260 ,250
  250 CALL QRDET(1,Z(1),RLKE)
      VALUE1=CRDT(1)
C     (N-P)FRACT.FIN.STA.3/2 L.E.
  260 PT(2)=3.0
      PT(4)=POMS
      PT(14)=1.0
      PT(26)=3.0
      PT(28)=POMS
      PT(38)=1.0
      CALL CQLP28
      GOTO120
  270 ISW(13)=2.0
      GOTO150
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE QRDET(NODATA,DATA,ENER)
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      DIMENSION DATA(380)
      SAVE
C
      IE=DABS(ENER/20.0)
      UNIV=(ENER-DFLOAT(IE)*20.0)/20.0
      DO10 I=1,25
   10 CRDT(I)=0.0
      K=(NODATA*IE)+1
      IF(INPT)50 ,20 ,50
   20 N=NODATA
   30 L=K+NODATA
      DO40 I=1,N
         CRDT(I)=(DATA(L)-DATA(K))*UNIV+DATA(K)
         K=K+1
   40 L=L+1
      INPT=0
      RETURN
   50 K=INPT-1+K
      N=2
      GOTO30
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CQSTOR
      IMPLICIT REAL *8  (A-H,O-Z)
*KEEP,CBERT3.
      REAL*8 TAPCRS(29850),DUME1(4679),CURR(11),DUME2(169),DUME3(35)
      COMMON/CBERT/ DUME1,CURR,DUME2,
     +               RANDS(4),DUME3,TAPCRS
      INTEGER *2  RANDS
C
*KEEP,CISOB2.
      REAL*8 PM(4),PART(5),CRDT(25),PT(48),E(4),
     +    PXYZ(12),COL(24),PNIDK(23),OUT(40),
     +    ANDIT,EINC,CASESN,PRTIN,TRSYM,
     +    PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,
     +    BEGRU,STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,
     +    CST,COM2,VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A
      DIMENSION ISW(13)
      COMMON/CISOBR/ANDIT,EINC,CASESN
      COMMON/CISOBR/ PM,PART,CRDT,PT,E,PXYZ,COL,PNIDK,OUT,PRTIN,TRSYM,
     + PGCNT,PACNT,VALUE2,PNMS,SQNM,DNCMS,RCPMV,POMS,VALUE1,ANS,BEGRU,
     + STRKP,RLKE,P1OE1,POLC,POLS,SOPC,SOPS,P2,SN,COM,SNT,CST,COM2,
     + VALUE3,UNIV, UNIVE, UNIVER, COM1, FTR, A,
     + ISW,NRT,LN,INPT,NO,IV,IP,I1,I2,IK,I3,NOR
C
*KEND.
      SAVE
C
      L=(I1*12)-28
      IF(I2)10,60,70
   10 JJ=0
      IF(PM(3)-DNCMS)30,30,20
   20 I1=I1+1
      JJ=1
C     X-Y-Z-COORDINATES OF COLLISION POINT
   30 UNIV=DSQRT(PXYZ(I1)*PXYZ(I1)+PXYZ(I1+4)*PXYZ(I1+4)+PXYZ(I1+8)*
     +PXYZ(I1+8))
      K=I1+8
      DO40 I=I1,K,4
         PT(L)=PXYZ(I)/UNIV
   40 L=L+1
      I1=I1-JJ
   50 RETURN
   60 K=14
      GOTO90
   70 IF(I2-2)80,110,110
   80 K=17
   90 UNIV=DSQRT(PNIDK(K)*PNIDK(K)+PNIDK(K+1)*PNIDK(K+1)+PNIDK
     +(K+2)*PNIDK(K+2))
      PT(L-3)=1.0
      J=K+2
      DO100 I=K,J
         PT(L)=PNIDK(I)/UNIV
  100 L=L+1
      GOTO50
  110 UNIV=DSQRT(PT(L-3)*PT(L-3)+PT(L-2)*PT(L-2)+PT(L-1)*PT(L-1))
      K=L-1
      M=L-3
      DO120 I=M,K
         PT(L)=PT(I)/UNIV
  120 L=L+1
      PT(M)=1.0
      GOTO50
      END
*CMZ :  0.92/00 02/12/92  16.02.29  by  Christian Zeitnitz
*-- Author :
      FUNCTION SFLRAF2(X)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      SFLRAF2 = 2.0 * RANDC2(ISEED)
      TEMP = 1.0 - SFLRAF2
      IF(TEMP) 10 ,20 ,20
   10 SFLRAF2 = TEMP
   20 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALSGM(NSGNL,IT,IS,DDE,EM,I,E,S)
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEEP,CBERT2.
      COMMON/CBERT/ DUME(4895),CS(29850)
      REAL*8 DUME,CS,TEMP
C
*KEND.
C
      DIMENSION PPNP(9,2),ENRGY(9)
      DATA ENRGY/1.,  3.,  5.,  8.,  10., 12.5,15., 17.5,20./
      DATA PPNP /1.20,.890,.620,.392,.310,.250,.208,.178,.155,
     +           4.25,2.28,1.62,1.14,.940,.765,.645,.555,.480/
      DATA IEMX /9/
      SAVE
C
      I= IFIX(EM/DDE + 1.)
      E= FLOAT(I-1)*DDE
      IF(EM.LT.20.0.AND.IT.LE.2) GO TO 70
      GO TO (10,30),NSGNL
   10 TEMP = SNGL(CS(I+IS))
      S = TEMP + (EM-E)/DDE*(SNGL(CS(I+1+IS))- TEMP)
   20 RETURN
   30 IF(IT.GT.2) GO TO 60
      IF(I.LT.176) GO TO 50
   40 CALL CERROR('CALSGM1$')
   50 S=  NPSG(IT,I) +(EM-E)/DDE*(NPSG(IT,I+1) - NPSG(IT,I) )
      GO TO 20
   60 IF(I.GT.125) GO TO 40
      IT = IT - 2
      S=  PIPSG(IT,I) + (EM-E)/DDE *(PIPSG(IT,I+1) - PIPSG(IT,I) )
      GO TO 20
C** LOW ENERGY (.LT. 20 MEV) P-P OF N-P XSECTS FOR ELAST. SCATT. WITH H.
   70 CONTINUE
      IF(EM.LT.ENRGY(1)) CALL CERROR('CALSGM2$')
      DO 80  IE = 2,IEMX
         IF(EM.LE.ENRGY(IE)) GO TO 90
   80 CONTINUE
      CALL CERROR('CALSGM3$')
   90 S = ALOG(PPNP(IE-1,IT)) + (EM - ENRGY(IE-1)) /
     +    (ENRGY(IE) - ENRGY(IE-1)) *
     +    (ALOG(PPNP(IE,IT)) - ALOG(PPNP(IE-1,IT)))
      S = EXP(S) * 1.0E-24
      GO TO 20
      END
*CMZ :  1.01/04 10/06/93  14.43.41  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CSHXD
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEND.
C
      DE = 20.
      LOCX(1,1) = 995
      LOCX(2,1) = 1153
      LOCX(3,1) = 3793
      LOCX(4,1)= 0
      LOCX(1,2) = 1283
      LOCX(2,2) = 1441
      LOCX(3,2) = 3969
      LOCX(4,2)= 0
      LOCX(1,3) = 2009
      LOCX(2,3)= 0
      LOCX(3,3) = 3667
      LOCX(4,3)= 0
      LOCX(1,4) = 2243
      LOCX(2,4)= 0
      LOCX(3,4) = 3541
      LOCX(4,4) = 3415
      DO 10 IT =1,4
         DO 10 ID =1,4
   10 ETH(ID,IT) = 0.
      DO 20 IT=1,2
         ETH(1,IT)= 360.
   20 ETH(2,IT)= 920.
      DO 30  IT =3,4
   30 ETH(1,IT)= 180.
      RETURN
      END
*CMZ :  0.90/04 11/09/92  05.11.48  by  Christian Zeitnitz
*-- Author :
      FUNCTION XSECHE(ID,ITP,EC)
*KEEP,CBERT2.
      COMMON/CBERT/ DUME(4895),CS(29850)
      REAL*8 DUME,CS,TEMP
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEND.
C
C   ID =   1          2         3         4
C      SNGL PROD  DBLE PROD  ELASTIC  EXCHANGE
C  ITP =   1          2         3         4
C        PROT       NEUT       PI+       PI-
      ET = ETH(ID,ITP)
      LC =LOCX(ID,ITP)
      I= IFIX( (EC-ET)/DE + 1.)
      E = FLOAT(I-1)*DE + ET
      TEMP = SNGL( CS(I+LC) )
      XSECHE=TEMP + (EC-E)/DE * ( SNGL( CS(I+1+LC) ) - TEMP )
      RETURN
      END
*CMZ :  0.90/00 27/05/92  16.43.05  by  Christian Zeitnitz
*-- Author :
      FUNCTION CZFOI(Z)
C**   USING REVISED DATA (1-70,TWA)
      DIMENSION FLI(13)
      DATA FLI/18.7,42.0,39.0,60.0,68.0,78.0,99.5,98.5,117.0,140.0,
     1150.0,157.0,163.0/,A1/9.76/,A2/58.8/,XP/-0.19/
      IF(Z.GT.13.) GO TO 10
      IZ=IFIX(Z)
      CZFOI=FLI(IZ)
      RETURN
   10 CZFOI=A1*Z + A2 *(Z**XP)
      RETURN
      END
*CMZ :  1.04/03 17/02/95  12.38.47  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   21/05/92
      SUBROUTINE CHETC(DOSKAL)
C*************************************************************
C
C process intranuclear2-cascade and evaporation
C call scaling for smooth transition to FLUKA
C If H-Atoms present -> special particle-H collision
C generate de-exitation gammas
C
C*************************************************************
C
C      Interface common
*KEEP,CALGEA.
C***************************************************************
C
C       CALOR-GEANT Interface common
C
C parameters of incident particle :
C                   IPinc   = particle type a la CALOR
C                   Einc    = kinetic energy
C                   Uinc(3) = direction cosines
C material parameters:
C                   NCEL    = number of elements in mixture (NMTC)
C                             GEANT material no. for MICAP
C                   Amed(I) = mass number
C                   Zmed(I) = charge number
C                   Dmed(I) = Atoms/cm**3 * 1E-24
C                   Hden    = Atoms/cm**3 * 1E-24
C                             of H-Atoms in mixture
C
C particle stack:
C            NPHETC           = number of particles
C            Ekinet(1:NPHETC) = kinetic energy of part.
C            IPCAL(1:NPHETC)  = particle type a la CALOR (extended)
C            UCAL(1:NPHETC,3) = direction cosines
C            CALTIM(1:NPHETC) = age of particle (nsec)
C
C            ATARGT = A no. of target nucleus
C            ZTARGT = Z no. of target nucleus
C
C return of residual nucleus information
C            NRECOL  = no. of heavy recoil products
C            Amed(I) = mass number of residual nucleus
C            Zmed(I) = charge number "          "
C            EXmed   = exitation energy of nucleus
C            ERmed(I)= recoil energy of nucleus
C            IntCal  = type of interaction (GEANT NAMEC index)
C return of cross section of hadronic interaction (CALSIG called)
C            SIG =  x-section
C
C set by CALSIG:
C            ICPROC = -1   undefined
C                   =  0   NMTC called for cross-section
C                   =  1   MICAP called for cross-section
C                   =  2   SKALE(NMTC at 3 GeV) called for cross-section
C                   =  3   FLUKA called for cross-section
C            KCALL : same coding as ICPROC, but is only valid after a
C                    call to GCALOR
C       18/8/92  C.Zeitnitz University of Arizona
C****************************************************************
C
      PARAMETER(EMAXP  = 3.495)
      PARAMETER(EMAXPI = 2.495)
C transition upper limit (GeV) NMTC-FLUKA
      PARAMETER(ESKALE = 10.0)
      PARAMETER(MXCP = 300)
C
      COMMON/ CALGEA / IPINC  , EINC       , UINC(3)   ,NCEL        ,
     +                 HDEN   , AMED(100)  , ZMED(100) ,DMED(100)   ,
     +                 NPHETC ,EKINET(MXCP),IPCAL(MXCP),UCAL(MXCP,3),
     +                 INTCAL , EXMED      , ERMED(100),SIG         ,
     +                 CALTIM(MXCP), ICPROC, NRECOL    ,KCALL       ,
     +                 ATARGT , ZTARGT
C
*KEND.
C
C  CALOR commons
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CCOMN2.
      COMMON/CCOMN2/IBBARR(200),WENO
*KEEP,CCOMN3.
      COMMON/CCOMN3/KINDI(200),WENI
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEEP,CGEOS.
C
      COMMON/CGEOS/ GEOSIG(240),SGPIMX,SGMUMX
C
*KEEP,CHEVAP.
      COMMON/CHEVAP/HEPART(200,4)
*KEEP,CTNCOL.
      COMMON/ CTNCOL / NCOL
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
      DIMENSION PMASS(12)
      EQUIVALENCE(PMASS(1),XMASS(0))
C
*KEND.
C
      DIMENSION F(8),PCAP(100,2),NPCOL(12),AP(12),ZP(12)
C
      LOGICAL DOSKAL,INIT
      INTEGER IBERT
      SAVE
C
      DATA AP/ 1., 1., 0., 0., 0., 0., 0., 2., 3., 3., 4., 0./
      DATA ZP/ 1., 0., 0., 0., 0., 0., 0., 1., 1., 2., 2., 0./
C
      DATA INIT/.TRUE./
C
      IF(INIT) THEN
         IBERT = 0
         INIT = .FALSE.
      ENDIF
      INTCAL = 12
      NO = 1
      ATARGT = 0.0
      ZTARGT = 0.0
      ITYP = IPINC + 1
      TIP(1)  = FLOAT(IPINC)
      WT(NO) = 1.0
      EC(1) = EINC
      MAT = 1
      MXMAT = 1
      NEL(1) = NCEL
C   copy material data to CALOR
      DO 10  I=1,NCEL
         DEN(I,1) = DMED(I)
         ZZ(I,1) = ZMED(I)
         A(I,1) = AMED(I)
         DENH(1) = HDEN
   10 CONTINUE
C    calculate x-section for given material
      CALL CALCXS
   20 CONTINUE
C
C --------- start of intranuclear2 cascade ----------------------
C
C
      R = RANDC2(ISEED)
      IF(E(NO) - 1.0)100,30 ,100
C*      PI- CAPTURE ?
   30 IF(TIP(NO).NE.4) GOTO 100
      INTCAL = 18
      M=1
      LMX=NEL(M)
      DO 40  L=1,LMX
   40 PCAP(L,M)=DEN(L,M)*ZZ(L,M)
      PCAPS=0.
      DO 50  L=1,LMX
   50 PCAPS=PCAPS+PCAP(L,M)
      DO 60  L=1,LMX
   60 PCAP(L,M)=PCAP(L,M)/PCAPS
      LMX=NEL(MAT)
      DO 80  L=1,LMX
         R0=R
         R=R-PCAP(L,MAT)
         IF(R.LE.0.) GO TO 70
         GO TO 80
   70    LELEM=L
         GO TO 90
   80 CONTINUE
      CALL CERROR('NMTC$')
   90 DKWT=1.
      GO TO 250
  100 CONTINUE
C
      IF(ITYP.GE.6) GO TO 220
      R = R-HSIGG(ITYP,MAT)/SIGMX(ITYP,MAT)
      IF(R) 110,110 ,230
  110 CONTINUE
CZ 10/11/92 SCALING added
C scaling selected ?
      IF(DOSKAL) THEN
         INC = ITYP - 1
C get H cross-section
         CALL SHXSEC(EC(1),INC,HEHT,HEHEL,HELNEL)
         R = RANDC2(ISEED)
         IF(HEHT*DENH(MAT)*1.E 24/HSIGG(ITYP,MAT)-R) 210,120,120
  120    CONTINUE
         ATARGT = 1.
         ZTARGT = 1.
         R = RANDC2(ISEED)
         IF(HEHEL/HEHT.GT.R) THEN
C ---- elastic
            CALL CSCATT(INC,EC(NO),KIND,EP,ALPHA,BETA,GAM)
            NOPART = 2
            GOTO 160
         ELSE
C ---- nonelastic
            EHICUT = EMAXPI*1000.
            IF(TIP(NO).LE.1.) EHICUT = EMAXP*1000.
            CALL SKALEH(IBERT,INC,HEHT,EC(NO),NOPART,KIND,EP,ALPHA,
     +      BETA,GAM,EHICUT)
            GOTO 160
         ENDIF
      ELSE
         CALL GTHSIG(2)
         R = RANDC2(ISEED)
         IF(HSIG*DENH(MAT)*1.E 24/HSIGG(ITYP,MAT)-R) 210,130,130
  130    CONTINUE
  140    CONTINUE
         ATARGT = 1.0
         ZTARGT = 1.0
         UU = 0.0
         CALL CPCOL(IBERT,ITYP,HSIG,EC(NO),NOPART,KIND,EP,ALPHA,BETA,
     +   GAM)
C            CHANGED NOV.1,1986
         IBERT = 1
      ENDIF
      IF(NOPART.LE.0) GO TO 170
      DO 150 I=1,NOPART
         KINDI(I)=KIND(I)+1
         IBB=1
         IF(KINDI(I).GT.2)IBB=0
         IBBARR(I)=IBB
  150 CONTINUE
  160 APR = 0.0
      ZPR = 0.0
      GOTO 190
  170 CONTINUE
C             END OF CHANGE
C
  180 CONTINUE
      LELEM = 1
      APR=A(LELEM,MAT)
      ZPR =ZZ(LELEM,MAT)
  190 EX= 0.
      EREC =0.
      DO 200 I = 1,6
  200 NPART(I) = 0
      UU = 0.
      GOTO 430
  210 CONTINUE
  220 CONTINUE
      NOPART = -1
      GO TO 180
  230 NNN = NEL(MAT)
      DO 240 LEM = 1,NNN
         LELEM = LEM
CZ no hydrogen accepted in BERT ; CZ 2 JUN 92
         IF(A(LELEM,MAT) .LT. 2.0) GOTO 240
         R = R - SIGG(LEM,MAT)/SIGMX(ITYP,MAT)
         IF(R) 250,250,240
  240 CONTINUE
      GOTO 220
C------------- elastic neutron-nucleus scattering not implemented -----
C
  250 ETOT = EINC + PMASS(IPINC+1)*1.E3
CZ
CZ   check if mass number to low for BERT (A>=4)
      IF(A(LELEM,MAT).LT.4.0) THEN
C
CZ 2.95         CALL CERROR('NMTC: A < 4$')
CZ   set A=4 (brute force, but will work )
         A(LELEM,MAT) = 4.0
      ENDIF
      F(1) = A(LELEM,MAT)
      F(2) = ZZ(LELEM,MAT)
      F(3) = EC(NO)
      F(4) = 0.0
      F(5) = 1.0
      F(6) = 0.0
      F(7) = TIP(NO)
      F(8) = 0.0
C
CZ 10/11/92 SCALING added
      IF(DOSKAL) THEN
         EHICUT = EMAXPI*1000.
         IF(TIP(NO).LE.1.) EHICUT = EMAXP*1000.
         CALL CSKALE(IBERT,F,NOPART,KIND,EP,ALPHA,BETA,GAM,EHICUT,
     +   RMFAS,EX,EREC)
      ELSE
         CALL CABERT(IBERT,F,NOPART,KIND,EP,ALPHA,BETA,GAM)
      ENDIF
      IBERT = 1
C
      IF(NOPART.GT.0) THEN
         DO 260 I=1,NOPART
            KINDI(I)=KIND(I)+1
            IBB=1
            IF(KINDI(I).GT.2) IBB=0
            IBBARR(I)=IBB
  260    CONTINUE
      ENDIF
      IF(NOPART.LT.0) THEN
C ----------- Pseudo collision -------------------------
C   if incident particle pi- with 1 MeV -> repeat BERT,
C   reason : pi- capture (below cutoff)
         IF(IPINC.EQ.4 .AND. EINC.EQ.1.0) GO TO 250
C  pi- capture ? -> retry
         IF(EINC.EQ.1.0) GOTO 20
         GOTO 420
      ELSE IF(NOPART.EQ.0) THEN
C ------------------- no particle escaped nucleus ------
         GO TO(270,270,280,290,280,290,290),ITYP
  270    APR = A(LELEM,MAT) + 1.
         ZPR = ZZ(LELEM,MAT) + 1. - TIP(1)
         EX = EC(NO) + 7.
         GO TO 400
  280    APR = A(LELEM,MAT)
         ZPR = ZZ(LELEM,MAT) + 3.- TIP(1)
         EX= EC(NO) + PMASS(ITYP)*1.E3
         GO TO 400
  290    CALL CERROR('NMTC: PI0,MU+-$')
C ---------------NOPART GT 0 --------------------------
      ELSE
  300    PI0 =0.
         SUME = 0.
         PRONO = 0.
         PIPOS = 0.
         PINEG = 0.
         DO 360 N=1,NOPART
            LK= KIND(N)+1
            GO TO(310,350,320,330,340,370,370),LK
  310       PRONO =PRONO +1.
            GO TO 350
  320       PIPOS = PIPOS +1.
            GO TO 350
  330       PI0 = PI0+1.
            GO TO 350
  340       PINEG= PINEG +1.
  350       SUME = SUME + EP(N)
  360    CONTINUE
         CHGPIS =PIPOS +PINEG
         FPT = NOPART
         FPT = FPT -CHGPIS-PI0
         IF(TIP(1)-1.) 380,380,390
  370    CALL CERROR('NMTC: MU+-$')
  380    APR=A(LELEM,MAT) + 1. - FPT
         ZPR= ZZ(LELEM,MAT) + 1. - TIP(1) - PRONO - PIPOS + PINEG
         IF(ZPR.LT.0.) THEN
            CALL CERROR(' NMTC: Zpr < 0$')
            EREC = 0.0
            EX = 0.0
            ZPR = 0
            GOTO 410
         ENDIF
         IF(.NOT.DOSKAL) EX= EINC + (1.-FPT)*7.0-SUME- CHGPIS*PMASS(3)*
     +   1.E3-PI0*PMASS(4)*1.E3
         GO TO 400
  390    APR = A(LELEM,MAT) - FPT
         ZPR = ZZ(LELEM,MAT)+ 3.-TIP(1)-PRONO-PIPOS + PINEG
         IF(ZPR.LT.0.) THEN
            CALL CERROR(' NMTC: Zpr < 0$')
            EREC = 0.0
            ZPR = 0
            GOTO 410
         ENDIF
         IF(.NOT.DOSKAL) EX= EINC+(1.-CHGPIS)*PMASS(3)*1.E3-SUME
     +   -FPT*7.-PI0*PMASS(4)*1.E3
      ENDIF
C calculate recoil energy of nucleus
  400 CONTINUE
      IF(.NOT.DOSKAL) CALL RECOIL
  410 EX=EX-EREC
      IF(EX.LT.0.0) EX = 0.0
C
C -------- evaporation ------------------------------
C
      CALL CERUP
C ------------------  fill return variables -------------
  420 CONTINUE
      IBERT = 1
  430 CONTINUE
CZ set target nucleus
      IF(ATARGT.EQ.0.0) THEN
        ATARGT = A(LELEM,MAT)
        ZTARGT = ZZ(LELEM,MAT)
      ENDIF
      EXMED    = EX
      IF(APR.GE.0 .AND. ZPR.GE.0) THEN
        ERMED(1) = EREC
        AMED(1) = APR
        ZMED(1) = ZPR
        NRECOL  = 1
      ELSE
        AMED(1)  = 0.0
        ZMED(1)  = 0.0
        ERMED(1) = 0.0
        NRECOL   = 0
      ENDIF
      IF(NOPART.LT.0) THEN
C Pseudo collision
         NCOL   = 5
         NPHETC = 0
         EKINET(1) = EINC
         IPCAL(1)  = IPINC
         CALTIM(1) = 0.0
         UCAL(1,1) = UINC(1)
         UCAL(1,2) = UINC(2)
         UCAL(1,3) = UINC(3)
         EXMED    = 0.0
         NRECOL   = 1
         ERMED(1) = 0.0
         INTCAL   = 24
         AMED(1)  = A(LELEM,MAT)
         ZMED(1)  = ZZ(LELEM,MAT)
      ELSE
C get particles from intranuclear2 cascade
         NCOL    = 2
         NPHETC  = 0
         AMED(1) = APR
         ZMED(1) = ZPR
         IF(NOPART.GT.0) THEN
            DO 440 I=1,NOPART
               NPHETC = NPHETC + 1
               IF(NPHETC.GT.MXCP) NPHETC=MXCP
               EKINET(NPHETC) = EP(I)
               IPCAL(NPHETC) = KIND(I)
               CALTIM(NPHETC) = 0.0
C               transformation into Lab ssystem
               CALL CB2LAB(ALPHA(I),BETA(I),GAM(I), UINC(1),UINC(2),
     +         UINC(3),UCAL(NPHETC,1),UCAL(NPHETC,2),UCAL(NPHETC,3))
  440       CONTINUE
         ENDIF
C get evaporated neutrons
         IF(NPART(1).GT.0) THEN
            DO 450 I=1,NPART(1)
               NPHETC = NPHETC + 1
               IF(NPHETC.GT.MXCP) NPHETC=MXCP
               EKINET(NPHETC) = EPART(I,1)
               IPCAL(NPHETC)  = 1
               CALTIM(NPHETC) = 0.0
               CALL GTISO2(ALP,BET,CAM)
               UCAL(NPHETC,1) = ALP
               UCAL(NPHETC,2) = BET
               UCAL(NPHETC,3) = CAM
  450       CONTINUE
         ENDIF
C get evaporated protons
         IF(NPART(2).GT.0) THEN
            DO 460 I=1,NPART(2)
               NPHETC = NPHETC + 1
               IF(NPHETC.GT.MXCP) NPHETC=MXCP
               EKINET(NPHETC) = EPART(I,2)
               IPCAL(NPHETC)  = 0
               CALTIM(NPHETC) = 0.0
               CALL GTISO2(ALP,BET,CAM)
               UCAL(NPHETC,1) = ALP
               UCAL(NPHETC,2) = BET
               UCAL(NPHETC,3) = CAM
  460       CONTINUE
         ENDIF
C get evaporated heavy particles (alpha,deuteron, triton, He3)
C              particle type       10     7         8      9
         DO 480 I=3,6
            IF(NPART(I).GT.0) THEN
               DO 470 K=1,NPART(I)
                  NPHETC = NPHETC + 1
                  IF(NPHETC.GT.MXCP) NPHETC=MXCP
                  EKINET(NPHETC) = HEPART(K,I-2)
                  IPCAL(NPHETC) = I + 4
                  CALTIM(NPHETC) = 0.0
                  CALL GTISO2(ALP,BET,CAM)
                  UCAL(NPHETC,1) = ALP
                  UCAL(NPHETC,2) = BET
                  UCAL(NPHETC,3) = CAM
  470          CONTINUE
            ENDIF
  480    CONTINUE
C generate de-exitation gammas
C
         IF(UU.GT.0.0) THEN
            EEX = UU
            EGTOT = 0.0
  490       CONTINUE
            EGAM = EEX * RANDC2(ISEED)
            IF((EGTOT+EGAM) .GT. EEX) THEN
               EGAM = EEX - EGTOT
               EEX = 0.0
            ENDIF
            EGTOT = EGTOT + EGAM
            CALL AZIRN2(SINA,COSA)
            COSP = SFLRAF2(DUM)
            SINP = SQRT(1.0-COSP*COSP)
            NPHETC = NPHETC + 1
            IF(NPHETC.GT.MXCP) NPHETC=MXCP
            EKINET(NPHETC) = EGAM
            UCAL(NPHETC,1) = SINP * COSA
            UCAL(NPHETC,2) = SINP * SINA
            UCAL(NPHETC,3) = COSP
            IPCAL(NPHETC) = 11
            CALTIM(NPHETC) = 0.0
            IF(EEX.GT.0.0) GOTO 490
         ENDIF
      ENDIF
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.37  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CABRAN(K1)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      VALUE1 = RANDC2(ISEED)
      VALUE1=VALUE1*SIGN
      VALUE2=0.0
      NOT=1
      DO10 I=2,K1
         VALUE2=CE(I)+VALUE2
         IF(VALUE2-VALUE1)10,20,20
   10 NOT=NOT+1
   20 RETURN
C     VALUE2=SUM OF CE FOR A PARTICULAR REGION--SUM F(I1)MASS
      END
*CMZ :  0.92/00 02/12/92  16.02.23  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALP19
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
C
      UNIV = RANDC2(ISEED)
      PT(2)=1.0
      PT(26)=1.0
      PT(14)=3.0
      PT(16)=POMS
      IF(ISW(12))10,10,140
   10 IF(UNIV-.25)20,20,110
   20 IF(ISW(4))40,30,40
   30 PT(2)=2.0
   40 UNIV = RANDC2(ISEED)
      IF(UNIV-6.6666667D-1)50,50,90
   50 PT(14)=4.0
   60 IF(ISW(4))80,70,80
   70 PT(26)=2.0
   80 GO TO 240
   90 PT(16)=PNMS
      IF(ISW(4))70,100,70
  100 PT(14)=5.0
      GOTO80
  110 IF(ISW(4))130,120,130
  120 PT(26)=2.0
      GOTO90
  130 PT(2)=2.0
      PT(16)=PNMS
      GOTO80
  140 IF(UNIV-.5)150,150,190
  150 IF(ISW(4))160,170,160
  160 PT(2)=2.0
  170 UNIV = RANDC2(ISEED)
      IF(UNIV-3.3333333D-1)90,90,180
  180 PT(14)=4.0
      GOTO60
  190 IF(ISW(4))210,200,210
  200 PT(2)=2.0
  210 UNIV = RANDC2(ISEED)
      IF(UNIV-6.6666667D-1)220,220,230
  220 PT(14)=4.0
      IF(ISW(4))70,80,70
  230 PT(16)=PNMS
      IF(ISW(4))100,70,100
  240 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALP28
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      REAL *8 R
C
      SAVE
C
      R = RANDC2(ISEED)
      IF(ISW(13))230,10,230
   10 IF(R-6.0D-1)20,20,120
   20 PT(4)=PNMS
      R = RANDC2(ISEED)
      IF(ISW(4))30,90,30
   30 IF(R-3.3333333D-1)40,40,70
   40 PT(26)=5.0
   50 PT(28)=PNMS
   60 RETURN
   70 PT(26)=4.0
   80 PT(38)=2.0
      GO TO 60
   90 PT(2)=5.0
      PT(14)=2.0
      IF(R-3.3333333D-1)100,100,110
  100 PT(28)=PNMS
      GO TO 80
  110 PT(26)=4.0
      GO TO 60
  120 R = RANDC2(ISEED)
      IF(ISW(4))130,180,130
  130 IF(R-6.6666667D-1)140,140,160
  140 PT(2)=4.0
  150 R = RANDC2(ISEED)
      IF(R-6.6666667D-1)110,110,100
  160 PT(14)=2.0
  170 PT(4)=PNMS
      GO TO 150
  180 IF(R-6.6666667D-1)190,190,220
  190 PT(2)=4.0
  200 PT(14)=2.0
  210 R = RANDC2(ISEED)
      IF(R-6.6666667D-1)70,70,40
  220 PT(2)=5.0
      PT(4)=PNMS
      GO TO 210
  230 IF(R-VALUE1)240,240,270
  240 PT(4)=PNMS
      IF(ISW(4))260,250,260
  250 PT(2)=5.0
      PT(14)=2.0
      GO TO 50
  260 PT(38)=2.0
      GO TO 40
  270 R = RANDC2(ISEED)
      IF(ISW(4))280,310,280
  280 IF(R-3.3333333D-1)290,290,300
  290 PT(4)=PNMS
      GO TO 200
  300 PT(2)=4.0
      GOTO210
  310 IF(R-3.3333333D-1)320,320,330
  320 PT(2)=5.0
      GOTO170
  330 PT(14)=2.0
      GOTO140
      END
*CMZ :  0.92/00 02/12/92  16.02.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALPHA
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      SAVE
C
      UNIV = RANDC2(ISEED)
      IF(VALUE3)300,10,140
   10 IF(UNIV-VALUE1)20,20,120
   20 IF(ISW(11))40,30,40
   30 PT(2)=5.0
      PT(26)=2.0
   40 PT(4)=PNMS
      PM(4)=PNMS
      UNIV = RANDC2(ISEED)
      IF(UNIV-VALUE2)50,50,70
   50 PT(14)=4.0
   60 RETURN
   70 IF(ISW(11))110,80,110
   80 PT(26)=1.0
   90 PT(14)=5.0
  100 PT(16)=PNMS
      GO TO 60
  110 PT(26)=2.0
      GO TO 100
  120 PT(2)=4.0
      IF(ISW(11))100,130,100
  130 PT(14)=5.0
      GO TO 110
  140 IF(UNIV-VALUE1)150,150,200
  150 PM(4)=PNMS
      IF(ISW(11))160,190,160
  160 PT(2)=5.0
  170 PT(16)=PNMS
  180 PT(4)=PNMS
      GO TO 60
  190 PT(14)=5.0
      PT(26)=2.0
      GO TO 170
  200 IF(UNIV-VALUE2)210,210,250
  210 PT(2)=4.0
      UNIV = RANDC2(ISEED)
      IF(UNIV-VALUE3)240,240,220
  220 IF(ISW(11))50,230,50
  230 PT(26)=2.0
      GO TO 50
  240 IF(ISW(11))110,90,110
  250 PM(4)=PNMS
      PT(4)=PNMS
      UNIV = RANDC2(ISEED)
      IF(UNIV-6.6666667D-1)260,260,280
  260 IF(ISW(11))230,270,230
  270 PT(2)=5.0
      GO TO 50
  280 IF(ISW(11))90,290,90
  290 PT(26)=2.0
      GO TO 160
  300 IF(UNIV-VALUE1)310,310,340
  310 PM(4)=PNMS
      PT(4)=PNMS
      UNIV = RANDC2(ISEED)
      IF(VALUE3+1.0)330,320,330
  320 IF(UNIV-3.3333333D-1)90,90,230
  330 PT(2)=5.0
      IF(UNIV-3.3333333D-1)110,110,50
  340 IF(UNIV-VALUE2)350,350,380
  350 PT(2)=4.0
      UNIV = RANDC2(ISEED)
      IF(VALUE3+1.0)370,360,370
  360 IF(UNIV-6.6666667D-1)50,50,110
  370 IF(UNIV-6.6666667D-1)230,230,90
  380 PM(4)=PNMS
      PT(4)=PNMS
      IF(VALUE3+1.0)390,160,390
  390 PT(14)=5.0
      GOTO110
      END
*CMZ :  0.92/00 02/12/92  16.02.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CANGID
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      REAL*8 R,TESISO
      SAVE
C
C     ******************************************************************
C****    CALCULATES  COS AND SIN THETA,SIN AND COS PHI    **************
C     ******************************************************************
      ICURR = CURR(1)
      GO TO(10,10,30,30,30),ICURR
C****  INCIDENT PARTICLE - NUCLEON
   10 IF(IT.EQ.21.OR.IT.EQ.22)GO TO 20
C****  SINGLE  PRODUCTION
      IF(RLKE.GT.3500.0D0) CALL CERROR('CANGID1$')
      IF(RLKE.LT.500.0D0)GO TO 70
      TESISO= 0.75D0
      IF(RLKE.LT.1000.0D0)GO TO 50
      TESISO= 0.5D0
      IF(RLKE.LT.1300.0D0)GO TO 50
      TESISO= 0.25D0
      IF(RLKE.LT.2500.0D0)GO TO 50
      GO TO 60
C****  DOUBLE PRODUCTION
   20 IF(RLKE.GT.3500.0D0) CALL CERROR('CANGID2$')
      GO TO 60
C**** INCIDENT PARTICLE-PION
   30 R = RANDC2(ISEED)
      IF(RLKE.GT.2500.0D0) CALL CERROR('CANGID3$')
      CST= -0.9999995D0
      SNT=  0.003162D0
      IF(IT.NE.11)GO TO 40
      IF(R.LE.0.75D0)GO TO 70
      GO TO 80
C****  (PI+)-(P),(PI-)-(N)
C****  (PI0)-(N),(PI0)-(P)
   40 IF(IT.NE.12.AND.IT.NE.28) CALL CERROR('CANGID4$')
      IF(RLKE.LT.500.0D0)CST=-CST
      IF(R.LE.0.80D0)GO TO 70
      GO TO 80
   50 R = RANDC2(ISEED)
      IF(R.LE.TESISO)GO TO 70
C**** BACKWARD/FORWARD
   60 R = RANDC2(ISEED)
C****  TEST FOR DIRECTION
      CST= 0.9999995D0
      SNT= 0.003162D0
      IF(R.LE.0.5)GO TO 80
      CST= -0.9999995D0
      GO TO 80
C****  ISOTROPIC
   70 CALL CAPOL1(CST,SNT)
C****  CALCULATES  COS,SIN PHI
   80 CALL CAAZIO(SOPC,SOPS)
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CAAZIO(SINE,COSINE)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      REAL * 8 SINE,COSINE,R1,R2,R1SQ,R2SQ,SUM
C
   10 R1 = RANDC2(ISEED)
      R1SQ = R1 * R1
C     XSQ
      R2 = RANDC2(ISEED)
      R2SQ = R2 * R2
C     YSQ
      SUM = R1SQ + R2SQ
      IF(SUM.GT.1.0) GO TO 10
      SUM = SUM * 0.5
C     (XSQ+YSQ)/2
      COSINE = (SUM-R1SQ) / SUM
C     (YSQ-XSQ)/(XSQ+YSQ)
      SINE = (R1*R2) / SUM
C     (2*X*Y)/(XSQ+YSQ)
      R1 = RANDC2(ISEED)
      IF(R1.LT.0.5) GO TO 20
      SINE = -SINE
   20 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.37  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   21/05/92
      SUBROUTINE CB2LAB(ALPHA,BETA,GAM,U,V,W,ULAB,VLAB,WLAB)
C***************************************************************
C
C   convert direction cosines of paticles produced in BERT
C   into Lab system
C
C   input: ALPHA,BETA,GAM : direction consine in BERT
C          u,v,w          : direction cosines in Lab system of
C                           the projectile
C   output:ulab,vlab,wlab : direction cosine in Lab system
C
C
C**************************************************************
C
      RT = SQRT(U*U + V*V)
      if(RT.EQ.0.0) THEN
         SINTH = 0.0
         COSTH = 1.0
         COSPHI = 1.0
         SINPHI = 0.0
      ELSE
         SINTH = RT
         COSTH = W
         COSPHI = U/RT
         SINPHI = V/RT
      ENDIF
      T1   =  COSTH * ALPHA  + SINTH * GAM
      ULAB = COSPHI * T1 - SINPHI * BETA
      VLAB = SINPHI * T1 + COSPHI * BETA
      WLAB = COSTH * GAM -  SINTH * ALPHA
C
C     U = COSPHI*COSTH* ALPHA  -SINPHI* BETA  +COSPHI*SINTH* GAMA
C
C     V = SINPHI*COSTH* ALPHA  +COSPHI* BETA  +SINPHI*SINTH* GAMA
C
C     W =       -SINTH* ALPHA  +   0. * BETA         +COSTH* GAMA
C                      ROTATION MATRIX
      RETURN
      END
*CMZ :  0.92/04 11/12/92  12.04.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CBBBBB
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      I=I2
C     COLLISION CUT-OFF ENERGY (PROTON)
      IF(I1)10,20,10
   10 I=I+3
C     COLLISION CUT-OFF ENERGY (NEUTRON)
   20 IF(KNOT-6)40,40,30
   30 IF(KNOT-12)50,50,40
   40 CLCFE=CFEPN(I)
   50 E(1)=WKRPN(I)*RCPMV+PM(1)
C     TOTAL ENERGY PARTICLE 1
   60 IF(IN)80,70,80
   70 CALL P1CLI
      GOTO90
   80 CALL P1CLC
C     P1OE1=CURRENT=MOMENT/TOTAL
   90 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.37  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CABERT(IBERT,FINPUT,NOPART,KIND,ERAY,ARAY,BRAY,GRAY)
C*************************************************************************
C
C calculate collision of particle with nucleus
C
C input: Finput(1) = A of nucleus
C        Finput(2) = Z of nucleus
C        Finput(3) = Ekin of incident particle
C        Finput(4) = energy cut off used in intranuclear2 cascade default = 0
C        Finput(5) = No. of incident particles = 1.0
C        Finput(6) = Angular distance
C        Finput(7) = particle type a la CALOR + 1
C        Finput(8) = same as Finput(4)
C
C output:NOPART > 0  -> no. of particles generated
C               = 0  -> collision with no escaping particle
C               = -1 -> pseudo collision
C        KIND(1-NOPART) -> particle type
C        ERAY(1-NOPART) -> kinetic energy
C        A,B,GRAY(1-NOPART) -> direction cosine (x,y,z-axis)
C                              incident particle with GRAY = 1 !!!
C
C*************************************************************************
C
      DIMENSION FINPUT(*),KIND(*),ERAY(*),ARAY(*),BRAY(*),GRAY(*)
C
C     A.C.3526(3410-44) CASCADE CALCULATION
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRN.
       COMMON/CRN/COUNT
       REAL*8 COUNT(10)
C
*KEEP,CMUNPU.
       DIMENSION NIP(12)
       REAL*8 PCC(12),PPNB(5)
       COMMON/CMUNPU/PCC,PPNB,NIP
C
C    CALOR random seed
*KEEP,CRUN.
       COMMON/CRUN/KE
C
*KEND.
      REAL*8 DCLN(80)  , DCIN(115) , PPAC(19)  , POAC(19)  , FMXSN(161),
     +       FMXDN(130), FMXSP(117), PDCI(60)  , PDCH(55)  , DCHN(143) ,
     +       DCHNA(36) , DCHNB(60) , PSPCL(158), PDPCL(130), SPCLN(158),
     +       DPCLN(130), FSLN(176) , FRINN(161), DMIN(101) , PPSCL(117),
     +       PNSCL(117), PMSCL(117), PNNSL(117), PCFSL(234), FRIPN(117),
     +       PNMI(101) , PNFSL(234), PNEC(126) , PNNEC(126), PMXC(126) ,
     +       PMEC(126) , PPEC(126) , PEC(176)  , ECN(176)  , PPDC(6426),
     +       PMDD(6426), PMDX(6426), PNDD(6426)
      DIMENSION ICC(12)
      REAL * 8 ZERO,XINC
      EQUIVALENCE (TAPCRS(1),DCLN(1))    , (TAPCRS(81),DCIN(1))   ,
     +            (TAPCRS(196),PPAC(1))  , (TAPCRS(215),POAC(1))  ,
     +            (TAPCRS(234),FMXSN(1)) , (TAPCRS(395),FMXDN(1)) ,
     +            (TAPCRS(525),FMXSP(1)) , (TAPCRS(642),PDCI(1))  ,
     +            (TAPCRS(702),PDCH(1))  , (TAPCRS(757),DCHN(1))  ,
     +            (TAPCRS(900),DCHNA(1)) , (TAPCRS(936),DCHNB(1)) ,
     +            (TAPCRS(996),PSPCL(1)) , (TAPCRS(1154),PDPCL(1)),
     +            (TAPCRS(1284),SPCLN(1)), (TAPCRS(1442),DPCLN(1)),
     +            (TAPCRS(1572),FSLN(1)) , (TAPCRS(1748),FRINN(1)),
     +            (TAPCRS(1909),DMIN(1)) , (TAPCRS(2010),PPSCL(1))
      EQUIVALENCE (TAPCRS(2127),PNSCL(1)), (TAPCRS(2244),PMSCL(1)),
     +            (TAPCRS(2361),PNNSL(1)), (TAPCRS(2478),PCFSL(1)),
     +            (TAPCRS(2712),FRIPN(1)), (TAPCRS(2829),PNMI(1)) ,
     +            (TAPCRS(2930),PNFSL(1)), (TAPCRS(3164),PNEC(1)) ,
     +            (TAPCRS(3290),PNNEC(1)), (TAPCRS(3416),PMXC(1)) ,
     +            (TAPCRS(3542),PMEC(1)) , (TAPCRS(3668),PPEC(1)) ,
     +            (TAPCRS(3794),PEC(1))  , (TAPCRS(3970),ECN(1))  ,
     +            (TAPCRS(4146),PPDC(1)) , (TAPCRS(10572),PMDD(1)),
     +            (TAPCRS(16998),PMDX(1)), (TAPCRS(23424),PNDD(1))
C
      SAVE
      AMASNO =DBLE(FINPUT(1))
      ZEE = DBLE(FINPUT(2))
      EINC = DBLE(FINPUT(3))
      CTOFE = DBLE(FINPUT(4))
      CASESN = DBLE(FINPUT(5))
      ANDIT = DBLE(FINPUT(6))
      CTOFEN = DBLE(FINPUT(8))
      PRTIN = FINPUT(7)
      KE = 0
      IF(IBERT)40,10,40
C           CHANGED SEPT.1,1987
   10 CONTINUE
CZ BERT dataset already read by CRBERT called by CALINI 19. june 92
      NRT = 0
      SF  =1.
C     SF=1.0 AT PRESENT
      LN=2
C     NOR=RECORD NUMBER
C     NRT=NUMBER OF FILES
      RANDI(1)=16896
      PNMS=.708D13
C     PI+ OR - MASS IN RECIP. CM
      DNCMS=4.758D13
      SQNM=DNCMS*DNCMS
C     NUCLEON MASS SQUARED
C     NUCLEON MASS IN RECIP. CM
      RCPMV=.50613D11
C     RECIPROCAL CM PER MV
      POMS=.684D13
C     PI0 MASS IN RECIP. CM
      IFIVE=5
      ISIX=6
      ZERO=0.0
      NE=0
      BEGRU = 0.0
      DO 20 I=1,3
   20 XI(I)=0.0
      DO 30 I=1,19
         POAC(I)=POAC(I)+POAC(I)
   30 PPAC(I)=PPAC(I)/SF
C     P0AC(19),PPAC(19)
C     SF IS A SCALE FACTOR SUBJECT TO CHANGE
C     ANDIT
C     ISOBAR ANGULAR DISTRIBUTION  0,50 PERCENT ISOTROPIC 50
C     PERCENT FORWARD-BACKWARD-1,ALL ISOTROPIC-2,ALL FORWARD-BACKWARD
C     =0,ALL OF WORD IN CRDET TO BE CONSIDERED.  NOT 0, ONLY PART. INPT
C     ESCAPING PARTICLE STORAGE     ESPS
C     NUMBER OF FORBIDDEN COLLISIONS FOR NEUTRONS     FCN
C     NUMBER OF FORBIDDEN COLLISIONS FOR PROTONS   FCP
C     PARTICLE WITH VELOCITY LESS THAN CRITERION   PLVC
C     PARTICLE WITH VELOCITY GREATER THAN CRITERION   PGVC
   40 DO 50 I=1,60
         IPEC(I)=0
   50 CONTINUE
      I18=0
      I19=0
      DO 60 I=1,2114
         ESPS(I)=0.0
   60 CONTINUE
      DO 70 I= 4515,4849
         ESPS(I)=0.D0
   70 CONTINUE
      DO 80 I=1,10
         COUNT(I)=0.0D0
   80 CONTINUE
      DO 90 I=1,12
         ICC(I)=0
   90 CONTINUE
      SPACE(13)=EINC
      NO=AMASNO
      NMAS=1+(NO-1)*10
      DO 100 I=1,10
         OUT(I)=CRSC(NMAS)
         NMAS=NMAS+1
  100 CONTINUE
      CALL ROUT1
      IF(PRTIN.GT.4) THEN
         CALL CERROR(' BERT called for muon$')
         NOPART=-1
         RETURN
      ENDIF
      NO= PRTIN + 1.
      IF(SPACE(4).GT.100.0) SPACE(4)=100.0
      VALUE1=EINC+SPACE(4)
      IF(NO.LT.3) GOTO 2540
      IF(NO.EQ.4) THEN
         CALL CERROR(' BERT called for pi0$')
         NOPART = -1
         RETURN
      ENDIF
C ----- Charged pions ------
      CALL ROUT2(PPAC(1))
      IF(I1.EQ.0) THEN
         CALL CERROR(' BERT Epion > 2.5 GeV$')
         RETURN
      ENDIF
      IV=2
      IF(NO.EQ.5) IV=0
      CALL CALXYI(1,14,30)
      IP=1
  110 CALL ROUT3
      IF(BEGRU.EQ.0.0) GOTO 2460
C     IF BEGRU=0, LAST RUN COMPLETED--BG6A
      KK=I1
      XINC=XI(1)
C     XINC=X-COORDINATE INC.PART.
      CALL ROUT4
      IF(I1.LT.0.0) GOTO 2820
      I1=KK
  120 IF(IN.NE.0) GOTO 2200
      IF(EX.GT.D(2)) GOTO 650
  130 CURR(2)=OUT(13)
      WKRPN(3)=CURR(2)
C     K.E. WITH RESPECT TOPROTONS RG.3
      WKRPN(6)=OUT(16)
C     K.E. WITH RESPECT TONEUTRONS RG.3
      IFCA=0
  140 CALL CBG6CA(3,3)
  150 IFCC=0
      CALL CABRAN(6)
      KNOT=NOT
      IF(NOT.EQ.4) GOTO 380
      CALL CABG6C(ISW(11))
      VALUE1=RLKE
      IF(IN.NE.0) GOTO 1980
      IF(NOT.EQ.4) GOTO 380
      IF(NOT.LT.4) THEN
         ANY=SPACE(NOT+13)
         GOTO 170
      ELSE
         ANY=S(NOT-4)
      ENDIF
  160 IF(NOT-5)170,600,630
C     IT=1-6  PIPPS(20051),BG129(21011),PIMPD(21004),PIPND(20644)
  170 CALL ROUT5(PPEC(1),PMEC(1),PMXC(1))
C     PPEC(126),PMEC(126),PMXC(126)
  180 IF(CLSM-2.0)880 ,740,190
C     (PIM-P)EXCHANGE SCATTERING CRS.
  190 IF(VALUE1.GT.VALUE2) GOTO 300
  200 IF(ISW(1).NE.0) GOTO 240
      IFC=IFCC+1
      IF(IN.NE.0) GOTO 1990
  210 C(3)=0.0
  220 C(1)=CURR(4)
      C(2)=CURR(5)
      C(3)=C(3)+CURR(6)+EX+D(1)
  230 CONTINUE
      GOTO(960 ,1230,1240,1300,1310,1410,1420,1450,1460,1420,1470,1830,1
     +840 ,1460,1850,1860,1870,1880,1960,1930,1940,1950,2360,2420,2430,2
     +440 ,1420,2450),IT
  240 IF(ISW(2))280,250,280
  250 IFC=2+IFCC
  260 IF(IN)2000,270,2000
  270 C(3)=D(2)+D(3)
      GOTO 220
  280 IFC=3+IFCC
      IF(IN)480,290,480
  290 C(3)=D(2)+D(3)+D(4)+D(5)
      GOTO 220
C     IFC(1-3),BG6C(1502),BG6F(3243),BG6K(4055) COLLISION
  300 CALL SIGNEX
  310 IF(ISW(1))320,120,320
  320 IF(IN)2010,330,2010
  330 IF(EX-D(6))130,130,340
  340 IF(ISW(2))360,350,360
  350 IPEC(7)=IPEC(7)+1
C     NO. OF ESCAPED PARTICLES ON REGION 2
      GOTO 110
  360 IPEC(11)=IPEC(11)+1
C     NO. OF ESCAPED PARTICES ON REGION 1
      GOTO 110
  370 I3=1
      GOTO 390
  380 I3=-1
  390 CALL ROUT6
      IF(I3)400 ,410,450
  400 CALL CERROR(' BERT CURR(1) < 3 or > 5$')
      NOPART=-1
      RETURN
  410 CALL ROUT6A
      IF(CLSM-2.0)910 ,940 ,2180
  420 IFCA=1
  430 IF(ISW(1))440,210,440
  440 IF(ISW(2))290,270,290
C     NON-DEUTERON ABSORPTION
  450 CALL ROUT7
      IF(I3)400 ,460,460
  460 CALL ROUT7A
      I3=I3
      GOTO(480,470 ,590,540,210,290,500,510,270),I3
  470 CALL CERROR(' BERT PWD or NWD < 7$')
      NOPART = -1
      RETURN
  480 VALUE1=EX+D(4)+D(5)
  490 IF(CURR(10)-2.0)500,510,510
  500 C(1)=VALUE1*CURR(7)+CURR(4)
      C(2)=VALUE1*CURR(8)+CURR(5)
      C(3)=VALUE1*CURR(9)+CURR(6)
      GO TO 230
  510 VALUE1=VALUE1+D(3)
      GO TO 520
  520 IF(CURR(10)-2.0)500,500,530
  530 VALUE1=VALUE1+D(2)
      GO TO 500
  540 IF(INC)550,570,550
  550 C(3)=D(2)
      IF(ISW(3))560,220,560
  560 C(3)=C(3)+D(3)+D(4)
      GO TO 220
  570 IF(ISW(3))580,520,580
  580 VALUE1=EX+D(4)
      GO TO 490
  590 VALUE1=EX
      IF(INC)270,490,270
  600 IF(RLKE.GT.2500.0) THEN
         CALL CERROR(' BERT RLKE > 2.5 GeV$')
         RLKE = 2500.0
      ENDIF
      IF(RLKE-180.0)610,610,620
  610 CALL SIGNEX
      IF(CLSM-2.0)850 ,760,310
  620 VALUE1=VALUE1-180.0
      CALL CRJAB(1,PPSCL(1))
C     PPSCL(117)
C     (PIP-P)SINGLE PROD. CRS. LOW ENERGY
      GO TO 180
  630 IF(RLKE.GT.2500.0) THEN
         CALL CERROR(' BERT RLKE > 2.5 GeV (2)$')
         RLKE = 2500.0
      ENDIF
      IF(RLKE-180.0)610,610,640
  640 VALUE1=VALUE1-180.0
      CALL CRJAB(1,PMSCL(1))
C     PMSCL(117)
C     (PIM-P)SINGLE PROD. CRS. LOW ENERGY
      GO TO 180
  650 IF(D(3))670,660,670
  660 IPEC(2)=IPEC(2)+1
C     NO. OF PARTICLES INCIDENT ON REGION 3 ESCAPING
      GO TO 110
  670 ISW(1)=1
      CALL SPAC32(31)
  680 IF(IN)2020,690  ,2020
  690 IF(EX-D(3))710,710,810
  700 IF(IN)720,710,720
  710 CURR(2)=OUT(14)
      WKRPN(2)=CURR(2)
      WKRPN(5)=OUT(17)
C     K.E. FOR PROTONS AND NEUTRONS REGION 2
  720 CALL CBG6CA(2,2)
      GO TO 150
  730 IV=-1
      GO TO 750
  740 IV=0
  750 CALL ROUT8
      I3=I3
      GOTO(760,2030,220,580),I3
  760 IF(ISW(3))770,680,770
  770 IF(EX-D(5))700 ,700 ,780
  780 IF(IN)2040,790  ,2040
  790 CALL SPAC32(32)
  800 IF(EX-D(6))130,130,360
  810 IF(D(4))840 ,820 ,840
  820 CALL SPAC32(32)
  830 IF(EX-D(6))130,130,350
  840 ISW(2)=1
      ISW(3)=1
      CALL SPAC32(30)
  850 IF(IN)2050,860  ,2050
  860 CALL ROUT10
      IF(I3)770,870 ,870
  870 CALL CBG6CA(1,1)
      GO TO 150
  880 IF(VALUE1-VALUE2)890 ,890 ,900
  890 IFC=9+IFCC
      IF(IN)2060,270,2060
  900 CALL SIGNEX
      IF(IN)2050,860  ,2050
  910 IF(IN)930 ,920 ,930
  920 IFCA=6
      GO TO 270
  930 IFCA=9*IABS(I6-2)+13*(I6-1)*(3-I6)
      GOTO2060
  940 IF(IN)2070,950 ,2070
  950 IFCA=7
      GOTO550
  960 I3=1
      GOTO1000
  970 I3=4
      GOTO1000
  980 I3=2
      GOTO1000
  990 I3=3
 1000 CALL ROUT11(PPDC(1))
C     PPDCL(378)
      I3=I3
      GOTO(1180,1270,1400,1010),I3
 1010 CST=CRDT(2)-DABS(SNT*(CRDT(2)-CRDT(1)))
 1020 SNT=DSQRT(1.0-CST*CST)
 1030 CALL ROUT12
      IF(I3)1040,1050,1110
 1040 CALL CERROR(' BERT COM < -5E-6$')
      NOPART=-1
      RETURN
 1050 IF(EFRN-VALUE1)1150,1060,1060
 1060 FCN=FCN+1.0
 1070 IV=-1
      GOTO1090
 1080 IV=0
 1090 I1=0
      CALL ROUT13
      IF(I3)460,1100,410
 1100 IFC=IFC
      GOTO(120,830 ,800 ,2840,3210,3270,680,770,850 ,3150,3250,3230,2200
     +    ,2010,2010,2080,2090,2100,2020,770,2200,2010,2010,2050,2200,20
     +10  ,2010,2020,2110,2050),IFC
 1110 IF(EFRP-VALUE1)1150,1120,1120
 1120 FCP=FCP+1.0
      GOTO1070
 1130 I3=0
      GOTO1160
 1140 I3=-1
      GOTO1160
 1150 I3=1
 1160 CALL ROUT14
      I3=I3
      GOTO(1110,1050,1170,3560,2120),I3
 1170 CALL CERROR(' BERT I3=3$')
      NOPART=-1
      RETURN
 1180 I3=1
      GOTO1210
 1190 I3=3
      GOTO1210
 1200 I3=4
 1210 CALL ROUT15(PPDC(1))
C     HPPDCI(45),PPDCI(170)
      I3=I3
      GOTO(1250,1340,1020,1220,1260,1390),I3
 1220 CALL CERROR(' BERT I3=4$')
C     SNN(RLKE GTE 1000)  DCINTP(RLKE GTE CRS.SECT.VALUES)
      NOPART=-1
      RETURN
 1230 PT(2)=5.0
      IK=IT
C     BG129  (PIM-N)
      PT(14)=2.0
      GOTO980
 1240 PT(2)=5.0
C     PIPNX  DIR. SCAT.
      PT(14)=1.0
      IK=IT
      GOTO 980
 1250 I3=1
      GOTO1280
 1260 I3=2
      GOTO1280
 1270 I3=3
 1280 CALL ROUT16(PMDD(1))
C     HPMDDI(45),PMDDI(170),PMDDL(378)
 1290 IF(I3)1020,1190,1020
 1300 PT(2)=3.0
      PT(14)=2.0
      IK=3
      GO TO 980
 1310 PT(14)=2.0
 1320 IK=IT
 1330 PT(2)=4.0
      PM(3)=POMS
C     PI 0 MASS/CM
      GO TO 990
 1340 IF(IK-23)1350,2390,1350
 1350 I3=1
      GO TO 1380
 1360 I3=2
      GO TO 1380
 1370 I3=3
 1380 CALL ROUT16(PMDX(1))
C     HPMDXI(45),PMDXI(170),PMDXL(378)
      GO TO 1290
 1390 IF(IK-23)1360,2370,1360
 1400 IF(IK-23)1370,2380,1370
C     (PIM-P)XCH.
 1410 PT(14)=1.0
      GO TO 1320
 1420 PT(2)=1.0
C     PIM+(PP)  ABS
C     IT=10,PIP+(NN)  ABS
 1430 PT(14)=2.0
 1440 CALL CAPOL1(CST,SNT)
      GO TO 1030
 1450 PT(2)=2.0
C     PIN+(NN)  ABS
      GO TO 1430
 1460 PT(2)=1.0
C     PIN+(PP)  ABS    ALS0 PI+ ABS
      PT(14)=1.0
      GO TO 1440
 1470 ISW(9)=0
      ISW(10)=0
 1480 I3=0
      GO TO 1500
 1490 I3=-1
 1500 CALL ROUT17(FRIPN(1),PNMI(1),FMXSP(1),PCFSL(1),PNFSL(1))
C     FRIPN(117),PNMI(101),FMXSP(117),PCFSL(234),PNFSL(234)
      IF(I3) 1510,1640,1520
 1510 CALL CERROR(' BERT I3 < 0$')
C     COLL(COM LT -5.0E-6)  ECPL(ERROR IN CURR ,STRKP,PT(26),
C     PT(2),PT(14) OR PT(37))  ISW10=0
      NOPART=-1
      RETURN
 1520 K=3
 1530 IF(PT(K-1)-1.0)1650,1540,1650
 1540 IF(PT(K))1560,1560,1550
 1550 IF(PT(K)-EFRP)1560,1560,1580
 1560 FCP=FCP+1.0
C     NO. FORBIDDEN COLLISIONS INVOLVING PROTONS
 1570 PM(4)=DNCMS
      GO TO 1080
 1580 M=PT(K-1)
      IF(PT(K)-ECO (M)) 1590,1590,1600
 1590 PT(K)=0.0
      PNBC(M)=PNBC(M)+1.0
 1600 IF(COL(15)-1.0)1640,1740,1610
 1610 IF(COL(15)-3.0)1720,1710,1620
 1620 IF(COL(15)-5.0)1730,1780,1630
 1630 CALL CERROR(' BERT COL(15)>5$')
      NOPART=-1
      RETURN
 1640 CALL COLLM(0)
      IF(PT(38)) 1700,1690,1700
 1650 IF(PT(K-1)-2.0) 1810,1660,1810
 1660 IF(PT(K)) 1680,1680,1670
 1670 IF(PT(K)-EFRN) 1680,1680,1580
 1680 FCN = FCN+1.0
      GO TO 1570
 1690 I3=1
      GO TO 1750
 1700 I3=2
      GO TO 1750
 1710 I3=4
      GO TO 1750
 1720 I3=5
      GO TO 1750
 1730 I3=6
      GO TO 1750
 1740 I3=3
 1750 CALL ROUT18
      I3=I3
      K=IV
      GO TO (1530,1760,1600,1900,1770),I3
 1760 CALL CERROR(' BERT PT(K-1) < 3$')
      NOPART=-1
      RETURN
 1770 I18=I18+1
      GO TO 1570
 1780 CALL ROUT19
      IF(I3)1790,1900,1800
 1790 CALL CERROR(' BERT PT(K-1)<3, >6 K<27$')
      NOPART=-1
      RETURN
 1800 I19=I19+1
      GO TO 1570
 1810 IF(COL(15)-1.0)1640,1820,1820
 1820 CALL CERROR(' BERT COL(15) >=1$')
      NOPART=-1
      RETURN
 1830 I3=2
      GO TO 1910
 1840 I3=3
      GO TO 1910
 1850 I3=4
      GOTO1910
 1860 I3=5
      GOTO1910
 1870 I3=6
      GOTO1910
 1880 I3=7
      GOTO1910
 1890 I3=8
      GOTO1910
 1900 I3=1
 1910 CALL ROUT20(DCIN(1),DCLN(1),DCHN(1),PDCI(1),PDCH(1))
C     DCIN(115),DCLN(80),DCHN(64),PDCI(52),PDCH(64)
      I3=I3
      GOTO(1920,1140,1490,1430,1200,1020,1440,1030),I3
 1920 CALL CERROR(' BERT RLKE>3.5GeV$')
      NOPART=-1
      RETURN
 1930 I3=2
      GOTO1970
 1940 I3=3
      GOTO1970
 1950 I3=4
      GOTO1970
 1960 I3=1
 1970 CALL ROUT21(FRINN(1),DMIN(1),  FMXSN(1),FMXDN(1),FSLN(1))
C     FRINN(161),DMIN(101),FMXSN(161),FMXDN(130),FSLN(176)
      GOTO1500
 1980 IV=2
      GOTO2210
 1990 IV=3
      GOTO2210
 2000 IV=4
      GOTO2210
 2010 IV=5
      GOTO2210
 2020 IV=6
      GOTO2210
 2030 IV=7
      GOTO2210
 2040 IV=8
      GOTO2210
 2050 IV=9
      GOTO2210
 2060 IV=10
      GOTO2210
 2070 IV=11
      GOTO2210
 2080 IV=12
      GOTO2210
 2090 IV=13
      GOTO2210
 2100 IV=14
      GOTO2210
 2110 IV=15
      GOTO2210
 2120 IV=16
      GOTO2210
 2130 IV=17
      GOTO2210
 2140 IV=18
      GOTO2210
 2150 IV=19
      GOTO2210
 2160 IV=20
      GOTO2210
 2170 IV=21
      GOTO2210
 2180 IV=22
      GOTO2210
 2190 IV=23
      GOTO2210
 2200 IV=1
 2210 CALL ROUT22(PPAC(1),POAC(1),PNEC(1),PMXC(1),PNNEC(1))
C     PPAC(19),POAC(19),PNEC(126),PMXC(126),PNNEC(126)
      IV=IV
      IF(I1)2820,2220,2220
 2220 GOTO(2350,2230,770,1130,2890,500,520,490,3400,3010,2990,3310,720,1
     +60 ,870 ,420,480,580,2900,140,2330,3020,2240),IV
 2230 CALL CERROR(' BERT COM>3500,ESPS(1)>=30. COM>2500$')
      NOPART=-1
      RETURN
 2240 CALL CERROR(' BERT IV > 22$')
      NOPART=-1
      RETURN
 2250 XABS=1.0
      VALUE1 = RANDC2(ISEED)
      IF(VALUE1-PPNDA)2260,450,450
C     PROB. PIN-DEUT ABS
 2260 IT=27
C     BG117(20040) PI0 ABS
      MED=MED
      ABSEC=-HVP(MED)
      GO TO 370
 2270 IF(RLKE-2500.0)2290,2290,2280
 2280 CALL CERROR(' BERT RLKE > 2.5GeV$')
      RLKE=2500.0
 2290 IF(RLKE-180.0) 2320,2320,2300
 2300 IF(NOT-6) 2310,2310,2340
 2310 VALUE1=RLKE-180.0
      CALL CRJAB(1,PNSCL(1))
C     PNSCL(117)
C     (PIN-P)SINGLE PRODUCTION CRS. LOW EN.
      GO TO 3020
 2320 IF(CLSM-2.0)3550,3510,3040
 2330 IF(NOT-6)2190,2270,2270
 2340 VALUE1=RLKE-180.0
      CALL CRJAB(1,PNNSL(1))
C     PNNSL(117)
C     (PIN-N)SINGLE PROD. CRS. LOW EN.
      GOTO3020
 2350 ISW(11)=0
      GOTO2130
 2360 PT(14)=1.0
      GO TO 1320
 2370 I3=2
      GO TO 2400
 2380 I3=3
      GO TO 2400
 2390 I3=1
 2400 CALL ROUT16(PNDD(1))
C     HPNDDI(45),PNDDI(170),PNDDL(378)
C     (PIN-P)DRCT. CROSS SECTION INT. EN.
C     (PIN-P)DRCT DIFF. CRS. SEC. LOW ENERGY
 2410 GO TO 1290
 2420 PT(2)=3.0
      PT(14)=2.0
      IK=IT
      GO TO 980
 2430 PT(14)=2.0
      IK=23
      GO TO 1330
 2440 PT(2)=5.0
      GO TO 970
 2450 ISW(9)=2
      GO TO 1890
 2460 ITOTE  =IPEC(2)+IPEC(7)+IPEC(11)
      IF(ITOTE-1)2500,2480,2470
 2470 CALL CERROR('BERT1$')
 2480 NOPART = -1
 2490 CONTINUE
      RETURN
 2500 NOPART = ESPS(1)
      IF(NOPART-60)2520,2520,2510
 2510 WRITE(IO ,10000) NOPART
10000 FORMAT(' BERT : NOPART HAS EXCEEDED THE MAXIMUM = ',I6)
      NOPART = 60
 2520 CONTINUE
      DO 2530 NDEX = 1,NOPART
         KLMN = 8*(NDEX-1) + 1
         KIND(NDEX) = ESPS(KLMN+1)-1.
         ERAY(NDEX) = ESPS(KLMN+2)
         ARAY(NDEX) = ESPS(KLMN+3)
         BRAY(NDEX) = ESPS(KLMN+4)
 2530 GRAY(NDEX) = ESPS(KLMN+5)
      GO TO 2490
 2540 VALUE2=EINC+SPACE(12)
      IF(VALUE1-160.0)2550,2550,2570
 2550 SPACE(33)=1.4D-24
C     NO PRODUCTION POSSIBLE
      FMAX(2)=1.4D-24
      SPACE(34)=0.46D-24
      FMAX(1)=0.46D-24
      DO2560 I=9,12
 2560 S(I)=0.0
C     EINC+50.0 IS LESS THAN 160.0
      GOTO2740
 2570 CALL CBOVER(VALUE2,DNCMS,ANS)
C     NUCLEON MASS=CONSTANT  ANS=P1/E1
      IF(VALUE1-560.0)2580,2580,2660
 2580 S(11)=0.0
      S(12)=0.0
C     SINGLE PRODUCTION POSSIBLE--S(11),S(12) DOUBLE PROD.
      IF(VALUE1-400.0)2600,2590,2590
 2590 S(9)=22.6D-27*ANS
      S(10)=14.0D-27*ANS
      SPACE(44)=56.0D-27
      SPACE(45)=27.0D-27*ANS
      GOTO2650
 2600 IF(VALUE1-300.0)2620,2610,2610
 2610 S(9)=20.0D-27*ANS
      S(10)=14.0D-27*ANS
      SPACE(44)=0.106D-24
      SPACE(45)=36.0D-27*ANS
      GOTO2650
 2620 IF(VALUE1-200.0)2640,2630,2630
 2630 S(9)=11.4D-27*ANS
      S(10)=11.2D-27*ANS
      SPACE(44)=0.313D-24
      SPACE(45)=0.103D-24
      GOTO2650
 2640 S(9)=1.95D-27*ANS
      S(10)=1.7D-27*ANS
      SPACE(44)=0.52D-24
      SPACE(45)=0.176D-24
 2650 SPACE(33)=SPACE(44)
      SPACE(34)=SPACE(45)
      GOTO2740
 2660 IF(VALUE1-3600.0)2680,2680,2670
 2670 CALL CERROR(' BERT VALUE1 > 3.6GeV$')
      NOPART=-1
      RETURN
 2680 S(9)=22.6D-27*ANS
C     DOUBLE PRODUCTION POSSIBLE
      S(10)=14.0D-27*ANS
      IF(VALUE1-800.0)2690,2700,2700
 2690 S(11)=1.9D-27*ANS
      S(12)=9.0D-27*ANS
      SPACE(46)=38.4D-27*ANS
      SPACE(47)=27.2D-27*ANS
      GOTO2730
 2700 IF(VALUE1-1680.0)2710,2720,2720
 2710 S(11)=10.8D-27*ANS
      S(12)=17.4D-27*ANS
      SPACE(46)=33.0D-27*ANS
      SPACE(47)=27.2D-27*ANS
      GOTO2730
 2720 SPACE(46)=25.0D-27*ANS
      SPACE(47)=26.5D-27*ANS
      S(10)=13.6D-27*ANS
      S(11)=18.0D-27*ANS
      S(12)=23.6D-27*ANS
 2730 SPACE(33)=SPACE(46)
      SPACE(34)=SPACE(47)
 2740 GO TO (2750,3630), NO
 2750 IV=1
 2760 CALL CALXYI(9,33,41)
      IP=2
 2770 IF(NO-2)2790,2780,2780
 2780 ISW(4)=0
      GO TO 2800
 2790 ISW(4)=1
 2800 CALL UNDIS
      IF(BEGRU) 2810,2460,2810
 2810 XABS=0.0
      XINC=XI(1)
C     XINC=X-COORDINATE INC.PART.
      INC=1
C     0 IF PARTICLE CASCADE
      CURR(1)=NO
      CURR(3)=DNCMS
C     NUCLEON MASS/CM
      CALL CALGEO
      IF(I1) 2820,2830,2830
 2820 CALL CERROR(' BERT error in GEOM$')
      NOPART=-1
      RETURN
 2830 CALL PARTIN
      CALL SPAC32(43)
 2840 IF(EX-D(2))2850,2850,3120
 2850 WKRPN(3)=OUT(13)
      WKRPN(6)=OUT(16)
      CURR(2)=WKRPN(6)
      IF(ISW(4))2860,2870,2860
 2860 CURR(2)=WKRPN(3)
C     K.E.WITH RESPECT TO NEUTRONS(PROTONS), RG.3
 2870 CALL CBG6CA(3,0)
      IFCA=3
 2880 IFCC=3
 2890 KA=6
 2900 CALL CABRAN(KA)
      KNOT=NOT+6
      IF(IN)2920,2920,2910
 2910 KNOT=KNOT+6
 2920 IF(KNOT-17)2930,2250,2930
 2930 CALL CABG6C(ISW(4))
      IF(RLKE)2940,2940,2950
 2940 CALL CERROR(' BERT RLKE <= 0.0$')
      NOPART=-1
      RETURN
 2950 VALUE1=RLKE
      IF(IN) 2140,2960,2140
 2960 IF(NOT-5) 2970,3400,3400
 2970 IF(NOT-2)2980,3000,3310
 2980 ANY=SPACE(33)
 2990 CALL CRJAB(1,ECN(1))
C     ECN(176)
C     (N-P)ELASTIC CRS. SCATTERING
      GOTO3020
 3000 ANY=SPACE(34)
 3010 CALL CRJAB(1,PEC(1))
C     PEC(176)
C     (P-P)ELASTIC SCAT. CRS.
 3020 IF(CLSM-2.0)3540,3500,3030
 3030 IF(VALUE1-VALUE2)200,200,3040
 3040 CALL SIGNEX
      IF(ISW(1))3070,3050,3070
 3050 IF(IN)3060 ,2840,3060
 3060 IF(CURR(1)-2.0)2200,2200,2150
 3070 IF(IN)2010,3080,2010
 3080 IF(EX-D(6))2850,2850,3090
 3090 IF(ISW(2))3110,3100,3110
 3100 IPEC(7)=IPEC(7)+1
C     NO. OF ESCAPED PARTICLES ON RG.2
      GOTO 2770
 3110 IPEC(11)=IPEC(11)+1
      GOTO 2770
C     NO. OF PARTICLES ESCAPED ON RG.1
 3120 IF(D(3))3140,3130,3140
 3130 IPEC(2)=IPEC(2)+1
      GOTO 2770
C     NO. OF PARTICLES INCIDENT ON RG.3 ESCAPING
 3140 ISW(1)=1
      CALL SPAC32(42)
 3150 IF(EX-D(3))3160,3160,3190
 3160 WKRPN(2)=OUT(14)
      WKRPN(5)=OUT(17)
      CURR(2)=WKRPN(5)
      IF(ISW(4))3170,3180,3170
 3170 CURR(2)=WKRPN(2)
C     K.E.WITH RESPECT TO NEUTRONS(PROTONS) RG.2
 3180 CALL CBG6CA(2,0)
      GOTO2880
 3190 IF(D(4))3220,3200,3220
 3200 CALL SPAC32(43)
 3210 IF(EX-D(6))2850,2850,3100
 3220 ISW(2)=1
      ISW(3)=1
      CALL SPAC32(41)
 3230 IF(EX-D(4))3280,3280,3240
 3240 CALL SPAC32(42)
 3250 IF(EX-D(5))3160,3160,3260
 3260 CALL SPAC32(43)
 3270 IF(EX-D(6))2850,2850,3110
 3280 WKRPN(1)=OUT(15)
      WKRPN(4)=OUT(18)
      CURR(2)=WKRPN(4)
      IF(ISW(4))3290,3300,3290
 3290 CURR(2)=WKRPN(1)
C     K.E. WITH RESPECT TO NEUTRONS(PROTONS) RG.1
 3300 CALL CBG6CA(1,0)
      GOTO 2880
 3310 IF(RLKE-3500.0)3330,3330,3320
 3320 CALL CERROR(' BERT RLKE>3.5GeV (2)$')
      RLKE=3500.0
 3330 IF(RLKE-360.0)3530,3530,3340
 3340 VALUE1=RLKE-360.0
      IF(IN)3360,3350,3360
 3350 ANY=S(KNOT)
 3360 IF(NOT-4)3380,3390,3370
 3370 CALL CERROR(' BERT NOT=5$')
      NOPART=-1
      RETURN
 3380 CALL CRJAB(1,PSPCL(1))
C     PSPCL(158)
C     (P-P) SING. PROD. CRS. LOW ENERGY
      GOTO 3020
 3390 CALL CRJAB(1,SPCLN(1))
C     SPCLN(158)
C     (N-P) SINGLE PROD. CRS. LOW ENERGY
      GOTO 3020
 3400 IF(RLKE-3500.0)3410,3410,3320
 3410 IF(RLKE-920.0)3530,3530,3420
 3420 VALUE1=RLKE-920.0
      IF(NOT-6)3440,3470,3430
 3430 CALL CERROR(' BERT NOT > 6$')
      NOPART=-1
      RETURN
 3440 IF(IN)3460,3450,3460
 3450 ANY=S(11)
 3460 CALL CRJAB(1,PDPCL(1))
C     PDPCL(130)
C     (P-P) DOUBLE PRODUCTION CRS. LOW ENERGY
      GOTO 3020
 3470 IF(IN)3490,3480,3490
 3480 ANY=S(12)
 3490 CALL CRJAB(1,DPCLN(1))
C     DPCLN(130)
C     (N-P) DOUBLE PRODUCTION CRS. LOW ENERGY
      GOTO 3020
 3500 IF(VALUE1-VALUE2)730,730,3510
 3510 CALL SIGNEX
      IF(IN)2160,3520,2160
 3520 IF(ISW(3))3250,3150,3250
 3530 IF(CLSM-2.0)3550,3510,3040
 3540 IF(VALUE1-VALUE2)890 ,890 ,3550
 3550 CALL SIGNEX
      IF(IN)2170,3230,2170
 3560 IF(ESPS(1))3580,3570,3580
 3570 NWDS=1
      GOTO 3610
 3580 NWDS=ESPS(1)*8.0+1.5
C     TOTAL NO. OF WORDS(ESCAPING PARTICLES)
      IF(COUNT(6).GE.0.0) GO TO 3610
C MINUS,RECORD NOT REPRESENTATIVE,SKIP
      DO 3590 I=1,NWDS
 3590 ESPS(I) = 0.0
      DO 3600 I=1,5
 3600 COUNT(I) = 0.0D0
 3610 NOR=NOR+1
 3620 IN=0
      GOTO(110,2770),IP
 3630 IV=-1
      GOTO 2760
C1370 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.37  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CABG6B
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      SAVE
      CALL CZERO
      J=I2
      DO10 I=2,I4
         CE(I)=SPACE(J)
   10 J=J+1
      J=I4+1
      DO20 I=J,6
         CE(I)=S(I3)
   20 I3=I3+1
      RETURN
      END
*CMZ :  0.92/03 10/12/92  10.53.07  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CABG6C(INT1)
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      IF(KNOT-7)10,190,190
   10 XABS=0.0
      IF(KNOT-2)20,30,30
   20 IF(INT1)70,100,70
   30 IF(KNOT-5)40,50,60
   40 IF(INT1)100,70,100
   50 IT=11
      IF(INT1)80,110,80
   60 IT=12
      IF(INT1)110,80,110
   70 IT=2*KNOT-1
   80 STRKP=-1.0
   90 I1=0
      GOTO130
  100 IT=2*KNOT
  110 STRKP=-2.0
  120 I1=1
  130 I2=CLSM
      CALL CBBBBB
  140 CALL CAISOM
      GOTO(150,150,150,160,150,150,180,180,180,180,180,180,150,150,150,
     +150,160,150,150), KNOT
  150 IF(RLKE-2500.0)170,170,140
  160 RLKE=0.0
  170 RETURN
  180 IF(RLKE-3500.0)170,170,140
  190 IF(KNOT-12)200,200,310
  200 IF(IN)370,210,370
  210 IF(KNOT-8)220,270,320
  220 IF(INT1)230,250,230
  230 IT=2*(KNOT+1)
  240 STRKP=-2.0
      GOTO90
  250 IT=2*KNOT+1
  260 STRKP=-1.0
      GOTO120
  270 IF(INT1)280,300,280
  280 IT=2*(KNOT+1)
  290 GOTO80
  300 IT=2*KNOT+1
      GOTO110
  310 IF(KNOT-18)320,450,450
  320 IT=KNOT+10
  330 IF(KNOT-10)340,350,360
  340 IF(INT1)80,110,80
  350 IF(INT1)240,260,240
  360 IF(KNOT-12)340,350,430
  370 IF(KNOT-8)380,400,320
  380 IF(INT1)390,320,390
  390 IT=KNOT+11
      GOTO80
  400 IF(INT1)420,410,420
  410 IT=2*KNOT-1
      GOTO260
  420 IT=KNOT+KNOT
      GOTO240
  430 XABS=0.0
      IF(KNOT-15)80,110,440
  440 IF(KNOT-18)110,80,110
  450 IT=28
      GOTO430
      END
*CMZ :  0.92/00 02/12/92  16.02.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CBG6CA(K,L)
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      CLSM=K
      IF(IN)20,10,20
   10 CURR(10)=CLSM
      CURR(11)=CLSM
C     COLLISION MED. STORED IN REGION OF INITIAL COLL. AND
C     MEDIUM WHERE PARTICLE WAS BORN
   20 EFRP=SPACE(K+9)-7.0
C     PROTON WELL DEPTH + BINDING ENERGY=FERMI ENERGY PROTONS--MEV
      EFRN=SPACE(K+3)-7.0
      PM(2)=DNCMS
C     NUCLEON MASS PER CM
      PM(1)=DNCMS
      IF(K-L)30,40,50
   30 PM(1)=POMS
C     PI0 MASS PER CM
      GOTO50
   40 PM(1)=PNMS
C     PI(+OR-) MASS PER CM
   50 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.37  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CABIG7(C,GREAT,IX)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      REAL*8 C, GREAT
C
      GREAT = C
      I = IX + 1
      DO 10 K = 1,I
         C = RANDC2(ISEED)
         IF(C.LT.GREAT) GO TO 10
         GREAT = C
   10 CONTINUE
C     GREAT IS THE LARGEST OF I RANDOM NOS.
      RETURN
      END
*CMZ :  0.90/00 05/06/92  10.53.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CBOVER(V,VE,VER)
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL *8 V,VE,VER
C
      VER=DSQRT(1.0-((VE*VE)/((V*RCPMV+VE)**2)))
      VER=(DSQRT(VER*(6.91D-1+(VER*11.09D-1))+1.08D-1))/VER
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CCPES
      SAVE
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
*KEEP,CRN.
       COMMON/CRN/COUNT
       REAL*8 COUNT(10)
C
*KEND.
C
      I1=0
      I = IDINT(CURR(1) + 5.0D-2)
      COUNT(I) = COUNT(I) + 1.0D0
C*** COUNT NO. OF TIMES EACH TYPE OF PARTICLE ESCAPES
      IF(CURR(1)-2.0)10,20,10
   10 K=CURR(10)+9.05
      GOTO30
   20 K=CURR(10)+3.05
   30 IF(ESPS(1)-60.0)60,40,40
   40 I1=1
C     STORAGE ALREADY FILLED
   50 RETURN
   60 L=ESPS(1)*8.D0 + 2.05D0
      ESPS(L)=CURR(1)
      ESPS(L+1)=CURR(2)-SPACE(K)
      M=13.05-CURR(11)
      CC(M)=CC(M)+1.0
      M=4
      L=L+2
      N=L+2
      DO70 I=L,N
         ESPS(I)=CURR(M+3)
         ESPS(I+3)=CURR(M)
   70 M=M+1
      ESPS(1)=ESPS(1)+1.0
      GOTO50
      END
*CMZ :  0.92/03 10/12/92  10.53.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE COLE4
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      K=CLSM
      COM=(E(4)-DNCMS)/RCPMV
C     K.E. OF PARTICLE 4 IN MEV
C     TYPE OF PARTIL. 1-5  CURRENT NUCLEON
      IF(CURR(1)-3.0)120,10,10
   10 IF(XABS)20,30,20
   20 COM=COM+ABSEC
      GOTO120
   30 IF(IT-5)40,70,40
   40 IF(IT-24)50,70,50
   50 IF(IT-6)60,80,60
   60 IF(IT-26)120,80,120
   70 UNIV=0.0
C     NEUT WITH WRONG ENERGY
      GOTO90
   80 UNIV=1.0
   90 UNIVE=SPACE(K+3)-SPACE(K+9)
C     REGION I N-P WELL DEPTH DIFFERENCE
      IF(UNIV)110,100,110
  100 COM=COM+UNIVE
      GOTO120
  110 COM=COM-UNIVE
  120 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CACOLL(M)
      SAVE
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      IF(M)10,20,20
   10 A=PM(4)*PM(4)
      GOTO30
   20 A=SQNM
   30 COL(15)=0.0
      MED=CLSM
      ECO (1)=CFEPN(MED)
      ECO (2)=CFEPN(MED+3)
C     PROTON(NEUTRON) ENERGY CUT-OFF
      COL(1)=E(1)+E(2)
C     TOTAL ENERGY PARTICLES 1 AND 2
      DO40 I=1,3
   40 COL(I+1)=PM(I)*PM(I)
C     MASS PARTICLE I SQD.
      COL(5)=COL(3)+COL(2)+2.0*(E(1)*E(2)-(PXYZ(1)*PXYZ(2)+PXYZ(5)*
     1PXYZ(6)+PXYZ(9)*PXYZ(10)))
      COL(6)=DSQRT(COL(5))
      COL(7)=COL(6)/COL(1)
C     GAM
      COL(8)=2.0*COL(6)
      COL(9)=(COL(4)+COL(5)-A)/COL(8)
      COM2=COL(9)*COL(9)
   50 IF(COL(4)-2.9882156D27)60,60,80
C     GT,PM(3)=ISOBAR--LTE,TEST FOR ROUNDOFF RANGE,(MIN)SQD+OR-5D23
   60 IF(COL(4)-2.9872156D27)90,70 ,70
C     LT,PION OR NUCLEON MASS=PM(3)
   70 COL(4)=2.9877156D27
      PM(3) = 5.466005D13
   80 IF(COM2-COL(4))100,120,120
   90 IF(COL(4) - SQNM) 80,80,140
C     LTE,HAVE NUCLEON OR PION--GT,GO TO ERROR
  100 IF(COM2 - 9.9D-1 * COL(4)) 120,110,110
  110 COM2 = COL(4)
      COL(9) = PM(3)
  120 COL(10)=DSQRT(COM2-COL(4))
C     P3 PRIME
      COL(11)=(COL(5)+COL(2)-COL(3))/COL(8)
C     E1 PRIME
      COL(12)=DSQRT(COL(11)*COL(11)-COL(2))
C     P1 PRIME
      COL(13)=(COL(7)*E(1)-COL(11))/COL(12)
C     BETA
      COM=1.0-(COL(13)*COL(13)+COL(7)*COL(7))
      IF(COM-5.0D-6)130,170,170
  130 IF(COM+5.0D-6)140,160,160
  140 COL(15)=1.0
C     ERROR
  150 RETURN
  160 COL(14)=2.236067977D-3
      GOTO180
  170 COL(14)=DSQRT(COM)
C     ALPHA
  180 E(3)=(COL(9)+COL(10)*(COL(13)*CST+COL(14)*SOPC*SNT))/COL(7)
      E(4)=COL(1)-E(3)
      GOTO150
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE COLLM(M)
      SAVE
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      REAL *8 B
      UNIV=E(2)+COL(6)-COL(11)
      UNIVE=E(1)+COL(11)
      UNIVER=COL(1)+COL(6)
      K=16
      DO10 I=1,9,4
         COL(K)=(PXYZ(I)*UNIV-PXYZ(I+1)*UNIVE)/UNIVER
         COL(K+3)=(PXYZ(I)+PXYZ(I+1))/COL(1)
C     VX
   10 K=K+1
      COL(22)=(PXYZ(10)*PXYZ(5)-PXYZ(9)*PXYZ(6))/COL(1)
C     QX
      COL(23)=(PXYZ(2)*PXYZ(9)-PXYZ(10)*PXYZ(1))/COL(1)
C     QY
      COL(24)=(PXYZ(6)*PXYZ(1)-PXYZ(5)*PXYZ(2))/COL(1)
      A=SNT/COL(14)
      B=A*COL(10)
C     (-BETA*COS PHI*SIN THETA/ALPHA + COS THETA)/P1P*P3P
      UNIV=COL(10)*(CST-A*SOPC*COL(13))/COL(12)
      UNIVE=B*SOPS/COL(12)
C     P3P*SIN PHI*SIN THETA/P1P*ALPHA
      UNIVER=(SOPC*B)+((E(3)+COL(9))/(COL(7)+1.0))
C     COS PHI*SIN THETA*P3P/ALPHA  +  (E3+E3P)/(1.0+GAMMA)
      K=19
      DO20 I=3,11,4
         PXYZ(I)=COL(K)*UNIVER+COL(K+3)*UNIVE+COL(K-3)*UNIV
   20 K=K+1
      IF(M)30,40,30
   30 IF(PT(15))40,60,40
   40 DO50 I=1,9,4
   50 PXYZ(I+3)=PXYZ(I)+PXYZ(I+1)-PXYZ(I+2)
      IF(M)60,130,60
   60 IF(PT(3))70,100,70
   70 PT(4)=PM(3)
      I1=3
   80 I2=-1
      CALL PSTOR
   90 IF(I1-3)100,100,120
  100 IF(PT(15))110,120,110
  110 PT(16)=DNCMS
C     NUCLEON MASS PER CM
      I1=4
      GOTO80
  120 PT(27)=0.0
      PT(39)=0.0
  130 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CRDET(NODATA,DATA,ENER)
      REAL*8 DATA(6426),ENER
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      IE=DABS(ENER/20.0)
C     ENERGY INTERVAL
      UNIV=(ENER-DFLOAT(IE)*20.0)/20.0
C     INPT=0 IF WHOLE INTERVAL CONSIDERED
C     NODATA=DATA PER ENERGY INTERVAL
      DO10 I=1,25
   10 CRDT(I)=0.0
C     ANSWERS STORED IN CRDT
   20 K=(NODATA*IE)+1
   30 IF(INPT)40,50 ,80
   40 WRITE(6,*) ' CALOR: ERROR in CRDET ====> STOP'
      STOP
   50 N=NODATA
   60 L=K+NODATA
      DO70 I=1,N
         CRDT(I)=(DATA(L)-DATA(K))*UNIV+DATA(K)
         K=K+1
   70 L=L+1
      INPT=0
      RETURN
   80 K=INPT-1+K
      N=2
      GOTO60
C     NOT ALL PARTS EVALUATED
      END
*CMZ :  0.90/00 29/07/92  13.00.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CRJAB(K1,PP)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      REAL*8 PP(380)
C
      CALL CRDET(K1,PP(1),VALUE1)
      VALUE1=(PXYZ(1)*PXYZ(2)+PXYZ(5)*PXYZ(6)+PXYZ(9)*PXYZ(10))
     1/E(1)
C     P1.P2/E(1)
      VALUE2=(VALUE1/(P2*P2))*((E(2)/DNCMS)-1.0)-(1.0/DNCMS)
C     S=((P1.P2)/(E1*P2*P2))*((E2/M)-1.0)-1.0/M
      VALUE2=DNCMS*CRDT(1)*DSQRT(P1OE1*P1OE1+2.0*VALUE1
     1*VALUE2+P2*P2*VALUE2*VALUE2)/(E(2)*P1OE1*ANY)
C     (M)(C.S)(J**2+2S(P1.P2)/E1+(P2)(P2)(S)(S)
CZ changed 20.june 92 CZ
      IF(VALUE2.GT.1.0) VALUE2 = 1.0
C     THIS TESTS SAMPLING TECH.TO ENSURE FMAXS WERE SELECTED SO THAT
C     VALUE2 LTE ONE.
      VALUE1 = RANDC2(ISEED)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE DCINTP(W)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      REAL*8 W(250),Z(24),FLTI
      SAVE
C
      Z(1)=RLKE-6.6D2
      IE=IDINT(Z(1)/2.0D1+5.0D-6)
      UNIV=(Z(1)-DFLOAT(IE)*2.0D1)/2.0D1
      IE=IE+1
      UNIVE=(W(IE+1)-W(IE))*UNIV+W(IE)
C RATIO
      I2=0
      K=1
      UNIV = RANDC2(ISEED)
      IF(UNIV.GE.UNIVE)GOTO190
C LT=BACKWARD
C N-P ELASTIC SCAT.,RLKE GT 660
      LLL=179
      IF(W(180).GT.RLKE) GO TO 20
      DO 10 I = 1,5
         IF(W(179+K).GT.RLKE)GO TO 40
   10 K=K+12
   20 I1=-1
C ERROR
   30 RETURN
   40 M=12
   50 DO60 L=1,M
         Z(L+M)=W(LLL+K)
         Z(L)=W(LLL+K-M)
   60 K=K+1
      UNIV = RANDC2(ISEED)
      UNIVE=(RLKE-Z(1))/(Z(M+1)-Z(1))
      DO70 I=2,M
         P=(Z(I+M)-Z(I))*UNIVE+Z(I)
         IF(P.GE.UNIV) GO TO 80
   70 CONTINUE
      GO TO 20
   80 I1=I
      UNIV = RANDC2(ISEED)
      FLTI=UNIV+DFLOAT(I1-2)
      IF(M.LE.9) GO TO 230
   90 GOTO(20,100,100,110,120,130,130,140,150,160,170,180),I1
  100 CST=1.0D-2*FLTI-0.1D1
      GO TO 30
  110 CST=2.0D-2*UNIV-9.8D-1
      GO TO 30
  120 CST=4.0D-2*UNIV-9.6D-1
      GO TO 30
  130 CST=6.0D-2*FLTI-0.116D1
      GO TO 30
  140 CST=8.0D-2*UNIV-8.0D-1
      GO TO 30
  150 CST=1.0D-1*UNIV-7.2D-1
      GO TO 30
  160 CST=1.2D-1*UNIV-6.2D-1
      GO TO 30
  170 CST=2.0D-1*UNIV-5.0D-1
      GO TO 30
  180 CST=3.0D-1*(UNIV-1.0D0)
      GO TO 30
C FORWARD
  190 LLL=143
      IF(W(144).GT.RLKE) GO TO 20
  200 DO 210 I = 1,4
         IF(W(143+K).GT.RLKE) GO TO 220
  210 K=K+9
      GOTO20
  220 M=9
      GOTO50
  230 GOTO(20,240,240,240,240,250,260,270,280),I1
  240 CST=1.0D0-2.5D-2*FLTI
      GOTO30
  250 CST=8.5D-1+0.5D-1*UNIV
      GOTO30
  260 CST=7.0D-1+1.5D-1*UNIV
      GOTO30
  270 CST=5.0D-1+2.0D-1*UNIV
      GOTO30
  280 CST=5.0D-1*UNIV
      GOTO30
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CADCPR(W,LK)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      REAL*8 W(60),Z(24)
      REAL*8 FRACT,R,SUM,FLTI
      SAVE
C
C PDCI HAS KK=12, PDCH HAS KK=11
      I2=0
      KK=LK
      K=1
      DO10 I=1,5
         IF(W(K).GE.RLKE)GOTO40
   10 K=K+KK
   20 I2=1
C ERROR RETURN
   30 RETURN
   40 DO 50 L = 1,KK
         Z(L+KK)=W(K)
         Z(L)=W(K-KK)
   50 K=K+1
      SUM=0.0D0
      R = RANDC2(ISEED)
      FRACT=(RLKE-Z(1))/(Z(KK+1)-Z(1))
      DO 60 I = 2,KK
         SUM=SUM+Z(I)+((Z(I+KK)-Z(I))*FRACT)
         IF(R.LT.SUM) GO TO 70
   60 CONTINUE
      GO TO 20
C ERROR
   70 R = RANDC2(ISEED)
      I1=I
      IF(KK.GT.11) GO TO 90
      IF(I1.GT.2) GO TO 80
      CST=4.0D-1*R
      GO TO 150
   80 I1=I1+1
   90 FLTI=DFLOAT(I1-2)+R
  100 GO TO (20,110,110,110,120,120,130,130,130,130,140,140),I1
  110 CST=2.0D-1*(FLTI)
      GO TO 150
  120 CST=3.0D-1+1.0D-1*(FLTI)
      GO TO 150
  130 CST=6.0D-1+4.0D-2*(FLTI)
      GO TO 150
  140 CST=7.8D-1+2.0D-2*(FLTI)
  150 R = RANDC2(ISEED)
      IF(R.GT.5.0D-1) GO TO 30
      CST=-(CST)
      GO TO 30
      END
*CMZ :  0.92/00 02/12/92  16.02.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE DFMAX
      SAVE
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL*8 WK
C
      I=I2
      IF(CURR(1)-2.0)20,10,10
   10 I=I+3
   20 WK=WKRPN(I)
   30 CALL CBOVER(WK,DNCMS,UNIV)
      IF(WK-560.0)40,40,60
   40 FMAX(1)=27.2D-27*UNIV
C     820 MEV
C     (P-P)S
      FMAX(2)=38.0D-27*UNIV
C     230 MEV
C     (P-N)S
      FMAX(3)=22.6D-27*UNIV
C     1020 MEV
C     (P-P)S.P.
      FMAX(4)=14.0D-27*UNIV
C     750 MEV
C     (P-N)S.P.
      FMAX(5)=0.0
C     (P-P)D.P.
      FMAX(6)=0.0
C     (P-N)D.P.)
   50 RETURN
   60 IF(WK-800.0)70,90,90
   70 FMAX(2)=37.0D-27*UNIV
C     250 MEV
      FMAX(5)=1.9D-27*UNIV
C     5 AN6 AT 1380 MEV
      FMAX(6)=9.0D-27*UNIV
   80 FMAX(1)=27.2D-27*UNIV
C     820 MEV
      FMAX(3)=22.6D-27*UNIV
C     1020
      FMAX(4)=14.0D-27*UNIV
C     750
      GO TO 50
   90 IF(WK-1680.0)100,110,110
  100 FMAX(2)=33.0D-27*UNIV
C     400
      FMAX(5)=10.8D-27*UNIV
C     5 AND 6 AT 2600
      FMAX(6)=17.4D-27*UNIV
      GO TO 80
  110 FMAX(1)=26.3D-27*UNIV
C     1000
      FMAX(2)=24.7D-27*UNIV
C     1000
      FMAX(3)=22.6D-27*UNIV
C     1020
      FMAX(4)=13.5D-27*UNIV
C     1000
      FMAX(5)=18.0D-27*UNIV
      FMAX(6)=23.6D-27*UNIV
C     3500
      GO TO 50
      END
*CMZ :  0.92/00 02/12/92  16.02.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CAECPL
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      SAVE
      I1=0
      MED=CLSM
      IF(PT(38))590,10,590
   10 IF(CURR(1)-1.0)380,540,20
   20 IF(CURR(1)-3.0)450,420,30
   30 IF(CURR(1)-5.0)320,40,380
   40 IF(STRKP+1.0)50,60,380
   50 IF(STRKP+2.0)380,230,380
   60 IF(PT(2)-2.0)80,70,80
   70 PT(3)=VNVP(MED)
      GOTO90
C     PI-,CURR(1)=5.0,PT6+1=0,STRKP=1.0
   80 PT(3)=0.0
   90 PT(15)=HVP(MED)
      IF(PT(26)-1.0)380,190,100
  100 IF(PT(26)-2.0)380,110,380
  110 PT(27)=-PPAN(MED)
      IF(CURR(1)-2.0)580,120,120
C     PPAN=-VNHP(NEUT.WELL DEPTH-1/2PROTON WELL DEPTH)
  120 IF(CURR(1)-4.0)440,380,130
  130 IF(PT(2)-3.0)380,150,140
  140 IF(PT(2)-5.0)170,180,380
  150 IF(PT(14)-5.0)380,160,380
  160 RETURN
  170 IF(PT(14)-4.0)380,160,380
  180 IF(PT(14)-3.0)380,160,380
C     1/2PROT.WELL DEPTH
  190 PT(27)=HVP(MED)
      IF(CURR(1)-2.0)560,200,200
  200 IF(CURR(1)-4.0)400,380,210
  210 IF(PT(2)-4.0)380,150,220
  220 IF(PT(2)-5.0)380,170,380
  230 PT(3)=-VNVP(MED)
  240 PT(15)=-PMAC(MED)
  250 IF(PT(26)-1.0)380,270,260
  260 IF(PT(26)-2.0)380,300,380
  270 PT(27)=-PMAC(MED)
      IF(CURR(1)-2.0)150,150,280
  280 IF(CURR(1)-4.0)130,210,290
  290 IF(PT(2)-5.0)380,150,380
  300 PT(27)=HVN(MED)
      IF(CURR(1)-2.0)170,170,310
  310 IF(CURR(1)-4.0)400,130,210
  320 IF(STRKP+1.0)330,340,380
  330 IF(STRKP+2.0)380,230,380
C     PI0
  340 PT(3)=0.0
  350 PT(15)=HVP(MED)
      IF(PT(26)-1.0)380,370,360
  360 IF(PT(26)-2.0)380,390,380
  370 PT(27)=HVP(MED)
      IF(CURR(1)-4.0)170,130,380
  380 I1=1
      GOTO160
  390 PT(27)=-PPAN(MED)
      IF(CURR(1)-4.0)180,400,380
  400 IF(PT(2)-3.0)380,170,410
  410 IF(PT(2)-4.0)380,180,380
  420 IF(STRKP+1.0)430,60,380
C     PI+
  430 IF(STRKP+2.0)380,230,380
  440 IF(PT(2)-3.0)380,180,380
  450 IF(STRKP+1.0)460,470,380
C     NEUTRON
  460 IF(STRKP+2.0)380,490,380
  470 PT(3)=0.0
      IF(PT(2)-1.0)380,240,480
  480 IF(PT(2)-2.0)380,350,380
  490 PT(15)=-PMAC(MED)
      IF(PT(2)-1.0)380,510,500
  500 IF(PT(2)-2.0)380,530,380
  510 IF(PT(26)-2.0)380,520,380
  520 PT(3)=-VNVP(MED)
      PT(27)=HVN(MED)
      GOTO150
  530 PT(3)=0.0
      GOTO250
  540 IF(STRKP+1.0)550,60,380
  550 IF(STRKP+2.0)380,470,380
C     PROTON
  560 IF(PT(2)-1.0)380,170,570
  570 IF(PT(2)-2.0)380,180,380
  580 IF(PT(2)-1.0)380,180,380
  590 IF(CURR(1)-1.0)380,610,600
  600 IF(CURR(1)-2.0)380,630,380
  610 IF(STRKP+1.0)620,840,380
  620 IF(STRKP+2.0)380,650,380
  630 IF(STRKP+1.0)640,650,380
  640 IF(STRKP+2.0)380,960,380
  650 IF(PT(14))380,380,660
  660 IF(PT(38))380,380,670
  670 IF(PT(38)-2.0)680,740,380
  680 IF(PT(14)-2.0)690,800,380
  690 PT(3)=TFFN(MED)
      PT(15)=TFFN(MED)
      PT(27)=TFFN(MED)
      PT(39)=TFFN(MED)
  700 IF(PT(2)-3.0)380,380,710
  710 IF(PT(2)-5.0)730,720,380
  720 IF(PT(26)-4.0)380,160,380
  730 IF(PT(26)-5.0)380,160,380
  740 IF(PT(14)-2.0)750,810,380
  750 PT(27)=FFPTFN(MED)
      PT(3)=FVNP(MED)
  760 PT(39)=FVNP(MED)
      PT(15)=FVNP(MED)
  770 IF(PT(2)-3.0)380,730,780
  780 IF(PT(2)-5.0)720,790,380
  790 IF(PT(26)-3.0)380,160,380
  800 PT(3)=FFPTFN(MED)
      PT(27)=FVNP(MED)
      GOTO760
  810 PT(3)=TFFN(MED)
      PT(27)=TFFN(MED)
      PT(15)=TFFP(MED)
      PT(39)=TFFP(MED)
  820 IF(PT(2)-3.0)380,720,830
  830 IF(PT(2)-4.0)380,790,380
  840 IF(PT(14))380,380,850
  850 IF(PT(38)-1.0)380,870,860
  860 IF(PT(38)-2.0)380,930,380
  870 IF(PT(14)-2.0)880,900,380
  880 PT(3)=HVP(MED)
  890 PT(15)=HVP(MED)
      PT(27)=HVP(MED)
      PT(39)=HVP(MED)
      IF(PT(14)-2.0)770,700,380
  900 PT(27)=HVN(MED)
  910 PT(3)=-PMAC(MED)
  920 PT(39)=HVN(MED)
      PT(15)=HVN(MED)
      IF(PT(38)-2.0)820,770,380
  930 IF(PT(14)-2.0)940,950,380
  940 PT(3)=HVN(MED)
      PT(15)=HVN(MED)
      PT(27)=-PMAC(MED)
      PT(39)=HVN(MED)
      GOTO820
  950 PT(15)=-PPAN(MED)
      PT(39)=-PPAN(MED)
      PT(3)=HVP(MED)
      PT(27)=HVP(MED)
      IF(PT(2)-3.0)380,790,380
  960 IF(PT(14))380,380,970
  970 IF(PT(38)-1.0)380,990,980
  980 IF(PT(38)-2.0)380,1020,380
  990 IF(PT(14)-2.0)1000,1010,380
 1000 PT(39)=-PMAC(MED)
      PT(15)=-PMAC(MED)
      PT(27)=-PMAC(MED)
      PT(3)=-PMAC(MED)
      IF(PT(2)-5.0)380,730,380
 1010 PT(3)=THPN(MED)
      GOTO890
 1020 IF(PT(14)-2.0)1030,1040,380
 1030 PT(3)=HVP(MED)
      PT(15)=HVP(MED)
      PT(39)=HVP(MED)
      PT(27)=THPN(MED)
      GOTO700
 1040 PT(27)=-PMAC(MED)
      GOTO910
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CERROR(CARG)
C
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,CERRCM.
      LOGICAL CERRF
      COMMON/CERRCM/CERRF,IERRU
*KEND.
C
      CHARACTER*1 CARG(50),CPRT(50)
      CHARACTER*1 ZEI,CEND
      DATA CEND/'$'/
C
      DO 10 I=1,50
         ZEI=CARG(I)
         IF(ZEI.EQ.CEND) GOTO 20
         CPRT(I)=CARG(I)
   10 CONTINUE
   20 DO 30 J=I,50
         CPRT(J)=' '
   30 CONTINUE
      WRITE(IOUT,*) ' HETC : ERROR in ',CPRT
C
      CERRF = .TRUE.
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE EXPRN(EXPA)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      REAL * 8 EXPA,EXPB,WHOLE,EXPAO
C
      WHOLE=0.0
   10 EXPA = RANDC2(ISEED)
      EXPAO=EXPA
   20 EXPB = RANDC2(ISEED)
      IF(EXPB.LT.EXPA) GO TO 40
C     RANDOM2 IS.GTE.TO RANDOM1
   30 EXPA=EXPAO+WHOLE
      RETURN
   40 EXPA = RANDC2(ISEED)
      IF(EXPA.LT.EXPB) GO TO 20
      WHOLE=WHOLE+1.0
      GO TO 10
      END
*CMZ :  0.92/00 02/12/92  16.02.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE FRMICC(GPART)
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      DIMENSION G(3)
      REAL * 8 GPART,G
      SAVE
C
      DO 10 I = 1,3
   10 G(I) = RANDC2(ISEED)
C     FIND LARGEST OF 3 RANDOM NOS.
      IF(G(3).LT.G(2)) GO TO 40
C     3.GTE.2
      IF(G(3).LT.G(1))GO TO 30
C     3.GTE.2,AND 3.GTE.1
      GPART=G(3)
   20 RETURN
   30 GPART=G(1)
C     3.GTE.2 AND 3.LT.1 OR 3.LT.2 AND 2.LT.1
      GO TO 20
   40 IF(G(2).LT.G(1))GO TO 30
      GPART=G(2)
C     3.LT.2,AND 2.GTE.1
      GO TO 20
      END
*CMZ :  0.92/00 02/12/92  16.02.25  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CAGENE(Z)
      IMPLICIT REAL*8 (A-H,O-Z)
      REAL*8 Z(101)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      CD=COM*1.0D2
      I=IDINT(CD+1.00D0)
      AZ=Z(I)
      IF(I.EQ.1)GOTO150
   10 BZ=Z(I+1)
      IF(101-(I+1))70,20,30
   20 CZ=BZ+5.0D-1*(BZ-AZ)
      GOTO40
   30 CZ=Z(I+2)
   40 XZ=CD-DFLOAT(I-1)
      SCA=CZ-AZ
C F(2)-F(0)
   50 SBA=BZ-AZ
C F(1)-F(0)
      SQA=AZ*AZ
C F(0)**2
      SQAC=SQA-CZ*CZ
C F(0)**2-F(2)**2
      SQBA=BZ*BZ-SQA
C F(1)**2-F(0)**2
      RB=SQAC+SQBA+SQBA
C (ASQ-CSQ)+2(BSQ-ASQ)
CZ
CZ  changed in order to keep exponent small 5/21/92
      RC=AZ*1.0D-20*CZ*SCA-SBA*1.0D-20*(2.0D0*AZ*BZ+XZ*(BZ-CZ)*SCA)
CZ   RC is 1E-20 smaller than it supposed to be !!!!
      RA=SCA-SBA-SBA
C (C-A)-2(B-A)
      IF(RA.NE.0.0)GOTO60
      COM=AZ+XZ*SBA
      GOTO80
   60 CONTINUE
CZ                               \/  factor 1E-20 in RC !!
      DISC=RB*1.0D-20*RB-4.0D0*RA*RC
      IF(DISC)70,90,90
C B**2-4AC
   70 CALL CERROR('CAGENE1$')
   80 RETURN
CZ                      \/ correct for factor 1E-20
   90 DISC=DSQRT(DISC)*1.0D10
CZ   end of change
CZ
      PLUS=(DISC-RB)/(RA+RA)
      AMINUS=(-RB-DISC)/(RA+RA)
      IF(I.EQ.1)GOTO160
  100 IF(PLUS.GT.BZ)GOTO120
      IF(PLUS.LT.AZ)GOTO120
      IF(AMINUS.GT.BZ)GOTO110
      IF(AMINUS.GE.AZ)GOTO140
  110 COM=PLUS
      GOTO80
  120 IF(AMINUS.GT.BZ)GOTO70
      IF(AMINUS.LT.AZ)GOTO70
  130 COM=AMINUS
      GOTO80
  140 RA=XZ*SBA+AZ
      RB=DABS(RA-AMINUS)
      RC=DABS(RA-PLUS)
      IF(RB.GT.RC)GOTO110
      GOTO130
  150 CZ=Z(I+1)
      SCA=CZ-AZ
      BZ=AZ+SCA*7.071067812D-1
      XZ=CD+CD
      GOTO50
C (CZ-AZ)(CZ-AZ)=C,CZ=MASS FOR R=1,AZ=MASS FOR R=0, C=CONST.FOR PARABOLA
C (M-AZ)(M-AZ)=0.5*C,DETERMINES MASS,BZ,FOR R=1/2
  160 BZ=CZ
      XZ=XZ-CD
      SBA=CZ-AZ
      GOTO100
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALGEO
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL * 8 T1,T2,T3,T4,T5,T6,TEMP,TEMPO
      SAVE
C
      I1=0
      T1=OUT(2)*OUT(2)
C     R1SQ
      T2=OUT(3)*OUT(3)
C     (R1+1)SQ
      T3=OUT(4)*OUT(4)
C     (R1+2)SQ
      T4=2.0*T3
C     2(R1+2)SQ
   10 T5=XI(1)*XI(1)+XI(2)*XI(2)+XI(3)*XI(3)
C     T5=R SQ
      GO TO(20 ,70 ,130,190),MED
   20 T6=T5-T1
      IF(T6)240,240,30
C     MED=1
   30 TEMP=T1
   40 IF((T6/TEMP)-5.0D-6)50 ,50 ,230
   50 DO60 I=1,3
         XI(I)=XI(I)*9.99995D-1
   60 CURR(I+3)=XI(I)
      GOTO10
   70 T6=T5-T1
C     MED=2
      IF(T6)80 ,80 ,120
   80 TEMP=T1
   90 IF(5.0D-6+(T6/TEMP))230,100,100
  100 DO110 I=1,3
         XI(I)=XI(I)*10.00005D-1
  110 CURR(I+3)=XI(I)
      GOTO10
  120 T6=T5-T2
      TEMP=T2
      IF(T6)240,240,40
  130 T6=T5-T2
C     MED=3
      IF(T6)140,140,150
  140 TEMP=T2
      GOTO90
  150 T6=T5-T3
      IF(T6)240,240,160
  160 TEMP=T3
C****DUMMY  IF ST. FOLLOWS TO KEEP ST. 175
      IF (TEMP.NE.T3) GO TO 170
      GOTO40
  170 IF(XI(2))230,180,230
C     MED=4
  180 IF(CURR(5))230,190,230
  190 T6=T5-T3
      IF(T6)200,200,210
  200 TEMP=T3
      GOTO90
  210 T6=T5-T4
      IF(T6)240,240,220
  220 TEMP=T4
      GOTO40
  230 I1=-1
      GOTO290
  240 T4=XI(1)*DCOS(1)+XI(2)*DCOS(2)+XI(3)*DCOS(3)
C     T4=-B=-RCOS(THETA)=SUM OF XI(I)*DCOS(I)
      T6=T4*T4
C     T5=R SQ.
      T6=T5-T6
C     T6=R SQ.-B SQ.
      IF(T3-T6)230,250 ,250
  250 T3=DSQRT(T3-T6)
C     T3=A3=SQ.ROOT OF B SQ.-R SQ.+RADIUS3 SQ. SIMILAR
C     FOR T2=A2 ANDT1=A1
      TEMP=T2-T6
      T2=DSQRT(DABS(TEMP))
      TEMPO=T1-T6
      T1=DSQRT(DABS(TEMPO))
      DO260 I=1,6
  260 D(I)=0.0
      GOTO(270,300,360,420),MED
  270 IF(TEMP)230,280,280
  280 D(4)=T1-T4
C     B+A1
      D(5)=T2-T1
C     A2-A1
      D(6)=T3-T2
C     A3-A2
  290 RETURN
  300 IF(TEMP)230,310,310
  310 D(6)=T3-T2
  320 IF(T4)340,330,330
  330 D(3)=T2-T4
C     B+A2
      GOTO290
  340 IF(TEMPO)330,350,350
  350 D(3)=-(T4+T1)
C     B-A1
      D(4)=T1+T1
C     2A1
      D(5)=T2-T1
C     A2-A1
      GOTO290
  360 IF(T4)380,370,370
  370 D(2)=T3-T4
C     B+A3
      GOTO290
  380 IF(TEMP)370,390,390
  390 D(2)=-(T4+T2)
C     B-A2
      D(6)=T3-T2
C     A3-A2
      IF(TEMPO)400,410,410
  400 D(3)=T2+T2
C     2A2
      GOTO290
  410 D(3)=T2-T1
C     A2-A1
      D(5)=D(3)
      D(4)=T1+T1
C     2A1
      GOTO290
  420 D(1)=-(T4+T3)
  430 IF(TEMP)440,450,450
  440 D(2)=T3+T3
      GOTO290
  450 D(2)=T3-T2
      D(6)=D(2)
C     B-A3, A3-A2,REGION 4
      IF(TEMPO)470,460,460
  460 D(3)=T2-T1
C     A2-A1
      D(5)=D(3)
      D(4)=T1+T1
      GOTO290
  470 D(3)=T2+T2
C     2A2
      GOTO290
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALIDK
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      UNIV=PNIDK(6)*PNIDK(6)
C     M(P1) SQUARED  DECAY PION MASS SQUARED
      PNIDK(7)=(PNIDK(1)*PNIDK(1)+UNIV-SQNM)/(2.0*PNIDK(1))
C     E(PI)PRIME  DECAY PION ENERGY PRIME
      PNIDK(8)=DSQRT(PNIDK(7)*PNIDK(7)-UNIV)
C     DECAY PION MOMENTUM PRIME  P(D)
      CALL CAPOL1(PNIDK(20),PNIDK(21))
C     COS THETA, SIN THETA
      CALL CAAZIO(PNIDK(22),PNIDK(23))
C     COS PHI, SIN PHI
      PNIDK(9)=PNIDK(22)*PNIDK(21)*PNIDK(8)
C     DECAY PION X MOMENTUM COMPONENT PRIME
      PNIDK(10)=PNIDK(21)*PNIDK(23)*PNIDK(8)
C     P(P1)PRIME Y
      PNIDK(11)=PNIDK(20)*PNIDK(8)
C     P(P1)PRIME Z
      UNIV=PNIDK(9)*PNIDK(2)+PNIDK(10)*PNIDK(3)+PNIDK(11)*PNIDK(4)
C     P P1 PRIME DOT P
      PNIDK(12)=(PNIDK(7)*PNIDK(5)+UNIV)/PNIDK(1)
C     DECAY PION ENERGY  E(PI)
      PNIDK(13)=PNIDK(5)-PNIDK(12)
      UNIV=(((PNIDK(5)/PNIDK(1))-1.0)*UNIV)/(PNIDK(2)*PNIDK(2)+
     +PNIDK(3)*PNIDK(3)+PNIDK(4)*PNIDK(4))
C     (E/M-1.0)*P(P1)PRIME DOT P/P SQUARED
      UNIVE=PNIDK(7)/PNIDK(1)
C     E PI PRIME OVER MASS
      DO10 I=2,4
         PNIDK(I+12)=PNIDK(I)*(UNIV+UNIVE) +PNIDK(I+7)
   10 PNIDK(I+15)=PNIDK(I)-PNIDK(I+12)
      RETURN
C     PION MOMENTUM COMPONENTS AND NUCLEON MOMENTUM
C     COMPONENTS
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CAISOM
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL * 8 FERMN
      SAVE
C
      CALL CAPOL1(POLC,POLS)
      CALL CAAZIO(SOPC,SOPS)
      M = SNGL(CLSM) + .05
      IF(STRKP+2.0)20,20,10
   10 FERMN=FMPN(M)
C     STRUCK PROTON
      GOTO30
   20 FERMN=FMPN(M+3)
C     STRUCK NEUTRON
   30 CALL FRMICC(P2)
      P2=FERMN*P2
C     FRMIC SELECTS LARGEST OF 3 RANDOM NUMBERS
C     P2=MOMENTUM OF PARTICLE SELECTED FROM PROPER
C     FERMI DISTRIBUTION
      A=P2*POLS
C     P2 SIN THETA
      PXYZ(2)=A*SOPC
C     P2 SIN THETA COS PHI
      PXYZ(6)=A*SOPS
C     P2 SIN PHI
      PXYZ(10)=P2*POLC
C     P2 COS THETA
      E(2)=DSQRT(P2*P2+SQNM)
C     SQ. RT. MOMENTUM STRUCK PART. SQD. +NUCLEON MASS SQD.
      RLKE=(((E(1)*E(2)-PXYZ(1)*PXYZ(2)-PXYZ(5)*PXYZ(6)-PXYZ(9)*
     1PXYZ(10))/DNCMS   )-PM(1))/RCPMV
C     RELATIVE K.E.(MEV)--CONSTANT=NUCLEON MASS         /CM,
C     SECOND=MEV/CM.
      RETURN
      END
*CMZ :  0.90/00 29/07/92  11.28.17  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALMUD(SINE,INP)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      REAL * 8 SINE
C
      SINE= RANDC2(ISEED)
      SINE = 5.0 D1 * SINE
      INP = IDINT(SINE + 0.1D1)
      SINE=DFLOAT(INP)-SINE
C     SINE=(.02N-R)/.02=N-R/.02   N=INPT   R/.02=(N-1)+X
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALNNN
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      FMAX(1) = 0.46 D-24
      FMAX(2) = 1.4 D-24
      DO10 I=3,6
   10 FMAX(I)=0.0
      RETURN
      END
*CMZ :  0.90/00 19/05/92  17.08.07  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE P1CLC
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      P1OE1=DSQRT(E(1)*E(1)-PM(1)*PM(1))
      PXYZ(1)=P1OE1*CURR(7)
      PXYZ(5)=P1OE1*CURR(8)
      PXYZ(9)=P1OE1*CURR(9)
      P1OE1=P1OE1/E(1)
      RETURN
      END
*CMZ :  0.90/00 06/06/92  14.08.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE P1CLI
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      PXYZ(1)=0.0
      PXYZ(5)=0.0
      PXYZ(9)=DSQRT(E(1)*E(1)-PM(1)*PM(1))
      P1OE1=PXYZ(9)/E(1)
      RETURN
C     MOMENTUM X AND Y COORDINATES,PARTICLE 1 =0.0
C     Z COORD. =TOTAL ENERGY SQUARED-MASS SQ. TO THE 1/2
C     FOR PARTICLE ONE.  P1OE1=CURRENT(MOMENT/TOTAL)
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE PARTIN
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      SAVE
      IF(D(4))10 ,20 ,10
   10 IPEC(10)=IPEC(10)+1
C     NO. OF INC. PARTICLES ON REG.1 ONLY
      GOTO50
   20 IF(D(3))30 ,40 ,30
   30 IPEC(6)=IPEC(6)+1
C     NO. OF INC. PARTICLES ON REG.2 ONLY
      GOTO50
   40 IPEC(1)=IPEC(1)+1
C     NO. OF INC. PARTICLES ON REG.3 ONLY
   50 DO60 I=1,3
   60 ISW(I)=0
C     1=0 WHEN START IN RG.3 OR RG.4
C     2=0 WHEN IN RG.3 NOT PASSING THROUGH RG.1
C     3=0 WHEN IN RG.2 NOT PASSING THROUGH RG.1
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE PFMAX
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL * 8 WK
      SAVE
C
      I=I2
      IF(CURR(1)-2.0)20,10,10
   10 I=I+3
   20 WK=WKRPN(I)
      IF(WK-160.0)30,30,50
   30 FMAX(1)=0.176D-24
      FMAX(2)=0.52D-24
      FMAX(3)=0.0
      FMAX(4)=0.0
   40 RETURN
   50 CALL CBOVER(WK,DNCMS,UNIV)
      IF(WK-400.0)60,110,110
   60 IF(WK-300.0)70,100,100
   70 IF(WK-200.0)80,90,90
   80 FMAX(3)=1.95D-27*UNIV
C     3 AND 4 AT 465 MEV
      FMAX(4)=1.7D-27*UNIV
      FMAX(1)=0.103D-24
      FMAX(2)=0.313D-24
      GOTO40
   90 FMAX(1)=0.09D-24
C     1 AND 2 AT 35 MEV
      FMAX(2)=0.26D-24
      FMAX(3)=11.4D-27*UNIV
C     3 AND 4 AT 630 MEV
      FMAX(4)=11.2D-27*UNIV
      GOTO40
  100 FMAX(1)=28.0D-27*UNIV
C     1 AND 2 AT 100 MEV
      FMAX(2)=0.073D-24
      FMAX(3)=20.0D-27*UNIV
C     3 AND 4 AT 780 MEV
      FMAX(4)=14.0D-27*UNIV
      GOTO40
  110 FMAX(1)=27.2D-27*UNIV
C     1 AND 2 AT 155 MEV
      FMAX(2)=48.0D-27*UNIV
      FMAX(3)=22.6D-27*UNIV
C     3 AND 4 AT 1020 MEV
      FMAX(4)=14.0D-27*UNIV
      GOTO40
C     FMAX(1)=(P-P)S---(2)=(P-N)S---(3)=(P-P)S.P.---(4)=(P-N)S.P.
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE PINST
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      I1=0
      MED=CLSM
      IF(INC)10,140,10
   10 INC=0
      IF(MED-1)20,50,40
   20 I1=1
   30 RETURN
   40 IF(MED-3)60,90,20
   50 IPEC(12)=IPEC(12)+1
C     INCIDENT PARTICLE ON REG.1 COLLISION IN REG.1
      GOTO30
   60 IF(D(4))80,70,80
   70 IPEC(8)=IPEC(8)+1
      GOTO30
C     INC. PARTICLE ON REG.2 COLLISION IN REG.2
   80 IPEC(9)=IPEC(9)+1
C     INC. PARTICLE ON REG.1 COLLISION IN REG.2
      GOTO30
   90 IF(D(3))100,120,100
  100 IF(D(4))110,130,110
  110 IPEC(5)=IPEC(5)+1
C     INC. PARTICLE ON REG.1 COLLISION IN REG.3
      GOTO30
  120 IPEC(3)=IPEC(3)+1
C     INC. PARTICLE ON REG.3 COLLISION IN REG.3
      GOTO30
  130 IPEC(4)=IPEC(4)+1
C     INC. PARTICLE ON REG.2 COLLISION IN REG.3
      GOTO30
  140 K=CURR(11)
      K=3*(MED-1)+K
      CC(K)=CC(K)+1.0
      GOTO30
C     COLLISION REG.1 PARTICLE ORIGIN K
      END
*CMZ :  0.90/00 29/07/92  11.28.53  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CAPOL1(CS,SI)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      REAL*8 CS, SI
C
      CS = RANDC2(ISEED)
      S = 2.0 * RANDC2(ISEED) - 1.0
      IF(S.LT.0) CS = -CS
      SI = DSQRT(1.0-(CS*CS))
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE PSTOR
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      L=(I1*12)-28
      IF(I2)10,60,70
   10 JJ=0
      IF(PM(3)-DNCMS)30,30,20
   20 I1=I1+1
      JJ=1
C     X-Y-Z-COORDINATES OF COLLISION POINT
   30 UNIV=DSQRT(PXYZ(I1)*PXYZ(I1)+PXYZ(I1+4)*PXYZ(I1+4)+PXYZ(I1+8)
     +*PXYZ(I1+8))
      K=I1+8
      DO40 I=I1,K,4
         PT(L)=PXYZ(I)/UNIV
   40 L=L+1
      I1=I1-JJ
   50 PT(L)=CLSM
      PT(L+1)=CURR(11)
      PT(L-6)=C(1)
      PT(L-5)=C(2)
      PT(L-4)=C(3)
      RETURN
   60 K=14
      GOTO90
   70 IF(I2-2)80,110,110
   80 K=17
   90 UNIV=DSQRT(PNIDK(K)*PNIDK(K)+PNIDK(K+1)*PNIDK(K+1)+PNIDK
     +(K+2)*PNIDK(K+2))
      J=K+2
      DO100 I=K,J
         PT(L)=PNIDK(I)/UNIV
  100 L=L+1
      GOTO50
  110 UNIV=DSQRT(PT(L-3)*PT(L-3)+PT(L-2)*PT(L-2)+PT(L-1)*PT(L-1))
      K=L-1
      M=L-3
      DO120 I=M,K
         PT(L)=PT(I)/UNIV
  120 L=L+1
      GOTO50
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CAPUNP
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRN.
       COMMON/CRN/COUNT
       REAL*8 COUNT(10)
C
*KEEP,CMUNPU.
       DIMENSION NIP(12)
       REAL*8 PCC(12),PPNB(5)
       COMMON/CMUNPU/PCC,PPNB,NIP
C
C    CALOR random seed
*KEND.
      REAL*8 AC,ZC,AR,ZE
      SAVE
C
      IF(PGVC(1))10,60,30
   10 I1=-1
   20 RETURN
   30 PGVC(1)=PGVC(1)-11.0
      K=PGVC(1)+2.005
      DO40 I=1,11
         CURR(I)=PGVC(K)
         PGVC(K)=0.0
   40 K=K+1
   50 I1=1
      GOTO20
   60 IF(PLVC(1))10,130,70
   70 UNIV=0.0
      L=PLVC(1)
      K=-10
      DO110 I=1,L
   80    K=K+12
         IF(PLVC(K))10,80,90
   90    IF(PLVC(K)-UNIV)110,100,100
  100    UNIV=PLVC(K)
         M=K
  110 CONTINUE
      PLVC(M)=0.0
      DO120 I=1,11
         M=M+1
         CURR(I)=PLVC(M)
  120 PLVC(M)=0.0
      PLVC(1)=PLVC(1)-1.0
      GOTO50
  130 I1=0
      AC=AMASNO
      IF(NO.GT.2)GOTO140
      ZC=ZEE
      AC=AMASNO+1.0D0
C AC-COMPOUND NUC,ZC=CHG.COMPOUND,AR=MASS CASCADE RESID.NUCLEUS
      IF(NO.EQ.1)GOTO150
      GOTO160
  140 IF(NO.LT.5)GOTO150
      ZC=ZEE-1.0D0
      GOTO160
  150 ZC=ZEE+1.0D0
  160 AR=AC-COUNT(1)-COUNT(2)
      ZE=COUNT(1)+COUNT(3)-COUNT(5)
      IF(AR)170,180,190
  170 COUNT(7)=COUNT(7)+1.0D0
      GOTO210
  180 IF(ZC.EQ.ZE)GOTO20
      COUNT(8)=COUNT(8)+1.0D0
      GOTO210
  190 IF(AR.GE.(ZC-ZE))GOTO200
      COUNT(9)=COUNT(9)+1.0D0
      GOTO210
  200 IF(ZC.GE.ZE)GOTO20
      COUNT(10)=COUNT(10)+1.0D0
  210 IF(BEGRU.EQ.1.0D0)GOTO260
      BEGRU=BEGRU-1.0D0
  220 DO230 I=1,12
         CC(I)=PCC(I)
  230 IPEC(I)=NIP(I)
      DO 240 I = 1,5
  240 PNBC(I)=PPNB(I)
  250 NOR=NOR-1
      COUNT(6)=-1.0D0
      GO TO 20
  260 BEGRU=-1.0D0
      GO TO 220
C 1. PICKS UP LAST 11 ITEMS IN PGVC AND STORES
C THEM IN CURR.  STORES ZERO IN THOSE 11 PGVC CELLS.
C     GROUP IS GREATER THAN 1ST IN ALL OTHER GROUPS.  STORES
C     2-12TH ITEMS IN CURR--ZEROES ITEMS 1-12 IN PLVC GROUP.
      END
*CMZ :  1.05/03 27/06/2001  17.24.29  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   20/05/92
      DOUBLE PRECISION FUNCTION RANDC2(DUMMY)
C
      integer DUMMY
      DIMENSION RND1(1)
C
      CALL GRNDM(RND1,1)
      RANDC2 = RND1(1)
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT10
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      I3=0
      IF(EX-D(4))40 ,40 ,10
   10 CALL SPAC32(31)
      GO TO 20
   20 I3=-1
   30 RETURN
   40 CURR(2)=OUT(15)
      WKRPN(1)=OUT(15)
      WKRPN(4)=OUT(18)
C     K.E. FOR PROTONS AND NEUTRONS REGION 1
      GO TO 30
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT11(T)
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      REAL *8 T(6426)
      GO TO (10 ,30 ,40 ,20  ),I3
   10 PT(2)=3.0
   20 IK=IT
      PT(14)=1.0
   30 PM(3)=PNMS
   40 IF(340.0-RLKE)50 ,70 ,70
   50 I3=1
   60 RETURN
   70 CALL CALMUD(SNT,INPT)
      IF(IK-3)100,80 ,90
   80 I3=2
      GO TO 60
   90 I3=3
      GO TO 60
  100 CALL CRDET(51,T(1),RLKE)
      I3=4
      GOTO60
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT12
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRUN.
       COMMON/CRUN/KE
C
*KEND.
C
      I3=0
      CALL CAAZIO(SOPC,SOPS)
      CALL CACOLL(0)
      IF(COL(15))10 ,30 ,10
   10 I3=-1
   20 RETURN
   30 IF(KE)10 ,50 ,40
   40 COM = (E(4)-DNCMS)/RCPMV
      GO TO 60
   50 CALL COLE4
   60 I1= -1
      VALUE1=COM
      IF(PT(14)-2.0)70 ,20 ,20
   70 I3=1
      GOTO20
      END
*CMZ :  0.92/03 10/12/92  10.53.45  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT13
      SAVE
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      I3=0
      IF(IV)10 ,50 ,50
   10 IF(XABS)20 ,50 ,20
   20 IF(IFCA-2)30 ,70 ,60
   30 IN=0
   40 I3=1
      GOTO90
   50 CALL SIGNEX
      IF(IFC-12)120,120,130
   60 IF(IFCA-6)70 ,30 ,100
   70 IN=0
   80 I3=-1
   90 RETURN
  100 IF(IFCA-8)30 ,110,110
  110 IN=1
      GOTO40
  120 IN=0
      GOTO90
  130 IF(IFC-18)140,140,150
  140 IN=-1
      GOTO90
  150 IN=1
      GOTO90
      END
*CMZ :  0.92/03 10/12/92  10.54.08  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT14
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRUN.
       COMMON/CRUN/KE
C
*KEND.
C
      IF(I3)310,270,10
   10 IF(I1)20 ,80 ,80
   20 I1=0
      VALUE1=(E(3)-PM(3))/RCPMV
      IF(XABS)30 ,40 ,30
   30 VALUE1=VALUE1+ABSEC
   40 IF(PT(2)-2.0)70 ,50 ,80
C     PT(2)=1=PROTON   PT(2)=2=NEUTRON   PT(2)=3,4,5=PION
   50 I3=2
   60 GO TO 320
   70 I3=1
      GOTO60
   80 CALL PINST
      IF(I1)90 ,100,90
   90 I3=3
      GOTO60
  100 I1=0
      M=PT(2)
      VALUE2=VALUE1
      IF(M-3)110,150,150
  110 IF(ECO(M)-VALUE2)140,120,130
  120 IF(ECO(M))90 ,90 ,130
  130 PT(I1+3)=0.0
      PNBC(M)=PNBC(M)+1.0
      GOTO230
  140 PT(I1+3)=VALUE2
      IF(I1)300,240,300
  150 CCOFE=CLCFE
      IF(M-4)160,170,170
  160 IF(STRKP+2.0)200,190,200
  170 IF(STRKP+2.0)200,200,180
  180 CCOFE=CLCFE-CTOFE+CTOFEN
      GOTO200
  190 CCOFE=CLCFE+CTOFE-CTOFEN
  200 IF(VALUE2-CCOFE)130,130,210
  210 IF(STRKP+2.0)220,220,140
  220 PT(3)=VALUE1-SPACE(MED+3)+SPACE(MED+9)
  230 IF(I1)260,240,260
  240 M=PT(14)
      IF(M-3)250,90 ,90
  250 VALUE2=COM
      I1=12
      GOTO110
  260 IF(PT(3))300,270,300
  270 CALL CAPUNP
      IF(I1)90 ,280 ,290
C     -, =ERROR  0=END OF RECORD  +=PISCC(6607)
  280 I3=4
      GOTO60
  290 I3=5
      GOTO60
  300 CALL COLLM(-1)
  310 IF(KE.GT.0)GO TO 320
      CALL CASTPR
      IF(I1)90 ,270,90
  320 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT15(T)
      SAVE
      REAL*8 T(6426)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      GOTO(10 ,80 ,20 ,100),I3
   10 IF(RLKE.LE.2.5D3) GO TO 40
   20 I3=4
   30 GO TO 160
   40 IF(IK-3)70 ,50 ,60
   50 I3=1
      GOTO30
   60 I3=2
      GOTO30
   70 CALL CALMUD(SNT,INPT)
      CALL CRDET(51,T(1),RLKE)
      I2 = 0
      CST = CRDT(2) - DABS(SNT*(CRDT(2) - CRDT(1)))
   80 IF(I2)90 ,90 ,20
   90 I3=3
      GOTO30
  100 VALUE1 = RANDC2(ISEED)
      IF(VALUE1-CRDT(1))150,110,110
  110 VALUE2=1.0
C     SCATT. FORWARD
      VALUE1= RANDC2(ISEED)
      IF(VALUE1-CRDT(4))120,140,140
  120 VALUE1 = RANDC2(ISEED)
C     TO SAMPLE FROM UNIFORM DIST.
  130 CST=VALUE1*VALUE2
      GOTO90
  140 COM=0.0
      CALL CABIG7(COM,VALUE1,I1)
      GOTO130
  150 VALUE2=-1.0
      VALUE1 = RANDC2(ISEED)
      I1=I1+I2
      IF(VALUE1-CRDT(2))120,140,140
  160 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT16(T)
      REAL*8 T(6426)
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      CALL CALMUD(SNT,INPT)
      CALL CRDET(51,T(1),RLKE)
      I2 = 0
      CST = CRDT(2) - DABS(SNT*(CRDT(2) - CRDT(1)))
      GO TO (10 ,30 ,40 ), I3
   10 I3=-1
   20 RETURN
   30 I3=0
      GOTO20
   40 I3=1
      GOTO20
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT17(T,B,R,W,G)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      REAL*8 T(117),B(101),R(117),W(234),G(234)
      SAVE
C
      IF(I3)10  ,10  ,150
   10 PT(38)=0.0
C     1-ALPHA  PART.6+1
      VALUE1=RLKE-180.0
      CALL CRDET(1,T(1),VALUE1)
      COM2=CRDT(1)
      FTR=DNCMS*RLKE*2.0*RCPMV+2.9877156D27
C     E**2=MIN**2+NCNMS*RLKE*2*RCPMV
      UNIVER=DSQRT(FTR)
C     E
   20 VALUE2 = RANDC2(ISEED)
      COM=VALUE2*COM2
C     R-PRIME
      CALL CAGENE(B(1))
      COM1=(COM*COM+FTR-.501264D26)/(2.0*UNIVER)
C     M1R PRIME)**2+E**2-2(PNMS)/2E=E ALPHA
      A=COM1*COM1-COM*COM
      IF(A)30  ,40  ,40
   30 PACNT=PACNT+1.0
      GO TO 20
   40 UNIVE=((UNIVER-COM1)*COM1/UNIVER)*DSQRT(A)
C     ((E BETA*E ALPHA*P ALPHA)/E)=F(M,TR)
      CALL CRDET(1,R(1),VALUE1)
C     (PI-NUC)FMAX(RLKE)ISOBAR SAMPLING S.P.
      COM1 = RANDC2(ISEED)
      IF((UNIVE/CRDT(1))-COM1)20  ,50  ,50
C     RANDOM NO. LESS OR EQUAL THAN F(M,TR)/FMAX(TR)
   50 CALL CANGID
      PM(3)=COM
      PM(4)=POMS
      PT(2)=3.0
      PT(4)=POMS
      PT(14)=3.0
      PT(16)=POMS
      PT(26)=1.0
      PT(28)=DNCMS
      IF(ISW(9))70  ,60  ,70
   60 IF(ISW(10))110 ,100 ,110
   70 IF(ISW(10))120 ,80 ,120
   80 I3=-1
   90 RETURN
  100 VALUE1=.4
      VALUE2=6.6666667D-1
      VALUE3=0.0
      GO TO 140
  110 CALL CRDET(2,W(1),VALUE1)
C     (PICH-P)FRACT. FIN.STA.WITH RECL. PI1 PI0 L.E.
      VALUE3=3.3333333D-1
      GO TO 130
  120 CALL CRDET(2,G(1),VALUE1)
      VALUE3=STRKP
C     (PIN-P)FRACT.FIN.STA.WITH RECL.PI1 PIO L.E.
  130 VALUE1=CRDT(1)
      VALUE2=CRDT(2)
  140 CALL CALPHA
  150 CALL CAECPL
      IF(I1)160 ,160 ,80
  160 CALL CACOLL(-1)
      IF(COL(15))80 ,170 ,80
  170 IF(PT(38))180 ,190 ,180
  180 I3=0
      GO TO 90
  190 PT(39)=0.0
      PT(3)=((E(4)-PM(4))/RCPMV)+PT(3)
      I3=1
      GO TO 90
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT18
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      GOTO(10  ,20  ,80  ,210 ,170 ,190 ),I3
   10 I=3
      COL(15)=1.0
      K=27
      GO TO 30
   20 I=3
      COL(15)=4.0
      K=15
   30 PNIDK(1)=PM(I)
      J=I
      DO40  L=2,4
         PNIDK(L)=PXYZ(J)
   40 J=J+4
      PNIDK(5)=E(I)
      PNIDK(6)=PT(K-11)
      CALL CALIDK
      IF(K-27)60  ,50  ,60
   50 PT(15)=PT(15)+((PNIDK(12)-PNIDK( 6))/RCPMV)
   60 PT(K)=PT(K)+((PNIDK(13)-DNCMS)/RCPMV)
      I3=1
   70 IV=K
      RETURN
   80 K=3
      COL(15)=2.0
      IF(PT(2)-3.0)170 ,90  ,90
   90 IF(PT(K)-2500.0)110 ,110 ,100
  100 I3=5
      GOTO70
  110 IF(PT(K))150 ,150 ,120
  120 CCOFE = ECO(1)
      IF(PT(K-1)-4.0) 140 ,130 ,130
  130 CCOFE = CCOFE - CTOFE + CTOFEN
  140 IF(PT(K) - CCOFE ) 150 ,150 ,160
  150 M=PT(K-1)
      PNBC(M)=PNBC(M)+1.0
      PT(K)=0.0
      I3=3
      GOTO70
  160 IF(K-3)170 ,170 ,210
  170 COL(15)=3.0
      K=15
      IF(PT(14)-2.0)180,180,90
  180 I3=2
      GOTO70
  190 L=14
      DO200 M=5,7
         PT(M)=PNIDK(L)
         PT(M+12)=PNIDK(L+3)
  200 L=L+1
      PT(11)=PNIDK(12)
      PT(12)=PNIDK(6)
      I=4
      K=39
      COL(15)=5.0
      GO TO 30
  210 I1=3
  220 K=12*I1-33
      IF(I1-4)230 ,240 ,250
  230 I2=-1
      GO TO 280
  240 I2=0
      GO TO 280
  250 IF(I1-5)240 ,270 ,260
  260 I3=4
      GO TO 70
  270 I2=1
  280 IF(PT(K))290 ,300 ,290
  290 CALL PSTOR
  300 I1=I1+1
      GO TO 220
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT19
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      PT(3)=PT(3)+((PT(11)-PT(12))/RCPMV)
C     COLLISION ALLOWED
      K=3
   10 IF(PT(K)-2500.0)30  ,30  ,20
   20 I3=1
      GO TO 90
   30 IF(PT(K))70  ,70  ,40
   40 CCOFE = ECO(1)
      IF(PT(K-1)-4.0) 60  ,50  ,50
   50 CCOFE = CCOFE - CTOFE + CTOFEN
   60 IF(PT(K) - CCOFE) 70  ,70  ,170
   70 PT(K)=0.0
      IF(PT(K-1)-3.0)80 ,110 ,100
   80 I3=-1
   90 RETURN
  100 IF(PT(K-1)-5.0)110 ,110 ,80
  110 M=PT(K-1)
      PNBC(M)=PNBC(M)+1.0
      GOTO140
  120 I2=2
  130 I1=(K/12)+3
      CALL PSTOR
  140 IF(K-15)150 ,160 ,190
  150 K=15
      IF(PT(15))160 ,160 ,120
  160 K=27
      PT(27)=PT(27)+((PNIDK(12)-PT(K+1))/RCPMV)
      GOTO10
  170 IF(K-15)120 ,180 ,180
  180 I2=0
      GOTO130
  190 IF(K-27)80 ,200 ,210
  200 IF(PT(39))210 ,210 ,220
  210 I3=0
      GOTO90
  220 I2=1
      K=39
      GOTO130
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT20(T,B,R,W,G)
      REAL*8 T(115),B(80),R(239),W(60),G(55)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      GO TO (10  ,50  ,70  ,80  ,190 ,200 ,290 ,60  ),I3
   10 PM(4)=DNCMS
      CALL PINST
      IF(I1)20 ,40 ,20
   20 I3=1
   30 RETURN
   40 I3=2
      GOTO30
   50 ISW(9)=0
   60 ISW(10)=2
      I3=3
      GOTO30
C     PI MESON - SINGLE PRODUCTION
   70 PT(2)=2.0
      I3=4
      GOTO30
C     COLLISION PARTICLE PI-
   80 PT(2)=2.0
      PT(14)=1.0
   90 PM(3)=DNCMS
      IF(740.0-RLKE)140 ,100 ,100
  100 IF(300.0-RLKE)110 ,130 ,130
  110 VALUE1=RLKE-300.0
      CALL CRDET(5,T(1),VALUE1)
C     (N-P)DIFF.CRS.INT.EN.
      I1=3
      I2=3
  120 I3=5
      GOTO30
  130 CALL CRDET(5,B(1),RLKE)
C     (N-P)DIFF.CRS.LOW EN.
      I1=3
      I2=1
      GOTO120
  140 IF(3500.0-RLKE)20 ,150 ,150
  150 IF(IT-17)160 ,20 ,20
  160 CALL DCINTP(R(1))
C     (N-P)DIFF.CRS.HIGH EN.
  170 IF(I1)20 ,180,180
  180 I3=6
      GOTO30
  190 PT(2)=1.0
      PT(14)=2.0
      GOTO90
  200 PT(2)=2.0
      PT(14)=2.0
  210 PM(3)=DNCMS
      IF(500.0-RLKE)230 ,220,220
  220 I3=7
      GOTO30
  230 IF(1000.0-RLKE)270 ,240 ,240
  240 CALL CADCPR(W(1),12)
      IF(I2.EQ.1) GO TO 20
C    SAMPLE + MU IN CST
  250 SNT=DSQRT(1.0-CST*CST)
C     P-P SCATTERING
  260 I3=8
      GOTO30
C     -, SCATTERING BACKWARD, MU LESS THAN 0
  270 IF(3500.0-RLKE)20 ,280 ,280
  280 CALL CADCPR(G(1),11)
      IF(I2.EQ.1) GO TO 20
C     (P-P)DIFF.CRS.SEC.HIGH EN.
      GOTO170
  290 PT(2)=1.0
      PT(14)=1.0
      GOTO210
C     NO PION PRODUCTION POSSIBLE
      END
*CMZ :  0.92/00 02/12/92  16.02.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT21(V,W,X,Y,Z)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      REAL*8 V(161),W(101),X(161),Y(130),Z(176)
      SAVE
C
      VALUE2=RLKE*4.81633308D24+9.0554256D27
C     E(TR)**2=RLKE*RCPMV*2*NCMS+4*NCMS**2
      VALUE3=DSQRT(VALUE2)
      GO TO (10  ,100 ,110 ,240 ),I3
   10 ISW(12)=0
   20 PT(38)=0.0
      I1=0
      ANS=RLKE
   30 VALUE1=ANS-300.0
      CALL CRDET(1,V(1),VALUE1)
C     (NUC-NUC) F(TR) ISOBAR SAMPLING
      FTR=CRDT(1)
   40 SN = RANDC2(ISEED)
      COM=SN*FTR
C     R PRIME=F(TR)*RANDOM
      CALL CAGENE(W(1))
C     (NUC-NUC)MASS OF ISOBAR S.P.    M(R PRIME)
      IF(I1)130 ,50  ,140
   50 COM1=(COM*COM-SQNM+VALUE2)/(2.0*VALUE3)
C     E GAMMA
      A=COM1*COM1-COM*COM
      IF(A)60  ,70  ,70
   60 PGCNT=PGCNT+1.0
      GOTO40
C
CZ changed in order to keep exponent small 5/21/92
   70 UNIVER=DSQRT(A)*COM1*(1.0D0-COM1/VALUE3)
CZ end of change
CZ
C     F(M,TR)=P GAMMA*E GAMMA*E DELTA/E
      CALL CRDET(1,X(1),VALUE1)
C     (NUC-NUC)FMAX(TR) ISOBAR SAMPLING S.P.
      COM1 = RANDC2(ISEED)
      IF(COM1-(UNIVER/CRDT(1)))80  ,80  ,40
   80 PM(4)=DNCMS
      PM(3)=COM
      CALL CANGID
      PT(4)=DNCMS
      PT(28)=DNCMS
      CALL CALP19
   90 RETURN
  100 ISW(12)=2
      GOTO20
  110 ISW(13)=0
  120 I1=-1
      ANS=((VALUE3-PNMS)**2-9.0554256D27)/4.81633308D24
      GO TO 30
C     TR PRIME     COM1=RLKE PRIME
  130 COM1=((VALUE3+DNCMS-COM)**2-9.0554256D27)/4.81633308D24
      COM2=COM
      ANS=COM1
      COM4=FTR
      I1=1
      GO TO 30
  140 COM1=(COM2*COM2-COM*COM+VALUE2)/(2.0*VALUE3)
C     E EPSILON
      A=COM1*COM1-COM2*COM2
      IF(A)150 ,160 ,160
  150 PECNT=PECNT+1.0
      GOTO170
C     F(M1,M2,TR)=P EPSILON*E EPSILON*E ZETA/E
C
CZ changed in order to keep exponent small 5/21/92
  160 UNIVER=DSQRT(A)*COM1*(1.0D0-COM1/VALUE3)
CZ end of change
CZ
      VALUE1=RLKE-920.0
      CALL CRDET(1,Y(1),VALUE1)
C     (NUC-NUC)FMAX(TR) ISOBAR SAMPLING D.P.  FMAX(M1,M2,TR)
      SN = RANDC2(ISEED)
      IF(SN-(UNIVER*FTR/(CRDT(1)*COM4)))180 ,180 ,170
  170 FTR=COM4
      I1=-1
      GOTO40
  180 VALUE1 = RANDC2(ISEED)
      IF(VALUE1-.5)190 ,190 ,200
  190 PM(3)=COM2
      PM(4)=COM
      GOTO210
  200 PM(3)=COM
      PM(4)=COM2
  210 CALL CANGID
      PT(16)=DNCMS
      PT(40)=DNCMS
      IF(ISW(13))220 ,230 ,220
  220 CALL CRDET(1,Z(1),RLKE)
      VALUE1=CRDT(1)
C     (N-P)FRACT.FIN.STA.3/2 L.E.
  230 PT(2)=3.0
      PT(4)=POMS
      PT(14)=1.0
      PT(26)=3.0
      PT(28)=POMS
      PT(38)=1.0
      CALL CALP28
      GO TO 90
  240 ISW(13)=2
      GO TO 120
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT22(V,W,X,Y,Z)
      REAL*8 V(19),W(19),X(126),Y(126),Z(126)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      I5=CURR(1)
      GOTO(270 ,1070,340 ,350 ,370 ,1040,520 ,1110,1170,460 ,1270,440 ,4
     +00  ,500 ,1440,10  ,700 ,590 ,260 ,530 ,430 ,1220,1570),IV
   10 DO20  I=1,3
         XI(I)=CURR(I+3)
   20 DCOS(I)=CURR(I+6)
      IN=-1
      MED=CURR(10)
      I5=CURR(1)
      CALL CALGEO
      IF(I1)60  ,30  ,30
   30 IF(CURR(1)-2.0)70  ,680 ,40
   40 IF(CURR(1)-4.0)690 ,700 ,50
   50 IV=1
   60 RETURN
   70 ISW(4)=1
C     PROTON
   80 XABS=0.0
      I4=1
      I2=MED
      IF(I2-1)110,90  ,210
   90 I4=6
      GOTO210
  100 ISW(6)=1
      ISW(5)=1
      I3=0
      IF(COM-3600.0)120 ,120 ,110
  110 IV=2
      GOTO60
C     COM=GREATEST ENERGY INSIDE NUCLEUS FOR NUCLEONS ONLY
  120 IF(COM-560.0)130 ,130 ,140
  130 IF(COM-160.0)200 ,200 ,190
  140 CALL DFMAX
C     DFMAX FILLS OUT FMAX(1-6)
      I1=6
  150 IF(CURR(1)-2.0)170 ,160 ,160
  160 I3=1
  170 CALL CSTORE
      EX=0.0
      CALL SIGNEX
      GOTO(260 ,370 ,430 ,480 ,400 ,580 ,920 ,1040,1170,180,1440),I4
  180 IV=3
      GOTO60
  190 ISW(6)=0
      CALL PFMAX
C     PFMAX FILLS OUT FMAX(1-4)
      I1=4
      GOTO150
  200 ISW(5)=0
      ISW(6)=0
      CALL CALNNN
C     NN FILLS OUT FMAX(1-2),FMAX(3-6)=0
      I1=2
      GOTO150
  210 ISW(1)=0
      ISW(2)=0
      ISW(3)=0
  220 M=MED+ INT(15.0-6.0*SNGL(CURR(1)))
      A=CURR(2)-SPACE(M)
  230 DO240 I=1,3
         WKRPN(I)=A+SPACE(I+9)
  240 WKRPN(I+3)=A+SPACE(I+3)
  250 M=4-3*ISW(4)
      COM=WKRPN(M)
      GOTO100
  260 GOTO(1290,1290,270 ),I2
  270 IF(EX-D(2))310 ,310 ,280
C     ENTRY POINT FOR CASCADE CHARGED AND NEUTRAL PIONS AFTER CRJAB
C     REJECTION,PROD.REACTION LT 180 FERMI REJECTION FOR NON-ABSORPTION
C     REACTION ALSO ALL CASCADE NUCLEAR2 REJECTIONS INCLUDING CRJAB OR
C     RLKE LT PROD.THRESHOLD
  280 IF(D(3))560 ,290 ,560
  290 CALL CCPES
      IF(I1)300,300,110
C     GO TO CAPUNP
  300 IV=4
      GOTO60
  310 IF(IN) 320 ,320  ,1460
  320 CALL CBG6CA(3,0)
      IFCC=12
  330 MED=CLSM
      IV=5
      GOTO60
  340 VALUE1=EX
      IV=6
      GOTO60
  350 VALUE1=EX+D(3)
  360 IV=7
      GOTO60
C     E.P.FOR REJECTION FOLLOWING CRJAB OR RLKE LT 180 IN PROD.REACTIONS
C     AND FOR FERMI REJECTION IN SCATTERING AND PRODUCTION REACTIONS
C     FOR CASCADE CHARGED AND NEUTRAL PIONS
  370 IF(EX-D(6))310 ,310 ,290
  380 ISW(1)=1
  390 GOTO(400 ,400 ,400 ,1040),I5
C     E.P.FOR ALL REJECTIONS,CRJAB,PRODUCTION,AND FERMI FOR CASCADE
C     NUCLEONS
  400 IF(EX-D(3))510 ,510 ,410
  410 I2=3
      I4=2
      I3=1
      I1=2
      IF(D(4))420 ,250 ,420
  420 ISW(2)=1
      ISW(3)=1
      I4=3
      I2=1
      GOTO250
  430 GOTO(440 ,440 ,440 ,1170),I5
  440 IF(EX-D(4))450 ,450 ,470
  450 CALL CBG6CA(1,0)
      IFCC=7
      GOTO330
  460 VALUE1=EX
      IV=8
      GOTO60
  470 I4=4
      I1=2
      I2=2
      I3=1
      GOTO250
C     E.P.FOR CASCADE NUCLEONS AND PI0,AFTER CRJAB AND PROD.THRESHOLD
C     REJECTIONS
  480 IF(I5-2)500 ,500 ,490
  490 IF(I5-4)110,1440,110
C     E.P.FOR CASCADE NUCLEONS AFTER ALL FERMI REJECTIONS
  500 IF(EX-D(5))510 ,510 ,540
  510 CALL CBG6CA(2,0)
      IFCC=10
      GOTO330
  520 VALUE1=EX
      GOTO360
  530 IF(ISW(3))480 ,390 ,480
  540 I4=2
      I2=3
  550 I3=1
      I1=2
      GOTO250
  560 ISW(1)=1
      IF(CURR(1)-3.0)570 ,940 ,1390
  570 I4=5
      I2=2
      GOTO550
C     D.P.
  580 ISW(1)=1
      ISW(2)=1
      ISW(3)=1
      GOTO260
  590 ANY=FMAX(NOT)
      IF(NOT-5)620 ,600 ,610
  600 IV=9
      GOTO60
  610 IF(I5-4)600 ,630 ,600
  620 IF(KNOT-15)630 ,1560,1560
  630 GOTO(640 ,640 ,640 ,1510),I5
  640 IF(NOT-2)650 ,660 ,670
  650 IV=10
      GOTO60
  660 IV=11
      GOTO60
  670 IV=12
      GOTO60
  680 ISW(4)=0
C     NEUTRON
      GOTO80
  690 ISW(11)=1
C     CURR(1)=3=PI+ MESON(11575)--PI 0=4(15100)--PI -(14646)
  700 IN=1
      ISW(1)=0
      ISW(2)=0
      ISW(3)=0
      ISW(5)=1
      ISW(6)=0
      ISW(7)=0
      ISW(8)=1
      I6=I5-2
      I2=MED
      COM=CURR(2)-SPACE(MED+9)
      GOTO(720 ,710 ,730 ),MED
C     E.P.FOR PI0 AFTER FERMI REJECTION
  710 ISW(8)=0
  720 ISW(7)=1
  730 DO740 I=1,3
         WKRPN(I)=COM+SPACE(I+9)
  740 WKRPN(I+3)=COM+SPACE(I+3)
      COM=COM+SPACE(4)
  750 IF(COM-2600.0)760 ,760 ,110
  760 IF(COM-100.0)770 ,770 ,780
  770 LG=4
      GOTO1330
  780 LG=6
  790 CALL CASPCN
      IF(VALUE1)800 ,800 ,830
  800 COM=CURR(2)-SPACE(MED+9)
      IF(COM-360.0)810 ,830 ,830
  810 GOTO(820 ,1350,820 ),I6
  820 CALL CRDET(1,V(1),COM)
      FMAX(4)=CRDT(1)
  830 GOTO(840 ,1360,840 ),I6
  840 I1=6
  850 I4=7
      I2=1
      I3=0
      GOTO(860 ,870 ,860 ),I6
  860 IF(ISW(11))870 ,910 ,870
C     PI+
  870 IF(ISW(7))880 ,900 ,880
C     PI-
  880 IF(ISW(8))170 ,890 ,170
  890 I2=2
      GOTO170
  900 I2=3
      GOTO170
  910 I3=1
      GOTO870
  920 IF(CURR(1)-2.0)930 ,930 ,260
  930 A=CURR(2)-SPACE(MED+9)
      GOTO230
  940 I4=8
  950 I2=2
  960 I3=0
      I1=LG
      IF(CURR(1)-4.0)970 ,1030,970
  970 IF(ISW(11))990 ,980 ,990
  980 I3=1
  990 IF(CURR(1)-3.0)1000,1010,1010
 1000 IV=23
      GOTO60
 1010 IF(LG-4)1000,170 ,1020
 1020 M=5-IABS(I5-4)
      UNIVER=FMAX(M)
      CALL CASPCN
      FMAX(M)=UNIVER
      GOTO170
 1030 I1=I1+1
      GOTO1010
C     E.P.FOR CHARGED AND NEUTRAL PIONS AFTER CRJAB REJECTION ALSO,AFTER
C     RLKE.LE.180 IN PROD.REACTIONS AND AFTER FERMI REJECTION IN SCATTER
C     ING AND PROD.REACTIONS
 1040 IF(EX-D(3))1050,1050,1140
 1050 GOTO(1060,1410,1060),I6
 1060 IV=13
      GOTO60
 1070 ANY=FMAX(NOT)
      IF(CURR(1)-3.0)1080,1100,1100
 1080 IFC=12
 1090 IV=14
      GOTO60
 1100 IFCC=(CLSM-2.0)*((CLSM*5.5)-8.5)+12.05
      GOTO1090
 1110 IF(I4-10)1120,1210,1120
C     E.P.FOR ESCAPE PRIOR TO CHOOSING REACTIONS--CASCADE CHARGED PION
 1120 IF(CLSM-2.0)1130,1210,1130
 1130 I4=2
      GOTO950
 1140 I4=2
C     E.P.WHEN CASCADE PARTICLE ESCAPES FROM REGION 2
      I2=3
      IF(D(4))1160,1150,1160
 1150 GOTO(960 ,1450,960 ),I6
 1160 ISW(2)=1
      ISW(3)=1
      I4=9
      I2=1
      GOTO1150
C     E.P.AFTER ALL REJECTIONS EXCEPT FERMI IN ABS.REACTIONS FOR
C     CHARGED AND NEUTRAL CC PIONS--ESCAPE FROM REGION 1 PRIOR TO
C     CHOOSING REACTION FOR CC CHARGED PION
 1170 IF(EX-D(4))1180,1180,1200
 1180 GOTO(1190,1480,1190),I6
 1190 IV=15
      GOTO60
 1200 I4=10
      GOTO(950 ,1430,950 ),I6
 1210 I4=2
      I2=3
      GOTO960
 1220 IF(IN)1240,1230,1240
 1230 IV=16
      GOTO60
 1240 IFCA=8*IABS(I6-2)-11*(I6-1)*(I6-3)
      IF(ISW(1))1250,340 ,1250
 1250 IF(ISW(2))1260,350,1260
 1260 IV=17
      GOTO60
 1270 IFCA=10*IABS(I6-2)+12*(I6-1)*(3-I6)
      IF(ISW(3))1280,520,1280
 1280 IV=18
      GOTO60
 1290 IF(CURR(1)-3.0)1300,1310,1310
 1300 GOTO(430 ,380 ),MED
 1310 ISW(1)=1
      GOTO(1320,1040),MED
 1320 ISW(2)=1
      ISW(3)=1
      GOTO1170
 1330 ISW(5)=0
      GOTO(1340,1500,1340),I6
 1340 CALL CBOVER(CURR(2),PNMS,ANS)
      FMAX(1)=.20 D-24*ANS
C     (PI+P)SCATTERING
      FMAX(2) = 23.0D-27*ANS
C     (PIM+P)SCATTERING
      FMAX(3)=45.1D-27*ANS
C     (PIM+P)EXCHANGE
      COM=CURR(2)-SPACE(MED+9)
C     (K.E.OF PIONS OUTSIDE NUCLEUS
      CALL CRDET(1,V(1),COM)
      FMAX(4)=CRDT(1)
C     C(PIP+P)ABS.
      I1=4
      GOTO850
 1350 CALL CRDET(1,W(1),COM)
      FMAX(5)=CRDT(1)
 1360 I1=7
      GOTO850
 1370 CALL CBG6CA(3,4)
      IFCC=24
 1380 KA=7
      MED=CLSM
      IV=19
      GOTO60
 1390 I4=8
 1400 I2=2
      GOTO960
 1410 CALL CBG6CA(2,3)
 1420 IFCC=21
      GOTO1380
 1430 I4=11
      GOTO1400
 1440 IF(EX-D(5))1410,1410,1490
 1450 I1=9-I5
      GOTO960
 1460 GOTO(1470,1370,1470),I6
 1470 IV=20
      GOTO60
 1480 CALL CBG6CA(1,2)
      GOTO1420
 1490 I1=5
      GOTO1210
 1500 CALL CBOVER(CURR(2),POMS,ANS)
      FMAX(1) = 89.2D-27*ANS
C     (PI0+P)ELAST.SCAT.
      FMAX(2)=45.1D-27*ANS
C     (PI0+P)EX.SCAT.
      FMAX(3)=FMAX(1)
      SPACE(48)=FMAX(1)
      FMAX(4)=FMAX(2)
      SPACE(49)=FMAX(2)
      COM=CURR(2)-SPACE(MED+9)
      CALL CRDET(1,W(1),COM)
C     (PIN-P)ABS. CRS.SEC.
      FMAX(5)=CRDT(1)
C     (PI0+P)ABS.
      SPACE(50)=FMAX(5)
      I1=5
      GOTO850
 1510 IF(NOT-2)1530,1550,1520
 1520 IV=21
      GOTO60
 1530 CALL CRJAB(1,X(1))
C     (PIN-P)DIRECT SCAT.CRS.
 1540 IV=22
      GOTO60
 1550 CALL CRJAB(1,Y(1))
C     (PIM-P)XCH.SCAT.CRS.
      GOTO1540
 1560 IF(KNOT-16)1570,1550,1550
 1570 CALL CRJAB(1,Z(1))
C     (PIN-N)DRCT.SCAT.CRS.
      GOTO1540
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT1
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      OUT(11)=ZEE
      VALUE2=ZEE**6.6666667D-1
      DO10 I=5,7
         SPACE(I+2)=OUT(I)*OUT(11)
   10 SPACE(I+5)=(OUT(I+3)*VALUE2)+7.0
C     SCALED PROTONS PER CC AND POTENTIAL PROTON WELL DEPTH
C     (MEV) IN EACH REGION
      OUT(12)=AMASNO-OUT(11)
C     NO. OF NEUTRONS N, STORED
      VALUE2=OUT(12)**6.6666667D-1
C     N 2/3
      DO20 I=5,7
         SPACE(I-4)=OUT(I)*OUT(12)
   20 SPACE(I-1)=(OUT(I+3)*VALUE2)+7.0
C     SCALED NEUTS. PER CC AND POT. NEUT. WELL DEPTH (MEV)
C     IN EACH REGION
      DO30 I=1,3
         HVN(I)=0.5*SPACE(I+3)
         HVP(I)=0.5*SPACE(I+9)
         AWD(I)=HVN(I)+HVP(I)
         FVNP(I)=0.5*AWD(I)
         VNVP(I)=SPACE(I+3)-SPACE(I+9)
         PMAC(I)=VNVP(I)-HVN(I)
         PPAN(I)=-VNVP(I)-HVP(I)
         THPN(I)=HVP(I)-VNVP(I)
         FFPTFN(I)=-VNVP(I)+FVNP(I)
         TFFN(I)=SPACE(I+9)-FVNP(I)
   30 TFFP(I)=VNVP(I)+TFFN(I)
      PPPDA=(2.0*ZEE)/(ZEE+AMASNO-1.0)
      PPMDA=(2.0*OUT(12))/(AMASNO+OUT(12)-1.0)
      PPNDA=(2.0*ZEE*OUT(12))/(AMASNO*AMASNO-AMASNO)
      PPNNA=(OUT(12)*OUT(12)-OUT(12))/(OUT(12)*OUT(12)+ZEE*ZEE-AMASNO)
C     PION ABSORPTION CALC. FOR EACH REG.  1/2 NWD, (-PNAN, -PPAC)
C     1/2 PWD, (-PNAP, -PNAC) AV. WELL DEPTH, 1/4 AV. WELL DEPTH,
C     (N-P)WELL DEPTH, (-VPVN), 1/2NWD -PWD, (PMAP, -VPHN), 1/2PWD -NWD,
C     (-VNHP), 3/2PWD -NWD, 5/4PWD -3/4NWD, 3/4PWD -1/4NWD,
C     3/4NWD -1/4PWD, PROB. PIP DEUT ABS, PROB PIM DEUT ABS
C     PROB PIN DEUT ABS, PROB PIN NN ABS RATHER THAN PP
      K=15
      DO40 I=4,6
         OUT(K)=SPACE(I+6)+EINC
         OUT(K+3)=SPACE(I)+EINC
   40 K=K-1
C     TOTAL K.E. IN MEV INCIDENT PROTON(NEUTRON)PARTICLE IN EACH REGION
      OUT(30)=(ZEE/OUT(4))*1.4412D-13
C     COULOMB POTENTIAL AT SURFACE IN MEV.  CONVERSION
C     FACTOR=MEV-CM PER PROTON    (BG33)
      IF(CTOFE)60,50,60
   50 CTOFE=OUT(30)
C     IF CTOFE=0,THEN EQUATE IT TO1/2 POTENTIAL ENERGY AT SURFACE
   60 DO70 I=1,3
         CFEPN(I+3)=SPACE(I+3)+CTOFEN
   70 CFEPN(I)=SPACE(I+9)+CTOFE
C     BG33P--CUTOFF ENERGIES IN EACH REGION FOR NEUTRONS(PROTONS)
      IN=0
      VALUE1=6.28318531D10*(1.19366207D-1)**3.3333333D-1
C     CALC. OF FERMI MOMENTA PER CM.  PF EQU. 2PI*((3/8PI)TO 1/3)*E10
      DO80 I=1,3
         FMPN(I)=VALUE1* (SPACE(I+6))**3.3333333D-1
   80 FMPN(I+3)=VALUE1* (SPACE(I))**3.3333333D-1
C     FERMI MOMENTA PER CM. OF PROTONS(NEUTRONS)
      DO 90  I = 1,4
   90 RANDS(I)=RANDI(I)
      RETURN
      END
*CMZ :  0.92/05 19/12/92  15.36.43  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT2(T)
      REAL*8 T(19)
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      I1=1
      VALUE2=EINC+SPACE(12)
      CALL CBOVER(VALUE2,PNMS,ANS)
      SPACE(14)=0.20D-24*ANS
C     PIP+P
      SPACE(15)=0.023D-24*ANS
C     (PIM+P)EL
      SPACE(16)=.0451D-24*ANS
C     (PIM+P)EX
C     180
      IF(VALUE1-100.0)10 ,10 ,50
   10 FMAX(1)=SPACE(14)
      FMAX(2)=SPACE(15)
      FMAX(3)=SPACE(16)
      S(1)=0.0
      S(2)=0.0
   20 CALL CRDET(1,T(1),EINC)
C     (PIP-P) ABSORPTION CROSS SECTION
      SPACE(17)=CRDT(1)
      IF(I1)40 ,40 ,30
   30 FMAX(4)=SPACE(17)
   40 RETURN
   50 IF(VALUE2-2600.0)70 ,70 ,60
C     VALUE2 IS GREATER THAN 2600
   60 I1=0
      GOTO40
   70 SPACE(17)=0.0
      IF(VALUE2-220.0)80 ,80 ,90
   80 S(1)=0.75D-27*ANS
C     (PIP-P)S.P. 400MEV
      S(2)=4.7D-27*ANS
C     (PIM-P)S.P. 400MEV
      GOTO110
   90 IF(VALUE2-400.0)100,100,120
  100 SPACE(14)=0.20D-24
      SPACE(16)=.0451D-24
      S(1)=7.8D-27*ANS
      S(2)=21.8D-27*ANS
C     660 MEV
  110 IF(EINC-360.0)20   ,40 ,40
  120 IF(VALUE2-500.0)130,130,140
  130 SPACE(14)=.113D-24
C     250 MEV
      SPACE(15)=20.5D-27*ANS
C     620 MEV
      SPACE(16)=27.7D-27
C     250 MEV
      S(1)=13.8D-27*ANS
      S(2)=24.4D-27*ANS
C     800 MEV
      I1=-1
      GOTO110
  140 S(2)=30.4D-27*ANS
      SPACE(15)=26.3D-27*ANS
C     900
      IF(VALUE2-600.0)150,150,160
C     940,325
  150 SPACE(14)=53.0D-27
C     325
C     VALUE2 LTE 600
C     325
      SPACE(16)=16.2D-27
      S(1)=15.2D-27*ANS
C     940
      GOTO40
  160 IF(VALUE2-800.0)170,170,180
C     1200,400
  170 SPACE(14)=33.0D-27
C     400
      SPACE(16)=12.0D-27*ANS
C     400
      S(1)=20.9D-27*ANS
C     1200
      GOTO40
  180 SPACE(14)=19.3D-27*ANS
C     1300
      SPACE(16)=8.2D-27*ANS
C     540
      S(1)=23.3D-27*ANS
C     1400
      S(2)=30.4D-27*ANS
C     SIGMA(A) 900+2MB FOR FUTURE CORRECTION
      GOTO40
C     VALUES OF FI FOR BOTH INCIDENT AND CASCADE PARTICLES FOR
C     CHARGED PIONS(PI +OR-) ,SINGLE PRODUCTION.  S(1)=N)S.P., S(2)=P)
C     S.P., SPACE(14)=N)S, SPACE(15)=P)D.S., SPACE(16)=P)ABS, SPACE(17)
C     =P)ABS  (PPAC)
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT3
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      IF(NO-4)10 ,20 ,20
C     BG6A IN ORIGINAL
   10 ISW(11)=1
      GOTO30
   20 ISW(11)=0
   30 CALL UNDIS
      INC=1
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT4
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      CALL CALGEO
      IF(I1) 20,10,10
   10 CURR(3)=PNMS
C     PI+ OR -MASS/CM
      CURR(1)=NO
      CALL PARTIN
      CALL SPAC32(32)
   20 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT5(T,B,R)
      REAL*8 T(126),B(126),R(126)
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      IF(NOT-2) 10 ,20 ,30
   10 CALL CRJAB(1,T(1))
      GO TO 40
C     (PIP-P)ELASTIC SCATTERING CRS.
   20 CALL CRJAB(1,B(1))
      GO TO 40
C     (PIM-P)DIRECT SCATTERING CRS.
   30 CALL CRJAB(1,R(1))
   40 RETURN
      END
*CMZ :  0.92/03 10/12/92  10.54.57  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT6
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      IF(I3)10 ,90 ,90
   10 XABS=1.0
      MED=CLSM
      KNOT=NOT
      VALUE1 = RANDC2(ISEED)
      IF(ISW(11))50 ,20 ,50
   20 IF(VALUE1-PPMDA)60 ,40 ,40
C     PROB. PIM-DEUT ABS.
   30 RETURN
   40 I3=1
      GO TO 30
   50 IF(VALUE1-PPPDA)60 ,40 ,40
C     PROB. PIP-DEUT ABS.
   60 IF(ISW(11))80 ,70 ,80
   70 IT=13
      ABSEC=PMAC(MED)
      GO TO 90
   80 IT=14
      ABSEC=-HVN(MED)
   90 STRKP=-1.0
      I1=0
      I2=MED
      CALL CBBBBB
      I3=0
      GO TO 30
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT6A
      SAVE
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
   10 I1=0
      CALL SPISOM
      STRKP=-2.0
      I1=1
      CALL SPISOM
      STRKP=-1.0
      COM=(AWD(MED)-7.0)*2.0*RCPMV
      IF(COM-E(2))10 ,10 ,20
   20 PM(2)=2.0*DNCMS
      PM(3)=DNCMS
      E(2)=PM(2)+E(2)
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT7
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
      I3=0
      IF(CURR(1)-3.0)20 ,50 ,10
   10 IF(CURR(1)-5.0)60 ,40 ,20
C     PROTON, NEUTRON NOT PERMITTED
   20 I3=-1
   30 RETURN
   40 IT=7
      IFCA=5
C     PI MESON - (5)
      ABSEC=PMAC(MED)
C     PIM +PP ABS.  TYOR=PMAPP(20021)
      GOTO90
   50 IT=10
      IFCA=3
C     TYOR=PPAN(20004)  PIP-NN ABS. ENERGY CORRECTION PIMESON +
      ABSEC=PPAN(MED)
      GOTO100
   60 VALUE1 = RANDC2(ISEED)
      IF(VALUE1-PPNNA)70 ,80 ,80
   70 IT=8
      IFCA=4
C     PNANN(20015)=TYOR  PIN-NN ABS  PIMESON 0
      ABSEC=-HVN(MED)
      GOTO100
   80 IT=9
      IFCA=2
C     PNAPP(20011)=TYOR  PIN+PP ABS.  PIMESON 0
      ABSEC=-HVP(MED)
   90 STRKP=-1.0
      E(1)=WKRPN(MED)*RCPMV+PM(1)
      GOTO110
  100 STRKP=-2.0
      E(1)=WKRPN(MED+3)*RCPMV+PM(1)
  110 IF(INC)130,120,130
  120 CALL P1CLC
      GOTO30
  130 CALL P1CLI
      GOTO30
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT7A
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      SAVE
   10 I1=-1
      CALL SPISOM
      GOTO(20 ,30 ,20 ,20 ,30 ),IFCA
   20 VALUE1=SPACE(MED+3)-7.0
      GOTO40
   30 VALUE1=SPACE(MED+9)-7.0
   40 IF(VALUE1)50 ,70 ,70
   50 I3=2
   60 RETURN
   70 IF((VALUE1*2.0*RCPMV)-E(2))10 ,10 ,80
   80 PM(3)=DNCMS
      PM(2)=2.0*DNCMS
      E(2)=PM(2)+E(2)
      VALUE1=EX
      IF(MED-2)90 ,100,110
   90 I3=3
      GOTO60
  100 I3=4
      GOTO60
  110 IF(INC)120,170,120
  120 IF(ISW(1))140,130,140
  130 I3=5
      GOTO60
  140 IF(ISW(2))150,160,150
  150 I3=6
      GOTO60
  160 I3=9
      GOTO60
  170 IF(ISW(1))190,180,190
  180 I3=7
      GOTO60
  190 IF(ISW(2))200,210,200
  200 I3=1
      GOTO60
  210 I3=8
      GOTO60
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ROUT8
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      SAVE
      I3=1
      IF(IV) 20 ,10 ,10
   10 IF(VALUE1-VALUE2) 20 ,20 ,110
   20 IF(ISW(3)) 80 ,30 ,80
   30 IFC=7+IFCC
C     7=BG6E(2461)  8=BG6IA(4026)  NTNT(21626)  BG48X(12762)=19
      IF(IN) 40  ,60 ,40
   40 I3=2
   50 RETURN
   60 C(3)=D(2)
      GO TO 70
   70 I3=3
      GO TO 50
   80 IFC=8+IFCC
      IF(IN)90 ,100,90
   90 I3=4
      GO TO 50
  100 C(3)=D(2)+D(3)+D(4)
      GO TO 70
  110 CALL SIGNEX
      GOTO 50
      END
*CMZ :  0.90/00 05/06/92  10.57.24  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SIGNEX
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      CALL EXPRN(UNIV)
      EX=EX+UNIV/SIGN
      RETURN
C     EX=DISTANCE IN SAMPLING ROUTINE
C     EXPONENTIAL RANDOM DIVIDED BY SIGMA CI REGION I
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SPAC32(I)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      EX=0.0
      I4=5
      SIGN=9.99999D-1*SPACE(I)
      IF(I-31)10,20,30
   10 I2=18
      I3=3
      GOTO90
   20 I2=22
      I3=5
      GOTO90
   30 IF(I-41)40,50,50
   40 I2=26
      I3=7
      GOTO90
   50 I4=3
      IF(I-42)60,70,80
   60 I2=35
      I3=13
      GOTO90
   70 I2=37
      I3=17
      GOTO90
   80 I2=39
      I3=21
   90 CALL CABG6B
      CALL SIGNEX
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CASPCN
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL*8 WK
      SAVE
C
      FMAX(4)=0.0
      FMAX(5)=0.0
      I6=CURR(1)-1.95
      WK=WKRPN(I2)
      GOTO(10,20,10),I6
   10 UNIV=PNMS
      GOTO30
   20 UNIV=POMS
   30 CALL CBOVER(WK,UNIV,UNIVE)
      VALUE1=0.0
      IF(WK-220.0)40,40,100
   40 GOTO(50,80,50),I6
   50 FMAX(5)=0.35D-27*UNIVE
C     (PIP+P)S.P.
      FMAX(6)=2.3D-27*UNIVE
C     (PIM+P)S.P.
      FMAX(1)=0.20D-24*UNIVE
C     (PIP+P)SC
      FMAX(3)=.0451D-24*UNIVE
C     (PIM+P)EX
   60 FMAX(2)=0.023D-24*UNIVE
C     (PIM-P)SC
   70 RETURN
   80 FMAX(6)=1.35D-27*UNIVE
C     (PI0+P)S.P.
      FMAX(1)=89.2D-27*UNIVE
C     (PI0+P)SC
      FMAX(2)=.0451D-24*UNIVE
C     (PI0+P)EX
   90 FMAX(3)=FMAX(1)
C     (PI0+N)SC
      FMAX(4)=FMAX(2)
C     (PI0+N)EX
      FMAX(7)=FMAX(6)
C     (PI0+N)S.P.
      GOTO70
  100 IF(WK-400.0)110,110,140
  110 GOTO(120,130,120),I6
  120 FMAX(5)=4.5D-27*UNIVE
      FMAX(6)=20.6D-27*UNIVE
      FMAX(1)=0.20D-24
      FMAX(3)=.0451D-24
      GOTO60
  130 FMAX(6)=12.5D-27*UNIVE
      FMAX(1)=89.2D-27
      FMAX(2)=.0451D-24
      GOTO90
  140 IF(WK-500.0)150,150,180
  150 GOTO(160,170,160),I6
  160 FMAX(1)=.113D-24
      FMAX(2)=20.5D-27*UNIVE
      FMAX(3)=27.7D-27
      FMAX(5)=11.7D-27*UNIVE
      FMAX(6)=21.7D-27*UNIVE
      GOTO70
  170 FMAX(1)=50.8D-27
      FMAX(2)=27.7D-27
      FMAX(6)=14.6D-27*UNIVE
      GOTO90
  180 VALUE1=1.0
      IF(WK-600.0)190,190,220
  190 GOTO(200,210,200),I6
  200 FMAX(1)=51.0D-27
      FMAX(2)=24.7D-27*UNIVE
      FMAX(3)=15.5D-27*UNIVE
      FMAX(5)=15.1D-27*UNIVE
      FMAX(6)=30.4D-27*UNIVE
      GOTO70
  210 FMAX(1)=23.0D-27*UNIVE
      FMAX(2)=15.5D-27*UNIVE
      FMAX(6)=22.6D-27*UNIVE
      GOTO90
  220 IF(WK-800.0)230,230,260
  230 GOTO(240,250,240),I6
  240 FMAX(1)=33.0D-27
      FMAX(2)=26.3D-27*UNIVE
      FMAX(3)=12.0D-27*UNIVE
      FMAX(5)=20.1D-27*UNIVE
      FMAX(6)=30.4D-27*UNIVE
      GOTO70
  250 FMAX(1)=16.0D-27*UNIVE
      FMAX(2)=12.0D-27*UNIVE
      FMAX(6)=22.6D-27*UNIVE
      GOTO90
  260 GOTO(270,280,270),I6
  270 FMAX(1)=19.3D-27*UNIVE
      FMAX(2)=26.3D-27*UNIVE
      FMAX(3)=8.2D-27*UNIVE
      FMAX(5)=23.3D-27*UNIVE
      FMAX(6)=30.4D-27*UNIVE
      GOTO70
  280 FMAX(1)=16.0D-27*UNIVE
      FMAX(2)=8.2D-27*UNIVE
      FMAX(6)=24.9D-27*UNIVE
      GOTO90
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SPISOM
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
   10 CALL CAISOM
      IF(I1)20,20,30
   20 SPACE(176)=PXYZ(2)
      SPACE(177)=PXYZ(6)
      SPACE(178)=PXYZ(10)
      IF(I1)50,40,40
   30 PXYZ(2)=PXYZ(2)+SPACE(176)
      PXYZ(6)=PXYZ(6)+SPACE(177)
      PXYZ(10)=PXYZ(10)+SPACE(178)
      E(2)=(PXYZ(10)*PXYZ(10)+PXYZ(6)*PXYZ(6)+PXYZ(2)*PXYZ(2))/
     11.9032D14
   40 RETURN
   50 I1=1
      GOTO10
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CSTORE
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      REAL * 8 SUB1,SUB2
      SAVE
C
      CALL CZERO
      N=I1
      IF(I3)200,10,200
   10 K=I2+6
      L=I2
      GOTO(50,50,50,20,50),I5
   20 IF(I1-5)30,230,30
   30 MM=-6
   40 L=K
      N=N-1
   50 DO110 I=1,N,2
         ID=I
         CE(I+1)=FMAX(I)*1.0D30*SPACE(K)
         CE(I+2)=FMAX(I+1)*1.0D30*SPACE(L)
         GOTO(110,110,60,60,60),I5
   60    M=K
         K=L
         GOTO(110,110,100,80,70),I5
   70    IF(ID-2)110,110,90
   80    K=M+MM
         MM=-MM
         L=K
         GOTO110
   90    K=I2
  100    L=M
  110 CONTINUE
      GOTO(120,120,120,220,120),I5
  120 SIGN=0.0
      DO130 I=2,8
  130 SIGN=SIGN+CE(I)
      GOTO(140,140,150,250,150),I5
  140 SIGN=SIGN*9.99999D-1
      RETURN
  150 IF(I1-4)160,160,140
  160 IF(I3)170,170,180
  170 SPACE(I2+87)=SIGN
      GOTO190
  180 SPACE(I2+106)=SIGN
  190 FMAX(5)=0.0
      FMAX(6)=0.0
      GOTO140
  200 K=I2
      L=I2+6
      GOTO(50,50,50,210,50),I5
  210 MM=6
      GOTO40
  220 CE(8)=FMAX(7)*1.0D30*SPACE(L)
      GOTO120
  230 SUB1=FMAX(1)*1.0D30
      SUB2=FMAX(2)*1.0D30
      DO240 I=2,N,2
         CE(I)=SUB1*SPACE(K)
         CE(I+1)=SUB2*SPACE(K)
         K=L
  240 L=K+6
      CE(N+1)=SPACE(K)*1.0D30*FMAX(N)
      GOTO120
  250 IF(I1-5)140,260,140
  260 SPACE(I2+68)=SIGN
      FMAX(6)=0.0
      FMAX(7)=0.0
      GOTO140
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CASTPH(W)
      REAL*8 W(11)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      IF(PGVC(1)-440.0)10,40,40
   10 I=PGVC(1)+2.005
      J=I+10
C     PGVC(1)=NO.OF TIMES VELOCITY GREATER THAN CRITERION ENTERED
      L=1
      DO20 K=I,J
         PGVC(K)=W(L)
   20 L=L+1
      PGVC(1)=PGVC(1)+11.0
   30 RETURN
   40 I1=1
      GOTO30
      END
*CMZ :  1.01/04 10/06/93  14.43.38  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CASTPL(W)
      REAL*8 W(12)
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
      SAVE
C
      DO10 K=2,950,12
         IF(PLVC(K))10,40,10
   10 CONTINUE
   20 I1=1
   30 RETURN
   40 I=K
      J=I+11
C     PLVC(1)=NO. OF TIMES ENTERED FOR STORAGE OF VELOCITY
C     LESS THAN CRITERION
      L=1
      DO50 K=I,J
         PLVC(K)=W(L)
   50 L=L+1
      PLVC(1)=PLVC(1)+1.0
      GOTO30
      END
*CMZ :  1.01/04 10/06/93  14.43.39  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CASTPR
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      SAVE
      I1=0
      MED=CLSM
      DO90 I=3,39,12
         K=I
         IF(PT(I))10,90,10
   10    IF(PT(K-1)-2.0)20,30,20
   20    PT(K-2)=PT(K)-SPACE(MED+9)
         GOTO60
   30    PT(K-2)=PT(K)-SPACE(MED+3)
   40    IF(PT(K-2)-500.0)50,50,80
   50    CALL CASTPL(PT(K-2))
C     VELOCITY LESS THAN CRITERION
         IF(I1)100,90,100
   60    IF(PT(K-1)-1.0)70,40,70
   70    PT(K-2)=(DNCMS*PT(K-2))/PT(K+1)
         GOTO40
   80    CALL CASTPH(PT(K-1))
C     VELOCITY GREATER THAN CRITERION
         IF(I1)100,90,100
   90 CONTINUE
  100 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.39  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE UNDIS
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CMUNPU.
       DIMENSION NIP(12)
       REAL*8 PCC(12),PPNB(5)
       COMMON/CMUNPU/PCC,PPNB,NIP
C
C    CALOR random seed
*KEEP,CRN.
       COMMON/CRN/COUNT
       REAL*8 COUNT(10)
C
*KEEP,CXYINC.
       COMMON/CXYINC/X,Y
       REAL*8 X,Y
C
*KEND.
      REAL*8 RAN1,RAN2
      SAVE
C
      IF(BEGRU) 110,130,100
   10 BEGRU=1.0
      DO 20 I = 1,4
   20 RANDS(I)=RANDI(I)
   30 RAN1 = RANDC2(ISEED)
      RAN2 = RANDC2(ISEED)
      RAN1 = 2.D0*RAN1-1.D0
      RAN2 = 2.D0*RAN2-1.D0
      IF(RAN1**2 + RAN2**2 .GE. 1.D0) GO TO 30
      XI(1) = RAN1*OUT(4)
      XI(2) = RAN2*OUT(4)
      X = XI(1)
      Y = XI(2)
      CURR(4)=XI(1)
      CURR(5) = XI(2)
      XI(3)=-OUT(4)
      DCOS(1)=0.0
      DCOS(2)=0.0
      DCOS(3)=1.0
      MED=4
      CURR(6)=XI(3)
      CURR(7)=0.0
      CURR(8)=0.0
      CURR(9)=1.0
      CURR(10)=MED
C     X, Y AND Z COORDINATES, ALSO ALPHA, BETA AND GAMMA
C     DIRECTION COSINES.  MED=4, (NO. OF GEOM)
   40 RETURN
   50 BEGRU = BEGRU + 1.0 D0
   60 BEGRU=BEGRU+1.0
      IF(CASESN -BEGRU)80,70,70
   70 FRAND = RANDC2(ISEED)
      GO TO 30
   80 BEGRU=0.0
      DO90 I=1,4
         RANDI(I)=RANDS(I)
   90 ERAND(I)=RANDS(I)
      GOTO40
C     FINAL RANDOM IN ERAND.  RUN COMPLETED
  100 IF(COUNT(6).EQ.0.0) GO TO 130
  110 COUNT(6) = 0.0
  120 IF(BEGRU) 50,10,60
  130 DO 140 I=1,12
         PCC(I) = CC(I)
  140 NIP(I) = IPEC(I)
      DO 150 I=1,5
  150 PPNB(I) = PNBC(I)
      GO TO 120
C*** WHEN BEGRU = 0, MUNPU COMMON IS ZEROED
      END
*CMZ :  1.01/04 10/06/93  14.43.39  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CALXYI(II,JJ,KK)
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      REAL * 8 W1,W2,W3,W4,W5,W6
      SAVE
C
      W1=S(II)*1.0D30
      W2=S(II+1)*1.0D30
      IF(IABS(IV)-1)10,20,10
   10 W3=SPACE(JJ)*1.0D30
      W4=SPACE(JJ+1)*1.0D30
      W5=SPACE(JJ+2)*1.0D30
      W6=SPACE(JJ+3)*1.0D30
      LL=II+2
      IF(IV)40,60,40
   20 W3=S(II+2)*1.0D30
      W4=S(II+3)*1.0D30
      W5=SPACE(JJ)*1.0D30
      W6=SPACE(JJ+1)*1.0D30
      LL=II+4
      IF(IV)50,30,30
   30 NM=7
      I7=1
   40 MM=7
      NN=1
      GO TO 70
   50 NM=1
      I7=7
   60 MM=1
      NN=7
   70 DO100 I=1,3
         S(LL)=W1*SPACE(MM)
         S(LL+1)=W2*SPACE(NN)
         IF(IABS(IV)-1)90,80,90
   80    S(LL+2)=W3*SPACE(NM)
         S(LL+3)=W4*SPACE(I7)
         LL=LL+2
         NM=NM+1
         I7=I7+1
   90    MM=MM+1
         NN=NN+1
  100 LL=LL+2
      IF(IV)110,120,130
  110 NM=7
      I7=1
      GOTO170
  120 MM=1
      NN=7
      NM=7
      I7=7
      GOTO 150
  130 IF(IV-1)160,160,140
  140 MM=7
      NN=1
      NM=1
      I7=7
  150 LL=JJ+4
      GOTO180
  160 NM=1
      I7=7
  170 LL=JJ
  180 DO210 I=1,3
         SPACE(LL+2)=W5*SPACE(NM)
         SPACE(LL+3)=W6*SPACE(I7)
         IF(IABS(IV)-1)190,200,190
  190    SPACE(LL)=W3*SPACE(MM)
         SPACE(LL+1)=W4*SPACE(NN)
         LL=LL+2
         MM=MM+1
         NN=NN+1
  200    NM=NM+1
         I7=I7+1
  210 LL=LL+2
      LL=KK+2
      IF(IABS(IV)-1)220,250,220
  220 MM=JJ+4
      NN=II+2
      DO230 I=KK,LL
         SPACE(I)=SPACE(MM)+SPACE(MM+1)+SPACE(MM+2)+SPACE(MM+3) +S(NN)+
     +   S(NN+1)
         MM=MM+4
  230 NN=NN+2
  240 RETURN
  250 MM=II+4
      NN=JJ+2
      DO260 I=KK,LL
         SPACE(I)=SPACE(NN)+SPACE(NN+1)+S(MM)+S(MM+1)+S(MM+2)+S(MM+3)
         MM=MM+4
  260 NN=NN+2
      GOTO240
      END
*CMZ :  0.92/00 02/12/92  16.02.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CZERO
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      DO 10 I = 1,21
   10 CE(I) = 0.0
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.30  by  Christian Zeitnitz
*-- Author :
      FUNCTION CDOST(I,Z)
C
*KEEP,CEVCM.
      COMMON / CEVCM / Y0,B0,T(4,7),CAM2(130),CAM3(200),WAPS(250,20)
C
*KEND.
C
      IF(Z-70.0) 30,10,10
   10 CDOST = T(I,7)
   20 RETURN
   30 IF(Z-10.0) 40,40,50
   40 CDOST = T(I,1)
      GO TO 20
   50 N = 0.1 * Z + 1.0
      X = 10 * N
      X = (X-Z) * 0.1
      CDOST = X * T(I,N-1) + (1.0-X) * T(I,N)
      GO TO 20
      END
*CMZ :  1.05/01 21/02/2000  16.44.49  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CDRES(M2,M3,T1,NPART,EPART,SOCHPE,U,EREC,HEPART)
C*****A LA EVAP III(TWA,8-68)
C*****COMPATIBLE WITH O5R DRES EXCEPT FOR COMMON/COMON/
C
*KEEP,CJOINT.
       COMMON/ CJOINT/IBERTP,NBERTP
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEEP,CFORCN.
      COMMON/CFORCN/FKEY
*KEEP,CDRESC.
      REAL*4 FLA(6), FLZ(6), EXMASS(6),
     +       CAM4(130),CAM5(200), RMASS(300),
     +       P0(1001),P1(1001),P22(1001),RHO(6),OMEGA(6),
     +       ALPH(300),BET(300)
      COMMON/CDRESC/ IA(6),IZ(6), FLA, FLZ, EXMASS,
     +       CAM4,CAM5, RMASS,
     +       P0,P1,P22,RHO,OMEGA,
     +       ALPH,BET
C
*KEEP,CEVCM.
      COMMON / CEVCM / Y0,B0,T(4,7),CAM2(130),CAM3(200),WAPS(250,20)
C
*KEEP,CAMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
*KEND.
      LOGICAL INIT
C
C
      DIMENSION ZMASS(6),Q(6) ,
     +          FLKCOU(6) ,CCOUL(6) ,THRESH(6) , NPART(6),
     +          EPART(200,2) ,HEPART(200,4) ,SMALLA(6) ,
     +          R(6) ,S(6) ,SOS(6) ,STRUN(6) ,EYE1(6) ,EYE0(6) ,
     +          SMOM1(6) ,IAI(5) ,IZI(5) ,XX(5)
C
      SAVE
      DATA INIT/.TRUE./
C
CZ      DELTAS (A)=(A-1.0)/(1.0+(124.0/A**0.6666667))
      IF(.NOT.INIT) GO TO 20
      INIT = .FALSE.
      FKEY=0.
C evaporation data read in by CRBERT called by CALINI CZ 19.JUNE 92
      DO10 K=1,7
   10 T(4,K)=0.0
      Y0=1.5
      B0=8.0
      NBE8 = 0
      NRNEEP = 0
      ZMASS(1) = XMASS(1)*1.E3
      ZMASS(2) = XMASS(0)*1.E3
      ZMASS(3) = XMASS(7)*1.E3
      ZMASS(4) = XMASS(8)*1.E3
      ZMASS(5) = XMASS(9)*1.E3
      ZMASS(6) = XMASS(10)*1.E3
      EMH = ZMASS(2)
      EMN = ZMASS(1)
C      QUESTION:WHAT IS UM?
C       END OF CHANGE
      UM = 931.20793
      EMHN=EMH-EMN
      EMNUM=EMN-UM
   20 CONTINUE
      DO30 I=1,6
         NPART(I)=0
   30 SMOM1(I)=0.0
      DO40  K=1,6
         FLA(K)=IA(K)
   40 FLZ(K)=IZ(K)
   50 JA=M2
      JZ=M3
      U=T1
      IF(JA-JZ)60  ,60  ,70
   60 CONTINUE
      RETURN
   70 A=JA
      Z=JZ
      BE=Z*EMHN+A*EMNUM-CENERG(A,Z)
      RNMASS=Z*EMH+(A-Z)*EMN-BE
      IF(EREC)80  ,80  ,90
   80 VRNSQ=0.
      VCM=0.
      GO TO 100
   90 VRNSQ=2.0*EREC/RNMASS
      VCM=SQRT(VRNSQ)
  100 IF(JA-8)120 ,110 ,120
  110 IF(JZ-4)120 ,710 ,120
  120 CONTINUE
      DO150 K=1,6
         IF((A-FLA(K)).LE.(Z-FLZ(K)))GO TO 150
         IF(A-2.0*FLA(K))150,130,130
  130    IF(Z-2.0*FLZ(K))150,140,140
  140    Q(K) = CQNRG(A-FLA(K),Z-FLZ(K),A,Z) + EXMASS(K)
C 728 Q(K)=CENERG(A-FLA(K),Z-FLZ(K))-CENERG(A,Z)+EXMASS(K)
  150 CONTINUE
      FLKCOU(1)=0.0
      FLKCOU(2)=CDOST(1,Z-FLZ(2))
      FLKCOU(3)=FLKCOU(2)+.06
      FLKCOU(4)=FLKCOU(2)+.12
      FLKCOU(6)=CDOST(2,Z-FLZ(6))
      FLKCOU(5)=FLKCOU(6)-.06
      CCOUL(1)=1.0
      CCOU2=CDOST(3,Z-FLZ(2))
      CCOUL(2)=CCOU2+1.0
      CCOUL(3)=CCOU2*1.5+3.0
      CCOUL(4)=CCOU2+3.0
      CCOUL(6)=CDOST(4,Z-FLZ(6))*2.0+2.0
      CCOUL(5)=2.0*CCOUL(6)-1.0
      SIGMA=0.0
      DO 200 J=1,6
         IF(A-2.0*FLA(J))180,160,160
  160    IF(Z-2.0*FLZ(J))180,170,170
  170    MM=JA-IA(J)
         ZZ=Z-FLZ(J)
         AA=A-FLA(J)
         IF(AA.LE.ZZ)GO TO 180
         SMALLA(J)=AA*(1.0+Y0*(AA-2.0*ZZ)**2/AA**2)/B0
         THRESH(J)=Q(J)+.88235*FLKCOU(J)*FLZ(J)* ZZ/(RMASS(MM)+RHO(J))
         NN=AA-ZZ
         IZZ=ZZ
         CORR=CAM4(IZZ)+CAM5(NN)
         IF(FKEY.EQ.1.) CORR=0.
         ARG=U-THRESH(J)-CORR
         IF(ARG)180,190,190
  180    R(J)=0.0
         S(J)=0.0
         SOS(J)=0.
         GOTO200
  190    S(J)=SQRT (SMALLA(J)*ARG)*2.0
         SOS(J)=10.0*S(J)
  200 CONTINUE
      N1=1
      DO210 J=1,6
         IF(SOS(J)-1250.0)210 ,220 ,220
  210 CONTINUE
      N1=2
      GO TO 230
  220 SES=AMAX1(S(1),S(2),S(3),S(4),S(5),S(6))
  230 DO390 J=1,6
         IF(S(J))240 ,390 ,240
  240    JS=SOS(J)+1.0
         MM=JA-IA(J)
         IF(N1-1)250 ,260 ,250
  250    IF(JS-1000)290 ,270 ,270
  260    SAS=EXP (S(J)-SES)
         GO TO 280
  270    SAS=EXP (S(J)-50.0)
  280    EYE1(J)=(S(J)**2-3.0*S(J)+3.0)*SAS/(4.0*SMALLA(J)**2)
         FJS=JS
         STRUN(J)=FJS-1.0
         GO TO 300
  290    FJS=JS
         STRUN(J)=FJS-1.0
         EYE1(J)=(P1(JS)+(P1(JS+1)-P1(JS))*(SOS(J)-STRUN(J)))/ SMALLA(J
     +   )**2
  300    IF(J-1)320,320,310
  310    R(J)=CCOUL(J)*RMASS(MM)**2*EYE1(J)
         GOTO380
  320    IF(N1-1)330 ,340 ,330
  330    IF(JS-1000)350 ,340 ,340
  340    EYE0(J)=(S(J)-1.0)*0.5*SAS/SMALLA(J)
         GO TO 360
  350    EYE0(J)=(P0(JS)+(P0(JS+1)-P0(JS))*(SOS(J)-STRUN(J))) /
     +   SMALLA(J)
  360    R(J)=RMASS(MM)**2*ALPH(MM)*(EYE1(J)+BET(MM)* EYE0(J))
         IF(R(J))370 ,380,380
  370    R(J)=0.0
  380    SIGMA=SIGMA+R(J)
  390 CONTINUE
      NCOUNT = 0
  400 IF(SIGMA)410,410,500
  410 CONTINUE
      DO 430  J = 1,6
         IF(JA-IA(J))430 ,420 ,430
  420    IF(JZ-IZ(J))430 ,440 ,430
  430 CONTINUE
      GO TO 480
  440 JEMISS = J
C*****STORE,RESIDUAL NUC IS OF EMITTED PARTICLE TYPE
      EPS = U + EREC
      NPART(JEMISS) = NPART(JEMISS)+1
      NRNEEP = NRNEEP + 1
  450 SMOM1(JEMISS) = SMOM1(JEMISS) + EPS
      IF(JEMISS-2)460 ,460 ,470
  460 EPART(NPART(JEMISS),JEMISS)=EPS
      GO TO 780
  470 KEMISS=JEMISS-2
      HEPART(NPART(JEMISS),KEMISS)=EPS
      GO TO 780
  480 IF(JA-8)790,490,790
  490 IF(JZ-4)790,710,790
  500 URAN = RANDC2(ISEED) * SIGMA
      SUM=0.0
      DO510 J=1,6
         K=J
         SUM=R(J)+SUM
         IF(SUM -URAN)510,510,520
  510 CONTINUE
  520 JEMISS=K
      JS=SOS(JEMISS)+1.0
      IF(JS-1000)540 ,530 ,530
  530 RATIO2=(S(JEMISS)**3-6.0*S(JEMISS)**2+15.0*
     +S(JEMISS)-15.0)/((2.0*S(JEMISS)**2-6.0*S(JEMISS)+6.0)*SMALLA
     +(JEMISS))
      GO TO 550
  540 RATIO2=(P22(JS)+(P22(JS+1)-P22(JS))*
     +(SOS(JEMISS)-STRUN(JEMISS)))/SMALLA(JEMISS)
  550 EPSAV=RATIO2*2.0
      IF(JEMISS-1)560,560,580
  560 MM=JA-IA(J)
  570 EPSAV=(EPSAV+BET(MM))/(1.0+BET(MM)*EYE0(JEMISS)
     +/EYE1(JEMISS))
  580 E1=EXPRNF2(V)/2.0
      E2=EXPRNF2(V)/2.0
      EPS=(E1+E2)*EPSAV+THRESH(JEMISS)-Q(JEMISS)
      COSCM = RANDC2(ISEED)
      PLORMI = RANDC2(ISEED)
      IF(PLORMI-0.5)590,590,600
  590 COSCM=-COSCM
  600 AR=A-FLOAT (IA(JEMISS))
      ZR=Z-FLOAT (IZ(JEMISS))
      BE=ZR*EMHN+AR*EMNUM-CENERG(AR,ZR)
      RNMASS=ZR*EMH+(AR-ZR)*EMN-BE
      VCMEPS = 2.0*EPS/(ZMASS(JEMISS)*(1.+ZMASS(JEMISS)/RNMASS))
      VCMEVP=SQRT(VCMEPS)
      VRNSQ=VCMEPS*ZMASS(JEMISS)*ZMASS(JEMISS)/(RNMASS*RNMASS)
     ++VCM*VCM+2.0*ZMASS(JEMISS)/RNMASS*VCMEVP*VCM*COSCM
      VLBEPS=VCMEPS+VCM*VCM-2.*VCMEVP*VCM*COSCM
      EPS=0.5*ZMASS(JEMISS)*VLBEPS
  610 UNEW=U-0.5*VCMEPS*(ZMASS(JEMISS)*ZMASS(JEMISS)/RNMASS+ZMASS(JEMISS
     +))-Q(JEMISS)
      IF(UNEW)630 ,620 ,620
  620 U = UNEW
      VCM=SQRT(VRNSQ)
      EREC=0.5*RNMASS*VRNSQ
      NPART(JEMISS)=NPART(JEMISS)+1
      GO TO 650
  630 NCOUNT = NCOUNT + 1
      IF(NCOUNT-10) 580,580,640
  640 SIGMA = SIGMA - R(JEMISS)
      R(JEMISS) = 0.0
      NCOUNT = 0
      GO TO 400
  650 JAT=JA-IA(JEMISS)
      JZT=JZ-IZ(JEMISS)
      IF(JAT-JZT)410,410,660
  660 JA=JAT
      JZ=JZT
C*****STORE,END OF NORMAL CYCLE
      SMOM1(JEMISS)=SMOM1(JEMISS)+EPS
      IF(NPART(JEMISS).LE.0)CALL CERROR('CDRES1$')
      IF(JEMISS-2)670 ,670 ,680
  670 EPART(NPART(JEMISS),JEMISS)=EPS
      GO TO 690
  680 KEMISS=JEMISS-2
      HEPART(NPART(JEMISS),KEMISS)=EPS
  690 IF(JA-8)70,700 ,70
  700 IF(JZ-4)70,710 ,70
  710 IF(U)720 ,720 ,730
  720 EPS=0.
      GO TO 740
  730 EPS=0.5*(U+.093)
  740 NBE8=NBE8+1
      COSCM = RANDC2(ISEED)
      VCMEPS=2.0*EPS/ZMASS(6)
      VCMEVP=SQRT(VCMEPS)
      VLBEPS=VCMEPS+VRNSQ+2.0*VCMEVP*VCM*COSCM
      NOP=0
  750 EPS=0.5*ZMASS(6)*VLBEPS
C*****STORE,BE 8 BREAKUP
      SMOM1(6)=SMOM1(6)+EPS
      NPART(6)=NPART(6)+1
      HEPART(NPART(6),4)=EPS
      IF(NOP)760,760,770
  760 VLBEPS=VCMEPS+VRNSQ-2.0*VCMEVP*VCM*COSCM
      NOP=1
      GO TO 750
  770 CONTINUE
  780 EREC=0.
      U = 0.0
  790 SOCHPE=SMOM1(3)+SMOM1(5)+SMOM1(6)+SMOM1(4)
  800 CONTINUE
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.43  by  Christian Zeitnitz
*-- Author :
      FUNCTION CENERG(A,Z)
C
*KEEP,CEVCM.
      COMMON / CEVCM / Y0,B0,T(4,7),CAM2(130),CAM3(200),WAPS(250,20)
C
*KEND.
C
      DELTAS (A)=(A-1.0)/(1.0+(124.0/A**0.6666667))
      CAM (A,Z)=8.367*A-0.783*Z
     + -17.0354*A*(1.0-1.84619*(A-2.0*Z)**2/A**2)
     + +25.8357*A**0.6666667*(1.0-1.71219*(A-2.0*Z)**2/A**2)
     + *(1.0-0.62025/A**0.6666667)**2
     + +0.779*Z*(Z-1.0)*(1.0-1.5849/A**0.6666667+1.2273/A
     + +1.5772/A**1.3333333)/A**0.3333333
     + -0.4323*Z**1.3333333*(1.0-0.57811/A**0.3333333
     + -0.14518/A**0.6666667+0.49597/A)/A**0.3333333
      I=A
      KZ=Z
      N=A-Z
      IF(I.EQ.0) THEN
         CENERG=0.0
         RETURN
      ENDIF
      IF(N.LT.0)CALL CERROR('CENERG A<Z $')
      JPRIME=DELTAS (A)
      J=I-2*KZ-JPRIME+10
      IF(J-20)10,10,40
   10 IF(J)40,40,20
   20 IF(WAPS(I,J))30,40,30
   30 CENERG=WAPS(I,J)
      RETURN
   40 CENERG=CAM (A,Z)+CAM2(KZ)+CAM3(N)
      RETURN
      END
*CMZ :  1.01/09 29/06/93  19.03.31  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CERUP
C*****MODIFIED TO OBTAIN APR,ZPR AFTER CAS + EVAP (8-68,T.W.A.)
*KEEP,CHEVAP.
      COMMON/CHEVAP/HEPART(200,4)
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CCOMN3.
      COMMON/CCOMN3/KINDI(200),WENI
*KEEP,CCOMN2.
      COMMON/CCOMN2/IBBARR(200),WENO
*KEEP,CFORCN.
      COMMON/CFORCN/FKEY
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CAZ.
      COMMON/CAZ/LOWAZ
*KEND.
      DIMENSION FPART(6)
      SAVE
C
      IF(EX) 10 ,20 ,50
   10 NEGEX =NEGEX +1
   20 DO 30  I=1,6
   30 NPART(I)=0
      HEVSUM = 0.0
      UU = 0.0
      RETURN
   40 LOWAZ=LOWAZ+1
      GO TO 20
   50 IF(APR.LE.4.)GO TO 40
      IF(ZPR.LE.2.)GO TO 40
      IF(APR.LE.ZPR)GO TO 40
      M2= APR
      M3= ZPR
      CALL CDRES(M2,M3,EX,NPART,EPART,HEVSUM,UU,EREC,HEPART)
      DO 60   I=1,6
   60 IF(NPART(I).GT.0) GOTO 70
      FKEY =1.
      CALL CDRES(M2,M3,EX,NPART,EPART,HEVSUM,UU,EREC,HEPART)
      FKEY=0.
   70 CONTINUE
   80 DO 90  I=1,6
         IF(NPART(I).GT.200) THEN
            CALL CERROR(' CERUP : N_EVAP > 200 $')
            WRITE(IO,10000) I,NPART(I)
10000     FORMAT(' CERUP: I=',I5,' NPART=',I5)
            NPART(I)=200
         ENDIF
         FPART(I)=NPART(I)
   90 CONTINUE
      ZPR=ZPR-FPART(2)-FPART(3)-2.*(FPART(5)+FPART(6)) -FPART(4)
      APR=APR-FPART(1)-FPART(2)-2.*FPART(3)-3.*(FPART(4)+FPART(5))
     +    -4.*FPART(6)
C         CHANGED JAN.1,1986
      NPART1=NPART(1)
      NPART2=NPART(2)
      IF(NPART1.LE.0)GO TO 110
      DO 100 I=1,NPART1
         KINDI(I)=2
         IBBARR(I)=1
  100 CONTINUE
  110 IF(NPART2.LE.0) RETURN
      DO 120 I=1,NPART2
         KINDI(I)=1
         IBBARR(I)=1
  120 CONTINUE
C        END OF CHANGE
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.30  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE GTISO2(U,V,W)
C
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
   10 Z = RANDC2(ISEED)
      X = 0.687368 * SFLRAF2(X)
      Y = 0.687368 * SFLRAF2(X)
      XSQ = X * X
      YSQ = Y * Y
      ZSQ = Z * Z
      D = XSQ + YSQ + ZSQ
      IF(D*D-Z) 20 ,20 ,10
   20 U = 2.0*X*Z/D
      V = 2.0*Y*Z/D
      W = (ZSQ-XSQ-YSQ)/D
      RETURN
      END
*CMZ :  1.01/09 29/06/93  16.14.56  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE RECOIL
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CAMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
*KEND.
      SAVE
C
      IF(APR.LE.4.) THEN
        EREC = 0.0
      ELSE
        PX=0.
        PY=0.
        PZ=0.
        IF(NOPART.NE.0) THEN
          DO 10 I=1,NOPART
            TM = XMASS(KIND(I))*1000.
            PI = EP(I)*SQRT (1.+2.*TM/EP(I))
            PX = PI*ALPHA(I) +PX
            PY = PI*BETA(I) +PY
            PZ = PI*GAM(I)   +PZ
   10     CONTINUE
        ENDIF
        KT= TIP(NO)
        TM = XMASS(KT)*1000.
        PZ = EC(NO)*SQRT (1.+2.*TM/EC(NO)) - PZ
        AA  = APR * 931.49432
        EREC = SQRT (AA**2 +PX**2 +PY**2 +PZ**2)-AA
      ENDIF
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.30  by  Christian Zeitnitz
*-- Author :
      FUNCTION CQNRG(A1,Z1,A2,Z2)
C
*KEEP,CEVCM.
      COMMON / CEVCM / Y0,B0,T(4,7),CAM2(130),CAM3(200),WAPS(250,20)
C
*KEND.
C
      DELTAS (A)=(A-1.0)/(1.0+(124.0/A**0.6666667))
      CAM (A,Z)=8.367*A-0.783*Z
     1-17.0354*A*(1.0-1.84619*(A-2.0*Z)**2/A**2)
     2+25.8357*A**0.6666667*(1.0-1.71219*(A-2.0*Z)**2/A**2)
     3*(1.0-0.62025/A**0.6666667)**2
     4+0.779*Z*(Z-1.0)*(1.0-1.5849/A**0.6666667+1.2273/A
     5+1.5772/A**1.3333333)/A**0.3333333
     6-0.4323*Z**1.3333333*(1.0-0.57811/A**0.3333333
     7-0.14518/A**0.6666667+0.49597/A)/A**0.3333333
      I1 = A1
      I2 = A2
      KZ1 = Z1
      KZ2 = Z2
      N1 = A1 - Z1
      N2 = A2 - Z2
      IF(N1.LE.0) CALL CERROR('CQNRG1$')
      IF(N2.LE.0) CALL CERROR('CQNRG2$')
      JP1 = DELTAS(A1)
      JP2 = DELTAS(A2)
      J1 = I1 - 2*KZ1 - JP1 + 10
      J2 = I2 - 2*KZ2 - JP2 + 10
      IF(J1.LT.1.OR.J1.GT.20) GO TO 10
      IF(J2.LT.1.OR.J2.GT.20) GO TO 10
      ENRG1 = WAPS(I1,J1)
      ENRG2 = WAPS(I2,J2)
      IF(ENRG1.EQ.0.) GO TO 10
      IF(ENRG2.EQ.0.) GO TO 10
      GO TO 20
   10 ENRG1 = CAM(A1,Z1) + CAM2(KZ1) + CAM3(N1)
      ENRG2 = CAM(A2,Z2) + CAM2(KZ2) + CAM3(N2)
   20 CQNRG = ENRG1 - ENRG2
      RETURN
      END
*CMZ :  1.04/10 07/10/97  09.28.00  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   06/06/92
      SUBROUTINE CALSIG
C************************************************************
C         CALOR-Cross-Section
C
C  INPUT  : material constants and particle type
C  OUTPUT : distance to next hadronic interaction
C
C  Author : Christian Zeitnitz (U of Arizona)
C  Date   : 6-6-92
C************************************************************
C
C GEANT Commons
*KEEP,GCKINE.
      COMMON/GCKINE/IKINE,PKINE(10),ITRA,ISTAK,IVERT,IPART,ITRTYP
     +      ,NAPART(5),AMASS,CHARGE,TLIFE,VERT(3),PVERT(4),IPAOLD
C
*KEEP,GCTRAK.
      PARAMETER (MAXMEC=30)
      COMMON/GCTRAK/VECT(7),GETOT,GEKIN,VOUT(7),NMEC,LMEC(MAXMEC)
     + ,NAMEC(MAXMEC),NSTEP ,MAXNST,DESTEP,DESTEL,SAFETY,SLENG
     + ,STEP  ,SNEXT ,SFIELD,TOFG  ,GEKRAT,UPWGHT,IGNEXT,INWVOL
     + ,ISTOP ,IGAUTO,IEKBIN, ILOSL, IMULL,INGOTO,NLDOWN,NLEVIN
     + ,NLVSAV,ISTORY
      PARAMETER (MAXME1=30)
      COMMON/GCTPOL/POLAR(3), NAMEC1(MAXME1)
C
*KEEP,GCMATE.
      COMMON/GCMATE/NMAT,NAMATE(5),A,Z,DENS,RADL,ABSL
C
      INTEGER NMAT,NAMATE
      REAL A,Z,DENS,RADL,ABSL
C
*KEEP,GCJLOC.
      COMMON/GCJLOC/NJLOC(2),JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      INTEGER       NJLOC   ,JTM,JMA,JLOSS,JPROB,JMIXT,JPHOT,JANNI
     +                  ,JCOMP,JBREM,JPAIR,JDRAY,JPFIS,JMUNU,JRAYL
     +                  ,JMULOF,JCOEF,JRANG
C
      COMMON/GCJLCK/NJLCK(2),JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                      ,JPOLAR,JTSTRA,JTSTCO,JTSTEN,JTASHO
C
      EQUIVALENCE (JLASTV,JTSTEN)
C
      INTEGER       NJLCK,JTCKOV,JABSCO,JEFFIC,JINDEX,JCURIN
     +                   ,JPOLAR,JLASTV,JTSTRA,JTSTCO,JTSTEN
     +                   ,JTASHO
C
*KEEP,GCBANK.
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
*KEEP,GCONSP,IF=-SINGLE.
      DOUBLE PRECISION PI,TWOPI,PIBY2,DEGRAD,RADDEG,CLIGHT,BIG,EMASS
      DOUBLE PRECISION EMMU,PMASS,AVO
*
      PARAMETER (PI=3.14159265358979324D0)
      PARAMETER (TWOPI=6.28318530717958648D0)
      PARAMETER (PIBY2=1.57079632679489662D0)
      PARAMETER (DEGRAD=0.0174532925199432958D0)
      PARAMETER (RADDEG=57.2957795130823209D0)
      PARAMETER (CLIGHT=29979245800.D0)
      PARAMETER (BIG=10000000000.D0)
      PARAMETER (EMASS=0.0005109990615D0)
      PARAMETER (EMMU=0.105658387D0)
      PARAMETER (PMASS=0.9382723128D0)
      PARAMETER (AVO=0.60221367D0)
*
*KEEP,GCPHYS.
      COMMON/GCPHYS/IPAIR,SPAIR,SLPAIR,ZINTPA,STEPPA
     +             ,ICOMP,SCOMP,SLCOMP,ZINTCO,STEPCO
     +             ,IPHOT,SPHOT,SLPHOT,ZINTPH,STEPPH
     +             ,IPFIS,SPFIS,SLPFIS,ZINTPF,STEPPF
     +             ,IDRAY,SDRAY,SLDRAY,ZINTDR,STEPDR
     +             ,IANNI,SANNI,SLANNI,ZINTAN,STEPAN
     +             ,IBREM,SBREM,SLBREM,ZINTBR,STEPBR
     +             ,IHADR,SHADR,SLHADR,ZINTHA,STEPHA
     +             ,IMUNU,SMUNU,SLMUNU,ZINTMU,STEPMU
     +             ,IDCAY,SDCAY,SLIFE ,SUMLIF,DPHYS1
     +             ,ILOSS,SLOSS,SOLOSS,STLOSS,DPHYS2
     +             ,IMULS,SMULS,SOMULS,STMULS,DPHYS3
     +             ,IRAYL,SRAYL,SLRAYL,ZINTRA,STEPRA
      COMMON/GCPHLT/ILABS,SLABS,SLLABS,ZINTLA,STEPLA
     +             ,ISYNC
     +             ,ISTRA
*
*KEND.
C
C CALOR common
*KEEP,CALGEA.
C***************************************************************
C
C       CALOR-GEANT Interface common
C
C parameters of incident particle :
C                   IPinc   = particle type a la CALOR
C                   Einc    = kinetic energy
C                   Uinc(3) = direction cosines
C material parameters:
C                   NCEL    = number of elements in mixture (NMTC)
C                             GEANT material no. for MICAP
C                   Amed(I) = mass number
C                   Zmed(I) = charge number
C                   Dmed(I) = Atoms/cm**3 * 1E-24
C                   Hden    = Atoms/cm**3 * 1E-24
C                             of H-Atoms in mixture
C
C particle stack:
C            NPHETC           = number of particles
C            Ekinet(1:NPHETC) = kinetic energy of part.
C            IPCAL(1:NPHETC)  = particle type a la CALOR (extended)
C            UCAL(1:NPHETC,3) = direction cosines
C            CALTIM(1:NPHETC) = age of particle (nsec)
C
C            ATARGT = A no. of target nucleus
C            ZTARGT = Z no. of target nucleus
C
C return of residual nucleus information
C            NRECOL  = no. of heavy recoil products
C            Amed(I) = mass number of residual nucleus
C            Zmed(I) = charge number "          "
C            EXmed   = exitation energy of nucleus
C            ERmed(I)= recoil energy of nucleus
C            IntCal  = type of interaction (GEANT NAMEC index)
C return of cross section of hadronic interaction (CALSIG called)
C            SIG =  x-section
C
C set by CALSIG:
C            ICPROC = -1   undefined
C                   =  0   NMTC called for cross-section
C                   =  1   MICAP called for cross-section
C                   =  2   SKALE(NMTC at 3 GeV) called for cross-section
C                   =  3   FLUKA called for cross-section
C            KCALL : same coding as ICPROC, but is only valid after a
C                    call to GCALOR
C       18/8/92  C.Zeitnitz University of Arizona
C****************************************************************
C
      PARAMETER(EMAXP  = 3.495)
      PARAMETER(EMAXPI = 2.495)
C transition upper limit (GeV) NMTC-FLUKA
      PARAMETER(ESKALE = 10.0)
      PARAMETER(MXCP = 300)
C
      COMMON/ CALGEA / IPINC  , EINC       , UINC(3)   ,NCEL        ,
     +                 HDEN   , AMED(100)  , ZMED(100) ,DMED(100)   ,
     +                 NPHETC ,EKINET(MXCP),IPCAL(MXCP),UCAL(MXCP,3),
     +                 INTCAL , EXMED      , ERMED(100),SIG         ,
     +                 CALTIM(MXCP), ICPROC, NRECOL    ,KCALL       ,
     +                 ATARGT , ZTARGT
C
*KEND.
C
C  Avogadro number multiplied by 1.E-24
      PARAMETER(XNAVO = 0.60221367)
CC
      LOGICAL INIT,GOFLUK,DOSKAL,SKALEF
C
      DATA INIT/.TRUE./
C
      IF(INIT) THEN
C
C Initialize CALOR at first call
         INIT = .FALSE.
C      print *,'*************** calling calsig ************ '
         CALL CALINI
      ENDIF
C
      DOSKAL = .FALSE.
      IF(Z+0.5.GE.1.0 ) THEN
         IPINC = -1
         IF(IPART .LE. 48) IPINC = IGECAL(IPART)
C
C ------------- check if FLUKA have to be called ---------
C ------------------------------------------------- Goto FLUKA ?
C
C particle type not implemented in CALOR
         GOFLUK = IPINC .EQ. -1 .OR. GEKIN .GE. ESKALE
         DOSKAL = (IPINC.EQ.0 .OR. IPINC.EQ.1) .AND. GEKIN.GT.EMAXP
         DOSKAL = DOSKAL .OR. (GEKIN .GT. EMAXPI .AND. (IPINC .GT. 1))
         DOSKAL = DOSKAL .AND. .NOT.GOFLUK
         GOFLUK = GOFLUK .OR. (DOSKAL.AND.SKALEF(IPINC,GEKIN,ESKALE))
C
         IF(GOFLUK) THEN
            ICPROC = 3
            CALL FLDIST
            RETURN
         ENDIF
C
C --------- material information for CALOR --------------------------
C
         EINC = GEKIN * 1000.0
         IF(IPINC .EQ. 1 .AND. EINC .LT. 20.0 ) THEN
C MICAP needs only the GEANT material number !
           NCEL = NMAT
         ELSE
           NCEL = 1
           AMED(1) = A
           ZMED(1) = Z
           DMED(1) = DENS/A*XNAVO
           IF(A.GT.1.0 .AND. A.LT.1.1) THEN
              HDEN = DMED(1)
           ELSE
              HDEN = 0.0
           ENDIF
C ------- get material parameter for a mixture---------------------
           KK=MIN(Q(JMA+11),100.)
           NCEL = 1
           IF(KK.GT.1) THEN
              NCEL = 0
              HDEN = 0.0
              AMOL = Q(LQ(JMIXT-1)+2)
              DO 10 K=1,KK
                 IF(NINT(Q(JMIXT+K)).EQ.1) THEN
                    XMOLCM = DENS/AMOL*XNAVO
                    WI = Q(JMIXT+K+2*KK)*AMOL/Q(JMIXT+K)
                    HDEN = HDEN + XMOLCM*WI
                 ELSE
                    NCEL = NCEL + 1
                    AMED(NCEL)= Q(JMIXT+K)
                    ZMED(NCEL) = Q(JMIXT+K+KK)
                    XMOLCM = DENS/AMOL*XNAVO
                    WI = Q(JMIXT+K+2*KK)*AMOL/AMED(NCEL)
                    DMED(NCEL) = XMOLCM*WI
                 ENDIF
   10         CONTINUE
           ENDIF
         ENDIF
C
         CALL GETXSC
         IF( SIG .GT. 0.0) THEN
            SHADR = ZINTHA/SIG
         ELSE
            SHADR = BIG
         ENDIF
      ELSE
         SHADR = BIG
      ENDIF
      IF(DOSKAL) ICPROC = 2
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.44  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   06/06/92
      SUBROUTINE GETXSC
C***************************************************
C    Get x-section for hadronic interaction
C
C  INPUT: material and particle parameters
C  OUTPUT: SIG = x-section
C  Author: C.Zeitnitz
C
C**************************************************
C GEANT-CALOR interface common
*KEEP,CALGEA.
C***************************************************************
C
C       CALOR-GEANT Interface common
C
C parameters of incident particle :
C                   IPinc   = particle type a la CALOR
C                   Einc    = kinetic energy
C                   Uinc(3) = direction cosines
C material parameters:
C                   NCEL    = number of elements in mixture (NMTC)
C                             GEANT material no. for MICAP
C                   Amed(I) = mass number
C                   Zmed(I) = charge number
C                   Dmed(I) = Atoms/cm**3 * 1E-24
C                   Hden    = Atoms/cm**3 * 1E-24
C                             of H-Atoms in mixture
C
C particle stack:
C            NPHETC           = number of particles
C            Ekinet(1:NPHETC) = kinetic energy of part.
C            IPCAL(1:NPHETC)  = particle type a la CALOR (extended)
C            UCAL(1:NPHETC,3) = direction cosines
C            CALTIM(1:NPHETC) = age of particle (nsec)
C
C            ATARGT = A no. of target nucleus
C            ZTARGT = Z no. of target nucleus
C
C return of residual nucleus information
C            NRECOL  = no. of heavy recoil products
C            Amed(I) = mass number of residual nucleus
C            Zmed(I) = charge number "          "
C            EXmed   = exitation energy of nucleus
C            ERmed(I)= recoil energy of nucleus
C            IntCal  = type of interaction (GEANT NAMEC index)
C return of cross section of hadronic interaction (CALSIG called)
C            SIG =  x-section
C
C set by CALSIG:
C            ICPROC = -1   undefined
C                   =  0   NMTC called for cross-section
C                   =  1   MICAP called for cross-section
C                   =  2   SKALE(NMTC at 3 GeV) called for cross-section
C                   =  3   FLUKA called for cross-section
C            KCALL : same coding as ICPROC, but is only valid after a
C                    call to GCALOR
C       18/8/92  C.Zeitnitz University of Arizona
C****************************************************************
C
      PARAMETER(EMAXP  = 3.495)
      PARAMETER(EMAXPI = 2.495)
C transition upper limit (GeV) NMTC-FLUKA
      PARAMETER(ESKALE = 10.0)
      PARAMETER(MXCP = 300)
C
      COMMON/ CALGEA / IPINC  , EINC       , UINC(3)   ,NCEL        ,
     +                 HDEN   , AMED(100)  , ZMED(100) ,DMED(100)   ,
     +                 NPHETC ,EKINET(MXCP),IPCAL(MXCP),UCAL(MXCP,3),
     +                 INTCAL , EXMED      , ERMED(100),SIG         ,
     +                 CALTIM(MXCP), ICPROC, NRECOL    ,KCALL       ,
     +                 ATARGT , ZTARGT
C
*KEND.
C HETC-COMMON
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEND.
C
C MICAP or HETC ?
      IF(IPINC.EQ.1.AND.EINC.LT.20.0) THEN
C set MICAP parameter
         EK = EINC * 1.0E6
         SIG = SIGMOR2(EK,NCEL)
         ICPROC = 1
      ELSE
C copy parameter to HETC common
         NO = 1
         ITYP = IPINC + 1
         TIP(1) = FLOAT(IPINC)
         EC(1) = EINC
         IF(IPINC.LE.1.AND.EINC.GT.EMAXP) EC(1) = EMAXP*1000.
         IF(IPINC.GT.1.AND.EINC.GT.EMAXPI) EC(1) = EMAXPI*1000.
         MAT = 1
         MXMAT = 1
         NEL(1) = NCEL
C   copy material data to HETC
         DO 10 I=1,NCEL
            DEN(I,1) = DMED(I)
            ZZ(I,1) = ZMED(I)
            A(I,1) = AMED(I)
            DENH(1) = HDEN
   10    CONTINUE
C calcutlate x-section for particle type IPINC and material
         CALL CALCXS
         SIG = SIGMX(ITYP,MAT)
         ICPROC = 0
      ENDIF
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.44  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   06/06/92
      SUBROUTINE CALCXS
C***********************************************
C
C calculate cross section for given material
C
C***********************************************
*KEEP,CCOMON.
      COMMON/CCOMON/A(100,1) ,ALPHA(200) ,APR ,ARG(1) ,BETA(200) ,
     +   COSKS ,COSPH ,COSTH  ,D ,DELSIG  ,DEN(100,1),
     +   DENH(1) ,DKWT ,E(200) ,EC(1) ,
     +   EION(100,1) ,EMAX ,EMIN(7) ,EP(200) ,EPART(200,2) ,EREC ,
     +   EX ,GAM(200) ,HEVSUM ,HSIGG(5,1) ,HSIG ,IBERT ,ITYP ,
     +   KIND(200) ,LELEM ,MAT ,MAXBCH ,MAXCAS ,MXMAT ,N ,NABOV ,
     +   NAMAX,NBELO,NBERTT,NBOGUS,
     +   NEGEX,NEL(1),NEUTNO,NEUTP,NGROUP,NPIDK,NO,
     +   NOBCH,NOCAS,NOMAX,NOPART,NPART(6),OLDWT,
     +   SIGG(100,1),SIGMX(7,2),SINKS,SINPHI,SINTH,TIP(1),
     +   UMAX,UU,WT(1),
     +   ZZ(100,1),ZPR
*KEEP,CGEOS.
C
      COMMON/CGEOS/ GEOSIG(240),SGPIMX,SGMUMX
C
*KEEP,CXPD.
      COMMON / CXPD / NPSG(2,176), PIPSG(2,126), HSIGMX(7),
     +  LOCX(4,4), ETH(4,4), DE
      REAL*4 NPSG
C
*KEND.
C
      M=1
      DO 10  I=1,7
         SIGMX(I,M) = 0.0
   10 CONTINUE
      TOT = 0.0
      DO 20  L=1,NEL(MAT)
         EION(L,M) = CZFOI(ZZ(L,M))*1.0E-6
         NA = INT(A(L,M)+0.5)
         SIGG(L,M) = DEN(L,M)*GEOSIG(NA)
         TOT = TOT + SIGG(L,M)
   20 CONTINUE
      DO 30  IT=1,5
         HSIGG(IT,M) = DENH(M) * HSIGMX(IT) * 1.E24
   30 CONTINUE
      SIGMX(1,M) = TOT + HSIGG(1,M)
      SIGMX(2,M) = TOT + HSIGG(2,M)
      SIGMX(3,M) = TOT + SGPIMX + HSIGG(3,M)
      SIGMX(4,M) = 0.
      SIGMX(5,M) = TOT + SGPIMX + HSIGG(5,M)
      SIGMX(6,M) = SGMUMX
      SIGMX(7,M) = SGMUMX
C
      MT =MXMAT +1
      SIGMX(1,MT)= SGPIMX
      SIGMX(2,MT)= SGPIMX
      SIGMX(3,MT)= SGPIMX
      SIGMX(4,MT)= 0.
      SIGMX(5,MT)= SGPIMX
      SIGMX(6,MT)= SGMUMX
      SIGMX(7,MT)= SGMUMX
CZ      CALL RANGE
      K =1
      SUMARG = DENH(K)* 21.132
      III = NEL(K)
      DO 40   I=1,III
         SUMARG = DEN(I,K)*ZZ(I,K)*(ZZ(I,K)+1.)* (10.566-.333*
     +   ALOG(ZZ(I,K)* A(I,K))) +SUMARG
   40 CONTINUE
      ARG(K) = SQRT (.498*SUMARG)
      RETURN
      END
*CMZ :  1.05/03 27/06/2001  18.17.08  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   30/07/92
      FUNCTION SIGMOR2(EK,NMED)
C***************************************************
C    Get x-section for low energetic neutrons
C    Ek < 20 MeV (Ek is given in eV)
C  INPUT: material and neutron energy
C  OUTPUT: SIG = x-section
C
C**************************************************
C MICAP common
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MPOINT.
      COMMON/MPOINT/LMAG1,LFP1,LFP2,LFP3,LFP4,LFP5,LFP6,LFP7,LFP8,
     + LFP9,LFP10,LFP11,LFP12,LFP13,LFP14,LFP140,LFP15,LFP16,LFP17,
     + LFP18,LFP19,LFP20,LFP21,LFP22,LFP23,LFP24,LFP25,LFP26,
     + LFP27,LFP28,LFP29,LFP30,LFP31,LFP32,LFP33,LFP34,LFP35,
     + LFP36,LFP37,LFP38,LFP39,LFP40,LFP41,LFP42,LFP43,LFP44,
     + LFP45,LFP46,LFP47,LFP48,LFP49,LFP50,LFP51,LFP52,LFP53,
     + LFP18A,LFP210
*KEND.
C
      CALL NSIGTA2(EK,NMED,TSIG,D,LD(LFP32),LD(LFP33))
      SIGMOR2 = TSIG
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.45  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ANGCDF2(D,LD,LZ)
C       THIS ROUTINE READS THE INPUT ANGULAR DISTRIBUTION FILES
C       AND CONVERTS THEM TO A NORMALIZED CDF
      DIMENSION D(*),LD(*)
      IPP=1
      NR=LD(IPP)
      NE=LD(IPP+1)
      NR2=2*NR
      II=2+NR2
   10 CONTINUE
      E=D(II+1)
      NP=LD(II+2)
      A1=-1.0
      PL=D(II+4)
      D(II+4)=0.0
      PROB=0.0
      DO 20 I=2,NP
         N=II+2*I+2
         A2=D(N-1)
         PH=D(N)
         PROB=PROB+(PH+PL)*(A2-A1)/2.0
         PL=PH
         D(N)=PROB
         A1=A2
   20 CONTINUE
      DO 30 I=1,NP
         N=II+2*I+2
         D(N)=D(N)/PROB
   30 CONTINUE
      II=II+2*NP+2
      IF(II.GE.LZ)GO TO 40
      GO TO 10
   40 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.31  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE BANKR2(D,LD,NBNKID)
C       THIS IS A DUMMY ROUTINE USUALLY SUPPLIED BY THE USER TO
C       OBTAIN FURTHER ANALYSIS OF THE PROBLEM DEPENDING ON THE
C       VALUE ASSIGNED TO NBNKID.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MPOINT.
      COMMON/MPOINT/LMAG1,LFP1,LFP2,LFP3,LFP4,LFP5,LFP6,LFP7,LFP8,
     + LFP9,LFP10,LFP11,LFP12,LFP13,LFP14,LFP140,LFP15,LFP16,LFP17,
     + LFP18,LFP19,LFP20,LFP21,LFP22,LFP23,LFP24,LFP25,LFP26,
     + LFP27,LFP28,LFP29,LFP30,LFP31,LFP32,LFP33,LFP34,LFP35,
     + LFP36,LFP37,LFP38,LFP39,LFP40,LFP41,LFP42,LFP43,LFP44,
     + LFP45,LFP46,LFP47,LFP48,LFP49,LFP50,LFP51,LFP52,LFP53,
     + LFP18A,LFP210
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MGAMMA.
      COMMON/MGAMMA/NAMEXG,MTNG,NMEDG,NCOLG,EG,UG,VG,WG,
     1XG,YG,ZG,WATEG,AGEG
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEND.
      DIMENSION D(*),LD(*)
      NBNK=NBNKID
   10 GO TO (20,30,40,50,60,70,80,90,100,110,120,130,140),NBNKID
C       SOURCES GENERATED
   20 RETURN
C       SPLITTINGS OCCURRING
   30 RETURN
C       FISSIONS OCCURRING
   40 RETURN
C       GAMMA RAYS GENERATED
   50 RETURN
C       REAL COLLISIONS
   60 RETURN
C       ALBEDO SCATTERINGS
   70 RETURN
   80 RETURN
   90 RETURN
C       ENERGY CUTOFFS
  100 RETURN
C       TIME CUTOFFS
  110 RETURN
C       RUSSIAN ROULETTE KILLS
  120 RETURN
C       RUSSIAN ROULETTE SURVIVORS
  130 RETURN
C       GAMMA RAYS NOT STORED BECAUSE BANK WAS FULL
  140 RETURN
      END
*CMZ :  1.01/16 26/10/93  09.45.57  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE BARIER2(KZ1,KZ2,A1,A2,CB)
C       THIS ROUTINE CALCULATES THE COULOMB BARRIER FOR A
C       COLLISION INVOLVING CHARGED PARTICLE EMISSION
      IFLG=0
C       CALCULATE THE RADIUS OF THE NUCLEUS AND CHARGED PARTICLE
      A=A1
   10 IF(A.LT.5.5)R=1.20E-13
      IF((A.GE.5.5).AND.(A.LT.6.5))R=2.02E-13
      IF((A.GE.6.5).AND.(A.LT.7.5))R=2.43E-13
      IF((A.GE.7.5).AND.(A.LT.8.5))R=2.84E-13
      IF((A.GE.8.5).AND.(A.LT.9.5))R=3.25E-13
      IF(A.GE.9.5)R=(A**(1.0/3.0))*1.70E-13
      IF(IFLG.EQ.0)R1=R
      IF(IFLG.EQ.1)GO TO 20
      IFLG=1
      A=A2
      GO TO 10
   20 R2=R
C       CALCULATE THE COULOMB BARRIER (UNITS=MEV)
C       THE FACTOR 0.75 IS ARBITRARYLY SET TO ACCOUNT FOR CHARGED
C       PARTICLE EMISSION BELOW THE COULOMB BARRIER
      CB=((KZ1*KZ2*1.44E-13)/(R1+R2))*0.75
      IF(CB.LT.0.0) CB = 0.0
      RETURN
      END
*CMZ :  0.90/00 20/07/92  14.28.01  by  Christian Zeitnitz
*-- Author :
      FUNCTION CADIG2(E)
C       THIS FUNCTION ADDS A TOLERANCE TO THE ARGUMENT
      ARG=ALOG10(E)
      ITR=5-IFIX(ARG)
      EPS=10.**ITR
      CADIG2=1./EPS
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.45  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CANGLE2(D,LD,E,FM,LEN)
C       THIS ROUTINE SELECTS THE SCATTERING ANGLE AT A COLLISION
      DIMENSION D(*),LD(*)
      SAVE
      I=0
      IPP=1
      NR=LD(IPP)
      NE=LD(IPP+1)
      NR2=2*NR
      IP=2+NR2
      INT=LD(IP)
   10 IP=IP+1
      I=I+1
      EINCD=D(IP)
      IF(E.LE.EINCD)GO TO 30
      IP1=IP
      IP=IP+1
      NP=LD(IP)
      IP=IP+2*NP
      IF(IP.GE.LEN)GO TO 20
      GO TO 10
C       E IS GREATER THAN THE LAST INCIDENT ENERGY
C       USE THE LAST DISTRIBUTION
   20 IP=IP-2*NP-1
      GO TO 70
   30 IF(I.EQ.1)GO TO 60
C       CHOOSE WHICH DISTRIBUTION TO SAMPLE FROM
C       THE INTERP2OLATION SCHEME IS ASSUMED LINEAR-LINEAR IF IT
C       IS NOT EQUAL TO THREE (LINEAR-LOG).  THIS IS GENERALLY TRUE
      IF(INT.NE.3)GO TO 40
      PROB=ALOG(EINCD/E)/ALOG(EINCD/D(IP1))
   40 PROB=(EINCD-E)/(EINCD-D(IP1))
      R=FLTRNF2(0)
      IF(R.LE.PROB)GO TO 50
C       SELECT FROM THE SECOND DISTRIBUTION
      NP=LD(IP+1)
      GO TO 70
C       SELECT FROM THE FIRST DISTRIBUTION
   50 IP=IP1
      GO TO 70
C       E IS LESS THAN THE FIRST INCIDENT ENERGY
C       USE THE FIRST DISTRIBUTION
   60 NP=LD(IP+1)
   70 CONTINUE
      PROB1=0.0
      R=FLTRNF2(0)
      DO 80 I=2,NP
         N=IP+2*I+1
         A1=D(N-3)
         IF(R.LE.D(N))GO TO 90
         PROB1=D(N)
   80 CONTINUE
      FM=1.0
      RETURN
   90 FM=A1+(R-PROB1)*(D(N-1)-A1)/(D(N)-PROB1)
      IF(ABS(FM).GT.1.) FM = 1.0
      RETURN
      END
*CMZ :  1.04/00 02/02/95  09.20.58  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CEVAP2(E,Q,ATAR,CB,EX)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM AN
C       EVAPORATION SPECTRUM
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      SAVE
C       CONVERT THE COULOMB BARRIER (CB) TO UNITS OF EV
      CB=CB*1.00E+06
C       CALCULATE THE MAXIMUM ENERGY AVAILABLE
      CBI=CB
      EMAX=E+Q-CB
      IF(EMAX.GT.0.0)GO TO 10
      CB=0.5*CB
      EMAX=E+Q-CB
      IF(EMAX.GT.0.0)GO TO 10
      CB=0.0
      EMAX=E+Q-CB
      IF(EMAX.GT.0.0)GO TO 10
      WRITE(IOUT,10000)E,EMAX,Q,CBI
10000 FORMAT(' MICAP: NEGATIVE MAXIMUM ENERGY CALCULATED IN ROUTINE ',
     1'EVAP --- INDICATING PROBABLE CROSS SECTION ERROR ALLOWING ',
     2'THE REACTION TO OCCUR',/,10X,'E,EMAX,Q,CB=',4E13.5)
      WRITE(6,*) ' CALOR: Fatal ERROR in EVAP ====> STOP '
      STOP
C       CALCULATE THE NUCLEAR2 TEMPERATURE (THETA)
   10 THETA=4.0161E+03*(SQRT(E+Q-CB)/(ATAR**0.8333333))
C       SELECT THE EXIT ENERGY FROM AN EVAPORATION SPECTRUM
   20 R1=FLTRNF2(0)
      R2=FLTRNF2(0)
      W=-ALOG(R1*R2)
      EX=THETA*W
      IF(EX.LT.0.0) EX = 0.0
      IF(EX.LE.EMAX)RETURN
C       RESAMPLE 75% OF THE TIME IF EX IS GREATER THAN EMAX
      R=FLTRNF2(0)
      IF(R.LE.0.75)GO TO 20
      EX=EMAX
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.32  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CEVAP21(EOLD,E,Q,ATAR,CB,EX)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM AN
C       EVAPORATION SPECTRUM FOR AN (N,N-PRIME X) REACTION
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      SAVE
C       CONVERT THE COULOMB BARRIER (CB) TO UNITS OF EV
      CB=CB*1.00E+06
C       CALCULATE THE MAXIMUM ENERGY AVAILABLE
      CBI=CB
      EMAX=EOLD+Q-CB-E
      IF(EMAX.GT.0.0)GO TO 10
      CB=0.5*CB
      EMAX=EOLD+Q-CB-E
      IF(EMAX.GT.0.0)GO TO 10
      CB=0.0
      EMAX=EOLD+Q-CB-E
      IF(EMAX.LE.0.0)EMAX=1.0E+00
C       CALCULATE THE NUCLEAR2 TEMPERATURE (THETA)
   10 THETA=4.0161E+03*(SQRT(EMAX)/(ATAR**0.8333333))
C       SELECT THE EXIT ENERGY FROM AN EVAPORATION SPECTRUM
      ITRY = 0
   20 R1=FLTRNF2(0)
      R2=FLTRNF2(0)
      W=-ALOG(R1*R2)
      EX=THETA*W
      IF(EX.LE.EMAX)RETURN
C       RESAMPLE 75% OF THE TIME IF EX IS GREATER THAN EMAX
      R=FLTRNF2(0)
      ITRY = ITRY + 1
      IF(R.LE.0.75.AND.ITRY.LT.5)GO TO 20
      EX=EMAX
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.45  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   27/04/93
      SUBROUTINE CHKZEB2(NW,IX)
C
C Check if NW words are available in ZEBRA division IX
C
C ZEBRA user communication common
      COMMON/ QUEST / IQUEST(100)
C
      CALL MZNEED(IX,NW,'G')
      IF(IQUEST(11).LT.0) THEN
         PRINT *,'******************************************'
         PRINT *,'*            G C A L O R                 *'
         PRINT *,'*   NOT enough space available in ZEBRA  *'
         PRINT '('' *  division '',I3,'' to store '',I8,               '
     +   //'            '' words  *'')',IX,NW
         PRINT *,'*                                        *'
         PRINT *,'*  INCREASE ZEBRA COMMON SIZE AND RERUN  *'
         PRINT *,'*                                        *'
         PRINT *,'*             RUN TERMINATED             *'
         PRINT *,'******************************************'
         STOP
      ENDIF
      RETURN
      END
*CMZ :  0.93/05 12/02/93  19.04.36  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CLEAR2(L,L1,L2)
C       THIS ROUTINE ZEROS ARRAY L FROM
C       STARTING POINT L1 TO ENDING POINT L2
      DIMENSION L(*)
      IF(L2-L1.LT.0)GO TO 20
      DO 10 I=L1,L2
   10 L(I)=0
   20 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.45  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CMLABE2(D,LD,AWR,KZ,ID,FM,Q,IFLG)
C       THIS ROUTINE CONVERTS THE EXIT NEUTRON SCATTERING ANGLE
C       FROM THE CENTER OF MASS COORDINATE SYSTEM TO THE LABORATORY
C       COORDINATE SYSTEM FOR AN ELASTIC SCATTERING REACTION. IT
C       ALSO CALCULATES THE EXIT ENERGIES AND DIRECTIONAL COSINES
C       FOR THE NEUTRON AND RECOIL NUCLEUS AS WELL AS SETTING ALL
C       EXIT PARAMETERS FOR THE RECOIL NUCLEUS.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MUPSCA.
      COMMON/MUPSCA/ERFGM
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
      MT=0
      IF(ID.EQ.2)MT=2
C       IFLG EQUAL TO ONE IMPLIES LABORATORY COORDINATE SYSTEM
      IF(IFLG.EQ.1)GO TO 10
      IF(IFLG.EQ.2)GO TO 50
      ALPHA=((AWR-1.0)/(AWR+1.0))**2
C       E EQUALS THE EXIT ENERGY IN THE LAB SYSTEM
      E=0.5*EOLD*((1.0-ALPHA)*FM+1.0+ALPHA)
C       CALCULATE COSINE OF SCATTERING ANGLE (FM) IN LAB SYSTEM
      FM=(1.0+AWR*FM)/SQRT(1.0+AWR**2+2.0*AWR*FM)
C       CALCULATE THE NEUTRON EXIT DIRECTIONAL COSINES
   10 SINPSI=SQRT(1.0-FM**2)
      CALL AZIRN2(SINETA,COSETA)
      STHETA=1.0-UOLD**2
      IF(STHETA)30,30,20
   20 STHETA=SQRT(STHETA)
      COSPHI=VOLD/STHETA
      SINPHI=WOLD/STHETA
      GO TO 40
   30 COSPHI=1.0
      SINPHI=0.0
      STHETA=0.0
   40 U=UOLD*FM-COSETA*SINPSI*STHETA
      V=VOLD*FM+UOLD*COSPHI*COSETA*SINPSI-SINPHI*SINPSI*SINETA
      W=WOLD*FM+UOLD*SINPHI*COSETA*SINPSI+COSPHI*SINPSI*SINETA
      S=1.0/SQRT(U**2+V**2+W**2)
      U=U*S
      V=V*S
      W=W*S
C       CALCULATE AND SET THE RECOIL NUCLEUS EXIT PARAMETERS
   50 ER=EOLD-E
C       PERFORM ENERGY BALANCE CONSIDERING TARGET NUCLEUS ENERGY
      IF(IFLG.EQ.2)ER=ERFGM+EOLD-E
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=AWR*AN
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
C       CALCULATE THE NEUTRON MOMENTUM BEFORE AND AFTER COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
      PO=SQRT(2.0*ZN*E)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*UOLD-PO*U
      PRY=PI*VOLD-PO*V
      PRZ=PI*WOLD-PO*W
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      IF(PR.GT.0.0) THEN
         UR=PRX/PR
         VR=PRY/PR
         WR=PRZ/PR
      ELSE
         UR=0.0
         VR=0.0
         WR=0.0
      ENDIF
C       STORE THE  RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      AMP = AR
      ZMP = FLOAT(NZR)
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.45  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CMLABI2(D,LD,AWR,KZ,ID,FM,Q,IFLG,LIFLAG,LRI)
C       THIS ROUTINE CONVERTS THE EXIT NEUTRON SCATTERING ANGLE
C       FROM THE CENTER OF MASS COORDINATE SYSTEM TO THE LABORATORY
C       COORDINATE SYSTEM FOR AN INELASTIC SCATTERING REACTION. IT
C       ALSO CALCULATES THE EXIT ENERGIES AND DIRECTIONAL COSINES
C       FOR THE NEUTRON AND RECOIL NUCLEUS AS WELL AS SETTING ALL
C       EXIT PARAMETERS FOR THE RECOIL NUCLEUS.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
      MT=0
      IF((ID.GE.14).AND.(ID.LE.54))MT=51
      IF(MT.NE.51)GO TO 10
      IMT=ID-14
      MT=MT+IMT
   10 IF(ID.EQ.11)MT=22
      IF(ID.EQ.13)MT=28
C       IFLG EQUAL TO ONE IMPLIES LABORATORY COORDINATE SYSTEM
      IF(LIFLAG.EQ.1)GO TO 60
      IF(IFLG.EQ.1)GO TO 20
C       E1 EQUALS THE EXIT ENERGY IN THE COM SYSTEM
      E1=((AWR/(AWR+1.0))**2)*EOLD+Q*(AWR/(AWR+1.0))
C re-sample in COLISN2 E1<0.0 (Q-value = -EOLD) !!!
      IF(E1.LT.0.0) THEN
         IFLG = -1
         RETURN
      ENDIF
C       E2 EQUALS THE EXIT ENERGY IN THE LAB SYSTEM
      E2=E1+(EOLD+2.0*FM*(AWR+1.0)*SQRT(EOLD*E1))/((AWR+1.0)**2)
C       CALCULATE COSINE OF SCATTERING ANGLE FM IN LAB SYSTEM
      FM=(SQRT(E1/E2))*FM+(SQRT(EOLD/E2))*(1.0/(AWR+1.0))
      E=E2
C       CALCULATE THE NEUTRON EXIT DIRECTIONAL COSINES
   20 SINPSI=SQRT(1.0-FM**2)
      CALL AZIRN2(SINETA,COSETA)
      STHETA=1.0-UOLD**2
      IF(STHETA)40,40,30
   30 STHETA=SQRT(STHETA)
      COSPHI=VOLD/STHETA
      SINPHI=WOLD/STHETA
      GO TO 50
   40 COSPHI=1.0
      SINPHI=0.0
      STHETA=0.0
   50 U=UOLD*FM-COSETA*SINPSI*STHETA
      V=VOLD*FM+UOLD*COSPHI*COSETA*SINPSI-SINPHI*SINPSI*SINETA
      W=WOLD*FM+UOLD*SINPHI*COSETA*SINPSI+COSPHI*SINPSI*SINETA
      S=1.0/SQRT(U**2+V**2+W**2)
      U=U*S
      V=V*S
      W=W*S
      IF(MT.EQ.91)LIFLAG=1
      IF(MT.EQ.22)LIFLAG=1
      IF(MT.EQ.28)LIFLAG=1
      IF(LIFLAG.EQ.1)GO TO 60
C       CALCULATE AND SET THE RECOIL NUCLEUS EXIT PARAMETERS
      ER=EOLD-E+Q
   60 XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=AWR*AN
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
C       CALCULATE THE NEUTRON MOMENTUM BEFORE AND AFTER COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
      PO=SQRT(2.0*ZN*E)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*UOLD-PO*U
      PRY=PI*VOLD-PO*V
      PRZ=PI*WOLD-PO*W
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      UR=PRX/PR
      VR=PRY/PR
      WR=PRZ/PR
C       CALCULATE THE RECOIL HEAVY ION ENERGY FOR MT-91
      IF(LIFLAG.EQ.0)GO TO 70
      XM = AR*931.075E6
      ER= SQRT(PR**2 + XM**2) - XM
   70 CONTINUE
C       IF LR-FLAG IS USED, DO NOT STORE RECOIL ION AT THIS TIME
      IF(LRI.EQ.22)RETURN
      IF(LRI.EQ.23)RETURN
      IF(LRI.EQ.28)RETURN
C       STORE THE  RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      AMP = AR
      ZMP = FLOAT(NZR)
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.05/03 27/06/2001  18.32.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE COLISN2(D,LD,IGAMS,LGAM,INABS,LNAB,XTHRMS,ITHRMS,LTHRM,
     + IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,Q,NSEI,NAEI,NMT2,NMT4,
     + NMT16,NMT17,NMT18,NMT22,NMT23,NMT24,NMT28,NMT51,NMT91,
     + NMT102,NMT103,NMT104,NMT105,NMT106,NMT107,NMT108,NMT109,
     + NMT111,NMT112,NMT113,NMT114,IGCBS2,LGCB2,KZ,LR,QLR,
     + IIN,IIM)
C        THIS ROUTINE IS CALLED AT EACH COLLISION TO
C        DETERMINE THE POST COLLISION PARAMETERS
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MCROSS.
      COMMON/MCROSS/SIGT,SIGTNS,SIGTNA,SIGNES,SIGNIS,SGNISD,SGNISC,
     1SIGN2N,SIGN3N,SIGNNA,SGNN3A,SGN2NA,SIGNNP,SIGNF,SIGNG,SIGNP,
     2SIGND,SIGNT,SGN3HE,SIGNA,SIGN2A,SIGN3A,SIGN2P,SIGNPA,SGNT2A,
     3SGND2A
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MUPSCA.
      COMMON/MUPSCA/ERFGM
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      DIMENSION D(*),LD(*),IGAMS(*),LGAM(*),INABS(*),LNAB(*),
     + XTHRMS(*),ITHRMS(*),LTHRM(*),IDICTS(NNR,NNUC),LDICT(NNR,NNUC),
     + NTX(*),
     + NTS(*),IGCBS(NGR,NNUC),LGCB(NGR,NNUC),AWR(*),Q(NQ,NNUC),
     + NSEI(*),NAEI(*),NMT2(*),NMT4(*),NMT16(1),NMT17(*),NMT18(*),
     + NMT22(*),NMT23(*),NMT24(*),NMT28(*),NMT51(*),NMT91(*),
     + NMT102(*),NMT103(*),NMT104(*),NMT105(*),NMT106(*),NMT107(*),
     + NMT108(*),NMT109(*),NMT111(*),NMT112(*),NMT113(*),NMT114(*),
     + IGCBS2(NGR,NNUC),LGCB2(NGR,NNUC),KZ(*),LR(NQ,NNUC),QLR(NQ,NNUC),
     + FM(MAXNEU)
C
      CHARACTER*80 COMM
C
      DATA QBE8/-7.3686E+06/
      SAVE
      CALL GTMED2(NMED,MED)
C       INITIALIZE THE COUNTERS AND FLAGS
C       ITRY ALLOWS FOR MULTIPLE ATTEMPTS IF THE ENDF/B PARTIAL
C       CROSS SECTIONS DO NOT EXACTLY SUM TO THE TOTAL
   10 ISTOP=0
      ITRY=0
      NCOL=NCOL+1
      SIGREC=0.0
      SUMREC=0.0
      FSUMS = 1.0
      FSUMIS = 1.0
      FSUMA = 1.0
   20 ID=0
      MT=0
      QI=0.0
      LRI=0
      QLRI=0.0
      DO 30 I=1,MAXNEU
         FM(I)=1.0
   30 CONTINUE
      DO 40 I=1,MAXNEU
         ENE(I)=0.0
   40 CONTINUE
      INEU = 0
      U1=0.0
      V1=0.0
      W1=0.0
      ERFGM=0.0
      IFLG=0
      LIFLAG=0
      AWRI=AWR(IIN)
      KZI=KZ(IIM)
C       INITIALIZE THE CROSS SECTION VARIABLES
      SIGT=0.0
      SIGTNS=0.0
      SIGTNA=0.0
      SIGNES=0.0
      SIGNIS=0.0
      SGNISD=0.0
      SGNISC=0.0
      SIGN2N=0.0
      SIGN3N=0.0
      SIGNNA=0.0
      SGNN3A=0.0
      SGN2NA=0.0
      SIGNNP=0.0
      SIGNF=0.0
      SIGNG=0.0
      SIGNP=0.0
      SIGND=0.0
      SIGNT=0.0
      SGN3HE=0.0
      SIGNA=0.0
      SIGN2A=0.0
      SIGN3A=0.0
      SIGN2P=0.0
      SIGNPA=0.0
      SGNT2A=0.0
      SGND2A=0.0
      SUMIS=0.0
      SUMS=0.0
      SUMA=0.0
C       DETERMINE THE TOTAL CROSS SECTION (MT-1)
      L1=LDICT(1,IIN)
      IF(L1.EQ.0)GO TO 50
      LS1=IDICTS(1,IIN) + LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGT)
      GO TO 60
   50 CONTINUE
      COMM=' COLISN2: TOTAL CROSS SECTION LENGTH IS ZERO'
      SIGREC = 0.0
      SUMREC = 0.0
      GOTO 980
   60 CONTINUE
C       DETERMINE THE TOTAL NEUTRON DISAPPEARANCE (MT-102 TO MT-114
C       AND MT-18)
      L1=LNAB(IIN)
      IF(L1.EQ.0)GO TO 70
      LS1=INABS(IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGTNA)
      GO TO 80
   70 SIGTNA=0.0
   80 CONTINUE
C       DETERMINE THE NON-ABSORPTION PROBABILITY
      PNAB=1.0-SIGTNA/SIGT
C       DETERMINE THE COLLISION TYPE (ABSORPTION OR SCATTERING)
      R=FLTRNF2(0)
      IF(R.GT.PNAB)GO TO 570
C       THE REACTION TYPE IS A SCATTER
      NSEI(IIN)=NSEI(IIN)+1
      SIGTNS=SIGT-SIGTNA
      R=FLTRNF2(0)
C       DETERMINE (N,N) CROSS SECTION (MT-2)
      ID=2
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 110
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNES)
      SUMS=SIGNES/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 120
C       REACTION TYPE IS (N,N)
      NMT2(MED)=NMT2(MED)+1
C       DETERMINE IF SCATTERING OCCURS IN THE THERMAL ENERGY RANGE
      ETHERM = 500.*8.617E-5*TEMP/AWRI
      IF(E.LE.ETHERM) THEN
C Reaction is a thermal scatter
         CALL THRMSC2(D,LD,XTHRMS,ITHRMS,LTHRM,E,U,V,W,TEMP,FM,AWR,IIN,
     +               IFLG,IOUT)
         QI=Q(ID,IIN)
         CALL CMLABE2(D,LD,AWRI,KZI,ID,FM,QI,IFLG)
         EP = E
         VP = V
         UP = U
         WP = W
         AGEP = AGE
         MTP = 2
         CALL STOPAR2(IDNEU,NNEU)
         RETURN
      ENDIF
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       CENTER OF MASS COORDINATE SYSTEM
      L1=LDICT(67,IIN)
      IF(L1.EQ.0)GO TO 90
      LS1=IDICTS(67,IIN)+LMOX2
      LEN=L1
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
      GO TO 100
C       ASSUME ISOTROPIC IN THE CENTER OF MASS COORDINATE SYSTEM
   90 R=FLTRNF2(0)
      FM(1)=2.0*R-1.0
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
  100 CONTINUE
      QI=Q(ID,IIN)
      CALL CMLABE2(D,LD,AWRI,KZI,ID,FM(1),QI,IFLG)
      EP = E
      VP = V
      UP = U
      WP = W
      AGEP = AGE
      MTP = 2
      CALL STOPAR2(IDNEU,NNEU)
      RETURN
  110 SIGNES=0.0
  120 CONTINUE
C       DETERMINE (N,N") CROSS SECTION (MT-4)
      ID=3
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 240
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNIS)
      SUMS=SUMS+SIGNIS/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 250
C       REACTION TYPE IS (N,N")
      NMT4(MED)=NMT4(MED)+1
C       DETERMINE (N,N"-DISCRETE) CROSS SECTION (MT-51 TO MT-90)
      R=FLTRNF2(0)
      DO 130 I=14,53
         L1=LDICT(I,IIN)
         IF(L1.EQ.0)GO TO 170
         LS1=IDICTS(I,IIN)+LMOX2
         LEN=L1/2
         CALL XSECNU2(D,LEN,E,SGNISD,LS1,L1)
         SUMIS=SUMIS+SGNISD/SIGNIS*FSUMIS
         IF(R.LE.SUMIS)GO TO 140
  130 CONTINUE
      GO TO 180
  140 CONTINUE
C       REACTION TYPE IS (N,N") DISCRETE
      NMT51(MED)=NMT51(MED)+1
      I=I+68
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       CENTER OF MASS COORDINATE SYSTEM
      L1=LDICT(I,IIN)
      IF(L1.EQ.0)GO TO 150
      LS1=IDICTS(I,IIN)+LMOX2
      LEN=L1
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
      GO TO 160
C       ASSUME ISOTROPIC IN THE CENTER OF MASS COORDINATE SYSTEM
  150 R=FLTRNF2(0)
      FM(1)=2.0*R-1.0
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
  160 ID=I-68
      QI=Q(ID,IIN)
      LRI=LR(ID,IIN)
      QLRI=QLR(ID,IIN)
      CALL CMLABI2(D,LD,AWRI,KZI,ID,FM(1),QI,IFLG,LIFLAG,LRI)
C Re-sample if no energy determined in CMLABI2
      IF(IFLG.EQ.-1) GOTO 10
      EP = E
      VP = V
      UP = U
      WP = W
      AGEP = AGE
      MTP = 51
      CALL STOPAR2(IDNEU,NNEU)
      IF(LRI.EQ.22)GO TO 520
      IF(LRI.EQ.23)GO TO 530
      IF(LRI.EQ.28)GO TO 540
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGNISD)
      RETURN
  170 SGNISD=0.0
  180 CONTINUE
C       DISCRETE INELASTIC SCATTERING LEVEL WAS NOT CHOSEN
C       DETERMINE (N,N"-CONTINUUM) CROSS SECTION (MT-91)
      ID=54
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 210
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SGNISC)
      SUMIS=SUMIS+SGNISC/SIGNIS*FSUMIS
      IF(R.GT.SUMIS)GO TO 220
C       REACTION TYPE IS (N,N") CONTINUUM
      NMT91(MED)=NMT91(MED)+1
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
      L1=LDICT(122,IIN)
      IF(L1.EQ.0)GO TO 190
      LS1=IDICTS(122,IIN)+LMOX2
      LEN=L1
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
      GO TO 200
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  190 CALL GTISO2(U1,V1,W1)
      U=U1
      V=V1
      W=W1
      LIFLAG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  200 L1=LDICT(133,IIN)
      IF(L1.EQ.0)GO TO 230
      LS1=IDICTS(133,IIN)+LMOX2
      CALL SECEGY2(EX,D(LS1),E,LD(LS1))
      E=EX
      IFLG=1
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      LRI=LR(ID,IIN)
      QLRI=QLR(ID,IIN)
      CALL CMLABI2(D,LD,AWRI,KZI,ID,FM(1),QI,IFLG,LIFLAG,LRI)
C Re-sample if no energy determined in CMLABI2
      IF(IFLG.EQ.-1) GOTO 10
      EP = E
      VP = V
      UP = U
      WP = W
      AGEP = AGE
      MTP = 91
      CALL STOPAR2(IDNEU,NNEU)
      IF(LRI.EQ.22)GO TO 520
      IF(LRI.EQ.23)GO TO 530
      IF(LRI.EQ.28)GO TO 540
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGNISC)
      RETURN
  210 SGNISC=0.0
  220 CONTINUE
      COMM=' COLISN: INELASTIC SCATTERING CROSS SECTION WAS NOT CHOSEN'
      NMT4(MED)=NMT4(MED)-1
      FSUMIS = 1./SUMIS
      GO TO 550
  230 CONTINUE
      COMM=' COLISN2: NO SECONDARY ENERGY DISTRIBUTION WAS FOUND MT-91'
      ISTOP=1
      GO TO 560
  240 SIGNIS=0.0
  250 CONTINUE
C       DETERMINE (N,2N) CROSS SECTION (MT-16)
      ID=8
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 290
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGN2N)
      SUMS=SUMS+SIGN2N/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 300
C       REACTION TYPE IS (N,2N)
      NMT16(MED)=NMT16(MED)+1
C       USE THE ONE NEUTRON EMISSION MODEL AND MULTIPLY THE
C       WEIGHT BY TWO
C changed to 2 neutron production CZ July 30, 1992
CZ      WATE=2.0*WATE
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
      L1=LDICT(72,IIN)
      IF(L1.EQ.0)GO TO 260
      LS1=IDICTS(72,IIN)+LMOX2
      LEN=L1
C get scattering angle for 1. neutron
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
C get scattering angle for 2. neutron
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(2),LEN)
      GO TO 270
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  260 CONTINUE
      IFLG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  270 INEU = 2
      L1=LDICT(123,IIN)
      IF(L1.EQ.0)GO TO 280
      LS1=IDICTS(123,IIN)+LMOX2
      CALL GETENE2(E,D(LS1),LD(LS1),INEU)
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      CALL N2NN3N2(D,LD,AWRI,KZI,ID,FM,QI,IFLG)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGN2N)
      RETURN
  280 CONTINUE
      COMM=' COLISN2: NO SECONDARY ENERGY DISTRIBUTION WAS FOUND MT-16'
      ISTOP=1
      GO TO 560
  290 SIGN2N=0.0
  300 CONTINUE
C       DETERMINE (N,3N) CROSS SECTION (MT-17)
      ID=9
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 350
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGN3N)
      SUMS=SUMS+SIGN3N/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 360
C       REACTION TYPE IS (N,3N)
      NMT17(MED)=NMT17(MED)+1
C       USE THE ONE NEUTRON EMISSION MODEL AND MULTIPLY THE
C       WEIGHT BY THREE
C changed to 3 neutron production CZ July 30,1992
CZ      WATE=3.0*WATE
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
      L1=LDICT(73,IIN)
      IF(L1.EQ.0)GO TO 320
      LS1=IDICTS(73,IIN)+LMOX2
      LEN=L1
      DO 310 KN=1,3
         CALL CANGLE2(D(LS1),LD(LS1),E,FM(KN),LEN)
  310 CONTINUE
      GO TO 330
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  320 CONTINUE
      IFLG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  330 L1=LDICT(124,IIN)
      IF(L1.EQ.0)GO TO 340
      LS1=IDICTS(124,IIN)+LMOX2
      INEU = 3
      CALL GETENE2(E,D(LS1),LD(LS1),INEU)
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      CALL N2NN3N2(D,LD,AWRI,KZI,ID,FM,QI,IFLG)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGN3N)
      RETURN
  340 CONTINUE
      COMM= ' COLISN2; NO SECONDARY ENERGY DISTRIBUTION WAS FOUND MT-17'
      ISTOP=1
      GO TO 560
  350 SIGN3N=0.0
  360 CONTINUE
C       DETERMINE (N,N"A) CROSS SECTION (MT-22)
      ID=11
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 400
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNNA)
      SUMS=SUMS+SIGNNA/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 410
C       REACTION TYPE IS (N,N"A)
      NMT22(MED)=NMT22(MED)+1
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
      L1=LDICT(75,IIN)
      IF(L1.EQ.0)GO TO 370
      LS1=IDICTS(75,IIN)+LMOX2
      LEN=L1
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
      GO TO 380
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  370 CALL GTISO2(U1,V1,W1)
      U=U1
      V=V1
      W=W1
      LIFLAG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  380 L1=LDICT(126,IIN)
      IF(L1.EQ.0)GO TO 390
      LS1=IDICTS(126,IIN)+LMOX2
      CALL SECEGY2(EX,D(LS1),E,LD(LS1))
      E=EX
      IFLG=1
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      LRI=22
      CALL CMLABI2(D,LD,AWRI,KZI,ID,FM(1),QI,IFLG,LIFLAG,LRI)
C Re-sample if no energy determined in CMLABI2
      IF(IFLG.EQ.-1) GOTO 10
      UP = U
      VP = V
      WP = W
      EP = E
      AGEP = AGE
      MTP = 22
      CALL STOPAR2(IDNEU,NNEU)
      KZ1=2
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=22
      CALL NN2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNNA)
      RETURN
  390 CONTINUE
      COMM=' COLISN2; NO SECONDARY ENERGY DISTRIBUTION WAS FOUND MT-22'
      ISTOP=1
      GO TO 560
  400 SIGNNA=0.0
  410 CONTINUE
C       DETERMINE (N,2NA) CROSS SECTION (MT-24)
      ID=12
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 450
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SGN2NA)
      SUMS=SUMS+SGN2NA/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 460
C       REACTION TYPE IS (N,2NA)
      NMT24(MED)=NMT24(MED)+1
C       USE THE ONE NEUTRON EMISSION MODEL AND MULTIPLY THE
C       WEIGHT BY TWO
C changed to 2 neutron production CZ July 30,1992
CZ      WATE=2.0*WATE
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
      L1=LDICT(76,IIN)
      IF(L1.EQ.0)GO TO 420
      LS1=IDICTS(76,IIN)+LMOX2
      LEN=L1
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(2),LEN)
      GO TO 430
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  420 CONTINUE
      IFLG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  430 L1=LDICT(127,IIN)
      IF(L1.EQ.0)GO TO 440
      LS1=IDICTS(127,IIN)+LMOX2
      INEU=2
      CALL GETENE2(E,D(LS1),LD(LS1),INEU)
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      CALL N2NN3N2(D,LD,AWRI,KZI,ID,FM,QI,IFLG)
      KZ1=2
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR-AN-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=24
      CALL NN2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGN2NA)
      RETURN
  440 CONTINUE
      COMM=' COLISN2; NO SECONDARY ENERGY DISTRIBUTION WAS FOUND MT-24'
      ISTOP=1
      GO TO 560
  450 SGN2NA=0.0
  460 CONTINUE
C       DETERMINE (N,N"P) CROSS SECTION (MT-28)
      ID=13
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 500
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNNP)
      SUMS=SUMS+SIGNNP/SIGTNS*FSUMS
      IF(R.GT.SUMS)GO TO 510
C       REACTION TYPE IS (N,N"P)
      NMT28(MED)=NMT28(MED)+1
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
      L1=LDICT(77,IIN)
      IF(L1.EQ.0)GO TO 470
      LS1=IDICTS(77,IIN)+LMOX2
      LEN=L1
      CALL CANGLE2(D(LS1),LD(LS1),E,FM(1),LEN)
      GO TO 480
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  470 CALL GTISO2(U1,V1,W1)
      U=U1
      V=V1
      W=W1
      LIFLAG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  480 L1=LDICT(128,IIN)
      IF(L1.EQ.0)GO TO 490
      LS1=IDICTS(128,IIN)+LMOX2
      CALL SECEGY2(EX,D(LS1),E,LD(LS1))
      E=EX
      IFLG=1
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      LRI=28
      CALL CMLABI2(D,LD,AWRI,KZI,ID,FM(1),QI,IFLG,LIFLAG,LRI)
C Re-sample if no energy determined in CMLABI2
      IF(IFLG.EQ.-1) GOTO 10
      EP = E
      UP = U
      VP = V
      WP = W
      AGEP = AGE
      MTP = 28
      CALL STOPAR2(IDNEU,NNEU)
      KZ1=1
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AP
      A2=ATAR-AP
      Z1=ZP
      Z2=A2*9.31075E+08
      MT=28
      CALL NN2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNNP)
      RETURN
  490 CONTINUE
      COMM=' COLISN2; NO SECONDARY ENERGY DISTRIBUTION FOUND FOR MT-28'
      SIGREC=SIGTNS
      SUMREC=SUMS
      ISTOP=1
      GO TO 560
  500 SIGNNP=0.0
  510 CONTINUE
      FSUMS = 1./SUMS
      GO TO 550
  520 CONTINUE
C       REACTION TYPE IS (N,N"A) USING LR FLAG
      NMT22(MED)=NMT22(MED)+1
      SIGNNA=SGNISD
      IF(ID.EQ.54)SIGNNA=SGNISC
      KZ1=2
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=22
      CALL LR2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,QLRI,ID,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNNA)
      RETURN
  530 CONTINUE
C       REACTION TYPE IS (N,N"3A) USING LR FLAG
C       CARBON-12 IS CURRENTLY THE ONLY ELEMENT CONTAINING MT-23
      NMT23(MED)=NMT23(MED)+1
      SGNN3A=SGNISD
      IF(ID.EQ.54)SGNN3A=SGNISC
      KZ1=2
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR-AA
      Z1=ZA
      Z2=A2*9.31075E+08
C       QBE8 IS THE MASS DIFFERENCE FOR A CARBON-ALPHA EMISSION
      MT=23
      CALL LR2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,QBE8,ID,MT)
      KZ1=2
      KZ2=KZ2-KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=A2-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=23
      CALL LR2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QBE8,QLRI,ID,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGNN3A)
      RETURN
  540 CONTINUE
C       REACTION TYPE IS (N,N"P) USING LR FLAG
      NMT28(MED)=NMT28(MED)+1
      SIGNNP=SGNISD
      IF(ID.EQ.54)SIGNNP=SGNISC
      KZ1=1
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AP
      A2=ATAR-AP
      Z1=ZP
      Z2=A2*9.31075E+08
      MT=28
      CALL LR2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,QLRI,ID,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNNP)
      RETURN
  550 ITRY=ITRY+1
      NSEI(IIN)=NSEI(IIN)-1
      ISTOP = 1
      IF((FSUMS.GT.0.1.AND.FSUMS.LE.10.0).AND.
     +   (FSUMIS.GT.0.1.AND.FSUMIS.LE.10.0)) ISTOP = 0
      IF(ISTOP.EQ.0.AND.ITRY.LE.5) GOTO 20
C       A SCATTERING REACTION WAS NOT CHOSEN
      COMM=' COLISN2: A SCATTERING REACTION TYPE WAS NOT CHOSEN '
      SIGREC=SIGTNS
      SUMREC=SUMS
      GOTO 980
  560 CONTINUE
      IF(ISTOP.EQ.1)GO TO 980
      ITRY=0
      GO TO 20
C       THE REACTION TYPE IS AN ABSORPTION
  570 NAEI(IIN)=NAEI(IIN)+1
      R=FLTRNF2(0)
C       DETERMINE THE FISSION CROSS SECTION (MT-18)
C       THE TREATMENT OF THE FISSION REACTION ASSUMES THE FISSION
C       CROSS SECTION IS STORED AS NUBAR*SIGF
      ID=10
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 640
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNF)
C       DETERMINE THE AVERAGE NUMBER OF NEUTRONS EMITTED PER FISSION
C       EVENT (NUBAR)
      L1=LDICT(134,IIN)
      IF(L1.EQ.0)GO TO 630
      LS1=IDICTS(134,IIN)+LMOX2
      LEN=L1
      CALL GETNU2(D(LS1),LD(LS1),EOLD,LEN,XNU)
C       EXTRACT THE FISSION CROSS SECTION FROM THE NUBAR*SIGF CROSS
C       SECTION STORED IN POSITION 10 OF THE DICTIONARY
      SIGNF=SIGNF/XNU
      SUMA=SIGNF/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 650
C       THE REACTION TYPE IS (N,F)
      NMT18(MED)=NMT18(MED)+1
      WATE = 0.0
C       DETERMINE THE COSINE OF THE NEUTRON SCATTERING ANGLE IN THE
C       LABORATORY COORDINATE SYSTEM
C changed in order to get N fission neutron CZ July 30,1992
C INEU is poisson distributed with mean XNU
  580 CALL G3POISS(XNU,INEU,1)
      IF(INEU.GT.INT(4.*XNU)) GOTO 580
C check for maximum number of neutrons emitted
      IF(INEU.GT.INT(AWRI)-KZ(MED)) INEU = INT(AWRI) - KZ(MED)
      IF(INEU.GT.MAXNEU) INEU = MAXNEU
      L1=LDICT(74,IIN)
      IF(L1.EQ.0)GO TO 600
      LS1=IDICTS(74,IIN)+LMOX2
      LEN=L1
      DO 590 KN=1,INEU
         CALL CANGLE2(D(LS1),LD(LS1),E,FM(KN),LEN)
  590 CONTINUE
      GO TO 610
C       ASSUME ISOTROPIC IN THE LABORATORY COORDINATE SYSTEM
  600 CONTINUE
      LIFLAG=1
C       DETERMINE THE EXIT NEUTRON ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
  610 L1=LDICT(125,IIN)
      IF(L1.EQ.0)GO TO 620
      LS1=IDICTS(125,IIN)+LMOX2
      IF(INEU.GT.0) CALL GETENE2(E,D(LS1),LD(LS1),INEU)
C       DETERMINE THE EXIT NEUTRON WEIGHT FROM THE AVERAGE NUMBER
C       OF NEUTRONS EMITTED PER FISSION REACTION (NU)
C changed CZ July 30,1992
CZ      WATE=WATE*XNU
C       DETERMINE THE EXIT COLLISION PARAMETERS IN THE LABORATORY
C       COORDINATE SYSTEM
      QI=Q(ID,IIN)
      IF(INEU.GT.0) CALL LABNF2(D,LD,FM,AWRI,KZI,QI,LIFLAG)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNF)
      NPSCL(3)=NPSCL(3)+1
      CALL BANKR2(D,LD,3)
      RETURN
  620 CONTINUE
      COMM=' COLISN2: NO SECONDARY ENERGY DISTRIBUTION FOUND FOR MT-18'
      SIGREC=SIGNF
      SUMREC=SUMA
      ISTOP=1
      GO TO 970
  630 CONTINUE
      COMM=' COLISN2: NO NUMBER OF FISSION NEUTRON FOUND FOR MT-18'
      SIGREC=SIGNF
      SUMREC=SUMA
      ISTOP=1
      GO TO 970
  640 SIGNF=0.0
  650 CONTINUE
C       DETERMINE (N,G) CROSS SECTION (MT-102)
      ID=55
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 660
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNG)
      SUMA=SUMA+SIGNG/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 670
C       THE REACTION TYPE IS (N,G)
      NMT102(MED)=NMT102(MED)+1
      QI=Q(ID,IIN)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNG)
      MT=102
      CALL NGHEVY2(D,LD,KZI,AWRI,QI,MT)
      WATE=0.0
      RETURN
  660 SIGNG=0.0
  670 CONTINUE
C       DETERMINE (N,P) CROSS SECTION (MT-103)
      ID=56
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 690
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNP)
      SUMA=SUMA+SIGNP/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 700
C       THE REACTION TYPE IS (N,P)
      NMT103(MED)=NMT103(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AP
      A2=ATAR+AN-AP
      Z1=ZP
      Z2=A2*9.31075E+08
      MT=103
      IF(KZI.EQ.6)GO TO 680
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNP)
      WATE=0.0
      RETURN
  680 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  690 SIGNP=0.0
  700 CONTINUE
C       DETERMINE (N,D) CROSS SECTION (MT-104)
      ID=57
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 720
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGND)
      SUMA=SUMA+SIGND/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 730
C       THE REACTION TYPE IS (N,D)
      NMT104(MED)=NMT104(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AD
      A2=ATAR+AN-AD
      Z1=ZD
      Z2=A2*9.31075E+08
      MT=104
      IF((KZI.EQ.5).OR.(KZI.EQ.6))GO TO 710
      IF((KZI.EQ.8).OR.(KZI.EQ.13))GO TO 710
      IF((KZI.EQ.14).OR.(KZI.EQ.20))GO TO 710
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGND)
      WATE=0.0
      RETURN
  710 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  720 SIGND=0.0
  730 CONTINUE
C       DETERMINE (N,T) CROSS SECTION (MT-105)
      ID=58
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 750
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNT)
      SUMA=SUMA+SIGNT/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 760
C       THE REACTION TYPE IS (N,T)
      NMT105(MED)=NMT105(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AT
      A2=ATAR+AN-AT
      Z1=ZT
      Z2=A2*9.31075E+08
      MT=105
      IF((KZI.EQ.5).OR.(KZI.EQ.13))GO TO 740
      IF(KZI.EQ.20)GO TO 740
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNT)
      WATE=0.0
      RETURN
  740 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  750 SIGNT=0.0
  760 CONTINUE
C       DETERMINE (N,3HE) CROSS SECTION (MT-106)
      ID=59
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 780
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SGN3HE)
      SUMA=SUMA+SGN3HE/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 790
C       THE REACTION TYPE IS (N,3HE)
      NMT106(MED)=NMT106(MED)+1
      QI=Q(ID,IIN)
      KZ1=2
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AHE3
      A2=ATAR+AN-AHE3
      Z1=ZHE3
      Z2=A2*9.31075E+08
      MT=106
      IF(KZI.EQ.20)GO TO 770
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGN3HE)
      WATE=0.0
      RETURN
  770 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  780 SGN3HE=0.0
  790 CONTINUE
C       DETERMINE (N,A) CROSS SECTION (MT-107)
      ID=60
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 810
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNA)
      SUMA=SUMA+SIGNA/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 820
C       THE REACTION TYPE IS (N,A)
      NMT107(MED)=NMT107(MED)+1
      QI=Q(ID,IIN)
      KZ1=2
      KZ2=KZI-KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR+AN-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=107
      IF((KZI.EQ.6).OR.(KZI.EQ.13))GO TO 800
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNA)
      WATE=0.0
      RETURN
  800 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  810 SIGNA=0.0
  820 CONTINUE
C       DETERMINE (N,2A) CROSS SECTION (MT-108)
      ID=61
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 840
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGN2A)
      SUMA=SUMA+SIGN2A/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 850
C       THE REACTION TYPE IS (N,2A)
      NMT108(MED)=NMT108(MED)+1
      QI=Q(ID,IIN)
      KZ1=2
      KZ2=KZI-2*KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR+AN-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=108
C       USE THE ONE PARTICLE EMISSION MODEL AND MULTIPLY THE
C       WEIGHT BY TWO
      IF((KZI.EQ.7).OR.(KZI.EQ.20))GO TO 830
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGN2A)
      WATE=0.0
      RETURN
  830 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  840 SIGN2A=0.0
  850 CONTINUE
C       DETERMINE (N,3A) CROSS SECTION (MT-109)
      ID=62
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 860
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGN3A)
      SUMA=SUMA+SIGN3A/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 870
C       THE REACTION TYPE IS (N,3A)
      NMT109(MED)=NMT109(MED)+1
      QI=Q(ID,IIN)
      KZ1=2
      KZ2=KZI-3*KZ1
      ATAR=AWRI*AN
      A1=AA
      A2=ATAR+AN-AA
      Z1=ZA
      Z2=A2*9.31075E+08
      MT=109
C       USE THE ONE PARTICLE EMISSION MODEL AND MULTIPLY THE
C       WEIGHT BY THREE
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGN3A)
      WATE=0.0
      RETURN
  860 SIGN3A=0.0
  870 CONTINUE
C       DETERMINE (N,2P) CROSS SECTION (MT-111)
      ID=63
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 890
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGN2P)
      SUMA=SUMA+SIGN2P/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 900
C       THE REACTION TYPE IS (N,2P)
      NMT111(MED)=NMT111(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=KZI-2*KZ1
      ATAR=AWRI*AN
      A1=AP
      A2=ATAR+AN-AP
      Z1=ZP
      Z2=A2*9.31075E+08
      MT=111
C       USE THE ONE PARTICLE EMISSION MODEL AND MULTIPLY THE
C       WEIGHT BY TWO
      IF(KZI.EQ.20)GO TO 880
      CALL TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGN2P)
      WATE=0.0
      RETURN
  880 CALL GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,QI,MT)
      WATE=0.0
      RETURN
  890 SIGN2P=0.0
  900 CONTINUE
C       DETERMINE (N,PA) CROSS SECTION (MT-112)
      ID=64
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 910
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SIGNPA)
      SUMA=SUMA+SIGNPA/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 920
C       THE REACTION TYPE IS (N,PA)
      NMT112(MED)=NMT112(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=2
      KZ3=KZI-KZ1-KZ2
      ATAR=AWRI*AN
      A1=AP
      A2=AA
      A3=ATAR+AN-A1
      Z1=ZP
      Z2=ZA
      Z3=A3*9.31075E+08
      MT=112
CZ July 30,1992 Three-Body process added ----
      CALL TREBOD2(D,LD,KZ1,KZ2,KZ3,A1,A2,A3,Z1,Z2,Z3,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGNPA)
      WATE=0.0
      RETURN
  910 SIGNPA=0.0
  920 CONTINUE
C       DETERMINE (N,T2A) CROSS SECTION (MT-113)
      ID=65
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 930
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SGNT2A)
      SUMA=SUMA+SGNT2A/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 940
C       THE REACTION TYPE IS (N,T2A)
      NMT113(MED)=NMT113(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=2
      KZ3=KZI-KZ1-2*KZ2
      ATAR=AWRI*AN
      A1=AT
      A2=AA
      A3=ATAR+AN-A1
      Z1=ZT
      Z2=ZA
      Z3=A3*9.31075E+08
      MT=113
CZ July 30,1992 Three-Body process added ----
      CALL TREBOD2(D,LD,KZ1,KZ2,KZ3,A1,A2,A3,Z1,Z2,Z3,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGNT2A)
      WATE=0.0
      RETURN
  930 SGNT2A=0.0
  940 CONTINUE
C       DETERMINE (N,D2A) CROSS SECTION (MT-114)
      ID=66
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 950
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,SGND2A)
      SUMA=SUMA+SGND2A/SIGTNA*FSUMA
      IF(R.GT.SUMA)GO TO 960
C       THE REACTION TYPE IS (N,D2A)
      NMT114(MED)=NMT114(MED)+1
      QI=Q(ID,IIN)
      KZ1=1
      KZ2=2
      KZ3=KZI-KZ1-2*KZ2
      ATAR=AWRI*AN
      A1=AD
      A2=AA
      A3=ATAR+AN-A1
      Z1=ZD
      Z2=ZA
      Z3=A3*9.31075E+08
      MT=114
CZ July 30,1992 Three-Body process added ----
      CALL TREBOD2(D,LD,KZ1,KZ2,KZ3,A1,A2,A3,Z1,Z2,Z3,ATAR,QI,MT)
      CALL PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,
     +IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SGND2A)
      WATE=0.0
      RETURN
  950 SGND2A=0.0
  960 CONTINUE
      FSUMA = 1./SUMA
      ITRY=ITRY+1
      ISTOP=1
      IF(FSUMA.GT.0.1.AND.FSUMA.LE.10.0) ISTOP=0
      NAEI(IIN)=NAEI(IIN)-1
      IF(ISTOP.EQ.0.AND.ITRY.LE.5)GO TO 20
C       AN ABSORPTION REACTION WAS NOT CHOSEN
      COMM=' COLISN2:AN ABSORPTION REACTION TYPE WAS NOT CHOSEN '
      SIGREC = SIGTNA
      SUMREC = SUMA
      GOTO 980
  970 CONTINUE
      IF(ISTOP.EQ.1)GO TO 980
      ITRY=0
      GO TO 20
  980 CONTINUE
      WRITE(IOUT,'(A80,/,I5,F7.1,I4,/,G18.7,I5,3G10.4)') COMM,
     +      NMED,AWR(IIN),KZ(IIM),
     +      E,MT,
     +      SIGT,SIGREC,SUMREC
      RETURN
      END
*CMZ :  0.90/00 20/07/92  14.28.14  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CTERP2(X1,X2,X,Y1,Y2,Y)
C       THIS ROUTINE PERFORMS LINEAR INTERP2OLATION
      Y=Y2-(X2-X)*(Y2-Y1)/(X2-X1)
      RETURN
      END
*CMZ :  1.04/00 02/02/95  09.21.40  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE EVAPLR2(E,Q,SQ,ATAR,CB,EX)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM AN
C       EVAPORATION SPECTRUM FOR AN LR-FLAG (N,N-PRIME X) REACTION
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      SAVE
C       CONVERT THE COULOMB BARRIER (CB) TO UNITS OF EV
      CB=CB*1.00E+06
C       SET THE EXCITATION ENERGY (Q) TO ITS ABSOLUTE VALUE
      QA=ABS(Q)
C       CALCULATE THE MAXIMUM ENERGY AVAILABLE
      CBI=CB
      EMAX=QA+SQ-CB
      IF(EMAX.GT.0.0)GO TO 10
      CB=0.5*CB
      EMAX=QA+SQ-CB
      IF(EMAX.GT.0.0)GO TO 10
      CB=0.0
      EMAX=QA+SQ-CB
      IF(EMAX.GT.0.0)GO TO 10
      WRITE(IOUT,10000)E,EMAX,QA,SQ,CBI
10000 FORMAT(' MICAP: NEGATIVE MAXIMUM ENERGY CALCULATED IN ROUTINE ',
     1'EVAPLR2 --- INDICATING PROBABLE CROSS SECTION ERROR ALLOWING ',
     2'THE REACTION TO OCCUR',/,10X,'E,EMAX,QA,SQ,CB=',1P5E13.5)
      WRITE(6,*) ' CALOR: ERROR in EVAPLR2 ====> STOP '
      STOP
C       CALCULATE THE NUCLEAR2 TEMPERATURE (THETA)
   10 THETA=4.0161E+03*(SQRT(QA+SQ-CB)/(ATAR**0.8333333))
C       SELECT THE EXIT ENERGY FROM AN EVAPORATION SPECTRUM
   20 R1=FLTRNF2(0)
      R2=FLTRNF2(0)
      W=-ALOG(R1*R2)
      EX=THETA*W
      IF(EX.LE.EMAX)RETURN
C       RESAMPLE 75% OF THE TIME IF EX IS GREATER THAN EMAX
      R=FLTRNF2(0)
      IF(R.LE.0.75)GO TO 20
      EX=EMAX
      RETURN
      END
*CMZ :  0.90/09 03/11/92  15.18.49  by  Christian Zeitnitz
*-- Author :
C*********************************************************************
      FUNCTION FISRNF2(A,B)
C*********************************************************************
C Sample secondary fission neutron energy from Watt spectrum
C taken from ORNL/TM-7631
C CZ 3/11/92
      DIMENSION RNDM(3)
C
      CALL GRNDM(RNDM,3)
      Z=SQRT(-ALOG(RNDM(1)))
      S=6.28319*RNDM(2)
      ALOGR3=ALOG(RNDM(3))
      X=SQRT(A*B)/2.
      E1=A*((Z*COS(S)+X)**2-ALOGR3)
C--  E2=A*((Z*SIN(S)+X)**2-ALOGR3)
C distribution of E1 and E2 are identical
      FISRNF2 = E1
      RETURN
      END
*CMZ :  1.05/03 27/06/2001  17.54.33  by  Christian Zeitnitz
*-- Author :
C*********************************************************************
      FUNCTION FLTRNF2(IX)
C*********************************************************************
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
      FLTRNF2 = RANDC2(ISEED)
      RETURN
      END
*CMZ :  1.05/03 27/06/2001  17.56.54  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   23/10/92
      SUBROUTINE GETENE2(EN,D1,LD2,N)
C sample N times secondary energy distribution and
C store in ENE(*)
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEND.
C
      DIMENSION D1(*),LD2(*)
C
      DO 10 I=1,N
         CALL SECEGY2(EX,D1,EN,LD2)
         ENE(I) = EX
  10  CONTINUE
      RETURN
      END

*CMZ :  1.01/04 10/06/93  14.43.47  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE GETNU2(D,LD,E,LEN,XNU)
C       THIS ROUTINE SELECTS THE AVERAGE NUMBER OF NEUTRONS
C       BORN FROM A FISSION REACTION (I.E. NU-BAR)
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION D(*),LD(*),C(4)
      SAVE
      IP=1
      XNU=0.0
      LNU=LD(IP)
      IP=IP+1
      IF(LNU.NE.1)GO TO 30
C       POLYNOMIAL REPRESENTATION USED TO SPECIFY NU-BAR
C       INITIALIZE THE POLYNOMIAL COEFFICIENTS TO ZERO
      DO 10 I=1,4
         C(I)=0.0
   10 CONTINUE
      NC=LD(IP)
      DO 20 I=1,NC
         C(I)=D(IP+I)
   20 CONTINUE
C       CALCULATE NU-BAR USING POLYNOMIAL COEFFICIENTS
      XNU=C(1)+C(2)*E+C(3)*(E**2)+C(4)*(E**3)
      RETURN
C       TABULATED DATA USED TO SPECIFY NU-BAR
C       CURRENT ENDF/B DATA (VERSION V) ALLOWS ONLY ONE
C       INTERP2OLATION RANGE (NR) AND ONLY LINEAR-LINEAR
C       INTERP2OLABLE DATA (INT=2)
   30 IF(LNU.NE.2)GO TO 40
      NR=LD(IP)
      NP=LD(IP+1)
      IP=IP+2*NR+2
C       SELECT NU-BAR FROM THE TABULATED DATA
C       LINEAR-LINEAR INTERP2OLATION IS ASSUMED AT THIS POINT
      CALL TBSPLT2(D(IP),E,NP,XNU)
      RETURN
   40 WRITE(IOUT,10000)LNU
10000 FORMAT(' MICAP: ERROR IN ROUTINE GETNU2; LNU=',I3)
      WRITE(6,*) ' CALOR: ERROR in GETNU2 ====> STOP'
      STOP
      END
*CMZ :  1.01/04 10/06/93  14.43.48  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   03/08/92
      SUBROUTINE GATPAR2(ID,N,IERR)
C retrieve particle from MPSTOR common
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      IERR = 0
      NN = 0
      NS = 1
   10 CONTINUE
      IF(IDN(NS).EQ.ID) NN = NN + 1
      IF(N.EQ.NN) GOTO 20
      NS = NS + 1
      IF(NS.GT.NPSTOR) THEN
         WRITE(IOUT,'('' MICAP: Cant retrieve particle no. '',I3,      '
     +   //'          '' of type '',I3,''; End of data '')') N,ID
         IERR = 1
         RETURN
      ENDIF
      GOTO 10
   20 CONTINUE
      EP = EN(NS)
      UP = UN(NS)
      VP = VN(NS)
      WP = WN(NS)
      AMP = AMN(NS)
      ZMP = ZMN(NS)
      AGEP = AGEN(NS)
      MTP = MTN(NS)
      RETURN
      END
*CMZ :  1.01/16 18/11/93  09.19.55  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE GRNDST2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,Q,MT)
C       THIS ROUTINE CALCULATES THE EXIT ENERGIES AND DIRECTIONAL
C       COSINES FOR THE CHARGED PARTICLE AND RECOIL NUCLEUS FOR
C       A GROUND STATE TWO-BODY REACTION USING CLASSICAL KINEMATICS
C       AND A MOMEMTUM BALANCE. IT ALSO SETS ALL EXIT PARAMETERS FOR
C       THE COLLISION PRODUCTS AND STORES THEM IN THE RECOIL BANK.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
      NPN = 1
      IF(MT.EQ.108) NPN = 2
      IF(MT.EQ.109) NPN = 3
      IF(MT.EQ.111) NPN = 2
C       CALCULATE THE CONSTANTS USED IN THE KINEMATIIC EQUATIONS
      ZATAR=ATAR*9.31075E+08
      PXO = 0.0
      PYO = 0.0
      PZO = 0.0
C loop over emmited particles
      DO 40  NP=1,NPN
C       ASSUME ISOTROPIC CHARGED PARTICLE EMISSION IN THE CENTER
C       OF MASS COORDINATE SYSTEM
         R=FLTRNF2(0)
         FM=2.0*R-1.0
C       FOR A GROUND STATE REACTION THE RECOIL MASS IS KNOWN EXACTLY
         Z2=ZN+ZATAR-FLOAT(NP)*Z1-Q
         A2=Z2/9.31075E+08
         DENOM=(AN+ATAR)*(A1*FLOAT(NP)+A2)
         ERATIO=EOLD/(EOLD+Q)
         AC=((AN*A2)/DENOM)*ERATIO
         BC=((AN*A1)/DENOM)*ERATIO
         CC=((ATAR*A1)/DENOM)*(1.0+(AN*Q)/(ATAR*(EOLD+Q)))
         DC=((ATAR*A2)/DENOM)*(1.0+(AN*Q)/(ATAR*(EOLD+Q)))
C       CALCULATE THE CHARGED PARTICLE AND RECOIL NUCLEUS IN THE
C       LABORATORY COORDINATE SYSTEM
         E1=(EOLD+Q)*(BC+DC+(2.0*SQRT(AC*CC))*FM)
         E2=(EOLD+Q)*(AC+CC-(2.0*SQRT(AC*CC))*FM)
C       CALCULATE THE CHARGED PARTICLE ENERGY AND VELOCITY IN THE
C       CENTER OF MASS COORDINATE SYSTEM
         E1CM=(Z2/(Z1+Z2))*((ZATAR/(ZN+ZATAR))*EOLD+Q)
         V1CM=SQRT((2.0*E1CM)/Z1)
C       CALCULATE THE VELOCITY OF THE CENTER OF MASS
         VCM=SQRT(2.0*ZN*EOLD)/(ZN+ZATAR)
C       CONVERT THE COSINE OF THE SCATTERING ANGLE IN THE CENTER OF
C       MASS COORDINATE SYSTEM TO THE LABORATORY COORDINATE SYSTEM
         FM=(V1CM*FM+VCM)/(SQRT(((V1CM*FM+VCM)**2)+ ((V1CM*(1.0-FM**2))
     +   **2)))
C       CALCULATE THE CHARGED PARTICLE EXIT DIRECTIONAL COSINES
         SINPSI=SQRT(1.0-FM**2)
         CALL AZIRN2(SINETA,COSETA)
         STHETA=1.0-UOLD**2
         IF(STHETA)20,20,10
   10    STHETA=SQRT(STHETA)
         COSPHI=VOLD/STHETA
         SINPHI=WOLD/STHETA
         GO TO 30
   20    COSPHI=1.0
         SINPHI=0.0
         STHETA=0.0
   30    U1=UOLD*FM-COSETA*SINPSI*STHETA
         V1=VOLD*FM+UOLD*COSPHI*COSETA*SINPSI-SINPHI*SINPSI*SINETA
         W1=WOLD*FM+UOLD*SINPHI*COSETA*SINPSI+COSPHI*SINPSI*SINETA
         S=1.0/SQRT(U1**2+V1**2+W1**2)
         U1=U1*S
         V1=V1*S
         W1=W1*S
         PPO = SQRT(2.0*Z1*E1)
         PXO = PXO + U1*PPO
         PYO = PYO + V1*PPO
         PZO = PZO + W1*PPO
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
         XR=X
         YR=Y
         ZR=Z
         WATER=WTBC
         NZR=KZ1
         AGER=AGE
         NCOLR=NCOL
         MTNR=MT
         AR=A1
         ENIR=EOLD
         UNIR=UOLD
         VNIR=VOLD
         WNIR=WOLD
         ENOR=0.0
         UNOR=0.0
         VNOR=0.0
         WNOR=0.0
         WTNR=0.0
         QR=Q
         UR=U1
         VR=V1
         WR=W1
         ER=E1
C       STORE THE CHARGED PARTICLE IN THE RECOIL BANK
         EP = ER
         UP = UR
         VP = VR
         WP = WR
         AMP = AR
         ZMP = FLOAT(NZR)
         AGEP = AGE
         MTP = MT
         CALL STOPAR2(IDHEVY,NHEVY)
   40 CONTINUE
C       CALCULATE THE TOTAL MOMENTUM BEFORE THE COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*UOLD-PXO
      PRY=PI*VOLD-PYO
      PRZ=PI*WOLD-PZO
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      U2=PRX/PR
      V2=PRY/PR
      W2=PRZ/PR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      XM = A2 * 931.075E6
      E2 = SQRT(PR**2+XM**2) - XM
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ2
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A2
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=0.0
      UNOR=0.0
      VNOR=0.0
      WNOR=0.0
      WTNR=0.0
      QR=Q
      UR=U2
      VR=V2
      WR=W2
      ER=E2
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AMP = AR
      ZMP = FLOAT(NZR)
      AGEP = AGE
      MTP = MT
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.04/05 16/08/95  15.27.07  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   28/07/92
      SUBROUTINE GTMED2(MEDGEA,MEDMOR)
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
C get MICAP material number
      DO 10 I=1,MEDIA
         IF(LD(LGE2MO+I).EQ.MEDGEA) THEN
            MEDMOR = I
            GOTO 20
         ENDIF
   10 CONTINUE
      WRITE(IOUT,'('' MICAP GTMED2: GEANT Medium '',I5, '
     +        //' '' not found ==> STOP'')') MEDGEA
      STOP
   20 RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.32  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE INTERP2(X,Y,X1,Y1,X2,Y2,INT)
C       THIS ROUTINE PERFORMS THE INTERP2OLATION ACCORDING
C       TO THE ENDF/B INTERP2OLATION SCHEME INT
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      SAVE
      IF(INT.LT.1.OR.INT.GT.5)GO TO 60
      IF(X2.EQ.X1)GO TO 10
      GO TO (10,20,30,40,50),INT
   10 Y=Y1
      RETURN
   20 Y=Y1+(X-X1)*(Y2-Y1)/(X2-X1)
      RETURN
   30 IF(X1.EQ.0.0.OR.X2.EQ.0.0)GO TO 20
      Y=Y1+ALOG(X/X1)*(Y2-Y1)/ALOG(X2/X1)
      RETURN
   40 IF(Y1.EQ.0.0.OR.Y2.EQ.0.0)GO TO 20
      Y=Y1*EXP((X-X1)*ALOG(Y2/Y1)/(X2-X1))
      RETURN
   50 IF(Y1.EQ.0.0.OR.Y2.EQ.0.0)GO TO 30
      IF(X1.EQ.0.0.OR.X2.EQ.0.0)GO TO 40
      Y=Y1*EXP(ALOG(X/X1)*ALOG(Y2/Y1)/ALOG(X2/X1))
      RETURN
   60 WRITE(IOUT,10000)INT
10000 FORMAT(' MICAP: INTERP2-INVALID INTERP2OLATION SCHEME',I11)
      WRITE(6,*) ' CALOR: ERROR in INTERP2 ====> STOP '
      STOP
      END
*CMZ :  1.01/04 10/06/93  14.43.48  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE INTSCH2(IFSE,I,IS,NR)
C       THIS ROUTINE DETERMINES THE INTERP2OLATION SCHEME
C       ACCORDING TO ENDF/B-V FORMATTED DATA FILES
      DIMENSION IFSE(*)
      DO 10 J=1,NR
         J1=3+2*(J-1)
         NPTS=IFSE(J1)
         IF(I.LE.NPTS)GO TO 20
   10 CONTINUE
   20 IS=IFSE(J1+1)
      RETURN
      END
*CMZ :  1.04/00 02/02/95  09.26.26  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ISOTPE2(D,LD,KM,RHO,IN,IDICTS,LDICT,E,TSIG,NMED,
     +                  IIN,IIM)
C       THIS ROUTINE DETERMINES WHICH ISOTOPE HAS BEEN STRUCK
C       IN MEDIA NMED
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
C
      DIMENSION D(*),LD(*),KM(*),RHO(*),IN(*),IDICTS(NNR,NNUC),
     +          LDICT(NNR,NNUC)
      SAVE
C
      R=FLTRNF2(0)
      NOA=0
      SUM=0.
   20 DO 30 K=1,NMIX
         IF(KM(K).NE.NMED)GO TO 30
C       DETERMINE ISOTOPE NUMBER
         K1=IN(K)
         K2=K
C       DETERMINE TOTAL CROSS SECTION FOR THIS ISOTOPE
         LS1=IDICTS(1,K1)+LMOX2
         L1=LDICT(1,K1)
         LEN=L1/2
         CALL TBSPLT2(D(LS1),E,LEN,X)
         SUM=SUM+X*RHO(K)
C       CHECK TO SEE IF THIS ISOTOPE WAS HIT
         IF(R.LE.SUM/TSIG)GO TO 40
   30 CONTINUE
C       AN ISOTOPE WAS NOT CHOSEN, TRY AGAIN
      NOA=NOA+1
      IF(NOA.GT.5)GO TO 50
      SUM=0.0
      R=FLTRNF2(0)
      GO TO 20
   40 IIN=K1
      IIM=K2
      RETURN
   50 WRITE(IOUT,10000)NMED,TSIG
10000 FORMAT(' MICAP: AN ISOTOPE WAS NOT CHOSEN IN 5 ATTEMPTS IN ',
     +'ROUTINE ISOTPE2',/,3X,'MEDIUM=',I5,5X,'MACROSCOPIC XSEC=',
     +1PE12.4)
      WRITE(IOUT,10100)R,SUM,TSIG,X,E,RHO(K2),NMED,K1,K2
10100 FORMAT('0',1X,1P6E12.4,3I10)
      WRITE(6,*) ' CALOR: ERROR in ISOTPE2 =====> STOP '
      STOP
      END
*CMZ :  1.01/04 10/06/93  14.43.48  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE LABNF2(D,LD,FM,AWR,KZ,Q,LIFLAG)
C       THIS ROUTINE CALCULATES THE DIRECTIONAL COSINES FOR THE
C       NEUTRON BORN FROM THE FISSION REACTION.  THIS VERSION OF
C       THE PROGRAM WILL TREAT A FISSION REACTION AS A SCATTERING
C       EVENT WITH THE NEUTRON EMERGING WITH A MODIFIED WEIGHT OF
C       WATE*NU-BAR.  NO PROVISIONS ARE MADE AT THIS TIME TO
C       CALCULATE THE FISSION FRAGMENTS PARAMETERS, HOWEVER A HEAVY
C       RECOIL ION WILL BE STORED (FOR ANALYSIS PURPOSES) WITH
C       ENERGY AND DIRECTION COSINES EQUAL TO ZERO.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*),FM(*)
      SAVE
      MT=18
C       CALCULATE THE NEUTRON EXIT DIRECTIONAL COSINES
      POX = 0.0
      POY = 0.0
      POZ = 0.0
      DO 40 KN=1,INEU
         IF(LIFLAG.EQ.1) THEN
            CALL GTISO2(UP,VP,WP)
         ELSE
            SINPSI=SQRT(1.0-FM(KN)**2)
            CALL AZIRN2(SINETA,COSETA)
            STHETA=1.0-UOLD**2
            IF(STHETA)20,20,10
   10       STHETA=SQRT(STHETA)
            COSPHI=VOLD/STHETA
            SINPHI=WOLD/STHETA
            GO TO 30
   20       COSPHI=1.0
            SINPHI=0.0
            STHETA=0.0
   30       UP=UOLD*FM(KN)-COSETA*SINPSI*STHETA
            VP=VOLD*FM(KN)+UOLD*COSPHI*COSETA*SINPSI-SINPHI* SINPSI*
     +      SINETA
            WP=WOLD*FM(KN)+UOLD*SINPHI*COSETA*SINPSI+COSPHI* SINPSI*
     +      SINETA
            S=1.0/SQRT(UP**2+VP**2+WP**2)
            UP=UP*S
            VP=VP*S
            WP=WP*S
         ENDIF
         AGEP = AGE
         EP = ENE(KN)
C use only first neutron for recoil calculation in order to ensure
C correct recoil nucleus energy spectrum
         IF(KN.EQ.1) THEN
            PP = SQRT(EP**2 + 2.0*EP*ZN)
            POX = POX + PP*UP
            POY = POY + PP*VP
            POZ = POZ + PP*WP
         ENDIF
         MTP = MT
         CALL STOPAR2(IDNEU,NNEU)
   40 CONTINUE
C       SET THE HEAVY RECOIL ION PARAMETERS FOR ANALYSIS TAPE
   50 PI=SQRT(2.0*ZN*EOLD)
      PIX=PI*UOLD
      PIY=PI*VOLD
      PIZ=PI*WOLD
      PRX=PIX-POX
      PRY=PIY-POY
      PRZ=PIZ-POZ
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
      UR=PRX/PR
      VR=PRY/PR
      WR=PRZ/PR
      AR=AWR*AN+AN-INEU*AN
      XM=AR*931.075E6
      ER=SQRT(PR**2+XM**2)-XM
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AMP = AR
      ZMP = FLOAT(KZ)
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.32  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE LR2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,Q,SQ,ID,MT)
C       THIS ROUTINE CALCULATES THE EXIT ENERGIES AND DIRECTIONAL
C       COSINES FOR THE CHARGED PARTICLE AND RECOIL NUCLEUS FOR
C       A TWO-BODY REACTION USING AN EVAPORATION SPECTRUM AND
C       MOMEMTUM BALANCE.  IT ALSO SETS ALL EXIT PARAMETERS FOR
C       THE COLLISION PRODUCTS AND STORES THEM IN THE RECOIL BANK.
C       THE TWO BODY REACTION RESULTS FROM THE BREAK-UP OF A NUCLEUS
C       LEFT IN AN EXCITED STATE BY AN INELASTIC COLLISION
C       DESIGNATED BY A LR-FLAG IN THE INELASTIC RESOLVED DATA
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
C       CALCULATE THE CONSTANTS USED IN THE KINEMATIIC EQUATIONS
      ZATAR=ATAR*9.31075E+08
C       FOR A CARBON-ALPHA EMISSION THE RECOIL MASS IS KNOWN EXACTLY
      IF(KZ1+KZ2.EQ.6)Z2=ZATAR-Z1-SQ
      IF(KZ1+KZ2.EQ.6)A2=Z2/9.31075E+08
C       TRANSFER THE RECOILING COMPOUND NUCLEUS PARAMETERS OUT OF
C       COMMON RECOIL FOR USE IN THE MOMENTUM BALANCE EQUATIONS
      ERCN=ER
      URCN=UR
      VRCN=VR
      WRCN=WR
      ARCN=AR
      NZRCN=NZR
      ZARCN=ARCN*9.31075E+08
      IF(MT.EQ.23)GO TO 10
C       CALCULATE THE COULOMB BARRIER (CB)
      CALL BARIER2(KZ1,KZ2,A1,A2,CB)
C       CALCULATE THE ENERGY AVAILABLE IN THE CENTER OF MASS (EAV)
      CALL EVAPLR2(E,Q,SQ,ATAR,CB,EX)
      EAV=EX+CB
      GO TO 30
   10 IF((ID.EQ.54).AND.(KZ1+KZ2.EQ.6))GO TO 20
      EAV=ABS(Q)+SQ
      GO TO 30
   20 Q=EOLD-E-ERCN
      IF(Q.LE.ABS(SQ))Q=7.65300E+06
      EAV=Q+SQ
   30 CONTINUE
C       CALCULATE THE CHARGED PARTICLE ENERGY USING CONSERVATION
C       OF MOMENTUM (CENTER OF MASS SYSTEM)
      E1CM=(A2/(A1+A2))*EAV
C       ASSUME ISOTROPIC CHARGED PARTICLE EMISSION IN THE CENTER
C       OF MASS COORDINATE SYSTEM
      R=FLTRNF2(0)
      FM=2.0*R-1.0
C       CALCULATE THE VELOCITY OF THE CENTER OF MASS AND THE
C       CHARGED PARTICLE IN THE CENTER OF MASS SYSTEM
      VCM=SQRT((2.0*ERCN)/ZARCN)
      V1CM=SQRT((2.0*E1CM)/Z1)
C       CALCULATE THE CHARGED PARTICLE ENERGY IN THE LABORATORY
C       COORDINATE SYSTEM
      E1=0.5*Z1*(VCM**2+V1CM**2+VCM*V1CM*FM)
C       CONVERT THE COSINE OF THE SCATTERING ANGLE IN THE CENTER OF
C       MASS COORDINATE SYSTEM TO THE LABORATORY COORDINATE SYSTEM
      FM=(V1CM*FM+VCM)/(SQRT(((V1CM*FM+VCM)**2)+((V1CM*(1.0-FM**2))
     1**2)))
C       CALCULATE THE CHARGED PARTICLE EXIT DIRECTIONAL COSINES
      SINPSI=SQRT(1.0-FM**2)
      CALL AZIRN2(SINETA,COSETA)
      STHETA=1.0-URCN**2
      IF(STHETA)50,50,40
   40 STHETA=SQRT(STHETA)
      COSPHI=VRCN/STHETA
      SINPHI=WRCN/STHETA
      GO TO 60
   50 COSPHI=1.0
      SINPHI=0.0
      STHETA=0.0
   60 U1=URCN*FM-COSETA*SINPSI*STHETA
      V1=VRCN*FM+URCN*COSPHI*COSETA*SINPSI-SINPHI*SINPSI*SINETA
      W1=WRCN*FM+URCN*SINPHI*COSETA*SINPSI+COSPHI*SINPSI*SINETA
      S=1.0/SQRT(U1**2+V1**2+W1**2)
      U1=U1*S
      V1=V1*S
      W1=W1*S
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ1
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A1
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
      UR=U1
      VR=V1
      WR=W1
      ER=E1
C       STORE THE CHARGED PARTICLE IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      AMP = AR
      ZMP = FLOAT(NZR)
      CALL STOPAR2(IDHEVY,NHEVY)
C       CALCULATE THE TOTAL MOMENTUM BEFORE THE COLLISION
C       COMPOUND NUCLEUS MOMENTUM BEFORE THE COLLISION (PI) EQUALS
C       THE TOTAL MOMENTUM
      PI=SQRT(2.0*ZARCN*ERCN)
C       CALCULATE THE TOTAL MOMEMTUM OF THE EXIT CHARGED PARTICLE
      PO=SQRT(2.0*Z1*E1)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*URCN-PO*U1
      PRY=PI*VRCN-PO*V1
      PRZ=PI*WRCN-PO*W1
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      U2=PRX/PR
      V2=PRY/PR
      W2=PRZ/PR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      XM = A2*931.075E6
      E2 = SQRT(PR**2+XM**2) - XM
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ2
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A2
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
      UR=U2
      VR=V2
      WR=W2
      ER=E2
      IF((KZ2.EQ.4).AND.(MT.EQ.23))RETURN
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      AMP = AR
      ZMP = FLOAT(NZR)
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.48  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE LRNORM2(D,LD,IDICTS,LDICT,LR,EOLD,MT,IIN,XSLR)
C       THIS ROUTINE IS DESIGNED TO ADJUST THE NEUTRON CROSS SECTION
C       USED TO CALCULATE THE PHOTON2 MULTIPLICITY WHEN THE
C       INELASTIC RESOLVED DATA CONTAINS LR-FLAGS DESIGNATING
C       CHARGED PARTICLE EMISSION
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MCROSS.
      COMMON/MCROSS/SIGT,SIGTNS,SIGTNA,SIGNES,SIGNIS,SGNISD,SGNISC,
     1SIGN2N,SIGN3N,SIGNNA,SGNN3A,SGN2NA,SIGNNP,SIGNF,SIGNG,SIGNP,
     2SIGND,SIGNT,SGN3HE,SIGNA,SIGN2A,SIGN3A,SIGN2P,SIGNPA,SGNT2A,
     3SGND2A
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      DIMENSION D(*),LD(*),IDICTS(NNR,NNUC),LDICT(NNR,NNUC),
     +LR(NQ,NNUC)
      SAVE
C       INITIALIZE VARIABLES USED IN THE CALCULATION
      SUM=0.0
      SUM4=SIGNIS
C       DETERMINE (N,N") CROSS SECTION AND LR-FLAG
      DO 10 I=14,54
         L1=LDICT(I,IIN)
         IF(L1.EQ.0)GO TO 10
         LS1=IDICTS(I,IIN)+LMOX2
         LEN=L1/2
         CALL XSECNU2(D,LEN,EOLD,SIG,LS1,L1)
         LRI=LR(I,IIN)
         IF(LRI.EQ.MT)SUM=SUM+SIG
         IF(LRI.EQ.22)SUM4=SUM4-SIG
         IF(LRI.EQ.23)SUM4=SUM4-SIG
         IF(LRI.EQ.28)SUM4=SUM4-SIG
   10 CONTINUE
      XSLR=SUM
      IF(MT.EQ.4)XSLR=SUM4
      RETURN
      END
*CMZ :  1.04/05 16/08/95  14.52.27  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   25/05/94
      SUBROUTINE MATISO2(IZ,IA,NI,IDISO,FSINGL,NUNIT)
C
C Search array MATIDS for the isotopes which have to be taken
C into account for the element described by IZ and IA
C
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
C
      DIMENSION IDISO(20,2)
      LOGICAL FSINGL
C
      IF(IZ.GT.0.AND.IZ.LE.100.and.MATIDS(IZ,1,1).GT.0) THEN
        ID   = IZ*1000+IA
        IF = 0
        IC = 0
        IDIFF = 1000000
C
C check first if selected isotope available
        DO 10 I=2,MATIDS(IZ,1,1)+1
          IF( MATIDS(IZ,I,1).EQ.ID  .AND.
     +       (MATIDS(IZ,I,2).EQ.100 .OR. FSINGL)) IF = I
          IF( IABS(MATIDS(IZ,I,1)-ID).LT.IDIFF) THEN
             IDIFF = IABS(MATIDS(IZ,I,1)-ID)
             IC = I
          ENDIF
          IDISO(I-1,1) = MATIDS(IZ,I,1)
          IDISO(I-1,2) = MATIDS(IZ,I,2)
   10   CONTINUE
        NI = 1
C the unit number on which the x-section is stored
        NUNIT = MATIDS(IZ,1,2)
        IF(.NOT. FSINGL) THEN
          IF(IF .EQ. 0) THEN
C no matching isotope found. Look for closest one
             IF(MATIDS(IZ,2,2).NE.100) NI = MATIDS(IZ,1,1)
          ELSE
C matching isotope found
            IDISO(1,1) = MATIDS(IZ,IF,1)
            IDISO(1,2) = 100
          ENDIF
        ELSE
          IDISO(1,1) = MATIDS(IZ,IC,1)
          IDISO(1,2) = 100
        ENDIF
      ELSE
         WRITE(IOUT,'('' MATISO2: Error in neutron x-section '',   '
     +         //'    ''file detected - Z = '',I4)') IZ
         WRITE(6,'('' MICAP : Error in x-section file '',       '
     +         //'    '' detected -> STOP '')')
         STOP
      ENDIF
      RETURN
      END
*CMZ :  1.05/03 27/06/2001  18.31.28  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE MICAP
C
C CALOR-GEANT interface COMMON
*KEEP,CALGEA.
C***************************************************************
C
C       CALOR-GEANT Interface common
C
C parameters of incident particle :
C                   IPinc   = particle type a la CALOR
C                   Einc    = kinetic energy
C                   Uinc(3) = direction cosines
C material parameters:
C                   NCEL    = number of elements in mixture (NMTC)
C                             GEANT material no. for MICAP
C                   Amed(I) = mass number
C                   Zmed(I) = charge number
C                   Dmed(I) = Atoms/cm**3 * 1E-24
C                   Hden    = Atoms/cm**3 * 1E-24
C                             of H-Atoms in mixture
C
C particle stack:
C            NPHETC           = number of particles
C            Ekinet(1:NPHETC) = kinetic energy of part.
C            IPCAL(1:NPHETC)  = particle type a la CALOR (extended)
C            UCAL(1:NPHETC,3) = direction cosines
C            CALTIM(1:NPHETC) = age of particle (nsec)
C
C            ATARGT = A no. of target nucleus
C            ZTARGT = Z no. of target nucleus
C
C return of residual nucleus information
C            NRECOL  = no. of heavy recoil products
C            Amed(I) = mass number of residual nucleus
C            Zmed(I) = charge number "          "
C            EXmed   = exitation energy of nucleus
C            ERmed(I)= recoil energy of nucleus
C            IntCal  = type of interaction (GEANT NAMEC index)
C return of cross section of hadronic interaction (CALSIG called)
C            SIG =  x-section
C
C set by CALSIG:
C            ICPROC = -1   undefined
C                   =  0   NMTC called for cross-section
C                   =  1   MICAP called for cross-section
C                   =  2   SKALE(NMTC at 3 GeV) called for cross-section
C                   =  3   FLUKA called for cross-section
C            KCALL : same coding as ICPROC, but is only valid after a
C                    call to GCALOR
C       18/8/92  C.Zeitnitz University of Arizona
C****************************************************************
C
      PARAMETER(EMAXP  = 3.495)
      PARAMETER(EMAXPI = 2.495)
C transition upper limit (GeV) NMTC-FLUKA
      PARAMETER(ESKALE = 10.0)
      PARAMETER(MXCP = 300)
C
      COMMON/ CALGEA / IPINC  , EINC       , UINC(3)   ,NCEL        ,
     +                 HDEN   , AMED(100)  , ZMED(100) ,DMED(100)   ,
     +                 NPHETC ,EKINET(MXCP),IPCAL(MXCP),UCAL(MXCP,3),
     +                 INTCAL , EXMED      , ERMED(100),SIG         ,
     +                 CALTIM(MXCP), ICPROC, NRECOL    ,KCALL       ,
     +                 ATARGT , ZTARGT
C
*KEND.
C MICAP commons
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MPOINT.
      COMMON/MPOINT/LMAG1,LFP1,LFP2,LFP3,LFP4,LFP5,LFP6,LFP7,LFP8,
     + LFP9,LFP10,LFP11,LFP12,LFP13,LFP14,LFP140,LFP15,LFP16,LFP17,
     + LFP18,LFP19,LFP20,LFP21,LFP22,LFP23,LFP24,LFP25,LFP26,
     + LFP27,LFP28,LFP29,LFP30,LFP31,LFP32,LFP33,LFP34,LFP35,
     + LFP36,LFP37,LFP38,LFP39,LFP40,LFP41,LFP42,LFP43,LFP44,
     + LFP45,LFP46,LFP47,LFP48,LFP49,LFP50,LFP51,LFP52,LFP53,
     + LFP18A,LFP210
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,CMAGIC.
      PARAMETER(NMAGIC=123456789)
*KEND.
C
C convert Z,A of recoil to CALOR particle code
C only p = 0, D = 7, T = 8, He3 = 9, alpha=10
      DIMENSION NPART(4,0:2)
      DATA ((NPART(I,J),I=1,4),J=0,2)/1 ,-1 ,-1 , -1,
     +                                0 , 7 , 8 , -1,
     +                               -1 ,-1 , 9 , 10/
      LOGICAL NOP
      SAVE
C first check, if ZEBRA still in order
      IF(LD(LMAG1).NE.NMAGIC.OR.LD(LMAG2).NE.NMAGIC) THEN
         WRITE(6,*) ' CALOR: ZEBRA banks screwed up --> STOP'
         WRITE(IOUT,'('' MICAP: Magic number '',I12,'' not found: '',  '
     +   //'      2I12)') NMAGIC,LD(LMAG1),LD(LMAG2)
         STOP
      ENDIF
C       THIS ROUTINE PERFORMS THE RANDOM WALK FOR ALL PARTICLES
   10 CONTINUE
C get material and particle information
      U = UINC(1)
      V = UINC(2)
      W = UINC(3)
      X = 0.0
      Y = 0.0
      Z = 0.0
      BLZNT = 1
      WATE = 1.0
      AGE = 0.0
      NREG = 1
      WTBC = 1.0
C Energy MeV -> eV
      E = EINC * 1.E6
C Material number a la GEANT
      NMED = NCEL
      NMEM=1
C reset counter of heavy/charged and gamma bank
      NMEMR = 0
      NMEMG = 0
      INALB=0
      EOLD=E
      UOLD=U
      VOLD=V
      WOLD=W
      OLDWT=WATE
      XOLD=X
      YOLD=Y
      ZOLD=Z
      BLZON=BLZNT
      MEDOLD=NMED
      OLDAGE=AGE
      I=1
      CALL GTMED2(NMED,IMED)
C get total cross-section
      CALL NSIGTA2(E,NMED,TSIG,D,LD(LFP32),LD(LFP33))
C       DETERMINE WHICH ISOTOPE HAS BEEN HIT
      CALL ISOTPE2(D,LD,LD(LFP10),D(LFP12),LD(LFP16),LD(LFP26),LD(LFP27)
     +             ,E,TSIG,IMED,IIN,IIM) 
C       THE PARAMETER (IIN) IS THE POINTER FOR ARRAYS DIMENSIONED BY
C       (NNUC) AND THE PARAMETER (IIM) IS THE POINTER FOR ARRAYS
C       DIMENSIONED BY (NMIX)
      LD(LFP42+IMED-1)=LD(LFP42+IMED-1)+1
      INEU = 0
      NNEU = 0
      NHEVY = 0
      NGAMA = 0
      NPSTOR = 0
      ATARGT = D(LFP34+IIN-1)*1.008665
      ZTARGT = FLOAT(LD(LFP13+IIM-1))
      CALL COLISN2(D,LD,LD(LFP20),LD(LFP21),LD(LFP22),LD(LFP23),
     + D(LFP24),LD(LFP24),
     + LD(LFP25),LD(LFP26),LD(LFP27),LD(LFP28),LD(LFP29),LD(LFP30),
     + LD(LFP31),D(LFP34),D(LFP35),LD(LFP41),LD(LFP41+NNUC),
     + LD(LFP42),LD(LFP42+MEDIA),LD(LFP42+2*MEDIA),LD(LFP42+3*MEDIA),
     + LD(LFP42+4*MEDIA),LD(LFP42+5*MEDIA),LD(LFP42+6*MEDIA),
     + LD(LFP42+7*MEDIA),LD(LFP42+8*MEDIA),LD(LFP42+9*MEDIA),
     + LD(LFP42+10*MEDIA),LD(LFP42+11*MEDIA),LD(LFP42+12*MEDIA),
     + LD(LFP42+13*MEDIA),LD(LFP42+14*MEDIA),LD(LFP42+15*MEDIA),
     + LD(LFP42+16*MEDIA),LD(LFP42+17*MEDIA),LD(LFP42+18*MEDIA),
     + LD(LFP42+19*MEDIA),LD(LFP42+20*MEDIA),LD(LFP42+21*MEDIA),
     + LD(LFP42+22*MEDIA),LD(LFP45),LD(LFP46),LD(LFP13),
     + LD(LFP35+NQ*NNUC),D(LFP35+2*NQ*NNUC),IIN,IIM)
      CALL BANKR2(D,LD,5)
C -------- fill return arrays with generated particles ---------------
C first heavy/charged particles
   20 NPHETC = 0
      NRECOL = 0
      ERMED(1) = 0.0
      EETOT = 0.0
C -------- store  neutrons -------------------------------------
      INTCAL = 0
C
      DO 30  N=1,NNEU
         CALL GATPAR2(IDNEU,N,IERR)
         IF(IERR.EQ.0) THEN
            NPHETC = NPHETC + 1
            IF(NPHETC.GT.MXCP) NPHETC=MXCP
            IPCAL(NPHETC) = 1
C kinetic energy in MeV
            EKINET(NPHETC) = EP * 1.E-6
            UCAL(NPHETC,1) = UP
            UCAL(NPHETC,2) = VP
            UCAL(NPHETC,3) = WP
            CALTIM(NPHETC) = AGEP
         ENDIF
   30 CONTINUE
C -------- store heavy recoil products ------------------------
      DO 40  N=1,NHEVY
         CALL GATPAR2(IDHEVY,N,IERR)
         IF(IERR.EQ.0) THEN
C check particle type
            MA = NINT(AMP)
            MZ = NINT(ZMP)
            NOP = .TRUE.
            IF(MA.LE.4.AND.MZ.LE.2) THEN
               IF(NPART(MA,MZ).GT.-1) NOP = .FALSE.
            ENDIF
            IF(NOP) THEN
C get heavy recoil nucleus
               NRECOL = NRECOL + 1
               AMED(NRECOL) = AMP
               ZMED(NRECOL) = ZMP
               ERMED(NRECOL)= EP * 1.E-6
               GOTO 40
            ENDIF
C store particle type
            NPHETC = NPHETC + 1
            IF(NPHETC.GT.MXCP) NPHETC=MXCP
            IPCAL(NPHETC) = NPART(MA,MZ)
C kinetic energy in MeV
            EKINET(NPHETC) = EP * 1.E-6
            UCAL(NPHETC,1) = UP
            UCAL(NPHETC,2) = VP
            UCAL(NPHETC,3) = WP
            CALTIM(NPHETC) = AGEP
         ENDIF
   40 CONTINUE
C
C----------- get generated gammas --------------------
      DO 50  N=1,NGAMA
         CALL GATPAR2(IDGAMA,N,IERR)
         IF(IERR.EQ.0) THEN
            NG = NG + 1
            NPHETC = NPHETC + 1
            IF(NPHETC.GT.MXCP) NPHETC=MXCP
            IPCAL(NPHETC) = 11
            EKINET(NPHETC) = EP*1.E-6
            UCAL(NPHETC,1) = UP
            UCAL(NPHETC,2) = VP
            UCAL(NPHETC,3) = WP
            CALTIM(NPHETC) = AGEP
C nucleus is in ground state !
            EXMED = 0.0
         ENDIF
   50 CONTINUE
      IF (MTP        .EQ.         2) THEN
         INTCAL = 13
      ELSEIF (MTP    .EQ.        18) THEN
         IF (NHEVY.GT.0) INTCAL = 15
      ELSEIF (MTP    .LT.       100) THEN
         IF (NNEU .GT.0) INTCAL = 20
      ELSEIF (MTP    .EQ.       102) THEN
         INTCAL = 18
      ELSEIF (MTP    .GE.       100) THEN
         IF (NHEVY+NGAMA.GT.0) INTCAL = 16
      ENDIF
      IF(NNEU+NHEVY+NGAMA.GT.0.AND.INTCAL.EQ.0) INTCAL=12
      RETURN
      END
*CMZ :  1.05/03 29/08/2001  14.35.16  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   21/07/92
      SUBROUTINE MORINI
C**************************************************************
C                  Initialize MICAP
C                  ================
C Called by : CALINI
C
C Purpose : setup cross-section tables and initialize pointer
C           print flags etc.
C
C Author : C.Zeitnitz
C
C last modification: Changed in order to read new x-section file
C
C
C for details see MICAP manual ORNL/TM-10340
C*************************************************************
C MICAP commons
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MPOINT.
      COMMON/MPOINT/LMAG1,LFP1,LFP2,LFP3,LFP4,LFP5,LFP6,LFP7,LFP8,
     + LFP9,LFP10,LFP11,LFP12,LFP13,LFP14,LFP140,LFP15,LFP16,LFP17,
     + LFP18,LFP19,LFP20,LFP21,LFP22,LFP23,LFP24,LFP25,LFP26,
     + LFP27,LFP28,LFP29,LFP30,LFP31,LFP32,LFP33,LFP34,LFP35,
     + LFP36,LFP37,LFP38,LFP39,LFP40,LFP41,LFP42,LFP43,LFP44,
     + LFP45,LFP46,LFP47,LFP48,LFP49,LFP50,LFP51,LFP52,LFP53,
     + LFP18A,LFP210
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,CMAGIC.
      PARAMETER(NMAGIC=123456789)
*KEEP,CERRCM.
      LOGICAL CERRF
      COMMON/CERRCM/CERRF,IERRU
*KEEP,CAMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
*KEND.
C GEANT common
*KEEP,GCCUTS.
      COMMON/GCCUTS/CUTGAM,CUTELE,CUTNEU,CUTHAD,CUTMUO,BCUTE,BCUTM
     +             ,DCUTE ,DCUTM ,PPCUTM,TOFMAX,GCUTS(5)
C
*KEEP,GCFLAG.
      COMMON/GCFLAG/IDEBUG,IDEMIN,IDEMAX,ITEST,IDRUN,IDEVT,IEORUN
     +        ,IEOTRI,IEVENT,ISWIT(10),IFINIT(20),NEVENT,NRNDM(2)
      COMMON/GCFLAX/BATCH, NOLOG
      LOGICAL BATCH, NOLOG
C
*KEND.
C pointer to material/mixture bank (NMATE,JMATE)
*KEEP,GCNUM.
      COMMON/GCNUM/NMATE ,NVOLUM,NROTM,NTMED,NTMULT,NTRACK,NPART
     +            ,NSTMAX,NVERTX,NHEAD,NBIT
      COMMON /GCNUMX/ NALIVE,NTMSTO
C
*KEND.
C
      COMMON / QUEST / IQUEST(100)
C
C  Avogadro number multiplied by 1.E-24
      PARAMETER(XNAVO = 0.60221367)
C
      DIMENSION A(100),AGEA(100),Z(100),DEN(100),MID(100,2),IDI(20,2)
      CHARACTER*100 XSFILE
      CHARACTER*4   CNAME
      CHARACTER*70 CCOMM
      CHARACTER*100 CHROOT
      LOGICAL OPENED,EXISTS,IFOUND,FMIST,FSINGL,FMIFL
C
C set GEANT initialization flag
      IFINIT(7) = 1
C
C  neutron energy cut (eV)
      ECUT = CUTNEU * 1.E9
C get time cut off from GEANT
      TCUT = TOFMAX
C temperature for thermal neutron xsection (Kelvin)
C only temporary constant !!!
      TEMP = 300.0
C xsection file unit
      MICROS = 31
C open MICAP I/O units
      INQUIRE(UNIT=MICROS,OPENED=OPENED)
      IF(OPENED) THEN
         REWIND MICROS
      ELSE
         XSFILE = 'xsneut.dat'
         INQUIRE(FILE=XSFILE,EXIST=EXISTS)
         IF(.NOT.EXISTS) THEN
            CHROOT=' '
C modif for VMC 	    
            CALL GETENVF('G3SYS',CHROOT)
            LNROOT = LNBLNK(CHROOT)
            IF(LNROOT.GT.0)XSFILE = CHROOT(1:LNROOT)//'/data/xsneut.dat'
         ENDIF
         INQUIRE(FILE=XSFILE,EXIST=EXISTS)
         IF(.NOT.EXISTS) THEN
           PRINT*,'**********************************'
           PRINT*,'*        G C A L O R             *'
           PRINT*,'*        -----------             *'
           PRINT*,'*   File XSNEUT.DAT not found    *'
           PRINT*,'*         Program STOP           *'
           PRINT*,'**********************************'
           STOP
         ENDIF
         OPEN(UNIT=MICROS,FILE=XSFILE,STATUS='OLD')
      ENDIF
C setup the link areas needed for x-section banks
      CALL MZLINK(IXCONS,'MICTMP',LTEMP,LTEMP,LTEMP)
      CALL MZLINK(IXCONS,'MMICAP',LMAG2,LMOX4,LMAG2)
      CALL MZLINK(IXCONS,'MPOINT',LMAG1,LFP210,LMAG1)
C
      LSUP = 0
      LCSUP = 0
      NUNIT = MICROS
C pointers into TEMP bank
      NTUNIT = 1
      NTNAME = NTUNIT + 1
      NTMPNI = NTNAME + 1 + 80/4
      NTCOMM = NTMPNI + 1
      NTDATS = NTCOMM + 1 + 80/4
      NTLIST = NTDATS + 1 + 24/4
   10 CONTINUE
C read comment and date of xsection file
        READ(NUNIT,'(A80,/,A24)') COMMEN,DATSTR
C read in material definition array
        READ(NUNIT,'(I10)') NISO
        NWW = NISO * 3 + 12 + NTLIST
C get temporary buffer
        CALL CHKZEB2(NWW,IXCONS)
        IF(LSUP.EQ.0) Then
C create a top level bank for the list of isotopes
          CALL MZBOOK(IXCONS,LTEMP,LSUP,2,'TEMP',3,0,NWW,0,-1)
          LT = LTEMP
        ELSE
C create an additional bank in the linear structure TEMP
          CALL MZBOOK(IXCONS,LT,LSUP,0,'TEMP',3,0,NWW,0,-1)
          LSUP = LT
        ENDIF
        NREC = NISO * 3 / 12
        NN = 0
C store the unit number of the file in bank TEMP
        IQ(LT + NTUNIT) = NUNIT
C store the file name in bank TEMP
        CALL UCTOH(XSFILE,IQ(LT+NTNAME+1),4,LNBLNK(XSFILE))
        IQ(LT + NTNAME) = LNBLNK(XSFILE)
C store the comment and date string in bank TEMP
        IQ(LT + NTCOMM) = LNBLNK(COMMEN)
        CALL UCTOH(COMMEN,IQ(LT+NTCOMM+1),4,LNBLNK(COMMEN))
        IQ(LT + NTDATS) = LNBLNK(DATSTR)
        CALL UCTOH(DATSTR,IQ(LT+NTDATS+1),4,LNBLNK(DATSTR))
        DO 20 I=1,NREC
           LL = (I-1)*12 + LT + NTLIST
           READ(NUNIT,'(12I6)') (IQ(L),L=LL,LL+11)
   20   CONTINUE
C
C get number of comment lines for different isotopes
        READ(NUNIT,'(I10)') NCOM
        NWW = NCOM * 80 + 2
C get CISO bank
        CALL CHKZEB2(NWW,IXCONS)
        IF(LCSUP.EQ.0) Then
C create a top level bank for the isotope comments
          CALL MZBOOK(IXCONS,LCISO,LCSUP,2,'CISO',3,0,NWW,0,-1)
          LC = LCISO
        ELSE
C create an additional bank in the linear structure CISO
          CALL MZBOOK(IXCONS,LC,LCSUP,0,'CISO',3,0,NWW,0,-1)
          LCSUP = LC
        ENDIF
        IQ(LC+1) = NCOM
        DO 30 I=1,NCOM
           J = (I-1)*81 + 2
           READ(NUNIT,'(I4,I4,A70)') IQ(LC+J),IQ(LC+J+1),
     +                CCOMM
           CALL UCTOH(CCOMM,IQ(LC+J+2),4,70)
   30   CONTINUE
C
C---------------------------------------------------------------------
C check the existence of secondary x-section files stored in bank MIFL
C real messy code !!! But its fortran after all !!! CZ Jan 95
        XSFILE = ' '
        IF(NUNIT.EQ.MICROS) THEN
          FMIFL = .FALSE.
          CALL MZINQD(IXCONS)
          IF(LMIFIL.GE.IQUEST(3) .AND. LMIFIL.LE.IQUEST(4)) THEN
             CALL UHTOC(IQ(LMIFIL-4),4,CNAME,4)
             IF(CNAME.EQ.'MIFL') FMIFL = .TRUE.
          ENDIF
          IXSF=LMIFIL
        ENDIF
        IF(FMIFL) THEN
   40     CONTINUE
C get the file name
          CALL UHTOC(IQ(IXSF+2),4,XSFILE,IQ(IXSF+1))
          IXSF = IXSF + 101
C last name in the list ?
          IF(IXSF-LMIFIL .GE. IQ(LMIFIL-1) ) FMIFL = .FALSE.
C
          INQUIRE(FILE=XSFILE,EXIST=EXISTS)
          IF(.NOT.EXISTS) THEN
             PRINT '(70(''*''))'
             PRINT '('' * MICAP : x-section file not found '')'
             PRINT '('' * '',A77)', XSFILE
             PRINT '(70(''*''))'
             IF(FMIFL) GOTO 40
          ELSE
C find a free unit number (greater 31), and use it
            DO 50 I=NUNIT+1,99
              INQUIRE(UNIT=I,OPENED=OPENED)
              IF(.NOT.OPENED) THEN
                 NUNIT = I
                 OPEN(UNIT=I,FILE=XSFILE,STATUS='OLD')
                 GOTO 10
              ENDIF
   50       CONTINUE
            PRINT '(70(''*''))'
            PRINT *,'* MICAP : No more free units available !'
            PRINT '(70(''*''))'
          ENDIF
        ENDIF
C---------------------------------------------------------------------
      CALL VZERO(MATIDS,4000)
      LT = LTEMP
   60 CONTINUE
        NUNIT = IQ(LT + NTUNIT)
        KK = LT + NTLIST
        DO 90 I=1,100
           NIS = IQ(KK)
           KK = KK + 1
           IF(NIS.EQ.0) GOTO 100
           IF(MATIDS(I,1,1).EQ.0) THEN
              MATIDS(I,1,1) = NIS
              MATIDS(I,1,2) = NUNIT
C is the Z of the element correct?
           ELSE IF(IQ(KK)/1000.EQ.I) THEN
C overwrite existing element with the one stored in new file
              DO 70 J=2,MATIDS(I,1,1)+1
                MATIDS(I,J,1) = 0
                MATIDS(I,J,2) = 0
   70         CONTINUE
              MATIDS(I,1,1) = NIS
              MATIDS(I,1,2) = NUNIT
           ELSE
C no action
              KK = KK + 2 * NIS
              GOTO 90
           ENDIF
C maximal 20 isotopes per element
           NIS = MIN(NIS,19)
           DO 80 J=2,NIS+1
              MATIDS(I,J,1) = IQ(KK)
              MATIDS(I,J,2) = IQ(KK+1)
              KK = KK + 2
   80      CONTINUE
   90   CONTINUE
  100   CONTINUE
        LT = LQ(LT)
      IF(LT.GT.0) GOTO 60
C
C       DEFINE CROSS SECTION DIMENSIONING VARIABLES
C         NNR EQUALS THE NUMBER OF NEUTRON RECORDS
C         NQ EQUALS THE NUMBER OF Q VALUES
C         NGR EQUALS THE NUMBER OF GAMMA RECORDS
C       SET THE DEFAULT VALUES FOR THE CURRENT CROSS SECTION DATA
      NNR=134
      NQ=66
      NGR=60
C
C       SET THE DEFAULT VALUES FOR THE NEUTRON, PROTON, DEUTERON,
C       TRITON, HELIUM-3, AND ALPHA PARTICLE MASSES (IN EV)
      ZN=XMASS(1)*1.E9
      ZP=XMASS(0)*1.E9
      ZD=XMASS(7)*1.E9
      ZT=XMASS(8)*1.E9
      ZHE3=XMASS(9)*1.E9
      ZA=XMASS(10)*1.E9
C       SET THE DEFAULT VALUES FOR THE NEUTRON, PROTON, DEUTERON,
C       TRITON, HELIUM-3, AND ALPHA PARTICLE MASSES (IN AMU)
      XAMU=0.93149432*1.E9
      AN=ZN/XAMU
      AP=ZP/XAMU
      AD=ZD/XAMU
      AT=ZT/XAMU
      AHE3=ZHE3/XAMU
      AA=ZA/XAMU
C now preprocess all materials xs
      MEDIA = 0
      NMIX = 0
      NMAT = 0
C Check if material option bank MIST exists
      FMIST = .FALSE.
      CALL MZINQD(IXCONS)
      IF(LMIST.GE.IQUEST(3) .AND. LMIST.LE.IQUEST(4)) THEN
         CALL UHTOC(IQ(LMIST-4),4,CNAME,4)
         IF(CNAME.EQ.'MIST') FMIST = .TRUE.
      ENDIF
C 1. loop over tracking media -> get NMIX,MEDIA
      DO 140 I=1,NTMED
         JTM = LQ(JTMED - I)
         IF(JTM.LE.0) GOTO 140
C valid tracking medium found get material number
C and get corresponding material parameters from JMATE structure
         IMA = INT(Q(JTM+6))
         IF(IMA.LE.0 .OR. IMA.GT.NMATE) GOTO 140
C count number of elements and number of mixing operations
         JMA = LQ(JMATE-IMA)
         IF(JMA.LE.0) GOTO 140
         IF(Q(JMA+6) .LE. 1.0 .OR. Q(JMA+6) .GE. 240.) GOTO 140
C Check if for material IMA single isotopes are selected
         FSINGL = .FALSE.
         IF(FMIST) THEN
           DO 110 KIM=1,IQ(LMIST-1),2
              IF(IMA.EQ.IQ(LMIST+KIM).AND.IQ(LMIST+KIM+1).EQ.0) THEN
                 FSINGL = .TRUE.
                 GOTO 120
              ENDIF
  110      CONTINUE
  120      CONTINUE
         ENDIF
C get number of elements in material max = 100
         KK = MIN(ABS(Q(JMA+11)),100.)
C relation between MICAP and GEANT material number
         MEDIA = MEDIA + 1
C mixture ?
         KK1 = KK
         IF(KK.GT.1) THEN
            JMIXT = LQ(JMA - 5)
C
C check if more than one isotope has to taken into account for all
C elements in the mixture
            DO 130 K=1,KK
               IA = NINT(Q(JMIXT+K))
               IZ = NINT(Q(JMIXT+K+KK))
               CALL MATISO2(IZ,IA,NNI,IDI,FSINGL,NUNIT)
               KK1 = KK1 + NNI - 1
  130       CONTINUE
         ELSE
            IA  = NINT(Q(JMA+6))
            IZ  = NINT(Q(JMA+7))
            CALL MATISO2(IZ,IA,NNI,IDI,FSINGL,NUNIT)
            KK1 = KK1 + NNI - 1
         ENDIF
         NMIX = NMIX + KK1
  140 CONTINUE
C allocate ZEBRA bank for material information
      NW = 9 * NMIX + MEDIA + 10
C define link area for MICAP banks in GCBANK
      CALL CHKZEB2(NW,IXCONS)
      CALL MZBOOK(IXCONS,LMOMA,0,2,'MOME',0,0,NW,0,-1)
      LMAG1 = LMOMA + 1
      IQ(LMAG1) = NMAGIC
      LGE2MO = LMAG1  + 1
      LFP10  = LGE2MO + MEDIA + 1
      LFP11  = LFP10  + NMIX
      LFP12  = LFP11  + NMIX
      LFP13  = LFP12  + NMIX
      LFP14  = LFP13  + NMIX
      LFP140 = LFP14  + NMIX
      LFP16  = LFP140 + NMIX
      LFP17  = LFP16  + NMIX
C 2. loop over tracking media
      MEDIA1 = 0
      NMIX1 = 0
      DO 230 I=1,NTMED
         JTM = LQ(JTMED - I)
         IF(JTM.LE.0) GOTO 230
C valid tracking medium found get material number
C and get corresponding material parameters from JMATE structure
         IMA = INT(Q(JTM+6))
         IF(IMA.LE.0 .OR. IMA.GT.NMATE) GOTO 230
C count number of elements and number of mixing operations
         JMA = LQ(JMATE-IMA)
         IF(JMA.LE.0) GOTO 230
         IF(Q(JMA+6) .LE. 1.0 .OR. Q(JMA+6) .GE. 240.) GOTO 230
C Check if for material IMA single isotopes are selected
         FSINGL = .FALSE.
         IF(FMIST) THEN
           DO 150 KIM=1,IQ(LMIST-1),2
              IF(IMA.EQ.IQ(LMIST+KIM).AND.IQ(LMIST+KIM+1).EQ.0) THEN
                 FSINGL = .TRUE.
                 GOTO 160
              ENDIF
  150      CONTINUE
  160      CONTINUE
         ENDIF
         NMAT = NMAT + 1
C get number of elements in material max = 100
         RHO1 = Q(JMA+8)
         KK = MIN1(ABS(Q(JMA+11)),100.)
C relation between MICAP and GEANT material number
C check if medium IMA already stored (multiple tracking media)
         DO K=1,100
            AGEA(K) = 0.0
         ENDDO
         DO 180 KMI=1,MEDIA1
            IF(IQ(LGE2MO+KMI).EQ.IMA) THEN
               IF(KK.EQ.1) THEN
                  IA  = NINT(Q(JMA+6))
                  IZ  = NINT(Q(JMA+7))
                  CALL MATISO2(IZ,IA,NNI,IDI,FSINGL,NUNIT)
                  NMIX = NMIX - NNI
               ELSE
                  JMIXT = LQ(JMA - 5)
                  DO 170 K=1,KK
                     IA = NINT(Q(JMIXT+K))
                     IZ = NINT(Q(JMIXT+K+KK))
                     CALL MATISO2(IZ,IA,NNI,IDI,FSINGL,NUNIT)
                     NMIX  = NMIX - NNI
  170             CONTINUE
               ENDIF
               MEDIA = MEDIA - 1
               GOTO 230
            ENDIF
  180    CONTINUE
         MEDIA1 = MEDIA1 + 1
         IQ(LGE2MO+MEDIA1) = IMA
C mixture ?
         KK2 = KK
         IF(KK.GT.1) THEN
            JMIXT = LQ(JMA - 5)
            KPOS = 1
            DO 200 K=1,KK
               AMOL = Q(LQ(JMIXT-1) + 2)
               XMOLCM = RHO1/AMOL*XNAVO
               IA = NINT(Q(JMIXT+K))
               IZ = NINT(Q(JMIXT+K+KK))
               CALL MATISO2(IZ,IA,NNI,IDI,FSINGL,NUNIT)
               KK2 = KK2 + NNI - 1
               DO 190 KJ=1,NNI
                  KKPOS = KPOS + KJ - 1
                  IF(KJ.EQ.1) THEN
                     AGEA(KKPOS) = Q(JMIXT+K)
                  ELSE
                     AGEA(KKPOS) = 0.
                  ENDIF
                  MID(KKPOS,1) = IDI(KJ,1)
                  MID(KKPOS,2) = NUNIT
                  IIZ = IDI(KJ,1)/1000
                  IIA = IDI(KJ,1) - IIZ * 1000
                  IF(IIA.NE.0 .AND. NNI.GT.1.) THEN
                    A(KKPOS) = FLOAT(IIA)
                  ELSE
                    A(KKPOS) = Q(JMIXT+K)
                  ENDIF
                  Z(KKPOS) =  Q(JMIXT+K+KK)
                  WISO = FLOAT(IDI(KJ,2))/100.
                  WI = Q(JMIXT+K+2*KK)*AMOL/A(KKPOS)*WISO
                  DEN(KKPOS) = XMOLCM * WI
  190          CONTINUE
               KPOS = KPOS + NNI
  200       CONTINUE
C element or compound
         ELSE
            IA  = NINT(Q(JMA+6))
            IZ  = NINT(Q(JMA+7))
            CALL MATISO2(IZ,IA,NNI,IDI,FSINGL,NUNIT)
            KK2 = KK2 + NNI - 1
            DO 210 KJ=1,NNI
               IF(KJ.EQ.1) THEN
                  AGEA(KJ) = Q(JMA+6)
               ELSE
                  AGEA(KJ) = 0.
               ENDIF
               MID(KJ,1) = IDI(KJ,1)
               MID(KJ,2) = NUNIT
               IIZ = IDI(KJ,1)/1000
               IIA = IDI(KJ,1) - IIZ * 1000
               IF(IIA.NE.0 .AND. NNI.GT.1.) THEN
                  A(KJ) = FLOAT(IIA)
               ELSE
                  A(KJ) = Q(JMA+6)
               ENDIF
               Z(KJ) =  Q(JMA+7)
               WISO = FLOAT(IDI(KJ,2))/100.
               DEN(KJ) = RHO1/A(KJ) * WISO *XNAVO
  210       CONTINUE
         ENDIF
C
C fill MICAP material arrays
C actual number of isotopes given by KK2
C
         DO 220 J = NMIX1 + 1, NMIX1 + KK2
            IQ(LFP10+J-1) = MEDIA1
            IQ(LFP11+J-1) = MID(J-NMIX1,1)
C check if bound hydrogen has been selected
            IF(MID(J-NMIX1,1).eq.1001.AND.KK.GT.1) IQ(LFP11+J-1) = 1000
            Q(LFP12+J-1) = DEN(J-NMIX1)
            IQ(LFP13+J-1) = NINT(Z(J-NMIX1))
            Q(LFP14+J-1) = A(J-NMIX1)
            Q(LFP140+J-1) = AGEA(J-NMIX1)
  220    CONTINUE
         NMIX1 = NMIX1 + KK2
  230 CONTINUE
      IF(NMIX.LE.0) THEN
         PRINT *,' GCALOR: NO tracking media found ===> STOP '
         STOP
      ENDIF
C read cross-sections and perform mixing and thinning
      CALL MOXSEC2
C close MICAP cross-section file(s)
      LT = LTEMP
  240 CONTINUE
        CLOSE(UNIT=IQ(LT+NTUNIT))
        LT = LQ(LT)
      IF(LT.GT.0) GOTO 240
C Drop temporary linear structures
      CALL MZDROP(IXCONS,LTEMP,'L')
      CALL MZDROP(IXCONS,LCISO,'L')
      RETURN
      END
*CMZ :  1.05/04 25/02/2005  14.27.38  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   22/07/92
      SUBROUTINE MOXSEC2
C************************************************************
C
C  setup cross-section tables for MICAP
C
C  Called by: MORINI
C
C  INPUT: MICAP element IDs in KE  = LD(LFP11)
C         element densities in RHO = D (LFP12)
C
C  Author : C.Zeitnitz
C
C  See USER's GUIDE TO MICAP ORNL/TM-10340
C  for details and pointer description (MPOINT)
C
C************************************************************
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MPOINT.
      COMMON/MPOINT/LMAG1,LFP1,LFP2,LFP3,LFP4,LFP5,LFP6,LFP7,LFP8,
     + LFP9,LFP10,LFP11,LFP12,LFP13,LFP14,LFP140,LFP15,LFP16,LFP17,
     + LFP18,LFP19,LFP20,LFP21,LFP22,LFP23,LFP24,LFP25,LFP26,
     + LFP27,LFP28,LFP29,LFP30,LFP31,LFP32,LFP33,LFP34,LFP35,
     + LFP36,LFP37,LFP38,LFP39,LFP40,LFP41,LFP42,LFP43,LFP44,
     + LFP45,LFP46,LFP47,LFP48,LFP49,LFP50,LFP51,LFP52,LFP53,
     + LFP18A,LFP210
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,CMAGIC.
      PARAMETER(NMAGIC=123456789)
*KEND.
C
      CHARACTER*80 XSFILE
      CHARACTER*70 CCOMM
      CHARACTER*11 CGEANT
      CHARACTER*4  MARK
      CHARACTER*20 MATNAM
      INTEGER INEL(134)
      LOGICAL NOHED,XSTOP
C
C       CALCULATE THE NUMBER OF ELEMENTS (NNUC)
C       AND GENERATE THE ISOTOPE NUMBER ARRAY (IN(NMIX))
      NWTOT = 0
      DO 10 I=1,NMIX
         LD(LFP17+I-1)=0
         LD(LFP16+I-1)=0
   10 CONTINUE
C       INITIALIZE THE NUMBER OF ELEMENTS (NNUC)
      NNUC=0
      DO 30 I=1,NMIX
         IF(LD(LFP16+I-1).GT.0)GO TO 30
         NNUC=NNUC+1
         LD(LFP16+I-1)=NNUC
         DO 20 J=I+1,NMIX
            IF(LD(LFP11+I-1).NE.LD(LFP11+J-1))GO TO 20
            LD(LFP16+J-1)=NNUC
   20    CONTINUE
   30 CONTINUE
C get number of isoptopes from xsection file(s)
      LT = LTEMP
      NII = 0
   40 CONTINUE
        NUNIT = IQ(LT+NTUNIT)
        READ(NUNIT,'(I10)') NIS
        NII = NII + NIS
        IQ(LT+NTMPNI) = NIS
        LT = LQ(LT)
      IF(LT.GT.0) GOTO 40
C allocate needed memory for x-section
      NW = 2*NII+13*NNUC+2*NNR*NNUC+4*NGR*NNUC+3*NQ*NNUC+26*MEDIA + 2
      NI = NII
      NWTOT = NWTOT + NW
      CALL CHKZEB2(NW,IXCONS)
      CALL MZBOOK(IXCONS,LMOX1,0,2,'MOX1',0,0,NW,0,-1)
C       SET UP THE B CONTROL BLOCK LOCATION NUMBER ARRAY ICOM(NNUC)
C LFP170 points to length of x-section data
      LFP170 = LMOX1 + 2
      LFP18=LFP170+NNUC
      LFP18A=LFP18+NII
      LFP19=LFP18A+NII
      LFP20=LFP19+NMIX
C       SET UP THE ARRAY (IREC(NII))
      CALL XSECN12(NII,LD(LFP11),LD(LFP16),LD(LFP17),
     +                LD(LFP18),LD(LFP18A),LD(LFP170),LD(LFP19),
     +                D(LFP20),LD(LFP20),INEL)
C check if all isotopes have been found in the x-section file(s)
      XSTOP = .FALSE.
      DO 50  I=1,NMIX
        IF(LD(LFP19+I-1).EQ.0) THEN
         WRITE(IOUT,10100)LD(LFP19+I-1)
10000    FORMAT(' MICAP: Could not find x-section of element ',I8)
         XSTOP = .TRUE.
        ENDIF
   50 CONTINUE
      IF(XSTOP) THEN
        PRINT '('' CALOR : Neutron x-section not found ===> STOP '')'
        STOP
      ENDIF
      LFP21=LFP20+NNUC
C store xs accuracy at LFP210 (used for thinning  in XSECN32)
      LFP210 = LFP21 + NNUC
      LFP22=LFP210+NNUC
      LFP23=LFP22+NNUC
      LFP24=LFP23+NNUC
      LFP25=LFP24+NNUC
      LFP26=LFP25+NNUC
      LFP27=LFP26+NNR*NNUC
      LFP28=LFP27+NNR*NNUC
      LFP29=LFP28+NNUC
      LFP30=LFP29+NNUC
      LFP31=LFP30+NGR*NNUC
      LFP32=LFP31+NGR*NNUC
      LFP33=LFP32+MEDIA
      LFP34=LFP33+MEDIA
      LFP35=LFP34+NNUC
      LFP36=LFP35+3*NQ*NNUC
C       CLEAR2 THE STORAGE LOCATIONS FOR THE DICTIONARIES, ETC.
      CALL CLEAR2(LD,LFP20,LFP36-1)
C       ESTABLISH THE RANDOM WALK STORAGE LOCATIONS
      LFP41=LFP36
      LFP42=LFP41+2*NNUC
      LFP45=LFP42+24*MEDIA
      LFP46=LFP45+NGR*NNUC
      NW = 0
      DO 60 INUC=1,NNUC
         NW = NW + LD(LFP170+INUC-1)
   60 CONTINUE
      NW = NW + 2
      NWTOT = NWTOT + NW
      CALL CHKZEB2(NW,IXCONS)
      CALL MZBOOK(IXCONS,LMOX2,0,2,'MOX2',0,0,NW,0,-1)
      LFP43 = LMOX2 + 2
      LAST = LFP43 - 1
      MAXD = LMOX2 + NW
C       PLACE THE MICROSCOPIC CROSS SECTION DATA INTO THE CORE
      CALL XSECN22(LD(LFP17),LD(LFP18),LD(LFP18A),
     +            LD(LFP20),LD(LFP21),D(LFP210),LD(LFP22),LD(LFP23),
     +            LD(LFP24),LD(LFP25),LD(LFP26),LD(LFP27),LD(LFP28),
     +            LD(LFP29),LD(LFP30),LD(LFP31),D(LFP34),D(LFP35),
     +            LD(LFP35+NQ*NNUC),D(LFP35+2*NQ*NNUC),
     +            D(LFP43),LD(LFP43),MAXD,LAST,INEL)
C determine length needed for macroscopic xs and mixing
C the bank has to store:
C - the xs of each isotope in the mixture
C - the mixed xs (defined by sum of diff. energy points)
      NW = 0
      DO 90  IM=1,MEDIA
         NM = 0
         LZ = 0
         DO 70 IN=1,NMIX
            IF(LD(LFP10+IN-1).NE.IM) GOTO 70
            NM = NM+1
            II = LD(LFP16+IN-1)
            LZ = LD(LFP27+NNR*(II-1))+LZ
C            LZ = MAX0(LD(LFP27+NNR*(II-1)),LZ)
C           LZ = MAX0(LDICT(1,II),LZ)
   70    CONTINUE
C         IF(NM.GT.1) LZ = 6*LZ
         NW = NW + 2.*LZ
   90 CONTINUE
      NW = NW + 2
      NWTOT = NWTOT + NW
      CALL CHKZEB2(NW,IXCONS)
      CALL MZBOOK(IXCONS,LMOX3,0,2,'MOX3',0,0,NW,0,-1)
      LAST = LMOX3 + 1
      LFP44=LAST+1
      MAXD = LMOX3+NW
C       SET, MIX AND THIN THE TOTAL CROSS SECTIONS
C       ACCORDING TO THE MIXING TABLE
      CALL XSECN32(LD(LFP10),LD(LFP11),D(LFP12),LD(LFP16),LD(LFP26),
     +            LD(LFP27),LD(LFP32),LD(LFP33),D(LFP44),LD(LFP44),
     +            D,MAXD,LAST)
C       ESTABLISH THE PHOTON2 TOTAL CROSS SECTION DATA DICTIONARY
C       STORAGE LOCATIONS
C determine number of words needed for photon2 production xs
      NW = 0
      DO 110 I=1,NNUC
         DO 100 J=1,LD(LFP28+I-1)
            LZ = LD(LFP31 + 2*J - 1 + NGR*(I-1))
C           LZ = LGCB(2*J,I)
            NW = NW + LZ
  100    CONTINUE
  110 CONTINUE
      NW = NW + 2*NGR*NNUC+2
      NWTOT = NWTOT + NW + 1
      CALL CHKZEB2(NW,IXCONS)
      CALL MZBOOK(IXCONS,LMOX4,0,2,'MOX4',0,0,NW,0,-1)
      LMAG2 = LMOX4 + 1
      LD(LMAG2) = NMAGIC
      LFP45 = LMAG2 + 1
      LFP46 = LFP45 + NGR*NNUC
      LFP47 = LFP46 + NGR*NNUC
      LAST = LFP47 - 1
      MAXD = LMOX4 + NW
C       CLEAR2 THE STORAGE LOCATIONS FOR THE PHOTON2 DICTIONARIES
C       OF THE TOTAL PHOTON2 PRODUCTION CROSS SECTIONS
      CALL CLEAR2(LD,LFP45,LFP47-1)
C       SUM THE PHOTON2 PARTIAL DISTRIBUTIONS OF THE ENDF/B-V
C       FILE 12 AND FILE 13 DATA (BY MT NUMBER) AND PLACE THESE
C       MICROSCOPIC MULTIPLICITIES TIMES CROSS SECTIONS IN CORE
      CALL XSECN52(LD(LFP28),LD(LFP30),LD(LFP31),LD(LFP45),LD(LFP46),
     +           D(LFP47),LD(LFP47),D,LD,MAXD,LAST)
C
C print out media to print unit IOUT
C      WRITE(IOUT,10000)
10100 FORMAT(23X,'MICAP Material Parameters',/,
     +       23X,'-------------------------',/)
      WRITE(IOUT,10200)
10200 FORMAT(8X,'GEANT Material Parameters',10X,
     +        6X,'MICAP Material Parameters',/,
     +       8X,25('-'),10X,6X,25('-'))
      WRITE(IOUT,10300)
10300 FORMAT(1X,'Material',16X,'No/Iso',4X,'A',5X,'Z',2X,'|',
     +        4X,'A',5X,'Z',3X,'Density',
     +        3X,'Coll.Len',/,44('-'),'+',33('-'))
      MFLAG = 0
      KMED  = 0
      NISO  = 1
      DO 130 I=0,NMIX-1
C get GEANT name of material
         MARK = '/   '
         IF(LD(LFP11+I)/1000.NE.LD(LFP13+I).OR.
     +      (I.LT.NMIX-1.AND.D(LFP140+I).NE.0..AND.D(LFP140+I+1).NE.0.
     +       .AND.NINT(D(LFP34+LD(LFP16+I)-1)*1.008665)
     +       .NE.NINT(D(LFP140+I)))) THEN
            MARK = '/  *'
            MFLAG=1
         ENDIF
         K1 = LD(LFP16+I)-1
         LS1 = LD(LFP26+NNR*K1)+LMOX2
         LEN = LD(LFP27+NNR*K1)/2
         EN = 1.E6
         CALL TBSPLT2(D(LS1),EN,LEN,XSEC)
         XSEC = 1./XSEC/D(LFP12+I)
         IF(D(LFP140+I).NE.0.) THEN
            WRITE(CGEANT,'(F6.1,I5)')  D(LFP140+I),LD(LFP13+I)
         ELSE
            WRITE(CGEANT,'(A11)')  '    -     -'
         ENDIF
         IF(KMED.NE.LD(LFP10+I)) THEN
          NISO = 1
          CALL G3FMATE(LD(LGE2MO+LD(LFP10+I)),MATNAM,AA,ZZ,DENS,
     +       RADL,ABSL,UB,NW)
          NBLK = LNBLNK(MATNAM)
          DO 120 JC=NBLK+1,20
             WRITE(MATNAM(JC:JC),'(A1)') '.'
  120     CONTINUE
          WRITE(MARK(2:3),'(I2)') NISO
          WRITE(IOUT,10400) MATNAM,LD(LGE2MO+LD(LFP10+I)),MARK,
     +     CGEANT,
     +     D(LFP34+LD(LFP16+I)-1)*1.008665,
     +     LD(LFP11+I)/1000,D(LFP12+I),XSEC
          KMED = LD(LFP10+I)
         ELSE
          WRITE(MARK(2:3),'(I2)') NISO
          WRITE(IOUT,10500) LD(LGE2MO+LD(LFP10+I)),MARK,CGEANT,
     +     D(LFP34+LD(LFP16+I)-1)*1.008665,
     +     LD(LFP11+I)/1000,D(LFP12+I),XSEC
         ENDIF
10400    FORMAT(1X,A20,I6,A4,A11,'  |',F6.1,I5,1X,E11.4,1X,E9.3)
10500    FORMAT(1X,20X,I6,A4,A11,'  |',F6.1,I5,1X,E11.4,1X,E9.3)
         LD(LFP13+I) = LD(LFP11+I)/1000
         NISO = NISO + 1
  130 CONTINUE
      WRITE(IOUT,'(78(''-''),/,48X,''Density in (Atoms/barn/cm)'')')
      WRITE(IOUT,'(36X, '
     +    //' ''Collision Length for 1 MeV neutron in (cm)'',/)')
      IF(MFLAG.EQ.1) WRITE(IOUT,'(/, '
     + //'15X,''*******************************************'',/,  '
     + //'15X,''*               W A R N I N G             *'',/,  '
     + //'15X,''*   Marked isotopes (*) not found in the  *'',/,  '
     + //'15X,''*        cross-section file(s)            *'',/,  '
     + //'15X,''*    Cross-sections of the isotope with   *'',/,  '
     + //'15X,''*    the closest Z will be used instead   *'',/,  '
     + //'15X,''*******************************************'',/)')
C which x-section files have been used?
      LT = LTEMP
      LCI = LCISO
      LC = 0
      NOHED=.TRUE.
  140 CONTINUE
C first check if x-section file has been used!
        NUNIT = IQ(LT+NTUNIT)
        DO 150 I=0,NMIX-1
           KISO = LD(LFP16+I)
           MISO = LD(LFP17+KISO-1)
           IF(NUNIT.EQ.LD(LFP18A+MISO-1)) GOTO 160
  150   CONTINUE
C unit never used !
        GOTO 190
  160   CONTINUE
C search for comments for selected isotopes
        NCOM = IQ(LCI+1)
        DO 180 J=1,NCOM
           K = (J-1)*81 + 2
           JZ = IQ(LCI+K)
           JA = IQ(LCI+K+1)
           CCOMM = ' '
           CALL UHTOC(IQ(LCI+K+2),4,CCOMM,70)
           DO 170 I=0,NMIX-1
              KISO = LD(LFP16+I)
              IA = NINT(D(LFP34+KISO-1)*1.008665)
              IZ = LD(LFP11+I)/1000
              MISO = LD(LFP17+KISO-1)
C print the comment, if the isotope is correct and has been read from
C the current x-section file
              IF(IA.EQ.JA .AND. IZ.EQ.JZ .AND.
     +           NUNIT.EQ.LD(LFP18A+MISO-1)) THEN
                IF(NOHED) THEN
                 WRITE(IOUT,'(/,23X,''COMMENTS ABOUT ISOTOPE DATA'')')
                 WRITE(IOUT,'(  23X,''---------------------------'',/)')
                 NOHED = .FALSE.
                ENDIF
                LC = LC + 1
                WRITE(IOUT,'(I4,'') '',A70)') LC,CCOMM
                GOTO 180
              ENDIF
  170      CONTINUE
  180   CONTINUE
  190   LT = LQ(LT)
        LCI = LQ(LCI)
      IF(LT.GT.0.AND.LCI.GT.0) GOTO 140
C print the x-section file names and comments
      WRITE(IOUT,'(/,20X,''USED NEUTRON CROSS-SECTION FILES'')')
      WRITE(IOUT,'(  20X,''--------------------------------'',/)')
      LT = LTEMP
  200 CONTINUE
C first check if x-section file has been used!
        NUNIT = IQ(LT+NTUNIT)
        DO 210 I=0,NMIX-1
           KISO = LD(LFP16+I)
           MISO = LD(LFP17+KISO-1)
           IF(NUNIT.EQ.LD(LFP18A+MISO-1)) GOTO 220
  210   CONTINUE
C unit never used !
        GOTO 230
  220   CONTINUE
C get file name of x-section file
        XSFILE = ' '
        COMMEN = ' '
        DATSTR = ' '
        CALL UHTOC(IQ(LT+NTNAME+1),4,XSFILE,IQ(LT+NTNAME))
        CALL UHTOC(IQ(LT+NTCOMM+1),4,COMMEN,IQ(LT+NTCOMM))
        CALL UHTOC(IQ(LT+NTDATS+1),4,DATSTR,IQ(LT+NTDATS))
        WRITE(IOUT,'('' File      : '',A66)') XSFILE
        WRITE(IOUT,'('' Generated : '',A24,/,    '
     +        //'    '' Comment   : '',A66,/)') DATSTR,COMMEN
  230   LT = LQ(LT)
      IF(LT.GT.0) GOTO 200
      WRITE(IOUT,'(/,'' MICAP :'',I10, '
     + //' '' words used in GCBANK for neutron x-section tables''/)')
     +   NWTOT
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.48  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE N2NN3N2(D,LD,AWR,KZ,ID,FM,Q,IFLG)
C       THIS ROUTINE CALCULATES THE DIRECTIONAL COSINES FOR THE
C       NEUTRON AND RECOIL NUCLEUS FOR AN N2N OR N3N REACTION
C       USING THE ONE NEUTRON EMMISION MODEL.  IT ALSO SETS ALL
C       EXIT PARAMETRS FOR THE RECOIL NUCLEUS.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*),FM(*)
      SAVE
      MT=0
      IF(ID.EQ.8)MT=16
      IF(ID.EQ.9)MT=17
      IF(ID.EQ.12)MT=24
C       IFLG EQUAL TO ONE IMPLIES THE DIRECTION COSINES WERE
C       SELECTED ISOTROPICALLY IN THE LABORATORY COORDINATE SYSTEM
C       CALCULATE THE NEUTRON EXIT DIRECTIONAL COSINES
      POX = 0.0
      POY = 0.0
      POZ = 0.0
      DO 40 KN=1,INEU
         IF(IFLG.EQ.1) THEN
            CALL GTISO2(UP,VP,WP)
         ELSE
            SINPSI=SQRT(1.0-FM(KN)**2)
            CALL AZIRN2(SINETA,COSETA)
            STHETA=1.0-UOLD**2
            IF(STHETA)20,20,10
   10       STHETA=SQRT(STHETA)
            COSPHI=VOLD/STHETA
            SINPHI=WOLD/STHETA
            GO TO 30
   20       COSPHI=1.0
            SINPHI=0.0
            STHETA=0.0
   30       UP = UOLD*FM(KN)-COSETA*SINPSI*STHETA
            VP = VOLD*FM(KN)+UOLD*COSPHI*COSETA*SINPSI-SINPHI* SINPSI*
     +      SINETA
            WP = WOLD*FM(KN)+UOLD*SINPHI*COSETA*SINPSI+COSPHI* SINPSI*
     +      SINETA
            S=1.0/SQRT(UP*UP+VP*VP+WP*WP)
            UP=UP*S
            VP=VP*S
            WP=WP*S
         ENDIF
         EP = ENE(KN)
C use ONLY first neutron for recoil calculation in order the ensure
C correct energy spectrum of recoil nucleus
         IF(KN.EQ.1) THEN
            PP = SQRT(EP**2 + 2.0*EP*ZN)
            POX = POX + PP*UP
            POY = POY + PP*VP
            POZ = POZ + PP*WP
         ENDIF
         AGEP = AGE
         MTP = MT
         CALL STOPAR2(IDNEU,NNEU)
   40 CONTINUE
C       CALCULATE AND SET THE RECOIL NUCLEUS EXIT PARAMETERS
   50 XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ
      ZMP = FLOAT(KZ)
      AGER=AGE
      AGEP = AGE
      NCOLR=NCOL
      MTNR=MT
      MTP = MT
      AR = (AWR*AN) - FLOAT(INEU-1)*AN
      AMP = AR
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
C       CALCULATE THE NEUTRON MOMENTUM BEFORE AND AFTER COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
C   CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PIX=PI*UOLD
      PIY=PI*VOLD
      PIZ=PI*WOLD
      PRX = PIX - POX
      PRY = PIY - POY
      PRZ = PIZ - POZ
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      UR=PRX/PR
      VR=PRY/PR
      WR=PRZ/PR
      UP = UR
      VP = VR
      WP = WR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      XM = AR*931.075E6
      ER= SQRT(PR**2 + XM**2) - XM
      EP = ER
      MTP = MT
C       IF MT=24, DO NOT STORE THE RECOIL HEAVY ION IN THE BANK
      IF(MT.EQ.24)RETURN
C       STORE THE  RECOIL HEAVY ION IN THE RECOIL BANK
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.01/00 01/06/93  09.05.16  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE NGHEVY2(D,LD,KZ,AWR,Q,MT)
C       THIS ROUTINE CALCULATES THE EXIT ENERGY AND DIRECTIONAL
C       COSINES FOR THE RECOIL NUCLEUS RESULTING FROM THE (N,G)
C       REACTION MT-102, AND STORES THE RECOIL NUCLEUS IN THE
C       HEAVY ION BANK.  THE ENERGY AND DIRECTIONAL COSINES ARE
C       DETERMINED BY A MOMENTUM BALANCE IN THE LABORATORY SYSTEM
C       WITH THE PHOTON2S MOMENTUM EQUAL TO ITS ENERGY.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,MGAMMA.
      COMMON/MGAMMA/NAMEXG,MTNG,NMEDG,NCOLG,EG,UG,VG,WG,
     1XG,YG,ZG,WATEG,AGEG
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
      AR=AWR*AN+AN
C       CALCULATE THE TOTAL MOMENTUM BEFORE THE COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
C       CALCULATE THE TOTAL MOMEMTUM OF THE EXIT PHOTON2
      PO=EG*1.00E+06
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*UOLD-PO*UG
      PRY=PI*VOLD-PO*VG
      PRZ=PI*WOLD-PO*WG
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      UR=PRX/PR
      VR=PRY/PR
      WR=PRZ/PR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      ER=PR**2/(2*AR*9.31075E+08)
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=0.0
      UNOR=0.0
      VNOR=0.0
      WNOR=0.0
      WTNR=0.0
      QR=Q
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AMP = AR
      ZMP = FLOAT(NZR)
      AGEP = AGE
      MTP = MT
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  0.90/00 03/08/92  17.58.51  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE NN2BOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,Q,MT)
C       THIS ROUTINE CALCULATES THE EXIT ENERGIES AND DIRECTIONAL
C       COSINES FOR THE CHARGED PARTICLE AND RECOIL NUCLEUS FOR
C       A TWO-BODY REACTION USING AN EVAPORATION SPECTRUM AND
C       MOMEMTUM BALANCE.  IT ALSO SETS ALL EXIT PARAMETERS FOR
C       THE COLLISION PRODUCTS AND STORES THEM IN THE RECOIL BANK.
C       THE TWO BODY REACTION RESULTS FROM THE BREAK-UP OF A NUCLEUS
C       LEFT IN AN EXCITED STATE BY AN INELASTIC COLLISION OR A
C       N,2N REACTION (I.E. MT-24).
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
C       TRANSFER THE RECOILING COMPOUND NUCLEUS PARAMETERS OUT OF
C       COMMON RECOIL FOR USE IN THE MOMENTUM BALANCE EQUATIONS
      ERCN=ER
      URCN=UR
      VRCN=VR
      WRCN=WR
      ARCN=AR
      NZRCN=NZR
      ZARCN=ARCN*9.31075E+08
C       CALCULATE THE COULOMB BARRIER (CB)
      CALL BARIER2(KZ1,KZ2,A1,A2,CB)
C       CALCULATE THE CHARGED PARTICLE EXIT ENERGY (EX)
      CALL CEVAP21(EOLD,E,Q,ATAR,CB,EX)
      E1=EX+CB
C       ASSUME ISOTROPIC CHARGED PARTICLE EMISSION IN THE LABORATORY
      CALL GTISO2(U1,V1,W1)
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ1
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A1
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
      UR=U1
      VR=V1
      WR=W1
      ER=E1
C       STORE THE CHARGED PARTICLE IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      AMP = AR
      ZMP = FLOAT(NZR)
      CALL STOPAR2(IDHEVY,NHEVY)
C       CALCULATE THE TOTAL MOMENTUM BEFORE THE COLLISION
C       COMPOUND NUCLEUS MOMENTUM BEFORE THE COLLISION (PI) EQUALS
C       THE TOTAL MOMENTUM
      PI=SQRT(2.0*ZARCN*ERCN)
C       CALCULATE THE TOTAL MOMEMTUM OF THE EXIT CHARGED PARTICLE
      PO=SQRT(2.0*Z1*E1)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*URCN-PO*U1
      PRY=PI*VRCN-PO*V1
      PRZ=PI*WRCN-PO*W1
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      U2=PRX/PR
      V2=PRY/PR
      W2=PRZ/PR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      XM = A2 * 931.075E6
      E2 = SQRT(PR**2 + XM**2) - XM
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ2
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A2
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=E
      UNOR=U
      VNOR=V
      WNOR=W
      WTNR=WATE
      QR=Q
      UR=U2
      VR=V2
      WR=W2
      ER=E2
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AGEP = AGE
      MTP = MT
      AMP = AR
      ZMP = FLOAT(NZR)
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  0.94/04 18/03/93  22.56.07  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE NSIGTA2(E,JMED,TSIG,D,ISIGTS,LSIGT)
C       THIS ROUTINE DETERMINES THE MACROSCOPIC TOTAL
C       CROSS SECTION FOR MEDIA MED
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      DIMENSION D(*),ISIGTS(*),LSIGT(*)
      CALL GTMED2(JMED,MED)
      TSIG=0.0
      L1=LSIGT(MED)
      LS1=ISIGTS(MED)+LMOX3
      LEN=L1/2
      CALL TBSPLT2(D(LS1),E,LEN,TSIG)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.48  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE PARTXS2(D,LD,E,SIGTOT,EP)
C       THIS ROUTINE SAMPLES FROM THE FILE 12 OR 13 PHOTON2
C       PRODUCTION PARTIAL DISTRIBUTIONS TO OBTAIN THE EXIT
C       PHOTON2 ENERGY FROM A NEUTRON REACTION
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
C       INITIALIZE THE VALUES USED IN THE SELECTION PROCESS
C       THE VALUE (II) IS A POINTER
      ITRY1=0
   10 R=FLTRNF2(0)
      SUM=0.0
      NH=0
      NL=0
      II=0
C       SET THE NUMBER OF PARTIAL DISTRIBUTIONS (NK) AND THE NUMBER
C       OF POINTS PER PARTIAL DISTRIBUTION (NP)
      NK=LD(II+1)
      NP=LD(II+2)
      II=II+2
C       DETERMINE WHICH POINTS (NL) AND (NH) BOUND THE INCIDENT
C       NEUTRON ENERGY
      DO 20 N=1,NP
         IF(E.LE.D(II+N))GO TO 40
   20 CONTINUE
C       THE INCIDENT NEUTRON ENERGY IS GREATER THAN THE LAST ENERGY
C       POINT OF THE PARTIAL DISTRIBUTIONS, THEREFORE USE THE LAST
C       ENERGY POINT OF THE PARTIAL DISTRIBUTION TO SAMPLE FROM
      NH=NP
      II=II+NP
      DO 30 K=1,NK
         EP=D(II+1)
         LP=LD(II+2)
         A=D(II+3)
         LF=LD(II+4)
         IF(LP.EQ.2)EP=EP+(A/(A+1))*E
         II=II+4
         SIG=D(II+NH)
         SUM=SUM+SIG/SIGTOT
         IF(EP.EQ.0.0)GO TO 100
         IF(R.LE.SUM)GO TO 100
         II=II+NP
   30 CONTINUE
      GO TO 80
   40 IF(N.EQ.1)GO TO 60
C       THE INCIDENT NEUTRON ENERGY IS BOUNDED BY THE ENEGY POINTS
C       (NL) AND (NH) OF THE PARTIAL DISTRIBUTIONS, THEREFORE USE
C       LINEAR INTERP2OLATION
      NH=N
      NL=N-1
      EH=D(II+NH)
      EL=D(II+NL)
      II=II+NP
      DO 50 K=1,NK
         EP=D(II+1)
         LP=LD(II+2)
         A=D(II+3)
         LF=LD(II+4)
         IF(LP.EQ.2)EP=EP+(A/(A+1))*E
         II=II+4
         SIG=D(II+NL)+(E-EL)*(D(II+NH)-D(II+NL))/(EH-EL)
         SUM=SUM+SIG/SIGTOT
         IF(EP.EQ.0.0)GO TO 100
         IF(R.LE.SUM)GO TO 100
         II=II+NP
   50 CONTINUE
      GO TO 80
C       THE INCIDENT NEUTRON ENERGY IS LESS THAN THE FIRST ENERGY
C       POINT OF THE PARTIAL DISTRIBUTIONS, THEREFORE USE THE FIRST
C       ENERGY POINT OF THE PARTIAL DISTRIBUTION TO SAMPLE FROM
   60 NL=N
      II=II+NP
      DO 70 K=1,NK
         EP=D(II+1)
         LP=LD(II+2)
         A=D(II+3)
         LF=LD(II+4)
         IF(LP.EQ.2)EP=EP+(A/(A+1))*E
         II=II+4
         SIG=D(II+NL)
         SUM=SUM+SIG/SIGTOT
         IF(EP.EQ.0.0)GO TO 100
         IF(R.LE.SUM)GO TO 100
         II=II+NP
   70 CONTINUE
C retry with new R if SUM != 0
   80 IF(SUM.EQ.0.0) GOTO 90
      ITRY1 = ITRY1 + 1
      IF(ITRY1.LE.2) GOTO 10
C no success set EP = 0
   90 EP = 0.0
  100 RETURN
      END
*CMZ :  1.05/03 27/06/2001  18.21.00  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE PHOTON2(D,LD,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,
     +      AWR,IGCBS2,LGCB2,LR,IGAMS,LGAM,QI,ID,IIN,LRI,SIGN)
C       THIS ROUTINE CONTROLS THE GENERATION AND STORAGE OF ALL
C       PHOTON2S PRODUCED BY THE NEUTRON INTERACTIONS.  WHERE DATA
C       PERMITS, THE PHOTON2 PRODUCED IS DIRECTLY COUPLED TO THE
C       NEUTRON REACTION OCCURING.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MCROSS.
      COMMON/MCROSS/SIGT,SIGTNS,SIGTNA,SIGNES,SIGNIS,SGNISD,SGNISC,
     1SIGN2N,SIGN3N,SIGNNA,SGNN3A,SGN2NA,SIGNNP,SIGNF,SIGNG,SIGNP,
     2SIGND,SIGNT,SGN3HE,SIGNA,SIGN2A,SIGN3A,SIGN2P,SIGNPA,SGNT2A,
     3SGND2A
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      DIMENSION IDICTS(NNR,NNUC),LDICT(NNR,NNUC),NTX(*),NTS(*),
     +  IGCBS(NGR,NNUC),LGCB(NGR,NNUC),AWR(*),IGCBS2(NGR,NNUC),
     +  LGCB2(NGR,NNUC),LR(NQ,NNUC),IGAMS(*),LGAM(*),D(*),LD(*)
      SAVE
C flag to mark call to SECEGY2 = 1 or PARTXS2 = 2 for EP   CZ 13/8/92
      IEP = 0
C       INITIALIZE THE PHOTON2 ENERGY TO ZERO IN CASE NO PHOTON2 IS
C       CHOSEN (THIS IS NECESSARY BECAUSE OF ENDF INCONSISTENCY)
      EG=0.0
C       INITIALIZE THE PARAMETERS USED IN THE SELECTION PROCESS
      MT=0
      IMT=0
      NUMBG=0
      XSIG2=0.0
      XSIG=0.0
      SIGMT3=0.0
      SIGP=0.0
      AWRI=AWR(IIN)
      NNTX=NTX(IIN)
      NNTS=NTS(IIN)
      L=2*NNTX+2*NNTS
C       NO PHOTON2 DATA PRESENT (IF L=0)
      IF(L.EQ.0)GO TO 360
      LX=2*NNTX
      LS=LX+1
C       DETERMINE THE NEUTRON REACTION MT NUMBER
      IF(ID.EQ.8)MT=16
      IF(ID.EQ.9)MT=17
      IF(ID.EQ.10)MT=18
      IF(ID.EQ.11)MT=22
      IF(ID.EQ.12)MT=24
      IF(ID.EQ.13)MT=28
      IF((ID.GE.14).AND.(ID.LE.54))MT=51
      IF(ID.EQ.55)MT=102
      IF(ID.EQ.56)MT=103
      IF(ID.EQ.57)MT=104
      IF(ID.EQ.58)MT=105
      IF(ID.EQ.59)MT=106
      IF(ID.EQ.60)MT=107
      IF(ID.EQ.61)MT=108
      IF(ID.EQ.62)MT=109
      IF(ID.EQ.63)MT=111
      IF(ID.EQ.64)MT=112
      IF(ID.EQ.65)MT=113
      IF(ID.EQ.66)MT=114
C       DETERMINE WHICH DISCRETE INELASTIC SCATTERING LEVEL OCCURRED
      IF(MT.NE.51)GO TO 130
      IMT=ID-14
      MT=MT+IMT
C       RESET THE MT NUMBER IF AN LR-FLAG IS INVOLKED
      IF(LRI.EQ.22)MT=22
      IF(LRI.EQ.23)MT=23
      IF(LRI.EQ.28)MT=28
C       CHECK PHOTON2 PRODUCTION DICTIONARY TO SEE IF THERE IS PHOTON2
C       DATA CORRESPONDING TO THE NEUTRON MT REACTION THAT OCCURRED
      DO 10 IX=1,NNTX
         MTG=LGCB(2*IX-1,IIN)
         IF(MTG.EQ.MT)GO TO 30
   10 CONTINUE
   20 IF(LRI.EQ.22)GO TO 190
      IF(LRI.EQ.23)GO TO 190
      IF(LRI.EQ.28)GO TO 190
      GO TO 70
C       PHOTON2 DATA FOUND CORRESPONDING TO NEUTRON MT REACTION
   30 L1=LGCB2(2*IX,IIN)
      IF(L1.EQ.0)GO TO 370
      LS1=IGCBS2(2*IX,IIN)+LMOX4
      LEN=L1/2
      CALL TBSPLT2(D(LS1),EOLD,LEN,SIGP)
      IF(SIGP.EQ.0.0)GO TO 190
      LS2=IGCBS(2*IX,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL PARTXS2(D(LS2),LD(LS2),EOLD,SIGP,EP)
      IEP = 2
      IF(EP.GT.0.0)GO TO 60
C       DISCRETE PHOTON2 ENERGY WAS NOT SELECTED (EP=0.0)
C       CHECK SECONDARY PHOTON2 DISTRIBUTION (FILE 15) FOR EP
      DO 40 IS=1,NNTS
         MTGS=LGCB(LX+2*IS-1,IIN)
         IF(MTGS.EQ.MT)GO TO 50
   40 CONTINUE
C no file 15 found and EP=0 in PARTXS2 -> try MT=4 etc
      GO TO 20
   50 L1=LGCB(LX+2*IS,IIN)
      IF(L1.EQ.0)GO TO 380
      LS3=IGCBS(LX+2*IS,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL SECEGY2(EP,D(LS3),EOLD,LD(LS3))
      IEP = 1
C       DETERMINE THE PHOTON2 MULTIPLICITY (YP)
C       RECALCULATE THE DENOMINATOR USED IN CALCULATING THE
C       PHOTON2 MULTIPLICITY TO ACCOUNT FOR THE LR-FLAGS
   60 IF(LRI.EQ.22)CALL LRNORM2(D,LD,IDICTS,LDICT,LR,EOLD,MT,IIN,SIGN)
      IF(LRI.EQ.23)CALL LRNORM2(D,LD,IDICTS,LDICT,LR,EOLD,MT,IIN,SIGN)
      IF(LRI.EQ.28)CALL LRNORM2(D,LD,IDICTS,LDICT,LR,EOLD,MT,IIN,SIGN)
      YP=SIGP/SIGN
      GO TO 330
C       THE DISCRETE INELASTIC LEVEL PHOTON2 DATA WAS NOT FOUND
C       CHECK THE PHOTON2 PRODUCTION DICTIONARY TO SEE IF THERE IS
C       PHOTON2 DATA CORRESPONDING TO MT=4
   70 DO 80 IX=1,NNTX
         MTG=LGCB(2*IX-1,IIN)
         IF(MTG.EQ.4)GO TO 90
   80 CONTINUE
      GO TO 190
C       PHOTON2 DATA FOUND CORRESPONDING TO MT=4
   90 L1=LGCB2(2*IX,IIN)
      IF(L1.EQ.0)GO TO 370
      LS1=IGCBS2(2*IX,IIN)+LMOX4
      LEN=L1/2
      CALL TBSPLT2(D(LS1),EOLD,LEN,SIGP)
      IF(SIGP.EQ.0.0)GO TO 190
      LS2=IGCBS(2*IX,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL PARTXS2(D(LS2),LD(LS2),EOLD,SIGP,EP)
      IEP = 2
      IF(EP.GT.0.0)GO TO 120
C       DISCRETE PHOTON2 ENERGY WAS NOT SELECTED (EP=0.0)
C       CHECK SECONDARY PHOTON2 DISTRIBUTION (FILE 15) FOR EP
      DO 100 IS=1,NNTS
         MTGS=LGCB(LX+2*IS-1,IIN)
         IF(MTGS.EQ.4)GO TO 110
  100 CONTINUE
      GO TO 380
  110 L1=LGCB(LX+2*IS,IIN)
      IF(L1.EQ.0)GO TO 380
      LS3=IGCBS(LX+2*IS,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL SECEGY2(EP,D(LS3),EOLD,LD(LS3))
      IEP = 1
C       DETERMINE THE PHOTON2 MULTIPLICITY (YP)
C       RECALCULATE THE DENOMINATOR USED IN CALCULATING THE
C       PHOTON2 MULTIPLICITY TO ACCOUNT FOR THE LR-FLAGS
  120 MT=4
      CALL LRNORM2(D,LD,IDICTS,LDICT,LR,EOLD,MT,IIN,SIGNIS)
      YP=SIGP/SIGNIS
      GO TO 330
C       CHECK PHOTON2 PRODUCTION DICTIONARY TO SEE IF THERE IS PHOTON2
C       DATA CORRESPONDING TO THE NEUTRON MT REACTION THAT OCCURRED
  130 DO 140 IX=1,NNTX
         MTG=LGCB(2*IX-1,IIN)
         IF(MTG.EQ.MT)GO TO 150
  140 CONTINUE
      GO TO 190
C       PHOTON2 DATA FOUND CORRESPONDING TO NEUTRON MT REACTION
  150 L1=LGCB2(2*IX,IIN)
      IF(L1.EQ.0)GO TO 370
      LS1=IGCBS2(2*IX,IIN)+LMOX4
      LEN=L1/2
      CALL TBSPLT2(D(LS1),EOLD,LEN,SIGP)
      IF(SIGP.EQ.0.0)GO TO 190
      LS2=IGCBS(2*IX,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL PARTXS2(D(LS2),LD(LS2),EOLD,SIGP,EP)
      IEP = 2
      IF(EP.GT.0.0)GO TO 180
C       DISCRETE PHOTON2 ENERGY WAS NOT SELECTED (EP=0.0)
C       CHECK SECONDARY PHOTON2 DISTRIBUTION (FILE 15) FOR EP
      DO 160 IS=1,NNTS
         MTGS=LGCB(LX+2*IS-1,IIN)
         IF(MTGS.EQ.MT)GO TO 170
  160 CONTINUE
      GO TO 380
  170 L1=LGCB(LX+2*IS,IIN)
      IF(L1.EQ.0)GO TO 380
      LS3=IGCBS(LX+2*IS,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL SECEGY2(EP,D(LS3),EOLD,LD(LS3))
      IEP = 1
C       DETERMINE THE PHOTON2 MULTIPLICITY (YP)
  180 YP=SIGP/SIGN
      GO TO 330
C       NO PHOTON2 DATA WAS FOUND FOR THE PARTICULAR NEUTRON MT
C       REACTION OR FOR NEUTRON MT=4, THEREFORE CHECK THE PHOTON2
C       PRODUCTION DICTIONARY TO SEE IF THERE IS PHOTON2 DATA
C       CORRESPONDING TO MT=3 (THE CATCH-ALL MT)
  190 DO 200 IX=1,NNTX
         MTG=LGCB(2*IX-1,IIN)
         IF(MTG.EQ.3)GO TO 210
  200 CONTINUE
      GO TO 360
C       PHOTON2 DATA FOUND CORRESPONDING TO MT=3
  210 L1=LGCB2(2*IX,IIN)
      IF(L1.EQ.0)GO TO 370
      LS1=IGCBS2(2*IX,IIN)+LMOX4
      LEN=L1/2
      CALL TBSPLT2(D(LS1),EOLD,LEN,SIGP)
      IF(SIGP.EQ.0.0)GO TO 360
      LS2=IGCBS(2*IX,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL PARTXS2(D(LS2),LD(LS2),EOLD,SIGP,EP)
      IEP = 2
      IF(EP.GT.0.0)GO TO 240
C       DISCRETE PHOTON2 ENERGY WAS NOT SELECTED (EP=0.0)
C       CHECK SECONDARY PHOTON2 DISTRIBUTION (FILE 15) FOR EP
      DO 220 IS=1,NNTS
         MTGS=LGCB(LX+2*IS-1,IIN)
         IF(MTGS.EQ.3)GO TO 230
  220 CONTINUE
      GO TO 380
  230 L1=LGCB(LX+2*IS,IIN)
      IF(L1.EQ.0)GO TO 380
      LS3=IGCBS(LX+2*IS,IIN)+LMOX2
C       DETERMINE EXIT PHOTON2 ENERGY (EP)
      CALL SECEGY2(EP,D(LS3),EOLD,LD(LS3))
      IEP = 1
C       THE PHOTON2 WAS SELECTED FROM PHOTON2 DATA FOR MT=3
C       TO OBTAIN THE CORRECT MULTIPLICITY, THE NEUTRON CROSS
C       SECTION FOR MT=3 MUST BE ADJUSTED TO REPRESENT THE SAME
C       DATA AS MT=3 DOES IN THE PHOTON2 DATA
  240 ID=2
C       OBTAIN NEUTRON ELASTIC SCATTERING CROSS SECTION
      L1=LDICT(ID,IIN)
      IF(L1.EQ.0)GO TO 250
      LS1=IDICTS(ID,IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),EOLD,LEN,XSIG2)
C       SUBTRACT THE ELASTIC SCATTERING CROSS SECTION FROM THE TOTAL
C       CROSS SECTION TO OBTAIN BASE NEUTRON MT=3 REACTION
      SIGMT3=SIGT-XSIG2
      GO TO 260
  250 SIGMT3=SIGT
  260 CONTINUE
C       SCAN THE PHOTON2 PRODUCTION DICTIONARY FOR ALL MT NUMBERS
C       NOT EQUAL TO MT=3
      DO 300 IX=1,NNTX
         MTG=LGCB(2*IX-1,IIN)
         IF(MTG.EQ.3)GO TO 300
         L1=LGCB2(2*IX,IIN)
         IF(L1.EQ.0)GO TO 370
         LS1=IGCBS2(2*IX,IIN)+LMOX4
         LEN=L1/2
         CALL TBSPLT2(D(LS1),EOLD,LEN,SIGEX)
C     IF THE TOTAL PHOTON2 PRODUCTION CROSS SECTION IS ZERO AT
C     THE NEUTRON ENERGY, THEN THE NEUTRON CROSS SECTION SHOULD
C     NOT BE SUBTRACTED FROM MT3 TO MAINTAIN PROPER NORMALIZATION
         IF(SIGEX.EQ.0.0)GO TO 300
C     SET THE NEUTRON DICTIONARY ID NUMBER CORRESPONDING TO MTG
         IF((MTG.LT.51).OR.(MTG.GT.91))GO TO 270
         ID=14
         IMT3=MTG-51
         ID=ID+IMT3
  270    IF(MTG.EQ.4)ID=3
         IF(MTG.EQ.16)ID=8
         IF(MTG.EQ.17)ID=9
         IF(MTG.EQ.18)ID=10
         IF(MTG.EQ.22)ID=11
         IF(MTG.EQ.24)ID=12
         IF(MTG.EQ.28)ID=13
         IF(MTG.EQ.102)ID=55
         IF(MTG.EQ.103)ID=56
         IF(MTG.EQ.104)ID=57
         IF(MTG.EQ.105)ID=58
         IF(MTG.EQ.106)ID=59
         IF(MTG.EQ.107)ID=60
         IF(MTG.EQ.108)ID=61
         IF(MTG.EQ.109)ID=62
         IF(MTG.EQ.111)ID=63
         IF(MTG.EQ.112)ID=64
         IF(MTG.EQ.113)ID=65
         IF(MTG.EQ.114)ID=66
C     OBTAIN THE NEUTRON CROSS SECTION CORRESPONDING TO MTG AND
C     SUBTRACT IT OFF OF THE BASE NEUTRON MT=3 CROSS SECTION
         L1=LDICT(ID,IIN)
         IF(L1.EQ.0)GO TO 280
         LS1=IDICTS(ID,IIN)+LMOX2
         LEN=L1/2
         CALL TBSPLT2(D(LS1),EOLD,LEN,XSIG)
         GO TO 290
  280    XSIG=0.0
  290    SIGMT3=SIGMT3-XSIG
         IF(SIGMT3.LE.0.0)GO TO 310
  300 CONTINUE
C    DETERMINE THE PHOTON2 MULTIPLICITY (YP)
      YP=SIGP/SIGMT3
      IF(YP.GE.100.0)GO TO 310
      GO TO 330
  310 CONTINUE
C       THIS SECTION OF CODING IS INCLUDED TO ACCOUNT FOR ANY
C       ENDF/B DATA INCONSISTENCY WHICH COULD YIELD A PHOTON2 OF
C       CONSIDERABLE WEIGHT.  THE FOLLOWING CODING WILL SAMPLE THE
C       PHOTON2 WEIGHT FROM THE GENERAL PHOTON2 YIELD ARRAY AND
C       ADJUST THE WEIGHT TO PHOTON2S PER NON-ELASTIC COLLISION.
      L1=LGAM(IIN)
      IF(L1.EQ.0)GO TO 320
      LS1=IGAMS(IIN)+LMOX2
      LEN=L1/2
      CALL TBSPLT2(D(LS1),EOLD,LEN,YP)
      YP=(YP*SIGT)/(SIGT-XSIG2)
      GO TO 330
  320 YP=1.00
C       THE FOLLOWING SECTION OF CODING IS INCLUDED TO DISTRIBUTE
C       THE WEIGHT ENDF/B-V DATA MAY GIVE A PARTICULAR PHOTON2.
C       FOR EXAMPLE, ENDF/B-V DATA MAY ASSIGN A MULITPLICITY OF
C       75 TO A PARTICULAR PHOTON2.  BECAUSE SUCH A PHOTON2 COULD
C       CONSIDERABLY MODIFY THE RESULTS OF A DETECTOR RESPONSE, THE
C       MULTIPLICITY (PHOTON2 WEIGHT) IS DISTRIBUTED TO SEVERAL
C       PHOTON2S (SPLITTING OF SORTS) WITH BOTH WEIGHT AND ENERGY
C       BEING CONSERVED.  THIS RARELY OCCURS BUT IS NECESSARY.
  330 CONTINUE
      MGPAR = INT(FLOAT(MAXPAR)*0.7)
C
C for a photon2 multiplicity > 1.01 a poisson distribution is sampled
C for the actually generated multiplicity (with mean YP)
C
      IF(YP.GT.1.01) THEN
C
C use poisson distribution
C
  340   CALL G3POISS(YP,NUMBG,1)
        IGTRY=IGTRY+1
        IF(NUMBG.GT.INT(4.*YP).OR.
     +     NUMBG.GT.MGPAR.AND.IGTRY.LT.5) GOTO 340
      ELSE
C  YP <= 1.01
C number of photon2s generated = INT(YP)
C plus an additional photon2 if YP-INT(YP) > random number
C CZ 21.8.95
        NUMBG = INT(YP)
        IF((YP-FLOAT(NUMBG)).GT.FLTRNF2(0)) NUMBG = NUMBG + 1
      ENDIF
      NUMBG=MIN(NUMBG,MGPAR)
C Allow 0 Photon2s to be generated
      IF(NUMBG.EQ.0) RETURN
      EPTOT = YP*EP
      EPSUM = 0.0
      DO 350 I=1,NUMBG
C       ASSUME ISOTROPIC PHOTON2 EMISSION IN THE LABORATORY SYSTEM
         CALL GTISO2(U1,V1,W1)
C       SET THE PHOTON2 EXIT PARAMETERS
         UP=U1
         VP=V1
         WP=W1
         AGEP=AGE
         MTP=MT
C re-sample photon2 energy depending on model used CZ 13.8.92
         IF(IEP.EQ.2) THEN
            CALL PARTXS2(D(LS2),LD(LS2),EOLD,SIGP,EP1)
            IF(EP1.GT.0.0) EP=EP1
         ENDIF
         IF(IEP.EQ.1) THEN
            CALL SECEGY2(EP1,D(LS3),EOLD,LD(LS3))
            IF(EP1.GT.0.0) EP=EP1
         ENDIF
         EPSUM = EPSUM+EP
C check for energy conservation
         IF(EPSUM.GT.EPTOT.OR.I.EQ.NUMBG) EP = EPTOT-EPSUM+EP
C       STORE THE PHOTON2
         CALL STOPAR2(IDGAMA,NGAMA)
C end photon2 production when energy is used up  CZ 13.8.92
         IF(EPSUM.GT.EPTOT) GOTO 360
  350 CONTINUE
  360 RETURN
  370 WRITE(IOUT,10000)
10000 FORMAT(' PHOTON2: THE PHOTON2 PRODUCTION ',
     +       'CROSS SECTION DATA WAS NOT FOUND (L1=0)')
      GOTO 390
  380 WRITE(IOUT,10100)
10100 FORMAT(' PHOTON2: NO SECONDARY ENERGY ',
     +   'DISTRIBUTION WAS FOUND FOR THE CONTINUUM REACTION CHOSEN')
  390 WRITE(6,*) ' CALOR: ERROR in PHOTON2 ===> STOP '
      STOP
      END
*CMZ :  1.05/03 27/06/2001  17.54.25  by  Christian Zeitnitz
*-- Author :
C*********************************************************************
      FUNCTION RNMAXF2(T)
C T := most probable value of distribution
C*********************************************************************
      DATA FF/0./
      SAVE FF,R1SQ,W,U
      U=EXPRNF2(U)
      IF(FF) 30 ,10 ,30
   10 R1=FLTRNF2(0)
      R2=FLTRNF2(0)
      R1SQ=R1*R1
      R2SQ=R2*R2
      RSQ=R1SQ+R2SQ
      IF(RSQ-1.) 20 ,20 ,10
   20 W=EXPRNF2(W)/RSQ
      FF=1.
      RNMAXF2=(R2SQ*W+U)*T
      GO TO 40
   30 FF=0.
      RNMAXF2=(R1SQ*W+U)*T
   40 RETURN
      END
*CMZ :  1.04/00 02/02/95  09.26.27  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SECEGY2(EX,FSE,E,IFSE)
C       THIS ROUTINE SELECTS A PARTIAL ENERGY DISTRIBUTION
C       TO SAMPLE THE EXIT ENERGY FROM
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION FSE(*),IFSE(*)
      SAVE
      EX = 0.0
      IPP=1
      N=1
      IP=1
      R=FLTRNF2(0)
      NK=IFSE(IP)
      PROB=0.
   10 IP=IP+1
      LF=IFSE(IP)
      IP=IP+1
C       TEMP FIX UP
      U=FSE(IP)
      IF(LF.EQ.11)U=FLOAT(IFSE(IP))
      IP=IP+1
      NR=IFSE(IP)
      IPR=IP
      IP=IP+1
      NP=IFSE(IP)
      IP=IP+2*NR
   20 CONTINUE
      DO 30 I=1,NP
         IP=IP+2
C       IF E IS LESS THAN THE LOWEST ENERGY OF THE MESH, THEN THE
C       PROBABILITY WILL EQUAL ZERO FOR SELECTING THAT DISTRIBUTION
         IF(E.LT.FSE(IP-1))GO TO 50
   30 CONTINUE
C       TRY THE NEXT PARTIAL DISTRIBUTION
   40 N=N+1
      IF(N.GT.NK)GO TO 170
      IF(LF.EQ.1)GO TO 100
      IF(LF.EQ.5)GO TO 120
      IF((LF.EQ.7).OR.(LF.EQ.9))GO TO 130
      GO TO 140
   50 IF(I.NE.1)GO TO 70
      IF(E+CADIG2(E).LT.FSE(IP-1))GO TO 60
      E=E+CADIG2(E)
      IP=IP-2
      GO TO 20
   60 CONTINUE
      IP=IP+(NP-1)*2
      GO TO 40
C       DETERMINE THE INTERP2OLATING SCHEME
   70 CONTINUE
      DO 80 J=1,NR
         J1=IPR+2*J
         IF(I.LE.IFSE(J1))GO TO 90
   80 CONTINUE
   90 IS=IFSE(J1+1)
      CALL INTERP2(E,P,FSE(IP-3),FSE(IP-2),FSE(IP-1),FSE(IP),IS)
      PROB=PROB+P
      IF(R.LE.PROB)GO TO 150
      IP=IP+2*(NP-I)
      GO TO 40
C       SKIP THE DATA FOR LF EQUAL ONE
  100 IP=IP+1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=IP+2*NR+1
      DO 110 I=1,NE
         IP=IP+2
         NR=IFSE(IP)
         IP=IP+1
         NP=IFSE(IP)
         IP=IP+2*NR+2*NP
  110 CONTINUE
      GO TO 10
C       SKIP THE DATA FOR LF EQUAL FIVE
  120 IP=IP+1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=IP+2*NR+1
      IP=IP+2*NE
      IP=IP+1
      NR=IFSE(IP)
      NF=IFSE(IP+1)
      IP=IP+2*NF+2*NR+1
      GO TO 10
C       SKIP THE DATA FOR LF EQUAL SEVEN, AND LF EQUAL NINE
  130 IP=IP+1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=IP+2*NR+1
      IP=IP+2*NE
      GO TO 10
C       SKIP THE DATA FOR LF EQUAL ELEVEN
  140 IP=IP+1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=IP+2*NR+1
      IP=IP+2*NE
      IP=IP+1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=IP+2*NR+1
      IP=IP+2*NE
      GO TO 10
C       NOW SELECT THE SECONDARY ENERGY FROM THE CHOSEN DISTRIBUTION
  150 IP=IP+2*(NP-I)
  160 CONTINUE
      IF(LF.EQ.1)CALL SECLF12(FSE(IP+1),IFSE(IP+1),EX,U,E)
      IF(LF.EQ.5)CALL SECLF52(FSE(IP+1),IFSE(IP+1),EX,U,E)
      IF(LF.EQ.7)CALL SECLF72(FSE(IP+1),IFSE(IP+1),EX,U,E)
      IF(LF.EQ.9)CALL SECLF92(FSE(IP+1),IFSE(IP+1),EX,U,E)
      IF(LF.EQ.11)CALL SECL112(FSE(IP+1),IFSE(IP+1),EX,U,E)
      RETURN
  170 CONTINUE
C       TEMP CARD
      LF=IFSE(IPP+1)
      U=FSE(IPP+2)
      IF(LF.EQ.11)U=FLOAT(IFSE(IPP+2))
      NR=IFSE(IPP+3)
      NP=IFSE(IPP+4)
      IP=2*NR+2*NP+5
      GO TO 160
      END
*CMZ :  1.04/00 02/02/95  09.23.46  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SECL112(FSE,IFSE,EX,U,E)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM
C       AN ENERGY DEPENDENT WATT SPECTRUM
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION FSE(*),IFSE(*)
      SAVE
      IP=1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=2*NR+1
      EMAX=E-U
C       DETERMINE A
      DO 10 I=1,NE
         IP=IP+2
         IF(E.LE.FSE(IP))GO TO 20
   10 CONTINUE
      GO TO 30
   20 IF(I.EQ.1)GO TO 40
C       DETERMINE THE INTERP2OLATING SCHEME
      CALL INTSCH2(IFSE,I,IS,NR)
      E1=FSE(IP-2)
      E2=FSE(IP)
      T1=FSE(IP-1)
      T2=FSE(IP+1)
      CALL INTERP2(E,A,E1,T1,E2,T2,IS)
      GO TO 50
C       INCIDENT ENERGY IS ABOVE THE LAST INCIDENT ENERGY GIVEN
C       USE THE LAST DISTRIBUTION
   30 IP=2+2*NR+2*NE
      A=FSE(IP)
      GO TO 50
C       INCIDENT ENERGY IS BELOW THE FIRST INCIDENT ENERGY GIVEN
C       USE THE FIRST DISTRIBUTION
   40 A=FSE(4+2*NR)
C       DETERMINE B
   50 IP=3+2*NR+2*NE
      NR1=IFSE(IP)
      NF=IFSE(IP+1)
      IP=2*NR+2*NE+2*NR1+3
      DO 60  I=1,NF
         IP=IP+2
         IF(E.LE.FSE(IP))GO TO 70
   60 CONTINUE
      GO TO 80
   70 IF(I.EQ.1)GO TO 90
      CALL INTSCH2(IFSE(2*NR+2*NE+3),I,IS,NR1)
      E1=FSE(IP-2)
      E2=FSE(IP)
      T1=FSE(IP-1)
      T2=FSE(IP+1)
      CALL INTERP2(E,B,E1,T1,E2,T2,IS)
      GO TO 100
   80 IP=2*NR+2*NF+2*NE+2*NR1+4
      B=FSE(IP)
      GO TO 100
   90 B=FSE(IP+1)
C       SELECT THE EXIT ENERGY FROM THE WATT SPECTRUM
  100 EX=FISRNF2(A,B)
      IF(EX.LE.EMAX)RETURN
      EX=EMAX
      RETURN
      END
*CMZ :  1.01/07 24/06/93  21.32.11  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SECLF12(FSE,IFSE,EX,U,E)
C        THIS ROUTINE SAMPLES AN EXIT ENERGY FROM
C        A TABULATED DISTRIBUTION
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION FSE(*),IFSE(*)
      SAVE
      C=0.
      IP=1
      NRE=IFSE(IP)
      NE=IFSE(IP+1)
      IP=IP+2*NRE+1
C       FIND THE TWO INCIDENT ENERGY DISTRIBUTIONS THAT BOUND E
C       INCIDENT ENERGY IS BELOW THE FIRST INCIDENT ENERGY GIVEN
C       USE THE FIRST DISTRIBUTION
      IP=IP+1
      IE=1
      E1=FSE(IP)
      IP1=IP
      IF(E.GT.E1)GO TO 10
      IPR=IP+1
      NR=IFSE(IPR)
      NP=IFSE(IPR+1)
      GO TO 50
   10 IP=IP+1
      IPR1=IP
      NP1=IFSE(IP+1)
      IP=IP+2*IFSE(IPR1)+1
      IP=IP+2*NP1
   20 IE=IE+1
      IP=IP+1
C       INCIDENT ENERGY IS ABOVE THE LAST INCIDENT ENERGY GIVEN
C       USE THE LAST DISTRIBUTION
      IF(IE.GT.NE)GO TO 40
      E2=FSE(IP)
      IF(E.LE.E2)GO TO 30
      E1=E2
      IP1=IP
      IP=IP+1
      IPR1=IP
      NP1=IFSE(IP+1)
      IP=IP+2*IFSE(IPR1)+1
      IP=IP+2*NP1
      GO TO 20
   30 IP2=IP
      IP=IP+1
      IPR2=IP
      NP2=IFSE(IP+1)
      IP=IP+2*IFSE(IPR2)+1
C       DETERMINE THE INTERP2OLATING SCHEME
      CALL INTSCH2(IFSE,IE,IS,NRE)
C       SELECT THE DISTRIBUTION TO SAMPLE FROM
      R=FLTRNF2(0)
C       INTERP2OLATION SCHEMES OF 1 (CONSTANT) OR 2 (LINEAR) ALLOWED
      IF(IS.GT.2)GO TO 110
      PROB=(E2-E)/(E2-E1)
      IF(IS.EQ.1)PROB=1.0
      IF(R.LE.PROB)GO TO 40
C       SELECT FROM THE SECOND DISTRIBUTION
      NP=NP2
      IP=IP2
      IPR=IPR2
      GO TO 50
C       SELECT FROM THE FIRST DISTRIBUTION
C       OR FROM THE LAST INCIDENT ENERGY
   40 NP=NP1
      IP=IP1
      IPR=IPR1
C       SELECT THE EXIT ENERGY FROM THE TABULATED DISTRIBUTION
   50 CONTINUE
      ITRY = 0
   60 CONTINUE
      PROB=0.
      R=FLTRNF2(0)
      NR=2*IFSE(IPR)+1
      DO 90  I=1,NP
         CALL INTSCH2(IFSE(IPR),NP,IS,IFSE(IPR))
         N=IP+NR+1+2*I
         PROB1=PROB
         IF(I.EQ.1)GO TO 90
         IF(IS.EQ.1)GO TO 70
         IF(IS.GT.2)GO TO 110
         PROB=PROB+(FSE(N)+FSE(N-2))*(FSE(N-1)-FSE(N-3))/2.
         GO TO 80
   70    PROB=PROB+FSE(N-2)*(FSE(N-1)-FSE(N-3))
   80    IF(R.LE.PROB)GO TO 100
   90 CONTINUE
      ITRY = ITRY + 1
      IF(ITRY.LT.5) GOTO 60
      IF(R.LT..998)GO TO 120
  100 EX=FSE(N-3)+(R-PROB1)*(FSE(N-1)-FSE(N-3))/(PROB-PROB1)
      RETURN
  110 WRITE(IOUT,10000)IS
10000 FORMAT(' MICAP: INTERP2OLATION SCHEME=',I3,' IN SECLF12')
      GOTO 130
  120 WRITE(IOUT,10100)R,PROB
10100 FORMAT(' MICAP: EXIT ENERGY NOT SELECTED IN SECLF12',1P2E13.5)
  130 WRITE(6,*) ' CALOR: ERROR in SECLF12 =====> STOP '
      STOP
      END
*CMZ :  1.04/00 02/02/95  09.24.15  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SECLF52(FSE,IFSE,EX,U,E)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM
C       A GENERAL EVAPORATION SPECTRUM
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION FSE(*),IFSE(*)
      SAVE
C       DETERMINE THETA
      IP=1
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=2*NR+IP
      EMAX=E-U
      R=FLTRNF2(0)
      DO 10 I=1,NE
         IP=IP+2
         IF(E.LE.FSE(IP))GO TO 20
   10 CONTINUE
      GO TO 80
   20 IF(I.EQ.1)GO TO 90
C       DETERMINE THE INTERP2OLATING SCHEME
      CALL INTSCH2(IFSE,I,IS,NR)
      E2=FSE(IP)
      E1=FSE(IP-2)
      CALL INTERP2(E,THETA,E1,FSE(IP-1),E2,FSE(IP+1),IS)
      IP=IP+2+(NE-I)*2
C       DETERMINE X
   30 NF=IFSE(IP+1)
      NR=IFSE(IP)
      IPR=IP
      IP=IP+1+2*NR
      PROB=0.
      DO 60 I=1,NF
         N=IP+2*I
         PROB1=PROB
         CALL INTSCH2(IFSE(IPR),I,IS,NR)
         IF(I.EQ.1)GO TO 60
         IF(IS.EQ.1)GO TO 40
         IF(IS.GT.2)GO TO 100
         PROB=PROB+(FSE(N)+FSE(N-2))*(FSE(N-1)-FSE(N-3))/2.
         GO TO 50
   40    PROB=PROB+FSE(N-2)*(FSE(N-1)-FSE(N-3))
   50    CONTINUE
         IF(R.LE.PROB)GO TO 70
   60 CONTINUE
   70 X=FSE(N-3)+(R-PROB1)*(FSE(N-1)-FSE(N-3))/(PROB-PROB1)
C       SELECT THE EXIT ENERGY FROM THE GENERAL EVAPORATION SPECTRUM
      EX=THETA*X
      IF(EX.LE.EMAX)RETURN
      EX=EMAX
      RETURN
C       INCIDENT ENERGY IS ABOVE THE LAST INCIDENT ENERGY GIVEN
C       USE THE LAST DISTRIBUTION
   80 THETA=FSE(IP+1)
      IP=IP+2
      GO TO 30
C       INCIDENT ENERGY IS BELOW THE FIRST INCIDENT ENERGY GIVEN
C       USE THE FIRST DISTRIBUTION
   90 THETA=FSE(IP+1)
      IP=IP+2*(NE-I)+2
      GO TO 30
  100 WRITE(IOUT,10100)IS
10100 FORMAT(' MICAP: INTERP2OLATION SCHEME=',I3,' IN SECLF52')
      WRITE(6,*) ' CALOR: ERROR in SECLF52 =====> STOP '
      STOP
      END
*CMZ :  1.04/00 02/02/95  09.24.44  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SECLF72(FSE,IFSE,EX,U,E)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM
C       A SIMPLE FISSION SPECTRUM
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION FSE(*),IFSE(*)
      SAVE
C       DETERMINE THETA
      IP=1
      EMAX=E-U
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=2*NR+1
      DO 10 I=1,NE
         IP=IP+2
         IF(E.LE.FSE(IP))GO TO 20
   10 CONTINUE
      GO TO 30
   20 IF(I.EQ.1)GO TO 40
C       DETERMINE THE INTERP2OLATING SCHEME
      CALL INTSCH2(IFSE,I,IS,NR)
      E1=FSE(IP-2)
      E2=FSE(IP)
      CALL INTERP2(E,THETA,E1,FSE(IP-1),E2,FSE(IP+1),IS)
      GO TO 50
C       INCIDENT ENERGY IS ABOVE THE LAST INCIDENT ENERGY GIVEN
C       USE THE LAST DISTRIBUTION
   30 THETA=FSE(IP+1)
      GO TO 50
C       INCIDENT ENERGY IS BELOW THE FIRST INCIDENT ENERGY GIVEN
C       USE THE FIRST DISTRIBUTION
   40 THETA=FSE(IP+1)
C       SELECT THE EXIT ENERGY FROM THE FISSION SPECTRUM
   50 R1=FLTRNF2(0)
      R2=FLTRNF2(0)
      S=R1**2+R2**2
      IF(S.GT.1.)GO TO 50
      TAU=(-ALOG(S)/S)*(R1**2)
      R=FLTRNF2(0)
      W=-ALOG(R)+TAU
      EX=THETA*W
      IF(EX.LE.EMAX)RETURN
      EX=EMAX
      RETURN
      END
*CMZ :  1.04/00 02/02/95  09.25.31  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SECLF92(FSE,IFSE,EX,U,E)
C       THIS ROUTINE SAMPLES AN EXIT ENERGY FROM
C       AN EVAPORATION SPECTRUM
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
      DIMENSION FSE(*),IFSE(*)
      SAVE
C       DETERMINE THETA
      IP=1
      EMAX=E-U
      NR=IFSE(IP)
      NE=IFSE(IP+1)
      IP=2*NR+1
      DO 10 I=1,NE
         IP=IP+2
         IF(E.LE.FSE(IP))GO TO 20
   10 CONTINUE
      GO TO 30
   20 IF(I.EQ.1)GO TO 40
C       DETERMINE THE INTERP2OLATING SCHEME
      CALL INTSCH2(IFSE,I,IS,NR)
      E1=FSE(IP-2)
      E2=FSE(IP)
      CALL INTERP2(E,THETA,E1,FSE(IP-1),E2,FSE(IP+1),IS)
      GO TO 50
C       INCIDENT ENERGY IS ABOVE THE LAST INCIDENT ENERGY GIVEN
C       USE THE LAST DISTRIBUTION
   30 THETA=FSE(IP+1)
      GO TO 50
C       INCIDENT ENERGY IS BELOW THE FIRST INCIDENT ENERGY GIVEN
C       USE THE FIRST DISTRIBUTION
   40 THETA=FSE(IP+1)
C       SELECT THE EXIT ENERGY FROM THE EVAPORATION SPECTRUM
   50 R1=FLTRNF2(0)
      R2=FLTRNF2(0)
      W=-ALOG(R1*R2)
      EX=THETA*W
      IF(EX.LE.EMAX)RETURN
      EX=EMAX
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.49  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   03/08/92
      SUBROUTINE STOPAR2(ID,NP)
C store particle in MPSTOR common
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEND.
C
      NPSTOR = NPSTOR + 1
      IF(NPSTOR.GT.MAXPAR) THEN
         WRITE(IOUT,'('' MICAP :  Cant store particle; bank full'',    '
     +   //'                 '' ID='',I3,'' NPSTOR='',I5)') ID,NPSTOR
         NPSTOR = NPSTOR - 1
      ELSE
         EN(NPSTOR) = EP
         UN(NPSTOR) = UP
         VN(NPSTOR) = VP
         WN(NPSTOR) = WP
         AMN(NPSTOR) = AMP
         ZMN(NPSTOR) = ZMP
         AGEN(NPSTOR) = AGEP
         MTN(NPSTOR) = MTP
         IDN(NPSTOR) = ID
         NP = NP + 1
      ENDIF
      RETURN
      END
*CMZ :  0.92/00 02/12/92  16.02.33  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE TBSPLT2(A,E,NP,Y)
C       THIS ROUTINE DETERMINES A CROSS SECTION AT A GIVEN
C       ENERGY FROM A CROSS SECTION VERSUS ENERGY TABLE USING
C       A TABLE SPLITTING METHOD
      DIMENSION A(1)
      SAVE
      IPP=1
      IF(E.LE.A(1))GO TO 40
      IF(E.GE.A(2*NP-1))GO TO 50
      INDXH=NP
      INDXL=0
   10 IF(INDXL+1.EQ.INDXH)GO TO 30
      J=(INDXH+INDXL)/2
      N=2*J-1
      IF(E.LE.A(N))GO TO 20
      INDXL=J
      GO TO 10
   20 INDXH=J
      GO TO 10
   30 N=2*INDXH-1
      Y=A(N-1)+(E-A(N-2))*(A(N+1)-A(N-1))/(A(N)-A(N-2))
      RETURN
   40 Y=A(IPP+1)
      RETURN
   50 Y=A(2*NP)
      RETURN
      END
*CMZ :  1.05/03 27/06/2001  18.34.49  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE THRMSC2(D,LD,XTHRMS,ITHRMS,LTHRM,E,U,V,W,TEMP,FM,AWR,
     +                  IIN,IFLG,IOUT)
C      THIS ROUTINE CONTROLS SELECTION OF THE NEUTRON EXIT ENERGY
C      IN THE THERMAL DATA RANGE
*KEEP,MUPSCA.
      COMMON/MUPSCA/ERFGM
*KEND.
      DIMENSION D(*),LD(*),XTHRMS(*),ITHRMS(*),LTHRM(*),AWR(*)
      REAL HMASSN/0.5044905/,SPI/1.1283792/
C       HMASSN EQUALS ONE-HALF THE NEUTRON MASS
C       SPI EQUALS TWO DIVIDED BY THE SQUARE ROOT OF PI
C       CONVERT TEMPERATURE FROM DEGREES KELVIN TO EV
      DATA BK/8.6167E-5/
      SAVE
C
      TDK=BK*TEMP
      AAWR=AWR(IIN)
      IFLG=0
      NE=ITHRMS(IIN)
      IF(NE.LE.0)GO TO 10
      EO=E
      NP7=ITHRMS(IIN+1)
      NB7=ITHRMS(IIN+2)
      CT=ITHRMS(IIN+3)
      LENMD=ITHRMS(IIN+4)
      N=NB7*NE
      CALL THRSEL2(NE,NP7,NB7,E,EOUT,FM,CT,XTHRMS(IIN+5),
     + XTHRMS(IIN+5+NE),XTHRMS(IIN+5+NE+NP7),
     + XTHRMS(IIN+5+NE+NP7+NB7),
     + XTHRMS(IIN+5+2*NE+NP7+NB7),XTHRMS(IIN+5+2*NE+NP7+NB7+N),
     + XTHRMS(IIN+5+2*NE+NP7+NB7+N+LENMD),AWR,IIN,
     + ITHRMS(IIN+5+2*NE+NP7+NB7+N+LENMD+NP7*NB7),
     + ITHRMS(IIN+5+2*NE+NP7+NB7+N),IOUT)
      E=EOUT
C       IFLG EQUAL TO ONE IMPLIES (FM) IN LABORATORY SYSTEM
      IFLG=1
      RETURN
C       FREE GAS MODEL
   10 CONTINUE
C       SPD IS THE SPEED OF THE INCIDENT NEUTRON
      SPD=SQRT(E/HMASSN)
      TAUN=SPI*SQRT(2.0*TDK/AAWR)
      PTEST=SPD/(SPD+TAUN)
C       UO, VO, AND WO ARE THE VELOCITY COMPONENTS OF THE INCIDENT
C       NEUTRON IN TERMS OF THE NEUTRON SPEED
      UO=SPD*U
      VO=SPD*V
      WO=SPD*W
   20 CONTINUE
      IF(PTEST.GT.FLTRNF2(0))GO TO 30
      ETA=-ALOG(FLTRNF2(0)*FLTRNF2(0))*TDK
      GO TO 40
   30 CONTINUE
      ETA=RNMAXF2(TDK)
   40 CONTINUE
C       ERFGM IS THE INITIAL ENERGY OF THE TARGET NUCLEUS
      ERFGM=ETA
C       ETA IS THE SPEED OF THE TARGET NUCLEUS
      ETA=SQRT(2.0*ETA/AAWR)
C       UN, VN, AND WN ARE THE VELOCITY COMPONENTS OF THE TARGET
C       NUCLEUS IN TERMS OF THE TARGET NUCLEUS SPEED
      CALL GTISO2(UN,VN,WN)
      UN=UN*ETA
      VN=VN*ETA
      WN=WN*ETA
      VRELSQ=(UO-UN)**2+(VO-VN)**2+(WO-WN)**2
      F2=FLTRNF2(0)**2
      V2=VRELSQ/(SPD+ETA)**2
      IF(F2.GT.V2)GO TO 20
      VREL=SQRT(VRELSQ)
      ALPHA=1.0/(AAWR+1.0)
      BETA=1.0-ALPHA
      CALL GTISO2(UA,VA,WA)
      UO=UO*ALPHA+BETA*(UN+VREL*UA)
      VO=VO*ALPHA+BETA*(VN+VREL*VA)
      WO=WO*ALPHA+BETA*(WN+VREL*WA)
      SPDSQ=UO*UO+VO*VO+WO*WO
C       E IS THE EXIT ENERGY OF THE NEUTRON
      E=HMASSN*SPDSQ
      SPD=1.0/SQRT(SPDSQ)
      FM=(U*UO+V*VO+W*WO)*SPD
C       U, V, AND W ARE THE EXIT NEUTRON DIRECTION COSINES
      U=UO*SPD
      V=VO*SPD
      W=WO*SPD
C       IFLG EQUAL TO TWO IMPLIES (U,V,W) IN LABORATORY SYSTEM
      IFLG=2
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.49  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE THRSEL2(NE,NP7,NB7,E,EOUT,FM,TDK,ETH,ALPHA,BETA,W,
     +                  PMUPS,PMDS,F,AWR,IIN,IPTMD,IPMDS,IOUT)
C      THIS ROUTINE SELECTS THE EXIT ENERGY AND SCATTERING ANGLE
C      FROM S(ALPHA,BETA) DATA TABLES
      DIMENSION ETH(*),ALPHA(*),BETA(*),ABETA2(2),PMDS(*),
     +   IPTMD(NE),W(NE),IPMDS(*),PMUPS(NB7,NE),F(NP7,NB7),AWR(*)
      SAVE
C
      AAWR=AWR(IIN)
      DO 10 IE=1,NE
         IF(E.LT.ETH(IE))GO TO 20
   10 CONTINUE
      INDX=NE
      GO TO 30
   20 INDX=IE
      IF(INDX.EQ.1)GO TO 30
      R=FLTRNF2(0)
      DELE=(ETH(INDX)-E)/(ETH(INDX)-ETH(INDX-1))
      DELEN=DELE
      GO TO 40
   30 DELEN=1.0
      INDX=2
   40 PROB=DELEN*W(INDX-1)+(1.0-DELEN)*W(INDX)
      IF(R.LE.PROB)GO TO 120
C       NEUTRON DOWNSCATTERS
      R=FLTRNF2(0)
      DO 90 I=1,2
         IP=IPTMD(INDX)
         NB=IPMDS(IP)
         DO 50 IB=1,NB
            IF(R.LE.PMDS(IP+NB+IB))GO TO 60
   50    CONTINUE
         WRITE(IOUT,10000)PMDS(IP+2*NB)
10000 FORMAT(' MICAP: CUMULATIVE DOWNSCATTER DIST. DOES NOT END ',
     +       'IN 1.0 IN THRSEL2',E12.4)
         PRINT *,' CALOR: ERROR in MICAP ====> STOP '
         STOP
   60    IF(IB.EQ.1)GO TO 70
         DELE=(PMDS(IP+NB+IB)-R)/(PMDS(IP+NB+IB)-PMDS(IP+NB+IB-1))
         ABETA=DELE*(PMDS(IP+IB-1)-PMDS(IP+IB))+PMDS(IP+IB)
         GO TO 80
   70    ABETA=BETA(IB)
   80    ABETA2(I)=ABETA
         INDX=INDX-1
   90 CONTINUE
      ABETA=DELEN*ABETA2(2)+(1.0-DELEN)*ABETA2(1)
      EOUT=E-TDK*ABETA
      IF(EOUT.LT.1.0E-05)EOUT=1.0E-05
      DO 100 IB=1,NB7
         IF(ABETA.LE.BETA(IB))GO TO 110
  100 CONTINUE
      IB=NB7
  110 DELE=(ABETA-BETA(IB))/(BETA(IB-1)-BETA(IB))
      GO TO 180
C       NEUTRON UPSCATTERS
  120 R=FLTRNF2(0)
      DO 170 I=1,2
         DO 130 IB=1,NB7
            IF(R.LE.PMUPS(IB,INDX))GO TO 140
  130    CONTINUE
         WRITE(IOUT,10100)PMUPS(NB7,INDX)
10100 FORMAT(' MICAP: CUMULATIVE UPSCATTER DIST. DOES NOT END ',
     +       'IN 1.0 IN THRSEL2',E12.4)
         PRINT *,' CALOR: ERROR in MICAP ====> STOP '
         STOP
  140    IF(IB.EQ.1)GO TO 150
         DELE=(PMUPS(IB,INDX)-R)/(PMUPS(IB,INDX)-PMUPS(IB-1,INDX))
         ABETA=DELE*(BETA(IB-1)-BETA(IB))+BETA(IB)
         GO TO 160
  150    WRITE(IOUT,10200)PMUPS(1,INDX)
10200 FORMAT(' MICAP: CUMULATIVE UPSCATTER DIST. DOES NOT BEGIN ',
     +       'AT 0.0 IN THRSEL2',E12.4)
         PRINT *,' CALOR: ERROR in MICAP ====> STOP '
         STOP
  160    ABETA2(I)=ABETA
         INDX=INDX-1
  170 CONTINUE
      ABETA=DELEN*ABETA2(2)+(1.0-DELEN)*ABETA2(1)
      EOUT=E+TDK*ABETA
C       SELECT ANGLE
  180 AMAX=(EOUT+E+2.0*SQRT(E*EOUT))/(AAWR*TDK)
      AMIN=(EOUT+E-2.0*SQRT(E*EOUT))/(AAWR*TDK)
      DO 190 IA=1,NP7
         IF(AMAX.LT.ALPHA(IA))GO TO 200
  190 CONTINUE
      IA=NP7
      DELA=0.0
      GO TO 210
  200 DELA=(ALPHA(IA)-AMAX)/(ALPHA(IA)-ALPHA(IA-1))
  210 F4=DELE*(F(IA,IB-1)-F(IA,IB))+F(IA,IB)
      F3=DELE*(F(IA-1,IB-1)-F(IA-1,IB))+F(IA-1,IB)
      F2=DELA*(F3-F4)+F4
      DO 220 IA=1,NP7
         IF(AMIN.LT.ALPHA(IA))GO TO 230
  220 CONTINUE
      IA=NP7
      DELA=0.0
      GO TO 240
  230 DELA=(ALPHA(IA)-AMIN)/(ALPHA(IA)-ALPHA(IA-1))
  240 F4=DELE*(F(IA,IB-1)-F(IA,IB))+F(IA,IB)
      F3=DELE*(F(IA-1,IB-1)-F(IA-1,IB))+F(IA-1,IB)
      F1=DELA*(F3-F4)+F4
      R=FLTRNF2(0)
      F0=R*F2+(1.0-R)*F1
      F1=0.0
      DO 250 IA=1,NP7
         F2=DELE*(F(IA,IB-1)-F(IA,IB))+F(IA,IB)
         IF(F0.LE.F2)GO TO 260
         F1=F2
  250 CONTINUE
  260 IF(F1.EQ.F2)GO TO 270
      DELA=(F2-F0)/(F2-F1)
      GO TO 280
  270 ALP=ALPHA(IA)
      GO TO 290
  280 ALP=DELA*ALPHA(IA-1)+(1.0-DELA)*ALPHA(IA)
  290 FM=(E+EOUT-ALP*AAWR*TDK)/(2.0*SQRT(E*EOUT))
      IF(ABS(FM).LE.1.0)RETURN
      WRITE(IOUT,10300)FM,E,EOUT,R,IA,IB
10300 FORMAT(' MICAP: ERROR IN THRSEL2, COSINE OF ANGLE >1'/,
     +' ',1P4E12.4,2I11)
      FM=2.0*FLTRNF2(0)-1.0
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.49  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE TREBOD2(D,LD,KZ1,KZ2,KZ3,A1,A2,A3,Z1,Z2,Z3,
     +                  ATAR,Q,MT)
C CZ July 30,1992 Simple aproach to get (N,PA), (N,T2A),(N,D2A)
C processes. This is TWOBOD2 extended to a third particle
C       THIS ROUTINE CALCULATES THE EXIT ENERGIES AND DIRECTIONAL
C       COSINES FOR THE CHARGED PARTICLE AND RECOIL NUCLEUS FOR
C       A THREE-BODY REACTION USING AN EVAPORATION SPECTRUM AND
C       MOMEMTUM BALANCE.  IT ALSO SETS ALL EXIT PARAMETERS FOR
C       THE COLLISION PRODUCTS AND STORES THEM IN THE RECOIL BANK.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*),ER1(3)
      SAVE
C loop over no. of emmitted particles CZ July 30,1992
      NPN = 1
      IF(MT.EQ.112) NPN = 2
      IF(MT.EQ.113) NPN = 3
      IF(MT.EQ.114) NPN = 3
      PRXO = 0.0
      PRYO = 0.0
      PRZO = 0.0
      DO 10  NP=1,NPN
C       CALCULATE THE COULOMB BARRIER (CB)
         CALL BARIER2(KZ1,KZ2,A1,A3,CB)
C       CALCULATE THE CHARGED PARTICLE EXIT ENERGY (EX)
         CALL CEVAP2(EOLD,Q,ATAR,CB,EX)
         E1=EX+CB
         ZMSS = Z2
         AMSS = A2
         KZZ = KZ2
         IF(NP.EQ.1) THEN
            ZMSS = Z1
            AMSS = A1
            KZZ = KZ1
         ENDIF
C       ASSUME ISOTROPIC CHARGED PARTICLE EMISSION IN THE LABORATORY
         CALL GTISO2(U1,V1,W1)
         PPN = SQRT(2.0*ZMSS*E1)
         PRXO = PRXO + U1*PPN
         PRYO = PRYO + V1*PPN
         PRZO = PRZO + W1*PPN
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
         XR=X
         YR=Y
         ZR=Z
         WATER=WTBC
         NZR=KZZ
         AGER=AGE
         NCOLR=NCOL
         MTNR=MT
         AR=AMSS
         ENIR=EOLD
         UNIR=UOLD
         VNIR=VOLD
         WNIR=WOLD
         ENOR=0.0
         UNOR=0.0
         VNOR=0.0
         WNOR=0.0
         WTNR=0.0
         QR=Q
         UR=U1
         VR=V1
         WR=W1
         ER=E1
C       STORE THE CHARGED PARTICLE IN THE RECOIL BANK
         EP = ER
         UP = UR
         VP = VR
         WP = WR
         AMP = AR
         ZMP = FLOAT(NZR)
         AGEP = AGE
         MTP = MT
         CALL STOPAR2(IDHEVY,NHEVY)
         A3 = A3 - A2
         Z3 = Z3 - Z2
         KZ3 = KZ3 - KZ2
   10 CONTINUE
      A3 = A3 + A2
      Z3 = Z3 + Z2
      KZ3 = KZ3 + KZ2
C       CALCULATE THE TOTAL MOMENTUM BEFORE THE COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*UOLD - PRXO
      PRY=PI*VOLD - PRYO
      PRZ=PI*WOLD - PRZO
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      U2=PRX/PR
      V2=PRY/PR
      W2=PRZ/PR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      XM = A2 * 931.075E6
      E2 = SQRT(PR**2+XM**2) - XM
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ3
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A3
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=0.0
      UNOR=0.0
      VNOR=0.0
      WNOR=0.0
      WTNR=0.0
      QR=Q
      UR=U2
      VR=V2
      WR=W2
      ER=E2
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AMP = AR
      ZMP = FLOAT(NZR)
      AGEP = AGE
      MTP = MT
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.04/03 15/02/95  14.00.42  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE TWOBOD2(D,LD,KZ1,KZ2,A1,A2,Z1,Z2,ATAR,Q,MT)
C       THIS ROUTINE CALCULATES THE EXIT ENERGIES AND DIRECTIONAL
C       COSINES FOR THE CHARGED PARTICLE AND RECOIL NUCLEUS FOR
C       A TWO-BODY REACTION USING AN EVAPORATION SPECTRUM AND
C       MOMEMTUM BALANCE.  IT ALSO SETS ALL EXIT PARAMETERS FOR
C       THE COLLISION PRODUCTS AND STORES THEM IN THE RECOIL BANK.
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MNUTRN.
      COMMON/MNUTRN/NAME,NAMEX,E,EOLD,NMED,MEDOLD,NREG,U,V,W,
     + UOLD,VOLD,WOLD,X,Y,Z,XOLD,YOLD,ZOLD,WATE,OLDWT,WTBC,
     + BLZNT,BLZON,AGE,OLDAGE,INEU,ENE(MAXNEU)
      INTEGER BLZNT
*KEEP,MRECOI.
      COMMON/MRECOI/NAMEXR,MTNR,NZR,NCOLR,AR,ER,UR,VR,WR,XR,YR,ZR,
     1WATER,AGER,ENIR,UNIR,VNIR,WNIR,ENOR,UNOR,VNOR,WNOR,WTNR,QR
*KEEP,MAPOLL.
      COMMON/MAPOLL/ETA,ETATH,ETAUSD,DEADWT(5),XTRA(10),ITERS,IFR,IFG,
     1ITSTR,NEWNM,NGEOM,NMEM,NMEMR,NMEMG,INALB,NDEAD(5),NPSCL(13)
*KEEP,MMASS.
      COMMON/MMASS/ZN,ZP,ZD,ZT,ZHE3,ZA,AN,AP,AD,AT,AHE3,AA
*KEEP,MPSTOR.
      PARAMETER(IDNEU  = 1)
      PARAMETER(IDHEVY = 2)
      PARAMETER(IDGAMA = 3)
      COMMON/ MPSTOR / EN(MAXPAR),UN(MAXPAR),VN(MAXPAR),WN(MAXPAR),
     +                 AGEN(MAXPAR),MTN(MAXPAR),AMN(MAXPAR),
     +                 ZMN(MAXPAR),IDN(MAXPAR),
     +                 EP,UP,VP,WP,MTP,AGEP,AMP,ZMP,
     +                 NNEU,NHEVY,NGAMA,NPSTOR
*KEND.
      DIMENSION D(*),LD(*)
      SAVE
      PRXO = 0.0
      PRYO = 0.0
      PRZO = 0.0
C loop over no. of emmitted particles CZ July 30,1992
      NPN = 1
      IF(MT.EQ.108) NPN = 2
      IF(MT.EQ.109) NPN = 3
      IF(MT.EQ.111) NPN = 2
C       CALCULATE THE COULOMB BARRIER (CB)
      CALL BARIER2(KZ1,KZ2,A1,A2,CB)
C       CALCULATE THE CHARGED PARTICLE EXIT ENERGY (EX)
      CALL CEVAP2(EOLD,Q,ATAR,CB,EX)
      E1=EX+CB
C calculate the massnumber and mass of the residual nucleus
      A2 = A2 - (NPN-1)*A1
      Z2 = Z2 - (NPN-1)*Z1
      IF(A2.LT.0.) A2 = 0.
      IF(Z2.LT.0.) Z2 = 0.
      IF(NPN.EQ.1) THEN
C for 1 final state particle the available kinetic energy is given
C by momentum and energy conservation
        E1 = E1*Z2/(Z1+Z2)
      ENDIF
      DO 10  NP=1,NPN
C       ASSUME ISOTROPIC CHARGED PARTICLE EMISSION IN THE LABORATORY
         CALL GTISO2(U1,V1,W1)
         IF(NPN.EQ.1) THEN
C only one final state particle -> use all the energy available
           PPN = SQRT(2.0*Z1*E1)
           EKN = E1
         ELSE
           IF(NP.LT.NPN) THEN
             EKN = E1*FLTRNF2(0)
           ELSE
             EKN = E1
           ENDIF
           E1 = E1 - EKN
           PPN = SQRT(2.0*Z1*EKN)
         ENDIF
         PRXO = PRXO + U1*PPN
         PRYO = PRYO + V1*PPN
         PRZO = PRZO + W1*PPN
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
         XR=X
         YR=Y
         ZR=Z
         WATER=WTBC
         NZR=KZ1
         AGER=AGE
         NCOLR=NCOL
         MTNR=MT
         AR=A1
         ENIR=EOLD
         UNIR=UOLD
         VNIR=VOLD
         WNIR=WOLD
         ENOR=0.0
         UNOR=0.0
         VNOR=0.0
         WNOR=0.0
         WTNR=0.0
         QR=Q
         UR=U1
         VR=V1
         WR=W1
         ER=EKN
C       STORE THE CHARGED PARTICLE IN THE RECOIL BANK
         EP = ER
         UP = UR
         VP = VR
         WP = WR
         AMP = AR
         ZMP = FLOAT(NZR)
         AGEP = AGE
         MTP = MT
         CALL STOPAR2(IDHEVY,NHEVY)
   10 CONTINUE
C       CALCULATE THE TOTAL MOMENTUM BEFORE THE COLLISION
C       NEUTRON MOMENTUM BEFORE COLLISION (PI) EQUALS TOTAL MOMENTUM
      PI=SQRT(2.0*ZN*EOLD)
C       CALCULATE THE DIRECTIONAL MOMENTUM OF THE RECOIL NUCLEUS
      PRX=PI*UOLD - PRXO
      PRY=PI*VOLD - PRYO
      PRZ=PI*WOLD - PRZO
C       CALCULATE THE TOTAL MOMENTUM OF THE RECOIL NUCLEUS
      PR=SQRT(PRX**2+PRY**2+PRZ**2)
C       CALCULATE THE RECOIL NUCLEUS DIRECTIONAL COSINES
      U2=PRX/PR
      V2=PRY/PR
      W2=PRZ/PR
C       CALCULATE THE RECOIL NUCLEUS EXIT ENERGY
      XM  = A2*931.075E6
      E2 = SQRT(PR**2+XM**2) - XM
C       CALCULATE AND SET THE CHARGED PARTICLE EXIT PARAMETERS
      XR=X
      YR=Y
      ZR=Z
      WATER=WTBC
      NZR=KZ2
      AGER=AGE
      NCOLR=NCOL
      MTNR=MT
      AR=A2
      ENIR=EOLD
      UNIR=UOLD
      VNIR=VOLD
      WNIR=WOLD
      ENOR=0.0
      UNOR=0.0
      VNOR=0.0
      WNOR=0.0
      WTNR=0.0
      QR=Q
      UR=U2
      VR=V2
      WR=W2
      ER=E2
C       STORE THE RECOIL HEAVY ION IN THE RECOIL BANK
      EP = ER
      UP = UR
      VP = VR
      WP = WR
      AMP = AR
      ZMP = FLOAT(NZR)
      AGEP = AGE
      MTP = MT
      CALL STOPAR2(IDHEVY,NHEVY)
      RETURN
      END
*CMZ :  1.05/04 30/11/2005  11.04.02  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE XSECN12(NII,KE,IN,ICOM,IREC,IUNIT,LNUMB,IND,
     +                  BUF,IBUF,INEL)
C       THIS ROUTINE READS THE SECOND RECORD ON INPUT
C       I/O UNIT (MICROS)  (I.E. THE B CONTROL BLOCK)
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))      
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEND.
      DIMENSION BUF(*),IBUF(*),ICOM(*),KE(*),IREC(*),IND(*),IN(*)
      DIMENSION INEL(*),LNUMB(*),IUNIT(*)
      INTEGER NII
C       READ THE B CONTROL BLOCK OFF INPUT I/O UNIT
      LT = LTEMP
      LZ = 1
      IU = 1
   10 CONTINUE
        NU = IQ(LT+NTUNIT)
        NIJ = IQ(LT+NTMPNI)
        LZZ=3*NIJ
        READ(NU,'((8I10))')(IBUF(I),I=LZ,LZZ+LZ-1)
C       INITIALIZE IND ARRAY AND IREC ARRAY TO ZERO
        DO 20 I=IU,IU+NIJ-1
          IUNIT(I) = NU
   20   CONTINUE
        IU = IU+NIJ
        LZ = LZ + LZZ
        LT = LQ(LT)
      IF(LT.GT.0) GOTO 10
      DO 30 I=1,NII
         INEL(I)=0
         IREC(I)=0
   30 CONTINUE
      DO 40 I=1,NMIX
   40 IND(I)=0
      II=0
      JI=0
   50 II=II+1
CZ      IF(II.GT.NII)GO TO 90
      IF(3*II.GT.LZ)GO TO 90
      NEL=IBUF(3*II-2)
      INEL(II)=NEL
      DO 60 IJ=1,NMIX
C correct element AND the correct unit ?
         IF(NEL.EQ.KE(IJ)) GO TO 70
   60 CONTINUE
      IREC(II)=0
      GO TO 50
   70 I=IN(IJ)
C       ICOM RELATES THE ISOTOPE NUMBER TO THE DICTIONARY NUMBER
      IF(ICOM(I).GT.0) IREC(ICOM(I)) = 0
      ICOM(I)=II
C total length of x-section data in words
      LNUMB(I)  = IBUF(3*II)
      IREC(II)  = IBUF(3*II-1)
C       SET INDICATORS
      DO 80  I=IJ,NMIX
         IF(NEL.NE.KE(I))GO TO 80
         IND(I)=1
         JI=JI+1
   80 CONTINUE
      GO TO 50
   90 RETURN
      END
*CMZ :  1.05/03 27/06/2001  18.41.30  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE XSECN22(ICOM,IREC,IUNIT,IGAMS,LGAM,ELTOL,INABS,LNAB,
     + ITHRMS,LTHRM,IDICTS,LDICT,NTX,NTS,IGCBS,LGCB,AWR,Q,LR,QLR,
     + BUF,IBUF,LIM,LAST,INEL)
C       THIS ROUTINE READS THE REMAINDER OF INPUT I/O UNIT(s),
C       SELECTS THE ELEMENTS NEEDED FOR THE CALCULATIONS,
C       AND STORES THE CROSS SECTION DATA IN CORE
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      CHARACTER*4 MARK
      DIMENSION BUF(*),IBUF(*),ICOM(*),IGAMS(*),LGAM(*),INABS(*),
     +LNAB(*),ITHRMS(*),LTHRM(*),AWR(*),IDICTS(NNR,NNUC),ELTOL(*),
     +LDICT(NNR,NNUC),Q(NQ,NNUC),NTX(*),NTS(*),IGCBS(NGR,NNUC),
     +LGCB(NGR,NNUC),IREC(*),LR(NQ,NNUC),QLR(NQ,NNUC)
      DIMENSION INEL(*),IUNIT(*)
C       ASSIGN THE DEFAULT VALUES
      LEN=0
C       INITIALIZE THE COUNTERS FOR THE LOOP
C       NISR EQUALS THE NUMBER OF ISOTOPES READ
C       IRECNO EQUALS THE NEXT RECORD NUMBER TO BE READ ON INPUT
C  I/O UNIT (NUNIT)
C       LAST EQUALS THE LAST CORE POSITION USED IN THE CALLING
CROUTINE (INPUT1)
C       LST EQUALS THE LAST POSITION USED IN THE BUF ARRAY
C   (I.E. (BUF(LST) = D(LAST)))
      NISR=0
      IRECNO=1
      LST=0
C       PRINT OUT THE CROSS SECTION DIRECTORY IF CALLED FOR
   10 CONTINUE
C       START LOOP TO READ IN THE DATA ON INPUT I/O UNIT
      DO 370 II=1,NI
        IR = IREC(II)
        IF(NUNIT.NE.IUNIT(II)) IRECNO = 1
        NUNIT= IUNIT(II)
        IF(NUNIT.LE.0) THEN
          WRITE(IOUT,'(/,'' XSECN22 : Wrong unit number '',I10)') NUNIT
          GOTO 370
        ENDIF
        IF(NISR.GE.NNUC)GO TO 370
        IF(IR.EQ.0)GO TO 370
C       LOOP TO LOCATE THE I CONTROL BLOCK RECORD (IR=IREC(II))
CZ x-section endmark = 'ENDE'
CZ file endmark ='ENDF'
        MARK = '   '
   20   IF(MARK.EQ.'ENDE') IRECNO = IRECNO + 1
        IF(MARK.EQ.'ENDF') GOTO 50
        IF(IR.EQ.IRECNO) GOTO 30
        READ(NUNIT,'(A)') MARK
        GO TO 20
C       CHECK TO DETERMINE THE ISOTOPE NUMBER FOR THE RANDOM WALK
   30   DO 40 I=1,NNUC
          IF(ICOM(I).EQ.II)GO TO 60
   40   CONTINUE
   50   WRITE(IOUT,10000)II
10000 FORMAT('0',10X,'ERROR IN ROUTINE XSECN22, II=',I6,/)
        GO TO 390
C       READ I CONTROL BLOCK RECORD OFF INPUT I/O UNIT (NUNIT) FOR
C       THE ELEMENT CORRESPONDING TO IREC(II) AND ICOM(I)
   60   IJK=I
        READ(NUNIT,'(I10,4G13.7,1I10,/,6I10)') IBUF(LST+1),(BUF(LST+
     +  IK),IK=2,5),(IBUF(LST+IJ),IJ=6,12)
        NISR=NISR+1
C       ASSIGN VALUES TO ARRAYS NEEDED FOR THE RANDOM WALK
        ISO=IJK
        NEL=INEL(II)
        AWR(ISO)=BUF(LST+2)
CZ store accuracy of xs
        ELTOL(ISO) = BUF(LST+4)
        IFLAGU=IBUF(LST+6)
        LGAM(ISO)=IBUF(LST+7)
        NTX(ISO)=IBUF(LST+8)
        NTS(ISO)=IBUF(LST+9)
        LTHRM(ISO)=IBUF(LST+11)
        LNAB(ISO)=IBUF(LST+12)
C       READ IN THE ISOTOPE DICTIONARY (IDICT ARRAY)
C       FROM INPUT I/O UNIT (NUNIT)
        READ(NUNIT,'((8I10))')(LDICT(J,ISO),J=1,NNR)
   70   CONTINUE
C       READ IN ENDF/B FILE3 CROSS SECTION DATA
C       READ IN ENDF/B FILE4 ANGULAR DISTRIBUTION DATA
C       READ IN ENDF/B FILE5 SECONDARY ENERGY DISTRIBUTION DATA
        DO 190 I2=1,NNR
          LZ=LDICT(I2,ISO)
          IF(LZ.EQ.0)GO TO 190
          LEN=LIM-LAST
          IF(LEN.LT.LZ)GO TO 380
          IDICTS(I2,ISO)=LAST+1-LMOX2
CZ changed in order to read ASCII input file
C I2 < 67  -> x-section data
C I2 < 123 -> angular distribution
C I2 < 134 -> secondary energy distribution
C I2 = 134 ->
          IF(I2.LT.67) THEN
            READ(NUNIT,'((6G13.7))')(BUF(LST+I),I=1,LZ)
          ELSE IF(I2.LT.123) THEN
C ------------------- I2 = 67 -----------------------------
            READ(NUNIT,'((8I10))') (IBUF(LST+I),I=1,2), (IBUF(LST+
     +      J+2),J=1,2*IBUF(LST+1))
            K = 2*IBUF(LST+1) + 2 + 1
            DO 80 J=1,IBUF(LST+2)
              READ(NUNIT,'(G13.7,I10,/,(6G13.7))') BUF(LST+K), IBUF(LST
     +        +K+1), (BUF(LST+IK+K+1),IK=1,IBUF(LST+K+1)*2)
              K = K + 2 + IBUF(LST+K+1)*2
   80       CONTINUE
          ELSE IF(I2.LT.134) THEN
C-------------------- I2 = 123 ----------------------------
C first header is different, because of nk in first position
            read(nunit,'(2I10,G13.7,2I10,/,(8I10))') (IBUF(LST+I),
     +      I=1,2),BUF(LST+3),(IBUF(LST+J),J=4,5), (IBUF(LST+K+5),
     +      K=1,2*IBUF(LST+4))
C define buffer position to start at LF type
            IP = 2
            do nk=1,IBUF(LST+1)
              if(nk.gt.1) then
                read(nunit,'(I10,G13.7,2I10,/,(8I10))') IBUF(LST+IP),
     +          BUF(LST+IP+1),(IBUF(LST+IP+J),J=2,3), (IBUF(LST+IP+K+3)
     +          ,K=1,2*IBUF(LST+IP+2))
              endif
              ID = IP - 2 + 2*IBUF(LST+IP+2) + 5
              LF = IBUF(LST+IP)
              NP2 = 2*IBUF(LST+IP+3)
              READ(NUNIT,'((6G13.7))') (BUF(LST+ID+I),I=1,NP2)
              ID = ID + NP2
              KEND = 1
              IF(LF.EQ.5.OR.LF.EQ.11) KEND = 2
              DO 100 K=1,KEND
                READ(NUNIT,'((8I10))') (IBUF(LST+ID+I),I=1,2)
                NR2 = 2*IBUF(LST+ID+1)
                NE = IBUF(LST+ID+2)
                ID = ID + 2
                READ(NUNIT,'((8I10))') (IBUF(LST+ID+I),I=1,NR2)
                ID = ID + NR2
                IEND = NE
                IF(LF.EQ.5.OR.LF.EQ.11) IEND = 1
                IF(LF.EQ.7.OR.LF.EQ.9) IEND = 1
                DO 90 I=1,IEND
                  IF(LF.EQ.1) THEN
                    READ(NUNIT,'(G13.7,2I10)') BUF(LST+ID+1), (IBUF(LST
     +              +ID+J),J=2,3)
                    NR2 = 2*IBUF(LST+ID+2)
                    NP2 = 2*IBUF(LST+ID+3)
                    ID = ID + 3
                    READ(NUNIT,'((8I10))') (IBUF(LST+ID+J),J=1, NR2)
                    ID = ID + NR2
                  ELSE
                    NP2 = 2*NE
                  ENDIF
                  READ(NUNIT,'((6G13.7))') (BUF(LST+ID+J),J=1,NP2)
                  ID = ID + NP2
   90           Continue
  100         CONTINUE
              IP = ID + 1
            enddo
          ELSE
C ------------------ I2 = 134 --------------------------------------
            READ(NUNIT,'(I10)') IBUF(LST+1)
            LNU = IBUF(LST+1)
            IF(LNU.NE.2) THEN
              READ(NUNIT,'(I10,/,(6G13.7))') IBUF(LST+2), (BUF(LST
     +        +I+2),I=1,IBUF(LST+2))
            ELSE
              READ(NUNIT,'((8I10))') (IBUF(LST+I),I=2,3)
              NR2 = IBUF(LST+2)*2
              READ(NUNIT,'((8I10))') (IBUF(LST+3+J),J=1,NR2)
              NP2 = IBUF(LST+3)*2
              READ(NUNIT,'((6G13.7))') (BUF(LST+3+NR2+J),J=1,NP2)
            ENDIF
          ENDIF
CZ end of change
          IF(I2.GT.66)GO TO 120
  110     CONTINUE
          GO TO 180
  120     IF(I2.GT.122)GO TO 150
  130     CONTINUE
          CALL ANGCDF2(BUF(LST+1),IBUF(LST+1),LZ)
  140     CONTINUE
          GO TO 180
  150     IF(I2.GT.133)GO TO 170
  160     CONTINUE
          GO TO 180
  170     CONTINUE
  180     CONTINUE
          LAST=LAST+LZ
          LST=LST+LZ
  190   CONTINUE
C       READ IN THE AVERAGE PHOTON2 PRODUCTION ARRAY
        LZ=LGAM(ISO)
        IF(LZ.EQ.0)GO TO 210
        LEN=LIM-LAST
        IF(LEN.LT.LZ)GO TO 380
        IGAMS(ISO)=LAST+1-LMOX2
        READ(NUNIT,'((6G13.7))')(BUF(LST+I),I=1,LZ)
  200   CONTINUE
        LAST=LAST+LZ
        LST=LST+LZ
  210   CONTINUE
C       READ IN THE TOTAL NEUTRON DISAPPERANCE ARRAY
        LZ=LNAB(ISO)
        IF(LZ.EQ.0)GO TO 230
        LEN=LIM-LAST
        IF(LEN.LT.LZ)GO TO 380
        INABS(ISO)=LAST+1-LMOX2
        READ(NUNIT,'((6G13.7))')(BUF(LST+I),I=1,LZ)
  220   CONTINUE
        LAST=LAST+LZ
        LST=LST+LZ
  230   CONTINUE
C       READ IN THE Q VALUE ARRAY
        READ(NUNIT,'((6G13.7))')(Q(I,ISO),I=1,NQ)
  240   CONTINUE
C       READ IN THE LR VALUE ARRAY
        READ(NUNIT,'((8I10))')(LR(I,ISO),I=1,NQ)
  250   CONTINUE
C       READ IN THE QLR VALUE ARRAY
        READ(NUNIT,'((6G13.7))')(QLR(I,ISO),I=1,NQ)
  260   CONTINUE
C       READ IN THE PHOTON2 DATA DICTIONARY (GCB ARRAY)
C       FROM INPUT I/O UNIT (NUNIT)
C       CURRENT STORAGE IS SET TO ACCOMODATE UP TO 30 INTERACTIONS
C       (I.E. (2*NTX(ISO)+2*NTS(ISO)).LE.NGR)
        L=2*NTX(ISO)+2*NTS(ISO)
        IF(L.EQ.0)GO TO 350
        L1=2*NTX(ISO)
        L2=L1+1
        READ(NUNIT,'((8I10))')(LGCB(J,ISO),J=1,L)
  270   CONTINUE
C       READ IN ENDF/B FILE12 PHOTON2 MULTIPLICATION DATA
C       READ IN ENDF/B FILE13 PHOTON2 CROSS SECTION DATA
        NNTX=NTX(ISO)
        DO 300 I2=1,NNTX
          LZ=LGCB(2*I2,ISO)
          IF(LZ.EQ.0)GO TO 300
          LEN=LIM-LAST
          IF(LEN.LT.LZ)GO TO 380
          IGCBS(2*I2-1,ISO)=LGCB(2*I2-1,ISO)
          IGCBS(2*I2,ISO)=LAST+1-LMOX2
CZ changed in order to read ASCII xsection file
          READ(NUNIT,'((8I10))') (IBUF(LST+I),I=1,2)
          READ(NUNIT,'((6G13.7))') (BUF(LST+J+2),J=1,IBUF(LST+2))
          ID = IBUF(LST+2) + 2 + LST
          DO 280 K = 1, IBUF(LST+1)
            READ(NUNIT,'(2(G13.7,I10))') BUF(ID+1),IBUF(ID+2), BUF(ID+3
     +      ),IBUF(ID+4)
            ID = ID + 4
            READ(NUNIT,'((6G13.7))') (BUF(ID + J),J=1,IBUF(LST+2))
            ID = ID + IBUF(LST+2)
  280     CONTINUE
CZ end of change
  290     CONTINUE
          LAST=LAST+LZ
          LST=LST+LZ
  300   CONTINUE
C       READ IN ENDF/B FILE15 PHOTON2 SECONDARY ENERGY DISTRIBUTIONS
        NNTS=NTS(ISO)
        IF(NNTS.EQ.0)GO TO 350
        DO 340 I2=1,NNTS
          LZ=LGCB(L1+2*I2,ISO)
          IF(LZ.EQ.0)GO TO 340
          LEN=LIM-LAST
          IF(LEN.LT.LZ)GO TO 380
          IGCBS(L1+2*I2-1,ISO)=LGCB(L1+2*I2-1,ISO)
          IGCBS(L1+2*I2,ISO)=LAST+1-LMOX2
CZ changed in order to read ASCII xsection file
          READ(NUNIT,'(2I10,G13.7,2I10,/,(8I10))') (IBUF(LST+I),I=1,
     +    2),BUF(LST+3), (IBUF(LST+J),J=4,5), (IBUF(LST+K+5),K=1,2*
     +    IBUF(LST+4))
          ID = 2*IBUF(LST+4) + 5
          LF = IBUF(LST+2)
          NP2 = 2*IBUF(LST+5)
          READ(NUNIT,'((6G13.7))') (BUF(LST+ID+I),I=1,NP2)
          ID = ID + NP2
          KEND = 1
          IF(LF.EQ.5.OR.LF.EQ.11) KEND = 2
          DO 320 K=1,KEND
            READ(NUNIT,'((8I10))') (IBUF(LST+ID+I),I=1,2)
            NR2 = 2*IBUF(LST+ID+1)
            NE = IBUF(LST+ID+2)
            ID = ID + 2
            READ(NUNIT,'((8I10))') (IBUF(LST+ID+I),I=1,NR2)
            ID = ID + NR2
            IEND = NE
            IF(LF.EQ.5.OR.LF.EQ.11) IEND = 1
            IF(LF.EQ.7.OR.LF.EQ.9) IEND = 1
            DO 310 I=1,IEND
              IF(LF.EQ.1) THEN
                READ(NUNIT,'(G13.7,2I10)') BUF(LST+ID+1), (IBUF(L
     +          ST+ID+J),J=2,3)
                NR2 = 2*IBUF(LST+ID+2)
                NP2 = 2*IBUF(LST+ID+3)
                ID = ID + 3
                READ(NUNIT,'((8I10))') (IBUF(LST+ID+J),J=1,NR2)
                ID = ID + NR2
              ELSE
                NP2 = 2*NE
              ENDIF
              READ(NUNIT,'((6G13.7))') (BUF(LST+ID+J),J=1,NP2)
              ID = ID + NP2
  310       CONTINUE
  320     CONTINUE
CZ end of change
  330     CONTINUE
          LAST=LAST+LZ
          LST=LST+LZ
  340   CONTINUE
  350   CONTINUE
C       READ IN THE THERMAL CROSS SECTION DATA ARRAY
        LZ=LTHRM(ISO)
        IF(LZ.EQ.0)GO TO 360
        LEN=LIM-LAST
        IF(LEN.LT.LZ)GO TO 380
        ITHRMS(ISO)=LAST+1
        READ(NUNIT,'((6G13.7))')(BUF(LST+I),I=1,LZ)
        LAST=LAST+LZ
        LST=LST+LZ
  360   CONTINUE
  370 CONTINUE
      GO TO 400
  380 WRITE(IOUT,10100)LZ,LEN
10100 FORMAT('0','NOT ENOUGH SPACE TO READ IN RECORD',/,5X,
     +'LENGTH OF RECORD=',I10,/,5X,'SPACE AVAILABLE=',I10)
  390 PRINT '('' CALOR: ERROR in XSECN22 ====> STOP '')'
      STOP
  400 RETURN
      END
*CMZ :  0.94/04 18/03/93  22.51.31  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE XSECN32(KM,KE,RHO,IN,IDICTS,LDICT,ISIGTS,LSIGT,BUF,
     +IBUF,TCS,LIM,LAST)
C       THIS ROUTINE CREATES MACROSCOPIC TOTAL CROSS SECTIONS
C       AND THEN MIXES AND THINS THESE CROSS SECTIONS ACCORDING
C       TO THE MIXING TABLE
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MPOINT.
      COMMON/MPOINT/LMAG1,LFP1,LFP2,LFP3,LFP4,LFP5,LFP6,LFP7,LFP8,
     + LFP9,LFP10,LFP11,LFP12,LFP13,LFP14,LFP140,LFP15,LFP16,LFP17,
     + LFP18,LFP19,LFP20,LFP21,LFP22,LFP23,LFP24,LFP25,LFP26,
     + LFP27,LFP28,LFP29,LFP30,LFP31,LFP32,LFP33,LFP34,LFP35,
     + LFP36,LFP37,LFP38,LFP39,LFP40,LFP41,LFP42,LFP43,LFP44,
     + LFP45,LFP46,LFP47,LFP48,LFP49,LFP50,LFP51,LFP52,LFP53,
     + LFP18A,LFP210
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      DIMENSION BUF(*),IBUF(*),KM(*),KE(*),RHO(*),IN(*),
     +IDICTS(NNR,NNUC),LDICT(NNR,NNUC),ISIGTS(*),LSIGT(*),TCS(*)
C       ASSIGN THE INITIAL VALUES
C       LST EQUALS THE LAST POSITION USED IN THE BUF ARRAY
C   (I.E. (BUF(LST) = D(LAST)))
C       LEN EQUALS THE CORE SPACE AVAILABLE
      LST=0
      LEN=LIM-LAST
      TOL = 1.0
C       READ IN TWO CROSS SECTION ARRAYS AND CREATE
C       MACROSCOPIC CROSS SECTIONS
      DO 160 J=1,MEDIA
         JI=0
         K=0
C       READ IN THE FIRST ARRAY
         DO 140 IJ=1,NMIX
            IF(KM(IJ).NE.J)GO TO 140
            JI=JI+1
            K=K+1
            II=IN(IJ)
            TOL = AMIN1(TCS(LFP210+II-1)/5.,TOL)
            IF(JI.EQ.2)GO TO 20
            LZ=LDICT(1,II)
            ISLZ=IDICTS(1,II)+LMOX2
            N=LZ
            IF(LEN.LT.N)GO TO 180
            NP=LZ/2
            DO 10 M=1,NP
               BUF(LST+2*M-1)=TCS(ISLZ+2*(M-1))
               BUF(LST+2*M)=TCS(ISLZ+2*M-1)*RHO(IJ)
   10       CONTINUE
            GO TO 140
   20       CONTINUE
C       READ IN THE SECOND ARRAY
            LZ2=LZ+1
            LZ1=LZ
            LZ=LDICT(1,II)
            ISLZ=IDICTS(1,II)+LMOX2
            N=2*(LZ+LZ1)
            IF(N.GE.LEN)GO TO 180
            NP=LZ/2
            DO 30 M=1,NP
               BUF(LST+LZ1+2*M-1)=TCS(ISLZ+2*(M-1))
               BUF(LST+LZ1+2*M)=TCS(ISLZ+2*M-1)*RHO(IJ)
   30       CONTINUE
            GO TO 40
C       MIX THE TWO ARRAYS
   40       K=2
            L=2
            IF(BUF(LST+1).NE.1.E-5)GO TO 170
            IF(BUF(LST+LZ2).NE.1.E-5)GO TO 170
            NXSEC=1
            BUF(LST+LZ1+LZ+1)=1.E-5
            BUF(LST+LZ1+LZ+2)=BUF(LST+2)+BUF(LST+LZ2+1)
C       DETERMINE THE NEXT ENERGY POINT
   50       IF(BUF(LST+1+K).EQ.BUF(LST+LZ2+L))GO TO 90
            IF(BUF(LST+1+K).LT.BUF(LST+LZ2+L))GO TO 70
C       DETERMINE THE CROSS SECTION AT ENERGY POINT BUF(LST+LZ2+L)
            CALL CTERP2(BUF(LST+K-1),BUF(LST+K+1),BUF(LST+LZ2+L),
     +                BUF(LST+K), BUF(LST+K+2),SIGMA)
            NXSEC=NXSEC+1
            LP=LZ1+LZ+1+2*(NXSEC-1)
            BUF(LST+LP)=BUF(LST+LZ2+L)
            BUF(LST+LP+1)=BUF(LST+LZ2+L+1)+SIGMA
            L=L+2
            IF(L.LT.LZ)GO TO 50
C       ALL THE POINTS IN THE SECOND ARRAY HAVE NOW BEEN USED
   60       NXSEC=NXSEC+1
            LP=LZ1+LZ+1+2*(NXSEC-1)
            BUF(LST+LP)=BUF(LST+1+K)
            BUF(LST+LP+1)=BUF(LST+2+K)
            K=K+2
            IF(K.LT.LZ1)GO TO 60
            GO TO 100
C       DETERMINE THE CROSS SECTION AT ENERGY POINT BUF(LST+1+K)
   70       CALL CTERP2(BUF(LST+LZ2+L-2),BUF(LST+LZ2+L),BUF(LST+1+K),
     +      BUF(LST+LZ2+L-1),BUF(LST+LZ2+L+1),SIGMA)
            NXSEC=NXSEC+1
            LP=LZ1+LZ+1+2*(NXSEC-1)
            BUF(LST+LP)=BUF(LST+1+K)
            BUF(LST+LP+1)=BUF(LST+K+2)+SIGMA
            K=K+2
            IF(K.LT.LZ1)GO TO 50
C       ALL THE POINTS IN THE FIRST ARRAY HAVE NOW BEEN USED
   80       NXSEC=NXSEC+1
            LP=LZ1+LZ+2*NXSEC-1
            BUF(LST+LP)=BUF(LST+LZ2+L)
            BUF(LST+LP+1)=BUF(LST+LZ2+L+1)
            L=L+2
            IF(L.LT.LZ)GO TO 80
            GO TO 100
C       THE ENERGY POINTS COINCIDE
   90       NXSEC=NXSEC+1
            LP=LZ1+LZ+1+2*(NXSEC-1)
            BUF(LST+LP)=BUF(LST+LZ2+L)
            BUF(LST+LP+1)=BUF(LST+2+K)+BUF(LST+LZ2+L+1)
            L=L+2
            K=K+2
            IF((L.LT.LZ).AND.(K.LT.LZ1))GO TO 50
            IF((L.GT.LZ).AND.(K.LT.LZ1))GO TO 60
            IF((L.LT.LZ).AND.(K.GT.LZ1))GO TO 80
C       FINISHED MIXING NOW THIN
  100       L=1
            NXSEC2=1
            LP=LZ1+LZ
            BUF(LST+NXSEC2)=BUF(LST+LP+L)
            BUF(LST+NXSEC2+1)=BUF(LST+LP+L+1)
            KI=0
  110       L=L+2
            KI=KI+1
C       CHECK TO SEE IF AT END OF CROSS SECTION ARRAY
            L2=L+2
            N=2*NXSEC
            IF(L2.LT.N)GO TO 120
C       FINISHED THINING
            NXSEC2=NXSEC2+1
            N=2*(NXSEC2-1)
            BUF(LST+1+N)=BUF(LST+LP+L)
            BUF(LST+2+N)=BUF(LST+LP+L+1)
            LZ=2*NXSEC2
            JI=1
            GO TO 140
  120       DO 130 I=1,KI
C       ESTIMATE THE CROSS SECTION AT KI NODES
               CALL CTERP2(BUF(LST+LP+L-2*KI),BUF(LST+LP+L2),
     +                   BUF(LST+LP+L-2*I+2),BUF(LST+LP+L-2*KI+1),
     +                   BUF(LST+LP+L2+1),SIGMA)
               ER=ABS(SIGMA-BUF(LST+LP+L-2*I+3))
C       IF ERROR IS WITHIN ALLOWABLE TOLERANCE, CHECK NEXT POINT
               ERMAX=BUF(LST+LP+L-2*I+3)*TOL
               IF(ER.LE.ERMAX)GO TO 130
C       NOT WITHIN ALLOWABLE TOLERANCE, MUST ADD NODE L-2 TO MESH
               IF(L.GT.3.AND.KI.GT.1) L = L - 2
               NXSEC2=NXSEC2+1
               N=2*(NXSEC2-1)
               BUF(LST+1+N)=BUF(LST+LP+L)
               BUF(LST+2+N)=BUF(LST+LP+L+1)
               KI = 0
               GO TO 110
  130       CONTINUE
C       ALL KI POINTS ARE WITHIN ALLOWABLE TOLERANCE
C       CHECK THE NEXT POINT
            GO TO 110
  140    CONTINUE
C       FINISHED WITH MEDIUM J, NOW STORE IN CORE
         N=2*NXSEC2
         IF(K.EQ.1)N=LZ
         LSIGT(J)=N
         ISIGTS(J)=LAST+1-LMOX3
  150    CONTINUE
         LAST=LAST+N
         LST=LST+N
C       FINISHED MIXING AND THINING
  160 CONTINUE
      GO TO 200
  170 WRITE(IOUT,10000)BUF(LST+1),BUF(LST+LZ2)
10000 FORMAT(' MICAP: ERROR-BEGINNING ENERGY DOES NOT START AT 1.-5',
     +1P2E12.4)
      GOTO 190
  180 CONTINUE
      L=LEN
      WRITE(IOUT,10100)L,N
10100 FORMAT(' MICAP: NOT ENOUGH ROOM TO MIX CROSS SECTIONS',/,5X,
     +'SPACE AVAILABLE=',I10,/,5X,'SPACE NEEDED=',I10)
  190 PRINT '('' CALOR: ERROR in XSECN32 ====> STOP'')'
      STOP
  200 RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.49  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE XSECN52(NTX,IGCBS,LGCB,IGCBS2,LGCB2,BUF,IBUF,D,LD,
     +LIM,LAST)
C       THIS ROUTINE READS THE PHOTON2 PARTIAL DISTRIBUTIONS FOR EACH
C       REACTION LISTED IN THE GCB ARRAYS AND SUMS THEM UP TO
C       CREATE A TOTAL MULTIPLICITY * CROSS SECTION ARRAY FOR
C       EACH REACTION AND STORES THIS CROSS SECTION DATA IN CORE
*KEEP,MINPUT.
      COMMON/MINPUT/NCASE,NSTRT,NMOST,MOSTG,MOSTR,NITS,NPHOTN,
     1 NHEAVY,NSOUR,NSPLT,NKILL,NPAST,NOLEAK,IEBIAS,MEDIA,NMIX,
     2 ISOUR,NGPFS,ISBIAS,INN,IOUT,MGEOM,MGAMMA,MHEAVY,MICROS,
     3 MACROS,MGSCR,MRSCR,MHETC,IPRTNX,IPRTNA,IPRTNE,IPRTPP,IPRTNP,
     4 IPRTGX,IPRTGE,IPRTMX,UINP,VINP,WINP,XSTRT,YSTRT,ZSTRT,WTSTRT,
     5 AGSTRT,ESOUR,TMAX,TCUT,ECUT,ETHERM,TEMP,TOL
*KEEP,MCONST.
      PARAMETER(MAXPAR=200)
      PARAMETER(MAXNEU=100)
      COMMON/MCONST/NNR,NQ,NGR,NTSTW,MGPREG,MGP1,M1M,NI,NNUC,NCOL
*KEEP,MMICAB.
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
*KEND.
      DIMENSION NTX(NNUC),IGCBS(NGR,NNUC),LGCB(NGR,NNUC),
     +IGCBS2(NGR,NNUC),LGCB2(NGR,NNUC),BUF(*),IBUF(*),D(*),LD(*)
C       ASSIGN THE DEFAULT VALUES
      LEN=0
C       INITIALIZE THE COUNTERS FOR THE LOOP
C       LAST EQUALS THE LAST CORE POSITION USED IN THE CALLING
CROUTINE (INPUT1)
C       LST EQUALS THE LAST POSITION USED IN THE BUF ARRAY
C   (I.E. (BUF(LST) = D(LAST)))
      LST=0
      DO 70 I=1,NNUC
         NNTX=NTX(I)
         L=2*NNTX
         IF(L.EQ.0)GO TO 70
         DO 60 I2=1,NNTX
            LZ=LGCB(2*I2,I)
            IF(LZ.EQ.0)GO TO 60
            LEN=LIM-LAST
            IF(LEN.LT.LZ)GO TO 80
C       EQUATE THE MT NUMBERS IN THE GCB AND GCB2 DICTIONARIES
            IGCBS2(2*I2-1,I)=IGCBS(2*I2-1,I)
            LGCB2(2*I2-1,I)=LGCB(2*I2-1,I)
C       SET THE STARTING LOCATION FOR THE PHOTON2 TOTAL CROSS SECTION
            IGCBS2(2*I2,I)=LAST+1-LMOX4
C       OBTAIN THE STARTING LOCATION OF THE PARTIAL DISTRIBUTIONS
            IST=IGCBS(2*I2,I)+LMOX2
            NK=LD(IST)
            NP=LD(IST+1)
            NP2=2*NP
            LGCB2(2*I2,I)=NP2
C       ZERO OUT THE CORE AREA TO STORE THE TOTAL PHOTON2
C       MULTIPLICITY * CROSS SECTION ARRAYS
            DO 10 IP=1,NP2
               BUF(LST+IP)=0.0
   10       CONTINUE
C       SET UP THE ENERGY BOUNDARIES FOR THE (E,XS) TABLE
            DO 20 J=1,NP
               BUF(LST+2*J-1)=D(IST+J+2-1)
   20       CONTINUE
            II=NP+2
            AWRI=D(IST+II+3-1)
C       SUM THE PARTIAL DISTRIBUTIONS TO OBTAIN THE TOTAL
C       MULTIPLICITY * CROSS SECTION ARRAY AND STORE IN THE
C       ENERGY,CROSS SECTION TABLE
            DO 40 J=1,NK
               II=II+4
               DO 30 K=1,NP
                  BUF(LST+2*K)=BUF(LST+2*K)+D(IST+II+K-1)
   30          CONTINUE
               II=II+NP
   40       CONTINUE
   50       CONTINUE
C       UPDATE CORE LOCATION POINTERS
            LAST=LAST+NP2
            LST=LST+NP2
   60    CONTINUE
   70 CONTINUE
      RETURN
   80 WRITE(IOUT,10000)LZ,LEN
10000 FORMAT(' MICAP: NOT ENOUGH SPACE TO READ IN RECORD',/,5X,
     +'LENGTH OF RECORD=',I10,/,5X,'SPACE AVAILABLE=',I10)
      PRINT '('' CALOR: ERROR in XSECN52 ====> STOP '')'
      STOP
      END
*CMZ :  1.01/04 10/06/93  14.43.49  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE XSECNU2(BUF,LEN,E,XSC,L1,L2)
C       THIS ROUTINE DETERMINES A CROSS SECTION AT A GIVEN ENERGY
C       FROM A CROSS SECTION VERSUS ENERGY TABLE
      DIMENSION BUF(*)
      SAVE
      IF(E.LT.BUF(L1))GO TO 40
      DO 10 J=1,LEN
         N=L1+2*(J-1)
         IF(E.LE.BUF(N))GO TO 20
   10 CONTINUE
      XSC=BUF(L2)
      RETURN
   20 IF(J.EQ.1)GO TO 30
      XSC=BUF(N-1)+(E-BUF(N-2))*(BUF(N+1)-BUF(N-1))/
     +(BUF(N)-BUF(N-2))
      RETURN
   30 XSC=BUF(N+1)
      RETURN
   40 XSC=0.0
      RETURN
      END
*CMZ :  1.03/00 27/05/94  16.22.23  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   27/05/94
      SUBROUTINE MICSET2(MATNO,NKEY)
C***********************************************************************
C set a option in MICAP
C
C INPUT:   MATNO  - GEANT material number
C          NKEY   - 0 -> use single isotopes instead of the
C                                 natural composition in material MATNO
C                   1 -> use natural composition
C
C************************************************************************
C
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEND.
C
      LOGICAL FIRST
      DATA FIRST/.TRUE./
C
      IF(FIRST) THEN
         FIRST = .FALSE.
         NWW = 100
         CALL CHKZEB2(NWW,IXCONS)
         CALL MZLINK(IXCONS,'MICPAR',LMIST,LMIST,LMIST)
         CALL MZBOOK(IXCONS,LMIST,0,2,'MIST',0,0,NWW,0,0)
      ENDIF
 10   CONTINUE
      DO 20 I=1,IQ(LMIST-1),2
         IF(IQ(LMIST+I).EQ.MATNO) THEN
            IQ(LMIST+I+1) = NKEY
            GOTO 999
         ENDIF
         IF(IQ(LMIST+I).EQ.0) THEN
            IQ(LMIST+I) = MATNO
            IQ(LMIST+I+1) = NKEY
            GOTO 999
         ENDIF
 20   CONTINUE
C
C  Bank got to small, increase the size
      NWW = 100 + IQ(LMIST-1)
      CALL CHKZEB2(NWW,IXCONS)
      CALL MZPUSH(IXCONS,LMIST,0,100,'I')
      GOTO 10
999   RETURN
      END
*CMZ :  1.04/01 09/02/95  17.09.56  by  Christian Zeitnitz
*-- Author :    Christian Zeitnitz   9/02/95
      SUBROUTINE MICFIL2(CNAME)
C***********************************************************************
C set a option in MICAP
C
C INPUT:
C          CNAME  - in case NKEY=10 the file name
C
C************************************************************************
C
*KEEP,MMICAP.
C
C
      COMMON/ MMICAP / LMAG2,LCISO,LGE2MO,LMOMA,LMOX1,LMOX2,
     +                 LMOX3,LMOX4
      COMMON/ MICPAR / LMIST
      COMMON/ MIFILE / LMIFIL
      COMMON/ MICTMP / LTEMP,NTUNIT,NTNAME,NTMPNI,NTCOMM,NTDATS,NTLIST
      PARAMETER (KWBANK=69000,KWWORK=5200)
      COMMON/GCBANK/NZEBRA,GVERSN,ZVERSN,IXSTOR,IXDIV,IXCONS,FENDQ(16)
     +             ,LMAIN,LR1,WS(KWBANK)
      DIMENSION IQ(2),Q(2),LQ(8000),IWS(2)
      EQUIVALENCE (Q(1),IQ(1),LQ(9)),(LQ(1),LMAIN),(IWS(1),WS(1))
      EQUIVALENCE (JCG,JGSTAT)
      COMMON/GCLINK/JDIGI ,JDRAW ,JHEAD ,JHITS ,JKINE ,JMATE ,JPART
     +      ,JROTM ,JRUNG ,JSET  ,JSTAK ,JGSTAT,JTMED ,JTRACK,JVERTX
     +      ,JVOLUM,JXYZ  ,JGPAR ,JGPAR2,JSKLT
C
      DIMENSION LD(1),D(1)
      EQUIVALENCE (D(1),Q(1)),(LD(1),IQ(1))
      CHARACTER*24 DATSTR
      CHARACTER*80 COMMEN
      COMMON/ MICMAT / DATSTR,COMMEN,MATIDS(100,20,2)
C
*KEND.
C
      CHARACTER*(*) CNAME
C
      LOGICAL FIRST
      DATA FIRST/.TRUE./
C
      IF(FIRST) THEN
         FIRST = .FALSE.
         NFIL = 101
         CALL CHKZEB2(NFIL,IXCONS)
         CALL MZLINK(IXCONS,'MICFIL2',LMIFIL,LMIFIL,LMIFIL)
         CALL MZBOOK(IXCONS,LMIFIL,0,2,'MIFL',0,0,NFIL,0,0)
      ELSE
C increase the bank for the x-section file name
        NFIL = 101 + IQ(LMIFIL-1)
        CALL CHKZEB2(NFIL,IXCONS)
        CALL MZPUSH(IXCONS,LMIFIL,0,101,'I')
      ENDIF
C store x-section file name in bank 'MIFL'
C find the last free index in the bank
      IF(LNBLNK(CNAME).GT.0) THEN
        I = LMIFIL+IQ(LMIFIL-1)-100+1
        CALL UCTOH(CNAME,IQ(I),4,LNBLNK(CNAME))
        IQ(I-1) = LNBLNK(CNAME)
      ELSE
        PRINT*,' MICSET2 : invalid file name '
      ENDIF
   30 RETURN
      END
*CMZ :  1.01/10 30/06/93  13.51.55  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CSKALE(IBERT,F,NOFAS,ITSLO,EFAS,ALPFAS,BETFAS,GAMFAS,
     +                 EHICUT,RMFAS,EXFAS,REFAS)
C
CZ  modified SKALE -- generate WT particles
C
      DIMENSION  F(*)     , ITSLO(*) , EFAS(*) , ALPFAS(*) , BETFAS(*) ,
     +           GAMFAS(*), WTFAS(200), ESLO(200), ALPSLO(200),
     +           BETSLO(200), GAMSLO(200), NPI(200)
C
      LOGICAL FTROBL
C
      DATA IELAS/1/
      SAVE
C
      NKEY=2
      NCT=1
   10 ESTOR=F(3)
      F(3)=EHICUT
C
      CALL CABERT(IBERT,F,NOSLO,ITSLO,ESLO,ALPSLO,BETSLO,GAMSLO)
      IBERT=1
      F(3)=ESTOR
C
      IF(NOSLO.GT.0) GO TO 70
      NOFAS=NOSLO
   20 CONTINUE
C
C scaling within geant
C generate N particles with RND*WT*Ei energy
C check for depletion of nucleus
C
      IF(NOFAS.LE.0) RETURN
C first determine recoil nucleus parameters
      FTROBL = .FALSE.
   30 CONTINUE
      AR=F(1)
      ZR=F(2)
      PI0NO = 0.0
      PIPNO = 0.0
      PIMNO = 0.0
      PRONO = 0.0
      XNEUT = 0.0
      DO 40 I=1,NOFAS
         IF(ITSLO(I).LE.0) PRONO = PRONO + 1.0
         IF(ITSLO(I).LE.1) XNEUT = XNEUT + 1.0
         IF(ITSLO(I).EQ.2) THEN
           CALL GRNDM(R,1)
           NPI(I) = INT(WTFAS(I))
           XN = WTFAS(I) - FLOAT(NPI(I)) - R
           IF(XN.GT.0.0) NPI(I) = NPI(I) + 1
           IF(NPI(I).LE.0.OR.FTROBL) NPI(I) = 1
           PIPNO = PIPNO + FLOAT(NPI(I))
         ELSE IF(ITSLO(I).EQ.4) THEN
           CALL GRNDM(R,1)
           NPI(I) = INT(WTFAS(I))
           XN = WTFAS(I) - FLOAT(NPI(I)) - R
           IF(XN.GT.0.0) NPI(I) = NPI(I) + 1
           IF(NPI(I).LE.0.OR.FTROBL) NPI(I) = 1
           PIMNO = PIMNO + FLOAT(NPI(I))
         ELSE IF(ITSLO(I).EQ.3) THEN
           CALL GRNDM(R,1)
           NPI(I) = INT(WTFAS(I))
           XN = WTFAS(I) - FLOAT(NPI(I)) - R
           IF(XN.GT.0.0) NPI(I) = NPI(I) + 1
           IF(NPI(I).LE.0.OR.FTROBL) NPI(I) = 1
         ENDIF
   40 CONTINUE
      AADD = 1.
      IF(F(7).GT.1) AADD = 0.0
      ZADD = 1. - F(7)
      IF(F(7).GT.1) ZADD = 3.-F(7)
      AR = AR + AADD - PRONO - XNEUT
      ZR = ZR + ZADD - PRONO - PIPNO + PIMNO
      IF((ZR.LT.0.OR.AR.LT.ZR).AND..NOT.FTROBL) THEN
        FTROBL = .TRUE.
        GOTO 30
      ENDIF
C  start generating more particles
      K = NOFAS + 1
C loop over particles
      DO 60 I=1,NOFAS
C don't scale nucleons
         IF(ITSLO(I).LE.1) THEN
            EFAS(I) = EFAS(I)*WTFAS(I)
         ELSE
          DO 50 J=1,NPI(I)
            IF(J.EQ.NPI(I)) THEN
              IF(WTFAS(I).GT.0.0) EFAS(I) = EFAS(I)*WTFAS(I)
            ELSE
              WTFAS(I) = WTFAS(I) - 1.
              EFAS(K) = EFAS(I)
              ITSLO(K)  = ITSLO(I)
              ALPFAS(K) = ALPFAS(I)
              BETFAS(K) = BETFAS(I)
              GAMFAS(K) = GAMFAS(I)
              K = K + 1
            ENDIF
   50     CONTINUE
         ENDIF
   60 CONTINUE
      NOFAS=K-1
      RETURN
   70 IF(IELAS.EQ.0) GO TO 80
      CALL ESKALE(IE,EHICUT,F,NOFAS,ITSLO,EFAS,ALPFAS,BETFAS,GAMFAS,
     + WTFAS,RMFAS,EXFAS,REFAS,NOSLO,ESLO,ALPSLO,BETSLO,GAMSLO)
      GO TO (80,10,20),IE
   80 ATAR=F(1)
      EINC=F(3)
      ITINC=F(7)
      CALL MCMOSC(NKEY,ATAR,ITINC,EINC,EHICUT,NOSLO,ITSLO,ESLO,ALPSLO,
     + BETSLO,GAMSLO,EFAS,WTFAS,ALPFAS,BETFAS,GAMFAS,RMFAS,NOFAS,EXFAS,
     + REFAS,WHY)
      IF(NOFAS.EQ.0) GO TO 10
      GOTO 20
      END
*CMZ :  1.01/09 29/06/93  12.26.35  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE ESKALE(IE,EHICUT,FIN,NOFAS,ITSLO,EFAS,ALPFAS,BETFAS,
     + GAMFAS,WTFAS,RMFAS,EXFAS,REFAS,NOSLO,ESLO,ALPSLO,BETSLO,GAMSLO)
C
C changed 10 Nov. 1992 C.Zeitnitz
C
      DIMENSION FIN(*)    , ITSLO(*)   , EFAS(*)    , ALPFAS(*)  ,
     +          BETFAS(*) , GAMFAS(*)  , WTFAS(*)   , ESLO(*)    ,
     +          ALPSLO(*) , BETSLO(*)  , GAMSLO(*)  , ITSLO2(200),
     +          EFAS2(200), WTFAS2(200), ALPFA2(200), BETFA2(200),
     +          GAMFA2(200)
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEEP,CBERT.
C
      INTEGER*2 RANDI(4),RANDS(4),ERAND(4)
      REAL*4  PRTIN,TRSYM
      REAL*8 SF, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS
      REAL*8 ESPS(481), PT(48), PLVC(961), PGVC(441), PNBC(5),
     +    SPACE(178), CRSC(2400), HVN(3), HVP(3), AWD(3), FVNP(3),
     +    VNVP(3), PMAC(3), PPAN(3), THPN(3), FFPTFN(3), TFFN(3),
     +    TFFP(3), CFEPN(6), FMPN(6), FMAX(7), CRDT(25), S(37), XI(3),
     +    DCOS(3), CURR(11), D(6), CE(21), WKRPN(6), PM(4), E(4),
     +    PXYZ(12), C(3), ECO(2), COL(24), CC(12), PNIDK(23), OUT(40),
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, ANS, BEGRU, FRAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS(29850)
      COMMON/CBERT/ SF, NRT, LN, ANDIT, AMASNO, ZEE, EINC, CTOFE,
     +    CASESN, PRTIN, TRSYM, RANDI, PNMS, SQNM, DNCMS, RCPMV,
     +    POMS, IPEC(13), ISW(13), IOUT(6), NOR, INPT, NO, NMAS, IN,
     +    IV, IP, MED, INC, IFCA, IFCC, NOT, IT, IFC, KNOT,
     +    I1, I2, I6, IK, I5, I4, I3, KA, ITOTE, ITOTI, ITOT2, ITOT3,
     +    NWDS
      COMMON/CBERT/ ESPS, PT, PLVC, PGVC, PNBC,
     +    SPACE, CRSC, HVN, HVP, AWD, FVNP,
     +    VNVP, PMAC, PPAN, THPN, FFPTFN, TFFN,
     +    TFFP, CFEPN, FMPN, FMAX, CRDT, S, XI,
     +    DCOS, CURR, D, CE, WKRPN, PM, E,
     +    PXYZ, C, ECO, COL, CC, PNIDK, OUT,
     +    FCN, FCP, PGCNT, PACNT, PECNT, VALUE2, PPPDA, PPMDA, PPNDA,
     +    PPNNA, CLCFE, VALUE1, RANDS, ANS, BEGRU, FRAND, ERAND,
     +    EX, SIGN, CLSM, EFRP, EFRN, XABS, STRKP, RLKE, P1OE1, POLC,
     +    POLS, SOPC, SOPS, P2, ANY, SN, ABSEC, COM, SNT, CST, COM2,
     +    VALUE3, UNIV, UNIVE, UNIVER, COM1, FTR, COM4, COM3, A ,
     +    CTOFEN, TAPCRS
C
*KEND.
C
      REAL*8 F,PRTIN2,FEINC
      REAL*4 W
C
      DATA F /0.95D0/
      DATA W /0.2/
      SAVE
C
      IND = 1
      EINC = DBLE(FIN(3))
      EPART= FIN(3)
      FIN(3) = EHICUT
      FEINC = DBLE(EHICUT) * F
      PRTIN2 = DBLE(FIN(7)) + 1.D0
C**
C**        NEP = NO. OF ESCAPING PARTICLES
C**
   10 NEP = IDINT(ESPS(1) + 1.0D-2)
C
C**      CHECK FOR PIONS
C
      J = 2
      DO 20 I = 1,NEP
         IF(ESPS(J).GE.3.D0) GO TO 50
         J = J + 8
   20 CONTINUE
      ITEST1 = ITEST1 + 1
      J = 2
      DO 40 I=1,NEP
C
C**      CHECK FOR ESCAPING PARTICLE SAME AS INCIDENT PARTICLE
C
         IF(ESPS(J).NE.PRTIN2) GO TO 30
C
C**      CHECK FOR ENERGY OF ESCAPING PARTICLE GREATER THAN F * ENERGY
C**      OF INCIDENT PARTICLE
C
         IF(ESPS(J+1).GT.FEINC) GO TO 60
   30    J = J + 8
   40 CONTINUE
C
C**      A 'NON-ELASTIC' COLLISION HAS OCCURRED
C
   50 GO TO (160 ,120),IND
C
C**      AN 'ELASTIC' COLLISION HAS OCCURRED
C
   60 CONTINUE
   70 GO TO (80,110),IND
   80 ATAR = FIN(1)
      NKEY = 2
      NELAST = NELAST + 1
      ITINC = FIN(7)
      CALL MCMOSC(NKEY,ATAR,ITINC,EPART,EHICUT,NOSLO,ITSLO,ESLO,
     + ALPSLO,BETSLO,GAMSLO,EFAS,WTFAS,ALPFAS,BETFAS,GAMFAS,RMFAS,
     + NOFAS,EXFAS,REFAS,WHY)
      NOFAS1 = NOFAS
      IF(NOFAS1.GT.0) GO TO 90
      IE = 2
      GO TO 170
C
C**      MULTIPLY ALL PARTICLE WEIGHTS FOR THIS COLLISION BY W
C
   90 DO 100 I=1,NOFAS1
         WTFAS(I) = WTFAS(I) * W
  100 CONTINUE
  110 IBERT = 1
      CALL CABERT(IBERT,FIN,NOSLO,ITSLO2,ESLO,ALPSLO,BETSLO,GAMSLO)
      IF(NOSLO.LE.0) GO TO 110
      IND = 2
      GO TO 10
  120 CALL MCMOSC(NKEY,ATAR,ITINC,EPART,EHICUT,NOSLO,ITSLO2,ESLO,
     + ALPSLO,BETSLO,GAMSLO,EFAS2,WTFAS2,ALPFA2,BETFA2,GAMFA2,RMFAS2,
     + NOFAS2,EXFAS2,REFAS2,WHY)
      IF(NOFAS2.LE.0) GO TO 110
C
C**      MULTIPLY ALL PARTICLE WEIGHTS BY 1.-W
      W2 = 1.0 - W
      DO 130 I=1,NOFAS2
         WTFAS2(I) = WTFAS2(I) * W2
  130 CONTINUE
C
C**      COMBINE TWO COLLISIONS
C
      IF(NOFAS1 + NOFAS2.LE.60) GO TO 140
      WRITE(IO,10000) NOFAS1,NOFAS2
10000 FORMAT(' HETC: Too many particles in ESKALE -- NOFAS1 = ',I2,
     +       ' NOFAS2 = ',I2)
      IF(NOFAS1.EQ.60) NOFAS1 = 59
      NOFAS2 = 60 - NOFAS1
  140 NOFAS = NOFAS1 + NOFAS2
      DO 150 I = 1,NOFAS2
         J = NOFAS1 + I
         ITSLO(J) = ITSLO2(I)
         EFAS(J) = EFAS2(I)
         WTFAS(J) = WTFAS2(I)
         ALPFAS(J) = ALPFA2(I)
         BETFAS(J) = BETFA2(I)
         GAMFAS(J) = GAMFA2(I)
  150 CONTINUE
      EXFAS = EXFAS * W + EXFAS2 * (1.-W)
      RMFAS = RMFAS * W + RMFAS2 * (1.-W)
      REFAS = REFAS * W + REFAS2 * (1.-W)
      IE = 3
      GO TO 170
  160 IE = 1
  170 FIN(3) = SNGL(EINC)
      RETURN
      END
*CMZ :  1.01/09 29/06/93  12.23.58  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE MCMOSC(NKEY,ATAR,ITINC,EOPRS,EINCS,NOSLO,ITSLO,ESLO,
     + ALPSLO,BETSLO,GAMSLO,EFAS,WTFAS,ALPFAS,BETFAS,GAMFAS,RMFAS,NOFAS,
     + EXFAS,REFAS,WHY)
C
C     CALCULATION OF MOMENTUM SPECTRA
C     FOR SCALED-UP INCIDENT PARTICLE ENERGIES
C
      REAL*8 AMASNO, EINC, ARRAY, BRRAY, BARB, EINCT, NUMBEA, TARMAT
      REAL*8 EOPR,TARMAS,FUG,AMORNT,AMRNST,ESTART, ERNPRT,ERNT,AMASIN,
     +EMASS,PMAX,AMOINC,CHEINC,RESMAS,ETOT,ETOTPR, AMOIPR,BETA,BETAPR,
     +GAMMA,GAMPR,ECM,RECAL1,RECAL2,RECAL3,ECMPR, CUTL,CUTCM,ECMOKE,
     +PCMO,YIELD,AVERE,BTOT,BTOTPR,ZKZ,BPRLAB,ECMKE, PLICIT,EXCIT,PX,
     +PY,PZ,PXS,PYS,PZS,P,CHECK,WEIGHT,PCM,EPRCM, PTEMP,WCM,W,PPR,
     +PSTOR1,PSTOR2,B,ESUM,BLANK,BLANK1,AMORN, ERN,ERNPR,AESUM,ESTAR,
     +ESTARP,TOTAL,ANSWER,A1,A2,A3,A4,A5,A11,B11 ,C11,ANSPLU,ANSMIN,A6,
     +A7,D1,STO,STOO,A8,ESUMPR,BTOLAB,ARRMON
C
*KEEP,CAMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
*KEND.
      DIMENSION PART(5),EMASS(5),CTOFM(5),ARRAY(500)
      DIMENSION BRRAY(500),WEIGHT(65),CUTL(5),CUTCM(5),RESMAS(5),
     +    AVERE(10),YIELD(10),ECMKE(5),PLICIT(5),EPRCM(65),FUG(5)
C
      DIMENSION ITSLO(*),ESLO(*),ALPSLO(*),BETSLO(*),GAMSLO(*),
     + EFAS(*),WTFAS(*),ALPFAS(*),BETFAS(*),GAMFAS(*)
C
      DIMENSION EINCT(10), NUMBEA(10)
      LOGICAL INIT
C
      EQUIVALENCE(CUTCM(1),RESMAS(1),CUTL(1),EMASS(1))
C
      DATA INIT/.TRUE./
      SAVE
C
   10 IF(INIT) THEN
   20    COUNT = 0.
         TARMAT=0.
         COUNT1 = 0.
         COUNT2=0.
         COUNT3=0.
         COUNT4 = 0.
         COUNT5 = 0.
         NTTME=0
         AMORNT = 0.0
         AMRNST = 0.0
         ESTART=0.
         ZKZ=0.
         NMLTEO = 0
         ERNPRT = 0.0
         ERNT = 0.0
         CHECK7=0.
         CHECK8=0.
         DO 30 III=1,500
            BRRAY(III)=0.
            ARRAY(III)=0.
   30    CONTINUE
         DO 40 IHK = 1,10
            EINCT(IHK)=0.
            NUMBEA(IHK)=0.
            YIELD(IHK) = 0.0
C     WILL CONTAIN AVERAGE MULTIPLICITIES WHEN DIVIDED BY # OF COLLISION
            AVERE(IHK) = 0.0
   40    CONTINUE
C     WILL CONTAIN AVERAGE ENERGY WHEN DIVIDED BY # OF COLLISIONS
         BTOT = 0.0
         BTOTPR=0.0
C       SETTING MASSES FOR THE 5 POSSIBLE EMERGENT PARTICLES
         RESMAS(1) = XMASS(0)*1000.
         RESMAS(2) = XMASS(1)*1000.
         RESMAS(3)= XMASS(2)*1000.
         RESMAS(4)= XMASS(2)*1000.
         RESMAS(5) = XMASS(3)*1000.
         FUG(3)=1.0D0
         FUG(4)=1.0D0
         FUG(5)=1.0D0
         INIT = .FALSE.
      ENDIF
      GO TO (50 ,70 ,50 ,440),NKEY
   50 RETURN
C     DEFINES INCIDENT PARTICLE
   60 EINCT(IPIN)=EINCT(IPIN)-EINC
      EINCT(IPIN+5)=EINCT(IPIN+5)-EOPR
      NUMBEA(IPIN)=NUMBEA(IPIN)-1.D0
      NUMBEA(IPIN+5)=NUMBEA(IPIN+5)-1.D0
      TARMAT = TARMAT-TARMAS
      RETURN
   70 PIN = ITINC +1
      ZKZ=ZKZ+1.D0
      IPIN= PIN
      NOFAS=0
      WHY=0.
      INTYPE=ITINC+1
      GOTO(80  ,90  ,100 ,100 ,100 ),INTYPE
   80 FUG(1)=1.00D0
      FUG(2)=1.00D0
      GOTO 110
   90 FUG(1)=1.00D0
      FUG(2)=1.00D0
      GOTO 110
  100 FUG(1)=1.0
      FUG(2)=1.0
  110 CONTINUE
      AMASNO= ATAR
      TARMAS= 931.49432D0*AMASNO
      TARMAT=TARMAT+TARMAS
      AMASIN=RESMAS(IPIN)
      EOPR=EOPRS
      EINC=EINCS
      CHEINC = 1.D0
      IF(IPIN.GT.2) CHEINC = 0.0
      EINCT(IPIN)=EINCT(IPIN)+EINC
      NUMBEA(IPIN)=NUMBEA(IPIN)+1.D0
      EINCT(IPIN+5)=EINCT(IPIN+5)+EOPR
      NUMBEA(IPIN+5)=NUMBEA(IPIN+5)+1.D0
      DO 120  I = 1,5
         ECMKE(I) = 0.0
C     TEMPORARY STORAGE FOR UNSCALED K.E. IN C.M. USED IN WEIGHT CALCULA
         PLICIT(I) = 0.0
  120 CONTINUE
C     TEMPORARY STORAGE FOR UNSCALED MULTIPLICITIES USED IN WEIGHT CALCU
      NWDS = NOSLO*8+1
      DO 130 III=2,NWDS,8
         M8=(III+6)/8
         ARRAY(III)=ITSLO(M8)+1
         ARRAY(III+1)=ESLO(M8)
         ARRAY(III+2)=ALPSLO(M8)
         ARRAY(III+3)=BETSLO(M8)
         ARRAY(III+4)=GAMSLO(M8)
  130 CONTINUE
C     TOTAL ENERGY OF INCIDENT PARTICLE  LAB
      ETOT=EINC+AMASIN
C     TOTAL ENERGY OF SCALED INCIDENT PARTICLE  LAB
      ETOTPR=EOPR+AMASIN
C     MOMENTUM OF INCIDENT PARTICLE  LAB
      AMOINC =DSQRT (EINC*(EINC + 2.0D0*AMASIN))
C     MOMENTUM OF SCALED INCIDENT PARTICLE  LAB
      AMOIPR=DSQRT(ETOTPR*ETOTPR-AMASIN*AMASIN)
C     BETA FOR INCIDENT PARTICLE AND TARGET
      BETA=AMOINC/(ETOT+TARMAS)
C     BETA FOR SCALED INCIDENT PARTICLE AND TARGET
      BETAPR=AMOIPR/(ETOTPR+TARMAS)
C     GAMMA FOR INCIDENT PARTICLE
      GAMMA=1.D0/DSQRT(1.D0-BETA*BETA)
C     GAMMA FOR SCALED INCIDENT PARTICLE
      GAMPR=1.D0/DSQRT(1.D0-BETAPR*BETAPR)
C     TOTAL ENERGY OF INCIDENT PARTICLE IN C.M.
      ECM=GAMMA*(ETOT-BETA*AMOINC)
      RECAL1=ECM
C     TOTAL ENERGY OF SCALED INCIDENT PARTICLE IN C.M.
      ECMPR=GAMPR*(ETOTPR-BETAPR*AMOIPR)
C     TOTAL CUTOFF ENERGY IN LAB SYSTEM FOR THE FIVE PARTICLES
C     KINETIC ENERGY OF INCIDENT PARTICLE IN C.M. SYSTEM
      ECMOKE=ECM-RESMAS(IPIN)
      RECAL2=ECMOKE
C     MOMENTUM OF INCIDENT PARTICLE IN C.M. SYSTEM
      PCMO=DSQRT(ECM*ECM-RESMAS(IPIN)*RESMAS(IPIN))
      RECAL3=PCMO
C     COUNTER FOR NUMBER OF COLLISIONS
  140 ECM=RECAL1
      ECMOKE=RECAL2
      PCMO=RECAL3
      DO 150  III = 2,NWDS
  150 BRRAY(III) = ARRAY(III)
  160 EXCIT = EINC + RESMAS(IPIN)*(1.D0-CHEINC)
      PX = 0.
      PY = 0.
      PZ = AMOINC
      PXS = 0.
      PYS = 0.
      PZS = AMOIPR
C     SETUP OF INITIAL LAB MOMENTUM
      DO 190   III = 2,NWDS,8
         KTYPE=ARRAY(III)
C     DEFINES TYPE OF ESCAPING PARTICLE
         M8 = (III+6)/8
         ARRAY(III+1) = ARRAY(III+1)+RESMAS(KTYPE)
C     TOTAL ENERGY OF ESCAPING PARTICLE
         AVERE(KTYPE) = ARRAY(III+1)+AVERE(KTYPE)-CUTL(KTYPE)
C     ENERGY CONSERVATION CHECK OF UNSCALED SYSTEM IN LAB
         YIELD(KTYPE)=YIELD(KTYPE)+1.D0
C     SUMMING UP PARTICLES  FOR MULTIPLICITY
         PLICIT(KTYPE) = PLICIT(KTYPE) + 1.0D0
C     MULTIPLICITY OF ESCAPING PARTICLES FOR THIS COLLISION
         P=(ARRAY(III+1)*ARRAY(III+1)-RESMAS(KTYPE)*RESMAS(KTYPE))**.5
C     MOMENTUM IN LAB OF ESCAPING UNSCALED PARTICLE
         PX=PX+P*ARRAY(III+2)
         PY=PY+P*ARRAY(III+3)
         PZ=PZ-P*ARRAY(III+4)
C     THREE MOMENTUM COMPONENTS IN LAB OF ESCAPING UNSCALED PARTICLE
         CHECK = 0.
         IF(KTYPE.LT.3) CHECK=1.D0
         EXCIT=EXCIT-ARRAY(III+1)+RESMAS(KTYPE)*CHECK
C      PRELIMINARY CALCULATION TO OBTAIN EXCITATION ENERGY
  170    WEIGHT(M8)=GAMMA*(ARRAY(III+1)-ARRAY(III+4)*P*BETA)
         IF(WEIGHT(M8).GT.ECM) COUNT = COUNT + 1.
C     WILL BE USED IN WEIGHT CALCULATION.
C     NOW CONTAINS T.E. IN CM OF UNSCALED ESCAPING PARTICLE
         IF(WEIGHT(M8).GT.ECM) ECMOKE=WEIGHT(M8)-RESMAS(IPIN)
         IF(WEIGHT(M8).GT.ECM) PCMO=DSQRT(WEIGHT(M8)**2-RESMAS(IPIN)**
     +   2)
         IF(WEIGHT(M8).GT.ECM) ECM=WEIGHT(M8)
         ECMKE(KTYPE)=ECMKE(KTYPE)+WEIGHT(M8)-RESMAS(KTYPE)
C     CM KE OF UNSCALED PARTICLES....USED IN CALCULATING B
         PCM=(WEIGHT(M8)*WEIGHT(M8)-RESMAS(KTYPE)*RESMAS(KTYPE))**.5
C     MOMENTUM IN CM OF UNSCALED ESCAPING PARTICLE
         EPRCM(M8)=((WEIGHT(M8)-CUTCM(KTYPE))/(ECM-CUTCM(IPIN )))**
     +   (1.D0/FUG(KTYPE))*(ECMPR-CUTCM(IPIN ))+CUTCM(KTYPE)
C     SCALED UP TOTAL ENERGY OF ESCAPING PARTICLE IN CM
         PTEMP=DSQRT(EPRCM(M8)*EPRCM(M8)-RESMAS(KTYPE)*RESMAS(KTYPE))
C     MOMENTUM OF SCALED UP PARTICLE IN CM
         W=1.D0-(P/PTEMP)**2+((P/PTEMP)**2)*ARRAY(III+4)*ARRAY(III+4)
         IF(W.LE.0.) CHECK8=CHECK8+1.
         IF(W.LE.0.) W=0.
         IF(W.LE.0.) GO TO 180
         W=DSQRT(W)
C     POLAR ANGLE IN CM...COMES FROM CONSERVATION OF TRANSVERSE MOMENTUM
         WCM=GAMMA*(P*ARRAY(III+4)-BETA*ARRAY(III+1))/PCM
C     THE SIGN OF W IS CHECKED NEXT
C      UNSCALED CM POLAR ANGLE
         IF(WCM.LT.0.) W=-W
  180    CONTINUE
         ARRAY(III+1)=GAMPR*(EPRCM(M8)+BETAPR*PTEMP*W)
C     CONTAINS TOTAL SCALED ENERGY IN LAB
         PPR=(ARRAY(III+1)*ARRAY(III+1)-RESMAS(KTYPE)*RESMAS(KTYPE))**
     +   .5
C     MOMENTUM OF SCALED PARTICLE IN LAB
         ARRAY(III+4)=GAMPR*(PTEMP*W+BETAPR*EPRCM(M8))/PPR
C     CORRECTED POLAR ANGLE IN LAB TO CONSERVE TRANSVERSE MOMENTUM
         ARRAY(III+1)=ARRAY(III+1)-RESMAS(KTYPE)
C     K.E. IN LAB OF SCALED PARTICLE
         PSTOR1=DSQRT(1.D0-ARRAY(III+4)*ARRAY(III+4))* DCOS(DATAN(ARRAY
     +   (III+3)/ARRAY(III+2)))
         PSTOR1=DABS(PSTOR1)
         PSTOR2=DSQRT(1.D0-ARRAY(III+4)*ARRAY(III+4))* DSIN(DATAN(ARRAY
     +   (III+3)/ARRAY(III+2)))
         PSTOR2=DABS(PSTOR2)
         IF(ARRAY(III+2).LT.0.) PSTOR1=-PSTOR1
         IF(ARRAY(III+3).LT.0.) PSTOR2=-PSTOR2
C     SETTING UP MODIFIED PX,PY TO PRESERVE THE AZIMUTHAL ANGLE
         ARRAY(III+2)=PSTOR1
         ARRAY(III+3)=PSTOR2
C     RESTORING CORRECTED X AND Y COSINES
  190 CONTINUE
      B = ECMOKE + AMASIN*(1.D0-CHEINC)
      DO 200  IIV = 1,5
  200 B=B-ECMKE(IIV)+PLICIT(IIV)*(CUTCM(IIV)-RESMAS(IIV))
      BTOT = BTOT + B
      BLANK = 1.D0
      BLANK1 = 1.D0/(ECM-CHEINC*AMASIN-B)
      DO 210  J = 2,NWDS,8
         KTYPE = ARRAY(J)
         M9 = (J+6)/8
         IF(KTYPE.LE.2)WEIGHT(M9)=(WEIGHT(M9)-CUTCM(KTYPE))/ (EPRCM(M9)
     +   -CUTCM(KTYPE))
         IF(KTYPE.GT.2)WEIGHT(M9)=WEIGHT(M9)/EPRCM(M9)
  210 CONTINUE
      AMORN=TARMAS+CHEINC*AMASIN - PLICIT(1)*RESMAS(1)-PLICIT(2)*
     +      RESMAS(2) +(PLICIT(1)+PLICIT(2))*7.0D0-CHEINC*7.D0
C     MASS OF RESIDUAL NUCLEUS
      IF(AMORN.LE.0.)WHY=1.
C     WHY=1  UNSCALED RESIDUAL MASS.LE.0
      IF(AMORN.LE.0.) GO TO 220
      AMORNT = AMORNT + AMORN
      ERN=DSQRT(PX*PX+PY*PY+PZ*PZ+AMORN*AMORN)-AMORN
C     ENERGY OF RECOILING NUCLEUS (UNSCALED)
      ERNT=ERNT+ERN
C     SUMMING TOTAL RECOIL ENERGIES FOR ALL COLLISIONS UNSCALED
      ESTAR=EXCIT-ERN-(PLICIT(1)+PLICIT(2)-1.D0*CHEINC)*7.D0
      ESTART=ESTART+ESTAR
      IF(ESTAR.LT.0.) CHECK7=CHECK7+1.
      IF(ESTAR.LT.0.) GO TO 270
      GO TO 290
  220 NMLTEO=NMLTEO+1
      ZKZ = ZKZ - 1.D0
  230 BTOT = BTOT - B
      DO 240   III = 2,NWDS,8
         KTYPE = ARRAY(III)
         YIELD(KTYPE)=YIELD(KTYPE)-1.D0
         AVERE(KTYPE)=AVERE(KTYPE)-BRRAY(III+1)+(CUTL(KTYPE)- RESMAS(KT
     +   YPE))
  240 CONTINUE
      GO TO 60
  250 DO 260   III = 2,NWDS,8
         KTYPE = ARRAY(III)
         M8 = (III+6)/8
         YIELD(KTYPE)=YIELD(KTYPE)-1.D0
         AVERE(KTYPE)=AVERE(KTYPE)-BRRAY(III+1)+(CUTL(KTYPE)- RESMAS(KT
     +   YPE))
         YIELD(KTYPE+5) = YIELD(KTYPE+5) - WEIGHT(M8)
         AVERE(KTYPE+5)=AVERE(KTYPE+5)-ARRAY(III+1)*WEIGHT(M8)+ (CUTL(K
     +   TYPE)-RESMAS(KTYPE))*WEIGHT(M8)
  260 CONTINUE
      BTOT = BTOT-B
      ZKZ = ZKZ - 1.D0
      ERNT=ERNT-ERN
      ESTART=ESTART-ESTAR
      AMORNT=AMORNT-AMORN
      GO TO 60
  270 ERNT = ERNT - ERN
      ERN = ERN+ESTAR
      ESTART = ESTART-ESTAR
      ERNT=ERNT+ERN
      ESTAR=0.
      IF(ERN.LT.0.) COUNT5 = COUNT5 + 1.
      IF(ERN.LT.0.)WHY=2
C     WHY=2  ENERGY OF UNSCALED RECOILING NUCLEUS.LT.0 WHEN ESTAR.LT.0.
C                 ERN=ERN+ESTAR.......ERN.LT.0
      IF(ERN.GE.0.) GO TO 290
      ZKZ=ZKZ-1.D0
      AMORNT=AMORNT-AMORN
      BTOT=BTOT-B
      ERNT=ERNT-ERN
      DO 280   III=2,NWDS,8
         KTYPE=ARRAY(III)
         YIELD(KTYPE)=YIELD(KTYPE)-1.D0
         AVERE(KTYPE)=AVERE(KTYPE)-BRRAY(III+1)+(CUTL(KTYPE)- RESMAS(KT
     +   YPE))
  280 CONTINUE
      GO TO 60
  290 CONTINUE
C*****CALCULATIONS DEALING WITH SCALED UP NUCLEAR2 RECOIL AND BPR********
      A1=0.
      A2=0.
      A3=0.
      A4=0.
      A5=0.
      DO 300  III=2,NWDS,8
         M8=(III+6)/8
         KTYPE=ARRAY(III)
         P=((ARRAY(III+1)+RESMAS(KTYPE))**2-RESMAS(KTYPE)**2)**.5
         A1=P*ARRAY(III+2)*WEIGHT(M8)+A1
         A2=P*ARRAY(III+3)*WEIGHT(M8)+A2
         A3=P*ARRAY(III+4)*WEIGHT(M8)+A3
         A4=(ARRAY(III+1)+RESMAS(KTYPE))*WEIGHT(M8)+A4
         IF(KTYPE.GT.2.) GO TO 300
         A5=(7.D0-RESMAS(KTYPE))*WEIGHT(M8)+A5
  300 CONTINUE
      A11=A1*A1+A2*A2+A3*A3+A5*A5-A4*A4
      B11=2.D0*((TARMAS+(AMASIN-7.D0)*CHEINC)*A5-AMOIPR*A3+A4*(ETOTPR
     + +TARMAS-ESTAR))
      C11=AMOIPR*AMOIPR+(TARMAS+(AMASIN-7.D0)*CHEINC)**2
     + -(ETOTPR+TARMAS-ESTAR)**2
      IF(A11.EQ.0.) COUNT1=COUNT1 + 1.
      IF(A11.EQ.0.) GO TO 310
      ANSPLU=(-B11+DSQRT(B11**2-4.D0*A11*C11))/(2.D0*A11)
      ANSMIN=(-B11-DSQRT(B11**2-4.D0*A11*C11))/(2.D0*A11)
      GO TO 320
  310 ANSWER=-C11/B11
      IF(ANSWER.LE.0.) COUNT2=COUNT2+1.
      IF(ANSWER.LE.0.) WHY=3
C     SOLUTION TO ENERGY BALANCE EQUATION IS .LE. 0.
      IF(ANSWER.LE.0.) GO TO 350
      ANSMIN=ANSWER
      ANSPLU=ANSWER
C$$$$$PUT IN CHECK
  320 SCORE=0.
      CHECK=0.
      DO 340  I=1,2
         A1=0.
         A2=0.
         A3=0.
         A4=0.
         A5=0.
         ANSWER=ANSPLU
         IF(I.EQ.2) ANSWER=ANSMIN
         DO 330 III=2,NWDS,8
            M8=(III+6)/8
            KTYPE=ARRAY(III)
            P=((ARRAY(III+1)+RESMAS(KTYPE))**2-RESMAS(KTYPE)**2)**.5
            A6=ANSWER*WEIGHT(M8)
            A1=A1+P*ARRAY(III+2)*A6
            A2=A2+P*ARRAY(III+3)*A6
            A3=A3+P*ARRAY(III+4)*A6
            IF(KTYPE.LT.3) A4=A4+(7.D0-RESMAS(KTYPE))*A6
            A5 = A5 + (ARRAY(III+1)+RESMAS(KTYPE))*WEIGHT(M8)
  330    CONTINUE
         A7=A1*A1+A2*A2+(AMOIPR-A3)**2+(TARMAS+(AMASIN-7.D0)*CHEINC
     +   +A4)**2
         A7=DSQRT(A7)
         D1 = (ETOTPR + TARMAS - ESTAR - A7)/A5
         STO =DABS((ANSWER-D1)/ANSWER)
         IF(I.EQ.1) A8=A7
         IF(I.EQ.1) STOO = STO
         IF(STO.LE..00001) COUNT3 = COUNT3 + 1.
         IF(STO.LE..00001) CHECK=I
         IF(STO.LE..00001) SCORE=SCORE+1.
  340 CONTINUE
      IF(SCORE.EQ.0.) WHY=5
C     WHY=5  ENERGY EQUATION NOT SATISFIED
      IF(SCORE.NE.0.) GO TO 360
  350 ZKZ = ZKZ-1.D0
      NTTME=NTTME+1
      ERNT=ERNT-ERN
      ESTART=ESTART-ESTAR
      AMORNT=AMORNT-AMORN
      GO TO 230
  360 CONTINUE
      IF(SCORE.EQ.2.) GO TO 370
      IF(CHECK.EQ.1.D0) ANSWER = ANSPLU
      IF(ANSWER.LE.0.) COUNT2=COUNT2+1.
      IF(ANSWER.LE.0.) WHY=3
      IF(ANSWER.LT.0.) GO TO 350
      GO TO 390
  370 IF(ANSPLU.GT.0.AND.ANSMIN.GT.0.) GO TO 380
      IF(ANSPLU.GT.0.) ANSWER=ANSPLU
      IF(ANSMIN.GT.0.) ANSWER=ANSMIN
      GO TO 390
  380 IF(A8.LT.A7) ANSWER=ANSPLU
      IF(ANSWER.LE.0.) COUNT2=COUNT2+1.
      IF(ANSWER.LE.0.) WHY=3
      IF(ANSWER.LE.0.) GO TO 350
  390 D1=0.
      DO 410  III=2,NWDS,8
         KTYPE=ARRAY(III)
         M8=(III+6)/8
         WEIGHT(M8)=ANSWER*WEIGHT(M8)
         IF(KTYPE.GT.2) GO TO 400
         D1=D1+WEIGHT(M8)*RESMAS(KTYPE)-7.D0*WEIGHT(M8)
         P=((ARRAY(III+1)+RESMAS(KTYPE))**2-RESMAS(KTYPE)**2)**.5
  400    CONTINUE
         AVERE(KTYPE+5)=AVERE(KTYPE+5)+ARRAY(III+1)*WEIGHT(M8)- (CUTL(K
     +   TYPE)-RESMAS(KTYPE))*WEIGHT(M8)
C       CALCULATION FOR SCALED-UP ENERGY
         YIELD(KTYPE+5)=YIELD(KTYPE+5)+WEIGHT(M8)
C     CALCULATION FOR MULTIPLICITY OF SCALED-UP PARTICLES
         PXS=PXS+WEIGHT(M8)*P*ARRAY(III+2)
         PYS=PYS+WEIGHT(M8)*P*ARRAY(III+3)
         PZS=PZS-WEIGHT(M8)*P*ARRAY(III+4)
  410 CONTINUE
      BARB=TARMAS+(AMASIN-7.D0)*CHEINC-D1
      IF(BARB.LE.0.) COUNT4=COUNT4+1.
      IF(BARB.LE.0.)WHY=4.
C     WHY=4  SCALED UP RESIDUAL MASS LE.0
      IF(BARB.LE.0.) GO TO 250
      ERNPR=(PXS*PXS+PYS*PYS+PZS*PZS+(TARMAS+(AMASIN-7.D0)*CHEINC-D1)**2
     +)**.5-TARMAS-(AMASIN-7.D0)*CHEINC+D1
      ERNPRT=ERNPR+ERNPRT
      BTOTPR=BTOTPR+ECMPR-ANSWER/BLANK1-RESMAS(IPIN)*CHEINC
      AMRNST = AMRNST + (TARMAS+(AMASIN-7.D0)*CHEINC-D1)
      RMFAS=BARB
      REFAS=ERNPR
      EXFAS=ESTAR
      NOFAS=NOSLO
C*****END CALCULATIONS DEALING WITH SCALED UP NUCLEAR RECOIL AND BPR****
  420 CONTINUE
      DO 430 III=2,NWDS,8
         M8=(III+6)/8
         EFAS(M8)=ARRAY(III+1)
         ALPFAS(M8)=ARRAY(III+2)
         BETFAS(M8)=ARRAY(III+3)
         GAMFAS(M8)=ARRAY(III+4)
         WTFAS(M8)=WEIGHT(M8)
  430 CONTINUE
      RETURN
  440 DO 450   IHK=1,10
         NUMBEA(IHK)=NUMBEA(IHK)/ZKZ
         EINCT(IHK)=EINCT(IHK)/ZKZ
         YIELD(IHK)=YIELD(IHK)/ZKZ
         AVERE(IHK)=AVERE(IHK)/ZKZ
  450 CONTINUE
      ESTART = ESTART/ZKZ
      TARMAT=TARMAT/ZKZ
      BTOTPR=BTOTPR/ZKZ
      AMORNT = AMORNT/ZKZ
      AMRNST = AMRNST/ZKZ
      ERNT=ERNT/ZKZ
      ERNPRT=ERNPRT/ZKZ
      BTOT = BTOT/ZKZ
      ETOT=0.
      ETOTPR=0.
      DO 460  I=1,5
         ETOT=ETOT+EINCT(I)+RESMAS(I)*NUMBEA(I)
         ETOTPR=ETOTPR+EINCT(I+5)+RESMAS(I)*NUMBEA(I+5)
  460 CONTINUE
      ESUM = 0.0
      ESUMPR = 0.0
      DO 470   I = 1,5
         ESUM = ESUM + AVERE(I)
         ESUMPR = ESUMPR + AVERE(I+5)
  470 CONTINUE
      RETURN
      END
*CMZ :  0.93/08 02/03/93  09.35.17  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE SHXSEC(E,INC,SIGT,SIGEL,SIGNEL)
C
*KEEP,CINOUT.
       COMMON/ CINOUT / IQIQ,IO
C
*KEND.
C
C CALCULATES PROTON AND NEUTRON CROSS SECTIONS FOR E > 3.5 GeV
C CALCULATES PI+    AND PI-     CROSS SECTIONS FOR E > 2.5 GeV
C       THE TARGET PARTICLE IS A PROTON
C       E ------- KINETIC ENERGY OF INCIDENT PARTICLE(MEV)
C       INC ----- TYPE OF INCIDENT PARTICLE
C                   0 -- PROTON
C                   1    NEUTRON
C                   2    PI+
C                   3    NOT USED
C                   4    PI-
C       SIGT ---- TOTAL CROSS SECTION(CM**2)
C       SIGEL --- ELASTIC CROSS SECTION(CM**2)
C       SIGNEL -- NONELASTIC CROSS SECTION(CM**2)
C
      REAL*8 E1
      IN = INC + 1
      E1 = E*1.D-3
      GO TO (20,30,50,10,80),IN
   10 CALL CERROR('CRSEC1')
C
   20 SIGT = 37.5D0 + 7.D0/(DSQRT(E1))
      SIGEL = 7.D0 + 21.03D0/(E1**0.873D0)
      GO TO 110
C
C
   30 IF(E1.GT.8.D0) GO TO 40
      SIGT = 42.D0
      SIGEL = -0.222D0*E1+12.48D0
      GO TO 110
   40 SIGT = 37.5D0 + 26.45D0/(E1**0.852D0)
      SIGEL = 6.0D0 + 73.144D0/(E1**1.32D0)
      GO TO 110
C
C
   50 IF(E1.GT.3.D0) GO TO 60
      SIGT = -4.66D0*E1 + 42.95D0
      SIGEL = -1.40D0*E1 + 10.0D0
      GO TO 110
   60 IF(E1.GT.6.D0) GO TO 70
      SIGT = -0.7567D0*E1 + 31.24D0
      SIGEL = -0.166D0*E1 + 6.298D0
      GO TO 110
   70 SIGT = 21.50D0 + 18.914D0/(E1**.7155D0)
      SIGEL = 3.5D0 + 9.93D0/(E1**.953D0)
      GO TO 110
C
C
   80 IF(E1.GT.5.D0) GO TO 90
      SIGT = -1.66D0*E1 + 37.34D0
      GO TO 100
   90 SIGT = 23.60D0 + 25.51D0/(E1**0.959D0)
  100 SIGEL = 3.8D0 + 7.273D0/(E1**0.896D0)
C
C
  110 SIGT = SIGT*1.E-27
      SIGEL = SIGEL*1.E-27
      SIGNEL = SIGT - SIGEL
C
      IF((IN.LE.2).AND.(E1.LT.3.4949D0)) WRITE(IO,10000) E1
      IF((IN.GT.2).AND.(E1.LT.2.4949D0)) WRITE(IO,10100) E1
10000 FORMAT(' HETC:  PROTON OR NEUTRON CROSS-SECTIONS ARE BEING
     + REQUESTED FOR AN ENERGY LESS THAN 3.5-GEV in SHXSEC E=',G18.7)
10100 FORMAT(' HETC:  PI+ OR PI- CROSS-SECTIONS ARE BEING REQUESTED
     + FOR AN ENERGY LESS THAN 2.5-GEV in SHXSEC E=',G18.7)
      RETURN
      END
*CMZ :  1.01/04 10/06/93  14.43.50  by  Christian Zeitnitz
*-- Author : Christian Zeitnitz  19/11/92
      SUBROUTINE SKALEH(IBERT,ITINC,HSIG,EINC,NOFAS,ITFAS,EFAS,ALPHAS,
     +  BETFAS,GAMFAS,EHICUT)
C
*KEEP,CMASS.
      REAL*4 XMASS(0:11)
      COMMON/CMASS/XMASS
      DIMENSION PMASS(12)
      EQUIVALENCE(PMASS(1),XMASS(0))
C
*KEND.
      DIMENSION ITFAS(*), EFAS(*) , ALPHAS(*) , BETFAS(*) , GAMFAS(*)
      DIMENSION R(60)
      SAVE
C
      ITYPE = ITINC + 1
      CALL CPCOL(IBERT,ITYPE,HSIG,EHICUT,NOFAS,ITFAS,EFAS,ALPFAS,BETFAS,
     +  GAMFAS)
      IF(NOFAS.LE.0) RETURN
CZ simple scaling for H-collision, conserve energy  19 Nov. 1992
      EI=EINC+PMASS(ITINC+1)
      ESUMF = 0.0
      DO 10 I=1,NOFAS
         ESUMF=ESUMF+PMASS(ITFAS(I)+1)+EFAS(I)
   10 CONTINUE
      EDIV = EI-ESUMF
      IF(EDIV.LE.0.0) RETURN
      CALL GRNDM(R,NOFAS)
      RS=0.0
      DO 20 I=1,NOFAS
         RS=RS+R(I)
   20 CONTINUE
      DO 30 I=1,NOFAS
         EFAS(I) = EFAS(I)+R(I)/RS*EDIV
   30 CONTINUE
      RETURN
      END
*CMZ :  0.93/01 08/02/93  14.21.45  by  Christian Zeitnitz
*-- Author :
      SUBROUTINE CSCATT(INC,EKE1,ITFAS,EFAS,ALPFAS,BETFAS,GAMFAS)
C
C
C      INC = TYPE OF INCIDENT PARTICLE
C               = 0  PROTON
C               = 1  NEUTRON
C               = 2  PI +
C               = 3  NOT USED
C               = 4  PI -
C      EKE1 = KINETIC ENERGY OF INCIDENT PARTICLE(MEV)
C      ITFAS = TYPE OF PARTICLE (SAME AS ABOVE)
C      EFAS = KINETIC ENERGY OF PARTICLES (MEV)
C      ALPFAS = X-DIRECTION COSINE
C      BETFAS = Y-DIRECTION COSINE
C      GAMFAS = Z-DIRECTION COSINE
C      RANDS = LOCATION OF RANDOM NUMBER SEQUENCE
C
C               SUBROUTINES CALLED CAAZIO.
C
      DIMENSION ITFAS(2),EFAS(2),ALPFAS(2),BETFAS(2),GAMFAS(2),RANDS(4)
      REAL*8 B,M1,M2,E1,P1,ECM1,PCM1,ETLAB,ETCM,BETA,GAMMA,T1,T2,T3,T4,
     1 T5,T6,T7,T8,T9,T10,T11,T12,PLAB1,PLAB2,CST,SNT,TB
*KEEP,CRANDM.
      DOUBLE PRECISION RANDC2
*KEND.
C
      DATA M2/940.075D0/
      SAVE
C
      T2 = M2*M2
      IN=INC+1
      GO TO (10,10,20,30,40),IN
   10 M1=940.075D0
      GO TO 60
   20 B=7.040D-6
      GO TO 50
   30 CALL CERROR('SCATT1')
   40 B=7.575D-6
   50 M1=139.89D0
   60 E1=EKE1+M1
      T1=M1*M1
      P1=DSQRT(E1*E1-T1)
      IF(IN.GT.2) GO TO 70
      B=7.26D-6+ (3.13D-11)*P1
   70 ETLAB=E1+M2
      BETA=P1/ETLAB
      GAMMA=1.D0/DSQRT(1.D0-BETA*BETA)
      ETCM=ETLAB/GAMMA
      T3=T1+T2
      T4=T1-T2
      T4=T4*T4
      T5=ETCM*ETCM
      T6=T5*T5
      T7=B*(T6-2.D0*T5*T3+T4)/(2.D0*T5)
      T8 = RANDC2(ISEED)
      TB=T7
      IF(T7.GT.50.D0) TB=50.D0
      CST=1.D0+(DLOG(1.D0-T8*(1.D0-DEXP(-TB))))/T7
      SNT=DSQRT(1.D0-CST*CST)
      CALL CAAZIO(T9,T10)
      ECM1=(T5+T1-T2)/(2.D0*ETCM       )
      PCM1=DSQRT(ECM1*ECM1-T1)
      ITFAS(1)=INC
      ITFAS(2)=0.
      T11    = GAMMA*(ECM1+PCM1*CST*BETA) - M1
      T12 = ETLAB - T11 -M1 - M2
      PLAB1 = DSQRT(2.D0*M1*T11 + T11*T11)
      PLAB2 = DSQRT(2.D0*M2*T12 + T12*T12)
      EFAS(1) = T11
      EFAS(2) = T12
      ALPFAS(1)=PCM1*SNT*T9
      ALPFAS(2)= -ALPFAS(1)
      ALPFAS(1)=ALPFAS(1)/PLAB1
      ALPFAS(2)=ALPFAS(2)/PLAB2
      BETFAS(1)=PCM1*SNT*T10
      BETFAS(2)=-BETFAS(1)
      BETFAS(1)=BETFAS(1)/PLAB1
      BETFAS(2)=BETFAS(2)/PLAB2
      GAMFAS(1)= GAMMA*(PCM1*CST+BETA*ECM1)
      GAMFAS(2)= -GAMFAS(1)+P1
      GAMFAS(1)= GAMFAS(1)/PLAB1
      GAMFAS(2)= GAMFAS(2)/PLAB2
      RETURN
      END
