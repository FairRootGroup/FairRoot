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
