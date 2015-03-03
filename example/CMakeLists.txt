 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
add_subdirectory (passive)
add_subdirectory (mcstack)

add_subdirectory (Tutorial1)
add_subdirectory (Tutorial2)
add_subdirectory (Tutorial3)
add_subdirectory (Tutorial4)
If(WITH_DBASE)
  add_subdirectory (Tutorial5)
  add_subdirectory (Tutorial6)
EndIf()

If(NOT CMAKE_CXX_FLAGS)
Message(STATUS "No C++11 support found. Tutorial7 will not be build.")
Else()
String(FIND ${CMAKE_CXX_FLAGS} "-std=c++11" POS_C++11)
If(${POS_C++11} EQUAL -1)
Message(STATUS "No C++11 support found. Tutorial7 will not be build.")
Else()
Message(STATUS "C++11 support found. Build Tutorial7 library.")
add_subdirectory(Tutorial7)
EndIf()
EndIf()

add_subdirectory (rutherford)


