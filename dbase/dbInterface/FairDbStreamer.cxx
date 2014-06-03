/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairDbStreamer.h"
#include "FairUtilStream.h"


#include "TBufferFile.h"
#include <iostream>                     // for cout
using std::cout;
using std::endl;


ClassImp(FairDbStreamer)

FairDbStreamer::FairDbStreamer()
  : TObject(),
    fString(""),
    fSize(0),
    fType(FairDb::kInt)
{
}

FairDbStreamer::FairDbStreamer(const TObject* obj,FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(obj,fSize);
  fType=type;
}

FairDbStreamer::FairDbStreamer(const Int_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}

FairDbStreamer::FairDbStreamer(const UInt_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}


FairDbStreamer::FairDbStreamer(const Short_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}

FairDbStreamer::FairDbStreamer(const UShort_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}

FairDbStreamer::FairDbStreamer(const Bool_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}


FairDbStreamer::FairDbStreamer(const Float_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}

FairDbStreamer::FairDbStreamer(const Double_t* iarr, Int_t size, FairDb::DataTypes type)
  : TObject()
{
  fString = FairDb::StreamAsString(iarr,size);
  fSize=size;
  fType=type;
}



FairDbStreamer::FairDbStreamer(const FairDbStreamer& from)
  : TObject(from),fString(from.fString)
{
}

FairDbStreamer& FairDbStreamer::operator=(const FairDbStreamer& from)
{

  if (this == &from) { return *this; }
  TObject::operator=(from);
  fString=from.fString;
  return *this;
}

FairDbStreamer::~FairDbStreamer()
{
}

void FairDbStreamer::Fill(Int_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Int_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Int_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}


void FairDbStreamer::Fill(UInt_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(UInt_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  UInt_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}


void FairDbStreamer::Fill(Short_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Short_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Short_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}

void FairDbStreamer::Fill(UShort_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(UShort_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  UShort_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}


void FairDbStreamer::Fill(Bool_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Bool_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Bool_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}

void FairDbStreamer::Fill(Float_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Float_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Float_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i]; }
}

void FairDbStreamer::Fill(Double_t* arr)
{
  // Decrypt str
  Int_t arr_size = GetSize();
  Int_t ll = arr_size * sizeof(Double_t);
  Char_t data[ll];
  // Decryption str
  std::string str_hex(fString.Data());
  Util::BinFromHex(str_hex,data);
  // Map to array
  Double_t r_array[arr_size];
  for(int i=0; i<arr_size; i++) { r_array[i]=0.; }
  TBufferFile b_read(TBuffer::kRead,ll,data,kFALSE);
  b_read.ReadFastArray(r_array,arr_size);
  for(Int_t i=0; i<arr_size; i++) { arr[i]=r_array[i];}
}



void FairDbStreamer::Fill(TObject* obj)
{
  // Filling  the Object
  TObject* cobj=obj->Clone();
  TBufferFile b_write(TBuffer::kWrite);
  cobj->Streamer(b_write);
  Int_t   ll   = b_write.Length();
  if (cobj) { delete cobj; }
  // Decryption str
  std::string str_hex(fString.Data());
  Char_t read_buf[ll];
  Util::BinFromHex(str_hex,read_buf);

  TBufferFile b_read(TBuffer::kRead,ll, read_buf,kFALSE);
  obj->Streamer(b_read);

}
