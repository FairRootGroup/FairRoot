/********************************************************************************
 * Copyright (C) 2020-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairXMLDetColor.h
 *
 *  Created on: 17 lip 2024
 *      Author: daniel
 */

#ifndef FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCOLOR_H_
#define FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCOLOR_H_

#include "FairXMLEveConf.h"
#include "FairXMLNode.h"

class TGeoNode;

class FairXMLDetectorColor : public FairXMLEveConf
{
  protected:
    FairXMLNode fNode;
    void ColorizeNode(TGeoNode* node, FairXMLNode* xml, Int_t depth) const;

  public:
    explicit FairXMLDetectorColor(FairXMLNode* node = nullptr);
    ~FairXMLDetectorColor() override = default;
    virtual void Colorize(TGeoNode* node);
};

#endif /* FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCOLOR_H_ */
