Cmake_Minimum_Required(VERSION 2.6.0 FATAL_ERROR)

Project(SVN_VERSION NONE)

set(CMAKE_MODULE_PATH "$ENV{SIMPATH}/scripts")            
include(GenerateVersionInfo)

