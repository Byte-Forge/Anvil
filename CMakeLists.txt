cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME HPSE)
project(${PROJ_NAME})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

set (SRC_DIR "src")

find_package(LuaJIT REQUIRED)

find_package(CEF REQUIRED)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.3 COMPONENTS window system REQUIRED)

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/[a-z,A-Z]*.[c,h,def]*)
add_executable(${PROJ_NAME} ${SRC_FILES})

target_include_directories(${PROJ_NAME} PUBLIC ${LUA_INCLUDE_DIR}
							${CEF_INCLUDE_DIR} ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${LUA_LIBRARIES} ${CEF_LIBRARY} 
						${SFML_LIBRARIES} ${SFML_DEPENDENCIES})