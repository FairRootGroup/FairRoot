/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRDBDATATYPEUNION
#define FAIRDBDATATYPEUNION

#include "DataType.h"                    // for DataType_t

#include "Rtypes.h"

#include <iosfwd>                       // for ostream
#include <list>                         // for list
#include <map>                          // for map, map<>::mapped_type, etc

class FairRegistry;


class FairDbDataTypeUnion
{
  public:

    typedef std::list<DataType::DataType_t>           SimList_t;
    typedef std::map<DataType::DataType_t,SimList_t > SimMap_t;

    FairDbDataTypeUnion();
    virtual ~FairDbDataTypeUnion();

    SimList_t Get(const DataType::DataType_t value)const;
    void Print(std::ostream& s)const;
    void Show();

    static const FairDbDataTypeUnion& Instance();

    void Clear() { fUnions.clear(); }
    void Set(const DataType::DataType_t value, SimList_t list) {
      fUnions[value] = list;
    }
    void Set(FairRegistry& reg);

  private:

    static const FairDbDataTypeUnion* fgInstance;


    SimMap_t fUnions;

    ClassDef(FairDbDataTypeUnion,0)  // DataType types Assoc.

};

std::ostream& operator<<(std::ostream& s, const FairDbDataTypeUnion& dataFlagAss);

#endif // FAIRDBDATATYPEUNION
