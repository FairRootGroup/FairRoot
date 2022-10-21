/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// $Id: FairLinkDef.h,v 1.4 2006/09/15 12:43:35 turany Exp $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class FairRunOnline;
#pragma link C++ class FairOnlineSource;
#pragma link C++ class FairUnpack;

#ifdef BUILD_MBS
#pragma link C++ class FairMbsSource;
#pragma link C++ class FairRemoteSource;
#pragma link C++ class FairMbsStreamSource;
#pragma link C++ class FairLmdSource;
#pragma link C++ class MRevBuffer;
#pragma link C++ class REvent;
#endif

#endif
