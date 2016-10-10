/*
 * FairXMLParser.cxx
 *
 *  Created on: 7 paź 2016
 *      Author: Daniel Wielanek
 */
#include "FairXMLParser.h"

FairXMLParser::FairXMLParser():
	fFilename("data.xml"),
	fMainNode(NULL),
	fRootNode(kFALSE),
	fEngine(NULL){
}

FairXMLParser::FairXMLParser(const char* filename, const char* mode):
	fFilename(filename),
	fMainNode(NULL),
	fRootNode(kFALSE),
	fEngine(NULL){
	TString mode_read = "READ";
	if(mode_read.EqualTo(mode)){
		Import();
	}
}

FairXMLParser::~FairXMLParser() {
	if(fMainNode) delete fMainNode;
	if(fEngine) delete fEngine;
}

FairXMLNode* FairXMLParser::GetRootNode() const {
	if(fRootNode){
		return fMainNode;
	}else{
		return NULL;
	}
}

const char* FairXMLParser::GetRootNodeName() const {
	if(fRootNode){
		return fMainNode->GetName();
	}else{
		LOG(DEBUG1)<<"FairXMLParser: Lack of root node in file "<<fFilename<<FairLogger::endl;
		return "";
	}
}

void FairXMLParser::Save(const char *filename) {
	fFilename = filename;
	Export();
}

void FairXMLParser::CreateRootNode(const char* nodename) {
	if(fRootNode){
		LOG(DEBUG1)<<"FairXMLParser: Can't create node in "<<fFilename<<" because root node alreadyexist "<<FairLogger::endl;
	}else{
		fMainNode = new FairXMLNode(nodename,"");
		fRootNode = kTRUE;
	}
}

void FairXMLParser::AddToRootNode(FairXMLNode* node) {
	if(fRootNode){
		fMainNode->AddChild(node);
	}else{
		LOG(DEBUG1)<<"FairXMLParser: Lack of root node in file "<<fFilename<<FairLogger::endl;
	}
}

void FairXMLParser::Import() {
	TDOMParser *fParser;
	fParser = new TDOMParser();
	fParser->SetValidate(kFALSE);
	fParser->ParseFile(fFilename);
	TXMLNode *MainNode = fParser->GetXMLDocument()->GetRootNode();
	TString name = MainNode->GetNodeName();
	if(MainNode==NULL) {
		LOG(DEBUG1)<<"FairXMLParser: Lack of root node in file "<<fFilename<<FairLogger::endl;
	};
	fRootNode = kTRUE;
	fMainNode = new FairXMLNode(MainNode);
	delete fParser;
}

void FairXMLParser::Export() {
	if(fRootNode==kFALSE){
		LOG(DEBUG1)<<"FairXMLParser: Lack of root node in file "<<fFilename<<FairLogger::endl;
	}
	fEngine = new TXMLEngine();
	//create root node
	XMLNodePointer_t mainnode = fEngine->NewChild(0, 0, fMainNode->GetName(),fMainNode->GetValue());
	ExportNodeChildren(mainnode,fMainNode);

	XMLDocPointer_t xmldoc =  fEngine->NewDoc();
	fEngine->DocSetRootElement(xmldoc,mainnode);
	fEngine->SaveDoc(xmldoc,fFilename);
	fEngine->FreeDoc(xmldoc);
	delete fEngine;
	fEngine = NULL;
}

void FairXMLParser::ExportNodeChildren(XMLNodePointer_t nodePointer, FairXMLNode* node) {
	for(int i=0;i<node->GetNChildren();i++){
		XMLNodePointer_t child = fEngine->NewChild(nodePointer,0,node->GetChild(i)->GetName(),node->GetChild(i)->GetValue());
		for(int j=0;j<node->GetChild(i)->GetNAttributes();j++){
			fEngine->NewAttr(child,0,node->GetChild(i)->GetAttribName(j),node->GetChild(i)->GetAttribValue(j));
		}
		ExportNodeChildren(child,node->GetChild(i));
	}
}
