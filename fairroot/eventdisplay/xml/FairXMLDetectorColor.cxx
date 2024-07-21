/*
 * FairXMLDetColor.cxx
 *
 *  Created on: 17 lip 2024
 *      Author: daniel
 */

#include "FairXMLDetectorColor.h"

#include "FairXMLNode.h"

#include <RtypesCore.h>
#include <TAttFill.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TNamed.h>
#include <TString.h>

void FairXMLDetectorColor::ColorizeNode(TGeoNode* node, FairXMLNode* xml, Int_t depth) const
{
    TString name = xml->GetAttrib("name")->GetValue();
    TString node_name = node->GetName();
    Bool_t recursive = (xml->GetAttrib("recursive")->GetValue().Length() != 0 && !name.EqualTo(node_name));
    if (recursive && depth == 0)
        return;
    TString transparency = xml->GetAttrib("transparency")->GetValue();
    TString color = xml->GetAttrib("color")->GetValue();
    if (!color.EqualTo("")) {
        node->GetVolume()->SetFillColor(FairXMLEveConf::StringToColor(color));
        node->GetVolume()->SetLineColor(FairXMLEveConf::StringToColor(color));
    }
    if (!transparency.EqualTo("")) {
        node->GetVolume()->SetTransparency((Char_t)(transparency.Atoi()));
    }
    if (xml->GetAttrib("recursive")->GetValue().Length() > 0) {
        TString val = xml->GetAttrib("recursive")->GetValue();
        Int_t xml_depth = val.Atoi();
        if (recursive) {
            xml_depth = depth - 1;
        }
        for (int i = 0; i < node->GetNdaughters(); i++) {
            TGeoNode* daughter_node = node->GetDaughter(i);
            ColorizeNode(daughter_node, xml, xml_depth);
        }
    }
    if (xml->GetNChildren() > 0 && !recursive) {
        for (int i = 0; i < node->GetNdaughters(); i++) {
            TString subdetector_name = node->GetDaughter(i)->GetName();
            for (int j = 0; j < xml->GetNChildren(); j++) {
                FairXMLNode* subnode = xml->GetChild(j);
                TString subnode_name = subnode->GetAttrib("name")->GetValue();
                if (subnode_name == subdetector_name) {
                    ColorizeNode(node->GetDaughter(i), subnode, 0);
                }
            }
        }
    }
}

FairXMLDetectorColor::FairXMLDetectorColor(FairXMLNode* node)
{
    if (node)
        fNode = *node;
}

void FairXMLDetectorColor::Colorize(TGeoNode* node)
{
    if (!node)
        return;
    ColorizeNode(node, &fNode, 0);
}
