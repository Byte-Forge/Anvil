# - Find rapidjson headers and lib.
# This module defines RAPIDJSON_INCLUDE_DIR, the directory containing headers

# check environment variable
set(_rapidjson_ENV_ROOT_DIR "$ENV{RAPIDJSON_ROOT_DIR}")

if(NOT RAPIDJSON_ROOT_DIR AND _rapidjson_ENV_ROOT_DIR)
    SET(RAPIDJSON_ROOT_DIR "${_rapidjson_ENV_ROOT_DIR}")
endif(NOT RAPIDJSON_ROOT_DIR AND _rapidjson_ENV_ROOT_DIR)

# put user specified location at beginning of search
if(RAPIDJSON_ROOT_DIR)
    set(RAPIDJSON_SEARCH_HEADER_PATHS "${RAPIDJSON_ROOT_DIR}"
                                "${RAPIDJSON_ROOT_DIR}/include"
                                 ${RAPIDJSON_SEARCH_HEADER_PATHS})
endif(RAPIDJSON_ROOT_DIR)

find_path(RAPIDJSON_INCLUDE_DIR "rapidjson/rapidjson.h"
    PATHS ${RAPIDJSON_SEARCH_HEADER_PATHS})

if (RAPIDJSON_INCLUDE_DIR)
  set(RAPIDJSON_FOUND TRUE)
else ()
  set(RAPIDJSON_FOUND FALSE)
endif ()

if (RAPIDJSON_FOUND)
  if (NOT RAPIDJSON_FIND_QUIETLY)
    message(STATUS "RapidJson headers found in: ${RAPIDJSON_INCLUDE_DIR}")
  endif ()
else ()
  message(STATUS "RapidJson headers NOT found.")
endif ()

mark_as_advanced(
  RAPIDJSON_INCLUDE_DIR
)