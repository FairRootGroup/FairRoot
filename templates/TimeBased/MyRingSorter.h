/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * MyRingSorter.h
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#ifndef MYRINGSORTER_H_
#define MYRINGSORTER_H_

#include <FairRingSorter.h>

class MyRingSorter: public FairRingSorter
{
  public:
    MyRingSorter(int size = 100, double width = 10)
      : FairRingSorter(size, width) {};

    virtual ~MyRingSorter();

    virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

    ClassDef (MyRingSorter,1);
};

#endif /* MYRINGSORTER_H_ */
