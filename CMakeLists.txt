cmake_minimum_required(VERSION 3.1)

#Name of this project is Anvil
set(PROJ_NAME Anvil)
project(${PROJ_NAME})

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

#Find LibRocket
find_package(ROCKET REQUIRED)

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

#Find GLI
find_package(GLFW REQUIRED)

#Compile all files
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/[a-z,A-Z]*.[c,h,def]*)
add_executable(${PROJ_NAME} ${SRC_FILES})

#Include our dependencies
target_include_directories(${PROJ_NAME} PUBLIC ${LUA_INCLUDE_DIR} ${OPENAL_INCLUDE_DIR} ${GLI_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS}
						${ROCKET_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIR})

#Link our dependencies
target_link_libraries(${PROJ_NAME} ${LUA_LIBRARIES} ${ROCKET_LIBRARIES} ${OPENAL_LIBRARY} ${FREETYPE_LIBRARIES}
						${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS})


set_target_properties(${PROJ_NAME} PROPERTIES COMPILE_DEFINITIONS ROCKET_STATIC_LIB)
#Use C++ 14
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD_REQUIRED  TRUE)