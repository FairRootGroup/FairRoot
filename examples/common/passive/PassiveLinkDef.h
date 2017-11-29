/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// $Id: PassiveLinkDef.h,v 1.1.1.1 2005/06/23 07:14:26 dbertini Exp $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class  FairMagnet+;
#pragma link C++ class  FairTarget+;
#pragma link C++ class  FairPipe+;
#pragma link C++ class  FairCave+;

#pragma link C++ class FairGeoCave;
#pragma link C++ class FairGeoPipe;
#pragma link C++ class FairGeoTarget;
#pragma link C++ class FairGeoMagnet;
#pragma link C++ class FairGeoPassivePar;
#pragma link C++ class FairPassiveContFact;

#endif

