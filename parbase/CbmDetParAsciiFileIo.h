#ifndef CBMDETPARASCIIFILEIO_H
#define CBMDETPARASCIIFILEIO_H


#include "CbmDetParIo.h"
//#include "TArrayI.h"

#include <fstream> 

class CbmParSet;

class CbmDetParAsciiFileIo : public CbmDetParIo {
protected:
  fstream* pFile;   //! pointer to ascii file
  TString fHeader;  //! header of container output in file
  TString sepLine;  //! comment line
public:
  CbmDetParAsciiFileIo(fstream* f);
  virtual ~CbmDetParAsciiFileIo() {}
//  Bool_t read(HDetGeomPar*,Int_t*);
//  Int_t writeFile(HDetGeomPar*);
protected:
  Bool_t findContainer(const Text_t* name);
  void writeHeader(const Text_t*, const Text_t* context="",
                   const Text_t* author="", const Text_t* description="");
  void writeComment(CbmParSet*);
  void readComment(const char*, CbmParSet*);
//  Bool_t readLabPositions(const Text_t*,HDetGeomPar*,Int_t*,Int_t,Int_t);
//  Bool_t readVolumes(const Text_t*,HDetGeomPar*);
//  void readTransform(HGeomTransform&);
//  Bool_t readVolume(HGeomVolume*,HGeomShapes*,Text_t*);
//  void writeTransform(const HGeomTransform&);
//  void writeVolume(HGeomVolume*,HGeomShapes*);
  ClassDef(CbmDetParAsciiFileIo,0) // Class for detector parameter I/O from ascii file
};

#endif  /* !CBMDETPARASCIIFILEIO_H */
