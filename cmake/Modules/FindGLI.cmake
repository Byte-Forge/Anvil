SET(_gli_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include")

# check environment variable
SET(_gli_ENV_ROOT_DIR "$ENV{GLI_ROOT_DIR}")

IF(NOT GLI_ROOT_DIR AND _gli_ENV_ROOT_DIR)
    SET(GLI_ROOT_DIR "${_gli_ENV_ROOT_DIR}")
ENDIF(NOT GLI_ROOT_DIR AND _gli_ENV_ROOT_DIR)

# put user specified location at beginning of search
IF(GLI_ROOT_DIR)
    SET(_gli_HEADER_SEARCH_DIRS "${GLI_ROOT_DIR}"
                                "${GLI_ROOT_DIR}/include"
                                 ${_gli_HEADER_SEARCH_DIRS})
ENDIF(GLI_ROOT_DIR)

# locate header
FIND_PATH(GLI_INCLUDE_DIR "gli/gli.hpp"
    PATHS ${_gli_HEADER_SEARCH_DIRS})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLI DEFAULT_MSG
    GLI_INCLUDE_DIR)

IF(GLI_FOUND)
    SET(GLI_INCLUDE_DIRS "${GLI_INCLUDE_DIR}")
    message(STATUS "Found GLI ${GLI_INCLUDE_DIR}")
ENDIF(GLI_FOUND)