################################################################################
# Copyright (C) 2018-2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(CMAKE_VERSION VERSION_LESS 3.12)
  message(FATAL_ERROR "Module FairFindPackage2 requires CMake 3.12 or later!")
endif()

include_guard(GLOBAL)

#[=======================================================================[.rst:
****************
FairFindPackage2
****************
.. versionadded:: 0.1.0

Requires CMake 3.12 or later.

.. contents::
   :local:

---------

On inclusion
============

.. versionadded:: 0.2.0

Add this module as a ``PRIVATE`` package dependency if included from the
FairCMakeModules package.

#]=======================================================================]

if(FairCMakeModules_FOUND)
  list(APPEND PROJECT_PACKAGE_DEPENDENCIES FairCMakeModules)
  if(_FairCMakeModules_REQUESTED_VERSION)
    set(PROJECT_FairCMakeModules_VERSION "${_FairCMakeModules_REQUESTED_VERSION}")
    unset(_FairCMakeModules_REQUESTED_VERSION)
  endif()
endif()

# private helper function to find longest common prefix in given
# true-thy strings
function(__find_package2_lcp)
  cmake_parse_arguments(ARGS "" "OUTVAR" "STRINGS" ${ARGN})

  if(NOT ARGS_OUTVAR)
    message(AUTHOR_WARNING "Parameter OUTVAR required. Skipping.")
    return()
  endif()

  if(NOT ARGS_STRINGS)
    message(AUTHOR_WARNING "Parameter list STRINGS required. Skipping.")
    return()
  endif()

  list(LENGTH ARGS_STRINGS __list_length)
  if(__list_length EQUAL 1)
    set(${ARGS_OUTVAR} "${ARGS_STRINGS}" PARENT_SCOPE)
    return()
  endif()

  set(__lcp)
  set(__pos 0)

  set(__pos_ok TRUE)
  while(__pos_ok)
    set(__current_char)
    foreach(__str IN LISTS ARGS_STRINGS)
      if(__str)
        string(LENGTH "${__str}" __length)
        if(__length GREATER __pos)
          string(SUBSTRING "${__str}" ${__pos} 1 __char)
          string(LENGTH "${__current_char}" __current_char_length)
          if(NOT __current_char_length)
            set(__current_char ${__char})
          else()
            if(NOT __current_char STREQUAL __char)
              set(__pos_ok FALSE)
              break()
            endif()
          endif()
        else()
          set(__pos_ok FALSE)
          break()
        endif()
      endif()
    endforeach()
    string(LENGTH "${__current_char}" __current_char_length)
    if(__pos_ok AND __current_char_length)
      string(APPEND __lcp ${__current_char})
    endif()
    math(EXPR __pos "${__pos} + 1")
  endwhile()

  set(${ARGS_OUTVAR} "${__lcp}" PARENT_SCOPE)
endfunction()

#[=======================================================================[.rst:
---------

``find_package2()``
===================

Wrapper around CMake's native :command:`find_package` command to add some
features and bookkeeping.

.. code-block:: cmake

  find_package2(PRIVATE|PUBLIC|INTERFACE|BUNDLED <pkgname>
                [VERSION <version>]
                [COMPONENTS <component> [<component>...]]
                [OPTIONAL_COMPONENTS <component> [<component>...]]
                [ADD_REQUIREMENTS_OF <dep_pkgname> [<dep_pkgname>...]]
                [<any other native `find_package` option>...])


The qualifier (\ ``PRIVATE|PUBLIC|INTERFACE|BUNDLED``\ ) is used to
populate the variables
:variable:`PROJECT_[INTERFACE]_<pkgname>_([VERSION]|[COMPONENTS]|PACKAGE_DEPENDENCIES)`
accordingly. This bookkeeping information is used to print a dependencies
found summary table and in the generation of a CMake package. ``BUNDLED``
decays to ``PUBLIC`` if the variable `<pkgname>_BUNDLED` is false and to
``PRIVATE`` otherwise.

When a dependending package is listed with ``ADD_REQUIREMENTS_OF`` the
variables :variable:`<dep_pkgname>_<pkgname>_VERSION|COMPONENTS` are looked
up and merged with ``VERSION`` (selected highest version) and ``COMPONENTS``
(deduplicated) requirements. ``COMPONENTS`` and ``VERSION`` args are then
just passed to :command:`find_package`.

.. versionchanged:: 0.2.0

The ``ADD_REQUIREMENTS_OF`` argument is now a no-op and only remains for
compatibility reasons. :command:`find_package2` now always merges all known
requirements.

.. versionadded:: 1.0.0

By default :command:`find_package2` tries to determine the install prefix if
the package is found. The result is populated to the variable
:variable:`<pkgname>_PREFIX``. This behaviour can be disabled by setting the
:variable:`FAIR_NO_AUTO_DETECT_PREFIX` to ``ON``.

Support for ``OPTIONAL_COMPONENTS`` was added.

#]=======================================================================]

macro(find_package2 qualifier pkgname)
  cmake_parse_arguments(ARGS "" "VERSION"
                        "COMPONENTS;ADD_REQUIREMENTS_OF;OPTIONAL_COMPONENTS" ${ARGN})

  string(TOUPPER ${pkgname} __pkgname_upper__)
  string(TOLOWER ${pkgname} __pkgname_lower__)
  set(__old_cpp__ ${CMAKE_PREFIX_PATH})
  set(CMAKE_PREFIX_PATH ${${__pkgname_upper__}_ROOT} $ENV{${__pkgname_upper__}_ROOT} ${CMAKE_PREFIX_PATH})

  # build lists of required versions and components
  unset(__required_versions__)
  unset(__components__)
  unset(__optional_components__)
  if(ARGS_VERSION)
    list(APPEND __required_versions__ ${ARGS_VERSION})
  endif()
  if(ARGS_COMPONENTS)
    list(APPEND __components__ ${ARGS_COMPONENTS})
  endif()
  if(ARGS_OPTIONAL_COMPONENTS)
    list(APPEND __optional_components__ ${ARGS_OPTIONAL_COMPONENTS})
  endif()
  foreach(req_pkgname IN LISTS PROJECT_PACKAGE_DEPENDENCIES)
    if(${req_pkgname}_${pkgname}_VERSION)
      list(APPEND __required_versions__ ${${req_pkgname}_${pkgname}_VERSION})
    endif()
    if(${req_pkgname}_${pkgname}_COMPONENTS)
      list(APPEND __components__ ${${req_pkgname}_${pkgname}_COMPONENTS})
    endif()
    if(${req_pkgname}_${pkgname}_OPTIONAL_COMPONENTS)
      list(APPEND __optional_components__ ${${req_pkgname}_${pkgname}_OPTIONAL_COMPONENTS})
    endif()
  endforeach()

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
  # deduplicate optional component list
  if(__optional_components__)
    list(REMOVE_DUPLICATES __optional_components__)
  endif()

  if(NOT FAIR_NO_AUTO_DETECT_PREFIX)
    set(PACKAGE_PREFIX_DIR)
  endif()

  # call native find_package
  if(__components__ AND __optional_components__)
    find_package(${pkgname} ${__version__} QUIET COMPONENTS ${__components__} OPTIONAL_COMPONENTS ${__optional_components__} ${ARGS_UNPARSED_ARGUMENTS})
  elseif(__components__ AND NOT __optional_components__)
    find_package(${pkgname} ${__version__} QUIET COMPONENTS ${__components__} ${ARGS_UNPARSED_ARGUMENTS})
  elseif(NOT __components__ AND __optional_components__)
    find_package(${pkgname} ${__version__} QUIET OPTIONAL_COMPONENTS ${__optional_components__} ${ARGS_UNPARSED_ARGUMENTS})
  else()
    find_package(${pkgname} ${__version__} QUIET ${ARGS_UNPARSED_ARGUMENTS})
  endif()

  if(NOT DEFINED ${pkgname}_PREFIX AND ${pkgname}_FOUND AND NOT FAIR_NO_AUTO_DETECT_PREFIX)
    # try to detect install prefix
    set(__candidates)
    set(__subdir_candidates)
    foreach(__pkg IN ITEMS ${pkgname} ${__pkgname_upper__} ${__pkgname_lower__})
      # guess targets
      foreach(__pkg2 IN ITEMS ${pkgname} ${__pkgname_upper__} ${__pkgname_lower__})
        foreach(__tgt IN ITEMS
          "${__pkg}"
          "${__pkg}::headers"
          "${__pkg}::${__pkg2}"
          "${__pkg}::${__pkg2}_shared"
          "${__pkg}::${__pkg2}_static"
        )
          if(TARGET ${__tgt})
            get_target_property(__includes ${__tgt} INTERFACE_INCLUDE_DIRECTORIES)
            if(__includes)
              list(APPEND __subdir_candidates "${__includes}")
            endif()
            unset(__includes)
            get_target_property(__location ${__tgt} INTERFACE_LOCATION)
            if(__location)
              list(APPEND __subdir_candidates "${__location}")
            endif()
            unset(__location)
          endif()
        endforeach()
      endforeach()

      # guess variables
      foreach(__var IN ITEMS
        ${${__pkg}_BIN_DIR}
        ${${__pkg}_BINDIR}
        ${${__pkg}_INCLUDE_DIR}
        ${${__pkg}_INCLUDEDIR}
        ${${__pkg}_INCLUDE_DIRS}
        ${${__pkg}_INCLUDEDIRS}
        ${${__pkg}_INCDIR}
        ${${__pkg}_LIBRARY_DIR}
        ${${__pkg}_LIBRARYDIR}
        ${${__pkg}_LIBRARY_DIRS}
        ${${__pkg}_LIBRARYDIRS}
        ${${__pkg}_LIBRARY_SHARED}
        ${${__pkg}_LIBRARY_STATIC}
        ${${__pkg}_LIBDIR}
        ${${__pkg}_DIR}
      )
        if(__var)
          list(APPEND __subdir_candidates ${__var})
        endif()
      endforeach()
      list(APPEND __candidates
        ${${__pkg}_EXECUTABLE}
        ${${__pkg}_PREFIX}
        ${${__pkg}_INSTALL_PREFIX}
        ${${__pkg}_INSTALLPREFIX}
        ${${__pkg}_INSTALL}
      )
    endforeach()
    list(APPEND __candidates ${PACKAGE_PREFIX_DIR})

    foreach(__subcand IN LISTS __subdir_candidates)
      # we assume that these paths are least one directory
      # level below the prefix
      if(__subcand)
        get_filename_component(__cand ${__subcand}/.. ABSOLUTE)
        list(APPEND __candidates "${__cand}")
        unset(__cand)
      endif()
    endforeach()
    if(__candidates)
      list(REMOVE_DUPLICATES __candidates)
      __find_package2_lcp(OUTVAR ${pkgname}_PREFIX STRINGS ${__candidates})
      message(VERBOSE "Guessing '${pkgname}' install prefix from: '${__candidates}' --> '${${pkgname}_PREFIX}'")
    endif()
    unset(__subdir_candidates)
    unset(__candidates)

    if(${pkgname}_PREFIX AND EXISTS ${pkgname}_PREFIX)
      set(${pkgname}_PREFIX "${${pkgname}_PREFIX}" CACHE PATH "Auto-detected install prefix of package '${pkgname}'")
    endif()
  endif()

  if(${qualifier} STREQUAL BUNDLED)
    if(${pkgname}_BUNDLED)
      set(__qualifier__ PRIVATE)
    else()
      set(__qualifier__ PUBLIC)
    endif()
  else()
    set(__qualifier__ ${qualifier})
  endif()

  if(${pkgname}_FOUND)
    if(${__qualifier__} STREQUAL PRIVATE)
      set(PROJECT_${pkgname}_VERSION ${__version__})
      set(PROJECT_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_${pkgname}_OPTIONAL_COMPONENTS ${__optional_components__})
      list(APPEND PROJECT_PACKAGE_DEPENDENCIES ${pkgname})
    elseif(${__qualifier__} STREQUAL PUBLIC)
      set(PROJECT_${pkgname}_VERSION ${__version__})
      set(PROJECT_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_${pkgname}_OPTIONAL_COMPONENTS ${__optional_components__})
      list(APPEND PROJECT_PACKAGE_DEPENDENCIES ${pkgname})
      set(PROJECT_INTERFACE_${pkgname}_VERSION ${__version__})
      set(PROJECT_INTERFACE_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_INTERFACE_${pkgname}_OPTIONAL_COMPONENTS ${__optional_components__})
      list(APPEND PROJECT_INTERFACE_PACKAGE_DEPENDENCIES ${pkgname})
    elseif(${__qualifier__} STREQUAL INTERFACE)
      set(PROJECT_INTERFACE_${pkgname}_VERSION ${__version__})
      set(PROJECT_INTERFACE_${pkgname}_COMPONENTS ${__components__})
      set(PROJECT_INTERFACE_${pkgname}_OPTIONAL_COMPONENTS ${__optional_components__})
      list(APPEND PROJECT_INTERFACE_PACKAGE_DEPENDENCIES ${pkgname})
    endif()
  endif()

  unset(__pkgname_lower__)
  unset(__pkgname_upper__)
  unset(__qualifier__)
  unset(__version__)
  unset(__components__)
  unset(__optional_components__)
  unset(__required_versions__)
  set(CMAKE_PREFIX_PATH ${__old_cpp__})
  unset(__old_cpp__)
endmacro()

#[=======================================================================[.rst:
---------

``find_package2_implicit_dependencies()``
=========================================

.. versionadded:: 0.2.0

Loop over all remaining implicit dependencies and :command:`find_package2`
them.

.. code-block:: cmake

  find_package2_implicit_dependencies([EXCLUDE <pkg> [<pkg>...]])

Listed packages with ``EXCLUDE`` are filtered out.

#]=======================================================================]

macro(find_package2_implicit_dependencies)
  cmake_parse_arguments(ARGS "" "" "EXCLUDE" ${ARGN})

  set(__2_new_implicit__ ON)
  while(__2_new_implicit__)
    set(__2_new_implicit__ OFF)
    foreach(dep IN LISTS PROJECT_PACKAGE_DEPENDENCIES)
      if(NOT dep IN_LIST ARGS_EXCLUDE)
        foreach(implicit IN LISTS ${dep}_PACKAGE_DEPENDENCIES)
          if(    NOT implicit IN_LIST PROJECT_PACKAGE_DEPENDENCIES
             AND NOT implicit IN_LIST ARGS_EXCLUDE)
            set(__2_new_implicit__ ON)
            unset(__2_version__)
            unset(__2_components__)
            if(${dep}_${implicit}_VERSION)
              set(__2_components__ VERSION ${${dep}_${implicit}_VERSION})
            endif()
            if(${dep}_${implicit}_COMPONENTS)
              set(__2_components__ COMPONENTS ${${dep}_${implicit}_COMPONENTS})
            endif()
            if(dep IN_LIST PROJECT_INTERFACE_PACKAGE_DEPENDENCIES)
              set(__2_qualifier__ PUBLIC)
            else()
              set(__2_qualifier__ PRIVATE)
            endif()
            find_package2(${__2_qualifier__} ${implicit} ${__2_version__} ${__2_components__} REQUIRED)
          endif()
        endforeach()
      endif()
    endforeach()
  endwhile()
  unset(__2_qualifier__)
  unset(__2_new_implicit__)
  unset(__2_version__)
  unset(__2_components__)
endmacro()

#[=======================================================================[.rst:
---------

``fair_generate_package_dependencies()``
========================================

.. versionadded:: 0.2.0

.. code-block:: cmake

  fair_generate_package_dependencies()

Populates the variable :variable:`PACKAGE_DEPENDENCIES` with a CMake snippet
from the public dependencies (read from
:variable:`PROJECT_INTERFACE_PACKAGE_DEPENDENCIES`) that can be included in a
CMake package config file to export its package dependencies.

These exported dependencies will be respected by :command:`find_package2`.

#]=======================================================================]

function(fair_generate_package_dependencies)
  list(JOIN PROJECT_INTERFACE_PACKAGE_DEPENDENCIES " " DEPS)
  set(PACKAGE_DEPENDENCIES "\
####### Expanded from PACKAGE_DEPENDENCIES by configure_package_config_file() #######

set(${PROJECT_NAME}_PACKAGE_DEPENDENCIES ${DEPS})

")
  foreach(dep IN LISTS PROJECT_INTERFACE_PACKAGE_DEPENDENCIES)
    list(JOIN PROJECT_INTERFACE_${dep}_COMPONENTS " " COMPS)
    if(COMPS)
      string(APPEND PACKAGE_DEPENDENCIES "\
set(${PROJECT_NAME}_${dep}_COMPONENTS ${COMPS})
")
    endif()
    list(JOIN PROJECT_INTERFACE_${dep}_OPTIONAL_COMPONENTS " " OPT_COMPS)
    if(OPT_COMPS)
      string(APPEND PACKAGE_DEPENDENCIES "\
set(${PROJECT_NAME}_${dep}_OPTIONAL_COMPONENTS ${OPT_COMPS})
")
    endif()
    if(PROJECT_INTERFACE_${dep}_VERSION)
      string(APPEND PACKAGE_DEPENDENCIES "\
set(${PROJECT_NAME}_${dep}_VERSION ${PROJECT_INTERFACE_${dep}_VERSION})
")
    endif()
  endforeach()
  string(APPEND PACKAGE_DEPENDENCIES "\

#####################################################################################")
  set(PACKAGE_DEPENDENCIES ${PACKAGE_DEPENDENCIES} PARENT_SCOPE)
endfunction()
