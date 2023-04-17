/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairXMLPdgColor.h
 *
 *  Created on: 21 paź 2021
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRROOT_EVENTDISPLAY_XML_FAIRXMLPDGCOLOR_H_
#define FAIRROOT_EVENTDISPLAY_XML_FAIRXMLPDGCOLOR_H_

#include "FairXMLEveConf.h"

#include <map>

class FairXMLNode;

class FairXMLPdgColor : public FairXMLEveConf
{
    std::map<int, int> fPDGToColor;
    void SetDefColor();

  public:
    explicit FairXMLPdgColor(FairXMLNode* node = nullptr);
    ~FairXMLPdgColor() override = default;
    void SetColor(Int_t pdg, Int_t color) { fPDGToColor[pdg] = color; }
    Int_t GetColor(Int_t pdg) const;
};

#endif /* FAIRROOT_EVENTDISPLAY_XML_FAIRXMLPDGCOLOR_H_ */
