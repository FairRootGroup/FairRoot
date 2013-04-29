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
