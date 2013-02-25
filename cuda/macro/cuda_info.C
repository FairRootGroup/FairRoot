cuda_info()
{
  //Load the library
  gSystem->Load("libcudaintrface.so");
  //Create the cuda instance
  FairCuda *Cuda = new FairCuda();
  //call the function to run on the GPU
  Cuda->DeviceInfo_();

}