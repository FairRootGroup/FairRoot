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
#ifndef FAIRXMLPARSER_H_
#define FAIRXMLPARSER_H_
#include <TXMLEngine.h>
#include <TDOMParser.h>
#include "FairXMLNode.h"
#include "FairLogger.h"
/**
 * simplified version of interface for ROOT XML interface
 */
class FairXMLParser : public TObject{
public:
	/**
	 * deafult constructor , create file "data.xml" if Save() will be called
	 */
	FairXMLParser();
	/**
	 * main constructor
	 * @param filename name of file to open/save
	 * @param mode mode of parser "READ" to read file, "NEW" to create new file
	 */
	FairXMLParser(const char*  filename, const char *mode="READ");
	/**
	 * save nodes from memory into file
	 * @param filname name of file to export
	 */
	void Save(const char *filename="data.xml");
	/**
	 * create root node
	 * @param nodename name of root node
	 */
	void CreateRootNode(const char * nodename);
	/**
	 *
	 * @return pointer to root node
	 */
	FairXMLNode *GetRootNode() const;
	/**
	 *
	 * @return root node name
	 */
	const char* GetRootNodeName() const;
	/**
	 * add node to root node
	 * @param node node to add
	 */
	void AddToRootNode(FairXMLNode *node);
	virtual ~FairXMLParser();

private:
	enum {
		kImporter,
		kExporter
	};
	void Import();
	void Export();
	TString fFilename;
	FairXMLNode *fMainNode;
	Bool_t fRootNode;
	TXMLEngine *fEngine;
	void ExportNodeChildren(XMLNodePointer_t nodePointer, FairXMLNode *node);
	ClassDef(FairXMLParser,1)
};

#endif /* FAIRXMLPARSER_H_ */
