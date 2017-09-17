/*
 * FairXMLNode.cxx
 *
 *  Created on: 01-10-2013
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairXMLNode.h"

FairXMLNode::FairXMLNode(TXMLNode* node):
fChildren(NULL),
fAttrib(NULL),
fNChildren(0),
fNAttrib(0){
	//if(gNode == NULL) gNode = new FairXMLNode();
	fName = node->GetNodeName();
	fValue = node->GetText();
	if(node->HasChildren()){
		fChildren = new TList();
		TXMLNode *child = node->GetChildren();
		do{
			if(child==NULL) break;

			TString name = child->GetNodeName();
			if(name!="text"){
				FairXMLNode *tempnode = new FairXMLNode(child);
				fChildren->Add(tempnode);
				fNChildren++;
			}
			if(child->HasNextNode())
				child=child->GetNextNode();
		}while(child->HasNextNode());

	}
	if(node->HasAttributes()){
		TList *atr_list = node->GetAttributes();
		fAttrib = new TList();
		for(int i=0;i<atr_list->GetEntries();i++){
			TXMLAttr *atrib = (TXMLAttr*)atr_list->At(i);
			fAttrib->Add(new FairXMLAttrib(atrib->GetName(),atrib->GetValue()));
			fNAttrib++;
		}
	}
	fMode = kModeImport;
}

FairXMLNode::FairXMLNode(TString name,TString value) {
	fName = name;
	fValue = value;
	fChildren = NULL;
	fAttrib = NULL;
	fNChildren = 0;
	fNAttrib = 0;
	fMode = kModeExport;
}

void FairXMLNode::AddChild(FairXMLNode* node) {
	if(node == NULL){
		return;
	}
	if(fMode==kModeExport){
		if(fChildren==NULL) fChildren = new TList();
		fChildren->AddLast(node);
		fNChildren++;
	}
}

void FairXMLNode::AddAttrib(TString name, TString value) {
	if(fMode==kModeExport){
		if(fAttrib==NULL) fAttrib = new TList();
		for(int i=0;i<fAttrib->GetEntries();i++){
			TString temp =(( FairXMLAttrib*)fAttrib->At(i))->GetName();
		}
		fAttrib->Add(new FairXMLAttrib(name,value));
		fNAttrib++;
	}
}

Int_t FairXMLNode::GetNChildren() const {
	if(fMode == kModeNull){
		//FairCout::Error("dont call for null node");
		return 0;
	}
	return fNChildren;
}

Int_t FairXMLNode::GetNAttributes() const {
	if(fMode == kModeNull){
		//FairCout::Error("not for null node");
		return 0;
	}
	return fNAttrib;
}

TList* FairXMLNode::GetChildren() const {
	if(fMode == kModeNull){
		//FairCout::Error("no child in null node");
		return NULL;
	}
	return fChildren;
}

FairXMLNode * FairXMLNode::fgNullInstance = NULL;

FairXMLNode* FairXMLNode::GetChild(TString name, Int_t count) const{
	if(fMode == kModeNull){
		//FairCout::Error("no child in null node");
		return FairXMLNode::NullInstance();
	}
	if(fNChildren==0){
		//FairCout::Error("No children in this node");
		return FairXMLNode::NullInstance();
	}
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
	//FairCout::Error("No child found by name");
	return FairXMLNode::NullInstance();
}

FairXMLNode* FairXMLNode::GetChild(Int_t index) const{
	if(fMode == kModeNull){
		return FairXMLNode::NullInstance();
	}
	if(fNChildren>index){
		return (FairXMLNode*)fChildren->At(index);
	}else{
		return FairXMLNode::NullInstance();
	}
}

Bool_t FairXMLNode::IsImport() const{
	if(fMode==kModeImport) return kTRUE;
	return kFALSE;
}

Bool_t FairXMLNode::IsNull() const {
	if(fMode == kModeNull) return kTRUE;
	return kFALSE;
}

FairXMLNode* FairXMLNode::NullInstance() {
	if(fgNullInstance){
		return fgNullInstance;
	}
	fgNullInstance = new FairXMLNode();
	return fgNullInstance;
}

FairXMLNode::FairXMLNode() {
	fName = "null";
	fValue= "null";
	fChildren = NULL;
	fAttrib = NULL;
	fNChildren = 0;
	fNAttrib = 0;
	fMode = kModeNull;
}

void FairXMLNode::SetValue(TString value) {
	if(fMode==kModeExport){
		fValue = value;
	}
}

void FairXMLNode::SetName(TString name) {
	if(fMode==kModeExport){
		fName = name;
	}else{
	}
}

TString FairXMLNode::GetValue() const {
	if(fMode==kModeNull){
		return "";
	}
	return fValue;
}

const char* FairXMLNode::GetName() {
	if(fMode==kModeNull){
		return "";
	}
	return fName.Data();
}

Bool_t FairXMLNode::IsExport() const{
	if(fMode==kModeNull){
		return kTRUE;
	}
	return kFALSE;
}

TString FairXMLNode::GetAttribValue(TString name, Int_t index) const{
	if(fMode==kModeNull){
		return "";
	}
	if(fNAttrib==0){
		return "";
	}
	int counter =-1;
	for(int i=0;i<fAttrib->GetEntries();i++){
		FairXMLAttrib *atrib = (FairXMLAttrib*)fAttrib->At(i);
		TString title = atrib->GetName();
		if(title == name){
			counter++;
		}
		if(counter==index){
			return atrib->GetValue();
		}
	}
	return "";
}

TString FairXMLNode::GetAttribValue(Int_t index) const{
	if(index>=fNAttrib||fMode==kModeNull){
		return "";
	}else{
		return ((FairXMLAttrib*)fAttrib->At(index))->GetValue();
	}
}

TString FairXMLNode::GetAttribTitle(Int_t index) const{
	if(index>=fNAttrib||fMode==kModeNull){
		return "";
	}else{
		return ((FairXMLAttrib*)fAttrib->At(index))->GetName();
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
		if(GetAttribTitle(i)==name)
			counter++;
	}
	return counter;
}

FairXMLNode::~FairXMLNode() {
	if(fChildren){
		for(int i=0;i<fChildren->GetEntries();i++){
			fChildren->At(i)->Delete();
		}
		delete fChildren;
	}
	if(fAttrib){
		for(int i=0;i<fAttrib->GetEntries();i++){
			fAttrib->At(i)->Delete();
		}
		delete fAttrib;
	}

}

const char* FairXMLNode::GetTitle() const {
	if(fMode==kModeNull){
		return "";
	}
	return fName.Data();
}
