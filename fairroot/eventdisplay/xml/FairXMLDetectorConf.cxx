/*
 * FairXMLDetectorConf.cxx
 *
 *  Created on: 21 paź 2021
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairXMLDetectorConf.h"

#include "FairXMLNode.h"

#include <FairLogger.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TNamed.h>

FairXMLDetectorConf::FairXMLDetectorConf(FairXMLNode* node)
{
    if (!node)
        return;
    if (TString(node->GetName()) == "detector") {
        SetGood();
    }
    if (!IsGood())
        return;
    if (node->GetAttrib("transparency")) {
        TString transparency = node->GetAttrib("transparency")->GetValue();
        fTransparency = (Char_t)(transparency.Atoi());
        fDefTransparency = kFALSE;
    }
    if (node->GetAttrib("name")) {
        fName = node->GetAttrib("name")->GetValue();
    }
    if (node->GetAttrib("color")) {
        TString col = node->GetAttrib("color")->GetValue();
        fColor = StringToColor(col);
        fDefColor = kFALSE;
    }
    if (node->GetAttrib("recursive")) {
        TString recu = node->GetAttrib("recursive")->GetValue();
        fRecursive = recu.Atoi();
    }
    for (int i = 0; i < node->GetNChildren(); i++) {
        FairXMLDetectorConf conf(node->GetChild(i));
        if (conf.IsGood()) {
            AddChild(conf);
        }
    }
}

void FairXMLDetectorConf::SetupSubNode(TGeoNode& node, Int_t depth) const
{
    if (depth < 0)
        return;
    ChangeNode(node);
    if (depth > 0) {
        for (int i = 0; i < node.GetNdaughters(); i++) {
            SetupSubNode(*node.GetDaughter(i), depth - 1);
        }
    }
}

void FairXMLDetectorConf::SetupNode(TGeoNode& node)
{
    TString nameNodeGeo = node.GetName();
    if (nameNodeGeo != GetDetectorName())
        return;
    if (fRecursive > 0) {
        SetupSubNode(node, fRecursive);
    } else {
        ChangeNode(node);
        for (int i = 0; i < node.GetNdaughters(); i++) {
            TGeoNode* dau = node.GetDaughter(i);
            TString name = dau->GetName();
            for (int j = 0; j < GetNChildren(); j++) {
                if (name == fChild[j].GetDetectorName()) {
                    fChild[j].SetupNode(*dau);
                    // node configured don't need anymore the daughter
                    fChild.erase(std::next(fChild.begin(), j--));
                    break;
                }
            }
        }
    }
}

void FairXMLDetectorConf::ChangeNode(TGeoNode& node) const
{
    if (!fDefTransparency)
        node.GetVolume()->SetTransparency(fTransparency);
    if (!fDefColor) {
        node.GetVolume()->SetFillColor(fColor);
        node.GetVolume()->SetLineColor(fColor);
    }
}
