////////////////////////////////////////////////////////////////////////////
// Experiment
//
// Experiment defines Exp_t which is an enumeration of the
// legal detector configurations for an dedicated Experiment.
//
//
////////////////////////////////////////////////////////////////////////////

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif


namespace Experiment
{
typedef enum EExperiment {
  kUnknown      = 0x00,
  kS001         = 0x01,
  kS002         = 0x02,
  kS003         = 0x04,
  kS004         = 0x08,
  kS005         = 0x10,
  kS006         = 0x11
} Experiment_t;

// no ctor or dtor's - this class consists of only static members

Int_t       FullMask();

// Translation enum to/from character strings

const Char_t*          AsString(Experiment_t detector);
Experiment::Experiment_t   CharToEnum(Char_t c);
Char_t*                MaskToString(Int_t mask);
Experiment::Experiment_t   StringToEnum(const Char_t* chars, Int_t maxChar=0);
Int_t                  StringToMask(const Char_t* chars, Int_t maxChar=0);

}

namespace ExperimentType = Experiment;

#endif // EXPERIMENT_H
