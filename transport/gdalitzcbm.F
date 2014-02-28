c------------------------------------------------------------------------------
c Generation of 2 particle mass according to the VDM form factor
c for Dalitz decay of (id) 1=pi0 2=eta  to (e+e-) gamma and 3=omega to pi0 e+e-
c------------------------------------------------------------------------------

      real function dalitz_evgen(id)
      real xmin(3), xmax(3), wmax(3), mesonmass(3), rndm(2)
      integer isw(3)
      data mesonmass/134.9766,547.75,782.59/
      data isw/1,1,2/
      data xstep/0.1/
      logical maxfound(3)
      data maxfound/3*.FALSE./
      save maxfound, wmax

      if (.NOT. maxfound(id)) then
         wmax(id) = 0.0
         xmas    = 0.0
 1       xmas    = xmas + xstep
         ff = vdmform(xmas,mesonmass(id),isw(id))
         if (ff .gt. wmax(id)) wmax(id) = ff
         if (xmas .lt. mesonmass(id)) goto 1
         maxfound(id) = .TRUE.
      end if

 2    call grndm(rndm,2)
      rnd1 = rndm(1)*mesonmass(id)
      rnd2 = rndm(2)*wmax(id)
      ff = vdmform(rnd1,mesonmass(id),isw(id))
      if (ff .lt. rnd2) goto 2
      
      dalitz_evgen = rnd1/1000.

      return
      end


