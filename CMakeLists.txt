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
    MESSAGE("DETECTED Microsoft Windows")
    SET(EXTRA_LIBS "glu32.lib" "opengl32.lib")
ENDIF(APPLE)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -stdlib=libc++ ")
endif()

add_definitions(-DGLFW_INCLUDE_GLCOREARB)
add_definitions(-DASSIMP_BUILD_BOOST_WORKAROUND)

INCLUDE(FindFreetype)
IF(NOT FREETYPE_FOUND)
  FIND_LIBRARY(FREETYPE_LIBRARIES NAMES libfreetype freetype.dll PATHS "./libs/MacOS" "./libs/Windows" DOC "Freetype library")
  FIND_PATH(FREETYPE_INCLUDE_DIRS ftbuild.h "./includes" DOC "Freetype includes")
ENDIF(NOT FREETYPE_FOUND)
INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})

set(EIGEN_INCLUDE_DIRS /usr/local/include/eigen3)
set(EXTRA_LIBS "${EXTRA_LIBS}" glfw3 ${FREETYPE_LIBRARIES} assimp freeimage)
set(GLFW_INCLUDE_DIRS /usr/local/include/GL/)
set(FREEIMAGE_INCLUDE_DIRS /usr/local/include)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# OZ HEADERS
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
set(ROOT_HEADER_DIR oz-source)
set(ROOT_SOURCE_DIR oz-source)
set(STATIC_LIB_DIR lib)
set(SHADERS_DIR shaders)
set(APPS_DIR apps)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# IMPORT ASSIMP
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# add imported target
#add_library(assimp STATIC IMPORTED)

# point the imported target at the real file
#set_property(TARGET assimp PROPERTY IMPORTED_LOCATION ${STATIC_LIB_DIR}/libassimp.a)

file(GLOB_RECURSE OZ_SOURCE ${ROOT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE OZ_HEADER ${ROOT_HEADER_DIR}/*.h)
file(GLOB_RECURSE OZ_SHADER ${SHADERS_DIR}/*.glsl)

# INCLUDES
include_directories(
        ${APPS_DIR}
        ${ROOT_HEADER_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${EIGEN_INCLUDE_DIRS}
        ${FREEIMAGE_INCLUDE_DIRS}
        ${OZ_MATH}
)

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# OZ TARGET
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
add_executable(${PROJECT_NAME} ${APPS_DIR}/AppBasic/AppBasic.cpp ${OZ_SOURCE} ${OZ_HEADER} ${APPS_DIR}/AppBasic/AppBasic.h ${OZ_SHADER})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# TEST TARGETS
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
#add_executable(sandbox ${APPS_DIR}/main_eigen.cpp ${OZ_HEADER})
add_executable(pngtest ${APPS_DIR}/main_png.cpp ${OZ_HEADER})
target_link_libraries(pngtest ${EXTRA_LIBS})
