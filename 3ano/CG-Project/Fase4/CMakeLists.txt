cmake_minimum_required(VERSION 3.10)

# Project Name
PROJECT(Fase4)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(engine src/Engine/engine.cpp)
add_executable(generator src/Generator/generator.cpp)

if  (WIN32)

else(WIN32) #Linux and Mac
	find_package(OpenGL REQUIRED)
	find_package(GLUT REQUIRED)
	find_package(GLEW REQUIRED)

endif(WIN32)


include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

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
		src/Engine/catmull-rom.cpp
)

add_library(
		generatorLib
		src/Generator/calcPoints.cpp
		src/Generator/calcPoints.hpp
		src/Generator/bezier.cpp
		src/Generator/bezier.hpp
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

if (NOT APPLE)
	if (WIN32)
		set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
		include_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
		link_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
	else(WIN32)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	
	include_directories(${GLEW_INCLUDE_DIRS})
	link_libraries(${GLEW_LIBRARIES})
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	

	find_package(DevIL REQUIRED)
	link_libraries(${IL_LIBRARIES} )
	include_directories(ยง{IL_INCLUDE_DIR})
endif(NOT WIN32)	
	
if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
		message(ERROR ": GLEW not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")	
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")
		message(ERROR ": DevIL not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")	
	
	include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
	target_link_libraries(engine ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib 
										  ${TOOLKITS_FOLDER}/devil/devIL.lib
										  ${TOOLKITS_FOLDER}/glew/glew32.lib )
	
	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
													AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/devil/devil.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
													AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
	
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)
	
else(WIN32)
	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
endif (WIN32)