#ifndef FAIRTEESTREAM_H
#define FAIRTEESTREAM_H

#include "teebuf.h"
#include <ostream>
#include <fstream>

class FairTeeStream : public std::ostream
{
  public:
    // Construct an ostream which tees output to the supplied
    // ostreams.
    FairTeeStream();
    FairTeeStream(std::ostream& o1, std::ostream& o2);
    //    FairTeeStream(std::ostream & o1, const char* filename);

    void  SetInput(std::ostream& o1, const char* filename);
    void  SetInput(std::ostream& o1, std::ofstream& o2);
    void  SetInputToCerr();
    std::ostream* GetTeeStream() { return this; }

  private:
    std::ofstream log;
    teebuf tbuf;

};

#endif
