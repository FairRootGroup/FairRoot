/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004
//*-- modified : 28/01/2009 by Ilse Koenig
/////////////////////////////////////////////////////////////
// FairDetParAsciiFileIo
//
// Class for parameter input/output from/into Ascii file
// Base class for all detector Ascii I/Os
//
/////////////////////////////////////////////////////////////

#include "FairDetParAsciiFileIo.h"

#include "FairParSet.h"   // for FairParSet

#include <fairlogger/Logger.h>

#include <fstream>    // for fstream
#include <stdio.h>    // for printf, sprintf
#include <string.h>   // for strlen, strncmp

using std::ios;

FairDetParAsciiFileIo::FairDetParAsciiFileIo(std::fstream* f)
    : FairDetParIo()
    , fHeader("")
    , sepLine("##############################################################################\n")
    , pFile(f)
{
    // constructor
    /*  pFile=f;
  sepLine=
  "##############################################################################\n";
  */
}

Bool_t FairDetParAsciiFileIo::findContainer(const Text_t* name)
{
    // searches the container in the file
    const Int_t maxbuf = 4000;
    Text_t buf[maxbuf];
    Text_t buf2[maxbuf];

    int result_length = snprintf(buf2, maxbuf-1, "%s%s%s", "[", name, "]");
    if (!(result_length > 0 && result_length < static_cast<int>(maxbuf))) {
      LOG(fatal) << "Buffer overrun in snprintf.";
    }

    // cout << " buf2 " <<  buf2 << endl;
    pFile->clear();
    pFile->seekg(0, ios::beg);
    while (!pFile->eof()) {
        pFile->getline(buf, maxbuf);
        if (buf[0] != '[') {
            continue;
        }
        // cout << " buf: " <<  buf << endl;
        if (!strncmp(buf, buf2, strlen(buf2))) {
            break;
        }
    }
    return !pFile->eof();
}

Bool_t FairDetParAsciiFileIo::checkAllFound(Int_t* set, Int_t setSize)
{
    // checks if all modules have been initialized
    Bool_t allFound = kTRUE;
    for (Int_t i = 0; i < setSize; i++) {
        if (set[i] == 999) {
            set[i] = 0;
            printf(" %i", i);
        }
        if (set[i]) {
            allFound = kFALSE;
        }
    }
    printf("\n");
    return allFound;
}

void FairDetParAsciiFileIo::writeHeader(const Text_t* name,
                                        const Text_t* context,
                                        const Text_t* author,
                                        const Text_t* description)
{
    // calls the function putAsciiHeader(...) of the parameter container
    // class and writes the header to the file
    pFile->write(sepLine, strlen(sepLine));
    pFile->write(fHeader.Data(), fHeader.Length());
    pFile->write(sepLine, strlen(sepLine));
    *pFile << "[" << name << "]\n";
    if (strlen(context) > 0) {
        *pFile << "// Parameter Context: " << context << "\n";
    }
    if (strlen(author) > 0) {
        *pFile << "author:      " << author << "\n";
    }
    TString t = description;
    if (!t.IsNull()) {
        t = t.ReplaceAll("\n", " \\\n");
        *pFile << "description: " << t << "\n";
    }
    *pFile << "//-----------------------------------------------------------"
              "-----------------\n";
}

void FairDetParAsciiFileIo::readComment(const Char_t* lastBuf, FairParSet* pPar)
{
    // reads the author or the description
    const Int_t maxbuf = 4000;
    Text_t buf[maxbuf];
    TString s = lastBuf;
    TString pName, pVal;
    Ssiz_t n = s.First(':');
    Ssiz_t m = s.Last('\\');
    pName = s(0, n);
    if (m > 0) {
        pVal = s(n + 1, m - n - 1);
    } else {
        pVal = s(n + 1, s.Length() - n - 1);
    }
    pVal = pVal.Strip(pVal.kLeading);
    while (m > 0) {
        pVal += "\n";
        pFile->getline(buf, maxbuf);
        if (buf[0] != '/') {
            s = buf;
            m = s.Last('\\');
            if (m > 0) {
                pVal += s(0, m);
            } else {
                pVal += s;
            }
        }
    }
    if (pName.CompareTo("author") == 0) {
        pPar->setAuthor(pVal.Data());
    } else if (pName.CompareTo("description") == 0) {
        pPar->setDescription(pVal.Data());
    }
}

void FairDetParAsciiFileIo::writeComment(FairParSet* pPar)
{
    TString t = pPar->getAuthor();
    if (!t.IsNull()) {
        *pFile << "author:      " << t << "\n";
    }
    t = pPar->getDescription();
    if (!t.IsNull()) {
        t = t.ReplaceAll("\n", " \\\n");
        *pFile << "description: " << t << "\n";
    }
}

/*
FairDetParAsciiFileIo::FairDetParAsciiFileIo(std::fstream* f) {
// constructor
pFile=f;
sepLine=
"##############################################################################\n";
}

Bool_t FairDetParAsciiFileIo::findContainer(const Text_t* name) {
  // searches the container in the file
  const Int_t maxbuf=4000;
  Text_t buf[maxbuf];
  Text_t buf2[maxbuf];
  
  int result_length = snprintf(buf2, maxbuf-1, "%s%s%s", "[", name, "]");
  if (!(result_length > 0 && result_length < static_cast<int>(maxbuf))) {
    LOG(fatal) << "Buffer overrun in snprintf.";
  }

  pFile->clear();
  pFile->seekg(0,ios::beg);
  while (!pFile->eof()) {
    pFile->getline(buf,maxbuf);
    if (buf[0]!='[') continue;
    if (!strncmp(buf,buf2,strlen(buf2))) break;
  }
  if (pFile->eof()) return kFALSE;
  return kTRUE;
}

void FairDetParAsciiFileIo::writeHeader(const Text_t* name, const Text_t* context,
                                 const Text_t* author, const Text_t* description) {
// calls the function putAsciiHeader(...) of the parameter container
// class and writes the header to the file
pFile->write(sepLine,strlen(sepLine));
pFile->write(fHeader.Data(),fHeader.Length());
pFile->write(sepLine,strlen(sepLine));
*pFile<<"["<<name<<"]\n";
if (strlen(context)>0) *pFile<<"// Parameter Context: "<<context<<"\n";
if (strlen(author)>0) *pFile<<"author:      "<<author<<"\n";
TString t=description;
if (!t.IsNull()) {
t=t.ReplaceAll("\n"," \\\n");
*pFile<<"description: "<<t<<"\n";
}
*pFile<<"//-----------------------------------------------------------"
        "-----------------\n";
}

void FairDetParAsciiFileIo::readComment(const char* lastBuf, FairParSet* pPar) {
// reads the author or the description
const Int_t maxbuf=4000;
Text_t buf[maxbuf];
TString s=lastBuf;
TString pName, pVal;
Ssiz_t n=s.First(':');
Ssiz_t m=s.Last('\\');
pName=s(0,n);
if (m>0) pVal=s(n+1,m-n-1);
else pVal=s(n+1,s.Length()-n-1);
pVal=pVal.Strip(pVal.kLeading);
while (m>0) {
pVal+="\n";
pFile->getline(buf,maxbuf);
if (buf[0]!='/') {
  s=buf;
  m=s.Last('\\');
  if (m>0) pVal+=s(0,m);
  else pVal+=s;
}
}
if (pName.CompareTo("author")==0) pPar->setAuthor(pVal.Data());
else if ( pName.CompareTo("description")==0) pPar->setDescription(pVal.Data());
}

void FairDetParAsciiFileIo::writeComment(FairParSet* pPar) {
TString t=pPar->getAuthor();
if (!t.IsNull()) *pFile<<"author:      "<<t<<"\n";
t=pPar->getDescription();
if (!t.IsNull()) {
t=t.ReplaceAll("\n"," \\\n");
*pFile<<"description: "<<t<<"\n";
}
}
*/
