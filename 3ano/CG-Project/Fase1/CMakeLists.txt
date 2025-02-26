cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(Fase1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(engine src/Engine/engine.cpp)
add_executable(generator src/Generator/generator.cpp)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_library(
		Lib
		src/tinyXML/tinystr.cpp
		src/tinyXML/tinyxml.cpp
		src/tinyXML/tinyxmlerror.cpp
		src/tinyXML/tinyxmlparser.cpp
)

add_library(
		engineLib
		src/Engine/world.cpp
		src/Engine/world.hpp
)

add_library(
		generatorLib
		src/Generator/calcPoints.cpp
		src/Generator/calcPoints.hpp
)

add_library(
		utilsLib
		src/Utils/utils.cpp
		src/Utils/utils.hpp
)

target_link_libraries(generator generatorLib)
target_link_libraries(generator Lib)
target_link_libraries(generator utilsLib)

target_link_libraries(engine engineLib)
target_link_libraries(engine Lib)
target_link_libraries(engine utilsLib)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")


	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(engine ${OPENGL_LIBRARIES}
			${TOOLKITS_FOLDER}/glut/glut32.lib)

	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)

else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)
