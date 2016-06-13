cmake_minimum_required(VERSION 3.1)

#Name of this project is Anvil
set(PROJ_NAME Anvil)
project(${PROJ_NAME})

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

#Use static SFML on windows
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(SFML_STATIC_LIBRARIES TRUE)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4244 /wd4018)
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
endif()

#The directory where source files are located
set(SRC_DIR "src")

#Find the Lua JIT compiler
find_package(LuaJIT REQUIRED)

#Find GLM for mathematics
find_package(GLM REQUIRED)

#Find OpenAL for audio
find_package(OpenAL REQUIRED)

#Find OpenGL 
find_package(OpenGL REQUIRED)

#Find RapidJSON
find_package(RapidJson REQUIRED)

#Find Freetype
find_package(Freetype REQUIRED)

#Find GLI
find_package(GLI REQUIRED)

#Find Vulkan
find_package(Vulkan)

#Add GLFW
set(GLFW_BUILD_EXAMPLES CACHE BOOL OFF)
set(GLFW_BUILD_TESTS CACHE BOOL OFF)
set(GLFW_BUILD_DOCS CACHE BOOL OFF)
add_subdirectory(glfw)

#Add spark
set(SPARK_BUILD_TEST CACHE BOOL OFF)
add_subdirectory(spark)

#Compile all files
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/[a-z,A-Z]*.[c,h,def]*)
add_executable(${PROJ_NAME} ${SRC_FILES})

if(VULKAN_FOUND)
	add_definitions(-DANVIL_USE_VULKAN)
	target_link_libraries(${PROJ_NAME} ${VULKAN_LIBRARY})
	target_include_directories(${PROJ_NAME} PUBLIC ${VULKAN_INCLUDE_DIR})
endif()

#Include our dependencies
target_include_directories(${PROJ_NAME} PUBLIC glfw spark ${LUA_INCLUDE_DIR} ${OPENAL_INCLUDE_DIR} ${GLI_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS}
						${GLM_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR})

#Link our dependencies
target_link_libraries(${PROJ_NAME} ${LUA_LIBRARIES} ${OPENAL_LIBRARY} ${FREETYPE_LIBRARIES}
						glfw spark ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS})

#Use C++ 14
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD_REQUIRED TRUE)

add_definitions(-DGLM_FORCE_AVX)

#Optimizations
if(MSVC)
    target_compile_options(${PROJ_NAME} PRIVATE /arch:AVX)
else()
    target_compile_options(${PROJ_NAME} PRIVATE -mavx)
endif()

#add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()