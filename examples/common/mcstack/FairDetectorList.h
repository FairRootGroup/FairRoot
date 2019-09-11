/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** Defines unique identifier for all detector systems **/

#ifndef FAIRDETECTORLIST_H
#define FAIRDETECTORLIST_H 1

// kSTOPHERE is needed for iteration over the enum. All detectors have to be put before.
enum DetectorId {kREF, kFairRutherford, kTutDet, kSTOPHERE, kTutGeane, kPixel};

#endif
