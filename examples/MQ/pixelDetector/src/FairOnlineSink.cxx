/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairOnlineSink.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairOnlineSink.h"

#include "FairMQRunDevice.h"

#include <FairMQLogger.h>

FairOnlineSink::FairOnlineSink()
  : fMQRunDevice(nullptr)
{}

void  FairOnlineSink::Fill()
{
  /// Fill the Root tree.
  LOG(debug) << "called FairOnlineSink::Fill()!!!!";

  if (fMQRunDevice) {
    fMQRunDevice->SendBranches();
  }
}
