################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################




################################################################################
#    Create Bash the Variable for G4 Data files
################################################################################
MACRO(Write_Geant4Data_Variables_sh)
Set(Geant4Data_Variables_sh "\
####################### Create the data set variables for Geant4 #############
")
foreach(DATASET  ${Geant4_DATASETS})
      string(CONCAT Geant4Data_Variables_sh ${Geant4Data_Variables_sh} "\
export ${Geant4_DATASET_${DATASET}_ENVVAR}=${Geant4_DATASET_${DATASET}_PATH}
")
endforeach()
string(CONCAT Geant4Data_Variables_sh ${Geant4Data_Variables_sh} "\
##############################################################################
")

ENDMACRO()

################################################################################
#    Create CSH the Variable for G4 Data files
################################################################################
MACRO(Write_Geant4Data_Variables_csh)
Set(Geant4Data_Variables_csh "\
####################### Create the data set variables for Geant4 #############
")
foreach(DATASET  ${Geant4_DATASETS})
      string(CONCAT Geant4Data_Variables_csh ${Geant4Data_Variables_csh} "\
setenv ${Geant4_DATASET_${DATASET}_ENVVAR}  ${Geant4_DATASET_${DATASET}_PATH}
")
endforeach()
string(CONCAT Geant4Data_Variables_csh ${Geant4Data_Variables_csh} "\
##############################################################################
")
################################################################################
ENDMACRO()

#Defines some variables with console color escape sequences
  if(NOT WIN32 AND NOT DISABLE_COLOR)
    string(ASCII 27 Esc)
    set(CR       "${Esc}[m")
    set(CB       "${Esc}[1m")
    set(Red      "${Esc}[31m")
    set(Green    "${Esc}[32m")
    set(Yellow   "${Esc}[33m")
    set(Blue     "${Esc}[34m")
    set(Magenta  "${Esc}[35m")
    set(Cyan     "${Esc}[36m")
    set(White    "${Esc}[37m")
    set(BRed     "${Esc}[1;31m")
    set(BGreen   "${Esc}[1;32m")
    set(BYellow  "${Esc}[1;33m")
    set(BBlue    "${Esc}[1;34m")
    set(BMagenta "${Esc}[1;35m")
    set(BCyan    "${Esc}[1;36m")
    set(BWhite   "${Esc}[1;37m")
  endif()

################################################################################
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
      IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
      ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

################################################################################
#
# Exchange file extention of LIST from FILE_EXT1 to FILE_EXT2
# and assign the newly created list to OUTVAR.
# The input list LIST is not changed at all
# Ex : CHANGE_FILE_EXTENSION(*.cxx *.h TRD_HEADERS "${TRD_SRCS}")
#
################################################################################
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

################################################################################
# Exchange file extention of file in list from ext1 to ext2,
# only if the resulting file exists in CMAKE_CURRENT_SOURCE_DIR,
# and assign the newly created list to 'output'.
# The input list is not changed at all
# Ex: fair_change_file_extension_ifexists(*.cxx *.h "${TRD_SRCS}" TRD_HEADERS)
################################################################################
function(fair_change_extensions_if_exists ext1 ext2)
  cmake_parse_arguments(ARGS "" "OUTVAR" "FILES" ${ARGN})

  set(required_args "FILES;OUTVAR")
  foreach(required_arg IN LISTS required_args)
    if(NOT ARGS_${required_arg})
      message(FATAL_ERROR "fair_change_extensions_if_exists is missing a required argument: ${required_arg}")
    endif()
  endforeach()

  if(${ext1} MATCHES "^[*][.]+.*$")
    string(REGEX REPLACE "^[*]+([.].*)$" "\\1" ext1new ${ext1})
  else()
    set(ext1new ${ext1})
  endif()
  if(${ext2} MATCHES "^[*][.]+.*$")
    string(REGEX REPLACE "^[*]+([.].*)$" "\\1" ext2new ${ext2})
  else()
    set(ext2new ${ext2})
  endif()
  foreach(file ${ARGS_FILES})
    set(newFile "")
    string(REGEX REPLACE "^(.*)${ext1new}$" "\\1${ext2new}" newFile ${file})
    if(NOT ${file} STREQUAL ${newFile} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${newFile})
      list(APPEND result ${newFile})
    endif()
  endforeach()
  set(${ARGS_OUTVAR} ${result} PARENT_SCOPE)
endfunction()

################################################################################
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
################################################################################

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

#################################################################################
# The macro checks if the user wants to build the project
# in the source directory and if so stop the execution
# of cmake with an error message.
#
################################################################################

MACRO (CHECK_OUT_OF_SOURCE_BUILD)

   STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
   IF(insource)
      FILE(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/Testing)
      FILE(REMOVE ${CMAKE_SOURCE_DIR}/DartConfiguration.tcl)
      MESSAGE(FATAL_ERROR "FAIRROOT should be installed as an out of source build, to keep the source directory clean. Please create a extra build directory and run the command 'cmake path_to_source_dir' in this newly created directory. You have also to delete the directory CMakeFiles and the file CMakeCache.txt in the source directory. Otherwise cmake will complain even if you run it from an out-of-source directory.")
   ENDIF(insource)

ENDMACRO (CHECK_OUT_OF_SOURCE_BUILD)

#################################################################################
# The macro checks if the build directory is different from the
# installation directory. In case both are the same
# stop the execution of cmake with an error message.
#
################################################################################

MACRO (CHECK_INSTALL_DIRECTORY)
   String(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "${CMAKE_BINARY_DIR}" _same)
   If(_same)
      MESSAGE(FATAL_ERROR "Your build and installation directory is the same one. This option does not work. Please change either your build or your installation directory and rerun cmake.")
   EndIf(_same)
EndMacro (CHECK_INSTALL_DIRECTORY)
################################################################################

MACRO(CHECK_EXTERNAL_PACKAGE_INSTALL_DIR)
  If(IS_DIRECTORY ${SIMPATH}/bin)
    Set(FAIRSOFT_EXTERN TRUE)
  Else(IS_DIRECTORY ${SIMPATH}/bin)
    Set(FAIRSOFT_EXTERN FALSE)
  EndIf(IS_DIRECTORY ${SIMPATH}/bin)
EndMacro(CHECK_EXTERNAL_PACKAGE_INSTALL_DIR)
MACRO(UNIQUE var_name list)
################################################################################
# Make the given list have only one instance of each unique element and
# store it in var_name.
################################################################################

  SET(unique_tmp "")
  FOREACH(l ${list})
    STRING(REGEX REPLACE "[+]" "\\\\+" l1 ${l})
    IF(NOT "${unique_tmp}" MATCHES "(^|;)${l1}(;|$)")
      SET(unique_tmp ${unique_tmp} ${l})
    ENDIF(NOT "${unique_tmp}" MATCHES "(^|;)${l1}(;|$)")
  ENDFOREACH(l)
  SET(${var_name} ${unique_tmp})
ENDMACRO(UNIQUE)
################################################################################
# Creates a variable which stores the intersection
# between two lists
################################################################################

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
################################################################################
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
################################################################################
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
  CONVERT_LIST_TO_STRING(${LD_LIBRARY_PATH})
  set(MY_LD_LIBRARY_PATH ${output})
  set(my_script_name ${SCRIPT_FULL_NAME})
  Write_Geant4Data_Variables_sh()
  IF(FAIRROOT_FOUND)
    configure_file(${FAIRROOT_CMAKEMOD_DIR}/scripts/set_env.sh.in
                   ${new_path}/${shell_script_name}
                  )
  ELSE(FAIRROOT_FOUND)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/set_env.sh.in
                   ${new_path}/${shell_script_name}
                  )
  ENDIF(FAIRROOT_FOUND)
  EXEC_PROGRAM(/bin/chmod ARGS "u+x  ${new_path}/${shell_script_name}" OUTPUT_VARIABLE tmp)
ENDMACRO (GENERATE_TEST_SCRIPT)
################################################################################

Macro(Generate_Exe_Script _Path _ExeName)

  Message("PATH: ${_Path}")
  Message("ExeName: ${_ExeName}")
  set(shell_script_name "${_ExeName}.sh")
  Message("shell_script_name: ${shell_script_name}")

  string(REPLACE ${PROJECT_SOURCE_DIR}
         ${PROJECT_BINARY_DIR} new_path ${_Path}
        )

  set(my_exe_name ${EXECUTABLE_OUTPUT_PATH}/${_ExeName})
  Write_Geant4Data_Variables_sh()
  configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/run_binary.sh.in
                   ${new_path}/${shell_script_name}
                  )

  EXEC_PROGRAM(/bin/chmod ARGS "u+x  ${new_path}/${shell_script_name}" OUTPUT_VARIABLE tmp )

EndMacro(Generate_Exe_Script)
################################################################################

Macro (Generate_Version_Info)
IF(FAIRROOT_FOUND)

  Add_Custom_Target(svnheader ALL)

  Add_Custom_Command(TARGET svnheader
                     COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${PROJECT_SOURCE_DIR}
		     -DBINARY_DIR=${CMAKE_BINARY_DIR}
                     -DINCLUDE_OUTPUT_DIRECTORY=${INCLUDE_OUTPUT_DIRECTORY}
                     -DFAIRROOT=${FAIRROOT_CMAKEMOD_DIR}
                     -P ${FAIRROOT_CMAKEMOD_DIR}/modules/GenerateVersionInfo.cmake
                      )
ELSE(FAIRROOT_FOUND)
  Add_Custom_Target(svnheader ALL)
  Add_Custom_Command(TARGET svnheader
                     COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
		     -DBINARY_DIR=${CMAKE_BINARY_DIR}
                     -DINCLUDE_OUTPUT_DIRECTORY=${INCLUDE_OUTPUT_DIRECTORY}
                     -P ${CMAKE_SOURCE_DIR}/cmake/modules/GenerateVersionInfo.cmake
		     )
ENDIF(FAIRROOT_FOUND)

EndMacro (Generate_Version_Info)
################################################################################

Macro (SetBasicVariables)
IF(FAIRROOT_FOUND)
  Set(BASE_INCLUDE_DIRECTORIES
    ${FAIRROOT_INCLUDE_DIR}
  )
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${ROOT_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
  )
  Set(ROOT_INCLUDE_PATH
      ${FAIRROOT_INCLUDE_DIR}
     )

ELSE(FAIRROOT_FOUND)
  Set(BASE_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/logger
    ${CMAKE_SOURCE_DIR}/fairtools
    ${CMAKE_SOURCE_DIR}/geobase
    ${CMAKE_SOURCE_DIR}/parbase
    ${CMAKE_SOURCE_DIR}/base
    ${CMAKE_SOURCE_DIR}/base/steer
    ${CMAKE_SOURCE_DIR}/base/event
    ${CMAKE_SOURCE_DIR}/base/field
    ${CMAKE_SOURCE_DIR}/base/sim
    ${CMAKE_SOURCE_DIR}/base/sink
    ${CMAKE_SOURCE_DIR}/base/source
    ${CMAKE_SOURCE_DIR}/dbase
    ${CMAKE_SOURCE_DIR}/dbase/dbInterface
    ${CMAKE_SOURCE_DIR}/dbase/dbValidation
    ${CMAKE_SOURCE_DIR}/dbase/dbUtils
    ${CMAKE_SOURCE_DIR}/input/db
    ${CMAKE_SOURCE_DIR}/dbase/dbInput
    ${CMAKE_SOURCE_DIR}/dbase/dbIO
    ${CMAKE_SOURCE_DIR}/alignment
  )
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${ROOT_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
  )
  Set(ROOT_INCLUDE_PATH
      ${BASE_INCLUDE_DIRECTORIES}
  )
ENDIF(FAIRROOT_FOUND)

Set(BASE_LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
)

IF(FAIRROOT_FOUND)
  Set(FAIRLIBDIR ${FAIRROOT_LIBRARY_DIR})
ELSE(FAIRROOT_FOUND)
  Set(FAIRLIBDIR ${CMAKE_BINARY_DIR}/lib)
ENDIF(FAIRROOT_FOUND)
Set(LD_LIBRARY_PATH  ${FAIRLIBDIR} ${LD_LIBRARY_PATH})

include_directories(${BASE_INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories(${BASE_LINK_DIRECTORIES})

EndMacro (SetBasicVariables)

################################################################################
#
# find_package2(PRIVATE|PUBLIC|INTERFACE <pkgname>
#               [VERSION <version>]
#               [COMPONENTS <list of components>]
#               [ADD_REQUIREMENTS_OF <list of dep_pgkname>]
#               [any other option the native find_package supports]...)
#
# Wrapper around CMake's native find_package command to add some features and bookkeeping.
#
# The qualifier (PRIVATE|PUBLIC|INTERFACE) to the package to populate
# the variables PROJECT_[INTERFACE]_<pkgname>_([VERSION]|[COMPONENTS]|PACKAGE_DEPENDENCIES)
# accordingly. This bookkeeping information is used to print our dependency found summary
# table and to generate a part of our CMake package.
#
# When a dependending package is listed with ADD_REQUIREMENTS_OF the variables
# <dep_pkgname>_<pkgname>_VERSION|COMPONENTS are looked up to and added to the native
# VERSION (selected highest version) and COMPONENTS (deduplicated) args.
#
# COMPONENTS and VERSION args are then just passed to the native find_package.
#
macro(find_package2 qualifier pkgname)
  cmake_parse_arguments(ARGS "" "VERSION" "COMPONENTS;ADD_REQUIREMENTS_OF" ${ARGN})

  string(TOUPPER ${pkgname} pkgname_upper)
  set(__old_cpp__ ${CMAKE_PREFIX_PATH})
  set(CMAKE_PREFIX_PATH ${${pkgname_upper}_ROOT} $ENV{${pkgname_upper}_ROOT} ${CMAKE_PREFIX_PATH})

  # build lists of required versions and components
  unset(__required_versions__)
  unset(__components__)
  if(ARGS_VERSION)
    list(APPEND __required_versions__ ${ARGS_VERSION})
  endif()
  if(ARGS_COMPONENTS)
    list(APPEND __components__ ${ARGS_COMPONENTS})
  endif()
  if(ARGS_ADD_REQUIREMENTS_OF)
    foreach(dep_pkgname IN LISTS ARGS_ADD_REQUIREMENTS_OF)
      if(${dep_pkgname}_${pkgname}_VERSION)
        list(APPEND __required_versions__ ${${dep_pkgname}_${pkgname}_VERSION})
      endif()
      if(${dep_pkgname}_${pkgname}_COMPONENTS)
        list(APPEND __components__ ${${dep_pkgname}_${pkgname}_COMPONENTS})
      endif()
    endforeach()
  endif()

  # select highest required version
  unset(__version__)
  if(__required_versions__)
    list(GET __required_versions__ 0 __version__)
    foreach(v IN LISTS __required_versions__)
      if(${v} VERSION_GREATER ${__version__})
        set(__version__ ${v})
      endif()
    endforeach()
  endif()
  # deduplicate required component list
  if(__components__)
    list(REMOVE_DUPLICATES __components__)
  endif()

  # call native find_package
  if(__components__)
    find_package(${pkgname} ${__version__} QUIET COMPONENTS ${__components__} ${ARGS_UNPARSED_ARGUMENTS})
  else()
    find_package(${pkgname} ${__version__} QUIET ${ARGS_UNPARSED_ARGUMENTS})
  endif()

  if(${pkgname}_FOUND)
    if(${qualifier} STREQUAL PRIVATE)
      set(PROJECT_${pkgname}_VERSION ${__version__})
      set(PROJECT_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_PACKAGE_DEPENDENCIES ${PROJECT_PACKAGE_DEPENDENCIES} ${pkgname})
    elseif(${qualifier} STREQUAL PUBLIC)
      set(PROJECT_${pkgname}_VERSION ${__version__})
      set(PROJECT_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_PACKAGE_DEPENDENCIES ${PROJECT_PACKAGE_DEPENDENCIES} ${pkgname})
      set(PROJECT_INTERFACE_${pkgname}_VERSION ${__version__})
      set(PROJECT_INTERFACE_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_INTERFACE_PACKAGE_DEPENDENCIES ${PROJECT_INTERFACE_PACKAGE_DEPENDENCIES} ${pkgname})
    elseif(${qualifier} STREQUAL INTERFACE)
      set(PROJECT_INTERFACE_${pkgname}_VERSION ${__version__})
      set(PROJECT_INTERFACE_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_INTERFACE_PACKAGE_DEPENDENCIES ${PROJECT_INTERFACE_PACKAGE_DEPENDENCIES} ${pkgname})
    endif()
  endif()

  unset(__version__)
  unset(__components__)
  unset(__required_versions__)
  set(CMAKE_PREFIX_PATH ${__old_cpp__})
  unset(__old_cpp__)
endmacro()
################################################################################
function(pad str width char out)
  cmake_parse_arguments(ARGS "LEFT" "COLOR" "" ${ARGN})
  string(LENGTH ${str} length)
  if(ARGS_COLOR)
    math(EXPR padding "${width}-(${length}-10*${ARGS_COLOR})")
  else()
    math(EXPR padding "${width}-${length}")
  endif()
  if(padding GREATER 0)
    foreach(i RANGE ${padding})
      if(ARGS_LEFT)
        set(str "${char}${str}")
      else()
        set(str "${str}${char}")
      endif()
    endforeach()
  endif()
  set(${out} ${str} PARENT_SCOPE)
endfunction()
################################################################################
function(generate_package_components)
  join("${PROJECT_PACKAGE_COMPONENTS}" " " COMPS)
  set(PACKAGE_COMPONENTS "\
####### Expanded from @PACKAGE_COMPONENTS@ by configure_package_config_file() #########
set(${PROJECT_NAME}_PACKAGE_COMPONENTS ${COMPS})
")
  foreach(comp IN LISTS PROJECT_PACKAGE_COMPONENTS)
    string(CONCAT PACKAGE_COMPONENTS ${PACKAGE_COMPONENTS} "\
set(${PROJECT_NAME}_${comp}_FOUND TRUE)
")
  endforeach()
  string(CONCAT PACKAGE_COMPONENTS ${PACKAGE_COMPONENTS} "\
check_required_components(${PROJECT_NAME})
")
set(PACKAGE_COMPONENTS ${PACKAGE_COMPONENTS} PARENT_SCOPE)
endfunction()
################################################################################
