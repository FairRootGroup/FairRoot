#include "ValValidate.h"

#include "ValContext.h"
#include "ValRange.h"

#include "TFile.h"
#include "TSystem.h"

#include <iomanip>
#include <map>

ClassImp(ValValidate)

//______________________________________________________________________________
ValValidate::ValValidate()
{

}

//______________________________________________________________________________
ValValidate::~ValValidate()
{
  // delete all the owned sub-objects

}

//______________________________________________________________________________
Bool_t ValValidate::RunAllTests()
{
  Int_t fail  = 0;
  Int_t tests = 0;

  tests++;
  if (!TestTimeStamp()) { fail++; }

  tests++;
  if (!TestContext()) { fail++; }

  tests++;
  if (!TestRange()) { fail++; }

  tests++;
  if (!TestFileIO()) { fail++; }


  cout   << "-I- ValValidate::RunAllTests had " << fail
         << " failures in " << tests << " tests"
         << endl << endl;

  return (!fail);

}

//______________________________________________________________________________
Bool_t ValValidate::TestTimeStamp(void)
{
  // Test ValTimeStamp behaviour

  cout << "-I- Test ValTimeStamp" << endl << endl;

  Int_t fail = 0;
  Int_t tests = 0;

  ValTimeStamp defctor;
  defctor.Print("");


  time_t nowtime;
  time(&nowtime);
  long int nsec = 12345;

  struct timespec nowts;
  nowts.tv_sec  = nowtime;
  nowts.tv_nsec = nsec;


  cout << "-I- original timespec:  {" << nowtime << "," << nsec << "} " << endl;

  ValTimeStamp vldnow(nowts);
  // reuses a common buffer space

  cout << " -I- vldnow as timespec: " << vldnow.AsString("2") << endl;
  cout << " vldnow default AsString: " << vldnow.AsString("") << endl;

  cout << " vldnow local   AsString: " << vldnow.AsString("l") << endl;

  struct timespec thents = vldnow.GetTimeSpec();

  cout   << " recovered timespec: {" << thents.tv_sec << "," << thents.tv_nsec << "} " << endl;

  tests++;
  if (nowts.tv_sec != thents.tv_sec || nowts.tv_nsec != thents.tv_nsec) { fail++; }


  // test various ctor's
  // all should map to Jan 04 2001, 01:26:03 GMT
  time_t   mytime = 978571563;
  Long_t   arbitrary = 123456; // fake nsec part

  timespec mytimespec = {mytime,arbitrary};
  ValTimeStamp vtr(mytime,arbitrary);
  ValTimeStamp vtsr(mytimespec);

  Int_t    year  = 2001;
  Int_t    month = 1;
  Int_t    day   = 4;
  Int_t    hour  = 1;
  Int_t    min   = 26;
  Int_t    sec   = 3;
  Int_t    secOffset = vtr.GetZoneOffset();

  ValTimeStamp vl1(year,month,day,hour,min,sec,arbitrary);
  ValTimeStamp vl2(year,month,day,hour,min,sec,arbitrary,kFALSE,-secOffset);
  ValTimeStamp vl3(year,month,day,hour-8,min,sec,arbitrary,kTRUE,8*60*60);
  ValTimeStamp vl4(year,month,day-1,hour+16,min,sec,arbitrary,kTRUE,8*60*60);
// this will only give correct results in PST zone
  ValTimeStamp vlpst(year,month,day,hour-8,min,sec,arbitrary,kFALSE);

  ValTimeStamp vly1(year-1900,month,day,hour,min,sec,arbitrary);
  ValTimeStamp vly2(year-2000,month,day,hour,min,sec,arbitrary);

  Int_t    date = year*10000 + month*100 + day;
  Int_t    time = hour*10000 + min*100 + sec;

  ValTimeStamp vs1(date,time,arbitrary);
  ValTimeStamp vs2(date,time,arbitrary,kFALSE,-secOffset);
// these next two aren't a smart way of dealing with local time
  ValTimeStamp vs3(date-1,time+160000,arbitrary,kTRUE,8*60*60);
  ValTimeStamp vs4(date,time-80000,arbitrary,kTRUE,8*60*60);
// the next two will only give correct results in PST zone
  ValTimeStamp vspst1(date,time-80000,arbitrary,kFALSE);
  ValTimeStamp vspst2(date-1,time+160000,arbitrary,kFALSE);
  ValTimeStamp vsy1(date-19000000,time,arbitrary);
  ValTimeStamp vsy2(date-20000000,time,arbitrary);

  cout  << " current TimeOffset is " << vtr.GetZoneOffset() << endl;

  cout << " std (vtr) " << vtr.AsString()  << endl;

  TString byhand = "Thu, 04 Jan 2001 01:26:03 +0000 (GMT) +   123456 nsec";
  TString byclass = vtr.AsString();
  tests++;
  if (byhand != byclass) {
    cout << " strings don't match!" << endl;
    fail++;
  } else {
    cout << " strings match as they should " << endl;
  }

  tests++;
  if (!CompareTimeStamps(" vtsr     ",vtsr,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vl1      ",vl1,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vl2      ",vl2,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vl3      ",vl3,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vl4      ",vl4,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vly1     ",vly1,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vly2     ",vly2,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vs1      ",vs1,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vs2      ",vs2,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vs3      ",vs3,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vs4      ",vs4,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vsy1     ",vsy1,vtr)) { fail++; }
  tests++;
  if (!CompareTimeStamps(" vsy2     ",vsy2,vtr)) { fail++; }

  if (secOffset == 28800) {
    tests++;
    if (!CompareTimeStamps(" vlpst    ",vlpst,vtr)) { fail++; }
    tests++;
    if (!CompareTimeStamps(" vspst1   ",vspst1,vtr)) { fail++; }
    tests++;
    if (!CompareTimeStamps(" vspst2   ",vspst2,vtr)) { fail++; }
  }

  cout << " next test expects to be a mismatch" << endl;
  CompareTimeStamps(" now is unlikely to match arbitrary time ",vldnow,vtr);

  cout << " Alternative formats" << endl;
  cout << " \"\"       " << vtr.AsString("")   << endl;
  cout << " \"l\"      " << vtr.AsString("l")  << endl;
  cout<< " \"c\"      " << vtr.AsString("c")  << endl;
  cout << " \"lc\"     " << vtr.AsString("lc") << endl;
  cout << " \"2\"      " << vtr.AsString("2")  << endl;

  tests++;
  if (vtr.GetDate() != date) { fail++; }
  tests++;
  if (vtr.GetTime() != time) { fail++; }


  cout   << "  GMT    GetDate: " << vtr.GetDate()
         << "   GetTime: " << vtr.GetTime() << endl;

  cout   << "  local  GetDate: " << vtr.GetDate(kFALSE)
         << "   GetTime: " << vtr.GetTime(kFALSE) << endl;

  cout   << "ValValidate::TestTimeStamp had " << fail
         << " failures in " << tests << " tests"
         << endl << endl;

  return (!fail);

}

//______________________________________________________________________________
Bool_t ValValidate::CompareTimeStamps(const char* label,
                                      ValTimeStamp& test, ValTimeStamp& std)
{
  if (test == std) {
    cout << label << "    exact match " << endl;
    return kTRUE;
  } else {
    cout << label << " ** mismatch ** " << endl;
    cout << "            " << test.AsString() << endl;
    cout<< "            " << std.AsString() << endl;
    return kFALSE;
  }
}

//______________________________________________________________________________
Bool_t ValValidate::TestContext(void)
{
  // Test ValContext

  cout << "Test ValContext" << endl << endl;

  Int_t fail = 0;

  map<ValContext,long> vldc_map;
  long int entry = 0;

  ValContext defctor;
  cout<< "ValContext default ctor: "
      << defctor.AsString("") << endl;
  vldc_map[defctor] = entry++;
//   gSystem->Sleep(2000); // sleep for 2 sec so timestamp advances

  ValContext defctor2;
  vldc_map[defctor2] = entry++;
//   gSystem->Sleep(2000); // sleep for 2 sec so timestamp advances

  // for the same timestamp try different combinations of detector & simflag
  // in the expected order that it will sort
  // (detector primary over simflag --> detector in outer loop)
  cout << endl << "ValContext test map<ValContext,long>" << endl;
  ValTimeStamp now;
  for (Int_t ibit_det = 0; ibit_det<3; ibit_det++) {
    Detector::Detector_t det =
      (Detector::Detector_t) (1<<ibit_det);
    for (Int_t ibit_sim = 0; ibit_sim<4; ibit_sim++) {
      SimFlag::SimFlag_t sim = (SimFlag::SimFlag_t) (1<<ibit_sim);

      ValContext vldc(det,sim,now);
      vldc_map[vldc] = entry++;

    }
  }
  typedef map<ValContext,long>::const_iterator vcl_itr;
  int expect = 0;
  bool pass  = true;
  for (vcl_itr p = vldc_map.begin(); p != vldc_map.end(); ++p, ++expect) {
    ValContext ac = p->first;
    long       al = p->second;
    if (al != expect) { pass = false; }

    cout  << "   " << setw(2) << expect << " ? " << setw(2) << al << " : "
          << ac.AsString()
          << endl;
  }
  if (!pass) { fail++; }



  cout << "ValValidate::TestContext had " << fail << " failures "
       << endl << endl;

  return (!fail);
}

//______________________________________________________________________________
Bool_t ValValidate::TestRange(void)
{
  // Test ValRange

  cout << "Test ValRange" << endl << endl;

  Int_t fail = 0;

  ValRange defctor;
  defctor.Print("");


  cout   << "ValValidate::TestRange had " << fail << " failures "
         << endl << endl;

  return (!fail);

}

//______________________________________________________________________________
Bool_t ValValidate::TestFileIO(void)
{
  // Test write/read Validity objects to/from a file

  cout << "Test file IO" << endl << endl;

//   UInt_t sleep_msec = 2000;

  // ****************** OUTPUT *******************************

  TFile fout("vld_io.root","RECREATE");

  ValTimeStamp out_ts;
  ValContext   out_c;
  ValRange     out_r;

//ValTimeStamp not derived from TObject
//   out_ts.Write();
  out_c.Write();
  out_r.Write();

  fout.ls();
  fout.Close();

  // ****************** Pause *******************************

//   gSystem->Sleep(sleep_msec);
  ValContext pause_c;

  // ****************** INPUT *******************************

  TFile fin("vld_io.root","READ");
  fin.ls();

//   ValTimeStamp *in_ts = dynamic_cast<ValTimeStamp*>(fin.Get("ValTimeStamp"));
  ValContext* in_c = dynamic_cast<ValContext*>(fin.Get("ValContext"));

  fin.Close();

  // ****************** Comparison *******************************


//   gSystem->Sleep(sleep_msec);
  ValContext final_c;

  cout << " wrote  ValContext: " << out_c << endl;
  cout << " interm ValContext: " << pause_c << endl;
  cout << " read   ValContext: " << (*in_c) << endl;
  cout << " final  ValContext: " << final_c << endl;

  Int_t fail = 0;

  cout   << "ValValidate::TestRange had " << fail << " failures "
         << endl << endl;

  return (!fail);

}

//______________________________________________________________________________
