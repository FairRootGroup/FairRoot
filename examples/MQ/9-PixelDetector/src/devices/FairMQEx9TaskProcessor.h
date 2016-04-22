/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQEXAMPLE9TASKPROCESSOR_H_
#define FAIRMQEXAMPLE9TASKPROCESSOR_H_

#include <string>

#include "FairEventHeader.h"
#include "FairGeoParSet.h"
#include "FairParGenericSet.h"

#include "FairMQDevice.h"
#include "FairMQParts.h"

#include "TClonesArray.h"
#include "TList.h"
#include "TMessage.h"

template<typename T>
class FairMQEx9TaskProcessor : public FairMQDevice
{
  public:
    enum
    {
        Last
    };

    FairMQEx9TaskProcessor();
    virtual ~FairMQEx9TaskProcessor();

    void SetProperty(const int key, const std::string& value);
    std::string GetProperty(const int key, const std::string& default_ = "");
    void SetProperty(const int key, const int value);
    int GetProperty(const int key, const int default_ = 0);

    void SetDataToKeep(std::string tStr) { fDataToKeep = tStr;}

  protected:
    virtual void Run();
    virtual void Init();

    void UpdateParameters();
    FairParGenericSet* UpdateParameter(FairParGenericSet* thisPar);

    static void CustomCleanup(void *data, void *hint);

    FairEventHeader* fEventHeader;
    TList*           fInput;
    TList*           fOutput;

    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;
    
};

// Template implementation is in FairMQEx9TaskProcessor.tpl :
#include "FairMQEx9TaskProcessor.tpl"

#endif /* FAIRMQEXAMPLE9TASKPROCESSOR_H_ */
