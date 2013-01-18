#include <iostream>

#include <GL/freeglut.h>

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE );
    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE,
                   GLUT_ACTION_GLUTMAINLOOP_RETURNS );
    glutInitWindowSize( 1024, 576 );
    glutCreateWindow( "fische 4" );
    glutMainLoop();
}
