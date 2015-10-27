 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
If(GEANT3_FOUND)
 add_subdirectory (passive)
 add_subdirectory (mcstack)

 add_subdirectory (Tutorial1)
 add_subdirectory (Tutorial2)
 add_subdirectory (Tutorial3)
 add_subdirectory (Tutorial4)
 If(WITH_DBASE)
  add_subdirectory (Tutorial5)
 EndIf()

 If(POS_C++11)
  add_subdirectory(Tutorial7)
 EndIf()
 add_subdirectory (rutherford)
EndIf()

add_subdirectory(Tutorial8)
