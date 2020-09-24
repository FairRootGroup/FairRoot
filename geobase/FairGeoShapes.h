/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOSHAPES_H
#define FAIRGEOSHAPES_H

#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <TObject.h>     // for TObject
#include <TString.h>     // for TString
#include <RtypesCore.h>  // for Bool_t, Int_t
#include <iosfwd>        // for fstream

class FairGeoVolume;
class FairGeoBasicShape;
class TList;
class TBuffer;
class TClass;
class TMemberInspector;

/**
 * manager class for geometry shapes
 * @author Ilse koenig
 */
class FairGeoShapes : public TObject
{
  private:
    FairGeoShapes(const FairGeoShapes&);
    FairGeoShapes& operator=(const FairGeoShapes&);

  protected:
    TList* shapes;   // list of already created shape classes

  public:
    FairGeoShapes();
    ~FairGeoShapes();
    FairGeoBasicShape* selectShape(FairGeoVolume*);
    FairGeoBasicShape* selectShape(const TString&);
    Int_t readPoints(std::fstream*, FairGeoVolume*);
    Bool_t writePoints(std::fstream*, FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoShapes, 0);   //
};

#endif /* !FAIRGEOSHAPES_H */
