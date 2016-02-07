# - Find rapidjson headers and lib.
# This module defines RAPIDJSON_INCLUDE_DIR, the directory containing headers

set(RAPIDJSON_SEARCH_HEADER_PATHS
  ${CMAKE_SOURCE_DIR}/thirdparty/rapidjson/include/
)

find_path(RAPIDJSON_INCLUDE_DIR rapidjson/rapidjson.h HINTS
  ${RAPIDJSON_SEARCH_HEADER_PATHS})

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