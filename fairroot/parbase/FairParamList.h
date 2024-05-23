/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARAMLIST_H
#define FAIRPARAMLIST_H

#include <Rtypes.h>           // for Text_t, Int_t, Bool_t, etc
#include <TArrayC.h>          // for TArrayC
#include <TFile.h>            // for TFile
#include <THashTable.h>       // for THashTable
#include <TNamed.h>           // for TNamed
#include <TObject.h>          // for TObject
#include <TROOT.h>            // for TROOT, gROOT
#include <TSeqCollection.h>   // for TSeqCollection
#include <TString.h>          // for TString

class TArrayD;
class TArrayF;
class TArrayI;

class FairParamObj : public TNamed
{
  protected:
    UChar_t* paramValue;      // Pointer to binary array
    Int_t arraySize;          // Size of binary array
    TString paramType;        // Type of parameter value or class name
    Bool_t basicType;         // kTRUE for C-types and C-type parameter arrays, kFALSE for classes
    Int_t bytesPerValue;      // number of bytes per value
    Int_t classVersion;       // Code version of classes stored as binary
    UChar_t* streamerInfo;    // Pointer to binary array container the streamer info
    Int_t streamerInfoSize;   // Size of streamer info array

  public:
    FairParamObj(const Text_t* name = "");
    FairParamObj(FairParamObj&);
    FairParamObj(const Text_t*, Int_t);
    FairParamObj(const Text_t*, Bool_t);
    FairParamObj(const Text_t*, UInt_t);
    FairParamObj(const Text_t*, Float_t);
    FairParamObj(const Text_t*, Double_t);
    FairParamObj(const Text_t*, const Int_t*, const Int_t);
    FairParamObj(const Text_t*, const UInt_t*, const Int_t);
    FairParamObj(const Text_t*, const Float_t*, const Int_t);
    FairParamObj(const Text_t*, const Double_t*, const Int_t);
    FairParamObj(const Text_t*, const Text_t*);
    FairParamObj(const Text_t*, const Char_t*, const Int_t);
    FairParamObj(const Text_t*, const UChar_t*, const Int_t);
    ~FairParamObj();
    void setParamType(const Text_t* t);
    UChar_t* setLength(Int_t l);
    void setParamValue(UChar_t*, const Int_t);
    void setClassVersion(const Int_t v) { classVersion = v; }
    UChar_t* setStreamerInfoSize(Int_t);
    void setStreamerInfo(UChar_t*, const Int_t);
    UChar_t* getParamValue() { return paramValue; }
    Bool_t isBasicType() { return basicType; }
    const char* getParamType() { return paramType.Data(); }
    Int_t getBytesPerValue() { return bytesPerValue; }
    Int_t getClassVersion() { return classVersion; }
    Int_t getLength() { return arraySize; }
    Int_t getNumParams();
    UChar_t* getStreamerInfo() { return streamerInfo; }
    Int_t getStreamerInfoSize() { return streamerInfoSize; }
    void print();

  protected:
    template<class type>
    void printData(type*, Int_t);

  private:
    FairParamObj& operator=(const FairParamObj&);

    // Class for binary parameter object (name + binary array)
    ClassDefOverride(FairParamObj, 0);
};

class FairParamList : public TObject
{
  protected:
    THashTable paramList;   // List for parameters stored as string
    class FairParamTFile : public TFile
    {
      public:
        FairParamTFile()
        {
            // Create StreamerInfo index
            Int_t lenIndex = gROOT->GetListOfStreamerInfo()->GetSize() + 1;
            if (lenIndex < 5000) {
                lenIndex = 5000;
            }
            fClassIndex = new TArrayC(lenIndex);
        }
        ~FairParamTFile()
        {
            delete fClassIndex;
            fClassIndex = 0;
        }
    };

  public:
    FairParamList();
    ~FairParamList();
    void add(FairParamObj&);
    void add(const Text_t*, const Text_t*);
    void add(const Text_t*, Int_t);
    void add(const Text_t*, Bool_t);
    void add(const Text_t*, UInt_t);
    void add(const Text_t*, Float_t);
    void add(const Text_t*, Double_t);
    void add(const Text_t*, TArrayI&);
    void add(const Text_t*, TArrayC&);
    void add(const Text_t*, TArrayF&);
    void add(const Text_t*, TArrayD&);
    void add(const Text_t*, const UChar_t*, const Int_t);
    void add(const Text_t*, const Int_t*, const Int_t);
    void add(const Text_t*, const Float_t*, const Int_t);
    void add(const Text_t*, const Double_t*, const Int_t);
    void addObject(const Text_t*, TObject*);
    Bool_t fill(const Text_t*, Text_t*, const Int_t);
    Bool_t fill(const Text_t*, Int_t*, const Int_t nValues = 1);
    Bool_t fill(const Text_t*, Bool_t*, const Int_t nValues = 1);
    Bool_t fill(const Text_t*, UInt_t*, const Int_t nValues = 1);
    Bool_t fill(const Text_t*, Float_t*, const Int_t nValues = 1);
    Bool_t fill(const Text_t*, Double_t*, const Int_t nValues = 1);
    Bool_t fill(const Text_t*, UChar_t*, const Int_t nValues = 1);
    Bool_t fill(const Text_t*, TArrayI*);
    Bool_t fill(const Text_t*, TArrayC*);
    Bool_t fill(const Text_t*, TArrayF*);
    Bool_t fill(const Text_t*, TArrayD*);
    Bool_t fillObject(const Text_t*, TObject*);
    void print();
    FairParamObj* find(const Text_t* name) { return static_cast<FairParamObj*>(paramList.FindObject(name)); }
    THashTable* getList() { return &paramList; }

  private:
    FairParamList(const FairParamList&);
    FairParamList& operator=(const FairParamList&);

    // Class for lists of parameters (of type FairParamObj)
    ClassDefOverride(FairParamList, 4);
};

#endif /* !FAIRPARAMLIST_H */
