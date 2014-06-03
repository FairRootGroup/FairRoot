/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                  FairDetectorList header file                  -----
// -----                 Created 12/06/07  by V. Friese                -----
// -------------------------------------------------------------------------


/** Defines unique identifier for all FAIR detector systems **/

#ifndef FAIRDETECTORLIST_H
#define FAIRDETECTORLIST_H 1

// kSTOPHERE is needed for iteration over the enum. All detectors have to be put before.
enum DetectorId {kREF, kFairRutherford, kTutDet, kSTOPHERE};

#endif
