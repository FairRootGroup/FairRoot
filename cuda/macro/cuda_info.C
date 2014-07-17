/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
cuda_info()
{
  //Load the library
  gSystem->Load("libcudaintrface.so");
  //Create the cuda instance
  FairCuda *Cuda = new FairCuda();
  //call the function to run on the GPU
  Cuda->DeviceInfo_();

}