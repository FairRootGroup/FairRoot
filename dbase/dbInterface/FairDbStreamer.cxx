
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

void FairDbStreamer::Fill(TObject* obj)
{
  // Filling  the Object
  TObject* cobj=obj->Clone();
  TBufferFile b_write(TBuffer::kWrite);
  cobj->Streamer(b_write);
  Int_t   ll   = b_write.Length();
  // Decryption str
  std::string str_hex(fString.Data());
  Char_t read_buf[ll];
  Util::BinFromHex(str_hex,read_buf);

  TBufferFile b_read(TBuffer::kRead,ll, read_buf,kFALSE);
  obj->Streamer(b_read);
}
