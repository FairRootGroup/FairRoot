#ifndef FAIRDBLOGBOUNDFORMAT_H
#define FAIRDBLOGBOUNDFORMAT_H


class FairDbLogFormat;

class FairDbLogBoundFormat
{
  public:
    FairDbLogBoundFormat(const FairDbLogFormat& ff, double v) : f(ff), val(v) {;}
    ~FairDbLogBoundFormat() {;}

#ifndef __CINT__
    const FairDbLogFormat& f;
#endif
    double val;
};

#endif // 
