/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDETPARASCIIFILEIO_H
#define FAIRDETPARASCIIFILEIO_H

#include "FairDetParIo.h"               // for FairDetParIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Text_t, Bool_t, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairParSet;

class FairDetParAsciiFileIo : public FairDetParIo
{
  protected:
    TString fHeader;  //! header of container output in file
    TString sepLine;  //! comment line
    std::fstream* pFile;   //! pointer to ascii file
// virtual Bool_t write(HDetector*) {return kTRUE;}
    Bool_t findContainer(const Text_t* name);
    Bool_t checkAllFound(Int_t*,Int_t);
    void writeHeader(const Text_t*, const Text_t* context="",
                     const Text_t* author="", const Text_t* description="");
    void writeComment(FairParSet*);
    void readComment(const Char_t*, FairParSet*);
//  Bool_t readLabPositions(const Text_t*,HDetGeomPar*,Int_t*,Int_t,Int_t);
//  Bool_t readVolumes(const Text_t*,HDetGeomPar*);
//  void readTransform(HGeomTransform&);
//  Bool_t readVolume(HGeomVolume*,HGeomShapes*,Text_t*);
//  void writeTransform(const HGeomTransform&);
//  void writeVolume(HGeomVolume*,HGeomShapes*);

  public:
    FairDetParAsciiFileIo(std::fstream* f);
    virtual ~FairDetParAsciiFileIo() {}
//  Bool_t read(HDetGeomPar*,Int_t*);
//  Int_t writeFile(HDetGeomPar*);

  private:

    FairDetParAsciiFileIo& operator=(const FairDetParAsciiFileIo&);
    FairDetParAsciiFileIo(const FairDetParAsciiFileIo&);

    ClassDef(FairDetParAsciiFileIo,0) // Class for detector parameter I/O from ascii file
};

#endif  /* !FAIRDETPARASCIIFILEIO_H */
