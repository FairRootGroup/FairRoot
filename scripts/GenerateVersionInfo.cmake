  # Configure FairVersion.h
  # ------------------------------

  Find_Package(Subversion)

  If(Subversion_FOUND AND EXISTS $ENV{SIMPATH}/.svn/ )
    Subversion_WC_INFO($ENV{SIMPATH} PROJECT)
    Set(FAIRROOT_SVN_REVISION ${PROJECT_WC_REVISION})
    Set(FAIRROOT_SVN_BRANCH ${PROJECT_WC_URL})
    Set(FAIRROOT_SVN_DATE ${PROJECT_WC_LAST_CHANGED_DATE})
#    String(REGEX MATCH "[^/]+$" FAIRROOT_SVN_BRANCH ${FAIRROOT_SVN_BRANCH})
    Message(STATUS "FairSoft Revision - ${FAIRROOT_SVN_REVISION} Branch - ${FAIRROOT_SVN_BRANCH}")
    Configure_File($ENV{SIMPATH}/scripts/FairVersion.h.tmp ${CMAKE_BINARY_DIR}/FairVersion.h @ONLY)
  Else(Subversion_FOUND AND EXISTS $ENV{SIMPATH}/.svn/ )
    Configure_File($ENV{SIMPATH}/scripts/FairVersion.h.default ${CMAKE_BINARY_DIR}/FairVersion.h COPYONLY)
  EndIf(Subversion_FOUND AND EXISTS $ENV{SIMPATH}/.svn/ )

  Execute_Process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
       ${CMAKE_BINARY_DIR}/FairVersion.h $ENV{SIMPATH_INSTALL}/include/FairSoftVersion.h)

