#ifndef FAIRTESTNEWOUTPUTHANDLER_H_
#define FAIRTESTNEWOUTPUTHANDLER_H_
#pragma once

#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include <vector>


/*
struct cout_redirect {
  // cout_redirect( std::streambuf * new_buffer )
  //      : old( std::cout.rdbuf( new_buffer ) )
  //  { }

  cout_redirect()
   : old( std::cout.rdbuf() )
  { }

  void Set( std::streambuf * new_buffer ) {
    old = std::cout.rdbuf();  // back up cout's streambuf
    std::cout.rdbuf(new_buffer);         // assign streambuf to cout
  }

  void Reset() {
    std::cout.rdbuf( old );
  }

  ~cout_redirect( ) {
    std::cout.rdbuf( old );
  }

private:
    std::streambuf * old;
};

struct cerr_redirect {
  //    cerr_redirect( std::streambuf * new_buffer )
  //      : old( std::cerr.rdbuf( new_buffer ) )
  //  { }

   cerr_redirect()
   : old( std::cerr.rdbuf() )
    { }

  void Set( std::streambuf * new_buffer ) {
    old = std::cerr.rdbuf();  // back up cerr's streambuf
    std::cerr.rdbuf(new_buffer);         // assign streambuf to cerr
  }

  void Reset() {
    std::cerr.rdbuf( old );
  }

  ~cerr_redirect( ) {
    std::cerr.rdbuf( old );
  }

private:
    std::streambuf * old;
};

*/

class FairTestNewOutputHandler
{
  public:

    FairTestNewOutputHandler( bool captureStdErr = true, bool captureStdOut = false );
    ~FairTestNewOutputHandler();


    std::string GetCaptureLine(int line);
    int GetNumberOfLines();

  private:

    std::streambuf* old_cout;
    std::streambuf* old_cerr;
    //    cout_redirect  fCout;
    //    cerr_redirect  fCerr;

    boost::test_tools::output_test_stream output;

    std::vector < std::string > fLineVector;

    bool fCaptureEnded;
    bool fCaptureStdOut;
    bool fCaptureStdErr;

    void Split();

};
#endif
