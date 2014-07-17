/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOGBDFORMAT_H
#define FAIRDBLOGBDFORMAT_H


class FairDbLogFormat;

class FairDbLogBFormat
{
  public:
    FairDbLogBFormat(const FairDbLogFormat& ff, double v) : f(ff), val(v) {;}
    ~FairDbLogBFormat() {;}

#ifndef __CINT__
    const FairDbLogFormat& f;
#endif
    double val;
};

#endif // 
