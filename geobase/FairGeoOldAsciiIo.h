/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOOLDASCIIIO_H
#define FAIRGEOOLDASCIIIO_H

#include "FairGeoIo.h"                  // for FairGeoIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Bool_t, kFALSE, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoInterface;
class FairGeoMedia;
class FairGeoNode;
class FairGeoSet;

/**
 * Class for geometry I/O from ASCII file in FAIR format
 * @author Ilse koenig
 */
class FairGeoOldAsciiIo: public FairGeoIo
{
    TString  filename;
    TString  filedir;
    Bool_t   writable;
    std::fstream* file;
  public:
    FairGeoOldAsciiIo();
    ~FairGeoOldAsciiIo();
    void setDirectory(const char* fDir) {filedir=fDir;}
    const char* getDirectory() {return filedir.Data();}
    const char* getFilename() {return filename.Data();}
    Bool_t open(const char*,const Text_t* status="in");
    Bool_t isOpen();
    Bool_t isWritable();
    void close();
    void print();
    Bool_t read(FairGeoMedia*) {return kFALSE;}
    Bool_t read(FairGeoSet*,FairGeoMedia*);
    Bool_t write(FairGeoMedia*) {return kFALSE;}
    Bool_t write(FairGeoSet*) {return kFALSE;}
    Bool_t readGeomConfig(FairGeoInterface*) {return kFALSE;}
    Bool_t readDetectorSetup(FairGeoInterface*) {return kFALSE;}
    Bool_t setSimulRefRun(const char*) {return kTRUE;}
    Bool_t setHistoryDate(const char*) {return kTRUE;}
  private:
    Bool_t calculateShapePoints(Double_t*,FairGeoNode*);
    FairGeoOldAsciiIo(const FairGeoOldAsciiIo&);
    FairGeoOldAsciiIo& operator=(const FairGeoOldAsciiIo&);

    ClassDef(FairGeoOldAsciiIo,0) //
};

#endif  /* !FAIRGEOOLDASCIIIO_H */
