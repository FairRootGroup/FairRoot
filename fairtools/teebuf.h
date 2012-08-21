#ifndef TEEBUF_H
#define TEEBUF_H

#include <streambuf>
#include <stdio.h>

class teebuf: public std::streambuf
{
  public:
    // Construct a streambuf which tees output to both input
    // streambufs.
    teebuf(std::streambuf* _sb1, std::streambuf* _sb2)
      : sb1(_sb1)
      , sb2(_sb2) {
    }
    void reopen(std::streambuf* _sb1, std::streambuf* _sb2)
    { sb1 = _sb1; sb2 = _sb2; }


  private:
    // This tee buffer has no buffer. So every character "overflows"
    // and can be put directly into the teed buffers.
    virtual int overflow(int c) {
      if (c == EOF) {
        return !EOF;
      } else {
        int const r1 = sb1->sputc(c);
        int const r2 = sb2->sputc(c);
        return r1 == EOF || r2 == EOF ? EOF : c;
      }
    }

    // Sync both teed buffers.
    virtual int sync() {
      int const r1 = sb1->pubsync();
      int const r2 = sb2->pubsync();
      return r1 == 0 && r2 == 0 ? 0 : -1;
    }
  private:
    std::streambuf* sb1;
    std::streambuf* sb2;
};
#endif
