//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

//////////////////////////////////////////////////////////////////////////////
// CbmGenericParAsciiFileIo
//
// Interface class to ASCII file for input/output of parameters derived
// from CbmParGenericSet
//
//////////////////////////////////////////////////////////////////////////////

#include "CbmGenericParAsciiFileIo.h"

#include "CbmParGenericSet.h"
#include "CbmParamList.h"

//#include "TClass.h"

using std::ios;

ClassImp(CbmGenericParAsciiFileIo)

CbmGenericParAsciiFileIo::CbmGenericParAsciiFileIo(fstream* f) : CbmDetParAsciiFileIo(f) {
  // constructor
  // sets the name of the I/O class "CbmGenericParIo"
  // gets the pointer to the ASCII file
  fName="CbmGenericParIo";
}

Bool_t CbmGenericParAsciiFileIo::init(CbmParSet* pPar) {
  // initializes the parameter container from ASCII file
  if (!pFile) return kFALSE; 
  if (pPar->InheritsFrom("CbmParGenericSet"))
      return readGenericSet((CbmParGenericSet*)pPar);
  Error("init(CbmParSet*)",
        "%s does not inherit from CbmParGenericSet",pPar->GetName());
  return kFALSE;
}

Int_t CbmGenericParAsciiFileIo::write(CbmParSet* pPar) {
  // writes the parameter container to ASCII file
  if (!pFile) return -1; 
  if (pPar->InheritsFrom("CbmParGenericSet"))
      return writeGenericSet((CbmParGenericSet*)pPar);
  Error("write(CbmParSet*)",
        "%s does not inherit from CbmParGenericSet",pPar->GetName());
  return -1;
}

Bool_t CbmGenericParAsciiFileIo::readGenericSet(CbmParGenericSet* pPar) {
  pFile->clear();
  pFile->seekg(0,ios::beg);
  Text_t* name=(char*)pPar->GetName();
  if (!findContainer(name)) return kFALSE;
  CbmParamList* paramList = new CbmParamList;
  const Int_t maxbuf=8000;
  Text_t buf[maxbuf];
  buf[0]='\0';
  TString s, pName, pVal, pType;
  Bool_t isBinary=kFALSE;
  while (buf[0]!='#' && !pFile->eof()) {             
    pFile->getline(buf,maxbuf);
    if (buf[0]!='/' && buf[0]!='#') {
      s=buf;
      Ssiz_t n=s.First(':');
      if (n==-1) {
	  Error("readGenericSet",
                "Error in Ascii File input for parameter container %s Missing backslash for parameter %s",
                name,pName.Data());
        return  kFALSE;
      } 
      Ssiz_t m=s.Last('\\');
      pName=s(0,n);
      if (m>0) s=s(n+1,m-n-1);
      else s=s(n+1,s.Length()-n-1);
      s=s.Strip(s.kLeading);
      if (pName.CompareTo("author")==0
          || pName.CompareTo("description")==0) pType='s';
      else {
        pType=s[0];
        if (s.Length()>1 && s[1]=='B') {
          isBinary=kTRUE;
          pType+="Bin";
        } else {
          s=s(1,s.Length()-1);
          s=s.Strip(s.kLeading);
        }
      }
      if (!isBinary) {
        if (!(pType[0]=='i'||pType[0]=='f'||pType[0]=='d'
	      ||pType[0]=='l'||pType[0]=='s')) {
	  Error("readGenericSet","%s : Unsupported type %s",pName.Data(),pType.Data());
          delete paramList;
          return kFALSE;
        }
        if (pType[0]=='s') {
          pVal=s;
          if (m>0) pVal+="\n";
        }
        else pVal=s.ReplaceAll(" ","");
        while (m>0) {
          pFile->getline(buf,maxbuf);
          if (buf[0]!='/') {
            s=buf;
            if (pType[0]!='s') s=s.ReplaceAll(" ","");
            m=s.Last('\\');
            if (m>0) {
              pVal+=s(0,m);
              if (pType[0]=='s') pVal+="\n";
            }
            else pVal+=s;
          }
        }
        Int_t nVal=1;
        if (pType[0]!='s' )
          for(Int_t i=0;i<pVal.Length();i++) { if (pVal[i]==',') nVal++; }
        paramList->add(pName.Data(),pVal.Data(),pType[0],nVal);
      } else {
        UChar_t* val=0;
        Int_t length=0;
    	if (pType.CompareTo("hBin")==0) {
            Short_t v=0;
            val=readArray(v,"%hi",length);
            if (val && length>0)
              paramList->addBinary(pName.Data(),(Short_t*)val,length/sizeof(Short_t));
        } else if (pType.CompareTo("iBin")==0) {
            Int_t v=0;
            val=readArray(v,"%i",length);
            if (val && length>0)
              paramList->addBinary(pName.Data(),(Int_t*)val,length/sizeof(Int_t));
        } else if  (pType.CompareTo("fBin")==0){
            Float_t v=0;
            val=readArray(v,"%f",length);
            if (val && length>0)
              paramList->addBinary(pName.Data(),(Float_t*)val,length/sizeof(Float_t));
        } else if (pType.CompareTo("dBin")==0) {
            Double_t v=0;
            val=readArray(v,"%lf",length);
            if (val && length>0)
              paramList->addBinary(pName.Data(),(Double_t*)val,length/sizeof(Double_t));
        } else {
	  Error("readGenericSet","%s : Unsupported type %s",pName.Data(),pType.Data());
          delete paramList;
          return kFALSE;
	}
        if (val) delete [] val;
      }
    }
  }
  CbmParamObj* p=paramList->find("author");
  if (p) pPar->setAuthor(p->getParamValue());
  p=paramList->find("description");
  if (p) pPar->setDescription(p->getParamValue());
  Bool_t allFound=pPar->getParams(paramList);
  if (allFound) { 
    pPar->setInputVersion(1,inputNumber);
    pPar->setChanged();
    printf("%s initialized from Ascii file\n",name);
  } else pPar->setInputVersion(-1,inputNumber);
  delete paramList;
  return allFound;  
}

template <class type> UChar_t* CbmGenericParAsciiFileIo::readArray(
              type t,const char* format,Int_t& length) {
  const Int_t st=sizeof(t);
  const Int_t maxbuf=8000;
  const Int_t bufSizeExt=10000*st;
  const char d[]=",";
  Text_t buf[maxbuf];
  Int_t m=1, l=0, bufSize=bufSizeExt ;
  UChar_t* val=new UChar_t[bufSize];
  do {             
    pFile->getline(buf,maxbuf);
    if (buf[0]!='/' && buf[0]!='#') {
      TString s=buf;
      s=s.ReplaceAll(" ","");
      m=s.Last('\\');
      if (m>0) s=s(0,s.Length()-2);
      if ((bufSize-1000)<l) {
        bufSize+=bufSizeExt;
        UChar_t* va=new UChar_t[bufSize];
        memcpy(va,val,l);
        delete [] val;
        val=va;
      }
      char* ss=strtok((char*)s.Data(),d);
      while (ss!=0) {
        sscanf(ss,format,&t);
        memcpy(&val[l],&t,st);
        l+=st;
        ss=strtok(NULL,d);
      }
    }
  } while (buf[0]!='#' && !pFile->eof() && m>0);
  length=l;
  return val;
}

Int_t CbmGenericParAsciiFileIo::writeGenericSet(CbmParGenericSet* pPar) {
  const Text_t* name=pPar->GetName();
  const Text_t* context=pPar->getParamContext();
  *pFile<<sepLine;
  *pFile<<"# Class:   "<<name<<"\n# Context: "<<context<<"\n";
  *pFile<<sepLine;
  *pFile<<"["<<name<<"]\n";
  writeComment(pPar);
  *pFile<<"//-----------------------------------------------------------"
          "-----------------\n";
  CbmParamList* paramList = new CbmParamList;
  pPar->putParams(paramList);
  TList* pList=paramList->getList();
  TIter next(pList);
  CbmParamObj* po;
  while ((po=(CbmParamObj*)next())) {
    char pType=po->getParamType();
    if (po->getNumParams() == 1) {
      *pFile<<po->GetName()<<":  "<<pType<<"  "<<po->getParamValue()<<"\n";
    } else {
      *pFile<<po->GetName()<<":  "<<pType<<" \\\n";
      TString s=po->getParamValue();
      if (pType=='s') s.ReplaceAll("\n"," \\\n");
      else {
        s.ReplaceAll(",",", ");
        TString ss;
        Ssiz_t l;
        do {
          l=s.Length();
          if (l>76) {
            ss=s(0,76);
            Ssiz_t n=ss.Last(' '); 
            ss=s(0,n);                  
            s=s(n+1,l);
            ss+=" \\";
          } else ss=s;
          *pFile<<"  "<<ss<<"\n";
        } while (l>76);
      }
    }
  }
  TList* pBinList=paramList->getBinaryList();
  TIter nextBin(pBinList);
  CbmParamBinObj* pbo;
  while ((pbo=(CbmParamBinObj*)nextBin())) {
    TString paramType=pbo->getParamType();
    *pFile<<pbo->GetName()<<":  "<<paramType<<" \\\n";
    Int_t l=0, i=0, k=0;
    TString format;
    if (paramType.CompareTo("hBin")==0) {
      l=pbo->getLength()/sizeof(Int_t);
      Int_t* paramValue=(Int_t*)pbo->getParamValue();
      while (k<l-1) {
        *pFile<<paramValue[k]<<", ";
        i++;
        k++;  
        if (i==10) {
          *pFile<<"\\\n";
          i=0;
        }
      }
      *pFile<<paramValue[l-1]<<"\n";
    } else if (paramType.CompareTo("iBin")==0) {
      l=pbo->getLength()/sizeof(Int_t);
      Int_t* paramValue=(Int_t*)pbo->getParamValue();
      while (k<l-1) {
        *pFile<<paramValue[k]<<", ";
        i++;
        k++;  
        if (i==10) {
          *pFile<<"\\\n";
          i=0;
        }
      }
      *pFile<<paramValue[l-1]<<"\n";
    } else if (paramType.CompareTo("fBin")==0) {
      l=pbo->getLength()/sizeof(Float_t);
      Float_t* paramValue=(Float_t*)pbo->getParamValue();
      while (k<l-1) {
        *pFile<<paramValue[k]<<", ";
        i++;
        k++;
        if (i==10) {
          *pFile<<"\\\n";
          i=0;
        }
      }
      *pFile<<paramValue[l-1]<<"\n";
    } else if (paramType.CompareTo("dBin")==0) {
      l=pbo->getLength()/sizeof(Double_t);
      Double_t* paramValue=(Double_t*)pbo->getParamValue();
      while (k<l-1) {
        *pFile<<paramValue[k]<<", ";
        i++;
        k++;  
        if (i==10) {
          *pFile<<"\\\n";
          i=0;
        }
      }
      *pFile<<paramValue[l-1]<<"\n";
    } else {
      Error("writeGenericSet(CbmParGenericSet*)",
            "Type %s of parameter %s not supported by ASCII I/O",
            paramType.Data(),pbo->GetName());
      return -1;
    }
  }
  *pFile<<sepLine;
  delete paramList;
  pPar->setChanged(kFALSE);
  return 1;
}  
