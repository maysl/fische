cmake_minimum_required( VERSION 2.6 )
project( fische )

find_package( PkgConfig )
pkg_check_modules( GLUT glut )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GLUT_CFLAGS_OTHER}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -O0 -g" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )

IF( NOT GLUT_FOUND )
    set( GLUT_LIBRARIES "glut" )
ENDIF( NOT GLUT_FOUND )

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

target_link_libraries( fische pthread ${GLUT_LIBRARIES} )

