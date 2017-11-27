/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyFieldCreator header file                  -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef MyFieldCreator_H
#define MyFieldCreator_H

#include "FairFieldFactory.h"

class MyFieldPar;

class FairField;

class MyFieldCreator : public FairFieldFactory 
{

 public:
  MyFieldCreator();
  virtual ~MyFieldCreator();
  virtual FairField* createFairField();
  virtual void SetParm();
  ClassDef(MyFieldCreator,1);
  
 protected:
  MyFieldPar* fFieldPar;
  
 private:
  MyFieldCreator(const MyFieldCreator&);
  MyFieldCreator& operator=(const MyFieldCreator&);

};
#endif //MyFieldCreator_H
