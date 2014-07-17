 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
 # Configure FairVersion.h
 # ------------------------------

 Find_Package(Subversion)
 
 If(Subversion_FOUND AND EXISTS ${SOURCE_DIR}/.svn/ )
      Subversion_WC_INFO(${SOURCE_DIR} PROJECT)
      Set(FAIRROOT_SVN_REVISION ${PROJECT_WC_REVISION})
      Set(FAIRROOT_SVN_BRANCH ${PROJECT_WC_URL})
      Set(FAIRROOT_SVN_DATE ${PROJECT_WC_LAST_CHANGED_DATE})
#     String(REGEX MATCH "[^/]+$" FAIRROOT_SVN_BRANCH ${FAIRROOT_SVN_BRANCH})
      Message(STATUS "FairRoot Revision - ${FAIRROOT_SVN_REVISION} Branch - ${FAIRROOT_SVN_BRANCH}")
      if(FAIRROOT)
          Configure_File(${FAIRROOT}/scripts/FairVersion.h.tmp ${BINARY_DIR}/FairVersion.h @ONLY)
      else(FAIRROOT)  
          Configure_File(${SOURCE_DIR}/cmake/scripts/FairVersion.h.tmp ${BINARY_DIR}/FairVersion.h @ONLY)
      endif(FAIRROOT)
  
 Else(Subversion_FOUND AND EXISTS ${SOURCE_DIR}/.svn/ )
      if(FAIRROOT)
          Configure_File(${FAIRROOT}/scripts/FairVersion.h.default ${BINARY_DIR}/FairVersion.h COPYONLY)
      else(FAIRROOT) 
          Configure_File(${SOURCE_DIR}/cmake/scripts/FairVersion.h.default ${BINARY_DIR}/FairVersion.h COPYONLY)
      endif(FAIRROOT)
 EndIf(Subversion_FOUND AND EXISTS ${SOURCE_DIR}/.svn/ )

 Execute_Process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
       ${BINARY_DIR}/FairVersion.h ${INCLUDE_OUTPUT_DIRECTORY}/FairVersion.h)

