project(oz CXX)
set( CMAKE_VERBOSE_MAKEFILE on )
cmake_minimum_required(VERSION 2.8.10)

#+++++++++++++++++++a+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# CMAKE MODULES PATH
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# EXTRA LIBS
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
IF(APPLE)
    MESSAGE("DETECTED APPLE")
    SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL -framework IOKit")
ELSEIF(MSVC)
        SET(EXTRA_LIBS "glu32.lib" "opengl32.lib")
ENDIF(APPLE)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -stdlib=libc++")
endif()

INCLUDE(FindFreetype)
IF(NOT FREETYPE_FOUND)
  FIND_LIBRARY(FREETYPE_LIBRARIES NAMES libfreetype freetype.dll PATHS "./libs/MacOS" "./libs/Windows" DOC "Freetype library")
  FIND_PATH(FREETYPE_INCLUDE_DIRS ftbuild.h "./includes" DOC "Freetype includes")
ENDIF(NOT FREETYPE_FOUND)
INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})

set(EXTRA_LIBS "${EXTRA_LIBS}" glfw ${FREETYPE_LIBRARIES})
set(EIGEN_INCLUDE_DIRS /usr/local/include/eigen3)
set(GLFW_INCLUDE_DIRS /usr/local/include/GL/)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# OZ HEADERS
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
set(ROOT_HEADER_DIR oz-source)
set(ROOT_SOURCE_DIR oz-source)
set(ROOT_APP_DIR apps)


file(GLOB_RECURSE OZ_SOURCE ${ROOT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE OZ_HEADER ${ROOT_HEADER_DIR}/*.h)

# INCLUDES
include_directories(
        ${ROOT_HEADER_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${EIGEN_INCLUDE_DIRS}
)

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# OZ TARGET
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
link_libraries(/usr/local/lib)
add_executable(${PROJECT_NAME} ${ROOT_APP_DIR}/AppBasic/AppBasic.cpp ${OZ_SOURCE} ${OZ_HEADER})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# TEST TARGETS
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
add_executable(sandbox ${ROOT_APP_DIR}/main_eigen.cpp ${OZ_HEADER})
