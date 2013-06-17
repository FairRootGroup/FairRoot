#ifndef FAIRDBSTREAMER_H
#define FAIRDBSTREAMER_H

#include "TObject.h"                    // for TObject
#include "TString.h"                    // for TObject
#include "Rtypes.h"                     // for UInt_t, Int_t, etc
#include <stddef.h>                     // for NULL
#include <cassert>                      // for assert
#include <string>                       // for string


#include "FairDb.h"


class FairDbStreamer : public TObject
{
  public:

    // Constructors and destructors.
    FairDbStreamer();
    FairDbStreamer(const TObject* obj,  FairDb::DataTypes type=FairDb::kBinary);
    FairDbStreamer(const Int_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const FairDbStreamer& from);
    FairDbStreamer& operator=(const FairDbStreamer&);
    virtual ~FairDbStreamer();

    // Meta-Data: String Encryption on Server Side
    const TString  AsString() const { return fString;};
    void SetString(TString aStr) { fString=aStr;}
    Int_t GetSize() {return fSize;}
    FairDb::DataTypes GetDataType() { return fType;}

    // Fill functions for arrays & objects
    void Fill(Int_t* arr);
    void Fill(TObject* obj);


  private:
    TString fString; //!
    Int_t   fSize; //!
    FairDb::DataTypes fType; //!

    ClassDef(FairDbStreamer,0)   // FairDbStreamer for a specific database table.

};


#endif  // FAIRDBSTREAMER_H
