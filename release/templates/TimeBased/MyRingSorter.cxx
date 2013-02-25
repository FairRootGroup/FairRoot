/*
 * MyRingSorter.cxx
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#include <MyRingSorter.h>
#include "MyDataClass.h"

MyRingSorter::~MyRingSorter()
{
}

FairTimeStamp* MyRingSorter::CreateElement(FairTimeStamp* data)
{
  return new MyDataClass(*(MyDataClass*)data);
}

ClassImp(MyRingSorter);
