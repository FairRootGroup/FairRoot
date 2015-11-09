/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiRingSorter.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiRingSorter_H_
#define FairTestDetectorDigiRingSorter_H_

#include <FairRingSorter.h> // for FairRingSorter

#include "Rtypes.h" // for ClassDef

class FairTimeStamp;

class FairTestDetectorDigiRingSorter : public FairRingSorter
{
  public:
    FairTestDetectorDigiRingSorter(int size = 100, double width = 10)
        : FairRingSorter(size, width) {};
    virtual ~FairTestDetectorDigiRingSorter();

    virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

    ClassDef(FairTestDetectorDigiRingSorter, 1);
};

#endif /* FairTestDetectorDigiRingSorter_H_ */
