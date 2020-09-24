/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOCOMPOSITEVOLUME_H
#define FAIRGEOCOMPOSITEVOLUME_H

#include <Rtypes.h>         // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>     // for Int_t

#include "FairGeoVolume.h"  // for FairGeoVolume

class TObjArray;
class TBuffer;
class TClass;
class TMemberInspector;

/**
 * basic geometry of a volume with components
 * @author Ilse koenig
 */
class FairGeoCompositeVolume : public FairGeoVolume
{
  protected:
    TObjArray* components;   // array of components (type FairGeoVolume)

  public:
    FairGeoCompositeVolume(Int_t nComp = 0);
    ~FairGeoCompositeVolume();
    Int_t getNumComponents();
    FairGeoVolume* getComponent(const Int_t);
    void createComponents(const Int_t);
    void setComponent(FairGeoVolume*, const Int_t);
    void clear();
    void print();
    ClassDef(FairGeoCompositeVolume, 1);

  private:
    FairGeoCompositeVolume(const FairGeoCompositeVolume&);
    FairGeoCompositeVolume& operator=(const FairGeoCompositeVolume&);
};

#endif /* !FAIRGEOCOMPOSITEVOLUME_H */
