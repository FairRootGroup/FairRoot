#include "FairTeeStream.h"
#include <iostream>

FairTeeStream::FairTeeStream(std::ostream& _o1, std::ostream& _o2)
  : log("bla.txt"),
    std::ostream(&tbuf),
    tbuf(_o1.rdbuf(), _o2.rdbuf())
{
}

FairTeeStream::FairTeeStream()
  : log("bla.txt"),
    std::ostream(&tbuf),
    tbuf(std::cerr.rdbuf(), log.rdbuf())
{
}

void FairTeeStream::SetInput(std::ostream& _o1, const char* filename)
{
  log.close();
  log.open(filename);
  tbuf.reopen(std::cerr.rdbuf(), log.rdbuf());
}


