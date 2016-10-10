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
#ifndef FAIRXMLNODE_H_
#define FAIRXMLNODE_H_

#include <TXMLNode.h>
#include <TObject.h>
#include <TList.h>
#include <TNamed.h>
#include <TXMLAttr.h>
#include "FairLogger.h"
#include "FairXMLAttrib.h"

class FairXMLNode : public TNamed{
public:
	/**
	 * create new node from ROOT node
	 * @param node node that wll be used to created this node
	 */
	FairXMLNode(TXMLNode *node );
	/**
	 * create new node
	 * @param name name of  node
	 * @param value value of node
	 */
	FairXMLNode(const char *name="node", const char *value="");
	/**
	 * set value of node
	 * @param value
	 */
	void SetValue(const char *value);
	/**
	 * aadd child to node
	 * @param node
	 */
	void AddChild(FairXMLNode *node);
	/**
	 * add attribute to node
	 * @param name name of attribute
	 * @param value value of attribute
	 */
	void AddAttrib(const char *name, const char *value);
	/**
	 * add atribute to node
	 * @param atrib
	 */
	void AddAttrib(FairXMLAttrib *atrib);
	/**
	 *
	 * @return mode of this node "import" for nodes that are from file"export" for nodes that will be written or "nul" if this node in null instance of this
	 * nodel
	 */
	const char* GetMode()const;
	/**
	 *
	 * @return true if this is "NULL" node
	 */
	Bool_t IsNull()const;
	/**
	 * create "NULL" node instance
	 * @return
	 */
	static FairXMLNode *NullInstance();
	/**
	 *
	 * @return number of sub-nodes
	 */
	Int_t GetNChildren()const;
	/**
	 *
	 * @return number of attributes
	 */
	Int_t GetNAttributes()const;
	/**
	 *
	 * @return value of node
	 */
	const char *GetValue() const;
	/**
	 * look for node with given name and retur it value
	 * @param name name of node
	 * @param index index of node (index-th node with name will be returned)
	 * @return
	 */
	const char *GetAttribValue(const char *name, Int_t index=0) const;
	/**
	 *
	 * @param index
	 * @return value of attribute with given index
	 */
	const char *GetAttribValue(Int_t index) const;
	/**
	 *
	 * @param index
	 * @return name of attribute with given index
	 */
	const char* GetAttribName(Int_t index) const;
	/**
	 *
	 * @return list with children
	 */
	TList *GetChildren() const;
	/**
	 *
	 * @param name name of node
	 * @param index index of node with given name (used to distinguish between nodes with the same name)
	 * @return
	 */
	FairXMLNode *GetChild(const char *name, Int_t index=0) const;
	/**
	 *
	 * @param index
	 * @return index-th node
	 */
	FairXMLNode *GetChild(Int_t index) const;
	virtual ~FairXMLNode();
private:
	enum EXMLMode{
		kModeImport,
		kModeExport,
		kModeNull
	};
	TList *fChildren;
	TList *fAttrib;
	TString  fValue;
	static FairXMLNode *fgNullInstance;
	EXMLMode fMode;
	ClassDef(FairXMLNode,1)
};

#endif /* FAIRXMLNODE_H_ */
