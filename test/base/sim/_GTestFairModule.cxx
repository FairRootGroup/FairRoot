/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairModule.h"

#include "FairTestNewOutputHandler.h"

#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <string>
#include <boost/regex.hpp>

//TEST(FairModuleTrueTest, TestBasicWorking)
//{
//  // basic check if everything works the test should be always true
//  EXPECT_TRUE(true);
//}


TEST(FairModuleSetGeometryFile, CorrectAbsolutePath)
{
  char* workdir;
  workdir = getenv ("VMCWORKDIR");

  if (workdir==NULL) {
    ASSERT_TRUE(false) <<"No environment variable VMCWORKDIR definied" << std::endl ;
  }

  std::string geofile(workdir);
  geofile += "/geometry/cave.geo";

  // Output is of level debug
  FairLogger* fLogger;
  fLogger = FairLogger::GetLogger();
  fLogger->SetLogScreenLevel("DEBUG");

  //Create new FairModule to test
  FairModule test;

  // Catch the output
  FairTestNewOutputHandler handler(true, true);

  // Set an existing filename
  test.SetGeometryFileName(geofile);

  // there should be only one line
  int lines = handler.GetNumberOfLines();
  EXPECT_EQ(lines,1);

  // Test if screen output is as expected
  std::string regexString = "\\[DEBUG  \\] : using geometry file .*cave.geo";
  const boost::regex e(regexString);
  EXPECT_TRUE(regex_match(handler.GetCaptureLine(0), e));

}


TEST(FairModuleSetGeometryFile, CorrectGeomPathEnvVariable)
{

  // Set an environment variable GEOMPATH where to look for
  // geometry files

  char the_path[256];
  getcwd(the_path, 255);

  std::string geompath = "GEOMPATH=";
  geompath += the_path;
  const char* path = geompath.c_str();
  putenv(const_cast<char*>(path));
  std::string geofile = "cave.geo";

  // Output is of level debug
  FairLogger* fLogger;
  fLogger = FairLogger::GetLogger();
  fLogger->SetLogScreenLevel("DEBUG");

  //Create new FairModule to test
  FairModule test;

  // Catch the output
  FairTestNewOutputHandler handler(true, true);

  // Set an existing filename
  test.SetGeometryFileName(geofile);

  int lines = handler.GetNumberOfLines();
  EXPECT_EQ(lines,1);

  // Test if screen output is as expected
  std::string regexString = "\\[DEBUG  \\] : using geometry file ";
  regexString += the_path;
  regexString += "/";
  regexString += geofile;
  const boost::regex e(regexString);
  EXPECT_TRUE(regex_match(handler.GetCaptureLine(0), e));

}

TEST(FairModuleSetGeometryFile, WrongGeomPathEnvVariable)
{

  // Set an environment variable GEOMPATH where to look for
  // geometry files

  std::string geompath = "GEOMPATH=/tmp/";
  const char* path = geompath.c_str();
  putenv(const_cast<char*>(path));
  std::string geofile = "cave.geo";

  // Output is of level debug
  FairLogger* fLogger;
  fLogger = FairLogger::GetLogger();
  fLogger->SetLogScreenLevel("DEBUG");

  //Create new FairModule to test
  FairModule test;

  // Catch the output
  FairTestNewOutputHandler handler(true, true);

  // Set an existing filename
  test.SetGeometryFileName(geofile);

  int lines = handler.GetNumberOfLines();
  EXPECT_EQ(lines,2);

  // Test if screen output is as expected
  std::string regexString = "\\[DEBUG  \\] : geometry file ";
  regexString += geofile;
  regexString += " not found in GEOMPATH /tmp/";
  const boost::regex e(regexString);

  EXPECT_TRUE(regex_match(handler.GetCaptureLine(0), e));


  char* workdir;
  workdir = getenv ("VMCWORKDIR");

  regexString = "\\[DEBUG  \\] : using geometry file ";
  regexString += workdir;
  regexString += "/geometry/";
  regexString += geofile;
  const boost::regex f(regexString);
  EXPECT_TRUE(regex_match(handler.GetCaptureLine(1), f));

}


TEST(FairModuleSetGeometryFile, WrongAbsolutePath)
{
  FairModule test;

  FairTestNewOutputHandler handler(false, true);

  // I am not bale to catch the output and get it back to compare
  // it with the expected string. Also defining a regex in EXPECT_DEATH
  // does not work. If I do this the comparison is always wrong and the
  // test case fails

  //std::cerr.flush();
  //std::cout.flush();
  //  std::cerr << "BLA BLA BLA" << std::endl;
  // Check that the program stops the execution when a geometry file
  // with absolut path isn't found
  EXPECT_DEATH(test.SetGeometryFileName("/tmp/bla"),"");
  //std::cerr.flush();
  //std::cout.flush();
  //int lines = handler.GetNumberOfLines();
  //std::cout << "NOL: " << lines << std::endl;
  //  for (int i = 0; i < lines; ++i) {
  //    std::cout << "Content: " << handler.GetCaptureLine(i) << std::endl;
  //  }
}

TEST(FairModuleSetGeometryFile, FileNotExist)
{
  FairModule test;

  FairTestNewOutputHandler handler(false, true);

  EXPECT_DEATH(test.SetGeometryFileName("cave1.geo"),"");
}
