/*
 * FairLink.h
 *
 *  Created on: Dec 23, 2009
 *      Author: stockman
 */

#ifndef FAIRLINK_H_
#define FAIRLINK_H_

#include "TObject.h"
#include "TString.h"

#include <utility>
#include <iostream>

class FairLink : public TObject{
public:
	FairLink();
	FairLink(Int_t type, Int_t index, Float_t weight = 1.);
	FairLink(TString branchName, Int_t index, Float_t weight = 1.);
	virtual ~FairLink();

	void SetLink(Int_t type, Int_t index, Float_t weight = 1.){fType = type; fIndex = index; fWeight = weight;}

	Int_t GetType() const {return fType;}
	Int_t GetIndex() const {return fIndex;}
	Float_t GetWeight() const {return fWeight;}

	void SetWeight(Float_t weight) {fWeight = weight;}
	void AddWeight(Float_t weight) {fWeight += weight;}

	virtual void Print(std::ostream& out = std::cout){out << *this;}

	bool operator==(const FairLink& link) const{
		if (fType == link.GetType() && fIndex == link.GetIndex())
			return true;
		else
			return false;
	}

	bool operator<(const FairLink& link) const{
		if(fType < link.GetType()){
			return true;
		}
		else if (fType == link.GetType() && fIndex < link.GetIndex()){
			return true;
		}
		else return false;
	}

	friend std::ostream& operator<< (std::ostream& out, FairLink& link){
		out << "(" << link.GetType() << "/" << link.GetIndex() << "/" << link.GetWeight() << ")";
		return out;
	}

    ClassDef(FairLink, 1);


private:
	Int_t fType;
	Int_t fIndex;
	Float_t fWeight;

	
};

#endif /* FAIRLINK_H_ */
