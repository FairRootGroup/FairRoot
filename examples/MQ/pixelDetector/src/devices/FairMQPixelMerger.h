/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelMerger.h
 *
 * @since 2016-03-21
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELMERGER_H_
#define FAIRMQPIXELMERGER_H_

#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts

#include <map>
#include <string>
#include <utility>   // pair

class PixelEventHeader;
class TObject;

typedef std::multimap<std::pair<std::pair<int, int>, int>, TObject*> MultiMapDef;

class FairMQPixelMerger : public fair::mq::Device
{
  public:
    FairMQPixelMerger();
    virtual ~FairMQPixelMerger();

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
    std::pair<std::pair<int, int>, int> fEvRIPartTrio;
    std::pair<MultiMapDef::iterator, MultiMapDef::iterator> fRet;

    int fNofReceivedMessages;
    int fNofSentMessages;

    int fNofParts;
    PixelEventHeader* fEventHeader;

    FairMQPixelMerger(const FairMQPixelMerger&);
    FairMQPixelMerger& operator=(const FairMQPixelMerger&);
};

#endif /* FAIRMQPIXELMERGER_H_ */
