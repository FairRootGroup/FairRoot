// $Id: f_find_peaks.h 478 2009-10-29 12:26:09Z linev $
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum für Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef F_FIND_PEAKS
#define F_FIND_PEAKS

#define TYPE__SHORT  0
#define TYPE__INT    1
#define TYPE__FLOAT  2
#define TYPE__DOUBLE 3
void f_find_peaks(
  void*,     // pointer to data
  int,       // data type: use definitions above
  int,       // first channel (0,...)
  int,       // number of channels
  int,       // channels to sum up (bin size in channels)
  double,    // noise factor to square root
  double,    // noise minimum (absolut)
  double*,   // array with noise (original channels)
  int,       // Maximum number of peaks. Arrays below must have this size.
  int*,      // returns number of peaks found
  int*,      // pointer to array of minima
  double*,   // pointer to array of minima values
  int*,      // pointer to array of maxima
  int*,      // pointer to array of width
  double*);  // pointer to array of integrals

#endif
