/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairXmlVMCConfig header file                    -----
// -----            Created 2022.10.04 by R. Karabowicz                -----
// -------------------------------------------------------------------------

#ifndef FAIR_XML_VMC_CONFIG_H
#define FAIR_XML_VMC_CONFIG_H

#include "FairGenericVMCConfig.h"
#include "FairLogger.h"
#include "TXMLEngine.h"

#include <string>

using namespace std;

class FairXmlVMCConfig : public FairGenericVMCConfig
{
  public:
    FairXmlVMCConfig();
    virtual ~FairXmlVMCConfig() {}

    virtual void Setup(const char* mcEngine);
    virtual void SetupPostInit(const char* mcEngine);

    virtual void UsePostInitConfig(bool useC = true, const char* stringC = "g4ConfigPostInit.xml")
    {
        fPostInitFlag = useC;
        fPostInitName = stringC;
    }

  private:
    string ObtainXmlFileName(const char* mcEngine);
    void StoreXmlInfo();

    string fMCEngine;

  protected:
    void SetupGeant3();
    void SetupGeant4();
    virtual void SetupStack() = 0;
    void SetCuts();

    TXMLEngine* fXmlEngine;
    XMLNodePointer_t fXmlConfig;

    XMLNodePointer_t fXmlConfigPostInit;

    XMLNodePointer_t GetPointer(string path, XMLNodePointer_t node, int verbose = 0);

    template<class T>
    T ConvertTo(XMLNodePointer_t xmlPointer);
    template<>
    string ConvertTo<string>(XMLNodePointer_t xmlPointer);
    template<>
    float ConvertTo<float>(XMLNodePointer_t xmlPointer);
    template<>
    bool ConvertTo<bool>(XMLNodePointer_t xmlPointer);

    template<class T>
    std::vector<T> ConvertToVector(XMLNodePointer_t xmlPointer)
    {
        std::vector<T> vect(0);
        XMLNodePointer_t child = fXmlEngine->GetChild(xmlPointer);
        while (child != 0) {
            vect.push_back(ConvertTo<T>(child));
            child = fXmlEngine->GetNext(child);
        }
        return vect;
    };
};

#endif
