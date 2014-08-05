/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH *
 *                                                                              *
 *              This software is distributed under the terms of the *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3, *
 *                  copied verbatim in the file "LICENSE" *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

//////////////////////////////////////////////////////////////////////////////
// FairGenericParAsciiFileIo
//
// Interface class to ASCII file for input/output of parameters derived
// from FairParGenericSet
//
//////////////////////////////////////////////////////////////////////////////

#include "FairGenericParAsciiFileIo.h"

#include "FairParGenericSet.h" // for FairParGenericSet
#include "FairParSet.h"        // for FairParSet
#include "FairParamList.h"     // for FairParamObj, FairParamList

#include "TCollection.h" // for TIter
#include "TList.h"       // for TList
#include "TString.h"     // for TString, operator<<

#include <stdio.h>  // for printf, sscanf
#include <string.h> // for strcmp, memcpy, strtok, etc

using std::ios;

ClassImp(FairGenericParAsciiFileIo)

FairGenericParAsciiFileIo::FairGenericParAsciiFileIo(fstream *f)
    : FairDetParAsciiFileIo(f) {
  // constructor
  // sets the name of the I/O class "FairGenericParIo"
  // gets the pointer to the ASCII file
  fName = "FairGenericParIo";
}

Bool_t FairGenericParAsciiFileIo::init(FairParSet *pPar) {
  // initializes the parameter container from ASCII file
  if (!pFile) {
    return kFALSE;
  }

  if (pPar->InheritsFrom("FairParGenericSet")) {
    //      std::cout << "FairGenericParAsciiFileIo ##########calling read
    // function " << std::endl;
    return readGenericSet((FairParGenericSet *)pPar);
  }

  Error("init(FairParSet*)", "%s does not inherit from FairParGenericSet",
        pPar->GetName());
  return kFALSE;
}

Int_t FairGenericParAsciiFileIo::write(FairParSet *pPar) {
  // writes the parameter container to ASCII file
  if (!pFile) {
    return -1;
  }
  if (pPar->InheritsFrom("FairParGenericSet")) {
    return writeGenericSet((FairParGenericSet *)pPar);
  }
  Error("write(FairParSet*)", "%s does not inherit from FairParGenericSet",
        pPar->GetName());
  return -1;
}

template <class type>
const UChar_t *FairGenericParAsciiFileIo::readData(type t, const Char_t *format,
                                                   TString &line,
                                                   Int_t &length) {
  // reads c-type single data and arrays
  const Int_t st = sizeof(t);
  const Int_t maxbuf = 8000;
  const Int_t bufSizeExt = 10000 * st;
  const Char_t d[] = " ";
  Text_t buf[maxbuf];
  TString s;
  Int_t l = 0, bufSize = bufSizeExt;
  UChar_t *val = new UChar_t[bufSize];
  Ssiz_t m = line.Last('\\');
  if (m < 0) {
    sscanf(line.Data(), format, &t);
    memcpy(&val[l], &t, st);
    length = st;
  } else {
    do {
      pFile->getline(buf, maxbuf);
      if (buf[0] != '/' && buf[0] != '#') {
        s = buf;
        m = s.Last('\\');
        if (m > 0) {
          s = s(0, s.Length() - 2);
        }
        if ((bufSize - 1000) < l) {
          bufSize += bufSizeExt;
          UChar_t *va = new UChar_t[bufSize];
          memcpy(va, val, l);
          delete[] val;
          val = va;
        }
        Char_t *ss = strtok((Char_t *)s.Data(), d);
        while (ss != 0) {
          sscanf(ss, format, &t);
          memcpy(&val[l], &t, st);
          l += st;
          ss = strtok(NULL, d);
        }
      }
    } while (buf[0] != '#' && !pFile->eof() && m > 0);
    length = l;
  }
  return val;
}

template <class type>
void FairGenericParAsciiFileIo::writeData(type *val, Int_t nParams) {
  // writes c-type arrays
  Int_t i = 0, k = 0;
  while (k < nParams) {
    if (i == 10) {
      *pFile << " \\\n  ";
      i = 0;
    }
    *pFile << val[k] << " ";
    i++;
    k++;
  }
  *pFile << std::endl;
}

Bool_t FairGenericParAsciiFileIo::readGenericSet(FairParGenericSet *pPar) {
  // reads condition-stype parameter containers from ASCII file
  if (!pFile) {
    return kFALSE;
  }
  pFile->clear();
  pFile->seekg(0, ios::beg);
  Text_t *name = (Char_t *)pPar->GetName();

  if (!findContainer(name)) {
    return kFALSE;
  }

  FairParamList *paramList = new FairParamList;
  const Int_t maxbuf = 8000;
  Text_t buf[maxbuf];
  buf[0] = '\0';
  TString s, pName, pVal, pType;
  Ssiz_t n, m;
  while (buf[0] != '#' && !pFile->eof()) {
    pFile->getline(buf, maxbuf);
    if (buf[0] != '/' && buf[0] != '#') {
      s = buf;
      n = s.First(':');
      if (n == -1) {
        Error("readCond(FairParGenericSet*)",
              "%s:\n  Missing backslash for parameter %s", name, pName.Data());
        delete paramList;
        return kFALSE;
      }
      pName = s(0, n);
      s = s(n + 1, s.Length() - n - 1);
      s = s.Strip(s.kLeading);
      if (pName.CompareTo("author") == 0 ||
          pName.CompareTo("description") == 0) {
        m = s.Last('\\');
        if (m <= 0) {
          pVal = s;
        } else {
          pVal = s(0, m);
          pVal += "\n";
          while (m > 0) {
            pFile->getline(buf, maxbuf);
            if (buf[0] != '/') {
              s = buf;
              m = s.Last('\\');
              if (m > 0) {
                pVal += s(0, m);
                pVal += "\n";
              } else {
                pVal += s;
              }
            }
          }
        }
        if (pName.CompareTo("author") == 0) {
          pPar->setAuthor(pVal.Data());
        } else if (pName.CompareTo("description") == 0) {
          pPar->setDescription(pVal.Data());
        }
      } else {
        n = s.First(' ');
        pType = s(0, n);
        s = s(n + 1, s.Length() - n - 1);
        s = s.Strip(s.kLeading);
        if (pType.CompareTo("Text_t") == 0) {
          m = s.Last('\\');
          if (m < 0) {
            pVal = s;
          } else {
            pVal = "";
            while (m >= 0) {
              pFile->getline(buf, maxbuf);
              if (buf[0] != '/') {
                s = buf;
                m = s.Last('\\');
                if (m > 0) {
                  pVal += s(0, m);
                  pVal += "\n";
                } else {
                  pVal += s;
                }
              }
            }
          }
          pVal = pVal.Strip(pVal.kLeading);
          if (pVal.Length() > 0) {
            paramList->add(pName.Data(), pVal.Data());
          }
        } else {
          const UChar_t *val = 0;
          Int_t length = 0;
          if (pType.CompareTo("Int_t") == 0) {
            Int_t v = 0;
            val = readData(v, "%i", s, length);
          } else if (pType.CompareTo("Float_t") == 0) {
            Float_t v = 0.F;
            val = readData(v, "%f", s, length);
          } else if (pType.CompareTo("Double_t") == 0) {
            Double_t v = 0.;
            val = readData(v, "%lf", s, length);
          } else if (pType.CompareTo("Char_t") == 0) {
            Char_t v = '0';
            val = readData(v, "%c", s, length);
          } else {
            Error("readCond(FairParGenericSet*)",
                  "%s:\n  Parameter %s with unsupported type %s", name,
                  pName.Data(), pType.Data());
            delete paramList;
            return kFALSE;
          }
          FairParamObj *obj = new FairParamObj(pName.Data());
          obj->setParamType(pType.Data());
          UChar_t *pValue = obj->setLength(length);
          memcpy(pValue, val, length);
          paramList->getList()->Add(obj);
          if (val) {
            delete[] val;
          }
        }
      }
    }
  }
  Bool_t allFound = pPar->getParams(paramList);
  if (allFound) {
    pPar->setInputVersion(1, inputNumber);
    pPar->setChanged();
    printf("%s initialized from Ascii file\n", name);
  } else {
    pPar->setInputVersion(-1, inputNumber);
  }
  delete paramList;
  return allFound;
}

Int_t FairGenericParAsciiFileIo::writeGenericSet(FairParGenericSet *pPar) {
  // writes condition-stype parameter containers to ASCII file
  if (pFile) {
    //   Int_t version=1;
    const Text_t *name = pPar->GetName();
    const Text_t *context = pPar->getParamContext();
    *pFile << sepLine;
    *pFile << "# Class:   " << name << "\n# Context: " << context << "\n";
    *pFile << sepLine;
    *pFile << "[" << name << "]\n";
    writeComment(pPar);
    *pFile << "//-----------------------------------------------------------"
              "-----------------\n";
    FairParamList *paramList = new FairParamList;
    pPar->putParams(paramList);
    TList *pList = paramList->getList();
    TIter next(pList);
    FairParamObj *po;
    while ((po = (FairParamObj *)next())) {
      const Char_t *pType = po->getParamType();
      UChar_t *pValue = po->getParamValue();
      if (po->isBasicType() && strcmp(pType, "UChar_t") != 0) {
        if (strcmp(pType, "Text_t") == 0) {
          TString val((Char_t *)pValue, po->getLength());
          val.ReplaceAll("\n", " \\\n");
          *pFile << po->GetName() << ":  " << pType << " \\\n  " << val.Data()
                 << std::endl;
        } else {
          Int_t nParams = po->getNumParams();
          if (nParams == 1) {
            *pFile << po->GetName() << ":  " << pType << "  ";
          } else {
            *pFile << po->GetName() << ":  " << pType << " \\\n  ";
          }
          if (strcmp(pType, "Char_t") == 0) {
            writeData((Char_t *)pValue, nParams);
          } else if (strcmp(pType, "Int_t") == 0) {
            writeData((Int_t *)pValue, nParams);
          } else if (strcmp(pType, "Float_t") == 0) {
            writeData((Float_t *)pValue, nParams);
          } else if (strcmp(pType, "Double_t") == 0) {
            writeData((Double_t *)pValue, nParams);
          }
        }
      } else {
        Error("writeCond(FairParGenericSet*)",
              "Type %s of parameter %s not supported by ASCII I/O", pType,
              po->GetName());
        //       version=-1;
      }
    }
    *pFile << sepLine;
    delete paramList;
    pPar->setChanged(kFALSE);
    return 1;
  }
  Error("writeCond(FairParGenericSet*)", "Output is not writable");
  return -1;
}
