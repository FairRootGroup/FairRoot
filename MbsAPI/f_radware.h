/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
