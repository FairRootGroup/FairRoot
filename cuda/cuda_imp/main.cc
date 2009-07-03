#include "stdio.h"  

// Forward declare the function  
extern "C" void DeviceInfo();
//extern "C" void runTest(int argc);

int main(int argc, char **argv)  
{  
    DeviceInfo();
    return 0;  
}  



