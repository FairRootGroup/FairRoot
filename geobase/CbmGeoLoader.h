/***************************************************************************
                          CbmGeoLoader.h  -  description
                             -------------------
    begin                : Thu Jun 17 2004
    copyright            : (C) 2004 by turany
    email                : m.al-turany@gsi.de
 ***************************************************************************/


#ifndef CbmGeoLOADER_H
#define CbmGeoLOADER_H

#include "TNamed.h"


class CbmGeoInterface;
class CbmGeoBuilder;
/**New Geometry Loader, this loader handel the Hades geometry description 
 * @author Ilse koenig
 * @author M. Al-Turany*/

class CbmGeoLoader : public TNamed  {
public: 
   CbmGeoLoader(const char *Name, const char *title);
   CbmGeoLoader();
   virtual ~CbmGeoLoader();
   CbmGeoInterface *getGeoInterface(){return fInterface;}
   CbmGeoBuilder   *getGeoBuilder(){return   fGeoBuilder; }
   /** static access method*/
   static CbmGeoLoader* Instance(); 

private: 
   CbmGeoLoader(const CbmGeoLoader &L);
   CbmGeoLoader& operator= (const CbmGeoLoader&) {return *this;}
   static CbmGeoLoader*	fgInstance;//!  /**Singleton instance*/
   CbmGeoInterface*		fInterface; //!  /** Hades Geometry Interface*/
   CbmGeoBuilder* 		fGeoBuilder; //!   /**Geometry builder*/
   ClassDef(CbmGeoLoader,1)

};   

#endif
