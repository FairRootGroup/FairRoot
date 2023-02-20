/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Last modified : 28/01/2009 by Ilse Koenig

#include "FairParamList.h"

#include "FairLogger.h"   // for FairLogger, MESSAGE_ORIGIN

#include <TArrayD.h>         // for TArrayD
#include <TArrayF.h>         // for TArrayF
#include <TArrayI.h>         // for TArrayI
#include <TBuffer.h>         // for TBuffer, etc
#include <TBufferFile.h>     // for TBufferFile
#include <TClass.h>          // for TClass
#include <TCollection.h>     // for TIter
#include <TDirectory.h>      // for TDirectory::TContext
#include <TStreamerInfo.h>   // for TStreamerInfo
#include <iostream>          // for operator<<, ostream, cout, etc
#include <string.h>          // for memcpy, strcmp, strlen

//_HADES_CLASS_DESCRIPTION
/////////////////////////////////////////////////////////////////////////////////////////
//
//  FairParamObj
//
//  Class for parameters stored in binary format in Oracle and used as list
//  elements in FairParamList::paramList.
//
//  The overloaded constructors and fill-functions accept single values or arrays of type
//    UChar_t, Int_t, Float_t, Double_t, char_t, Text_t.
//  The arguments for arrays are
//      the name of the parameter
//      the pointer to the array
//      the length of the array
//  The data are automatically converted to an UChar_t array.
//  For classes also the class version is stored, for ROOT classes also the TStreamerInfo.
//
//  -------------------------------------------------------------------------------------
//
//  FairParamList
//
//  Class for the generic Oracle and ASCII interface for parameter containers
//  derived from HParCond
//
//  The class contains a list to stores objects of type FairParamObj
//  The list objects store the name, the value, the parameter type and some
//  additional information depending for the object type.
//
//  All add/addObject functions add an initialized parameter to the list for
//  writing. The functions create a new list element and copy the data into
//  this object.
//  Add functions:
//    1. accepted basic types: Int_t, Float_t, Double_t, UChar_t
//    2. accepted ROOT arrays: TArrayI, TArrayF, TArrayD, TArrayC
//    3. accepted string: Text_t*
//       This can be any text, for example also numbers in hexadecimal or
//       scientific format. The number of characters must be specified (default 1).
//  AddObject function:
//    Accepts classes derived from TObject.
//    The persistent data elements are streamed into an UChar_t array using the
//    class streamer. For ROOT classes, for example histograms, the ROOT streamer
//    info is stored in an additional binary array.
//
//  All fill/fillObject functions convert the data in the list element back
//  to the type of the parameter and copies them into the data element in the
//  initialization process.
//    1. Single parameters of basic type:
//       The functions return kFALSE, if the parameter is not in the list.
//    2. Arrays:
//      a) If the array size is specified (return code Bool_t), the functions return
//         kFALSE, if the number of data elements in the list objects is not the same.
//      b) If the array size is not specified (return code Int_t), the array is
//         recreated with the size of the number of data elements in the list object.
//         The functions return the number of data elements or 0, if the parameter
//         was not found.
//    3. Classes:
//       The class version is checked and a warning printed, if it is not identical
//       with the current version (typically class version of list object higher than
//       version in the actual parameter container). The class streamer takes care
//       for backward compatibility. A warning is printed, if the ROOT version is
//       different from the current version.
//       The function returns the number of bytes in the list object or 0, if the
//       parameter was not found in the list.
//
//////////////////////////////////////////////////////////////////////////////////////

ClassImp(FairParamObj);
ClassImp(FairParamList);

FairParamObj::FairParamObj(const Text_t* name)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(0)
    , paramType("UChar_t")
    , basicType(kFALSE)
    , bytesPerValue(1)
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{}

FairParamObj::FairParamObj(FairParamObj& o)
    : TNamed(o)
    , paramValue(nullptr)
    , arraySize(o.arraySize)
    , paramType(o.paramType)
    , basicType(o.basicType)
    , bytesPerValue(o.bytesPerValue)
    , classVersion(o.classVersion)
    , streamerInfo(nullptr)
    , streamerInfoSize(o.streamerInfoSize)
{
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, o.getParamValue(), arraySize);
    if (streamerInfoSize > 0) {
        streamerInfo = new UChar_t[streamerInfoSize];
        memcpy(streamerInfo, o.getStreamerInfo(), streamerInfoSize);
    }
}

FairParamObj::FairParamObj(const Text_t* name, Int_t value)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Int_t))
    , paramType("Int_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Int_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for a Int_t value
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, &value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, Bool_t value)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Bool_t))
    , paramType("Bool_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Bool_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for a Int_t value
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, &value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, UInt_t value)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(UInt_t))
    , paramType("UInt_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(UInt_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for a Int_t value
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, &value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, Float_t value)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Float_t))
    , paramType("Float_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Float_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for a Float_t value
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, &value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, Double_t value)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Double_t))
    , paramType("Double_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Double_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for a Double_t value
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, &value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const Int_t* value, const Int_t nValues)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Int_t) * nValues)
    , paramType("Int_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Int_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for an array with nValues elements of type Int_t
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const UInt_t* value, const Int_t nValues)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(UInt_t) * nValues)
    , paramType("UInt_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(UInt_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for an array with nValues elements of type UInt_t
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const Float_t* value, const Int_t nValues)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Float_t) * nValues)
    , paramType("Float_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Float_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for an array with nValues elements of type Float_t
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const Double_t* value, const Int_t nValues)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Double_t) * nValues)
    , paramType("Double_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Double_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for an array with nValues elements of type Double_t
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const Text_t* value)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(strlen(value))
    , paramType("Text_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Char_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for a string value
    paramValue = new UChar_t[arraySize + 1];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const Char_t* value, const Int_t nValues)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(Char_t) * nValues)
    , paramType("Char_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(Char_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    // Constructor for an array with nValues elements of type Char_t
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::FairParamObj(const Text_t* name, const UChar_t* value, const Int_t nValues)
    : TNamed(name, "")
    , paramValue(nullptr)
    , arraySize(sizeof(UChar_t) * nValues)
    , paramType("UChar_t")
    , basicType(kTRUE)
    , bytesPerValue(sizeof(UChar_t))
    , classVersion(-1)
    , streamerInfo(nullptr)
    , streamerInfoSize(0)
{
    paramValue = new UChar_t[arraySize];
    memcpy(paramValue, value, arraySize);
}

FairParamObj::~FairParamObj()
{
    // Destructor
    delete[] paramValue;
    paramValue = 0;
    delete[] streamerInfo;
    streamerInfo = 0;
}

void FairParamObj::setParamType(const Text_t* t)
{
    // Sets the parameter type. Accepted type names are:
    //     UChar_t (default)
    //     Char_t
    //     Int_t
    //     Float_t
    //     Double_t
    //     Text_t
    //     class name
    paramType = t;
    if (strcmp(t, "Char_t") == 0) {
        basicType = kTRUE;
        bytesPerValue = sizeof(Char_t);
    } else if (strcmp(t, "Int_t") == 0) {
        basicType = kTRUE;
        bytesPerValue = sizeof(Int_t);
    } else if (strcmp(t, "Float_t") == 0) {
        basicType = kTRUE;
        bytesPerValue = sizeof(Float_t);
    } else if (strcmp(t, "Double_t") == 0) {
        basicType = kTRUE;
        bytesPerValue = sizeof(Double_t);
    } else if (strcmp(t, "Text_t") == 0) {
        basicType = kTRUE;
        bytesPerValue = sizeof(Char_t);
    } else {
        basicType = kFALSE;
        bytesPerValue = 1;
    }
    if (basicType) {
        classVersion = -1;
        streamerInfoSize = 0;
        streamerInfo = 0;
    }
}

UChar_t* FairParamObj::setLength(Int_t l)
{
    // Sets the length of the binary array
    delete[] paramValue;
    arraySize = l;
    if (l > 0) {
        paramValue = new UChar_t[arraySize];
    } else {
        paramValue = 0;
    }
    return paramValue;
}

void FairParamObj::setParamValue(UChar_t* value, const Int_t length)
{
    // Sets the parameter value (the array is not copied!)
    delete[] paramValue;
    arraySize = length;
    paramValue = value;
}

UChar_t* FairParamObj::setStreamerInfoSize(Int_t l)
{
    // Sets the length of the streamer info
    delete[] streamerInfo;
    streamerInfoSize = l;
    if (l > 0) {
        streamerInfo = new UChar_t[streamerInfoSize];
    } else {
        streamerInfo = 0;
    }
    return streamerInfo;
}

void FairParamObj::setStreamerInfo(UChar_t* array, const Int_t length)
{
    // Sets the streamer info of ROOT classes (the array is not copied!)
    delete[] streamerInfo;
    streamerInfoSize = length;
    streamerInfo = array;
}

Int_t FairParamObj::getNumParams()
{
    // Returns the number of values in the array, respectively 1 for classes and strings
    Int_t n = 1;
    if (basicType) {
        n = arraySize / bytesPerValue;
    }
    return n;
}

void FairParamObj::print()
{
    // Prints the name and type of the parameters, respectively class name and version.
    // Prints also the numbers for an array of type Int_t, Float_t, Double_t.
    std::cout << GetName() << ": ";
    if (classVersion >= 0) {
        std::cout << "\n  Class Type:    " << paramType.Data() << "\n  Class Version: " << classVersion << std::endl;
    } else if (strcmp(paramType, "Text_t") == 0) {
        TString val(reinterpret_cast<Char_t*>(paramValue), arraySize);
        val.ReplaceAll("\n", "\n  ");
        std::cout << paramType << "\n  " << val.Data() << std::endl;
    } else {
        Int_t nParams = getNumParams();
        if (nParams == 1) {
            std::cout << paramType << "   ";
        } else {
            std::cout << paramType << " array, nValues: " << nParams << "\n  ";
        }
        if (strcmp(paramType, "Char_t") == 0) {
            Char_t* val = reinterpret_cast<Char_t*>(paramValue);
            printData(val, nParams);
        } else if (strcmp(paramType, "Int_t") == 0) {
            Int_t* val = reinterpret_cast<Int_t*>(paramValue);
            printData(val, nParams);
        } else if (strcmp(paramType, "Float_t") == 0) {
            Float_t* val = reinterpret_cast<Float_t*>(paramValue);
            printData(val, nParams);
        } else if (strcmp(paramType, "Double_t") == 0) {
            Double_t* val = reinterpret_cast<Double_t*>(paramValue);
            printData(val, nParams);
        } else {
            std::cout << "Type: " << paramType << "  Array  length: " << arraySize << std::endl;
        }
    }
}

template<class type>
void FairParamObj::printData(type* val, Int_t nParams)
{
    Int_t i = 0, k = 0;
    while (k < nParams) {
        if (i == 10) {
            std::cout << "\n  ";
            i = 0;
        }
        std::cout << val[k] << " ";
        i++;
        k++;
        if (k > 50) {
            std::cout << "...";
            break;
        }
    }
    std::cout << std::endl;
}

//-----------------------------------------------------------------------------------

FairParamList::FairParamList()
    : TObject()
{}

FairParamList::~FairParamList()
{
    // Destructor
}

void FairParamList::add(FairParamObj& p)
{
    // Adds a FairParamObj object to the list
    paramList.Add(new FairParamObj(p));
}

void FairParamList::add(const Text_t* name, const Text_t* value)
{
    // Adds a string parameter to the list
    // name  = name of the parameter
    // value = string value
    paramList.Add(new FairParamObj(name, value));
}

void FairParamList::add(const Text_t* name, const Int_t value)
{
    // Adds a parameter of type Int_t to the list
    paramList.Add(new FairParamObj(name, value));
}

void FairParamList::add(const Text_t* name, const Bool_t value)
{
    // Adds a parameter of type Int_t to the list
    paramList.Add(new FairParamObj(name, value));
}

void FairParamList::add(const Text_t* name, const UInt_t value)
{
    // Adds a parameter of type UInt_t to the list
    paramList.Add(new FairParamObj(name, value));
}

void FairParamList::add(const Text_t* name, const Float_t value)
{
    // Adds a parameter of type Float_t to the list
    paramList.Add(new FairParamObj(name, value));
}

void FairParamList::add(const Text_t* name, const Double_t value)
{
    // Adds a parameter of type Double_t to the list
    paramList.Add(new FairParamObj(name, value));
}

void FairParamList::add(const Text_t* name, TArrayI& value)
{
    // Adds a parameter of type TArrayI to the list
    paramList.Add(new FairParamObj(name, value.GetArray(), value.GetSize()));
}

void FairParamList::add(const Text_t* name, TArrayC& value)
{
    // Adds a parameter of type TArrayC  to the list
    paramList.Add(new FairParamObj(name, value.GetArray(), value.GetSize()));
}

void FairParamList::add(const Text_t* name, TArrayF& value)
{
    // Adds a parameter of type TArrayF to the list
    paramList.Add(new FairParamObj(name, value.GetArray(), value.GetSize()));
}

void FairParamList::add(const Text_t* name, TArrayD& value)
{
    // Adds a parameter of type TArrayD to the list
    paramList.Add(new FairParamObj(name, value.GetArray(), value.GetSize()));
}

void FairParamList::add(const Text_t* name, const UChar_t* values, const Int_t nValues)
{
    // Adds a binary array of size nValues to the list
    paramList.Add(new FairParamObj(name, values, nValues));
}

void FairParamList::add(const Text_t* name, const Int_t* values, const Int_t nValues)
{
    // Adds an array of type Int_t and of size nValues as binary to the list
    paramList.Add(new FairParamObj(name, values, nValues));
}

void FairParamList::add(const Text_t* name, const Float_t* values, const Int_t nValues)
{
    // Adds an array of type Float_t and of size nValues as binary to the list
    paramList.Add(new FairParamObj(name, values, nValues));
}

void FairParamList::add(const Text_t* name, const Double_t* values, const Int_t nValues)
{
    // Adds an array of type Double_t and of size nValues as binary to the list
    paramList.Add(new FairParamObj(name, values, nValues));
}

void FairParamList::addObject(const Text_t* name, TObject* obj)
{
    // Adds a TObject to the list, sets the class version and the streamer info for
    // ROOT classes
    if (!obj) {
        return;
    }
    FairParamObj* o = new FairParamObj(name);
    o->setParamType(obj->IsA()->GetName());
    o->setClassVersion(obj->IsA()->GetClassVersion());
    TDirectory::TContext restorecwd{};
    FairParamTFile* paramFile = new FairParamTFile();
    gFile = paramFile;
    const Int_t bufsize = 10000;

    TBufferFile* buffer = new TBufferFile(TBuffer::kWrite, bufsize);

    buffer->SetParent(paramFile);
    buffer->MapObject(obj);
    obj->Streamer(*buffer);
    Int_t len = buffer->Length();
    Char_t* buf = new char[len];
    memcpy(buf, buffer->Buffer(), len);
    o->setParamValue(reinterpret_cast<UChar_t*>(buf), len);
    TArrayC* fClassIndex = paramFile->GetClassIndex();
    if (fClassIndex && fClassIndex->fArray[0] != 0) {
        TIter next(gROOT->GetListOfStreamerInfo());
        TStreamerInfo* info;
        TList list;
        while ((info = static_cast<TStreamerInfo*>(next()))) {
            Int_t uid = info->GetNumber();
            if (fClassIndex->fArray[uid]) {
                list.Add(info);
            }
        }
        if (list.GetSize() > 0) {
            list.Sort();
            fClassIndex->fArray[0] = 2;   // to prevent adding classes in TStreamerInfo::TagFile

            TBufferFile* infoBuffer = new TBufferFile(TBuffer::kWrite, bufsize);

            infoBuffer->MapObject(&list);
            list.Streamer(*infoBuffer);
            Int_t infolen = infoBuffer->Length();
            Char_t* infobuf = new char[infolen];
            memcpy(infobuf, infoBuffer->Buffer(), infolen);
            o->setStreamerInfo(reinterpret_cast<UChar_t*>(infobuf), infolen);
            delete infoBuffer;
        } else {
            o->setStreamerInfo(0, 0);
        }
    }
    fClassIndex->fArray[0] = 0;
    delete paramFile;
    paramList.Add(o);
    delete buffer;
}

void FairParamList::print()
{
    // Prints the parameter list including values
    TIter next(&paramList);
    FairParamObj* o;
    while ((o = static_cast<FairParamObj*>(next())) != 0) {
        o->print();
    }
}

Bool_t FairParamList::fill(const Text_t* name, Text_t* value, const Int_t length)
{
    // Copies the data from the list object into the parameter value of type string
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (value == 0) {
        return kFALSE;
    }
    if (o != 0 && strcmp(o->getParamType(), "Text_t") == 0) {
        Int_t l = o->getLength();
        if (l < length - 1) {
            memcpy(value, reinterpret_cast<Char_t*>(o->getParamValue()), l);
            value[l] = '\0';
            return kTRUE;
        } else {
            LOG(error) << "char array too small";
            //      Error("FairParamList::fill(const Text_t*,Text_t*)","char array too small");
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, UChar_t* values, const Int_t nValues)
{
    // Copies the data from the list object into the parameter array of type UChar_t of size nValues.
    // The function returns an error, if the array size of the list object is not equal
    // to nValues.
    if (values == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "UChar_t") == 0) {
        Int_t n = o->getLength();
        if (n == nValues) {
            memcpy(values, o->getParamValue(), n);
            return kTRUE;
        } else {
            LOG(error) << "Different array sizes for parameter " << name;
            //      Error("FairParamList::fill \nDifferent array sizes for parameter %s",name);
            return kFALSE;
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, Int_t* values, const Int_t nValues)
{
    // Copies the data from the list object into the parameter array of type Int_t.
    // The function returns an error, if the array size of the list object is not equal
    // to nValues.
    if (values == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Int_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (n == nValues) {
            memcpy(values, o->getParamValue(), l);
            return kTRUE;
        } else {
            LOG(error) << "Different array sizes for parameter " << name;
            //      Error("FairParamList::fill \nDifferent array sizes for parameter %s",name);
            return kFALSE;
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, Bool_t* values, const Int_t nValues)
{
    // Copies the data from the list object into the parameter array of type Int_t.
    // The function returns an error, if the array size of the list object is not equal
    // to nValues.
    if (values == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Bool_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (n == nValues) {
            memcpy(values, o->getParamValue(), l);
            return kTRUE;
        } else {
            LOG(error) << "Different array sizes for parameter " << name;
            //      Error("FairParamList::fill \nDifferent array sizes for parameter %s",name);
            return kFALSE;
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, UInt_t* values, const Int_t nValues)
{
    // Copies the data from the list object into the parameter array of type UInt_t.
    // The function returns an error, if the array size of the list object is not equal
    // to nValues.
    if (values == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Int_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (n == nValues) {
            memcpy(values, o->getParamValue(), l);
            return kTRUE;
        } else {
            LOG(error) << "Different array sizes for parameter " << name;
            //      Error("FairParamList::fill \nDifferent array sizes for parameter %s",name);
            return kFALSE;
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, Float_t* values, const Int_t nValues)
{
    // Copies the data from the list object into the parameter array of type Float_t.
    // The function returns an error, if the array size of the list object is not equal
    // to nValues.
    if (values == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Float_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (n == nValues) {
            memcpy(values, o->getParamValue(), l);
            return kTRUE;
        } else {
            LOG(error) << "Different array sizes for parameter " << name;
            //      Error("FairParamList::fill \nDifferent array sizes for parameter %s",name);
            return kFALSE;
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, Double_t* values, const Int_t nValues)
{
    // Copies the data from the list object into the parameter array of type Double_t.
    // The function returns an error, if the array size of the list object is not equal
    // to nValues.
    if (values == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Double_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (n == nValues) {
            memcpy(values, o->getParamValue(), l);
            return kTRUE;
        } else {
            LOG(error) << "Different array sizes for parameter " << name;
            //      Error("FairParamList::fill \nDifferent array sizes for parameter %s",name);
            return kFALSE;
        }
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, TArrayI* value)
{
    // Copies the data from the list object into the parameter value of type TArrayI
    // The array is resized, if the number of data is different.
    if (value == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Int_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (value->GetSize() != n) {
            value->Set(n);
        }
        memcpy(value->GetArray(), o->getParamValue(), l);
        return kTRUE;
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, TArrayC* value)
{
    // Copies the data from the list object into the parameter value of type TArrayC
    // The array is resized, if the number of data is different.
    if (value == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Char_t") == 0) {
        Int_t l = o->getLength();
        if (value->GetSize() != l) {
            value->Set(l);
        }
        memcpy(value->GetArray(), o->getParamValue(), l);
        return kTRUE;
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, TArrayF* value)
{
    // Copies the data from the list object into the parameter value of type TArrayF
    // The array is resized, if the number of data is different.
    if (value == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Float_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (value->GetSize() != n) {
            value->Set(n);
        }
        memcpy(value->GetArray(), o->getParamValue(), l);
        return kTRUE;
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name, TArrayD* value)
{
    // Copies the data from the list object into the parameter value of type TArrayD
    // The array is resized, if the number of data is different.
    if (value == 0) {
        return kFALSE;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), "Double_t") == 0) {
        Int_t l = o->getLength();
        Int_t n = o->getNumParams();
        if (value->GetSize() != n) {
            value->Set(n);
        }
        memcpy(value->GetArray(), o->getParamValue(), l);
        return kTRUE;
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return kFALSE;
}

Bool_t FairParamList::fillObject(const Text_t* name, TObject* obj)
{
    // Fills the object obj (must exist!) via the Streamer and returns the class version.
    // Prints a warning if the class version in the list objects differs from the actual
    // class version.
    if (!obj) {
        return 0;
    }
    FairParamObj* o = static_cast<FairParamObj*>(paramList.FindObject(name));
    if (o != 0 && strcmp(o->getParamType(), obj->IsA()->GetName()) == 0) {
        if (o->getClassVersion() != obj->IsA()->GetClassVersion()) {
            LOG(warn) << "Read Class Version = " << o->getClassVersion()
                      << " does not match actual version = " << obj->IsA()->GetClassVersion();
        }
        //      Warning("FairParamList::fill",
        //              "\n       Read Class Version = %i does not match actual version = %i",
        //              o->getClassVersion(),obj->IsA()->GetClassVersion());
        TDirectory::TContext restorecwd{};
        gFile = 0;
        TBufferFile* buf = 0;

        Int_t len = o->getStreamerInfoSize();
        if (len > 0 && o->getStreamerInfo() != 0) {
            buf = new TBufferFile(TBuffer::kRead, len);
            memcpy(buf->Buffer(), reinterpret_cast<Char_t*>(o->getStreamerInfo()), len);
            buf->SetBufferOffset(0);
            TList list;
            buf->MapObject(&list);
            list.Streamer(*buf);
            delete buf;
            TStreamerInfo* info;
            TIter next(&list);
            while ((info = static_cast<TStreamerInfo*>(next()))) {
                if (info->IsA() != TStreamerInfo::Class()) {
                    LOG(warn) << "Not a TStreamerInfo object";
                    //          Warning("FairParamList::fill","not a TStreamerInfo object");
                    continue;
                }
                info->BuildCheck();
            }
            list.Clear();   // this will delete all TStreamerInfo objects with kCanDelete
        }
        len = o->getLength();
        buf = new TBufferFile(TBuffer::kRead, len);
        memcpy(buf->Buffer(), reinterpret_cast<Char_t*>(o->getParamValue()), len);
        buf->SetBufferOffset(0);
        buf->MapObject(obj);
        obj->Streamer(*buf);
        delete buf;
        return len;
    }
    LOG(error) << "Could not find parameter " << name;
    //  Error("FairParamList::fill \nNot found: %s",name);
    return 0;
}
