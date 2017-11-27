/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                  MyProjDetectorList header file               -----
// -----                  M. Al-Turany   June 2014                     -----
// -------------------------------------------------------------------------


/** Defines unique identifier for all MyProj detectors system **/
/** THis is needed for stack filtring **/

#ifndef MyProjDetectorList_H
#define MyProjDetectorList_H 1
// kSTOPHERE is needed for iteration over the enum. All detectors have to be put before.
enum DetectorId {kNewDetector, kSTOPHERE};

#endif
