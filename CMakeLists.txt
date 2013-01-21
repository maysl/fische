################################################################
 # Copyright (C) 2013 Marcel Ebmer
 #
 # Permission is hereby granted, free of charge, to any person
 # obtaining a copy of this software and associated documen-
 # tation files (the "Software"), to deal in the Software
 # without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense,
 # and/or sell copies of the Software, and to permit persons to
 # whom the Software is furnished to do so, subject to the
 # following conditions:
 #
 # The above copyright notice and this permission notice shall
 # be included in all copies or substantial portions of the
 # Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 # KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 # WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 # PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 # OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 # OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 # OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 # SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ###############################################################


cmake_minimum_required( VERSION 2.6 )
project( fische )

IF( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE "Release" )
ENDIF( NOT CMAKE_BUILD_TYPE )

find_package( PkgConfig )
pkg_check_modules( GLUT glut )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GLUT_CFLAGS_OTHER}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -O0 -g" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s" )

IF( NOT GLUT_FOUND )
    set( GLUT_LIBRARIES "-lglut -lGL -lGLU" )
ENDIF( NOT GLUT_FOUND )

set( BOOST_LIBRARIES "-lboost_system -lboost_thread -lboost_program_options" )
IF( CMAKE_SYSTEM_NAME MATCHES "Windows" )
    set( BOOST_LIBRARIES "-lboost_system-mt -lboost_thread_win32-mt -lboost_program_options-mt" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_THREAD_USE_LIB" )
ENDIF( CMAKE_SYSTEM_NAME MATCHES "Windows" )

include_directories( src ${GLUT_INCLUDE_DIRS} )

add_executable( fische
                src/analyst.c
                src/audiobuffer.c
                src/blurengine.c
                src/cpudetect.c
                src/fische.c
                src/screenbuffer.c
                src/vector.c
                src/vectorfield.c
                src/wavepainter.c
                src/main.cpp )

target_link_libraries( fische -lpthread ${BOOST_LIBRARIES} ${GLUT_LIBRARIES} )

