/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairBaseTypes.h
 *
 *  Created on: May 16, 2023
 *      Author: R.Karabowicz
 */

#ifndef BASE_FAIRTYPES_H_
#define BASE_FAIRTYPES_H_

#include <Rtypes.h>

namespace fr {
    /// Alias name for event id type
    using EventID = UInt_t;

    /// Sentinel value for the event id, when none set
    static constexpr EventID NoEventID = std::numeric_limits<EventID>::max();
}

#endif   // BASE_FAIRTYPES_H_
