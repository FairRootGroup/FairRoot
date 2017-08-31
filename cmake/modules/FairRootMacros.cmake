################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

#############################
# FairRoot Macros/Functions #
#############################

# Define CMAKE_INSTALL_*DIR family of variables
include(GNUInstallDirs)

string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
set(FAIRROOT_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(FAIRROOT_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME_LOWER})
set(FAIRROOT_INSTALL_INCDIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER})
set(FAIRROOT_INSTALL_DATADIR ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER})

  ###############################################################
  #
  # Exchange file extention of LIST from
  # FILE_EXT1 to FILE_EXT2 and assign the
  # newly created list to OUTVAR. The input
  # list LIST is not changed at all
  # Ex: CHANGE_FILE_EXTENSION(*.cxx *.h TRD_HEADERS "${TRD_SRCS}")
  #
  ################################################################

MACRO (CHANGE_FILE_EXTENSION FILE_EXT1 FILE_EXT2 OUTVAR LIST)

   SET(BLA)

   IF (${FILE_EXT1} MATCHES "^[*][.]+.*$")
     STRING(REGEX REPLACE "^[*]+([.].*)$" "\\1" FILE_EXT1_NEW ${FILE_EXT1}) 
   ENDIF  (${FILE_EXT1} MATCHES "^[*][.]+.*$")

   IF (${FILE_EXT2} MATCHES "^[*][.]+.*$")
     STRING(REGEX REPLACE "^[*]+([.].*)" "\\1" FILE_EXT2_NEW ${FILE_EXT2}) 
   ENDIF  (${FILE_EXT2} MATCHES "^[*][.]+.*$")

   foreach (_current_FILE ${LIST})

     STRING(REGEX REPLACE "^(.*)${FILE_EXT1_NEW}$" "\\1${FILE_EXT2_NEW}" test ${_current_FILE})
     SET (BLA ${BLA} ${test})

   endforeach (_current_FILE ${ARGN})
   
   SET (${OUTVAR} ${BLA})



ENDMACRO (CHANGE_FILE_EXTENSION)

  ######################################################
  # 
  # Macro get string with a colon seperated string of
  # pathes or any other colon sperated list.
  # First the string is seperated  and the entries are
  # filled into a list.
  # Loop over the list and searches for the occurence
  # of keywords which are provided as a list.
  # If the keyword occurs this path (entry) is
  # deleted from the list. Returns the list of pathes
  # (entries) wich survives the loop.
  #
  # PATH: colon separated string of pathes or other 
  #       input entries
  # LIST_OF_KEYWORDS: list of the keywords which 
  #                   should be excluded in the output
  # OUTVAR: name of the variable which should be filled
  #         with the resulting output list
  #
  ######################################################

MACRO (CLEAN_PATH_LIST PATH LIST_OF_KEYWORDS OUTVAR)

  SET(BLA "")

  STRING(REGEX MATCHALL "[^:]+" PATH1 ${PATH})

  FOREACH(_current_PATH ${PATH1})
 
    SET(KEYWORD_FOUND FALSE)

    FOREACH(_current_KEYWORD ${LIST_OF_KEYWORDS})

      IF (${_current_PATH} MATCHES "${_current_KEYWORD}")
        SET(KEYWORD_FOUND TRUE)
      ENDIF (${_current_PATH} MATCHES "${_current_KEYWORD}")

    ENDFOREACH(_current_KEYWORD ${LIST_OF_KEYWORDS})
    
    IF (NOT KEYWORD_FOUND)
      SET(BLA ${BLA} ${_current_PATH})
    ENDIF (NOT KEYWORD_FOUND)  

  ENDFOREACH(_current_PATH ${PATH1})

  UNIQUE(${OUTVAR} "${BLA}")

ENDMACRO (CLEAN_PATH_LIST)

  ##########################################################
  #
  # The macro checks if the user wants to build the project
  # in the source directory and if so stop the execution
  # of cmake with an error message.
  #
  ##########################################################

MACRO (CHECK_OUT_OF_SOURCE_BUILD)


   STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
   IF(insource)
      FILE(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/Testing)
      FILE(REMOVE ${CMAKE_SOURCE_DIR}/DartConfiguration.tcl)
      MESSAGE(FATAL_ERROR "FAIRROOT should be installed as an out of source build, to keep the source directory clean. Please create a extra build directory and run the command 'cmake path_to_source_dir' in this newly created directory. You have also to delete the directory CMakeFiles and the file CMakeCache.txt in the source directory. Otherwise cmake will complain even if you run it from an out-of-source directory.") 
   ENDIF(insource)

ENDMACRO (CHECK_OUT_OF_SOURCE_BUILD)

  ##########################################################
  #
  # The macro checks if the build directory is different from the
  # installation directory. In case both are the same
  # stop the execution of cmake with an error message.
  #
  ##########################################################

Macro (CHECK_INSTALL_DIRECTORY)

   String(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}" _same)
   If(_same)
      MESSAGE(FATAL_ERROR "Your build and installation directory is the same one. This option does not work. Please change either your build or your installation directory and rerun cmake.")
   EndIf(_same)

EndMacro (CHECK_INSTALL_DIRECTORY)

Macro(CHECK_EXTERNAL_PACKAGE_INSTALL_DIR)
  If(IS_DIRECTORY ${SIMPATH}/bin)
    Set(FAIRSOFT_EXTERN TRUE)
  Else(IS_DIRECTORY ${SIMPATH}/bin)
    Set(FAIRSOFT_EXTERN FALSE)
  EndIf(IS_DIRECTORY ${SIMPATH}/bin)
EndMacro(CHECK_EXTERNAL_PACKAGE_INSTALL_DIR)


MACRO(UNIQUE var_name list)

  #######################################################################
  # Make the given list have only one instance of each unique element and
  # store it in var_name.
  #######################################################################

  SET(unique_tmp "")
  FOREACH(l ${list})
    STRING(REGEX REPLACE "[+]" "\\\\+" l1 ${l})
    IF(NOT "${unique_tmp}" MATCHES "(^|;)${l1}(;|$)")
      SET(unique_tmp ${unique_tmp} ${l})
    ENDIF(NOT "${unique_tmp}" MATCHES "(^|;)${l1}(;|$)")
  ENDFOREACH(l)
  SET(${var_name} ${unique_tmp})
ENDMACRO(UNIQUE)


###################################################
# Creates a variable which stores the intersection 
# between two lists
####################################################

MACRO(INTERSECTION var_name list1 list2)
  # Store the intersection between the two given lists in var_name.
  SET(intersect_tmp "")
  FOREACH(l ${list1})
    IF("${list2}" MATCHES "(^|;)${l}(;|$)")
      SET(intersect_tmp ${intersect_tmp} ${l})
    ENDIF("${list2}" MATCHES "(^|;)${l}(;|$)")
  ENDFOREACH(l)
  SET(${var_name} ${intersect_tmp})
ENDMACRO(INTERSECTION)

MACRO(REMOVE_FROM_LIST var_name list1 list2)
  # Remove elements in list2 from list1 and store the result in var_name.
  SET(filter_tmp "")
  FOREACH(l ${list1})
    IF(NOT "${list2}" MATCHES "(^|;)${l}(;|$)")
      SET(filter_tmp ${filter_tmp} ${l})
    ENDIF(NOT "${list2}" MATCHES "(^|;)${l}(;|$)")
  ENDFOREACH(l)
  SET(${var_name} ${filter_tmp})
ENDMACRO(REMOVE_FROM_LIST)

MACRO (GENERATE_TEST_SCRIPT SCRIPT_FULL_NAME) 

  get_filename_component(path_name ${SCRIPT_FULL_NAME} PATH)
  get_filename_component(file_extension ${SCRIPT_FULL_NAME} EXT)
  get_filename_component(file_name ${SCRIPT_FULL_NAME} NAME_WE)
  set(shell_script_name "${file_name}.sh")

  if(${ARGC} GREATER 1)
    set(new_path ${ARGV1})
  Else()
    string(REPLACE ${PROJECT_SOURCE_DIR}
           ${PROJECT_BINARY_DIR} new_path ${path_name}
          )
  EndIf()

#  Message("${new_path}/${shell_script_name}")
#  file(MAKE_DIRECTORY ${new_path}/data)

  CONVERT_LIST_TO_STRING(${LD_LIBRARY_PATH})
  set(MY_LD_LIBRARY_PATH ${output})
  set(my_script_name ${SCRIPT_FULL_NAME})

  IF(FAIRROOT_FOUND)
    configure_file(${FAIRROOT_CMAKEMOD_DIR}/scripts/set_env.sh.in
                   ${new_path}/${shell_script_name}
                  )
  ELSE(FAIRROOT_FOUND)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/set_env.sh.in
                   ${new_path}/${shell_script_name}
                  )
  ENDIF(FAIRROOT_FOUND)


  
  EXEC_PROGRAM(/bin/chmod ARGS "u+x  ${new_path}/${shell_script_name}")

ENDMACRO (GENERATE_TEST_SCRIPT)

Macro(Generate_Exe_Script _Path _ExeName) 


  Message("PATH: ${_Path}")
  Message("ExeName: ${_ExeName}")
  set(shell_script_name "${_ExeName}.sh")
  Message("shell_script_name: ${shell_script_name}")

  string(REPLACE ${PROJECT_SOURCE_DIR}
         ${PROJECT_BINARY_DIR} new_path ${_Path}
        )

  set(my_exe_name ${EXECUTABLE_OUTPUT_PATH}/${_ExeName})

  configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/run_binary.sh.in
                   ${new_path}/${shell_script_name}
                  )

  EXEC_PROGRAM(/bin/chmod ARGS "u+x  ${new_path}/${shell_script_name}")

EndMacro(Generate_Exe_Script)
MACRO (WRITE_CONFIG_FILE filename)

  String(REGEX REPLACE "^.*(install).*$" "\\1" INSTALL_VERSION ${filename})
  String(COMPARE EQUAL "install" "${INSTALL_VERSION}" INSTALL_TRUE)

  # List(REMOVE_ITEM LD_LIBRARY_PATH ${CMAKE_BINARY_DIR}/lib)

  If (INSTALL_TRUE)
    SET(_INSTALLDIR ${CMAKE_INSTALL_PREFIX})  
    SET(_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)  
#    SET(VMCWORKDIR ${CMAKE_INSTALL_PREFIX}/share/fairbase)  
    SET(FAIRLIBDIR ${CMAKE_INSTALL_PREFIX}/lib)  
    SET(_LD_LIBRARY_PATH ${FAIRLIBDIR} ${LD_LIBRARY_PATH}) 
  Else (INSTALL_TRUE)
    SET(_INSTALLDIR ${CMAKE_BINARY_DIR})  
    SET(_BINDIR ${CMAKE_BINARY_DIR})  
#    SET(VMCWORKDIR ${CMAKE_SOURCE_DIR})  
    SET(FAIRLIBDIR ${CMAKE_BINARY_DIR}/lib)  
    SET(_LD_LIBRARY_PATH ${FAIRLIBDIR} ${LD_LIBRARY_PATH}) 
  EndIf (INSTALL_TRUE)

  If(NOT DEFINED FULL_CONFIG_FILE)
    Set(FULL_CONFIG_FILE "true")
  EndIf(NOT DEFINED FULL_CONFIG_FILE)

  
  IF(CMAKE_SYSTEM_NAME MATCHES Linux)
    IF(FAIRROOTPATH)
      configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/check_system.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/check_system.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ELSE(FAIRROOTPATH)
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ENDIF(FAIRROOTPATH)
    
    EXECUTE_PROCESS(COMMAND lsb_release -sd 
                     OUTPUT_VARIABLE _linux_flavour
                     OUTPUT_STRIP_TRAILING_WHITESPACE
                    )

    IF(_linux_flavour)
      STRING(REGEX REPLACE "^\"" "" _linux_flavour ${_linux_flavour})
      STRING(REGEX REPLACE "\"$" "" _linux_flavour ${_linux_flavour})
    ENDIF(_linux_flavour)

    EXECUTE_PROCESS(COMMAND uname -m 
                    OUTPUT_VARIABLE _system 
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )
   
  ElseIf(CMAKE_SYSTEM_NAME MATCHES Darwin)
    IF(FAIRROOTPATH)
      configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/check_system_mac.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/check_system_mac.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ELSE(FAIRROOTPATH)
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system_mac.sh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.sh
                    )
      configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/check_system_mac.csh.in
                     ${CMAKE_CURRENT_BINARY_DIR}/check_system.csh
                    )
    ENDIF(FAIRROOTPATH)
    EXECUTE_PROCESS(COMMAND uname -sr 
                    OUTPUT_VARIABLE _linux_flavour
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )
    EXECUTE_PROCESS(COMMAND uname -m 
                    OUTPUT_VARIABLE _system 
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )
  ENDIF(CMAKE_SYSTEM_NAME MATCHES Linux)

   
  CONVERT_LIST_TO_STRING(${Geant4_LIBRARY_DIR})
  Set(GEANT4_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${Geant4_INCLUDE_DIR})
  Set(GEANT4_INCLUDE_DIR ${output})

  CONVERT_LIST_TO_STRING(${Geant4VMC_INCLUDE_DIR})
  Set(GEANT4VMC_INCLUDE_DIR ${output})

  CONVERT_LIST_TO_STRING(${GEANT4VMC_LIBRARY_DIR})
  Set(GEANT4VMC_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${GEANT4VMC_MACRO_DIR})
  Set(GEANT4VMC_MACRO_DIR ${output})

  CONVERT_LIST_TO_STRING(${G4LEDATA})
  Set(G4LEDATA ${output})

  CONVERT_LIST_TO_STRING(${G4LEVELGAMMADATA})
  Set(G4LEVELGAMMADATA ${output})

  CONVERT_LIST_TO_STRING(${G4PIIDATA})
  Set(G4PIIDATA ${output})

  CONVERT_LIST_TO_STRING(${G4NeutronHPCrossSections})
  Set(G4NeutronHPCrossSections ${output})

  CONVERT_LIST_TO_STRING(${G4NEUTRONHPDATA})
  Set(G4NEUTRONHPDATA ${output})

  CONVERT_LIST_TO_STRING(${G4NEUTRONXSDATA})
  Set(G4NEUTRONXSDATA ${output})

  CONVERT_LIST_TO_STRING(${G4RADIOACTIVEDATA})
  Set(G4RADIOACTIVEDATA ${output})

  CONVERT_LIST_TO_STRING(${G4REALSURFACEDATA})
  Set(G4REALSURFACEDATA ${output})

  CONVERT_LIST_TO_STRING(${CLHEP_INCLUDE_DIR})
  Set(CLHEP_INCLUDE_DIR ${output})

  CONVERT_LIST_TO_STRING(${CLHEP_LIBRARY_DIR})
  Set(CLHEP_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${CLHEP_BASE_DIR})
  Set(CLHEP_BASE_DIR ${output})
  
  CONVERT_LIST_TO_STRING(${PLUTO_LIBRARY_DIR})
  Set(PLUTO_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${PLUTO_INCLUDE_DIR})
  Set(PLUTO_INCLUDE_DIR ${output})

  CONVERT_LIST_TO_STRING(${PYTHIA6_LIBRARY_DIR})
  Set(PYTHIA6_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${GEANT3_SYSTEM_DIR})
  Set(G3SYS ${output})

  CONVERT_LIST_TO_STRING(${GEANT3_INCLUDE_DIR})
  Set(GEANT3_INCLUDE_DIR ${output})

  CONVERT_LIST_TO_STRING(${GEANT3_LIBRARY_DIR})
  Set(GEANT3_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${GEANT3_LIBRARIES})
  Set(GEANT3_LIBRARIES ${output})

  CONVERT_LIST_TO_STRING(${ROOT_LIBRARY_DIR})
  Set(ROOT_LIBRARY_DIR ${output})

  CONVERT_LIST_TO_STRING(${ROOT_LIBRARIES})
  Set(ROOT_LIBRARIES ${output})

  CONVERT_LIST_TO_STRING(${ROOT_INCLUDE_DIR})
  Set(ROOT_INCLUDE_DIR ${output} )

#  Set(VMCWORKDIR ${C})

  Set(FAIRLIBDIR ${FAIRLIBDIR})

  List(REMOVE_DUPLICATES _LD_LIBRARY_PATH)
  CONVERT_LIST_TO_STRING(${_LD_LIBRARY_PATH})

  IF(CMAKE_SYSTEM_NAME MATCHES Linux)
    Set(MY_LD_LIBRARY_PATH ${output})
  ELSE(CMAKE_SYSTEM_NAME MATCHES Linux)
    IF(CMAKE_SYSTEM_NAME MATCHES Darwin)
      Set(MY_DYLD_LIBRARY_PATH ${output})
    ENDIF(CMAKE_SYSTEM_NAME MATCHES Darwin)
  ENDIF(CMAKE_SYSTEM_NAME MATCHES Linux)

  Set(USE_VGM 1)

  SET(PYTHONPATH ${CMAKE_SOURCE_DIR}/python ${SIMPATH}/lib ${SIMPATH}/lib/root ${SIMPATH}/lib/Geant4 ${SIMPATH}/lib/g4py ${PYTHONPATH})
  UNIQUE(PYTHONPATH "${PYTHONPATH}")
  CONVERT_LIST_TO_STRING(${PYTHONPATH})
  SET(MY_PYTHONPATH ${output})

  SET (PATH ${ROOTSYS}/bin ${PATH})
  UNIQUE(PATH "${PATH}")
  CONVERT_LIST_TO_STRING(${PATH})
  Set(MY_PATH ${output})

  If(FAIRSOFT_EXTERN)
    Set(PYTHIA8DATA "${SIMPATH}/share/pythia8/xmldoc")
  Else(FAIRSOFT_EXTERN)
    Set(PYTHIA8DATA "${SIMPATH}/generators/pythia8/xmldoc")
  EndIf(FAIRSOFT_EXTERN)

  CONVERT_LIST_TO_STRING($ENV{NEW_CLASSPATH})
  Set(MY_CLASSPATH ${output})

  CONVERT_LIST_TO_STRING(${ROOT_INCLUDE_PATH})
  Set(ROOT_INCLUDE_PATH ${output})

  IF(${filename} MATCHES "[.]csh.*$")
    IF(FAIRROOTPATH)
    configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/config.csh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ELSE(FAIRROOTPATH)    
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/config.csh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ENDIF(FAIRROOTPATH)


  ELSE(${filename} MATCHES "[.]csh.*$")
    IF(FAIRROOTPATH)
    configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/config.sh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ELSE(FAIRROOTPATH) 
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/config.sh.in
	           ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                  )
    ENDIF(FAIRROOTPATH)

  ENDIF(${filename} MATCHES "[.]csh.*$")


ENDMACRO (WRITE_CONFIG_FILE)


MACRO (CONVERT_LIST_TO_STRING)

  set (tmp "")
  foreach (_current ${ARGN})

    set(tmp1 ${tmp})
    set(tmp "")
    set(tmp ${tmp1}:${_current})

  endforeach (_current ${ARGN})
  If(tmp)
    STRING(REGEX REPLACE "^:(.*)" "\\1" output ${tmp}) 
  Else(tmp)
    Set(output "")
  EndIf(tmp)

ENDMACRO (CONVERT_LIST_TO_STRING LIST)

#---------------------------------------------------------------------------------------------------
# copied for now until upstream changes are merged.
#---FAIRROOT_GET_SOURCES( <variable> cwd <sources> ...)
#---------------------------------------------------------------------------------------------------
function(FAIRROOT_GET_SOURCES variable cwd )
  set(sources)
  foreach( fp ${ARGN})
    if( IS_ABSOLUTE ${fp})
      file(GLOB files ${fp})
    else()
      if(root7)
        set(root7glob v7/src/${fp})
      endif()
      file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${cwd}/${fp} ${root7glob})
    endif()
    if(files)
      foreach(s ${files})
        if(fp MATCHES "[*]" AND s MATCHES "(^|/)G__") # Eliminate G__* files
        elseif(s MATCHES "${cwd}/G__")
          set(sources ${fp} ${sources})
        else()
          set(sources ${sources} ${s})
        endif()
      endforeach()
    else()
      if(fp MATCHES "(^|/)G__")
        set(sources ${fp} ${sources})
      else()
        set(sources ${sources} ${fp})
      endif()
    endif()
  endforeach()
  set(${variable} ${sources} PARENT_SCOPE)
endfunction()

#---------------------------------------------------------------------------------------------------
# Depth-first-search target interface include directories
#
# This is done by CMake at generation time. Unfortunately, there is currently no API to resolve the
# include directories at configuration time.
#---------------------------------------------------------------------------------------------------
function(get_target_interface_include_directories target)
  if(TARGET ${target})
    get_target_property(link_libs ${target} INTERFACE_LINK_LIBRARIES)
    if(link_libs)
      foreach(l ${link_libs})
        get_target_interface_include_directories(${l})
        list(APPEND includedirs ${new_includedirs})
      endforeach()
    endif()

    get_target_property(_includedirs ${target} INTERFACE_INCLUDE_DIRECTORIES)
    if(_includedirs)
      foreach(d ${_includedirs}) # Filter and format dirs 
        string(REGEX MATCHALL "^[$]<.*>$" is_generator_expr ${d})
        string(REGEX MATCHALL "^[$]<BUILD_INTERFACE:(.*)>$" is_build_interface ${d})
        if(CMAKE_MATCH_1)
          list(APPEND includedirs -I${CMAKE_MATCH_1})
        elseif(NOT is_generator_expr)
          list(APPEND includedirs -I${d})
        endif()
        unset(is_generator_expr)
        unset(CMAKE_MATCH_1)
      endforeach()
    endif()

    list(REMOVE_DUPLICATES includedirs)
    set(new_includedirs ${includedirs} PARENT_SCOPE)
  endif()
endfunction()

#---------------------------------------------------------------------------------------------------
# copied for now until upstream changes are merged.
#---FAIRROOT_GENERATE_DICTIONARY( dictionary headerfiles MODULE module DEPENDENCIES dep1 dep2
#                                                    BUILTINS dep1 dep2
#                                                    STAGE1 LINKDEF linkdef OPTIONS opt1 opt2 ...)
#---------------------------------------------------------------------------------------------------
function(FAIRROOT_GENERATE_DICTIONARY dictionary)
  CMAKE_PARSE_ARGUMENTS(ARG "STAGE1;MULTIDICT;NOINSTALL" "MODULE" "LINKDEF;OPTIONS;DEPENDENCIES;BUILTINS" ${ARGN})

  # Check if OPTIONS start with a dash.
  if (ARG_OPTIONS)
    foreach(ARG_O ${ARG_OPTIONS})
      if (NOT ARG_O MATCHES "^-*")
        message(FATAL_ERROR "Wrong rootcling option: ${ARG_OPTIONS}")
      endif()
    endforeach()
  endif(ARG_OPTIONS)

  #---roottest compability---------------------------------
  if(CMAKE_ROOTTEST_DICT)
    set(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_BINARY_DIR})
    set(libprefix "")
  endif()

  #---Get the list of include directories------------------
  get_directory_property(incdirs INCLUDE_DIRECTORIES)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/inc)
    set(localinclude ${CMAKE_CURRENT_SOURCE_DIR}/inc)
  else()
    set(localinclude ${CMAKE_CURRENT_SOURCE_DIR})
  endif()
  #---Get the list of header files-------------------------
  set(headerfiles)
  set(_list_of_header_dependencies)
  foreach(fp ${ARG_UNPARSED_ARGUMENTS})
    if(${fp} MATCHES "[*?]") # Is this header a globbing expression?
      file(GLOB files inc/${fp} ${fp})
      foreach(f ${files})
        if(NOT f MATCHES LinkDef) # skip LinkDefs from globbing result
          list(APPEND headerfiles ${f})
          list(APPEND _list_of_header_dependencies ${f})
        endif()
      endforeach()
    elseif(CMAKE_PROJECT_NAME STREQUAL ROOT AND 
           EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${fp}) # only for ROOT project
      list(APPEND headerfiles ${CMAKE_CURRENT_SOURCE_DIR}/${fp})
      list(APPEND _list_of_header_dependencies ${CMAKE_CURRENT_SOURCE_DIR}/${fp})
    elseif(IS_ABSOLUTE ${fp})
      list(APPEND headerfiles ${fp})
      list(APPEND _list_of_header_dependencies ${fp})
    else()
      find_file(headerFile ${fp} HINTS ${localinclude} ${incdirs} NO_DEFAULT_PATH)
      find_file(headerFile ${fp})
      if(headerFile)
        list(APPEND headerfiles ${headerFile})
        list(APPEND _list_of_header_dependencies ${headerFile})
      else()
        list(APPEND headerfiles ${fp})
      endif()
      unset(headerFile CACHE)
    endif()
  endforeach()
  string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/inc/" ""  headerfiles "${headerfiles}") 
  # Replace the non-standard folder layout of Core.
  if (ARG_STAGE1 AND ARG_MODULE STREQUAL "Core")
    # FIXME: Glob these folders.
    set(core_folders base clib clingutils cont dictgen doc foundation lzma lz4
                     macosx meta metacling multiproc newdelete pcre rint
                     rootcling_stage1 textinput thread unix winnt zip)
    foreach(core_folder ${core_folders})
     string(REPLACE "${CMAKE_SOURCE_DIR}/core/(${core_folders})/inc/" ""  headerfiles "${headerfiles}")
    endforeach()
  endif()

  if(CMAKE_PROJECT_NAME STREQUAL ROOT)
    set(includedirs -I${CMAKE_SOURCE_DIR}
                    -I${CMAKE_SOURCE_DIR}/interpreter/cling/include # This is for the RuntimeUniverse
                    -I${CMAKE_BINARY_DIR}/include)
    set(excludepaths ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
  elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/inc)
    set(includedirs -I${CMAKE_CURRENT_SOURCE_DIR}/inc)
  endif()
  foreach( d ${incdirs})
   set(includedirs ${includedirs} -I${d})
  endforeach()

  foreach(dep ${ARG_DEPENDENCIES})
    # Resolve interface include directories recursively
    get_target_interface_include_directories(${dep})
    list(APPEND includedirs ${new_includedirs})
  endforeach()

  list(REMOVE_DUPLICATES includedirs)
  #---Get the list of definitions---------------------------
  get_directory_property(defs COMPILE_DEFINITIONS)
  foreach( d ${defs})
   if((NOT d MATCHES "=") AND (NOT d MATCHES "^[$]<.*>$")) # avoid generator expressions
     set(definitions ${definitions} -D${d})
   endif()
  endforeach()
  #---Get LinkDef.h file------------------------------------
  foreach( f ${ARG_LINKDEF})
    if( IS_ABSOLUTE ${f})
      set(_linkdef ${_linkdef} ${f})
    else()
      if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/inc/${f})
        set(_linkdef ${_linkdef} ${CMAKE_CURRENT_SOURCE_DIR}/inc/${f})
      else()
        set(_linkdef ${_linkdef} ${CMAKE_CURRENT_SOURCE_DIR}/${f})
      endif()
    endif()
  endforeach()

  #---Build the names for library, pcm and rootmap file ----
  get_filename_component(dict_base_name ${dictionary} NAME_WE)
  if(dict_base_name MATCHES "^G__")
    string(SUBSTRING ${dictionary} 3 -1 deduced_arg_module)
  else()
    set(deduced_arg_module ${dict_base_name})
  endif()

  #---Set the library output directory-----------------------
  if(DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY AND NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY STREQUAL "")
    set(library_output_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  else()
    set(library_output_dir ${CMAKE_CURRENT_BINARY_DIR})
  endif()

  if(ARG_MODULE)
    set(library_name ${libprefix}${ARG_MODULE}${libsuffix})
    if(ARG_MULTIDICT)
      set(newargs -s ${library_output_dir}/${library_name} -multiDict)
      set(pcm_name ${library_output_dir}/${libprefix}${ARG_MODULE}_${dictionary}_rdict.pcm)
      set(rootmap_name ${library_output_dir}/${libprefix}${deduced_arg_module}.rootmap)
    else()
      set(newargs -s ${library_output_dir}/${library_name})
      set(pcm_name ${library_output_dir}/${libprefix}${ARG_MODULE}_rdict.pcm)
      set(rootmap_name ${library_output_dir}/${libprefix}${ARG_MODULE}.rootmap)
    endif()
  else()
    set(library_name ${libprefix}${deduced_arg_module}${libsuffix})
    set(newargs -s ${library_output_dir}/${library_name})
    set(pcm_name ${library_output_dir}/${libprefix}${deduced_arg_module}_rdict.pcm)
    set(rootmap_name ${library_output_dir}/${libprefix}${deduced_arg_module}.rootmap)
  endif()

  if(CMAKE_ROOTTEST_NOROOTMAP)
    set(rootmapname )
    set(rootmapargs )
  else()
    set(rootmapargs -rml ${library_name} -rmf ${rootmap_name})
  endif()

  #---Get the library and module dependencies-----------------
  if(ARG_DEPENDENCIES)
    foreach(dep ${ARG_DEPENDENCIES})
      set(newargs ${newargs} -m  ${libprefix}${dep}_rdict.pcm)
    endforeach()
  endif()

  #---what rootcling command to use--------------------------
  if(ARG_STAGE1)
    set(command rootcling_stage1)
    set(pcm_name)
  else()
    if(CMAKE_PROJECT_NAME STREQUAL ROOT)
      set(command ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib:$ENV{LD_LIBRARY_PATH}" "ROOTIGNOREPREFIX=1" $<TARGET_FILE:rootcling> -rootbuild)
      set(ROOTCINTDEP rootcling)
    elseif(TARGET ROOT::rootcling)
      set(command ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${ROOT_LIBRARY_DIR}:$ENV{LD_LIBRARY_PATH}" $<TARGET_FILE:ROOT::rootcling>)
    else()
      set(command rootcling)
    endif()
  endif()

  #---build the path exclusion switches----------------------
  set(excludepathsargs "")
  foreach(excludepath ${excludepaths})
    set(excludepathsargs ${excludepathsargs} -excludePath ${excludepath})
  endforeach()

  #---build the implicit dependencies arguments
  foreach(_dep ${_linkdef} ${_list_of_header_dependencies})
    list(APPEND _implicitdeps CXX ${_dep})
  endforeach()

  # Add other rootcling invocations for our PCM generation. This is only necessary when rootcling is supposed
  # to generate C++ modules as those build upon the generated modules of other rootcling invocations.
  set(module_dependencies "")
  if(runtime_cxxmodules)
    foreach(dep ${ARG_DEPENDENCIES})
      set(module_dependencies ${module_dependencies} ROOTCLING_${dep})
    endforeach()
  endif()

  #---call rootcint------------------------------------------
  add_custom_command(OUTPUT ${dictionary}.cxx ${pcm_name} ${rootmap_name}
                     COMMAND ${command} -v2 -f  ${dictionary}.cxx ${newargs} ${excludepathsargs} ${rootmapargs}
                                        ${ARG_OPTIONS} ${definitions} ${includedirs} ${headerfiles} ${_linkdef}
                     IMPLICIT_DEPENDS ${_implicitdeps}
                     DEPENDS ${_list_of_header_dependencies} ${_linkdef} ${ROOTCINTDEP} ${ARG_DEPENDENCIES} ${module_dependencies})
  get_filename_component(dictname ${dictionary} NAME)

  #---roottest compability
  add_custom_target(${dictname} DEPENDS ${dictionary}.cxx ${pcm_name} ${rootmap_name})
  if(NOT ARG_NOINSTALL AND NOT CMAKE_ROOTTEST_DICT AND DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set_property(GLOBAL APPEND PROPERTY ROOT_DICTIONARY_TARGETS ${dictname})
    set_property(GLOBAL APPEND PROPERTY ROOT_DICTIONARY_FILES ${CMAKE_CURRENT_BINARY_DIR}/${dictionary}.cxx)

    if(ARG_STAGE1)
      install(FILES ${rootmap_name}
          DESTINATION ${FAIRROOT_INSTALL_LIBDIR} COMPONENT libraries)
    else()
      install(FILES ${pcm_name} ${rootmap_name}
          DESTINATION ${FAIRROOT_INSTALL_LIBDIR} COMPONENT libraries)
    endif()
  endif()
  # Create a target for this rootcling invocation based on the module name.
  # We can use this in other ROOT_GENERATE_DICTIONARY that only care about
  # the generation of PCMs without waiting on the whole module compilation.
  if(ARG_MODULE AND NOT ARG_MULTIDICT)
    # If we have multiple modules with the same name, let's just attach the
    # generation of this dictionary to the ROOTCLING_X target of the existing
    # module. This happens for example with ROOTCLING_Smatrix which also has a
    # "Smatrix32" part.
    if (TARGET ROOTCLING_${ARG_MODULE})
      add_dependencies(ROOTCLING_${ARG_MODULE} ${dictname})
    else()
      add_custom_target(ROOTCLING_${ARG_MODULE} DEPENDS ${dictname})
    endif()
  endif()

  if(ARG_BUILTINS)
    foreach(arg1 ${ARG_BUILTINS})
      if(${arg1}_TARGET)
        add_dependencies(${dictname} ${${arg1}_TARGET})
      endif()
    endforeach()
  endif()
  # FIXME: Support mulptiple dictionaries. In some cases (libSMatrix and
  # libGenVector) we have to have two or more dictionaries (eg. for math,
  # we need the two for double vs Double32_t template specializations).
  # In some other cases, eg. libTreePlayer.so we add in a separate dictionary
  # files which for some reason (temporarily?) cannot be put in the PCH. Eg.
  # all rest of the first dict is in the PCH but this file is not and it
  # cannot be present in the original dictionary.
  # if(ARG_MODULE AND NOT ARG_MULTIDICT)
  #   ROOT_CXXMODULES_APPEND_TO_MODULEMAP("${ARG_MODULE}" "${headerfiles}")
  # endif()
endfunction()
#---------------------------------------------------------------------------------------------------
# copied for now until upstream changes are merged
#---FAIRROOT_LINKER_LIBRARY( <name> source1 source2 ...[TYPE STATIC|SHARED] [DLLEXPORT]
#                        [NOINSTALL] LIBRARIES library1 library2 ...
#                        BUILTINS dep1 dep2)
#---------------------------------------------------------------------------------------------------
function(FAIRROOT_LINKER_LIBRARY library)
  CMAKE_PARSE_ARGUMENTS(ARG "DLLEXPORT;CMAKENOEXPORT;TEST;NOINSTALL" "TYPE" "LIBRARIES;DEPENDENCIES;BUILTINS"  ${ARGN})
  FAIRROOT_GET_SOURCES(lib_srcs src ${ARG_UNPARSED_ARGUMENTS})
  if(NOT ARG_TYPE)
    set(ARG_TYPE SHARED)
  endif()
  if(ARG_TEST) # we are building a test, so add EXCLUDE_FROM_ALL
    set(_all EXCLUDE_FROM_ALL)
  endif()
  include_directories(BEFORE ${CMAKE_BINARY_DIR}/include)
  set(library_name ${library})
  if(TARGET ${library})
    message("Target ${library} already exists. Renaming target name to ${library}_new")
    set(library ${library}_new)
  endif()
  if(WIN32 AND ARG_TYPE STREQUAL SHARED AND NOT ARG_DLLEXPORT)
    #---create a list of all the object files-----------------------------
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
      #foreach(src1 ${lib_srcs})
      #  if(NOT src1 MATCHES "[.]h$|[.]icc$|[.]hxx$|[.]hpp$")
      #    string (REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" src2 ${src1})
      #    string (REPLACE ${CMAKE_CURRENT_BINARY_DIR} "" src3 ${src2})
      #    string (REPLACE ".." "__" src ${src3})
      #    get_filename_component(name ${src} NAME_WE)
      #    set(lib_objs ${lib_objs} ${library}.dir/${CMAKE_CFG_INTDIR}/${name}.obj)
      #  endif()
      #endforeach()
     set(lib_objs ${lib_objs} ${library}.dir/${CMAKE_CFG_INTDIR}/*.obj)
    else()
      foreach(src1 ${lib_srcs})
        if(NOT src1 MATCHES "[.]h$|[.]icc$|[.]hxx$|[.]hpp$")
          string (REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" src2 ${src1})
          string (REPLACE ${CMAKE_CURRENT_BINARY_DIR} "" src3 ${src2})
          string (REPLACE ".." "__" src ${src3})
          get_filename_component(name ${src} NAME)
          get_filename_component(path ${src} PATH)
          set(lib_objs ${lib_objs} ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${library}.dir/${path}/${name}.obj)
        endif()
      endforeach()
    endif()
    #---create a shared library with the .def file------------------------
    add_library(${library} ${_all} SHARED ${lib_srcs})
    target_link_libraries(${library} PUBLIC ${ARG_LIBRARIES} ${ARG_DEPENDENCIES})
    set_target_properties(${library} PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES} LINK_FLAGS -DEF:${library}.def)

    #---set the .def file as generated------------------------------------
    set_source_files_properties(${library}.def PROPERTIES GENERATED 1)
    #---create a custom pre-link command that runs bindexplib
    add_custom_command(TARGET ${library} PRE_LINK
                       COMMAND bindexplib
                       ARGS -o ${library}.def ${libprefix}${library} ${lib_objs}
                       DEPENDS bindexplib )
  else()
    #---Need to add a dummy source file if all sources are OBJECT libraries (Xcode, ...)
    if(NOT lib_srcs MATCHES "(^|[;])[^$][^<]")
      add_custom_command(OUTPUT dummy.cxx COMMAND ${CMAKE_COMMAND} -E touch dummy.cxx)
      set(lib_srcs ${lib_srcs} dummy.cxx)
    endif()
    add_library( ${library} ${_all} ${ARG_TYPE} ${lib_srcs})
    if(ARG_TYPE STREQUAL SHARED)
      set_target_properties(${library} PROPERTIES  ${FAIRROOT_LIBRARY_PROPERTIES} )
    endif()
    if(explicitlink OR ROOT_explicitlink_FOUND)
      target_link_libraries(${library} ${ARG_LIBRARIES} ${ARG_DEPENDENCIES})
    else()
      target_link_libraries(${library} ${ARG_LIBRARIES})
    endif()
  endif()
  if(TARGET G__${library})
    add_dependencies(${library} G__${library})
  else()
    # Uncomment to see if we maybe forgot to add a dependency between linking
    # a dictionary and generating the G__*.cxx file. We can't have this by
    # default because right now quite few dictionaries don't have the associated
    # ROOT_GENERATE_DICTIONARY call that prevents this warning.
    #message(AUTHOR_WARNING "Couldn't find target: " ${library} "\n Forgot to call ROOT_GENERATE_DICTIONARY?")
  endif()
  if(CMAKE_PROJECT_NAME STREQUAL ROOT)
    add_dependencies(${library} move_headers)
  endif()
  set_property(GLOBAL APPEND PROPERTY ROOT_EXPORTED_TARGETS ${library})
  set_target_properties(${library} PROPERTIES OUTPUT_NAME ${library_name})
  set_target_properties(${library} PROPERTIES INTERFACE_LINK_LIBRARIES "${ARG_DEPENDENCIES}")
  # Do not add -Dname_EXPORTS to the command-line when building files in this
  # target. Doing so is actively harmful for the modules build because it
  # creates extra module variants, and not useful because we don't use these
  # macros.
  set_target_properties(${library} PROPERTIES DEFINE_SYMBOL "")
  if(ARG_BUILTINS)
    foreach(arg1 ${ARG_BUILTINS})
      if(${arg1}_TARGET)
        add_dependencies(${library} ${${arg1}_TARGET})
      endif()
    endforeach()
  endif()

  #----Installation details-------------------------------------------------------
  if(NOT ARG_TEST AND NOT ARG_NOINSTALL AND CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    if(ARG_CMAKENOEXPORT)
      install(TARGETS ${library} RUNTIME DESTINATION ${FAIRROOT_INSTALL_BINDIR} COMPONENT libraries
                                 LIBRARY DESTINATION ${FAIRROOT_INSTALL_LIBDIR} COMPONENT libraries
                                 ARCHIVE DESTINATION ${FAIRROOT_INSTALL_LIBDIR} COMPONENT libraries)
    else()
      install(TARGETS ${library} EXPORT ${CMAKE_PROJECT_NAME}Exports
                                 RUNTIME DESTINATION ${FAIRROOT_INSTALL_BINDIR} COMPONENT libraries
                                 LIBRARY DESTINATION ${FAIRROOT_INSTALL_LIBDIR} COMPONENT libraries
                                 ARCHIVE DESTINATION ${FAIRROOT_INSTALL_LIBDIR} COMPONENT libraries)
    endif()
    if(WIN32 AND ARG_TYPE STREQUAL SHARED)
      install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib${library}.pdb
                    CONFIGURATIONS Debug RelWithDebInfo
                    DESTINATION ${CMAKE_INSTALL_BINDIR}
                    COMPONENT libraries)
    endif()
  endif()
endfunction()


# add_fairroot_library(name
#                      [SOURCES source1 source2 ...]
#                      [HEADERS header1 header2 ...]
#                      [NO_DICT_SRCS source1 source2 ...]
#                      [NO_DICT_HEADERS header1 header2 ...]
#                      [DEPENDENCIES dep1 dep2 ...]
#                      [LINKDEF linkdef1 linkdef2 ...]
#                      [INCLUDE_DIRS incdir1 incdir2 ...]
#                      [DEFINITIONS def1 def2 ...])
#
# Compiles and links a shared library. If a LINKDEF is given,
# generates also a ROOT dictionary. If no HEADERS are given,
# a .h file is generated for each .cxx file. If a header file is given,
# all header files must be given.
function(add_fairroot_library lib_NAME)
  cmake_parse_arguments(lib
      ""
      ""
      "SOURCES;HEADERS;NO_DICT_SRCS;DEPENDENCIES;NO_DICT_HEADERS;LINKDEF;INCLUDE_DIRS;DEFINITIONS"
      ${ARGN}
  )

  # if no headers are passed, generate a list of headers from the source file list
  if(NOT lib_HEADERS)
    CHANGE_FILE_EXTENSION(*.cxx *.h lib_HEADERS "${lib_SOURCES}")
  endif()

  # the following root macros expect include dirs to be set as directory property
  get_directory_property(include_dirs INCLUDE_DIRECTORIES)
  list(APPEND include_dirs ${lib_INCLUDE_DIRS})
  list(REMOVE_DUPLICATES include_dirs)
  include_directories(${include_dirs})

  # the following root macros expect definitions to be set as directory property
  foreach(def ${lib_DEFINITIONS})
    add_definitions(-D${def})
  endforeach()

  if(IWYU_FOUND)
    get_directory_property(system_include_dirs SYSTEM_INCLUDE_DIRECTORIES)
    set(_INCLUDE_DIRS ${include_dirs} ${system_include_dirs})
    set(header_rule_name "${lib_NAME}_HEADER_RULES")
    CHECK_HEADERS("${lib_SOURCES}" "${_INCLUDE_DIRS}" ${header_rule_name})
  endif()

  if(lib_LINKDEF)
    set(dict "G__${lib_NAME}")
    set(dict_src ${CMAKE_CURRENT_BINARY_DIR}/${dict}.cxx)
    set_source_files_properties(${dict_src} PROPERTIES COMPILE_FLAGS "-Wno-old-style-cast")
    set_source_files_properties(${dict_src} PROPERTIES GENERATED TRUE)
  endif()

  # build and install the library
  fairroot_linker_library(${lib_NAME}
    ${lib_SOURCES}
    ${lib_NO_DICT_SRCS}
    ${lib_HEADERS}
    ${lib_NO_DICT_HEADERS}
    ${lib_LINKDEF}
    ${dict_src}
    TYPE SHARED
    DEPENDENCIES ${lib_DEPENDENCIES} 
  )
  set_target_properties(${lib_NAME} PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
  if(lib_INCLUDE_DIRS)
    # wrap all inc dirs with generator expression BUILD_INTERFACE, this is needed to
    # properly export relocatable targets
    foreach(inc_dir ${lib_INCLUDE_DIRS})
      list(APPEND build_interface_inc_dirs $<BUILD_INTERFACE:${inc_dir}>)
    endforeach()
  endif()
  target_include_directories(${lib_NAME} PUBLIC 
    ${build_interface_inc_dirs}
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  if(lib_DEFINITIONS)
    target_compile_definitions(${lib_NAME} PUBLIC ${lib_DEFINITIONS})
  endif()

  # generate root dictionary
  if(lib_LINKDEF)
    fairroot_generate_dictionary(${dict} ${lib_HEADERS}
      LINKDEF ${lib_LINKDEF}
      DEPENDENCIES ${lib_DEPENDENCIES}
    )
    
    # make sure dictionary is generated before library
    add_dependencies(${lib_NAME} ${dict})
  endif()

  # install headers
  install(FILES ${lib_HEADERS} ${lib_NO_DICT_HEADERS} DESTINATION ${FAIRROOT_INSTALL_INCDIR})

  # add include paths to ROOT_INCLUDE_PATH needed at macro runtime from build tree
  get_property(ROOT_INCLUDE_PATH GLOBAL PROPERTY ROOT_INCLUDE_PATH)
  list(APPEND ROOT_INCLUDE_PATH ${lib_INCLUDE_DIRS})
  set_property(GLOBAL PROPERTY ROOT_INCLUDE_PATH ${ROOT_INCLUDE_PATH})
endfunction()

# compatibility to old macro interface
macro(GENERATE_LIBRARY)
  # include dirs were not passed via variable but via directory property
  get_directory_property(include_dirs INCLUDE_DIRECTORIES)

  add_fairroot_library(${LIBRARY_NAME}
    SOURCES ${SRCS}
    HEADERS ${HEADERS}
    DEPENDENCIES ${DEPENDENCIES}
    NO_DICT_SRCS ${NO_DICT_SRCS}
    LINKDEF ${LINKDEF}
    INCLUDE_DIRS ${include_dirs}
  )

  set(LIBRARY_NAME)
  set(DICTIONARY) # no longer supported
  set(LINKDEF)
  set(SRCS)
  set(HEADERS)
  set(NO_DICT_SRCS)
  set(DEPENDENCIES)
endmacro(GENERATE_LIBRARY)

# add_fairroot_executable(name
#                        [BIN_DESTINATION dest]
#                        [SOURCES source1 source2 ...]
#                        [DEPENDENCIES dep1 dep2 ...]
#                        [DEFINITIONS def1 def2 ...])
#
# Compiles and links an executable.
function(add_fairroot_executable exe_NAME)
  cmake_parse_arguments(exe
      ""
      "BIN_DESTINATION"
      "SOURCES;DEPENDENCIES;DEFINITIONS"
      ${ARGN}
  )

  add_executable(${exe_NAME} ${exe_SOURCES})
  target_link_libraries(${exe_NAME} ${exe_DEPENDENCIES})
  set_target_properties(${exe_NAME} PROPERTIES ${FAIRROOT_EXECUTABLE_PROPERTIES})

  if(exe_DEFINITIONS)
    target_compile_definitions(${exe_NAME} PUBLIC ${exe_DEFINITIONS})
  endif()

  if(NOT exe_BIN_DESTINATION)
    set(exe_BIN_DESTINATION ${CMAKE_INSTALL_BINDIR})
  endif()

  install(TARGETS ${exe_NAME} EXPORT FairRoot RUNTIME DESTINATION ${exe_BIN_DESTINATION})
endfunction()

# compatibility to old macro interface
macro(GENERATE_EXECUTABLE)
  add_fairroot_executable(${EXE_NAME}
    SOURCES ${SRCS}
    DEPENDENCIES ${DEPENDENCIES}
    BIN_DESTINATION ${BIN_DESTINATION}
  )

  set(EXE_NAME)
  set(SRCS)
  set(DEPENDENCIES)
endmacro(GENERATE_EXECUTABLE)

# add_fairroot_multiple_executable([NAMES name1 name2 ...]
#                                  [SOURCES source1 source2 ...]
#                                  [BIN_DESTINATION dest]
#                                  [DEPENDENCIES dep1 dep2 ...]
#                                  [DEFINITIONS def1 def2 ...])
#
# Compiles and links multiple executables. Each name given corresponds
# to each single source given. This function is intended to
# conveniently generate multiple test executables.
function(add_fairroot_multiple_executables)
  cmake_parse_arguments(exe
      ""
      "BIN_DESTINATION"
      "SOURCES;DEPENDENCIES;NAMES;DEFINITIONS"
      ${ARGN}
  )

  # Loop pairwise over exe_NAMES and exe_SOURCES
  list(LENGTH exe_NAMES length)
  math(EXPR length ${length}-1)

  foreach(exe RANGE 0 ${length})
    list(GET exe_NAMES ${exe} name)
    list(GET exe_SOURCES ${exe} src)

    add_fairroot_executable(${name}
        SOURCES ${src}
        BIN_DESTINATION ${exe_BIN_DESTINATION}
        DEPENDENCIES ${exe_DEPENDENCIES}
        DEFINITIONS ${exe_DEFINITIONS}
    )
  endforeach()
endfunction()

# GENERATE_ROOT_TEST_SCRIPT(script_name)
#
macro(GENERATE_ROOT_TEST_SCRIPT SCRIPT_FULL_NAME)
  get_filename_component(path_name ${SCRIPT_FULL_NAME} PATH)
  get_filename_component(file_extension ${SCRIPT_FULL_NAME} EXT)
  get_filename_component(file_name ${SCRIPT_FULL_NAME} NAME_WE)
  set(shell_script_name "${file_name}.sh")

  #MESSAGE("PATH: ${path_name}")
  #MESSAGE("Ext: ${file_extension}")
  #MESSAGE("Name: ${file_name}")
  #MESSAGE("Shell Name: ${shell_script_name}")

  string(REPLACE ${PROJECT_SOURCE_DIR}
         ${PROJECT_BINARY_DIR} new_path ${path_name}
        )

  #MESSAGE("New PATH: ${new_path}")

  file(MAKE_DIRECTORY ${new_path}/data)

  CONVERT_LIST_TO_STRING(${LD_LIBRARY_PATH})
  set(MY_LD_LIBRARY_PATH ${output})

  CONVERT_LIST_TO_STRING(${ROOT_INCLUDE_PATH})
  set(MY_ROOT_INCLUDE_PATH ${output})

  set(my_script_name ${SCRIPT_FULL_NAME})

  if(FAIRROOTPATH)
    configure_file(${FAIRROOTPATH}/share/fairroot/cmake/scripts/root_macro.sh.in
                   ${new_path}/${shell_script_name}
                  )
  else()
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/root_macro.sh.in
                   ${new_path}/${shell_script_name}
                  )
  endif()

  execute_process(COMMAND /bin/chmod u+x ${new_path}/${shell_script_name})
endmacro()
  
# ##########################
# # GTest helper functions #
# ##########################
#
# The helper functions allow concise cmake files for GTest based test submodules.
# Testsuites register themselves automatically as CTest test.
#
#
# Usage:
# 
#   add_testsuite(<name> SOURCES source1 [source2 ...]
#                        [DEPENDS dep1 [dep2 ...]]
#                        [LINKS linklib1 [linklib2 ...]
#                        [INCLUDES dir1 [dir2 ...]
#                        [TIMEOUT seconds]
#                        [RUN_SERIAL ON/OFF])
#
#   -> created target: testsuite_<name>
#
#   add_testhelper(<name> SOURCES source1 [source2 ...]
#                         [DEPENDS dep1 [dep2 ...]]
#                         [LINKS linklib1 [linklib2 ...]
#                         [INCLUDES dir1 [dir2 ...])
#
#   -> created target: testhelper_<name>
#
#   add_testlib(<name> SOURCES source1 [source2 ...]
#                      [DEPENDS dep1 [dep2 ...]]
#                      [LINKS linklib1 [linklib2 ...]
#                      [INCLUDES dir1 [dir2 ...])
#
#   -> created target: <name>
#
#   The above add_* functions add all created targets to the cmake
#   variable ALL_TEST_TARGETS which can be used to create an aggregate
#   target, e.g.:
#
#   add_custom_target(AllTests DEPENDS ${ALL_TEST_TARGETS})
#
#

function(add_testsuite suitename)
    cmake_parse_arguments(testsuite
        ""
        "TIMEOUT;RUN_SERIAL"
        "SOURCES;LINKS;DEPENDS;INCLUDES"
        ${ARGN}
    )

    list(INSERT testsuite_LINKS 0 GTest::Main GTest::GTest)
    set(target "testsuite_${suitename}")

    add_executable(${target} ${testsuite_SOURCES})
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set_target_properties("${target}" PROPERTIES LINK_FLAGS "-Wl,--no-as-needed")
    endif()
    target_link_libraries(${target} ${testsuite_LINKS})
    if(testsuite_DEPENDS)
        add_dependencies(${target} ${testsuite_DEPENDS})
    endif()
    if(testsuite_INCLUDES)
        target_include_directories(${target} PUBLIC ${testsuite_INCLUDES})
    endif()

    add_test(NAME "${suitename}" WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND ${target})
    if(testsuite_TIMEOUT)
        set_tests_properties("${suitename}" PROPERTIES TIMEOUT ${testsuite_TIMEOUT})
    endif()
    if(testsuite_RUN_SERIAL)
        set_tests_properties("${suitename}" PROPERTIES RUN_SERIAL ${testsuite_RUN_SERIAL})
    endif()

    list(APPEND ALL_TEST_TARGETS ${target})
    set(ALL_TEST_TARGETS ${ALL_TEST_TARGETS} PARENT_SCOPE)
endfunction()

function(add_testhelper helpername)
    cmake_parse_arguments(testhelper
        ""
        ""
        "SOURCES;LINKS;DEPENDS;INCLUDES"
        ${ARGN}
    )

    set(target "testhelper_${helpername}")
    
    add_executable(${target} ${testhelper_SOURCES})
    if(testhelper_LINKS)
        target_link_libraries(${target} ${testhelper_LINKS})
    endif()
    if(testhelper_DEPENDS)
        add_dependencies(${target} ${testhelper_DEPENDS})
    endif()
    if(testhelper_INCLUDES)
        target_include_directories(${target} PUBLIC ${testhelper_INCLUDES})
    endif()

    list(APPEND ALL_TEST_TARGETS ${target})
    set(ALL_TEST_TARGETS ${ALL_TEST_TARGETS} PARENT_SCOPE)
endfunction()

function(add_testlib libname)
    cmake_parse_arguments(testlib
        "HIDDEN"
        "VERSION"
        "SOURCES;LINKS;DEPENDS;INCLUDES"
        ${ARGN}
    )

    set(target "${libname}")
    
    add_library(${target} SHARED ${testlib_SOURCES})
    if(testlib_LINKS)
        target_link_libraries(${target} ${testlib_LINKS})
    endif()
    if(testlib_DEPENDS)
        add_dependencies(${target} ${testlib_DEPENDS})
    endif()
    if(testlib_INCLUDES)
        target_include_directories(${target} PUBLIC ${testlib_INCLUDES})
    endif()
    if(testlib_HIDDEN)
        set_target_properties(${target} PROPERTIES CXX_VISIBILITY_PRESET hidden)
    endif()
    if(testlib_VERSION)
        set_target_properties(${target} PROPERTIES VERSION ${testlib_VERSION})
    endif()

    list(APPEND ALL_TEST_TARGETS ${target})
    set(ALL_TEST_TARGETS ${ALL_TEST_TARGETS} PARENT_SCOPE)
endfunction()
