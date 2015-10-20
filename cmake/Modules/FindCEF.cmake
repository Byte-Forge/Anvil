# - Find Chromium Embedded Framework
# Find the Chromium Embedded Framework includes and library
# This module defines
#  CEF_INCLUDE_DIR, where to find db.h, etc.
#  CEF_LIBRARY, the libraries needed to use Chromium Embedded Framework.
#  CEF_FOUND, If false, do not try to use Chromium Embedded Framework.
# also defined, but not for general use are
FIND_PATH(CEF_INCLUDE_DIR cef/cef.h
  $ENV{CEF_DIR}/include
  /usr/local/include
  /usr/include
  )

FIND_LIBRARY(CEF_LIBRARY_RELEASE
  NAMES "libcef.lib"
  PATHS /usr/lib /usr/local/lib $ENV{CEF_DIR}/lib
  )

FIND_LIBRARY(CEF_LIBRARY_DEBUG
  NAMES "libcefd.lib"
  PATHS /usr/lib /usr/local/lib $ENV{CEF_DIR}/lib
  )

if(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
  set( CEF_LIBRARY optimized ${CEF_LIBRARY_RELEASE} debug ${CEF_LIBRARY_DEBUG} )
else()
  set( CEF_LIBRARY ${CEF_LIBRARY_RELEASE} )
endif()
MARK_AS_ADVANCED(CEF_LIBRARY_RELEASE CEF_LIBRARY_DEBUG)

IF (CEF_INCLUDE_DIR AND CEF_WRAPPER_INCLUDE_DIR)
    SET(CEF_INCLUDE_DIRS ${CEF_INCLUDE_DIR} ${CEF_WRAPPER_INCLUDE_DIR} )
ENDIF (CEF_INCLUDE_DIR AND CEF_WRAPPER_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CEF_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CEF DEFAULT_MSG CEF_LIBRARY CEF_INCLUDE_DIR)
mark_as_advanced( CEF_INCLUDE_DIRS CEF_LIBRARIES )

if(LUAJIT_FOUND)
  message(STATUS "Found CEF in ${CEF_INCLUDE_DIR}")
endif()
