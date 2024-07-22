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
    /**
     * applies setting to node with some cross-checks
     * @param node geo node
     * @param xml xml node
     * @param depth depth of node (used in recursion mode)
     */
    void ColorizeNode(TGeoNode& node, const FairXMLNode& xml, Int_t depth) const;
    /**
     * applies settings to node without any cross-checks
     * @param node
     * @param xml
     * @return recurency value, return 0 if recursive atribute has not been found
     */
    Int_t ApplyToNode(TGeoNode& node, const FairXMLNode& xml) const;

  public:
    explicit FairXMLDetectorColor(FairXMLNode* node = nullptr);
    ~FairXMLDetectorColor() override = default;
    virtual void Colorize(TGeoNode* node);
};

#endif /* FAIRROOT_EVENTDISPLAY_XML_FAIRXMLDETECTORCOLOR_H_ */
