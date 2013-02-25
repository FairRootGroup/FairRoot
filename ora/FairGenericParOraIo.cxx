
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
struct sql_cursor {
  unsigned int curocn;
  void* ptr1;
  void* ptr2;
  unsigned int magic;
};
typedef struct sql_cursor sql_cursor;
typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void* sql_context;
typedef void* SQL_CONTEXT;

/* Object support */
struct sqltvn {
  unsigned char* tvnvsn;
  unsigned short tvnvsnl;
  unsigned char* tvnnm;
  unsigned short tvnnml;
  unsigned char* tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts {
  unsigned int adtvsn;
  unsigned short adtmode;
  unsigned short adtnum;
  sqltvn adttvn[1];
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss {
  unsigned int tdsvsn;
  unsigned short tdsnum;
  unsigned char* tdsval[1];
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds = {
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp {
  unsigned short fillen;
  char  filnam[22];
};
static const struct sqlcxp sqlfpn = {
  21,
  "FairGenericParOraIo.pc"
};


static unsigned int sqlctx = 143820995;


static struct sqlexd {
  unsigned int   sqlvsn;
  unsigned int   arrsiz;
  unsigned int   iters;
  unsigned int   offset;
  unsigned short selerr;
  unsigned short sqlety;
  unsigned int   occurs;
  const short* cud;
  unsigned char*  sqlest;
  const char*  stmt;
  sqladts* sqladtp;
  sqltdss* sqltdsp;
  void**  sqphsv;
  unsigned int*   sqphsl;
  int*   sqphss;
  void**  sqpind;
  int*   sqpins;
  unsigned int*   sqparm;
  unsigned int**   sqparc;
  unsigned short*  sqpadto;
  unsigned short*  sqptdso;
  unsigned int   sqlcmax;
  unsigned int   sqlcmin;
  unsigned int   sqlcincr;
  unsigned int   sqlctimeout;
  unsigned int   sqlcnowait;
  int   sqfoff;
  unsigned int   sqcmod;
  unsigned int   sqfmod;
  void*  sqhstv[10];
  unsigned int   sqhstl[10];
  int   sqhsts[10];
  void*  sqindv[10];
  int   sqinds[10];
  unsigned int   sqharm[10];
  unsigned int*   sqharc[10];
  unsigned short  sqadto[10];
  unsigned short  sqtdso[10];
} sqlstm = {12,10};

// Prototypes
extern "C" {
  void sqlcxt (void**, unsigned int*,
               struct sqlexd*, const struct sqlcxp*);
  void sqlcx2t(void**, unsigned int*,
               struct sqlexd*, const struct sqlcxp*);
  void sqlbuft(void**, char*);
  void sqlgs2t(void**, char*);
  void sqlorat(void**, unsigned int*, void*);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(char*, int*); }

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] = {
  12,4130,1,0,0,
  5,0,0,1,340,0,4,94,0,0,10,1,0,1,0,2,9,0,0,2,9,0,0,2,9,0,0,2,3,0,0,2,3,0,0,2,3,
  0,0,2,3,0,0,2,4,0,0,2,4,0,0,1,3,0,0,
  60,0,0,2,93,0,6,162,0,0,4,4,0,1,0,1,3,0,0,3,68,0,0,2,68,0,0,2,23,0,0,
  91,0,0,3,91,0,6,174,0,0,3,3,0,1,0,3,68,0,0,1,68,0,0,2,23,0,0,
  118,0,0,4,392,0,6,221,0,0,6,6,0,1,0,3,3,0,0,1,97,0,0,1,97,0,0,3,3,0,0,1,97,0,0,
  1,97,0,0,
  157,0,0,5,180,0,3,293,0,0,8,8,0,1,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
  1,3,0,0,1,3,0,0,1,3,0,0,
  204,0,0,6,202,0,3,324,0,0,9,9,0,1,0,1,3,0,0,1,97,0,0,1,97,0,0,1,97,0,0,1,3,0,0,
  1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
  255,0,0,7,97,0,6,363,0,0,4,4,0,1,0,1,3,0,0,1,3,0,0,1,23,0,0,2,3,0,0,
  286,0,0,8,103,0,6,373,0,0,4,4,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,23,0,0,
  317,0,0,9,0,0,31,384,0,0,0,0,0,1,0,
  332,0,0,10,228,0,4,415,0,0,8,1,0,1,0,2,9,0,0,2,9,0,0,2,3,0,0,2,9,0,0,2,3,0,0,2,
  3,0,0,2,3,0,0,1,3,0,0,
  379,0,0,11,98,0,6,479,0,0,4,4,0,1,0,1,3,0,0,3,68,0,0,2,68,0,0,2,23,0,0,
  410,0,0,12,91,0,6,491,0,0,3,3,0,1,0,3,68,0,0,1,68,0,0,2,23,0,0,
};


//*-- AUTHOR : Ilse Koenig
//*-- Created : 26/11/2004

//////////////////////////////////////////////////////////////////////////////
// FairGenericParOraIo
//
// Interface class to database Oracle for input/output of generic parameter
// containers
//////////////////////////////////////////////////////////////////////////////

#include "FairGenericParOraIo.h"
#include "FairParGenericSet.h"
#include "FairParamList.h"
#include "TClass.h"

#define SQLCA_STORAGE_CLASS extern
#define ORACA_STORAGE_CLASS extern

// Oracle communication area
#include "oraca.h"
// Include the SQL Communications Area
#include "sqlca.h"

ClassImp(FairGenericParOraIo)

#define NMAX_PARAM 200
#define LOB_BUFSIZE 32512

FairGenericParOraIo::FairGenericParOraIo(FairOraConn* pC) : FairDetParOraIo(pC)
{
  // constructor
  // sets the name of the I/O class "FairGenericParIo"
  // gets the pointer to the connection class
  fName="FairGenericParIo";
}

Bool_t FairGenericParOraIo::init(FairParSet* pPar,Int_t* set)
{
  // calls read(FairParGenericSet*,Int_t*)
  if (pPar->InheritsFrom("FairParGenericSet")) { return read((FairParGenericSet*)pPar); }
  Error("FairGenericParOraIo::init(FairParSet*,Int_t*)",
        "%s does not inherit from FairParGenericSet",pPar->GetName());
  return kFALSE;
}

Int_t FairGenericParOraIo::write(FairParSet* pPar)
{
  // calls write(FairParGenericSet*)
  Int_t runStart=getRunStart(pPar);
  if (runStart<=0) { return -1; }
  if (pPar->InheritsFrom("FairParGenericSet")) { return writeSet((FairParGenericSet*)pPar); }
  Error("FairGenericParOraIo::write(FairParSet*)",
        "%s does not inherit from FairParGenericSet",pPar->GetName());
  return -1;
}

Bool_t FairGenericParOraIo::read(FairParGenericSet* pPar)
{
  // reads the parameters and fills the container
  Int_t runStart=getRunStart(pPar);
  FairParOraSet* pSet=getOraSet(pPar);
  if (pSet->contextId==-1 || runStart==-1) {
    pPar->setInputVersion(-1,inputNumber);
    return kFALSE;
  }
  Int_t contVers=pPar->getInputVersion(inputNumber);
  if (contVers!=-1 && runStart>=pSet->versDate[0] && runStart<=pSet->versDate[1]) {
    return contVers;
  }
  pSet->clearVersDate();
  /* EXEC SQL BEGIN DECLARE SECTION; */

  int id;
  struct {
    /* varchar p_name[NMAX_PARAM][81]; */
    struct { unsigned short len; unsigned char arr[82]; } p_name[200];

    /* varchar p_value[NMAX_PARAM][4001]; */
    struct { unsigned short len; unsigned char arr[4002]; } p_value[200];

    /* varchar p_type[NMAX_PARAM][81]; */
    struct { unsigned short len; unsigned char arr[82]; } p_type[200];

    int     p_is_binary[NMAX_PARAM];
    int     p_is_basic[NMAX_PARAM];
    int     p_class_vers[NMAX_PARAM];
    int     p_num[NMAX_PARAM];
    double  p_since[NMAX_PARAM];
    double  p_until[NMAX_PARAM];
  } ana;
  struct {
    short p_name_Ind[NMAX_PARAM];
    short p_value_Ind[NMAX_PARAM];
    short p_type_Ind[NMAX_PARAM];
    short p_is_binary_Ind[NMAX_PARAM];
    short p_is_basic_Ind[NMAX_PARAM];
    short p_class_vers_Ind[NMAX_PARAM];
    short p_num_Ind[NMAX_PARAM];
    short p_since_Ind[NMAX_PARAM];
    short p_until_Ind[NMAX_PARAM];
  } ana_Ind;
  /* EXEC SQL END DECLARE SECTION; */

  /* EXEC SQL WHENEVER SQLERROR DO showSqlError("read(FairParGenericSet*)"); */

  /* EXEC SQL WHENEVER NOT FOUND CONTINUE; */

  id=pSet->contextId;
  /* EXEC SQL SELECT par_name, par_value, par_value_type, is_binary, is_basic_type,
                  class_version, n_values,
                  cbmdate.to_ansitime(valid_since), cbmdate.to_ansitime(valid_until)
           INTO :ana INDICATOR :ana_Ind
           FROM cbm_ana.param_values_at_histdate_ext
           WHERE param_context_id = :id
           ORDER BY par_value_id; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select par_name ,par_value ,par_value_type ,is_binary ,is_b\
asic_type ,class_version ,n_values ,cbmdate.to_ansitime(valid_since) ,cbmdate.\
to_ansitime(valid_until) into :s1:s2 ,:s3:s4 ,:s5:s6 ,:s7:s8 ,:s9:s10 ,:s11:s1\
2 ,:s13:s14 ,:s15:s16 ,:s17:s18   from cbm_ana.param_values_at_histdate_ext wh\
ere param_context_id=:b2 order by par_value_id ";
    sqlstm.iters = (unsigned int  )200;
    sqlstm.offset = (unsigned int  )5;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void*)ana.p_name;
    sqlstm.sqhstl[0] = (unsigned int  )83;
    sqlstm.sqhsts[0] = (         int  )84;
    sqlstm.sqindv[0] = (         void*)ana_Ind.p_name_Ind;
    sqlstm.sqinds[0] = (         int  )sizeof(short);
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqharc[0] = (unsigned int*)0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void*)ana.p_value;
    sqlstm.sqhstl[1] = (unsigned int  )4003;
    sqlstm.sqhsts[1] = (         int  )4004;
    sqlstm.sqindv[1] = (         void*)ana_Ind.p_value_Ind;
    sqlstm.sqinds[1] = (         int  )sizeof(short);
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqharc[1] = (unsigned int*)0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void*)ana.p_type;
    sqlstm.sqhstl[2] = (unsigned int  )83;
    sqlstm.sqhsts[2] = (         int  )84;
    sqlstm.sqindv[2] = (         void*)ana_Ind.p_type_Ind;
    sqlstm.sqinds[2] = (         int  )sizeof(short);
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqharc[2] = (unsigned int*)0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void*)ana.p_is_binary;
    sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[3] = (         int  )sizeof(int);
    sqlstm.sqindv[3] = (         void*)ana_Ind.p_is_binary_Ind;
    sqlstm.sqinds[3] = (         int  )sizeof(short);
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqharc[3] = (unsigned int*)0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void*)ana.p_is_basic;
    sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[4] = (         int  )sizeof(int);
    sqlstm.sqindv[4] = (         void*)ana_Ind.p_is_basic_Ind;
    sqlstm.sqinds[4] = (         int  )sizeof(short);
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqharc[4] = (unsigned int*)0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (         void*)ana.p_class_vers;
    sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[5] = (         int  )sizeof(int);
    sqlstm.sqindv[5] = (         void*)ana_Ind.p_class_vers_Ind;
    sqlstm.sqinds[5] = (         int  )sizeof(short);
    sqlstm.sqharm[5] = (unsigned int  )0;
    sqlstm.sqharc[5] = (unsigned int*)0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqhstv[6] = (         void*)ana.p_num;
    sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[6] = (         int  )sizeof(int);
    sqlstm.sqindv[6] = (         void*)ana_Ind.p_num_Ind;
    sqlstm.sqinds[6] = (         int  )sizeof(short);
    sqlstm.sqharm[6] = (unsigned int  )0;
    sqlstm.sqharc[6] = (unsigned int*)0;
    sqlstm.sqadto[6] = (unsigned short )0;
    sqlstm.sqtdso[6] = (unsigned short )0;
    sqlstm.sqhstv[7] = (         void*)ana.p_since;
    sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
    sqlstm.sqhsts[7] = (         int  )sizeof(double);
    sqlstm.sqindv[7] = (         void*)ana_Ind.p_since_Ind;
    sqlstm.sqinds[7] = (         int  )sizeof(short);
    sqlstm.sqharm[7] = (unsigned int  )0;
    sqlstm.sqharc[7] = (unsigned int*)0;
    sqlstm.sqadto[7] = (unsigned short )0;
    sqlstm.sqtdso[7] = (unsigned short )0;
    sqlstm.sqhstv[8] = (         void*)ana.p_until;
    sqlstm.sqhstl[8] = (unsigned int  )sizeof(double);
    sqlstm.sqhsts[8] = (         int  )sizeof(double);
    sqlstm.sqindv[8] = (         void*)ana_Ind.p_until_Ind;
    sqlstm.sqinds[8] = (         int  )sizeof(short);
    sqlstm.sqharm[8] = (unsigned int  )0;
    sqlstm.sqharc[8] = (unsigned int*)0;
    sqlstm.sqadto[8] = (unsigned short )0;
    sqlstm.sqtdso[8] = (unsigned short )0;
    sqlstm.sqhstv[9] = (         void*)&id;
    sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[9] = (         int  )sizeof(int);
    sqlstm.sqindv[9] = (         void*)0;
    sqlstm.sqinds[9] = (         int  )0;
    sqlstm.sqharm[9] = (unsigned int  )0;
    sqlstm.sqadto[9] = (unsigned short )0;
    sqlstm.sqtdso[9] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) { showSqlError("read(FairParGenericSet*)"); }
  }


  FairParamList* paramList = new FairParamList;
  TList* blobList=new TList;
  for(Int_t i=0; i<sqlca.sqlerrd[2]; i++) {
    if (ana_Ind.p_name_Ind[i]!=-1 && ana_Ind.p_value_Ind[i]!=-1) {
      ana.p_name[i].arr[ana.p_name[i].len]='\0';
      ana.p_value[i].arr[ana.p_value[i].len]='\0';
      ana.p_type[i].arr[ana.p_type[i].len]='\0';
      if (ana.p_since[i]>pSet->versDate[0]) { pSet->versDate[0]=ana.p_since[i]; }
      if (ana.p_until[i]<pSet->versDate[1] || pSet->versDate[1]<0) {
        pSet->versDate[1]=ana.p_until[i];
      }
      if (ana.p_is_binary[i]==0)
        paramList->add((char*)(ana.p_name[i].arr),(char*)(ana.p_value[i].arr),
                       ana.p_type[i].arr[0],ana.p_num[i]);
      else {
        FairParamBinObj* o=new FairParamBinObj;
        o->SetName((char*)(ana.p_name[i].arr));
        o->setParamType((char*)(ana.p_type[i].arr));
        if (ana.p_is_basic[i]==0) { o->setClassVersion(ana.p_class_vers[i]); }
        paramList->getBinaryList()->Add(o);
        Int_t lobId;
        sscanf((char*)(ana.p_value[i].arr),"%i",&lobId);
        FairParOraBlob* ob=new FairParOraBlob(o,lobId);
        blobList->Add(ob);
      }
    }
  }
  TIter next(blobList);
  FairParOraBlob* b;
  Bool_t rc;
  if (sqlca.sqlerrd[2]==0) { rc=kFALSE; }
  else { rc=kTRUE; }
  while ((b=(FairParOraBlob*)next())!=0 && rc) {
    rc=readBlob(b->binaryParam,b->blobId);
  }
  if (rc) { rc=pPar->getParams(paramList); }
  else { pPar->setInputVersion(-1,inputNumber); }
  blobList->Delete();
  delete blobList;
  delete paramList;
  if (rc==kTRUE) {
    setChanged(pPar);
    cout<<pPar->GetName()<<" initialized from Oracle"<<'\n';
  }
  return rc;
}

Bool_t FairGenericParOraIo::readBlob(FairParamBinObj* obj,Int_t lobId)
{
  /* EXEC SQL BEGIN DECLARE SECTION; */

  int            id;
  unsigned int   loblength;
  unsigned int   amount;
  unsigned int   offset;
  unsigned char  buffer[LOB_BUFSIZE];
  /* EXEC SQL VAR buffer IS RAW(LOB_BUFSIZE); */

  /* EXEC SQL END DECLARE SECTION; */

  id=lobId;
  amount=LOB_BUFSIZE;
  UChar_t* paramValue=0;
  UInt_t amountRead=0;
  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */

  /* EXEC SQL WHENEVER NOT FOUND GOTO notfound; */

  /* EXEC SQL EXECUTE
    BEGIN
      cbm_ana.param_lob_access.read_blob(:id,:amount,:loblength,:buffer);
    END;
  END-EXEC; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "begin cbm_ana . param_lob_access . read_blob ( :id , :amoun\
t , :loblength , :buffer ) ; END ;";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )60;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void*)&id;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void*)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void*)&amount;
    sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void*)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void*)&loblength;
    sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void*)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void*)buffer;
    sqlstm.sqhstl[3] = (unsigned int  )32512;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void*)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) { goto notfound; }
    if (sqlca.sqlcode < 0) { goto notfound; }
  }


  obj->setLength(loblength);
  paramValue=obj->getParamValue();
  amountRead=amount;
  memcpy((unsigned char*)paramValue,buffer,amount);
  while (amountRead<loblength) {
    amount= (loblength>LOB_BUFSIZE) ? LOB_BUFSIZE : loblength ;
    offset=amountRead+1;
    /* EXEC SQL EXECUTE
      BEGIN
        cbm_ana.param_lob_access.read_next_buffer(:amount,:offset,:buffer);
      END;
    END-EXEC; */

    {
      struct sqlexd sqlstm;
      sqlorat((void**)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 10;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "begin cbm_ana . param_lob_access . read_next_buffer ( :am\
ount , :offset , :buffer ) ; END ;";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )91;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char*)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void*)&amount;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void*)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void*)&offset;
      sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void*)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void*)buffer;
      sqlstm.sqhstl[2] = (unsigned int  )32512;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void*)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) { goto notfound; }
      if (sqlca.sqlcode < 0) { goto notfound; }
    }


    memcpy((unsigned char*)(&paramValue[amountRead]),buffer,amount);
    amountRead+=amount;
  }
  return kTRUE;
notfound:
  showSqlError("readBlob");
  Error("readBlob","Blob %i not read",lobId);
  return kFALSE;
}

Int_t FairGenericParOraIo::createParamVers(FairParGenericSet* pPar)
{
  // create analysis parameter version in Oracle
  // returns version number or -1 if error occurred
  /* EXEC SQL BEGIN DECLARE SECTION; */

  char* p_class;
  char* p_author;
  char* p_descript;
  char* p_context;
  int vers=-1;
  int context_id=-1;
  /* EXEC SQL END DECLARE SECTION; */

  p_class=(char*)(pPar->IsA()->GetName());
  p_author=(char*)(pPar->getAuthor());
  p_descript=(char*)(pPar->getDescription());
  p_context=(char*)(pPar->getParamContext());
  if (strlen(p_author)==0) {
    Error("createParamVers(...)",
          "author of parameters not defined");
    return -1;
  }
  if (strlen(p_descript)==0) {
    Error("createParamVers(...)",
          "description of parameters not defined");
    return -1;
  }
  if (strlen(p_context)==0) {
    Error("createParamVers(...)",
          "Purpose of parameters not defined");
    return -1;
  }
  /* EXEC SQL WHENEVER SQLERROR GOTO not_found; */

  /* EXEC SQL WHENEVER NOT FOUND GOTO not_found; */

  /* EXEC SQL EXECUTE
    DECLARE
    BEGIN
      :context_id := cbm_ana.param_query.get_context_id(
                         :p_class,:p_context);
      IF :context_id > 0 THEN
        :vers := cbm_ana.param_query.next_param_vers_load(:p_class);
        IF :vers > 0 THEN
          INSERT INTO cbm_ana.param_vers_load
            (param_vers_load_id,param_context_id,author,description)
            VALUES (:vers,:context_id,:p_author,:p_descript);
        END IF;
      END IF;
    END;
  END-EXEC; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "declare BEGIN :context_id := cbm_ana . param_query . get_co\
ntext_id ( :p_class , :p_context ) ; IF :context_id > 0 THEN :vers := cbm_ana \
. param_query . next_param_vers_load ( :p_class ) ; IF :vers > 0 THEN INSERT I\
NTO cbm_ana . param_vers_load ( param_vers_load_id , param_context_id , author\
 , description ) VALUES ( :vers , :context_id , :p_author , :p_descript ) ; EN\
D IF ; END IF ; END ;";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )118;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void*)&context_id;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void*)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void*)p_class;
    sqlstm.sqhstl[1] = (unsigned int  )0;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void*)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void*)p_context;
    sqlstm.sqhstl[2] = (unsigned int  )0;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void*)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void*)&vers;
    sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void*)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void*)p_author;
    sqlstm.sqhstl[4] = (unsigned int  )0;
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         void*)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (         void*)p_descript;
    sqlstm.sqhstl[5] = (unsigned int  )0;
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         void*)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned int  )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) { goto not_found; }
    if (sqlca.sqlcode < 0) { goto not_found; }
  }


  return vers;
not_found:
  showSqlError("createParamVers(const char*)");
  rollback();
  return vers;
};

Int_t FairGenericParOraIo::writeSet(FairParGenericSet* pPar)
{
  // write analysis parameters to Oracle
  Int_t runStart=getRunStart();
  if (runStart==-1) {
    pPar->setChanged(kFALSE);
    return -1;
  }
  cout<<"---------------  Storage of "<<pPar->GetName()<<"  ---------------\n";
  Int_t version=createParamVers(pPar);
  if (version==-1) { return -1; }
  cout<<"****************************************************************\n";
  cout<<"***  Version:                     "<<version<<endl;
  /* EXEC SQL BEGIN DECLARE SECTION; */

  int vers[NMAX_PARAM];
  char p_name[NMAX_PARAM][81];
  char p_value[NMAX_PARAM][4000];
  char p_type[NMAX_PARAM][81];
  int  p_is_binary[NMAX_PARAM];
  int  p_is_basic[NMAX_PARAM];
  int p_nvalues[NMAX_PARAM];
  int p_num[NMAX_PARAM];
  int p_class_vers [NMAX_PARAM];
  short class_vers_Ind [NMAX_PARAM];
  int rows_to_insert;
  /* EXEC SQL END DECLARE SECTION; */

  FairParamList* paramList = new FairParamList;
  pPar->putParams(paramList);
  TList* pList=paramList->getList();
  TIter next(pList);
  FairParamObj* po;
  TList* pBinList=paramList->getBinaryList();
  TIter nextBin(pBinList);
  FairParamBinObj* pbo;
  Int_t n=0, m=0;
  while ((po=(FairParamObj*)next())) {
    vers[n]=version;
    strcpy(p_name[n],po->GetName());
    strcpy(p_value[n],po->getParamValue());
    p_type[n][0]=po->getParamType();
    p_type[n][1]='\0';
    p_is_binary[n]=0;
    p_is_basic[n]=1;
    p_nvalues[n]=po->getNumParams();
    p_num[n]=n+1;
    n++;
  }
  /* EXEC SQL WHENEVER SQLERROR GOTO not_found; */

  /* EXEC SQL WHENEVER NOT FOUND GOTO not_found; */

  if (n>0) {
    rows_to_insert=n;
    /* EXEC SQL FOR :rows_to_insert
      INSERT INTO cbm_ana.param_value_load
        ( param_vers_load_id,param_name,param_value,param_value_type,
          is_binary,is_basic_type,nvalues,param_num)
        VALUES(:vers,:p_name,:p_value,:p_type,:p_is_binary,:p_is_basic,
          :p_nvalues,:p_num); */

    {
      struct sqlexd sqlstm;
      sqlorat((void**)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 10;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "insert into cbm_ana.param_value_load (param_vers_load_id,\
param_name,param_value,param_value_type,is_binary,is_basic_type,nvalues,param_\
num) values (:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8)";
      sqlstm.iters = (unsigned int  )rows_to_insert;
      sqlstm.offset = (unsigned int  )157;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char*)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void*)vers;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )sizeof(int);
      sqlstm.sqindv[0] = (         void*)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqharc[0] = (unsigned int*)0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void*)p_name;
      sqlstm.sqhstl[1] = (unsigned int  )81;
      sqlstm.sqhsts[1] = (         int  )81;
      sqlstm.sqindv[1] = (         void*)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqharc[1] = (unsigned int*)0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void*)p_value;
      sqlstm.sqhstl[2] = (unsigned int  )4000;
      sqlstm.sqhsts[2] = (         int  )4000;
      sqlstm.sqindv[2] = (         void*)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqharc[2] = (unsigned int*)0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void*)p_type;
      sqlstm.sqhstl[3] = (unsigned int  )81;
      sqlstm.sqhsts[3] = (         int  )81;
      sqlstm.sqindv[3] = (         void*)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqharc[3] = (unsigned int*)0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void*)p_is_binary;
      sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[4] = (         int  )sizeof(int);
      sqlstm.sqindv[4] = (         void*)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqharc[4] = (unsigned int*)0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void*)p_is_basic;
      sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[5] = (         int  )sizeof(int);
      sqlstm.sqindv[5] = (         void*)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqharc[5] = (unsigned int*)0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void*)p_nvalues;
      sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[6] = (         int  )sizeof(int);
      sqlstm.sqindv[6] = (         void*)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqharc[6] = (unsigned int*)0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void*)p_num;
      sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[7] = (         int  )sizeof(int);
      sqlstm.sqindv[7] = (         void*)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqharc[7] = (unsigned int*)0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) { goto not_found; }
      if (sqlca.sqlcode < 0) { goto not_found; }
    }


    cout<<"***  Number of parameters:        "<<rows_to_insert<<endl;
  }
  m=n;
  n=0;
  while ((pbo=(FairParamBinObj*)nextBin())) {
    vers[n]=version;
    strcpy(p_name[n],pbo->GetName());
    strcpy(p_type[n],pbo->getParamType());
    p_is_binary[n]=1;
    if (pbo->isBasicType()) {
      p_is_basic[n]=1;
      class_vers_Ind[n]=-1;
    } else {
      p_is_basic[n]=0;
      p_class_vers[n]=pbo->getClassVersion();
      class_vers_Ind[n]=0;
      p_nvalues[n]=0;
    }
    p_nvalues[n]=pbo->getNumParams();
    sprintf(p_value[n],"%i",storeBlob(pbo->getParamValue(),pbo->getLength()));
    p_num[n]=m+n+1;
    n++;
  }
  if (n>0) {
    rows_to_insert=n;
    /* EXEC SQL FOR :rows_to_insert
      INSERT INTO cbm_ana.param_value_load
          (param_vers_load_id,param_name,param_value,param_value_type,
           is_binary,is_basic_type,nvalues,param_num,class_version)
        VALUES(:vers,:p_name,:p_value,:p_type,:p_is_binary,:p_is_basic,
               :p_nvalues,:p_num,:p_class_vers:class_vers_Ind); */

    {
      struct sqlexd sqlstm;
      sqlorat((void**)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 10;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "insert into cbm_ana.param_value_load (param_vers_load_id,\
param_name,param_value,param_value_type,is_binary,is_basic_type,nvalues,param_\
num,class_version) values (:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9:b10)";
      sqlstm.iters = (unsigned int  )rows_to_insert;
      sqlstm.offset = (unsigned int  )204;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char*)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void*)vers;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )sizeof(int);
      sqlstm.sqindv[0] = (         void*)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqharc[0] = (unsigned int*)0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void*)p_name;
      sqlstm.sqhstl[1] = (unsigned int  )81;
      sqlstm.sqhsts[1] = (         int  )81;
      sqlstm.sqindv[1] = (         void*)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqharc[1] = (unsigned int*)0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void*)p_value;
      sqlstm.sqhstl[2] = (unsigned int  )4000;
      sqlstm.sqhsts[2] = (         int  )4000;
      sqlstm.sqindv[2] = (         void*)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqharc[2] = (unsigned int*)0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void*)p_type;
      sqlstm.sqhstl[3] = (unsigned int  )81;
      sqlstm.sqhsts[3] = (         int  )81;
      sqlstm.sqindv[3] = (         void*)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqharc[3] = (unsigned int*)0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqhstv[4] = (         void*)p_is_binary;
      sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[4] = (         int  )sizeof(int);
      sqlstm.sqindv[4] = (         void*)0;
      sqlstm.sqinds[4] = (         int  )0;
      sqlstm.sqharm[4] = (unsigned int  )0;
      sqlstm.sqharc[4] = (unsigned int*)0;
      sqlstm.sqadto[4] = (unsigned short )0;
      sqlstm.sqtdso[4] = (unsigned short )0;
      sqlstm.sqhstv[5] = (         void*)p_is_basic;
      sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[5] = (         int  )sizeof(int);
      sqlstm.sqindv[5] = (         void*)0;
      sqlstm.sqinds[5] = (         int  )0;
      sqlstm.sqharm[5] = (unsigned int  )0;
      sqlstm.sqharc[5] = (unsigned int*)0;
      sqlstm.sqadto[5] = (unsigned short )0;
      sqlstm.sqtdso[5] = (unsigned short )0;
      sqlstm.sqhstv[6] = (         void*)p_nvalues;
      sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[6] = (         int  )sizeof(int);
      sqlstm.sqindv[6] = (         void*)0;
      sqlstm.sqinds[6] = (         int  )0;
      sqlstm.sqharm[6] = (unsigned int  )0;
      sqlstm.sqharc[6] = (unsigned int*)0;
      sqlstm.sqadto[6] = (unsigned short )0;
      sqlstm.sqtdso[6] = (unsigned short )0;
      sqlstm.sqhstv[7] = (         void*)p_num;
      sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[7] = (         int  )sizeof(int);
      sqlstm.sqindv[7] = (         void*)0;
      sqlstm.sqinds[7] = (         int  )0;
      sqlstm.sqharm[7] = (unsigned int  )0;
      sqlstm.sqharc[7] = (unsigned int*)0;
      sqlstm.sqadto[7] = (unsigned short )0;
      sqlstm.sqtdso[7] = (unsigned short )0;
      sqlstm.sqhstv[8] = (         void*)p_class_vers;
      sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[8] = (         int  )sizeof(int);
      sqlstm.sqindv[8] = (         void*)class_vers_Ind;
      sqlstm.sqinds[8] = (         int  )sizeof(short);
      sqlstm.sqharm[8] = (unsigned int  )0;
      sqlstm.sqharc[8] = (unsigned int*)0;
      sqlstm.sqadto[8] = (unsigned short )0;
      sqlstm.sqtdso[8] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) { goto not_found; }
      if (sqlca.sqlcode < 0) { goto not_found; }
    }


    cout<<"***  Number of binary parameters: "<<rows_to_insert<<endl;
  }
  cout<<"***  "<<pPar->GetName()<<" written to Oracle"<<endl;
  cout<<"****************************************************************\n";
  commit();
  pPar->setChanged(kFALSE);
  delete paramList;
  return version;
not_found:
  showSqlError("writeSet(FairParGenericSet*)");
  rollback();
  pPar->setChanged(kFALSE);
  delete paramList;
  return -1;
}

Int_t FairGenericParOraIo::storeBlob(UChar_t* pValue, Int_t pLength)
{
  /* EXEC SQL BEGIN DECLARE SECTION; */

  unsigned char buffer[LOB_BUFSIZE];
  int           totlen;
  int           amount;
  int           offset;
  int           id;
  /* EXEC SQL VAR buffer IS RAW(LOB_BUFSIZE); */

  /* EXEC SQL END DECLARE SECTION; */

  offset=1;
  totlen=pLength;
  amount= (totlen>LOB_BUFSIZE) ? LOB_BUFSIZE : totlen;
  memcpy(buffer,pValue,amount);
  id=-1;
  Int_t restlen=totlen-amount;
  /* EXEC SQL WHENEVER SQLERROR GOTO errorfound; */

  /* EXEC SQL WHENEVER NOT FOUND GOTO errorfound; */

  /* EXEC SQL EXECUTE
    DECLARE
    BEGIN
      cbm_ana.param_lob_access.add_blob(:totlen,:amount,:buffer,:id);
    END;
  END-EXEC; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "declare BEGIN cbm_ana . param_lob_access . add_blob ( :totl\
en , :amount , :buffer , :id ) ; END ;";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )255;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void*)&totlen;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void*)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void*)&amount;
    sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void*)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void*)buffer;
    sqlstm.sqhstl[2] = (unsigned int  )32512;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void*)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void*)&id;
    sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void*)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) { goto errorfound; }
    if (sqlca.sqlcode < 0) { goto errorfound; }
  }


  while (restlen>0) {
    offset+=LOB_BUFSIZE;
    amount= (restlen>LOB_BUFSIZE) ? LOB_BUFSIZE : restlen;
    memcpy(buffer,&pValue[offset-1],amount);
    /* EXEC SQL EXECUTE
      DECLARE
      BEGIN
        cbm_ana.param_lob_access.append_to_blob(:id,:amount,:offset,:buffer);
      END;
    END-EXEC; */

    {
      struct sqlexd sqlstm;
      sqlorat((void**)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 10;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "declare BEGIN cbm_ana . param_lob_access . append_to_blob\
 ( :id , :amount , :offset , :buffer ) ; END ;";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )286;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char*)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void*)&id;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void*)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void*)&amount;
      sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void*)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void*)&offset;
      sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void*)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqhstv[3] = (         void*)buffer;
      sqlstm.sqhstl[3] = (unsigned int  )32512;
      sqlstm.sqhsts[3] = (         int  )0;
      sqlstm.sqindv[3] = (         void*)0;
      sqlstm.sqinds[3] = (         int  )0;
      sqlstm.sqharm[3] = (unsigned int  )0;
      sqlstm.sqadto[3] = (unsigned short )0;
      sqlstm.sqtdso[3] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) { goto errorfound; }
      if (sqlca.sqlcode < 0) { goto errorfound; }
    }


    restlen-=amount;
  }
  return id;
errorfound:
  showSqlError("storeBlob");
  /* EXEC SQL ROLLBACK WORK; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )317;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) { goto errorfound; }
  }


  cout<<"Blob not stored."<<endl;
  return -1;
}

Bool_t FairGenericParOraIo::readFromLoadingTable(FairParGenericSet* pPar,Int_t version)
{
  // reads the analysis parameters from the LOAD table and fills the container
  /* EXEC SQL BEGIN DECLARE SECTION; */

  int vers;
  struct {
    /* varchar p_name[NMAX_PARAM][81]; */
    struct { unsigned short len; unsigned char arr[82]; } p_name[200];

    /* varchar p_value[NMAX_PARAM][4001]; */
    struct { unsigned short len; unsigned char arr[4002]; } p_value[200];

    int     p_num[NMAX_PARAM];
    /* varchar p_type[NMAX_PARAM][81]; */
    struct { unsigned short len; unsigned char arr[82]; } p_type[200];

    int     p_is_binary[NMAX_PARAM];
    int     p_is_basic[NMAX_PARAM];
    int     p_class_vers[NMAX_PARAM];
  } cl;
  struct {
    short p_name_Ind[NMAX_PARAM];
    short p_value_Ind[NMAX_PARAM];
    short p_num_Ind[NMAX_PARAM];
    short p_type_Ind[NMAX_PARAM];
    short p_is_binary_Ind[NMAX_PARAM];
    short p_is_basic_Ind[NMAX_PARAM];
    short p_class_vers_Ind[NMAX_PARAM];
  } cl_Ind;
  /* EXEC SQL END DECLARE SECTION; */

  /* EXEC SQL WHENEVER SQLERROR DO showSqlError("readFromLoadingTable(FairParGenericSet*,Int_t*)"); */

  /* EXEC SQL WHENEVER NOT FOUND CONTINUE; */

  vers=version;
  /* EXEC SQL SELECT param_name, param_value, nvalues, param_value_type,
                  is_binary, is_basic_type, class_version
           INTO :cl INDICATOR :cl_Ind
           FROM cbm_ana.param_value_load_all
           WHERE param_vers_load_id = :vers; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select param_name ,param_value ,nvalues ,param_value_type ,\
is_binary ,is_basic_type ,class_version into :s1:s2 ,:s3:s4 ,:s5:s6 ,:s7:s8 ,:\
s9:s10 ,:s11:s12 ,:s13:s14   from cbm_ana.param_value_load_all where param_ver\
s_load_id=:b2";
    sqlstm.iters = (unsigned int  )200;
    sqlstm.offset = (unsigned int  )332;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void*)cl.p_name;
    sqlstm.sqhstl[0] = (unsigned int  )83;
    sqlstm.sqhsts[0] = (         int  )84;
    sqlstm.sqindv[0] = (         void*)cl_Ind.p_name_Ind;
    sqlstm.sqinds[0] = (         int  )sizeof(short);
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqharc[0] = (unsigned int*)0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void*)cl.p_value;
    sqlstm.sqhstl[1] = (unsigned int  )4003;
    sqlstm.sqhsts[1] = (         int  )4004;
    sqlstm.sqindv[1] = (         void*)cl_Ind.p_value_Ind;
    sqlstm.sqinds[1] = (         int  )sizeof(short);
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqharc[1] = (unsigned int*)0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void*)cl.p_num;
    sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[2] = (         int  )sizeof(int);
    sqlstm.sqindv[2] = (         void*)cl_Ind.p_num_Ind;
    sqlstm.sqinds[2] = (         int  )sizeof(short);
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqharc[2] = (unsigned int*)0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void*)cl.p_type;
    sqlstm.sqhstl[3] = (unsigned int  )83;
    sqlstm.sqhsts[3] = (         int  )84;
    sqlstm.sqindv[3] = (         void*)cl_Ind.p_type_Ind;
    sqlstm.sqinds[3] = (         int  )sizeof(short);
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqharc[3] = (unsigned int*)0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void*)cl.p_is_binary;
    sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[4] = (         int  )sizeof(int);
    sqlstm.sqindv[4] = (         void*)cl_Ind.p_is_binary_Ind;
    sqlstm.sqinds[4] = (         int  )sizeof(short);
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqharc[4] = (unsigned int*)0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (         void*)cl.p_is_basic;
    sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[5] = (         int  )sizeof(int);
    sqlstm.sqindv[5] = (         void*)cl_Ind.p_is_basic_Ind;
    sqlstm.sqinds[5] = (         int  )sizeof(short);
    sqlstm.sqharm[5] = (unsigned int  )0;
    sqlstm.sqharc[5] = (unsigned int*)0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqhstv[6] = (         void*)cl.p_class_vers;
    sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[6] = (         int  )sizeof(int);
    sqlstm.sqindv[6] = (         void*)cl_Ind.p_class_vers_Ind;
    sqlstm.sqinds[6] = (         int  )sizeof(short);
    sqlstm.sqharm[6] = (unsigned int  )0;
    sqlstm.sqharc[6] = (unsigned int*)0;
    sqlstm.sqadto[6] = (unsigned short )0;
    sqlstm.sqtdso[6] = (unsigned short )0;
    sqlstm.sqhstv[7] = (         void*)&vers;
    sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[7] = (         int  )sizeof(int);
    sqlstm.sqindv[7] = (         void*)0;
    sqlstm.sqinds[7] = (         int  )0;
    sqlstm.sqharm[7] = (unsigned int  )0;
    sqlstm.sqadto[7] = (unsigned short )0;
    sqlstm.sqtdso[7] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) { showSqlError("readFromLoadingTable(FairParGenericSet*,Int_t*)"); }
  }


  FairParamList* paramList = new FairParamList;
  TList* blobList=new TList;
  for(Int_t i=0; i<sqlca.sqlerrd[2]; i++) {
    if (cl_Ind.p_name_Ind[i]!=-1 && cl_Ind.p_value_Ind[i]!=-1) {
      cl.p_name[i].arr[cl.p_name[i].len]='\0';
      cl.p_value[i].arr[cl.p_value[i].len]='\0';
      cl.p_type[i].arr[cl.p_type[i].len]='\0';
      if (cl.p_is_binary[i]==0)
        paramList->add((char*)(cl.p_name[i].arr),(char*)(cl.p_value[i].arr),
                       cl.p_type[i].arr[0],cl.p_num[i]);
      else {
        FairParamBinObj* o=new FairParamBinObj;
        o->SetName((char*)(cl.p_name[i].arr));
        o->setParamType((char*)(cl.p_type[i].arr));
        if (cl.p_is_basic[i]==0) { o->setClassVersion(cl.p_class_vers[i]); }
        paramList->getBinaryList()->Add(o);
        Int_t lobId;
        sscanf((char*)(cl.p_value[i].arr),"%i",&lobId);
        FairParOraBlob* ob=new FairParOraBlob(o,lobId);
        blobList->Add(ob);
      }
    }
  }
  TIter next(blobList);
  FairParOraBlob* b;
  Bool_t rc=kTRUE;
  while ((b=(FairParOraBlob*)next())!=0 && rc) {
    rc=readLoadBlob(b->binaryParam,b->blobId);
  }
  if (rc && sqlca.sqlerrd[2]>0) {
    rc=pPar->getParams(paramList);
    pPar->setInputVersion(version,inputNumber);
  } else { pPar->setInputVersion(-1,inputNumber); }
  blobList->Delete();
  delete blobList;
  delete paramList;
  if (rc==kTRUE) {
    setChanged(pPar);
    cout<<pPar->GetName()<<" initialized from Load Table"<<'\n';
  }
  return rc;
}

Bool_t FairGenericParOraIo::readLoadBlob(FairParamBinObj* obj,Int_t lobId)
{
  // reads the BLOB from the LOAD table
  /* EXEC SQL BEGIN DECLARE SECTION; */

  int            id;
  unsigned int   loblength;
  unsigned int   amount;
  unsigned int   offset;
  unsigned char  buffer[LOB_BUFSIZE];
  /* EXEC SQL VAR buffer IS RAW(LOB_BUFSIZE); */

  /* EXEC SQL END DECLARE SECTION; */

  id=lobId;
  amount=LOB_BUFSIZE;
  UChar_t* paramValue=0;
  UInt_t amountRead=0;
  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */

  /* EXEC SQL WHENEVER NOT FOUND GOTO notfound; */

  /* EXEC SQL EXECUTE
    BEGIN
      cbm_ana.param_lob_access.read_load_blob(:id,:amount,:loblength,:buffer);
    END;
  END-EXEC; */

  {
    struct sqlexd sqlstm;
    sqlorat((void**)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 10;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "begin cbm_ana . param_lob_access . read_load_blob ( :id , :\
amount , :loblength , :buffer ) ; END ;";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )379;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char*)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void*)&id;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void*)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void*)&amount;
    sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void*)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void*)&loblength;
    sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void*)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void*)buffer;
    sqlstm.sqhstl[3] = (unsigned int  )32512;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void*)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode == 1403) { goto notfound; }
    if (sqlca.sqlcode < 0) { goto notfound; }
  }


  obj->setLength(loblength);
  paramValue=obj->getParamValue();
  amountRead=amount;
  memcpy((unsigned char*)paramValue,buffer,amount);
  while (amountRead<loblength) {
    amount= (loblength>LOB_BUFSIZE) ? LOB_BUFSIZE : loblength ;
    offset=amountRead+1;
    /* EXEC SQL EXECUTE
      BEGIN
        cbm_ana.param_lob_access.read_next_buffer(:amount,:offset,:buffer);
      END;
    END-EXEC; */

    {
      struct sqlexd sqlstm;
      sqlorat((void**)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 10;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "begin cbm_ana . param_lob_access . read_next_buffer ( :am\
ount , :offset , :buffer ) ; END ;";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )410;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char*)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void*)&amount;
      sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void*)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void*)&offset;
      sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void*)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqhstv[2] = (         void*)buffer;
      sqlstm.sqhstl[2] = (unsigned int  )32512;
      sqlstm.sqhsts[2] = (         int  )0;
      sqlstm.sqindv[2] = (         void*)0;
      sqlstm.sqinds[2] = (         int  )0;
      sqlstm.sqharm[2] = (unsigned int  )0;
      sqlstm.sqadto[2] = (unsigned short )0;
      sqlstm.sqtdso[2] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void**)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) { goto notfound; }
      if (sqlca.sqlcode < 0) { goto notfound; }
    }


    memcpy((unsigned char*)(&paramValue[amountRead]),buffer,amount);
    amountRead+=amount;
  }
  return kTRUE;
notfound:
  showSqlError("readBlob");
  Error("readBlob","Blob %i not read",lobId);
  return kFALSE;
}
