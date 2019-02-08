/*
 * FairXMLNode.cxx
 *
 *  Created on: 01-10-2013
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairXMLNode.h"
#include "TDOMParser.h"
#include "TXMLEngine.h"
#include <iostream>


FairXMLNode::FairXMLNode(TString name,TString value) : TNamed(name, value){
	fChildren = new TList();
	fChildren->SetOwner(kTRUE);
	fAttrib = new TList();
	fAttrib->SetOwner(kTRUE);
}

void FairXMLNode::Copy(TXMLNode* node){
	fChildren->Clear();
	fAttrib->Clear();
	SetName(node->GetNodeName());
	SetTitle(node->GetText());
	fChildren->SetOwner(kTRUE);
	fAttrib->SetOwner(kTRUE);
	if(node->HasChildren()){
		TXMLNode *child = node->GetChildren();
		do{
			if(child==NULL) break;
			TString name = child->GetNodeName();
			if(name!="text"){
				FairXMLNode *tempnode = new FairXMLNode();
				tempnode->Copy(child);
				fChildren->Add(tempnode);
			}
			if(child->HasNextNode())
				child=child->GetNextNode();
		}while(child->HasNextNode());

	}
	if(node->HasAttributes()){
		TList *atr_list = node->GetAttributes();
		for(int i=0;i<atr_list->GetEntries();i++){
			TXMLAttr *atrib = (TXMLAttr*)atr_list->At(i);
			fAttrib->Add(new FairXMLAttrib(atrib->GetName(),atrib->GetValue()));
		}
	}
}

FairXMLNode::FairXMLNode(const FairXMLNode& other):
		FairXMLNode(other.GetName(),other.GetValue()){
	for(int i=0;i<other.fChildren->GetEntries();i++){
		fChildren->Add(new FairXMLNode(*(FairXMLNode*)other.fChildren->At(i)));
	}

	for(int i=0;i<other.fAttrib->GetEntries();i++){
		fAttrib->Add(new FairXMLAttrib(*(FairXMLAttrib*)other.fAttrib->At(i)));
	}
}

TList* FairXMLNode::GetChildren() const {
	return fChildren;
}

FairXMLNode* FairXMLNode::GetChild(TString name, Int_t count) const{
	Int_t control_index = 0;
	for(int i=0;i<fChildren->GetEntries();i++){
		FairXMLNode *node = (FairXMLNode*)fChildren->At(i);
		TString temp = node->GetName();
		if(temp==name){
			control_index++;
		}
		if(control_index>count)
			return node;
	}
	return nullptr;
}


FairXMLAttrib* FairXMLNode::GetAttrib(TString name) const{
	Int_t control_index = 0;
	for(int i=0;i<fAttrib->GetEntries();i++){
		FairXMLAttrib *node = (FairXMLAttrib*)fAttrib->At(i);
		TString temp = node->GetName();
		if(temp==name){
			return node;
		}
	}
	return nullptr;
}

FairXMLNode* FairXMLNode::GetChild(Int_t index) const{
	if(index<fChildren->GetEntries()){
		return (FairXMLNode*)fChildren->At(index);
	}else{
		return nullptr;
	}
}

void FairXMLNode::AddAttrib(FairXMLAttrib* attrib) {
	TString new_atr = attrib->GetName();
	for(int i=0;i<GetNAttributes();i++){
		TString atr = GetAttrib(i)->GetName();
		if(atr.EqualTo(new_atr)){
			std::cout<<"FairXMLNode::AddAttrib Can't have two attributes with the same name!"<<std::endl;
			return;
		}
	}
	fAttrib->AddLast(attrib);
}

FairXMLAttrib* FairXMLNode::GetAttrib(Int_t index) const{
	if(index<fAttrib->GetEntries()){
		return (FairXMLAttrib*)fAttrib->At(index);
	}else{
		return nullptr;
	}
}

Int_t FairXMLNode::GetNChildren(TString name) const{
	Int_t counter =0;
	for(int i=0;i<GetNChildren();i++){
		TString name_temp = GetChild(i)->GetName();
		if(name_temp==name){
			counter++;
		}
	}
	return counter;
}

Int_t FairXMLNode::GetNAttributes(TString name) const{
	Int_t counter =0;
	for(int i=0;i<GetNAttributes();i++){
		TString attr_name = GetAttrib(i)->GetName();
		if(attr_name.EqualTo(name))
			counter++;
	}
	return counter;
}

FairXMLNode::~FairXMLNode() {
	delete fChildren;
	delete fAttrib;
}

FairXMLFile::FairXMLFile(TString name, TString mode) :fName(name){
	if(mode=="read"||mode=="READ"){
		fOverwrite  = kFALSE;
		TDOMParser *Parser = new TDOMParser();
		Parser->SetValidate(kFALSE);
		Parser->ParseFile(name);
		TXMLNode *MainNode = Parser->GetXMLDocument()->GetRootNode();
		fRootNode = new FairXMLNode();
		fRootNode->Copy(MainNode);
		delete Parser;
	}else{
		fOverwrite  = kTRUE;
		fRootNode = nullptr;
	}
}

void FairXMLFile::CreateRootNode(TString name) {
	if(fRootNode!=nullptr) delete fRootNode;
	fRootNode = new FairXMLNode(name);
}

void FairXMLFile::SetRootNode(FairXMLNode *node) {
	if(fRootNode!=nullptr) delete fRootNode;
	fRootNode = node;
}

void FairXMLFile::Close() {
	if(fOverwrite){
		if(fRootNode==nullptr){
			std::cout<<"FairXMLFile::Close() No root node!"<<std::endl;
			return;
		}
		TXMLEngine *engine = new TXMLEngine();
		XMLNodePointer_t mainnode = engine->NewChild(0, 0, fRootNode->GetName());
		ExportNode(mainnode,fRootNode,engine);
		XMLDocPointer_t xmldoc =  engine->NewDoc();
		engine->DocSetRootElement(xmldoc,mainnode);
		engine->SaveDoc(xmldoc,fName);
		engine->FreeDoc(xmldoc);
		delete engine;
		delete fRootNode;
		fRootNode = nullptr;
	}
}

void FairXMLFile::ExportNode(XMLNodePointer_t& nodePointer,
		FairXMLNode* node, TXMLEngine *engine) const {
	for(int i=0;i<node->GetNChildren();i++){
		XMLNodePointer_t child = engine->NewChild(nodePointer,0,node->GetChild(i)->GetName(),node->GetChild(i)->GetValue());
		for(int j=0;j<node->GetChild(i)->GetNAttributes();j++){
			engine->NewAttr(child,0,node->GetChild(i)->GetAttrib(j)->GetName(),node->GetChild(i)->GetAttrib(j)->GetValue());
		}
		ExportNode(child,node->GetChild(i),engine);
	}
}

FairXMLFile::~FairXMLFile() {
	if(fRootNode!=nullptr){
		if(fOverwrite)
			Close();
		else
			delete fRootNode;
	}
}
