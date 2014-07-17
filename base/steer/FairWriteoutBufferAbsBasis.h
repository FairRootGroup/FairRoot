/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairWriteoutBufferAbsBasis.h
 *
 *  Created on: Jul 18, 2011
 *      Author: stockman
 */

#ifndef FAIRWRITEOUTBUFFERABSBASIS_H_
#define FAIRWRITEOUTBUFFERABSBASIS_H_

#include "TObject.h"

class FairWriteoutBufferAbsBasis : public TObject
{
  public:
    virtual ~FairWriteoutBufferAbsBasis() {};

    virtual void WriteOutData(double time) = 0;
    virtual void WriteOutAllData() = 0;

    ClassDef(FairWriteoutBufferAbsBasis,1)
};


#endif /* FAIRWRITEOUTBUFFERABSBASIS_H_ */
