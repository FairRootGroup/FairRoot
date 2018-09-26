/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTOCANVASDRAWEREXAMPLE
#define FAIRMQEXHISTOCANVASDRAWEREXAMPLE

#include "FairMQExHistoCanvasDrawer.h"

class TCanvas;

#include <memory>
#include <functional>

class FairMQExHistoCanvasDrawerExample : public FairMQExHistoCanvasDrawer
{
  public:
    FairMQExHistoCanvasDrawerExample();
    virtual ~FairMQExHistoCanvasDrawerExample();

    void CreateCanvases(THttpServer&);

    void DrawHistograms(TObjArray&);

  private:
    FairMQExHistoCanvasDrawerExample(const FairMQExHistoCanvasDrawerExample&);
    FairMQExHistoCanvasDrawerExample& operator=(const FairMQExHistoCanvasDrawerExample&);

    std::unique_ptr<TCanvas, std::function<void(TCanvas*)>> fCanvas;
};

#endif
