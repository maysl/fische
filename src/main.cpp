#include <iostream>
#include <cassert>

#include <GL/freeglut.h>

void on_resize( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, w, 0, h );
}

void on_display( void )
{
    glClearColor( .2f, 0.f, 0.f, 0.f );
    glClear( GL_COLOR_BUFFER_BIT );

    glutSwapBuffers();
    glutPostRedisplay();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE );
    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE,
                   GLUT_ACTION_GLUTMAINLOOP_RETURNS );

    glutInitWindowSize( 1024, 576 );
    glutCreateWindow( "fische 4" );

    glutDisplayFunc( on_display );
    glutReshapeFunc( on_resize );

    glutMainLoop();
}
