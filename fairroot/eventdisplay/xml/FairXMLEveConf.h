/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairXMLEveConf.h
 *
 *  Created on: 21 paź 2021
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRROOT_EVENTDISPLAY_XML_FAIRXMLEVECONF_H_
#define FAIRROOT_EVENTDISPLAY_XML_FAIRXMLEVECONF_H_

#include <TString.h>

class FairXMLEveConf

{
    bool fIsGood{false};

  protected:
    Int_t StringToColor(const TString& color) const;
    void SetGood() { fIsGood = kTRUE; }
    void SetBad() { fIsGood = kFALSE; }

  public:
    FairXMLEveConf() = default;
    bool IsGood() const { return fIsGood; }
    virtual ~FairXMLEveConf() = default;
    ClassDef(FairXMLEveConf, 1)
};

#endif /* FAIRROOT_EVENTDISPLAY_XML_FAIRXMLEVECONF_H_ */
