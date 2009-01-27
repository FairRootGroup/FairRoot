//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////////
//
//  FairParamObj
//
//  Class for single parameters of basic types or small arrays and used as
//  list elements in FairParamList::paramList.
//  The values are stored as strings. Arrays are concatinated to a string as a
//  comma-separated list.
///////////////////////////////////////////////////////////////////////////////


#include "FairParamList.h"

//#include "TClass.h"
#include "TFile.h"
#include "TArrayI.h"
#include "TArrayC.h"
#include "TArrayF.h"
#include "TArrayD.h"
#include "TClass.h"

#if ROOT_VERSION_CODE >= ROOT_VERSION(5,15,0)
#include <TBufferFile.h>
#else
#include <TBuffer.h>
#endif

#include <iostream>
//#include "stdlib.h"


ClassImp(FairParamObj)
 
FairParamObj::FairParamObj(const Text_t* name,const Text_t* value,
                     const char type,const Int_t numParam) 
: paramValue(value),
  paramType(type),
  nParam(numParam)
{
  // (Default) Constructor
  SetName(name);
 
}
FairParamObj::FairParamObj() 
: nParam(0)
{
}
void FairParamObj::print() {
  // prints the name and the value
  std::cout<<GetName()<<": "<<paramValue<<std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//
//  FairParamBinObj
//
//  Class for parameters of large arrays of basic types and used as list
//  elements in FairParamList::paramBinList.
//  The values are stored as binary.
//  Arrays of UChar_t, Short_t, Int_t, Float_t, Double_t are supported.
//  The arguments in the overloaded constructors and fill-functions are
//      the name of the parameter
//      the pointer to the array
//      the length of the array.      
//
///////////////////////////////////////////////////////////////////////////////

ClassImp(FairParamBinObj)
 
FairParamBinObj::FairParamBinObj() {
  // Default constructor with type "u" for "unknown"
  paramType="u";
  basicType=kFALSE;
  classVersion=-1;
  arraySize=0;
  paramValue=0;
}

FairParamBinObj::FairParamBinObj(FairParamBinObj& o) {
  // Copy constructor
  SetName(o.GetName());
  paramType=o.getParamType();
  if (o.isBasicType()) basicType=kTRUE;
  else basicType=kFALSE;
  classVersion=o.getClassVersion();
  arraySize=o.getLength();
  paramValue=new UChar_t[arraySize];
  memcpy(paramValue,o.getParamValue(),arraySize);
}

FairParamBinObj::FairParamBinObj(const Text_t* name,const UChar_t* value,const Int_t length) {
  // Constructor for an array of UChar_t with arraylength lenght 
  SetName(name);
  paramType="cBin";
  basicType=kTRUE;
  classVersion=-1;
  arraySize=length;
  paramValue=new UChar_t[arraySize];
  memcpy(paramValue,value,arraySize);
}

FairParamBinObj::FairParamBinObj(const Text_t* name,const Short_t* value,const Int_t nValues) {
  // Constructor for an array of nValues elements of type Short_t
  SetName(name);
  paramType="hBin";
  basicType=kTRUE;
  arraySize=nValues*sizeof(Short_t);
  paramValue=new UChar_t[arraySize];
  memcpy(paramValue,value,arraySize);
}

FairParamBinObj::FairParamBinObj(const Text_t* name,const Int_t* value,const Int_t nValues) {
  // Constructor for an array of nValues elements of type Int_t
  SetName(name);
  paramType="iBin";
  basicType=kTRUE;
  arraySize=nValues*sizeof(Int_t);
  paramValue=new UChar_t[arraySize];
  memcpy(paramValue,value,arraySize);
}

FairParamBinObj::FairParamBinObj(const Text_t* name,const Float_t* value,const Int_t nValues) {
  // Constructor for an array of nValues elements of type Float_t
  SetName(name);
  paramType="fBin";
  basicType=kTRUE;
  classVersion=-1;
  arraySize=nValues*sizeof(Float_t);
  paramValue=new UChar_t[arraySize];
  memcpy(paramValue,value,arraySize);
}

FairParamBinObj::FairParamBinObj(const Text_t* name,const Double_t* value,const Int_t nValues) {
  // Constructor for an array of nValues elements of type Double_t
  SetName(name);
  paramType="dBin";
  basicType=kTRUE;
  classVersion=-1;
  arraySize=nValues*sizeof(Double_t);
  paramValue=new UChar_t[arraySize];
  memcpy(paramValue,value,arraySize);
}

FairParamBinObj::~FairParamBinObj() {
  // Destructor
  if (paramValue) {
    delete [] paramValue;
    paramValue=0;
  }
}

void FairParamBinObj::setParamType(const Text_t* t) {
  // Sets the parameter type. Accepted type names are:
  //     cBin for UChar_t
  //     hBin for Short_t
  //     iBin for Int_t
  //     fBin for Float_t
  //     dBin for Double_t
  //     class name
  if (strcmp(t,"cBin")==0 || strcmp(t,"hBin")==0 || strcmp(t,"iBin")==0
         || strcmp(t,"fBin")==0 || strcmp(t,"dBin")==0) {
    basicType=kTRUE;
    classVersion=-1;
  }
  else basicType=kFALSE;
  paramType=t;
}

void FairParamBinObj::setParamValue(UChar_t* value,const Int_t length) {
  // Sets the parameter value (the array is not copied!)
  if (paramValue) delete [] paramValue;
  arraySize=length;
  paramValue=value;
}

void FairParamBinObj::setLength(Int_t l) {
  // Sets the length of the binary array
  if (paramValue && arraySize!=l) delete [] paramValue;
  arraySize=l;
  paramValue=new UChar_t[arraySize];
}

void FairParamBinObj::fill(const Text_t* name,UChar_t* value,const Int_t length) {
  // Sets the name and value (UChar_t array) of an existing object 
  SetName(name);
  paramType="cBin";
  basicType=kTRUE;
  setLength(length);
  memcpy(paramValue,value,arraySize);
}

void FairParamBinObj::fill(const Text_t* name,Short_t* value,const Int_t nValues)   // Sets the name and value (Short_t array) of an existing object 
{
  SetName(name);
  paramType="hBin";
  basicType=kTRUE;
  classVersion=-1;
  setLength(nValues*sizeof(Short_t));
  memcpy(paramValue,value,arraySize);
}

void FairParamBinObj::fill(const Text_t* name,Int_t* value,const Int_t nValues) {
  // Sets the name and value (Intt_t array) of an existing object 
  SetName(name);
  paramType="iBin";
  basicType=kTRUE;
  classVersion=-1;
  setLength(nValues*sizeof(Int_t));
  memcpy(paramValue,value,arraySize);
}

void FairParamBinObj::fill(const Text_t* name,Float_t* value,const Int_t nValues)   // Sets the name and value (Float_t array) of an existing object 
{
  SetName(name);
  paramType="fBin";
  basicType=kTRUE;
  classVersion=-1;
  setLength(nValues*sizeof(Float_t));
  memcpy(paramValue,value,arraySize);
}

void FairParamBinObj::fill(const Text_t* name,Double_t* value,const Int_t nValues)  // Sets the name and value (Double_t array) of an existing object 
 {
  SetName(name);
  paramType="dBin";
  basicType=kTRUE;
  classVersion=-1;
  setLength(nValues*sizeof(Double_t));
  memcpy(paramValue,value,arraySize);
}

Int_t FairParamBinObj::getNumParams() {
  // returns the number of values in the array, respectively 1 for classes
  Int_t n=0;
  if (basicType) {
    switch(paramType[0]) {
      case 'c': n=arraySize;                  break;
      case 'h': n=arraySize/sizeof(Short_t);  break;
      case 'i': n=arraySize/sizeof(Int_t);    break;
      case 'f': n=arraySize/sizeof(Float_t);  break;
      case 'd': n=arraySize/sizeof(Double_t); break;
      default: Error("FairParamBinObj::getNumParams()","Unknown Type %s",paramType.Data());
    }
  } else n=1;  // always 1 for classes
  return n;
}

void FairParamBinObj::print() {
  // Prints the name and type of the parameters, respectively class name and version
  // Prints also the numbers for an array of Short_t, Int_t, Float_t, Double_t.
  printf("%s:  ",GetName());
  if (!basicType) {
    printf("\n  Class Type:    %s\n  Class Version: %i\n",
           paramType.Data(),classVersion);
  } else {
    Int_t l=0, i=0, k=0;
    TString format;
    switch(paramType[0]) {
      case 'c':
        printf("Binary UChar_t Array\n");
        break;
      case 'h':
        printf("Binary Short_t Array\n");
        l=arraySize/sizeof(Short_t);
        while (k<l) {
          if (i==10) {
            printf("\n");
            i=0;
          }
          printf("%i ",((Short_t*)paramValue)[k]);
          i++;
          k++;  
        }
        printf("\n");
        break;
      case 'i':
        printf("Binary Int_t Array\n");
        l=arraySize/sizeof(Int_t);
        while (k<l) {
          if (i==10) {
            printf("\n");
            i=0;
          }
          printf("%i ",((Int_t*)paramValue)[k]);
          i++;
          k++;  
        }
        printf("\n");
        break;
      case 'f':
        printf("Binary Float_t Array\n");
        l=arraySize/sizeof(Float_t);
        while (k<l) {
          if (i==10) {
            printf("\n");
            i=0;
          }
          printf("%g ",((Float_t*)paramValue)[k]);
          i++;
          k++;  
        }
        printf("\n");
        break;
      case 'd':
        printf("Binary Double_t Array\n");
        l=arraySize/sizeof(Double_t);
        while (k<l) {
          if (i==10) {
            printf("\n");
            i=0;
          }
          printf("%g ",((Double_t*)paramValue)[k]);
          i++;
          k++;  
        }
        printf("\n");
        break;
      default:
        Error("FairParamBinObj::getNumParams()","Unknown Type %s",paramType.Data());
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  FairParamList
//
//  Class for generic Oracle and ASCII interface for parameter containers
//  derived from HParGenericSet
//
//  All add/addBin functions add an initialized parameter to the list for
//  writing, all fill-functions copies the value from the list to the
//  parameter in the initialization process.
//
///////////////////////////////////////////////////////////////////////////////

ClassImp(FairParamList)

FairParamList::FairParamList() {
  // Constructor
  paramList=new TList;
  paramBinList=new TList;
}

FairParamList::~FairParamList() {
  // Destructor
  if (paramList) {
    paramList->Delete();
    delete paramList;
    paramList=0;
  }
  if (paramBinList) {
    paramBinList->Delete();
    delete paramBinList;
    paramBinList=0;
  }
}

void FairParamList::add(FairParamObj& p) {
  // Adds a FairParamObj object to the list
  paramList->Add(new FairParamObj(p.GetName(),p.getParamValue(),
                               p.getParamType(),p.getNumParams()));
}

void FairParamList::addBinary(FairParamBinObj& p) {
  // Adds a HBinParamObj object to the list
  paramBinList->Add(new FairParamBinObj(p));
}

void FairParamList::add(const Text_t* name,const Text_t* value,
                     const char type,const Int_t n) {
  paramList->Add(new FairParamObj(name,value,type,n));
}

void FairParamList::add(const Text_t* name,const Int_t value) {
  const char f[]="%i";
  Text_t buf[100];
  sprintf(buf,f,value);
  paramList->Add(new FairParamObj(name,buf,'i',1));
}

void FairParamList::add(const Text_t* name,const UInt_t value) {
  const char f[]="%u";
  Text_t buf[100];
  sprintf(buf,f,value);
  paramList->Add(new FairParamObj(name,buf,'u',1));
}

void FairParamList::add(const Text_t* name,const Long_t value) {
  const char f[]="%ld";
  Text_t buf[100];
  sprintf(buf,f,value);
  paramList->Add(new FairParamObj(name,buf,'l',1));
}

void FairParamList::add(const Text_t* name,const Float_t value,const Int_t precision) {
  Text_t f[100];
  sprintf(f,"%s%i%s","%.",precision,"f");
  Text_t buf[100];
  sprintf(buf,f,value);
  paramList->Add(new FairParamObj(name,buf,'f',1));
}

void FairParamList::add(const Text_t* name,const Double_t value,const Int_t precision) {
  Text_t f[100];
  sprintf(f,"%s%i%s","%.",precision,"lf");
  Text_t buf[100];
  sprintf(buf,f,value);
  paramList->Add(new FairParamObj(name,buf,'d',1));
}

void FairParamList::add(const Text_t* name,TArrayI& value) {
  Int_t n=value.GetSize();
  const char f[]="%i";
  Text_t buf[100];
  TString s;
  for(Int_t i=0;i<n;i++) {
    if (i>0) s.Append(",");
    sprintf(buf,f,value.At(i));
    s.Append(buf);
  }
  paramList->Add(new FairParamObj(name,s,'i',n));
}

void FairParamList::add(const Text_t* name,TArrayC& value) {
  Int_t n=value.GetSize();
  const char f[]="%i";
  Text_t buf[100];
  TString s;
  for(Int_t i=0;i<n;i++) {
    if (i>0) s.Append(",");
    sprintf(buf,f,int(value.At(i)));
    s.Append(buf);
  }
  paramList->Add(new FairParamObj(name,s,'i',n));
}

void FairParamList::add(const Text_t* name,TArrayF& value,const Int_t precision){
  Int_t n=value.GetSize();
  Text_t f[100];
  sprintf(f,"%s%i%s","%.",precision,"f");
  Text_t buf[100];
  TString s;
  for(Int_t i=0;i<n;i++) {
    if (i>0) s.Append(",");
    sprintf(buf,f,value.At(i));
    s.Append(buf);
  }
  paramList->Add(new FairParamObj(name,s,'f',n));
}

void FairParamList::add(const Text_t* name,TArrayD& value,const Int_t precision){
  Int_t n=value.GetSize();
  Text_t f[100];
  sprintf(f,"%s%i%s","%.",precision,"lf");
  Text_t buf[100];
  TString s;
  for(Int_t i=0;i<n;i++) {
    if (i>0) s.Append(",");
    sprintf(buf,f,value.At(i));
    s.Append(buf);
  }
  paramList->Add(new FairParamObj(name,s,'d',n));
}

void FairParamList::addBinary(const Text_t* name,const UChar_t* values,const Int_t nValues){
  paramBinList->Add(new FairParamBinObj(name,values,nValues));
}

void FairParamList::addBinary(const Text_t* name,const Short_t* values,const Int_t nValues){
  paramBinList->Add(new FairParamBinObj(name,values,nValues));
}

void FairParamList::addBinary(const Text_t* name,const Int_t* values,const Int_t nValues){
  paramBinList->Add(new FairParamBinObj(name,values,nValues));
}

void FairParamList::addBinary(const Text_t* name,const Float_t* values,const Int_t nValues){
  paramBinList->Add(new FairParamBinObj(name,values,nValues));
}

void FairParamList::addBinary(const Text_t* name,const Double_t* values,const Int_t nValues){
  paramBinList->Add(new FairParamBinObj(name,values,nValues));
}

void FairParamList::addBinary(const Text_t* name,TObject* obj) {
  if (!obj) return;
  FairParamBinObj* o=new FairParamBinObj;
  o->SetName(name);
  o->setParamType(obj->IsA()->GetName());
  o->setClassVersion(obj->IsA()->GetClassVersion());
  TFile* filesave=gFile;
  gFile=0;
  const Int_t bufsize=10000;


#if ROOT_VERSION_CODE >= ROOT_VERSION(5,15,0)
    TBufferFile* buffer=new TBufferFile(TBuffer::kWrite,bufsize); 
#else
    TBuffer* buffer=new TBuffer(TBuffer::kWrite,bufsize); 
#endif
  

  buffer->MapObject(obj);
  obj->Streamer(*buffer);
  Int_t len=buffer->Length();
  char* buf=new char[len];
  memcpy(buf,buffer->Buffer(),len);
  o->setParamValue((UChar_t*)buf,len);
  paramBinList->Add(o);
  delete buffer;
  gFile=filesave;
}

void FairParamList::print() {
  TIter next(paramList);
  FairParamObj* o;
  while ((o=(FairParamObj*)next())!=0) o->print();
  TIter nextBin(paramBinList);
  FairParamBinObj* b;
  while ((b=(FairParamBinObj*)nextBin())!=0) b->print();
}

Bool_t FairParamList::fill(const Text_t* name,Text_t* value,const Int_t length) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='s') {
    const char* v=o->getParamValue();
    Int_t l=strlen(v);
    if (l<length) {
      strcpy(value,o->getParamValue());
      return kTRUE;
    } else Error("FairParamList::fill(const Text_t*,Text_t*)",
                 "char array too small");
  }
  Error("FairParamList::fill \nNot found: %s",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,Int_t* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='i' && o->getNumParams()==1) {
    sscanf(o->getParamValue(),"%i",value);
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,UInt_t* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='u' && o->getNumParams()==1) {
    sscanf(o->getParamValue(),"%u",value);
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,Long_t* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='l' && o->getNumParams()==1) {
    sscanf(o->getParamValue(),"%ld",value);
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,Float_t* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='f' && o->getNumParams()==1) {
    sscanf(o->getParamValue(),"%f",value);
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,Double_t* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='d' && o->getNumParams()==1) {
    sscanf(o->getParamValue(),"%lf",value);
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,TArrayI* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='i') {
    Int_t n=o->getNumParams();
    if (value->GetSize()!=n) value->Set(n);
    const char d[]=",";
    char* ss;
    Int_t v;
    char s[4001];
    strcpy(s,o->getParamValue());
    ss=strtok(s,d);
    sscanf(ss,"%i",&v);
    value->AddAt(v,0);
    for(Int_t i=1;i<n;i++) {
      ss=strtok(NULL,d);
      sscanf(ss,"%i",&v);
      value->AddAt(v,i);
    }
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,TArrayC* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='i') {
    Int_t n=o->getNumParams();
    if (value->GetSize()!=n) value->Set(n);
    const char d[]=",";
    char* ss;
    Int_t v;
    char s[4001];
    strcpy(s,o->getParamValue());
    ss=strtok(s,d);
    sscanf(ss,"%i",&v);
    value->AddAt(char(v),0);
    for(Int_t i=1;i<n;i++) {
      ss=strtok(NULL,d);
      sscanf(ss,"%i",&v);
      value->AddAt(v,i);
    }
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,TArrayF* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='f') {
    Int_t n=o->getNumParams();
    if (value->GetSize()!=n) value->Set(n);
    const char d[]=",";
    char* ss;
    Float_t v;
    char s[4001];
    strcpy(s,o->getParamValue());
    ss=strtok(s,d);
    sscanf(ss,"%f",&v);
    value->AddAt(v,0);
    for(Int_t i=1;i<n;i++) {
      ss=strtok(NULL,d);
      sscanf(ss,"%f",&v);
      value->AddAt(v,i);
    }
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fill(const Text_t* name,TArrayD* value) {
  FairParamObj* o=(FairParamObj*)paramList->FindObject(name);
  if (value==0) return kFALSE;
  if (o!=0 && o->getParamType()=='d') {
    Int_t n=o->getNumParams();
    if (value->GetSize()!=n) value->Set(n);
    const char d[]=",";
    char* ss;
    Double_t v;
    char s[4001];
    strcpy(s,o->getParamValue());
    ss=strtok(s,d);
    sscanf(ss,"%lf",&v);
    value->AddAt(v,0);
    for(Int_t i=1;i<n;i++) {
      ss=strtok(NULL,d);
      sscanf(ss,"%lf",&v);
      value->AddAt(v,i);
    }
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fillBinary(const Text_t* name,UChar_t* values,const Int_t nValues) {
  // Fills the array (no resize).
  if (values==0) return kFALSE;
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"cBin")==0) {
    Int_t n=o->getLength();  
    if (n==nValues) {
      memcpy(values,o->getParamValue(),n);
      return kTRUE;
    } else {
      Error("FairParamList::fillBinary \nDifferent array sizes for parameter ",name);
      return kFALSE;
    }
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fillBinary(const Text_t* name,Short_t* values,const Int_t nValues) {
  // Fills the array (no resize).
  if (values==0) return kFALSE;
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"hBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Short_t);  
    if (n==nValues) {
      memcpy(values,o->getParamValue(),l);
      return kTRUE;
    } else {
      Error("FairParamList::fillBinary \nDifferent array sizes for parameter ",name);
      return kFALSE;
    }
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fillBinary(const Text_t* name,Int_t* values,const Int_t nValues) {
  // Fills the array (no resize).
  if (values==0) return kFALSE;
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"iBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Int_t);  
    if (n==nValues) {
      memcpy(values,o->getParamValue(),l);
      return kTRUE;
    } else {
      Error("FairParamList::fillBinary \nDifferent array sizes for parameter ",name);
      return kFALSE;
    }
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fillBinary(const Text_t* name,Float_t* values,const Int_t nValues) {
  // Fills the array (no resize).
  if (values==0) return kFALSE;
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"fBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Float_t);  
    if (n==nValues) {
      memcpy(values,o->getParamValue(),l);
      return kTRUE;
    } else {
      Error("FairParamList::fillBinary \nDifferent array sizes for parameter ",name);
      return kFALSE;
    }
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Bool_t FairParamList::fillBinary(const Text_t* name,Double_t* values,const Int_t nValues) {
  // Fills the array (no resize).
  if (values==0) return kFALSE;
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"dBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Double_t);  
    if (n==nValues) {
      memcpy(values,o->getParamValue(),l);
      return kTRUE;
    } else {
      Error("FairParamList::fillBinary \nDifferent array sizes for parameter ",name);
      return kFALSE;
    }
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}

Int_t FairParamList::fillBinary(const Text_t* name,UChar_t* values) {
  // Recreates the array and returns the number of array elements
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"cBin")==0) {
    Int_t l=o->getLength();
    if (values) delete values;
    values=new UChar_t[l];
    memcpy(values,o->getParamValue(),l);
    return l;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return 0;
}

Int_t FairParamList::fillBinary(const Text_t* name,Short_t* values) {
  // Recreates the array and returns the number of array elements
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"hBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Short_t);  
    if (values) delete values;
    values=new Short_t[n];
    memcpy(values,o->getParamValue(),l);
    return n;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return 0;
}

Int_t FairParamList::fillBinary(const Text_t* name,Int_t* values) {
  // Recreates the array and returns the number of array elements
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"iBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Int_t);  
    if (values) delete values;
    values=new Int_t[n];
    memcpy(values,o->getParamValue(),l);
    return n;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return 0;
}

Int_t FairParamList::fillBinary(const Text_t* name,Float_t* values) {
  // Recreates the array and returns the number of array elements
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"fBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Float_t);  
    if (values) delete values;
    values=new Float_t[n];
    memcpy(values,o->getParamValue(),l);
    return n;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return 0;
}

Int_t FairParamList::fillBinary(const Text_t* name,Double_t* values) {
  // Recreates the array and returns the number of array elements
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),"dBin")==0) {
    Int_t l=o->getLength();
    Int_t n=l/sizeof(Double_t);  
    if (values) delete values;
    values=new Double_t[n];
    memcpy(values,o->getParamValue(),l);
    return n;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return 0;
}

Int_t FairParamList::fillBinary(const Text_t* name,TObject* obj) {
  // Fills the object obj (must exist!) via the Streamer and returns the class version
  // Prints a warning if the class version read differs from the actual class version
  if (!obj) return kFALSE;
  FairParamBinObj* o=(FairParamBinObj*)paramBinList->FindObject(name);
  if (o!=0 && strcmp(o->getParamType(),obj->IsA()->GetName())==0) {
    if (o->getClassVersion()!=obj->IsA()->GetClassVersion())
      Warning("FairParamList::fillBinary",
              "\n       Read Class Version = %i does not match actual version = %i",
              o->getClassVersion(),obj->IsA()->GetClassVersion());
    Int_t len=o->getLength();
    TFile* filesave=gFile;
    gFile=0;

#if ROOT_VERSION_CODE >= ROOT_VERSION(5,15,0)
    TBufferFile* buf=new TBufferFile(TBuffer::kRead,len);
#else
    TBuffer* buf=new TBuffer(TBuffer::kRead,len);
#endif


    memcpy(buf->Buffer(),(char*)o->getParamValue(),len);
    buf->SetBufferOffset(0);
    buf->MapObject(obj);
    obj->Streamer(*buf);
    delete buf;
    gFile=filesave;
    return kTRUE;
  }
  Error("FairParamList::fill \nNot found: ",name);
  return kFALSE;
}
