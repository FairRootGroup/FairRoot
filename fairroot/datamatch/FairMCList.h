/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCList.h
 *
 *  Created on: Dec 3, 2009
 *      Author: stockman
 */

#ifndef FAIRMCLIST_H_
#define FAIRMCLIST_H_

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include <Rtypes.h>    // for Int_t, FairMCList::Class, etc
#include <TObject.h>   // for TObject
#include <vector>      // for vector

class FairMCList : public TObject
{
  public:
    FairMCList();
    FairMCList(Int_t type, Int_t entry)
        : TObject()
        , fList()
        , fEntry(entry)
        , fType(type)
    {}

    FairMCList(Int_t type, Int_t entry, std::vector<Int_t> list)
        : TObject()
        , fList(list)
        , fEntry(entry)
        , fType(type)
    {}

    virtual ~FairMCList();

    void SetType(Int_t type) { fType = type; }
    void SetEntry(Int_t entry) { fEntry = entry; }
    void AddElement(Int_t element) { fList.push_back(element); }

    Int_t GetType() const { return fType; }
    Int_t GetEntry() const { return fEntry; }
    Int_t GetNElements() const { return fList.size(); }
    Int_t GetElement(Int_t index) const { return fList.at(index); }
    std::vector<Int_t> GetElements() const { return fList; }

    void Reset() { fList.clear(); }

  private:
    std::vector<Int_t> fList;
    Int_t fEntry;
    Int_t fType;

    ClassDef(FairMCList, 1);
};

#endif /* FAIRMCLIST_H_ */
