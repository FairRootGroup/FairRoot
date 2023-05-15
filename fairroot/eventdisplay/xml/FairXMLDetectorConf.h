/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairXMLDetectorConf.h
 *
 *  Created on: 21 paź 2021
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCONF_H_
#define FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCONF_H_

#include "FairXMLEveConf.h"

#include <TString.h>
#include <vector>

class TGeoNode;
class FairXMLNode;

class FairXMLDetectorConf : public FairXMLEveConf
{
    std::vector<FairXMLDetectorConf> fChild;
    TString fName{""};
    Int_t fRecursive{0};
    Color_t fColor{kWhite};
    Char_t fTransparency{'0'};
    Bool_t fDefColor{kTRUE};
    Bool_t fDefTransparency{kTRUE};
    void ChangeNode(TGeoNode& node) const;
    void SetupSubNode(TGeoNode& node, Int_t depth) const;

  public:
    FairXMLDetectorConf(FairXMLNode* node = nullptr);
    void SetupNode(TGeoNode& node);
    void AddChild(FairXMLDetectorConf& set) { fChild.push_back(set); };
    Int_t GetNChildren() const { return fChild.size(); }
    TString GetDetectorName() const { return fName; }
    const FairXMLDetectorConf& GetChild(Int_t n) const { return fChild[n]; };
    virtual ~FairXMLDetectorConf(){};
    ClassDefOverride(FairXMLDetectorConf, 1);
};

#endif /* FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCONF_H_ */
