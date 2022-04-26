/*
 * FairXMLNode.cxx
 *
 *  Created on: 01-10-2013
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairXMLNode.h"

#include <TDOMParser.h>
#include <TXMLAttr.h>       // for TXMLAttr
#include <TXMLDocument.h>   // for TXMLDocument
#include <TXMLNode.h>
#include <fairlogger/Logger.h>
#include <iostream>

FairXMLNode::FairXMLNode(TString name, TString value)
    : TNamed(name, value)
{
    fChildren.SetOwner(kTRUE);
    fAttrib.SetOwner(kTRUE);
}

FairXMLNode::FairXMLNode(const FairXMLNode& other)
    : FairXMLNode(other.GetName(), other.GetValue())
{
    for (int i = 0; i < other.fChildren.GetEntries(); i++) {
        fChildren.Add(new FairXMLNode(*other.GetChild(i)));
    }
    for (int i = 0; i < other.fAttrib.GetEntries(); i++) {
        fAttrib.Add(new FairXMLAttrib(*other.GetAttrib(i)));
    }
}

FairXMLNode& FairXMLNode::operator=(const FairXMLNode& other)
{
    if (&other == this)
        return *this;
    SetName(other.GetName());
    SetValue(other.GetValue());
    fChildren.Clear();
    fAttrib.Clear();
    for (int i = 0; i < other.fChildren.GetEntries(); i++) {
        fChildren.Add(new FairXMLNode(*other.GetChild(i)));
    }
    for (int i = 0; i < other.fAttrib.GetEntries(); i++) {
        fAttrib.Add(new FairXMLAttrib(*other.GetAttrib(i)));
    }
    return *this;
}

void FairXMLNode::Copy(TXMLNode* node)
{
    fChildren.Clear();
    fAttrib.Clear();
    SetName(node->GetNodeName());
    SetTitle(node->GetText());
    if (node->HasChildren()) {
        TXMLNode* child = node->GetChildren();
        do {
            if (child == nullptr)
                break;
            TString name = child->GetNodeName();
            if (name != "text") {   // skip "text" nodes
                FairXMLNode* tempnode = new FairXMLNode();
                tempnode->Copy(child);
                fChildren.Add(tempnode);
            }
            if (child->HasNextNode())
                child = child->GetNextNode();
        } while (child->HasNextNode());
    }
    if (node->HasAttributes()) {
        TList* atr_list = node->GetAttributes();
        for (int i = 0; i < atr_list->GetEntries(); i++) {
            TXMLAttr* atrib = (TXMLAttr*)atr_list->At(i);
            fAttrib.Add(new FairXMLAttrib(atrib->GetName(), atrib->GetValue()));
        }
    }
}

void FairXMLNode::AddAttrib(FairXMLAttrib* attrib)
{
    TString new_atr = attrib->GetName();
    if (GetAttrib(new_atr) != nullptr) {
        LOG(error) << "FairXMLNode::AddAttrib Can't have two attributes with the same name!";
        return;
    }
    fAttrib.AddLast(attrib);
}

Int_t FairXMLNode::GetNChildren(TString name) const
{
    Int_t counter = 0;
    for (int i = 0; i < GetNChildren(); i++) {
        TString name_temp = GetChild(i)->GetName();
        if (name_temp == name) {
            counter++;
        }
    }
    return counter;
}

FairXMLNode* FairXMLNode::GetChild(TString name, Int_t count) const
{
    Int_t control_index = 0;
    for (int i = 0; i < fChildren.GetEntries(); i++) {
        FairXMLNode* node = GetChild(i);
        TString temp = node->GetName();
        if (temp == name) {
            control_index++;
        }
        if (control_index > count)
            return node;
    }
    return nullptr;
}

FairXMLAttrib* FairXMLNode::GetAttrib(TString name) const
{
    return static_cast<FairXMLAttrib*>(fAttrib.FindObject(name));
}

FairXMLNode* FairXMLNode::GetChild(Int_t index) const { return static_cast<FairXMLNode*>(fChildren.At(index)); }

FairXMLAttrib* FairXMLNode::GetAttrib(Int_t index) const { return static_cast<FairXMLAttrib*>(fAttrib.At(index)); }

FairXMLNode::~FairXMLNode() {}

//---------- FairXMLFile ------------------------------------------------------------------------------------

FairXMLFile::FairXMLFile(TString name, TString mode)
    : fName(name)
{
    if (mode == "read" || mode == "READ") {
        fOverwrite = kFALSE;
        TDOMParser Parser;
        Parser.SetValidate(kFALSE);
        Parser.ParseFile(name);
        TXMLNode* MainNode = Parser.GetXMLDocument()->GetRootNode();
        fRootNode = std::make_unique<FairXMLNode>();
        fRootNode->Copy(MainNode);
    } else {
        fOverwrite = kTRUE;
    }
}

void FairXMLFile::CreateRootNode(TString name) { fRootNode = std::make_unique<FairXMLNode>(name); }

void FairXMLFile::SetRootNode(FairXMLNode* node) { fRootNode.reset(node); }

void FairXMLFile::Close()
{
    if (fOverwrite) {
        if (!fRootNode) {
            LOG(error) << "FairXMLFile::Close() No root node!";
            return;
        }
        TXMLEngine engine;
        XMLNodePointer_t mainnode = engine.NewChild(0, 0, fRootNode->GetName());
        ExportNode(mainnode, engine, *fRootNode.get());
        XMLDocPointer_t xmldoc = engine.NewDoc();
        engine.DocSetRootElement(xmldoc, mainnode);
        engine.SaveDoc(xmldoc, fName);
        engine.FreeDoc(xmldoc);
        fRootNode.reset(nullptr);
    }
}

void FairXMLFile::ExportNode(XMLNodePointer_t& nodePointer, TXMLEngine& engine, const FairXMLNode& node) const
{
    for (int i = 0; i < node.GetNChildren(); i++) {
        XMLNodePointer_t child =
            engine.NewChild(nodePointer, 0, node.GetChild(i)->GetName(), node.GetChild(i)->GetValue());
        for (int j = 0; j < node.GetChild(i)->GetNAttributes(); j++) {
            engine.NewAttr(
                child, 0, node.GetChild(i)->GetAttrib(j)->GetName(), node.GetChild(i)->GetAttrib(j)->GetValue());
        }
        ExportNode(child, engine, *node.GetChild(i));
    }
}

FairXMLFile::~FairXMLFile()
{
    if (fRootNode && fOverwrite)
        Close();
}
