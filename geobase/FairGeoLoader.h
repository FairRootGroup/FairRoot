/***************************************************************************
                          FairGeoLoader.h  -  description
                             -------------------
    begin                : Thu Jun 17 2004
    copyright            : (C) 2004 by turany
    email                : m.al-turany@gsi.de
 ***************************************************************************/


#ifndef FairGeoLOADER_H
#define FairGeoLOADER_H

#include "TNamed.h"


class FairGeoInterface;
class FairGeoBuilder;
/**New Geometry Loader, this loader handel the Hades geometry description
 * @author Ilse koenig
 * @author M. Al-Turany*/

class FairGeoLoader : public TNamed
{
  public:
    FairGeoLoader(const char* Name, const char* title);
    FairGeoLoader();
    virtual ~FairGeoLoader();
    FairGeoInterface* getGeoInterface() {return fInterface;}
    FairGeoBuilder*   getGeoBuilder() {return   fGeoBuilder; }
    /** static access method*/
    static FairGeoLoader* Instance();

  private:
    FairGeoLoader(const FairGeoLoader&);
    FairGeoLoader& operator=(const FairGeoLoader&);
    static FairGeoLoader*  fgInstance;//!  /**Singleton instance*/
    FairGeoInterface*    fInterface; //!  /** Hades Geometry Interface*/
    FairGeoBuilder*    fGeoBuilder; //!   /**Geometry builder*/
    ClassDef(FairGeoLoader,1)

};

#endif
