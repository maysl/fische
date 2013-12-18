/***************************************************************
 * Copyright (C) 2013 Marcel Ebmer
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documen-
 * tation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **************************************************************/


#include "fische.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/thread.hpp>
#include <boost/program_options.hpp>

#include <GL/freeglut.h>

#define DEFAULT_WIDTH 800

using namespace std;



FISCHE*         g_fische = 0;
unsigned        g_quadsY;
unsigned        g_quadsX;
volatile bool   g_isrotating = false;
double          g_angle = 0;
double          g_lastangle = 0;
double          g_angleincrement = 0;
double          g_texright;
double          g_texleft;
int             g_detail = 1;
GLuint          g_texture;
vector<uint8_t> g_axis;
volatile bool   g_run = true;
bool            g_fullscreen = false;
bool            g_fullscreen_start;
bool            g_nervous_start;
volatile bool   g_data_available = false;
volatile bool   g_paused = false;


/**
 * animation callback for the fische library
 */
void on_beat( double frames_per_beat )
{
    if( !g_isrotating ) {
        g_isrotating = true;
        if( frames_per_beat < 1 )
            frames_per_beat = 12;
        g_angleincrement = 180 / 4 / frames_per_beat;
    }
}



/**
 * GLUT reshape callback function
 */
void on_resize( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1, 1, 1, -1, 3, 15 );

    double aspect = static_cast<double>( w ) / h;
    g_texleft = ( 2 - aspect ) / 4;
    g_texright = 1 - g_texleft;
    g_quadsY = 8;
    g_quadsX = ( aspect * 8 + 0.5 );

    g_axis.resize( g_quadsX * g_quadsY);
    for( size_t i = 0; i < g_quadsX * g_quadsY; ++ i )
        g_axis[i] = rand() % 2;
}



/**
 * drawing utility function
 */
inline void textured_quad( double center_x, double center_y,
                           double angle, double axis,
                           double width, double height,
                           double tex_left, double tex_right, double tex_top, double tex_bottom )
{
    glPushMatrix();

    glTranslatef( center_x, center_y, 0 );
    glRotatef( angle, axis, 1 - axis, 0 );

    double scale = 1 - sin( angle / 360 * M_PI ) / 3;
    glScalef( scale, scale, scale );

    glBegin( GL_QUADS );

    glTexCoord2d( tex_left, tex_top );
    glVertex3d( -width / 2, - height / 2, 0 );

    glTexCoord2d( tex_right, tex_top );
    glVertex3d( width / 2, - height / 2, 0 );

    glTexCoord2d( tex_right, tex_bottom );
    glVertex3d( width / 2, height / 2, 0 );

    glTexCoord2d( tex_left, tex_bottom );
    glVertex3d( -width / 2, height / 2, 0 );

    glEnd();

    glPopMatrix();
}



/**
 * GLUT display callback function
 */
void on_display( void )
{
    if( g_paused )
        return;

    if( g_isrotating ) {
        g_angle += g_angleincrement;
        if( g_angle - g_lastangle > 180 ) {
            g_lastangle = g_lastangle ? 0 : 180;
            g_angle = g_lastangle;
            g_isrotating = false;
        }
    }

    glBindTexture( GL_TEXTURE_2D, g_texture );
    glTexSubImage2D( GL_TEXTURE_2D, 0,
                     0, 0, g_fische->width, g_fische->height,
                     GL_RGBA, GL_UNSIGNED_BYTE,
                     fische_render( g_fische ) );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 0, -6.0 );
    glRotatef( g_angle, 0, 1, 0 );

    glClear( GL_COLOR_BUFFER_BIT );

    int quad_count = 0;
    double quad_width = 4.0 / g_quadsX;
    double quad_height = 4.0 / g_quadsY;
    double tex_width = ( g_texright - g_texleft );

    for( double X = 0; X < g_quadsX; X += 1 ) {
        for( double Y = 0; Y < g_quadsY; Y += 1 ) {
            double center_x = -2 + ( X + 0.5 ) * 4 / g_quadsX;
            double center_y = -2 + ( Y + 0.5 ) * 4 / g_quadsY;
            double tex_left = g_texleft + tex_width * X / g_quadsX;
            double tex_right = g_texleft + tex_width * ( X + 1 ) / g_quadsX;
            double tex_top = Y / g_quadsY;
            double tex_bottom = ( Y + 1 ) / g_quadsY;
            double angle = ( g_angle - g_lastangle ) * 4 - ( X + Y * g_quadsX ) / ( g_quadsX * g_quadsY ) * 360;
            if ( angle < 0 ) angle = 0;
            if ( angle > 360 ) angle = 360;

            textured_quad( center_x, center_y,
                           angle, g_axis[quad_count ++],
                           quad_width, quad_height,
                           tex_left, tex_right, tex_top, tex_bottom);
        }
    }

    glutSwapBuffers();
}



/**
 * change fullscreen status
 */
void toggle_fullscreen()
{
    static size_t stored_w = DEFAULT_WIDTH;
    static size_t stored_h = ( DEFAULT_WIDTH * 9 ) / 16;

    if( !g_fullscreen ) {
        stored_w = glutGet( GLUT_WINDOW_WIDTH );
        stored_h = glutGet( GLUT_WINDOW_HEIGHT );
        glutFullScreen();
        glutSetCursor( GLUT_CURSOR_NONE );
        g_fullscreen = true;
    }
    else {
        glutReshapeWindow( stored_w, stored_h );
        glutSetCursor( GLUT_CURSOR_INHERIT );
        g_fullscreen = false;
    }
}



/**
 * GLUT key press callback function
 */
void on_key( unsigned char c, int x, int y )
{
    switch( c ) {
        case 27:
            glutLeaveMainLoop();
            break;

        case 'f':
            toggle_fullscreen();
            break;

        case 'n':
            g_fische->nervous_mode = g_fische->nervous_mode ? 0 : 1;
            break;

        case 'p':
            g_paused = g_paused ? false : true;
    }
}



/**
 * GLUT idle callback function
 */
void on_idle()
{
    static struct timeval tv;
    static int64_t last = 0;

    gettimeofday( &tv, 0 );
    int64_t now = tv.tv_sec * 1000000 + tv.tv_usec;
    if( !last )
        last = now;
    else {
        int delay = 20000 - ( now - last );
        if( delay > 0 ) {
            boost::this_thread::sleep( boost::posix_time::microseconds( delay ) );
            last = now + delay;
        }
        else
            last = now;
    }

    glutPostRedisplay();
}



/**
 * threaded input from stdin
 */
void read_thread_func()
{
    char buf[4096];

    for( ;; ) {
        cin.read( buf, 4096 );
        g_data_available = true;
        if( g_run && !g_paused )
            fische_audiodata( g_fische, buf, 4096 );
        else if( !g_run )
            break;
    }
}



/**
 * install a timeout for first audio data input
 */
void audio_valid_thread_func()
{
    boost::this_thread::sleep( boost::posix_time::seconds( 1 ) );
    if( !g_data_available ) {
        cerr << "*** please pipe me some data!\n";
        glutLeaveMainLoop();
    }
}



/**
 * GLUT and OpenGL initialization
 */
void glut_gl_init( int& argc, char**& argv )
{
    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_DOUBLE );
    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE,
                   GLUT_ACTION_GLUTMAINLOOP_RETURNS );

    glutInitWindowSize( DEFAULT_WIDTH, ( DEFAULT_WIDTH * 9 ) / 16 );
    glutCreateWindow( "fische 4" );

    glutDisplayFunc( on_display );
    glutReshapeFunc( on_resize );
    glutKeyboardFunc( on_key );
    glutIdleFunc( on_idle );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_TEXTURE_2D );
    glDisable( GL_DEPTH_TEST );
    glPolygonMode( GL_FRONT, GL_FILL );
}



/**
 * fische library initialization
 */
void fische_init()
{
    g_fische = fische_new();
    g_fische->on_beat = &on_beat;
    g_fische->pixel_format = FISCHE_PIXELFORMAT_0xAABBGGRR;
    g_fische->line_style = FISCHE_LINESTYLE_THICK;
    g_fische->audio_format = FISCHE_AUDIOFORMAT_S16;
    g_fische->used_cpus = boost::thread::hardware_concurrency();
    g_fische->height = 128 * pow( 2, g_detail );
    g_fische->width = 2 * g_fische->height;
    if( g_nervous_start )
        g_fische->nervous_mode = 1;

    if( fische_start( g_fische ) != 0 ) {
        cerr << "fische failed to start: " << g_fische->error_text << endl;
        exit( EXIT_FAILURE );
    }
}



/**
 * create an OpenGL texture
 */
void texture_init()
{
    glGenTextures( 1, &g_texture );
    glBindTexture( GL_TEXTURE_2D, g_texture );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
                  g_fische->width, g_fische->height,
                  0, GL_RGBA, GL_UNSIGNED_BYTE,
                  fische_render( g_fische ) );
}



/**
 * handle program options
 */
void parse_commandline( int& argc, char**& argv )
{
    namespace po = boost::program_options;
    po::options_description desc( "known options" );
    desc.add_options()
        ( "help,h", "this help message" )
        ( "detail,d", po::value<int>( &g_detail )->default_value( 2 ), "level of detail [0..3] (this eats CPU)" )
        ( "nervous,n", po::value<bool>( &g_nervous_start )->default_value( false )->implicit_value( true ), "start in nervous mode (more mode changes)" )
        ( "fullscreen,f", po::value<bool>( &g_fullscreen_start )->default_value( false )->implicit_value( true ), "start in fullscreen mode" )
    ;

    po::variables_map vm;
    po::store( po::parse_command_line( argc, argv, desc ), vm );
    po::notify( vm );

    if( vm.count( "help" ) ) {
        cout << "\nusage: <some_data_source> | fische [options]\n"
             << desc << "\n";
        exit( EXIT_SUCCESS );
    }
}



int main( int argc, char** argv )
{
    glut_gl_init( argc, argv );
    parse_commandline( argc, argv );
    fische_init();
    texture_init();

    boost::thread _( read_thread_func );
    boost::thread o( audio_valid_thread_func );

    if( g_fullscreen_start ) {
        toggle_fullscreen();
    }

    glutMainLoop();

    g_run = false;
    fische_free( g_fische );
}
