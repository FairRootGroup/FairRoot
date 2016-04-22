/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQEXAMPLE9TASKPROCESSORBIN_H_
#define FAIRMQEXAMPLE9TASKPROCESSORBIN_H_ 
#include <string>

#include "FairEventHeader.h"
#include "FairGeoParSet.h"
#include "FairParGenericSet.h"

#include "FairMQDevice.h"
#include "FairMQParts.h"

#include "TClonesArray.h"
#include "TList.h"
#include "TMessage.h"

#include "PixelPayload.h"
#include "PixelDigi.h"

template<typename T>
class FairMQEx9TaskProcessorBin : public FairMQDevice
{
  public:
    enum
    {
        Last
    };

    FairMQEx9TaskProcessorBin();
    virtual ~FairMQEx9TaskProcessorBin();

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

    TClonesArray*    fInputArray;
    TClonesArray*    fOutputArray;

    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;
    
};

// Template implementation is in FairMQEx9TaskProcessorBin.tpl :
#include "FairMQEx9TaskProcessorBin.tpl"

#endif /* FAIRMQEXAMPLE9TASKPROCESSOR_H_ */
