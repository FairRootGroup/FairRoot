/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCStage.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCOBJECT_H_
#define FAIRMCOBJECT_H_

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairLink.h"              // for FairLink
#include "FairMCEntry.h"           // for FairMCEntry
#include "FairMultiLinkedData.h"   // for FairMultiLinkedData

#include <Rtypes.h>    // for Int_t, FairMCObject::Class, etc
#include <TObject.h>   // for TObject
#include <iostream>    // for ostream, etc
#include <utility>     // for pair
#include <vector>      // for vector

class FairMCObject : public TObject
{
  public:
    FairMCObject();
    FairMCObject(Int_t type)
        : TObject()
        , fStage()
        , fStageId(type)
    {}
    FairMCObject(const FairMCObject& obj)
        : TObject(obj)
        , fStage(obj.GetEntryVector())
        , fStageId(obj.GetStageId())
    {}
    FairMCObject(Int_t type, std::vector<FairMCEntry> stage)
        : TObject()
        , fStage(stage)
        , fStageId(type)
    {}

    FairMCObject& operator=(const FairMCObject& from)
    {
        if (this == &from) {
            return *this;
        }

        TObject::operator=(from);
        fStage = from.fStage;
        fStageId = from.fStageId;

        return *this;
    }

    virtual ~FairMCObject();

    void SetStageId(Int_t type) { fStageId = type; }

    void SetEntry(std::vector<Int_t> type, std::vector<Int_t> link, int index);
    void SetEntry(FairMultiLinkedData* data, int index);
    void SetEntry(FairMCEntry link);

    void SetStage(std::vector<FairMCEntry> stage) { fStage = stage; }
    void SetLink(FairLink link, int index);
    void AddLink(FairLink link, int index);

    FairMCEntry GetEntry(int index) const { return fStage[index]; }
    FairLink GetSingleLink(int entryIndex, int linkIndex) const { return fStage.at(entryIndex).GetLink(linkIndex); }

    Int_t GetStageId(void) const { return fStageId; }

    FairMCEntry GetMCLink(Int_t index) { return fStage.at(index); }

    int GetNEntries() const { return fStage.size(); }
    int GetNLinks(int entryIndex) const { return fStage.at(entryIndex).GetNLinks(); }
    std::vector<FairMCEntry> GetEntryVector() const { return fStage; }

    FairMultiLinkedData PosInList(std::pair<int, int> link);
    FairMultiLinkedData PosInList(FairLink link);

    FairMultiLinkedData GetLinksWithType(Int_t type)
    {
        FairMultiLinkedData result;
        for (int i = 0; i < GetNEntries(); i++) {
            result.AddLinks(GetMCLink(i).GetLinksWithType(type));
        }
        return result;
    }

    void RemoveType(Int_t type);

    virtual void ClearEntries() { fStage.clear(); }

    virtual void PrintInfo(std::ostream& out = std::cout) { out << *this; }

    /*
        void operator=(const FairMCObject& obj) {
          fStageId = obj.GetStageId();
          fStage = obj.GetEntryVector();
        }
    */

    friend std::ostream& operator<<(std::ostream& out, const FairMCObject& obj)
    {
        std::vector<FairMCEntry> stages = obj.GetEntryVector();
        for (unsigned int i = 0; i < stages.size(); i++) {
            if (stages[i].GetNLinks() > 0) {
                out << i << ": ";
                stages[i].PrintInfo(out);
                out << std::endl;
            }
        }
        return out;
    }

  private:
    void AdoptSize(int index);
    std::vector<FairMCEntry> fStage;
    Int_t fStageId;

    ClassDef(FairMCObject, 0);
};

#endif /* FAIRMCOBJECT_H_ */
