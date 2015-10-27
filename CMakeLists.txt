cmake_minimum_required(VERSION 3.1)

set(PROJ_NAME HPSE)
project(${PROJ_NAME})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)

set (SRC_DIR "src")

find_package(LuaJIT REQUIRED)

find_package(CEF REQUIRED)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.3 COMPONENTS window system REQUIRED)

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/[a-z,A-Z]*.[c,h,def]*)
add_executable(${PROJ_NAME} ${SRC_FILES})

target_include_directories(${PROJ_NAME} PUBLIC ${LUA_INCLUDE_DIR}
							${CEF_INCLUDE_DIR} ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${LUA_LIBRARIES} ${CEF_LIBRARY} ${CEF_WRAPPER_LIBRARY}
						${SFML_LIBRARIES} ${SFML_DEPENDENCIES} -ldl -lGL)
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)