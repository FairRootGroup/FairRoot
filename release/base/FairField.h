// -------------------------------------------------------------------------
// -----                      FairField header file                     -----
// -----                Created 06/01/04  by M. Al-Turany              -----
// -----                Redesign 13/02/06  by V. Friese                -----
// -----                Redesign 04/08/06  by M. Al-Turany               -----
// -------------------------------------------------------------------------


/** FairField.h
 ** @author M.Al-Turany <m.al/turany@gsi.de>
 ** @author V.Friese <v.friese@gsi.de>
 ** @since 06.01.2004
 ** @version1.0
 **
 ** Abstract base class for magnetic fields in FAIR
 ** Concrete field should implement the pure virtual methods
 ** GetBx, GetBy and GetBz and/or  GetBxyz
 **
 ** Note: Field values should be returned in kG (thanks to GEANT3)
 **/

#include "FairLogger.h"


#ifndef FAIRFIELD_H
#define FAIRFIELD_H 1
#include "RVersion.h"


//#ifndef ROOT_TVirtualMagField
//#include "TVirtualMagField.h"
//#endif

#if ROOT_VERSION_CODE < 333824

#ifndef ROOT_TVirtualMagField
#define ROOT_TVirtualMagField
// copied from ROOT for backward compatibility with ROOT versions before 5.24
#include "TNamed.h"

class TVirtualMagField : public TNamed
{
  public:
    TVirtualMagField()                 : TNamed() {}
    TVirtualMagField(const char* name) : TNamed(name,"") {}
    virtual ~TVirtualMagField() {}
    virtual void Field(const Double_t* x, Double_t* B) = 0;
    ClassDef(TVirtualMagField, 1)              // Abstract base field class
};
ClassImp(TVirtualMagField)
#endif


#else

#include "TVirtualMagField.h"

#endif


#include <iostream>

class FairField : public TVirtualMagField
{

  public:

    /** Default constructor **/
    FairField();


    /** Constructor with name and title **/
    FairField(const char* name, const char* title = "FAIR Magnetic Field");

    FairField& operator=(const FairField&) {return *this;}

    /** Destructor **/
    virtual ~FairField();


    /** Intialisation. E.g. read in the field map. If needed, to be
     ** implemented in the concrete class.
     **/
    virtual void Init() { };

    /** Test whether field type is Constant **/
    Bool_t IsConst();


    /** Test whether field typ is Map **/
    Bool_t IsMap();


    /** Field type ( 0=constant, 1=map, 2=map sym2, 3 = map sym3 ) **/
    Int_t GetType() const { return fType; }


    /** Get x component of magnetic field [kG]
     ** @param x,y,z    Position [cm]
     **/
    virtual Double_t GetBx(Double_t x, Double_t y, Double_t z) {std::cout << "GetBx Should be implimented" << std::endl; return 0;}


    /** Get y component of magnetic field [kG]
     ** @param x,y,z    Position [cm]
     **/
    virtual Double_t GetBy(Double_t x, Double_t y, Double_t z) {std::cout << "GetBy Should be implimented" << std::endl; return 0;}


    /** Get z component of magnetic field [kG]
     ** @param x,y,z    Position [cm]
     **/
    virtual Double_t GetBz(Double_t x, Double_t y, Double_t z) {std::cout << "GetBz Should be implimented" << std::endl; return 0;}


    /** Get magnetic field. For use of GEANT3
     ** @param point            Coordinates [cm]
     ** @param bField (return)  Field components [kG]
     **/
    virtual void GetFieldValue(const Double_t point[3], Double_t* bField);


    void Field(const Double_t point[3], Double_t* B) {GetFieldValue(point,B);}


    /** Screen output. To be implemented in the concrete class. **/
    virtual void  Print(Option_t* option = "") const {;}
    virtual void GetBxyz(const Double_t point[3], Double_t* bField) { std::cout << "GetBz Should be implimented" << std::endl;};



    /**Fill Paramater*/

    virtual void FillParContainer() {printf("This should implimented in the exp. part \n");}
  protected:

    /** Field type. 1 = constant field, 2 = field map. **/
    Int_t fType;

    /** Fair Logger */
    FairLogger*            fLogger;//!

  private:
    FairField(const FairField&);
    //    FairField& operator=(const FairField&);
    //TODO: Check why the htrack needs this
    ClassDef(FairField,3);

};




#endif
