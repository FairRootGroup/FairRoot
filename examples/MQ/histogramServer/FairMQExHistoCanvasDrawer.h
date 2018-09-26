/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTOCANVASDRAWER
#define FAIRMQEXHISTOCANVASDRAWER

class THttpServer;
class TObjArray;

class FairMQExHistoCanvasDrawer
{
  public:
    FairMQExHistoCanvasDrawer() {}
    virtual ~FairMQExHistoCanvasDrawer() {}

    virtual void CreateCanvases(THttpServer&) = 0;

    virtual void DrawHistograms(TObjArray&) = 0;

  private:
    FairMQExHistoCanvasDrawer(const FairMQExHistoCanvasDrawer&);
    FairMQExHistoCanvasDrawer& operator=(const FairMQExHistoCanvasDrawer&);
};

#endif
