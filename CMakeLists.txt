cmake_minimum_required( VERSION 2.6 )
project( fische )

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
    set( BOOST_LIBRARIES "-DBOOST_THREAD_USE_LIB -lboost_system-mt -lboost_thread_win32-mt -lboost_program_options-mt" )
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

