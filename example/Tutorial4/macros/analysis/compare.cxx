/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::ifstream;
using std::vector;
using std::cout;
using std::endl;
using std::fabs;

int main(int argc, char* argv[])
{
  // No good solution
  // TODO
  bool isFortranFile;
  if ( 2 == argc ) {
    isFortranFile = argv[1];
  }

  // Read the milepede output and the file with shifts created by
  // TestMillePede to compare if the correction have been correctly calculated

  int label;
  float value;
  float value2;
  vector<int> labelVector;
  vector<float> valueVector;

  if (!isFortranFile) {

    cout<<"Read file created by TestMillePede."<<endl;

    ifstream vInput;
    vInput.open("shifts.txt");
    if (!vInput.is_open()) {
      cout<<"Could not open the input file."<<endl;
      exit(1);
    }
    while (1) {
      vInput >> label >> value;
      if (!vInput.good()) { break; }
      labelVector.push_back(label);
      valueVector.push_back(value);
    }
    vInput.close();

  } else {

    cout<<"Read file created by pede."<<endl;

    ifstream vInput;
    vInput.open("shifts.txt");
    if (!vInput.is_open()) {
      cout<<"Could not open the input file."<<endl;
      exit(1);
    }
    while (1) {
      vInput >> label >> value >> value2;
      if (!vInput.good()) { break; }
      int label1=10+label*2;
      labelVector.push_back(label1);
      valueVector.push_back(value);
      label1=500+label;
      labelVector.push_back(label1);
      valueVector.push_back(value2);
    }
    vInput.close();
  }

  for(int c=0; c < (int)labelVector.size(); ++c) {
    cout <<"c, label,value:" << c <<", "<<labelVector[c]<<", "<<valueVector[c]<<endl;
  }

  std::vector<int>::iterator result;

  result = std::max_element(labelVector.begin(), labelVector.end());

  int maxValue = *result;

  float origShifts[maxValue+1];
  float recoShifts[maxValue+1];

  for (int i=0; i<maxValue+1; ++i) {
    origShifts[i] = 0;
    recoShifts[i] = 0;
  }

  for (int i=0; i<labelVector.size(); ++i) {
    origShifts[labelVector[i]] = valueVector[i];
  }

  labelVector.clear();
  valueVector.clear();

  ifstream vInput1;
  float dummy1, dummy2, dummy3, dummy4;
  vInput1.open("millepede.res");
  if (!vInput1.is_open()) {
    cout<<"Could not open the input file."<<endl;
    exit(1);
  }
  while (1) {
    vInput1 >> label >> value >> dummy1 >> dummy2 >> dummy3;
    if (!vInput1.good()) { break; }
    labelVector.push_back(label);
    valueVector.push_back(value);
    cout << label<<", "<<value<<endl;
  }
  vInput1.close();

  for(int c=0; c < (int)labelVector.size(); ++c) {
    cout <<"c, label,value:" << c <<", "<<labelVector[c]<<", "<<valueVector[c]<<endl;
  }

  for (int i=0; i<labelVector.size(); ++i) {
    recoShifts[labelVector[i]] = valueVector[i];
  }

  for (int i=0; i<labelVector.size(); ++i) {
    recoShifts[labelVector[i]] = valueVector[i];
  }

  int numBadValues = 0;
  int percent2 = 0;
  int percent3 = 0;
  int percent4 = 0;
  for (int i=0; i<maxValue+1; ++i) {
    float diff = recoShifts[i]+origShifts[i];
    float percent = fabs(diff/origShifts[i])*100;
    if ( percent > 1.) {
      cout<<i<<" : "<<recoShifts[i]<<", "<<origShifts[i]<<", "<<diff<<", "<<percent<<endl;
      numBadValues++;
    }
    if ( percent > 2.) {
      percent2++;
    }
    if ( percent > 3.) {
      percent3++;
    }
    if ( percent > 4.) {
      percent4++;
    }
  }
  cout<<numBadValues<<" corrections with a deviation > 1%"<<endl;
  cout<<percent2<<" corrections with a deviation > 2%"<<endl;
  cout<<percent3<<" corrections with a deviation > 3%"<<endl;
  cout<<percent4<<" corrections with a deviation > 4%"<<endl;
}
