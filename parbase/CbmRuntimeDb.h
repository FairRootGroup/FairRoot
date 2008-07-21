#ifndef CBMRUNTIMEDB_H
#define CBMRUNTIMEDB_H

#include "TObject.h"
#include "TList.h"

class CbmParIo;
class CbmParSet;
class CbmRtdbRun;
class CbmContFact;

static TList contFactories;    //! list of container factories 

class CbmRuntimeDb : public TObject {
private:
  static CbmRuntimeDb* gRtdb; //!
protected:
  CbmRuntimeDb(void);
  TList* containerList;    // list of parameter containers
  TList* runs;             // list of runs
  CbmParIo* firstInput;    // first (prefered) input for parameters
  CbmParIo* secondInput;   // second input (used if not found in first input)
  CbmParIo* output;        // output for parameters
  CbmRtdbRun* currentRun;  // Current run
  TString currentFileName; // Name of current event file
  Bool_t versionsChanged;  // flag for write of list of runs (set kTRUE by each write)
  Bool_t isRootFileOutput; // flag indicating that the output is a ROOT file
public:
  static CbmRuntimeDb* instance(void);
  ~CbmRuntimeDb(void);

  Bool_t addParamContext(const char*);
  void printParamContexts();
  void addContFactory(CbmContFact*);

  Bool_t addContainer(CbmParSet*);
  CbmParSet* getContainer(Text_t*);
  CbmParSet* findContainer(const char*);
  void removeContainer(Text_t*);
  void removeAllContainers(void);
  Bool_t initContainers(Int_t runId,Int_t refId=-1,const Text_t* fileName="");
  void setContainersStatic(Bool_t f=kTRUE);
  Bool_t writeContainers(void);
  Bool_t writeContainer(CbmParSet*,CbmRtdbRun*,CbmRtdbRun* refRun=0);

  CbmRtdbRun* addRun(Int_t runId,Int_t refId=-1);
  CbmRtdbRun* getRun(Int_t);
  CbmRtdbRun* getRun(Text_t*);
  CbmRtdbRun* getCurrentRun(void) {return currentRun;}
  Text_t const *getCurrentFileName() {return currentFileName.Data();}
  void clearRunList(void);

  void removeRun(Text_t*);

  Bool_t setInputVersion(Int_t run,Text_t* container,
                        Int_t version,Int_t inputNumber);
  Bool_t setRootOutputVersion(Int_t run,Text_t* container,Int_t version);
  void setVersionsChanged(Bool_t f=kTRUE) {versionsChanged=f;}
  void resetInputVersions(void);
  void resetOutputVersions(void);
  void resetAllVersions(void);

  Bool_t readAll(void);
  void writeVersions(void);
  void saveOutput(void);

  Bool_t setFirstInput(CbmParIo*);
  Bool_t setSecondInput(CbmParIo*);
  Bool_t setOutput(CbmParIo*);
  CbmParIo* getFirstInput(void);
  CbmParIo* getSecondInput(void);
  CbmParIo* getOutput(void);
  void closeFirstInput(void);
  void closeSecondInput(void);
  void closeOutput(void);
  void activateParIo(CbmParIo*);

  void print(void);

  Int_t findOutputVersion(CbmParSet*);

private:
  CbmRuntimeDb(const CbmRuntimeDb &M);
  CbmRuntimeDb& operator= (const  CbmRuntimeDb&) {return *this;}
  Bool_t initContainers(void);

  ClassDef(CbmRuntimeDb,0) // Class for runtime database
};

#endif  /* !CBMRUNTIMEDB_H */
