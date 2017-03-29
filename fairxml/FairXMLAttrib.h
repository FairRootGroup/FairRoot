/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairXMLParser.h
 *
 *  Created on: 7 paź 2016
 *      Author: Daniel Wielanek
 */
#ifndef FAIRXMLATTRIB_H_
#define FAIRXMLATTRIB_H_
#include <TObject.h>
#include <TNamed.h>
/**
 * class for representation of node attribute
 */
class FairXMLAttrib : public TNamed{
public:
	/**
	 * defualut constructor
	 */
	FairXMLAttrib();
	/**
	 * constructor
	 * @param name name of attribute
	 * @param value value of attribute
	 */
	FairXMLAttrib(const char* name, const char *value="");
	/**
	 *
	 * @return value of atrribute
	 */
	const char*  GetValue() const{ return fValue.Data();};
	/**
	 * set value of atrribute
	 * @param value
	 */
	void SetValue(const char *value){ fValue = value;};
	virtual ~FairXMLAttrib();
private:
	TString fValue;
	ClassDef(FairXMLAttrib,1)
};

#endif /* FAIRXMLATTRIB_H_ */
