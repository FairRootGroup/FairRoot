/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

class FairParAsciiFileIo : public FairParIo
{
  public:
    FairParAsciiFileIo() = default;
    FairParAsciiFileIo(const FairParAsciiFileIo&) = delete;
    FairParAsciiFileIo& operator=(const FairParAsciiFileIo&) = delete;

    /**
     * default destructor closes an open file and deletes list of I/Os
     */
    ~FairParAsciiFileIo() override = default;

    /**
     * \brief Opens file
     *
     * If a file is already open, this file will be closed,
     * activates detector I/Os.
     * \param fname name of the parameter file
     * \param status reading with "in" or writing with "out"
     */
    Bool_t open(const Text_t* fname, const Text_t* status = "in");

    /**
     * \brief Opens TList of files
     *
     * Concatenates files whose names are stored in the TList,
     * TList holds list of TObjStrings.
     * Calls MergeFiles with all_$pid.par in local working directory,
     * calls open to open the generated file all_$pid.par.
     * \param fnamelist TList of file names to be merged
     * \param status reading with "in" or writing with "out"
     */
    Bool_t open(const TList* fnamelist, const Text_t* status = "in");

    /**
     * \brief Merges files
     *
     * \param fname the merged file name, f.e. "all.par"
     * \param fnamelist TList of file names to be merged
     *
     * Users should call standard open (f.e. open("all.par")) after calling this function.
     */
    static void MergeFiles(const char* fname, const TList* fnamelist);

    // closes file
    void close() override;

    // returns kTRUE if file is open
    Bool_t check() override { return file.is_open(); }

    // prints information about the file and the detector I/Os
    void print() override;

    std::fstream* getFile() { return &file; }

  private:
    std::fstream file{};
    void ActivateSelf();

    ClassDefOverride(FairParAsciiFileIo, 0);   // Parameter I/O from ASCII files
};

#endif /* !FAIRPARASCIIFILEIO_H */
