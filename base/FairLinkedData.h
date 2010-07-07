/**
 * FairLinkedData.h
 *
 *  \date Dec 7, 2009
 *  \author T.Stockmanns
 *  \brief Abstract base class for all data classes. It provides get and set functions for accessing links to other data classes
 *  which are necessary to create the corresponding data
 *
 *  \section DESCRIPTION
 *
 *  Simulation processes typically take place in sequences: Simulation of events, generation of tracks and hits, simulation of
 *  detector response, reconstruction, analysis. In each step a data set is created. Each of the simulation steps depends on the
 *  last data set but should not depend on older sets. To provide the information which data was used to create the actual data a
 *  link is provided by this base class. A link consists of a type which indicates which data set was used and an index which
 *  indicates the specific data inside the data set which is needed.
 */

#ifndef FAIRLINKEDDATA_H_
#define FAIRLINKEDDATA_H_


#include "FairLink.h"

#include <TObject.h>
#include <set>
#include <utility>

class FairLinkedData : public TObject{
public:


	FairLinkedData();

	/**
	 * Constructor
	 * \param defaultType an Int_t which is used if no type argument is given in SetLink and Add Link
	 */
	FairLinkedData(Int_t defaultType):fDefaultType(defaultType){}
	virtual ~FairLinkedData();


	virtual std::set<FairLink> GetLinks() const = 0;
	virtual Int_t GetNLinks() const = 0;
	virtual FairLink GetLink(Int_t pos) const = 0;

	virtual Int_t GetDefaultType(){ return fDefaultType;}

	virtual void SetLink(FairLink link, Bool_t bypass = kFALSE, Float_t mult = 1.0) = 0;

	virtual void SetDefaultType(Int_t type){	fDefaultType = type;}

	virtual void AddLink(FairLink link, Bool_t bypass = kFALSE, Float_t mult = 1.0) = 0;

	virtual void DeleteLink(Int_t type, Int_t index) = 0;


	virtual bool IsLinkInList(Int_t type, Int_t index) = 0;
	virtual Int_t LinkPosInList(Int_t type, Int_t index) = 0;


private:
	Int_t fDefaultType;

	ClassDef(FairLinkedData,2);
};

/** \fn virtual std::vector<std::pair<Int_t, Int_t> > FairLinkedData::GetLinks()
 * Returns the list of all links stored
 * \return a vector of pair<Int_t, Int_t>
 */

/** \fn virtual Int_t FairLinkedData::GetNLinks()
 * Returns the number of links stored
 */

/** \fn virtual std::pair<Int_t, Int_t> FairLinkedData::GetLink(Int_t pos)
 * Get a specific link out of the vector of links
 * \param pos an Int_t indicating the position of link in the vector
 */

/** \fn virtual void FairLinkedData::SetLink(Int_t type, Int_t& index)
 * Sets a new link. Old links are deleted
 */

/** \fn virtual void FairLinkedData::AddLink(Int_t type, Int_t& index)
 * Adds a link at the end to the vector of links
 */

/** \fn virtual void FairLinkedData::DeleteLink(Int_t type, Int_t& index)
 * Deletes a given link out of the vector of links
 */

/** \fn virtual bool FairLinkedData::IsLinkInList(Int_t type, Int_t& index)
 * Checks if a link is in the vector of links
 * \return true or false
 */

/** \fn virtual Int_t FairLinkedData::LinkPosInList(Int_t type, Int_t& index)
 * Gives back the position of a link in the vector
 * \return position or -1 if link is not in the vector
 */
#endif /* FAIRLINKEDDATA_H_ */
