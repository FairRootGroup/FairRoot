/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQChunkMerger.h
 *
 * @since 2018-09-28
 * @author R. Karabowicz
 */

#ifndef FAIRMQCHUNKMERGER_H_
#define FAIRMQCHUNKMERGER_H_

#include "FairMQ.h"   // for fair::mq::Device

#include <map>
#include <string>
#include <utility>   // pair

class TObject;
class FairMCSplitEventHeader;

typedef std::multimap<std::pair<int, int>, std::pair<int, TObject*>> MultiMapDef;

class FairMQChunkMerger : public fair::mq::Device
{
  public:
    FairMQChunkMerger();
    virtual ~FairMQChunkMerger();

    void SetNofParts(int iparts) { fNofParts = iparts; }

  protected:
    bool MergeData(fair::mq::Parts&, int);
    virtual void Init();

  private:
    std::string fInputChannelName;
    std::string fOutputChannelName;

    std::map<std::pair<int, int>, int> fNofPartsPerEventMap;   // number of parts for pair<event number,run id>
    MultiMapDef fObjectMap;   // TObjects for given pair<pair<event number, run,id>part>

    std::pair<int, int> fEvRIPair;
    std::pair<int, TObject*> fEvCOPair;
    std::pair<MultiMapDef::iterator, MultiMapDef::iterator> fRet;

    int fNofReceivedMessages;
    int fNofSentMessages;

    int fNofParts;
    FairMCSplitEventHeader* fMCSplitEventHeader;

    FairMQChunkMerger(const FairMQChunkMerger&);
    FairMQChunkMerger& operator=(const FairMQChunkMerger&);
};

#endif /* FAIRMQCHUNKMERGER_H_ */
