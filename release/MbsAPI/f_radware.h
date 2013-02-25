// $Id: f_radware.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef F_RADWARE
#define F_RADWARE

// Output functions for Radware

int f_radware_out1d(char* file, char* histogram, float* data, int channels, int over);
int f_radware_out2d(char* file, char* histogram, int*   data, int channels, int over);

// file     : output file name
// histogram: name of histogram
// data     : pointer to data (float for 1d, int for 2d)
// channels : # of channels
// over     : flag, if = 1, delete file first

#endif
