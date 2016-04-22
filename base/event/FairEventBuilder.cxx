/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* $Id: */

// -------------------------------------------------------------------------
// -----                    FairEventBuilder source file                -----
// -----                  Created 23/09/2013 by R. Karabowicz          -----
// -------------------------------------------------------------------------

/** FairEventBuilder
 *@author Radoslaw Karabowicz <r.karabowicz@gsi.de>
 *@since 23.09.2013
 *@version 1.0
 **
 ** FairRoot base task for the event buffers.
 ** The tasks may:
 ** 1. analyze data to reconstruct event times or other characteristics
 **    in the function TClonesArray* FindEvents(), that returns
 **    TClonesArray of FairRecoEvents
 ** 2. identify the data that could belong to event in the
 **    function and insert this identified data to the output TClonesArrays
 **    in the function StoreEventData(event)
 ** The implementations may be using any or both of the above functions.
 **/

#include "FairEventBuilder.h"

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "TClonesArray.h"

#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::fixed;
using std::right;
using std::left;
using std::setw;
using std::setprecision;
using std::set;
using std::map;

// -----   Default constructor   ------------------------------------------
FairEventBuilder::FairEventBuilder()
  : FairWriteoutBuffer(),
    fBuilderName                (""),
    fTimer                      (),
    fExecTime                   (0.),
    fIdentifier                 (0),
    fMaxAllowedEventCreationTime(0.)
{
}
// -------------------------------------------------------------------------


// -----   Constructor with name   -----------------------------------------
FairEventBuilder::FairEventBuilder(TString branchName, TString className, TString folderName, Bool_t persistance)
  : FairWriteoutBuffer(branchName,className,folderName,persistance),
    fBuilderName                (""),
    fTimer                      (),
    fExecTime                   (0.),
    fIdentifier                 (0),
    fMaxAllowedEventCreationTime(0.)
{
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairEventBuilder::~FairEventBuilder()
{
}
// -------------------------------------------------------------------------

void FairEventBuilder::WriteOutAllDeadTimeData()
{
  if ( fBranchName.Length() < 1 ) {
    return;
  }

  FairRootManager* ioman = FairRootManager::Instance();
  std::vector<FairTimeStamp*> data;
  if (fActivateBuffering) {
    if (fVerbose > 0) {
      std::cout << "-I- FairEventBuilder::WriteOutAllDeadTimeData" << std::endl;
    }
    data = GetAllData();
    if (fTreeSave && data.size() > 0) {
      TClonesArray* myArray = ioman->GetTClonesArray(fBranchName);
      if (!myArray) {
        std::cout << "-E- FairEventBuilder::WriteOutData " << fBranchName << " array is not available!" << std::endl;
      }
      if (fVerbose > 0) {
        std::cout << "-I- FairEventBuilder::WriteOutData size: " << data.size() << std::endl;
      }
      for (unsigned int i = 0; i < data.size(); i++) {
        AddNewDataToTClonesArray(data[i]);
        if (fVerbose > 1) {
          std::cout << i << " : ";
          data[i]->Print();
          std::cout << std::endl;
        }
        delete data[i];
      }
    }
  } else {
    ioman->GetTClonesArray(fBranchName);
  }
}
//_____________________________________________________________________________

// -----   Public method Finish   ------------------------------------------
void FairEventBuilder::Finish()
{

  cout << "-------------------- " << GetBuilderName() << " : Summary -----------------------" << endl;
  cout << " Should be implemented by the user" << endl;
  cout << "---------------------------------------------------------------------" << endl;
}
// -------------------------------------------------------------------------

ClassImp(FairEventBuilder)

