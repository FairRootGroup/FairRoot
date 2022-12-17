/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTOCANVASDRAWEREXAMPLE
#define FAIRMQEXHISTOCANVASDRAWEREXAMPLE

#include "FairMQExHistoCanvasDrawer.h"

class TCanvas;

#include <functional>
#include <memory>

class FairMQExHistoCanvasDrawerExample : public FairMQExHistoCanvasDrawer
{
  public:
    FairMQExHistoCanvasDrawerExample();
    ~FairMQExHistoCanvasDrawerExample() override;

    void CreateCanvases(THttpServer&) override;

    void DrawHistograms(TObjArray&) override;

  private:
    FairMQExHistoCanvasDrawerExample(const FairMQExHistoCanvasDrawerExample&);
    FairMQExHistoCanvasDrawerExample& operator=(const FairMQExHistoCanvasDrawerExample&);

    std::unique_ptr<TCanvas, std::function<void(TCanvas*)>> fCanvas;
};

#endif
