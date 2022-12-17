/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARASCIFILEIIO_H
#define FAIRPARASCIFILEIIO_H

#include "FairParIo.h"   // for FairParIo

#include <Rtypes.h>   // for Bool_t, Text_t, etc
#include <fstream>    // for fstream, etc

class TList;

class FairParAsciiFileIo : public FairParIo
{
  protected:
    std::fstream* file;   // pointer to a file

  public:
    FairParAsciiFileIo();

    // default destructor closes an open file and deletes list of I/Os
    ~FairParAsciiFileIo();

    // opens file
    // if a file is already open, this file will be closed
    // activates detector I/Os
    Bool_t open(const Text_t* fname, const Text_t* status = "in");

    // concatenate files whose names are stored in the TList
    // TList holds list od TObjStrings
    // create file all.par in local working directory
    // calls open to open the generated file all.par
    Bool_t open(const TList* fnamelist, const Text_t* status = "in");

    // closes file
    void close() override;

    // returns kTRUE if file is open
    Bool_t check() override
    {
        if (file) {
            return (file->rdbuf()->is_open() == 1);
        } else {
            return kFALSE;
        }
    }

    // prints information about the file and the detector I/Os
    void print() override;

    std::fstream* getFile();

  private:
    FairParAsciiFileIo(const FairParAsciiFileIo&);
    FairParAsciiFileIo& operator=(const FairParAsciiFileIo&);

    ClassDefOverride(FairParAsciiFileIo, 0);   // Parameter I/O from ASCII files
};

#endif /* !FAIRPARASCIIFILEIO_H */
