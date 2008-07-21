//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/03 by Ilse Koenig

///////////////////////////////////////////////////////////////////////////////
// CbmGeoInterface
//
// Manager class for geometry used by simulation

// *--15.12.04 M. Al-Turany
//  1-addInputFile(const char* name) is not used anymore 
//  2-addGeoModule(CbmGeoSet*pSet) is added 
//  3-setMediaFile(const char *file) is added 
//  3-findSet(const char* name) has been changed, no hard coding of name
//  4-nSets is now set by a method SetNoOfSets(Int_t) (see header file)

///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoInterface.h"

#include "CbmGeoIo.h"
#include "CbmGeoAsciiIo.h"
#include "CbmGeoMedia.h"
#include "CbmGeoShapes.h"
#include "CbmGeoSet.h"
#include "CbmGeoBuilder.h"
//#include "CbmGeoNode.h"

#include "TClass.h"
#include "TObjArray.h"

#include <iostream>
//#include <iomanip>
//#include <ctime>

using std::cout;
using std::endl;

ClassImp(CbmGeoInterface)

CbmGeoInterface::CbmGeoInterface() 
 :fileInput(0),
  oraInput(0),
  output(0),
  nSets(0),
  nActualSets(0),
  sets(new TObjArray()),
  media(new CbmGeoMedia()),
  shapes(new CbmGeoShapes()),
  masterNodes(new TList()),
  setupFile(""),
  geoBuilder(0)

{
  // Constructor
}

CbmGeoInterface::~CbmGeoInterface() {
  // Destructor
  if (fileInput) {
    delete fileInput;
    fileInput=0;
  }
  if (oraInput) {
    delete oraInput;
    oraInput=0;
  }
  if (output) {
    delete output;
    output=0;
  }
//  if (geoBuilder) {
//    delete geoBuilder;
//    geoBuilder=0;
//  }
  if (masterNodes) {
    masterNodes->Delete();
    delete masterNodes;
    masterNodes=0;
  }
  if (sets) {
    sets->Delete();
    delete sets;
    sets=0;
  }
  if (media) {
    delete media;
    media=0;
  }
  if (shapes) {
    delete shapes;
    shapes=0;
  }
}

void CbmGeoInterface::addGeoModule(CbmGeoSet*pSet)
{
	sets->AddLast(pSet);
	pSet->setShapes(shapes);
      	pSet->setMasterNodes(masterNodes);
	nActualSets++;

}
void CbmGeoInterface::setMediaFile(const char *file)
{
	media->setInputFile(file);
}

void CbmGeoInterface::addInputFile(const char* file) {
	
  Error("This Methode is not used any more ","Use addGeoModule to add detectors: %s",file);
/*
  // Adds the input file and creates the corresponding detector object
  CbmGeoSet* pSet=0;
  TString setName(file);
  setName.ToLower();
  Int_t l=setName.Last('/')+1;
  setName=setName(l,setName.Length()-l);
  if (setName.Contains("media")) {
    media->setInputFile(file);
  } else {
    if (setName.Contains("cave")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoCave);
      if (!pSet) {
        pSet=new CbmGeoCave;
        sets->AddAt(pSet,kCbmGeoCave);
      }
    } else if (setName.Contains("pipe")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoPipe);
      if (!pSet) {
        pSet=new CbmGeoPipe;
        sets->AddAt(pSet,kCbmGeoPipe);
      }
    } else if (setName.Contains("target")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoTarget);
      if (!pSet) {
        pSet=new CbmGeoTarget;
        sets->AddAt(pSet,kCbmGeoTarget);
      }
    } else if (setName.Contains("magnet")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoMagnet);
      if (!pSet) {
        pSet=new CbmGeoMagnet;
        sets->AddAt(pSet,kCbmGeoMagnet);
      }
    } else if (setName.Contains("rich")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoRich);
      if (!pSet) {
        pSet=new CbmGeoRich;
        sets->AddAt(pSet,kCbmGeoRich);
      }
    } else if (setName.Contains("sts")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoSts);
      if (!pSet) {
        pSet=new CbmGeoSts;
        sets->AddAt(pSet,kCbmGeoSts);
      }
    } else if (setName.Contains("trd")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoTrd);
      if (!pSet) {
        pSet=new CbmGeoTrd;
        sets->AddAt(pSet,kCbmGeoTrd);
      }
    } else if (setName.Contains("tof")) {
      pSet=(CbmGeoSet*)sets->At(kCbmGeoTof);
      if (!pSet) {
        pSet=new CbmGeoTof;
        sets->AddAt(pSet,kCbmGeoTof);
      }
    } else Error("addInputFile","Unknown detector set: %s",file);
    if (pSet) {
      pSet->setShapes(shapes);
      pSet->setMasterNodes(masterNodes);
      pSet->setGeomFile(file);
      nActualSets++;
    }
  }
  */
}

CbmGeoSet* CbmGeoInterface::findSet(const char* name) {
  // Find the detector set in the actual setup
  CbmGeoSet* pSet=0;
  TString setName(name);
  TString PSetName;
  setName.ToLower();
  Int_t l=setName.Last('/')+1;
  setName=setName(l,setName.Length()-l);
/*  if (setName.Contains("cave"))        pSet=(CbmGeoSet*)sets->At(kCbmGeoCave);
  else if (setName.Contains("pipe"))   pSet=(CbmGeoSet*)sets->At(kCbmGeoPipe);
  else if (setName.Contains("target")) pSet=(CbmGeoSet*)sets->At(kCbmGeoTarget);
  else if (setName.Contains("magnet"))  pSet=(CbmGeoSet*)sets->At(kCbmGeoMagnet);
  else if (setName.Contains("rich"))   pSet=(CbmGeoSet*)sets->At(kCbmGeoRich);
  else if (setName.Contains("sts"))    pSet=(CbmGeoSet*)sets->At(kCbmGeoSts);
  else if (setName.Contains("trd"))    pSet=(CbmGeoSet*)sets->At(kCbmGeoTrd);
  else if (setName.Contains("tof"))    pSet=(CbmGeoSet*)sets->At(kCbmGeoTof);
  else if (setName.Contains("ecal")) pSet=(CbmGeoSet*)sets->At(kCbmGeoEcal);
  return pSet;
  */
  for(Int_t i=0;i<nSets;i++){
  	PSetName=sets->At(i)->GetName();
	if (PSetName.Contains(setName.Data())){
		pSet=(CbmGeoSet*)sets->At(i);
		cout << "CbmGeoInterface::findSet" <<pSet->GetName() <<endl;
		break;
	}
  
  }
  return pSet;
  
}

Bool_t CbmGeoInterface::readSet(CbmGeoSet* pSet) {
  // Reads the geometry for the detector part
  Bool_t rc=kFALSE;
  CbmGeoIo* input=0;
  if (pSet) {
    input=connectInput(pSet->getGeomFile());
    if (input) rc=input->read(pSet,media);
  }
  return rc;
}

Bool_t CbmGeoInterface::writeSet(CbmGeoSet* pSet) {
  // Writes the geometry for the detector part to output
  if (pSet&&connectOutput(pSet->GetName())) return output->write(pSet);
  return kFALSE;
}

Bool_t CbmGeoInterface::writeSet(CbmGeoSet* pSet, const char* filename) {
  // Writes the geometry for the detector part to file
  if (pSet&&output) {
    output->open(filename,"out");
    if (output->isOpen()) return output->write(pSet);
  }
  return kFALSE;
}

void CbmGeoInterface::deleteSet(CbmGeoSet* pSet) {
  // Deletes the set
  if (pSet) {
    sets->Remove(pSet);
    delete pSet;
    pSet=0;
  }
}

Bool_t CbmGeoInterface::readMedia() {
  // Reads the media
  Bool_t rc=kFALSE;
  CbmGeoIo* input=connectInput(media->getInputFile());
  if (input) {
    rc=input->read(media);
  }
  return rc;  
}

Bool_t CbmGeoInterface::writeMedia() {
  // Writes the media to output
  if (connectOutput("media")) return output->write(media);
  return kFALSE;
}

Bool_t CbmGeoInterface::writeMedia(const char* filename) {
  // Writes the media to file
  if (output) {
    output->open(filename,"out");
    if (output->isOpen()) return output->write(media);
  }
  return kFALSE;
}

Bool_t CbmGeoInterface::readAll() {
  // Reads the media and the whole geometry
  Bool_t rc=kTRUE;
  if (nActualSets==0&&oraInput) {
    rc=oraInput->readGeomConfig(this);
//  if (rc) addInputFile("media_gdb");
    if (rc) addInputFile("media_gdb");
  } 
  if(rc) rc=readSetupFile();
  if(rc) rc=readMedia();  
  CbmGeoSet* pSet=0;
  for(Int_t i=0;i<nSets&&rc;i++) {
    pSet=(CbmGeoSet*)sets->At(i);
    if (pSet) {
      cout<<"Read "<<pSet->GetName()<<endl;
      rc=readSet(pSet);
    }
  }
  return rc;
}

Bool_t CbmGeoInterface::writeAll() {
  // Reads the media and the whole geometry to output
  Bool_t rc=kTRUE;
  CbmGeoSet* pSet=0;
  rc=writeMedia();
  for(Int_t i=0;i<nSets&&rc;i++) {
    pSet=(CbmGeoSet*)sets->At(i);
    if (pSet) rc=writeSet(pSet);
  }
  return rc;
}

Bool_t CbmGeoInterface::createAll(Bool_t withCleanup) {
  // Creates the whole geometry
  // (if withCleanup==kTRUE, the geometry input is deleted afterwards)
  Bool_t rc=kTRUE;
  Int_t n=0;  
  if (geoBuilder) {
    CbmGeoSet* pSet=0;
    for(Int_t i=0;i<nSets&&rc;i++) {
      pSet=(CbmGeoSet*)sets->At(i);
      if (pSet) {
        cout<<"Create "<<pSet->GetName()<<endl;
        rc=pSet->create(geoBuilder);
        n++;
        if (withCleanup) {
          sets->RemoveAt(i);
          delete pSet;
        }
      }
    }
    if (rc&&n>0) geoBuilder->finalize();
  } else Error("createAll()","No Builder");
  return rc;
}

Bool_t CbmGeoInterface::createGeometry(Bool_t withCleanup) {
  // Reads and creates the whole geometry
  // (if withCleanup==kTRUE, the geometry input is deleted after creation)
  Bool_t rc=kTRUE;  
  Int_t n=0;  
  if (geoBuilder) {
    if (nActualSets==0&&oraInput) {
      rc=oraInput->readGeomConfig(this);
      if (rc) addInputFile("media_gdb");
    }
    if (rc) rc=readSetupFile();
    if (rc) rc=readMedia();
    CbmGeoSet* pSet=0;
    for(Int_t i=0;i<nSets&&rc;i++) {
      pSet=(CbmGeoSet*)sets->At(i);
      if (pSet) {
	cout<<"Read and create "<<pSet->GetName()<<endl;
        rc=readSet(pSet);
        if (rc) {
          rc=pSet->create(geoBuilder);
          n++;
        }
        if (withCleanup) {
          sets->RemoveAt(i);
          delete pSet;
        }
      }
    }
    if (rc&&n>0) geoBuilder->finalize();
  } else Error("createAll()","No Builder");
  return rc;
}

CbmGeoIo* CbmGeoInterface::connectInput(const char* filename) {
  // Connects the input (ASCII or Oracle)
  CbmGeoIo* currentIo=0;
  if (filename) {
    TString s(filename);
    s=s.Strip();
    if (s.EndsWith(".dat")||s.EndsWith(".geo")||s.EndsWith(".setup")) {
      if (!fileInput) fileInput=new CbmGeoAsciiIo();
      fileInput->open(filename);
      currentIo=fileInput;
    } else if (s.EndsWith("_gdb")) currentIo=oraInput;
  }
  if (currentIo && currentIo->isOpen()) return currentIo;
  return 0; 
}

Bool_t CbmGeoInterface::connectOutput (const char* name) {
  // Connects the output (ASCII or Oracle)
  if (output) {
    if (strcmp(output->IsA()->GetName(),"CbmGeoAsciiIo")==0) {
      TString fName(name);
      char buf[80];
      struct tm* newtime;
      time_t t;
      time(&t);
      newtime=localtime(&t);
      if (newtime->tm_mday<10) sprintf(buf,"_0%i",newtime->tm_mday);
      else sprintf(buf,"_%i",newtime->tm_mday);
      fName=fName+buf;
      if (newtime->tm_mon<9) sprintf(buf,"0%i",newtime->tm_mon+1);
      else sprintf(buf,"%i",newtime->tm_mon+1);
      fName=fName+buf;
      Int_t y=newtime->tm_year-100;
      if (y<10) sprintf(buf,"0%i",y);
      else sprintf(buf,"%i",y);
      fName=fName+buf;
      if (newtime->tm_hour<10) sprintf(buf,"0%i",newtime->tm_hour);
      else sprintf(buf,"%i",newtime->tm_hour);
      fName=fName+buf;
      if (newtime->tm_min<10) sprintf(buf,"0%i",newtime->tm_min);
      else sprintf(buf,"%i",newtime->tm_min);
      fName=fName+buf;
      if (newtime->tm_sec<10) sprintf(buf,"0%i",newtime->tm_sec);
      else sprintf(buf,"%i",newtime->tm_sec);
      fName=fName+buf+".geo";
      output->open(fName,"out");
      cout<<"Output file for "<<name<<":  "
          <<((CbmGeoAsciiIo*)output)->getFilename()<<endl;
    }
    if (output->isOpen()&&output->isWritable()) return kTRUE;
  } else Error("connectOutput","No output open");
  return kFALSE;
}

Bool_t CbmGeoInterface::createSet(CbmGeoSet* pSet) {
  // Creates the geometry of detector part
  if (!geoBuilder) return kFALSE;
  return pSet->create(geoBuilder);
}

void CbmGeoInterface::print() {
  // Prints the media and the list of detector parts
  media->list();
  cout<<"********************************************************************\n";
  cout<<"List of detector parts:\n";
  CbmGeoSet* pSet=0;
  for(Int_t i=0;i<nSets;i++) {
    pSet=(CbmGeoSet*)sets->At(i);
    if (pSet) cout<<"  "<<pSet->GetName()<<":\t"<<pSet->getGeomFile()<<'\n';
  }
  cout<<"********************************************************************\n";
}

Bool_t CbmGeoInterface::readGeomConfig(const char* configFile) {
  // Reads the GEANT configuration file
  Bool_t rc=kFALSE;
  CbmGeoIo* input=0;
  if (configFile) {
    input=connectInput(configFile);
    if (input) rc=input->readGeomConfig(this);
  }
  return rc;
}

Bool_t CbmGeoInterface::readSetupFile() {
  // Reads the detector setups, needed for create only subsets
  Bool_t rc=kTRUE;
  if (setupFile.Length()>0) {
    CbmGeoAsciiIo* input=(CbmGeoAsciiIo*)(connectInput(setupFile));
    if (input) rc=input->readDetectorSetup(this);
  }
  return rc;
}


