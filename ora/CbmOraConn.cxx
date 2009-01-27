
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
    "FairOraConn.pc"
};


static unsigned int sqlctx = 567307;


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

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,0,0,27,104,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,0,0,32,124,0,0,0,0,0,1,0,
51,0,0,3,0,0,32,140,0,0,0,0,0,1,0,
66,0,0,4,0,0,27,210,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,10,0,0,1,10,0,0,
97,0,0,5,59,0,6,225,0,0,1,1,0,1,0,2,3,0,0,
116,0,0,6,66,0,6,266,0,0,2,2,0,1,0,3,3,0,0,2,3,0,0,
139,0,0,7,152,0,6,291,0,0,2,2,0,1,0,1,97,0,0,2,97,0,0,
162,0,0,8,153,0,6,317,0,0,2,2,0,1,0,1,97,0,0,2,97,0,0,
185,0,0,9,159,0,6,344,0,0,2,2,0,1,0,1,3,0,0,2,97,0,0,
};


//*-- AUTHOR : Ilse Koenig
//*-- Created : 26/11/2004 by I.Koenig

/////////////////////////////////////////////////////////////
// FairOraConn
//
// Connection class to database Oracle 
// (uses the Oracle C/C++ precompiler)
//
/////////////////////////////////////////////////////////////
using namespace std;
#include "FairOraConn.h"
#include "TRandom.h"
#include "stdio.h"
#include "iostream>
#include <iomanip>
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "termios.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "unistd.h"

// Oracle communication area
#include "oraca.h"
// SQL Communications Area
#include "sqlca.h"
 
ClassImp(FairOraConn)

FairOraConn::FairOraConn() {
  // default constructor
  // defines default values for user ("CBM_ANA_PUBLIC") and the database
  //   ("db-cbm.oracle.gsi.de", the CBM Oracle database on Linux at GSI)
  // User CBM_ANA_PUBLIC has Readonly access to the Oracle tables.
  // The connection to Oracle is not opened!
  strcpy(dbName,"db-cbm");
  strcpy(userName,"cbm_ana_public");
  isConnected=kFALSE;
  actRunId=-1;
  runStart=-1;
  historyDate[0]='\0';
  needsServerCheck=kTRUE;
}


FairOraConn::~FairOraConn() {
  // default destructor (closes connection)
  close();
}


Bool_t FairOraConn::open() {
  // opens default connection with readonly access
  char* password = new char[9];
  strcpy(password,"cbm");
  Bool_t rc=openConnection(password);
  if (!rc) close();
  return rc;
}

Bool_t FairOraConn::open(char *uName) {
  // opens connection to database db-cbm for user given by name
  // asks for password
  strncpy(userName,uName,30);
  char* password=getPassword();
  Bool_t rc=openConnection(password);
  if (!rc) close();
  return rc;
}


Bool_t FairOraConn::open(char *dbN, char *uN) {
  // opens connection to database with name dbName for user given by name
  // asks for password
  strncpy(dbName,dbN,30);
  strncpy(userName,uN,30);
  char* password=getPassword();
  Bool_t rc=openConnection(password);
  if (!rc) close();
  return rc;
}


Bool_t FairOraConn::reconnect() {
  // opens connection (contains the SQL-statements)
  if (isConnected) return kTRUE;
  if (strcmp(userName,"cbm_ana_public")!=0) return kFALSE;
  char connId[80];
  char password[]={"cbm"};
  strcpy(connId,userName);
  strcat(connId,"@");
  strcat(connId,dbName);
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* uName;
    char* pWord;
  /* EXEC SQL END DECLARE SECTION; */ 

  uName=connId;
  pWord=password;
  /* EXEC SQL WHENEVER SQLERROR DO
    showSqlError("openConnection(char*)","Wrong user/password"); */ 

  /* EXEC SQL CONNECT :uName IDENTIFIED BY :pWord; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )10;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)uName;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)pWord;
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
  sqlstm.sqlcmax = (unsigned int )100;
  sqlstm.sqlcmin = (unsigned int )2;
  sqlstm.sqlcincr = (unsigned int )1;
  sqlstm.sqlctimeout = (unsigned int )0;
  sqlstm.sqlcnowait = (unsigned int )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) showSqlError("openConnection(char*)","Wrong user/password");
}


  if (sqlca.sqlcode==0) {
    isConnected=kTRUE;
    setHistoryDate(historyDate);
  } else Error("reconnect()","*** Failed to connect to Oracle ***");
  return isConnected; 
}


void FairOraConn::close() {
  // disconnects from ORACLE
  // A transaction will be automatically rolled back,
  // that means changes in the database are not stored
  // without an explicit COMMIT
  actRunId=-1;
  runStart=-1;
  historyDate[0]='\0';
  /* EXEC SQL WHENEVER SQLERROR DO
    showSqlError("close()"); */ 

  if (isConnected) {
    /* EXEC SQL ROLLBACK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlorat((void **)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )36;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) showSqlError("close()");
}


    isConnected=kFALSE;
    cout<<"connection to Oracle closed"<<endl;
  }
  needsServerCheck=kTRUE;
}


void FairOraConn::disconnect() {
  // disconnects from ORACLE
  // may be opened again via reconnect()
  if (isConnected) {
    actRunId=-1;
    runStart=-1;
    /* EXEC SQL WHENEVER SQLERROR DO
      showSqlError("disconnect()"); */ 

    /* EXEC SQL ROLLBACK RELEASE; */ 

{
    struct sqlexd sqlstm;
    sqlorat((void **)0, &sqlctx, &oraca);
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )51;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)256;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) showSqlError("disconnect()");
}


    isConnected=kFALSE;
    cout<<"connection to Oracle closed"<<endl;
    needsServerCheck=kTRUE;
  }
}


void FairOraConn::print() {
  // prints information about the database connection
  if (isConnected)
    cout<<"Oracle-Database: "<<dbName<<"    Username: "<<userName<<'\n';
  else cout<<"*** no connection to Oracle established  ***\n";
  if (strlen(historyDate)==0) cout<<"No history date set\n";
  else cout<<"History date: "<<historyDate<<'\n';
}


void FairOraConn::showSqlError(const char* fctName,const char* msg) {
  // shows SQL error messages
  if (msg)
    Error(fctName,"\n%s\n%s\n",sqlca.sqlerrm.sqlerrmc,msg);
  else Error(fctName,"\n%s\n",sqlca.sqlerrm.sqlerrmc);
}


char* FairOraConn::getPassword() {
  // asks for the password
  char* passwd = new char[20];
  char buf[20];
  int ttyfd = 0;
  struct termios tio, itio;
  if ((ttyfd = ::open("/dev/tty", O_RDWR)) < 0) {
    fprintf(stderr, "cannot open tty, using stdin\n");
    ttyfd = 0;
  }
  if (tcgetattr(ttyfd, &tio) < 0) {
    fprintf (stderr, "\nUnable to get terminal characteristics: ");
    cout<<"enter password for user "<<userName<<" > ";
    scanf("%[^\n]%*c",passwd);
    return passwd; 
  }
  itio = tio;
  tio.c_lflag &= ~(ECHO|ICANON);         
  tcsetattr (ttyfd, TCSAFLUSH, &tio);
  cout<<"enter password for user "<<userName<<" > ";
  fgets(buf, 20, stdin);
  tcsetattr (ttyfd, TCSAFLUSH, &itio);
  //close(ttyfd);
  sscanf(buf, "%s", passwd);
  cout<<endl;
  return passwd;
}


Bool_t FairOraConn::openConnection(char* password) {
  // opens connection (contains the SQL-statements)
  if (isConnected) close();
  char connId[80];
  strcpy(connId,userName);
  strcat(connId,"@");
  strcat(connId,dbName);
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* uName;
    char* pWord;
  /* EXEC SQL END DECLARE SECTION; */ 

  uName=connId;
  pWord=password;
  /* EXEC SQL WHENEVER SQLERROR DO
    showSqlError("openConnection(char*)","Wrong user/password"); */ 

  /* EXEC SQL CONNECT :uName IDENTIFIED BY :pWord; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )10;
  sqlstm.offset = (unsigned int  )66;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)uName;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)pWord;
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
  sqlstm.sqlcmax = (unsigned int )100;
  sqlstm.sqlcmin = (unsigned int )2;
  sqlstm.sqlcincr = (unsigned int )1;
  sqlstm.sqlctimeout = (unsigned int )0;
  sqlstm.sqlcnowait = (unsigned int )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
  if (sqlca.sqlcode < 0) showSqlError("openConnection(char*)","Wrong user/password");
}


  if (sqlca.sqlcode==0) isConnected=kTRUE;
  else cout<<"*** Failed to connect to Oracle ***"<<endl;
  delete password;
  actRunId=-1;
  runStart=0;
  historyDate[0]='\0';
  return isConnected; 
}

Int_t FairOraConn::checkServerLoad() {
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    int retval; 
  /* EXEC SQL END DECLARE SECTION; */ 

  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */ 

  /* EXEC SQL EXECUTE
    BEGIN
      :retval := cbm_util.check_analysis_sessions;
    END;
  END-EXEC; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "begin :retval := cbm_util . check_analysis_sessions ; END ;";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )97;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&retval;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
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
  if (sqlca.sqlcode < 0) goto notfound;
}


  return retval;
notfound:
  showSqlError("checkServerLoad");
  return -1; 
}

Int_t FairOraConn::getRunStart(Int_t id) {
  // Gets the actual run id from the current event file and compares it with
  // the last used actRunId for fetching data.
  // If they are different, the run start time (converted to ansi C time) is
  // read from Oracle and stored together with the run id in the data members
  // run_id and runStart
  if (id==actRunId && runStart!=0) return runStart;
  if (needsServerCheck) {
    Int_t l=0;
    UInt_t nTotWait=0;
    l=checkServerLoad();
    while (l==0&&nTotWait<86400000) {
      UInt_t nWait=10000+gRandom->Integer(20000);
      nTotWait+=nWait;
      cout<<"Oracle server busy, retry in "<<nWait/1000<<" seconds"<<endl;
      usleep(nWait*1000);
      l=checkServerLoad();
    }
    if (l>0) needsServerCheck=kFALSE;
    else return -1;
  }
  if (strlen(historyDate)==0) setParamRelease(id);
  actRunId=id;
  runStart=-1;
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    int ri; 
    int rs;
  /* EXEC SQL END DECLARE SECTION; */ 

  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */ 

  ri = actRunId;
  /* EXEC SQL EXECUTE
    BEGIN
      cbm_ana.cbmrun_query.get_run_start(:ri,:rs);
    END;
  END-EXEC; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "begin cbm_ana . cbmrun_query . get_run_start ( :ri , :rs ) \
; END ;";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )116;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&ri;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&rs;
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
  if (sqlca.sqlcode < 0) goto notfound;
}


  if (ri==(int)actRunId) {
    runStart=rs;
    /* cout<<"actRunId: "<<actRunId<<"   runStart: "<<runStart<<endl; */
    return runStart;
  }
notfound:
  Error("getRunStart(Int_t)","Run not found!\n\n");
  return -1; 
}


Bool_t FairOraConn::setHistoryDate(const char* dateString) {
  // Sets the date to retrieve historic data
  // Returns kFALSE when the date string cannot be converted to a valid date.
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* d;
    char rd[21];
  /* EXEC SQL END DECLARE SECTION; */ 

  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */ 

  d=(char*)dateString;
  /* EXEC SQL EXECUTE
    BEGIN
      cbm_ana.cbmrun_query.set_history_date(:d);
      :rd := to_char(cbm_ana.cbmrun_query.get_history_date,'DD-MON-YYYY HH24:MI:SS');
    END;
  END-EXEC; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "begin cbm_ana . cbmrun_query . set_history_date ( :d ) ; :r\
d := to_char ( cbm_ana . cbmrun_query . get_history_date , 'DD-MON-YYYY HH24:M\
I:SS' ) ; END ;";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )139;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)d;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)rd;
  sqlstm.sqhstl[1] = (unsigned int  )21;
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
  if (sqlca.sqlcode < 0) goto notfound;
}


  rd[20]='\0';
  strcpy(historyDate,rd);
  cout<<"*************************************************************\n";
  cout<<"     Oracle history date: "<<historyDate<<"\n";
  cout<<"*************************************************************\n";
  return kTRUE;
notfound:
  showSqlError("setHistoryDate(Int_t)");
  return kFALSE;
}

Bool_t FairOraConn::setParamRelease(const char* release_name) {
  // Sets the history date to the creation date of the parameter release give by name
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    char* r;
    char rd[21];
  /* EXEC SQL END DECLARE SECTION; */ 

  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */ 

  rd[0]='\0';	
  r=(char*)release_name;
  /* EXEC SQL EXECUTE
    BEGIN
      cbm_ana.cbmrun_query.set_param_release(:r);
      :rd := to_char(cbm_ana.cbmrun_query.get_history_date,'DD-MON-YYYY HH24:MI:SS');
    END;
  END-EXEC; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "begin cbm_ana . cbmrun_query . set_param_release ( :r ) ; :\
rd := to_char ( cbm_ana . cbmrun_query . get_history_date , 'DD-MON-YYYY HH24:\
MI:SS' ) ; END ;";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )162;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)r;
  sqlstm.sqhstl[0] = (unsigned int  )0;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)rd;
  sqlstm.sqhstl[1] = (unsigned int  )21;
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
  if (sqlca.sqlcode < 0) goto notfound;
}


  rd[20]='\0';
  strcpy(historyDate,rd);
  cout<<"*************************************************************\n";
  cout<<"     Oracle history date: "<<historyDate<<"\n";
  cout<<"*************************************************************\n";
  return kTRUE;
notfound:
  showSqlError("setParamRelease(const char*)");
  return kFALSE;
}

Bool_t FairOraConn::setParamRelease(Int_t run) {
  // Sets the history date to the creation date of the parameter release
  // for the corresponding experiment
  /* EXEC SQL BEGIN DECLARE SECTION; */ 

    int r;
    char rd[21];
  /* EXEC SQL END DECLARE SECTION; */ 

  /* EXEC SQL WHENEVER SQLERROR GOTO notfound; */ 

  r=run;
  rd[0]='\0';
  /* EXEC SQL EXECUTE
    BEGIN
      cbm_ana.cbmrun_query.set_history_date_by_run(:r);	
      :rd := to_char(cbm_ana.cbmrun_query.get_history_date,'DD-MON-YYYY HH24:MI:SS');
    END;
  END-EXEC; */ 

{
  struct sqlexd sqlstm;
  sqlorat((void **)0, &sqlctx, &oraca);
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "begin cbm_ana . cbmrun_query . set_history_date_by_run ( :r\
 ) ; :rd := to_char ( cbm_ana . cbmrun_query . get_history_date , 'DD-MON-YYYY\
 HH24:MI:SS' ) ; END ;";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )185;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&r;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)rd;
  sqlstm.sqhstl[1] = (unsigned int  )21;
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
  if (sqlca.sqlcode < 0) goto notfound;
}


  rd[20]='\0';
  strcpy(historyDate,rd);
  cout<<"*************************************************************\n";
  cout<<"     Oracle history date: "<<historyDate<<"\n";
  cout<<"*************************************************************\n";
  return kTRUE;
notfound:
  showSqlError("setParamRelease(Int_t)");
  return kFALSE;
}
