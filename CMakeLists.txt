cmake_minimum_required(VERSION 3.1)

#Name of this project is HPSE
set(PROJ_NAME HPSE)
project(${PROJ_NAME})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

#Use static SFML on windows
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(SFML_STATIC_LIBRARIES TRUE)
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
endif()

#The directory where source files are located
set(SRC_DIR "src")

#Find the Lua JIT compiler
find_package(LuaJIT REQUIRED)

#Find Chromium Embedded Framework
find_package(CEF REQUIRED)

#Find SFML modules for window and system
find_package(SFML 2.3 COMPONENTS window system REQUIRED)

#Compile all files
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/[a-z,A-Z]*.[c,h,def]*)
add_executable(${PROJ_NAME} ${SRC_FILES})

#Include our dependencies
target_include_directories(${PROJ_NAME} PUBLIC ${LUA_INCLUDE_DIR}
							${CEF_INCLUDE_DIR} ${SFML_INCLUDE_DIR})
#Link our dependencies
target_link_libraries(${PROJ_NAME} ${LUA_LIBRARIES} ${CEF_LIBRARY} ${CEF_WRAPPER_LIBRARY}
						${SFML_LIBRARIES} ${SFML_DEPENDENCIES} -ldl -lGL)
#Use C++ 14
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)