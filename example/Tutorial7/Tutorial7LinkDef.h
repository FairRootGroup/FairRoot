/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/////////////////////////////// Tutorial 7 LinkDef ///////////////////////////////

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class MyDigi+;
#pragma link C++ class MyHit+;

#pragma link C++ namespace MyPodData;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class MyPodData::TimeStamp+;
#pragma link C++ class MyPodData::Digi+;
#pragma link C++ class MyPodData::Hit+;

#endif
