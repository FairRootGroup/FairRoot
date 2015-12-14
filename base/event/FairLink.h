/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairLink.h
 *
 *  Created on: Dec 23, 2009
 *      Author: stockman
 */

#ifndef FAIRLINK_H_
#define FAIRLINK_H_

#include "TObject.h"                    // for TObject

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Float_t, etc
#include "TString.h"                    // for TString

#include <iostream>                     // for ostream, cout

class FairLink : public TObject
{
  public:
    FairLink();
    FairLink(Int_t type, Int_t index, Float_t weight = 1.);
    FairLink(TString branchName, Int_t index, Float_t weight = 1.);
    FairLink(Int_t file, Int_t entry, Int_t type, Int_t index, Float_t weight = 1.);
    FairLink(Int_t file, Int_t entry, TString branchName, Int_t index, Float_t weight = 1.);
    virtual ~FairLink();

    void SetLink(Int_t file, Int_t entry, Int_t type, Int_t index, Float_t weight = 1.) {
      fFile = file;
      fEntry = entry;
      fType = type;
      fIndex = index;
      fWeight = weight;
    };
    void SetLink(Int_t type, Int_t index, Float_t weight = 1.) {
      fFile = -1;
      fEntry = -1;
      fType = type;
      fIndex = index;
      fWeight = weight;
    };
    Int_t GetFile() const {return fFile;}
    Int_t GetEntry() const {return fEntry;}
    Int_t GetType() const {return fType;}
    Int_t GetIndex() const {return fIndex;}
    Float_t GetWeight() const {return fWeight;}

    void SetWeight(Float_t weight) {fWeight = weight;}
    void AddWeight(Float_t weight) {fWeight += weight;}

    virtual void PrintLinkInfo(std::ostream& out = std::cout) const;

    virtual bool operator==(const FairLink& link) const {
      if ((fFile == link.GetFile() || link.GetFile() == -1) && (fEntry == link.GetEntry() || link.GetEntry() == -1) && fType == link.GetType() && fIndex == link.GetIndex()) {
        return true;
      } else {
        return false;
      }
    }

    virtual bool operator<(const FairLink& link) const {
	if (fFile != -1 && link.GetFile() != -1){
		if (fFile < link.GetFile()) 		return true;
		else if (link.GetFile() < fFile) 	return false;
	}
	if (fEntry != -1 && link.GetEntry() != -1){
		if(fEntry < link.GetEntry())		return true;
		else if (link.GetEntry() < fEntry)	return false;
	}
	if (fType < link.GetType())				return true;
	else if (link.GetType() < fType)		return false;
	if (fIndex < link.GetIndex())			return true;
	else if (link.GetIndex() < fIndex)		return false;

	return false;
//      if (fFile != -1 && fFile < link.GetFile()) {
//        return true;
//      } else if ((fFile == link.GetFile() || link.GetFile() == -1) && fEntry < link.GetEntry()) {
//        return true;
//      } else if ((fFile == link.GetFile() || link.GetFile() == -1)  && (fEntry == link.GetEntry() || link.GetEntry() == -1) && fType < link.GetType()) {
//        return true;
//      } else if ((fFile == link.GetFile() || link.GetFile() == -1)  && (fEntry == link.GetEntry() || link.GetEntry() == -1) && fType == link.GetType() && fIndex < link.GetIndex()) {
//        return true;
//      } else {
//        return false;
//      }
    }

    friend std::ostream& operator<< (std::ostream& out, const FairLink& link) {
      link.PrintLinkInfo(out);
      return out;
    }

    ClassDef(FairLink, 3);


  private:
    Int_t fFile;
    Int_t fEntry;
    Int_t fType;
    Int_t fIndex;
    Float_t fWeight;

};

#endif /* FAIRLINK_H_ */
