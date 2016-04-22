/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9Merger.h
 *
 * @since 2016-03-21
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9MERGER_H_
#define FAIRMQEX9MERGER_H_

#include "TClonesArray.h"
#include "TFile.h"
#include "TFolder.h"
#include "TTree.h"
#include "FairEventHeader.h"

#include "FairMQDevice.h"

#include "PixelEventHeader.h"

class FairMQEx9Merger : public FairMQDevice
{
  public:
    FairMQEx9Merger();
    virtual ~FairMQEx9Merger();

    void SetNofParts(int iparts) { fNofParts = iparts; }

  protected:
    virtual void Init();
    virtual void Run();

 private:

    std::map     <std::pair<int,int>,int>                     fNofPartsPerEventMap;  // number of parts for pair<event number,run id>
    std::multimap<std::pair<std::pair<int,int>,int>,TObject*> fObjectMap;            // TObjects for given pair<pair<event number, run,id>part>
    
    int fNofParts;
    PixelEventHeader* fEventHeader;
};

#endif /* FAIRMQEX9MERGER_H_ */
