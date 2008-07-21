
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
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
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[14];
};
static const struct sqlcxp sqlfpn =
{
    13,
    "CbmOraInfo.pc"
};


static unsigned int sqlctx = 567539;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {12,4};

// Prototypes
extern "C" {
  void sqlcxt (void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlcx2t(void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlbuft(void **, char *);
  void sqlgs2t(void **, char *);
  void sqlorat(void **, unsigned int *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(char *, int *); }

 static const char *sq0003 = 
"select ref_run_id ,ref_run_name ,TO_CHAR(run_start,'DD-MON-YYYY HH24:MI:SS')\
 ,TO_CHAR(run_stop,'DD-MON-YYYY HH24:MI:SS')  from cbm_ana.simul_subproject p \
,cbm_ana.simul_ref_run rr where (((upper(project_id)=:b0 and p.subproject_id=r\
r.subproject_id) and run_start between TO_DATE(:b1,'DD-MON-YYYY HH24:MI:SS') a\
nd TO_DATE(:b2,'DD-MON-YYYY HH24:MI:SS')) and rr.generation=(select max(genera\
tion)  from cbm_ana.simul_ref_run where subproject_id=p.subproject_id)) order \
by ref_run_id            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,100,0,4,50,0,0,2,1,0,1,0,2,97,0,0,1,3,0,0,
28,0,0,2,82,0,4,72,0,0,2,1,0,1,0,2,3,0,0,1,97,0,0,
51,0,0,3,491,0,9,138,0,0,3,3,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,
78,0,0,3,0,0,13,140,0,0,4,0,0,1,0,2,3,0,0,2,9,0,0,2,97,0,0,2,97,0,0,
109,0,0,3,0,0,15,156,0,0,0,0,0,1,0,
124,0,0,4,108,0,4,188,0,0,2,1,0,1,0,2,97,0,0,1,3,0,0,
147,0,0,5,110,0,4,194,0,0,2,1,0,1,0,2,97,0,0,1,97,0,0,
};


//*-- AUTHOR : Ilse Koenig
//*-- Created : 26/11/2004 by I.Koenig

//////////////////////////////////////////////////////////////////////////////
// CbmOraInfo
//
// Class for additional information from database Oracle
// (uses the Oracle C/C++ precompiler)
// Functions in this class are not used by the analysis but can be called
// by the user on the ROOT interpreter to get additional information from
// Oracle tables.
//////////////////////////////////////////////////////////////////////////////

using namespace std;
#include "CbmOraInfo.h"
#include "CbmOraConn.h"
#include "CbmOraRunInfo.h"
#include <iostream>
#include <iomanip>

#define SQLCA_STORAGE_CLASS extern
#define ORACA_STORAGE_CLASS extern

// Oracle communication area
#include "oraca.h"
// Include the SQL Communications Area
#include "sqlca.h"
 
ClassImp(CbmOraInfo)

#define NMAX_INFO 2000
 
void CbmOraInfo::showSqlError(char* f) {
  // shows SQL error messages
  Error(f,"\n%s",sqlca.sqlerrm.sqlerrmc);
}


void CbmOraInfo::showRunStart(Int_t run) {
  // prints the start date and time of given run
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    int id; 
    char runDate[21];
    short runDate_Ind=-1;
  /* EXEC SQL END DECLARE SECTION; */ 

  id=run;
  /* EXEC SQL WHENEVER SQLERROR DO
    showSqlError("showRunStart(Int_t)"); */ 

  /* EXEC SQL WHENEVER NOT FOUND GOTO notfound; */ 

  /* EXEC SQL SELECT TO_CHAR(run_start,'DD-MON-YYYY HH:MI:SS')
           INTO :runDate INDICATOR :runDate_Ind
           FROM cbm_ana.all_runs
           WHERE run_id = :id; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select TO_CHAR(run_start,'DD-MON-YYYY HH:MI:SS') into :b0:b\
1  from cbm_ana.all_runs where run_id=:b2";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)runDate;
  sqlstm.sqhstl[0] = (unsigned int  )21;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)&runDate_Ind;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&id;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode == 1403) goto notfound;
  if (sqlca.sqlcode < 0) showSqlError("showRunStart(Int_t)");
}


  if (runDate_Ind>=0) cout<<"Run "<<run<<" started at "<<runDate<<'\n';
  else cout << "no Run_Start for run "<<run<<'\n';
  return;
notfound:
  cout << "Run not found" <<endl;
  return;
}

Int_t CbmOraInfo::getRunId(Text_t* filename) {
  // returns the run id of a daq file
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* runname;
    int run;
  /* EXEC SQL END DECLARE SECTION; */ 

  runname=filename;
  /* EXEC SQL WHENEVER SQLERROR DO
    showSqlError("getRunId(Text_t*)"); */ 

  /* EXEC SQL WHENEVER NOT FOUND GOTO notfound; */ 

  /* EXEC SQL SELECT run_id INTO :run
           FROM cbm_ana.all_runs
           WHERE LOWER(run_filename) = LOWER(:runname); */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select run_id into :b0  from cbm_ana.all_runs where LOWER(r\
un_filename)=LOWER(:b1)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )28;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&run;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)runname;
  sqlstm.sqhstl[1] = (unsigned int  )0;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode == 1403) goto notfound;
  if (sqlca.sqlcode < 0) showSqlError("getRunId(Text_t*)");
}

           
  return run;
notfound:
  Error("getRunId(Text_t*)","No such file %s",filename);
  return -1;
}


TList* CbmOraInfo::getListOfRuns(const char* projectname,
                               const char* startAt, const char* endAt) {
  // returns the list of simulation reference runs (only last generation)
  //   for the specifies project and range
  // accepts dates (format DD-MON-YYYY HH24:MI:SS), filenames and run ids
  if (strlen(projectname)==0) return 0;
  TString pName(projectname);
  pName.ToUpper();
  TString rangeStart;
  TString rangeEnd;
  Bool_t rc=kTRUE;
  if (strlen(startAt)!=0) rc=getRefRunStart(startAt,rangeStart);
  else rangeStart="01-JAN-1990 00:00:00";
  if (!rc) return 0;
  if (strlen(endAt)!=0) rc=getRefRunStart(endAt,rangeEnd);
  else rangeEnd="01-JAN-4000 00:00:00";
  if (!rc) return 0;
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* project;
    char* pstart;
    char* pend;
    struct {
      int     rid[NMAX_INFO];
      /* varchar rname[NMAX_INFO][81]; */ 
struct { unsigned short len; unsigned char arr[82]; } rname[2000];

      char    ts[NMAX_INFO][21];
      char    te[NMAX_INFO][21];
    } refruns;
    struct {
      short rid_Ind[NMAX_INFO];
      short rname_Ind[NMAX_INFO];
      short ts_Ind[NMAX_INFO];
      short te_Ind[NMAX_INFO];
    } refruns_Ind;
  /* EXEC SQL END DECLARE SECTION; */ 

  project=(char*)projectname;
  pstart=(char*)rangeStart.Data();
  pend=(char*)rangeEnd.Data();
  Int_t nTot=0;
  Int_t nLast=0;
  TList* runsList=new TList();
  /* EXEC SQL WHENEVER SQLERROR GOTO errorfound; */ 

  /* EXEC SQL WHENEVER NOT FOUND continue; */ 

  /* EXEC SQL DECLARE refruns_cursor CURSOR FOR
           SELECT ref_run_id, ref_run_name,
                  TO_CHAR(run_start,'DD-MON-YYYY HH24:MI:SS'),
                  TO_CHAR(run_stop,'DD-MON-YYYY HH24:MI:SS')
           FROM cbm_ana.simul_subproject p,
                cbm_ana.simul_ref_run rr
           WHERE upper(project_id)= :project
             AND p.subproject_id = rr.subproject_id
             AND run_start BETWEEN TO_DATE(:pstart,'DD-MON-YYYY HH24:MI:SS')
                           AND TO_DATE(:pend,'DD-MON-YYYY HH24:MI:SS')
             AND rr.generation = ( SELECT MAX(generation)
                                   FROM cbm_ana.simul_ref_run
                                   WHERE subproject_id = p.subproject_id )
           ORDER BY ref_run_id; */ 

  /* EXEC SQL OPEN refruns_cursor; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 3;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = sq0003;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )51;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqcmod = (unsigned int )0;
  sqlstm.sqhstv[0] = (         void  *)project;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)pstart;
  sqlstm.sqhstl[1] = (unsigned int  )0;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)pend;
  sqlstm.sqhstl[2] = (unsigned int  )0;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
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
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) goto errorfound;
}


  do {
    /* EXEC SQL FETCH refruns_cursor INTO :refruns INDICATOR :refruns_Ind; */ 

{
    struct sqlexd sqlstm;
    sqlorat((void **)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )2000;
    sqlstm.offset = (unsigned int  )78;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqfoff = (           int )0;
    sqlstm.sqfmod = (unsigned int )2;
    sqlstm.sqhstv[0] = (         void  *)refruns.rid;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )sizeof(int);
    sqlstm.sqindv[0] = (         void  *)refruns_Ind.rid_Ind;
    sqlstm.sqinds[0] = (         int  )sizeof(short);
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqharc[0] = (unsigned int   *)0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)refruns.rname;
    sqlstm.sqhstl[1] = (unsigned int  )83;
    sqlstm.sqhsts[1] = (         int  )84;
    sqlstm.sqindv[1] = (         void  *)refruns_Ind.rname_Ind;
    sqlstm.sqinds[1] = (         int  )sizeof(short);
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqharc[1] = (unsigned int   *)0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)refruns.ts;
    sqlstm.sqhstl[2] = (unsigned int  )21;
    sqlstm.sqhsts[2] = (         int  )21;
    sqlstm.sqindv[2] = (         void  *)refruns_Ind.ts_Ind;
    sqlstm.sqinds[2] = (         int  )sizeof(short);
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqharc[2] = (unsigned int   *)0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void  *)refruns.te;
    sqlstm.sqhstl[3] = (unsigned int  )21;
    sqlstm.sqhsts[3] = (         int  )21;
    sqlstm.sqindv[3] = (         void  *)refruns_Ind.te_Ind;
    sqlstm.sqinds[3] = (         int  )sizeof(short);
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqharc[3] = (unsigned int   *)0;
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
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto errorfound;
}


    nLast=sqlca.sqlerrd[2]-nTot;
    for (Int_t i=0;i<nLast;i++) {
      refruns.rname[i].arr[refruns.rname[i].len]='\0';
      CbmOraRunInfo* p=new CbmOraRunInfo((char*)(refruns.rname[i].arr));
      p->setRunId(refruns.rid[i]);
      refruns.ts[i][20]='\0';
      p->setStartTime((char*)(refruns.ts[i]));
      if (refruns_Ind.te_Ind[i]!=-1) {
        refruns.te[i][20]='\0';
        p->setEndTime((char*)(refruns.te[i]));
      }
      runsList->Add(p);
      nTot++;
    }
  } while (nLast==NMAX_INFO);
  /* EXEC SQL CLOSE refruns_cursor; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )109;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) goto errorfound;
}


  cout<<"*** Total number of runs: "<<nTot<<endl;
  return runsList;
errorfound:
  pConn->showSqlError("getListOfRuns");
  if (runsList) {
    runsList->Delete();
    delete runsList;
    runsList=0;
  }
  return 0;
}


Bool_t CbmOraInfo::getRefRunStart(const char* startAt,TString& pTime) {
  // gets the run start for a simulation reference run
  TString s(startAt);
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* pfile;
    int   pid;    
    char  ts[21];
  /* EXEC SQL END DECLARE SECTION; */ 

  /* EXEC SQL WHENEVER SQLERROR GOTO errorfound; */ 

  /* EXEC SQL WHENEVER NOT FOUND GOTO notfound; */ 

  pfile=0;
  pid=-1;
  if (s.Contains("-")) {
    pTime=startAt;
  } else {
    char c=startAt[0];
    if (c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9') {
      pid=atoi(startAt);
      /* EXEC SQL SELECT TO_CHAR(run_start,'DD-MON-YYYY HH24:MI:SS')
               INTO :ts
               FROM cbm_ana.simul_ref_run
               WHERE ref_run_id = :pid; */ 

{
      struct sqlexd sqlstm;
      sqlorat((void **)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "select TO_CHAR(run_start,'DD-MON-YYYY HH24:MI:SS') into\
 :b0  from cbm_ana.simul_ref_run where ref_run_id=:b1";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )124;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)ts;
      sqlstm.sqhstl[0] = (unsigned int  )21;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)&pid;
      sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) goto notfound;
      if (sqlca.sqlcode < 0) goto errorfound;
}


    } else {
      pfile=(char*)startAt;
      /* EXEC SQL SELECT TO_CHAR(run_start,'DD-MON-YYYY HH24:MI:SS')
               INTO :ts
               FROM cbm_ana.simul_ref_run
               WHERE ref_run_name = :pfile; */ 

{
      struct sqlexd sqlstm;
      sqlorat((void **)0, &sqlctx, &oraca);
      sqlstm.sqlvsn = 12;
      sqlstm.arrsiz = 4;
      sqlstm.sqladtp = &sqladt;
      sqlstm.sqltdsp = &sqltds;
      sqlstm.stmt = "select TO_CHAR(run_start,'DD-MON-YYYY HH24:MI:SS') into\
 :b0  from cbm_ana.simul_ref_run where ref_run_name=:b1";
      sqlstm.iters = (unsigned int  )1;
      sqlstm.offset = (unsigned int  )147;
      sqlstm.selerr = (unsigned short)1;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)256;
      sqlstm.occurs = (unsigned int  )0;
      sqlstm.sqhstv[0] = (         void  *)ts;
      sqlstm.sqhstl[0] = (unsigned int  )21;
      sqlstm.sqhsts[0] = (         int  )0;
      sqlstm.sqindv[0] = (         void  *)0;
      sqlstm.sqinds[0] = (         int  )0;
      sqlstm.sqharm[0] = (unsigned int  )0;
      sqlstm.sqadto[0] = (unsigned short )0;
      sqlstm.sqtdso[0] = (unsigned short )0;
      sqlstm.sqhstv[1] = (         void  *)pfile;
      sqlstm.sqhstl[1] = (unsigned int  )0;
      sqlstm.sqhsts[1] = (         int  )0;
      sqlstm.sqindv[1] = (         void  *)0;
      sqlstm.sqinds[1] = (         int  )0;
      sqlstm.sqharm[1] = (unsigned int  )0;
      sqlstm.sqadto[1] = (unsigned short )0;
      sqlstm.sqtdso[1] = (unsigned short )0;
      sqlstm.sqphsv = sqlstm.sqhstv;
      sqlstm.sqphsl = sqlstm.sqhstl;
      sqlstm.sqphss = sqlstm.sqhsts;
      sqlstm.sqpind = sqlstm.sqindv;
      sqlstm.sqpins = sqlstm.sqinds;
      sqlstm.sqparm = sqlstm.sqharm;
      sqlstm.sqparc = sqlstm.sqharc;
      sqlstm.sqpadto = sqlstm.sqadto;
      sqlstm.sqptdso = sqlstm.sqtdso;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
      if (sqlca.sqlcode == 1403) goto notfound;
      if (sqlca.sqlcode < 0) goto errorfound;
}


    }
    ts[20]='\0';    
    pTime=ts;
  }
  return kTRUE;
errorfound:
  pConn->showSqlError("getRefRunStart");
  return kFALSE;
notfound:
  Error("getRefRunStart","Simulation reference run not found for %s",startAt);
  return kFALSE;
}
