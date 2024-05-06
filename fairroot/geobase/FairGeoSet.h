/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOSET_H
#define FAIRGEOSET_H

#include "FairGeoNode.h"

#include <Rtypes.h>    // for Int_t, Bool_t, etc
#include <TList.h>     // for TList
#include <TNamed.h>    // for TNamed
#include <TString.h>   // for TString
#include <iosfwd>      // for fstream
#include <string>      // for std::string

// class FairGeoNode;
class FairGeoShapes;
class FairGeoMedia;
class FairGeoBuilder;
class FairGeoTransform;
class TArrayI;

/**
 * Base class for geometry of detector parts
 * @author Ilse koenig
 */
class FairGeoSet : public TNamed
{
  protected:
    Int_t hadesGeo{0};

    class FairGeoCopyNode : public TNamed
    {
      public:
        FairGeoNode* pNode;
        FairGeoCopyNode(const char* name, FairGeoNode* node)
            : TNamed(name, "")
            , pNode(node)
        {}
        //          SetName(name);
        //
        //        }
        ~FairGeoCopyNode() override = default;

      private:
        FairGeoCopyNode(const FairGeoCopyNode&);
        FairGeoCopyNode& operator=(const FairGeoCopyNode&);
    };

    TList* volumes{new TList()};     /** list of volumes */
    TList* masterNodes{nullptr};     /** pointer to list of mother volumes from other detector parts*/
    Int_t maxSectors{0};             /** maximum number of sectors (-1 for detectors outside any sector)*/
    Int_t maxKeepinVolumes{0};       /** maximum number of keepin volumes per sector*/
    Int_t maxModules{0};             /** maximum number of modules per sector*/
    TArrayI* modules{nullptr};       /** Module's array.*/
    FairGeoShapes* pShapes{nullptr}; /** pointer to the class FairGeoShapes*/
    TString geoFile{""};             /** name of geometry input file or Oracle*/
    TString author{""};              /** author of the media version*/
    TString description{""};         /** description of the version*/

    FairGeoSet() = default;
    void readInout(std::fstream&);
    void readTransform(std::fstream&, FairGeoTransform&);
    Bool_t readVolumeParams(std::fstream&, FairGeoMedia*, FairGeoNode*, TList* l = 0);
    Bool_t readKeepIn(std::fstream&, FairGeoMedia*, TString&);
    Bool_t readModule(std::fstream&, FairGeoMedia*, TString&, TString&, Bool_t a = kFALSE);

  public:
    ~FairGeoSet() override;
    void setShapes(FairGeoShapes* s) { pShapes = s; }
    void setMasterNodes(TList* m) { masterNodes = m; }
    void setGeomFile(const char* filename) { geoFile = filename; }
    const char* getGeomFile() { return geoFile.Data(); }
    Int_t getMaxSectors() { return maxSectors; }
    Int_t getMaxModules() { return maxModules; }
    void setMaxModules(Int_t _maxMods) { maxModules = _maxMods; }
    Int_t getMaxKeepinVolumes() { return maxKeepinVolumes; }
    void setModules(Int_t, Int_t*);
    Int_t* getModules();
    Int_t getModule(Int_t, Int_t);
    FairGeoNode* getVolume(const char* name) { return dynamic_cast<FairGeoNode*>(volumes->FindObject(name)); }
    FairGeoNode* getMasterNode(const char* name) { return dynamic_cast<FairGeoNode*>(masterNodes->FindObject(name)); }
    TList* getListOfVolumes() { return volumes; }
    FairGeoShapes* getShapes() { return pShapes; }
    void setAuthor(TString& s) { author = s; }
    void setDescription(TString& s) { description = s; }
    TString& getAuthor() { return author; }
    TString& getDescription() { return description; }
    virtual const char* getKeepinName(Int_t, Int_t) { return 0; }
    virtual const char* getModuleName(Int_t);
    virtual const char* getEleName(Int_t);
    virtual Int_t getSecNumInMod(const TString&) { return -1; }

    /** returns the module index in the modules array from the module name.
        The module number is counted starting at 1, so to get the array index
        one has to substract 1 from the module number.
    */
    virtual Int_t getModNumInMod(const TString& name);

    virtual Bool_t read(std::fstream&, FairGeoMedia*);
    virtual void addRefNodes() {}
    virtual void write(std::fstream&);
    virtual void print();
    virtual Bool_t create(FairGeoBuilder*);
    void compare(FairGeoSet&);
    ClassDefOverride(FairGeoSet, 0);   //

  private:
    FairGeoSet(const FairGeoSet&);
    FairGeoSet& operator=(const FairGeoSet&);

    std::string fModNameSet{""};   //! name of module
    std::string fEleNameSet{""};   //! substring for elements in module
};

#endif /* !FAIRGEOSET_H */
