/*
 * FairXMLNode.cxx
 *
 *  Created on: 7 paź 2016
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairXMLNode.h"

FairXMLNode * FairXMLNode::fgNullInstance = NULL;

FairXMLNode::FairXMLNode(TXMLNode* node) :
	fChildren(NULL),
	fAttrib(NULL),
	fMode(kModeImport)
	{
	SetName(node->GetNodeName());
	fValue = node->GetText();
	if(node->HasChildren()){
		fChildren = new TList();
		fChildren->SetOwner();
		TXMLNode *child = node->GetChildren();
		do{
			if(child==NULL) break;

			TString name = child->GetNodeName();
			if(child->GetNodeType()==TXMLNode::kXMLElementNode){
				FairXMLNode *tempnode = new FairXMLNode(child);
				fChildren->AddLast(tempnode);
			}
			if(child->HasNextNode())
				child=child->GetNextNode();
		}while(child->HasNextNode());

	}
	if(node->HasAttributes()){
		TList *atr_list = node->GetAttributes();
		fAttrib = new TList();
		fAttrib->SetOwner();
		for(int i=0;i<atr_list->GetEntries();i++){
			TXMLAttr *atrib = (TXMLAttr*)atr_list->At(i);
			fAttrib->AddLast(new FairXMLAttrib(atrib->GetName(),atrib->GetValue()));
		}
	}
}

FairXMLNode::FairXMLNode(const char* name, const char* value) :
	fChildren(NULL),
	fAttrib(NULL),
	fValue(value),
	fMode(kModeExport){
	SetName(name);
}

void FairXMLNode::SetValue(const char* value) {
	fValue = value;
}

void FairXMLNode::AddChild(FairXMLNode* node) {
	if(node == NULL){
		LOG(DEBUG2) << "FairXMLNode: Cant add empty node to "<< GetName()<< " xml node"<<FairLogger::endl;
		return;
	}
	if(node==this){
		LOG(DEBUG2) << "FairXMLNode: Cannot add  xml node"<< GetName()<< "to itself"<<FairLogger::endl;
	}
	if(fMode==kModeExport){
		if(fChildren==NULL) fChildren = new TList();
		fChildren->AddLast(node);
	}else{
		LOG(DEBUG2) << "FairXMLNode: Cannot add  to node"<< GetName()<< "this node is not in \"export\" mode"<<FairLogger::endl;
	}
}

void FairXMLNode::AddAttrib(const char* name, const char* value) {
	AddAttrib(new FairXMLAttrib(name,value));
}

void FairXMLNode::AddAttrib(FairXMLAttrib* atrib) {
	if(fMode==kModeExport){
		if(fAttrib==NULL) fAttrib = new TList();
		for(int i=0;i<fAttrib->GetEntries();i++){
			TString temp =(( FairXMLAttrib*)fAttrib->At(i))->GetName();
			if(temp.EqualTo(atrib->GetName())){
				LOG(DEBUG2) << "FairXMLNode: Adding nodes with the same name"<<FairLogger::endl;
			}
		}
		fAttrib->AddLast(atrib);
	}else{
		LOG(DEBUG2) << "FairXMLNode: Cannot add  to node"<< GetName()<< "this node is not in \"export\" mode"<<FairLogger::endl;
	}
}

FairXMLNode* FairXMLNode::NullInstance() {
	if(fgNullInstance){
		return fgNullInstance;
	}
	fgNullInstance = new FairXMLNode();
	return fgNullInstance;
}

Int_t FairXMLNode::GetNChildren() const {
	if(fChildren) return fChildren->GetEntries();
	return 0;
}

Int_t FairXMLNode::GetNAttributes() const {
	if(fAttrib) return fAttrib->GetEntries();
	return 0;
}

Bool_t FairXMLNode::IsNull() const {
	if(fMode==kModeNull) return kTRUE;
	return kFALSE;
}

const char* FairXMLNode::GetMode() const {
	switch(fMode){
	case kModeExport:
		return "export";
		break;
	case kModeImport:
		return "import";
		break;
	default:
		return "null";
		break;
	}
}

const char* FairXMLNode::GetValue() const {
	return fValue.Data();
}

const char* FairXMLNode::GetAttribValue(const char* name, Int_t index) const {
	if(fMode==kModeNull){
		LOG(DEBUG2) << "FairXMLNode: Node is null, can'tt get attribute "<<name<<FairLogger::endl;
		return "";
	}
	if(GetNAttributes()==0){
		LOG(DEBUG2) << "FairXMLNode: Node  "<<name<<" doesn't contain attributes"<<FairLogger::endl;
		return "";
	}
	int counter =-1;
	for(int i=0;i<fAttrib->GetEntries();i++){
		FairXMLAttrib *atrib = (FairXMLAttrib*)fAttrib->At(i);
		TString title = atrib->GetName();
		if(title.EqualTo(name)){
			counter++;
		}
		if(counter==index){
			return atrib->GetValue();
		}
	}
	return "";
}

const char* FairXMLNode::GetAttribValue(Int_t index) const {
	if(index>=GetNAttributes()||fMode==kModeNull){
		return "";
	}else{
		return ((FairXMLAttrib*)fAttrib->At(index))->GetValue();
	}
}

const char* FairXMLNode::GetAttribName(Int_t index) const {
	if(index>=GetNAttributes()||fMode==kModeNull){
		return "";
	}else{
		return ((FairXMLAttrib*)fAttrib->At(index))->GetName();
	}
}

TList* FairXMLNode::GetChildren() const {
	return fChildren;
}

FairXMLNode* FairXMLNode::GetChild(const char* name, Int_t index) const {
	if(fMode == kModeNull){
		LOG(DEBUG2) << "FairXMLNode: Node is null, can'tt get child "<<FairLogger::endl;
		return FairXMLNode::NullInstance();
	}
	if(GetNChildren()==0){
		LOG(DEBUG2) << "FairXMLNode: Node  "<<this->GetName()<<"doens;t contain child"<<FairLogger::endl;
		return FairXMLNode::NullInstance();
	}
	Int_t control_index = 0;
	for(int i=0;i<fChildren->GetEntries();i++){
		FairXMLNode *node = (FairXMLNode*)fChildren->At(i);
		TString temp = node->GetName();
		if(temp==name){
			control_index++;
		}
		if(control_index>index)
			return node;
	}
	LOG(DEBUG2) << "FairXMLNode: Couldn't find  "<<name<<" in " <<this->GetName()<<FairLogger::endl;
	return FairXMLNode::NullInstance();
}

FairXMLNode* FairXMLNode::GetChild(Int_t index) const {
	if(fMode == kModeNull){
		LOG(DEBUG2) << "FairXMLNode: Node is null, can'tt get child "<<FairLogger::endl;
		return FairXMLNode::NullInstance();
	}
	if(GetNChildren()>index){
		return (FairXMLNode*)fChildren->At(index);
	}else{
		LOG(DEBUG2) <<"FairXMLNode: No child at such index in node"<<this->GetName()<<FairLogger::endl;
		return FairXMLNode::NullInstance();
	}
}

FairXMLNode::~FairXMLNode() {
	if(fChildren) delete fChildren;
	if(fAttrib) delete fAttrib;
}

