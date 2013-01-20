#include "fische.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/thread.hpp>
#include <boost/program_options.hpp>

#ifdef _WIN32
#include <unistd.h>
#endif

#include <GL/freeglut.h>

#define DEFAULT_WIDTH 800

using namespace std;



// some globals
FISCHE*         g_fische = 0;
unsigned        g_quadsY = 8;
unsigned        g_quadsX = ( g_quadsY * 16 ) / 9;
volatile bool   g_isrotating = false;
double          g_angle = 0;
double          g_lastangle = 0;
double          g_angleincrement = 0;
double          g_texright = 0.94444444;
double          g_texleft = 0.05555555;
int             g_detail = 1;
GLuint          g_texture = -1;
vector<uint8_t> g_axis;
volatile bool   g_run = true;
bool            g_fullscreen = false;
bool            g_nervous_start;



void on_beat( double frames_per_beat )
{
    if( !g_isrotating ) {
        g_isrotating = true;
        if( frames_per_beat < 1 )
            frames_per_beat = 12;
        g_angleincrement = 180 / 4 / frames_per_beat;
    }
}



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



void textured_quad( double center_x, double center_y,
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

void on_display( void )
{
    if( g_isrotating ) {
        g_angle += g_angleincrement;
        if( g_angle - g_lastangle > 180 ) {
            g_lastangle = g_lastangle ? 0 : 180;
            g_angle = g_lastangle;
            cout << "angl " << g_angle << "\n";
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



void on_key( unsigned char c, int x, int y )
{
    static size_t stored_w = DEFAULT_WIDTH;
    static size_t stored_h = ( DEFAULT_WIDTH * 9 ) / 16;

    switch( c ) {
        case 27:
            glutLeaveMainLoop();
            break;

        case 'f':
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
            break;

        case 'n':
            g_fische->nervous_mode = g_fische->nervous_mode ? 0 : 1;
    }
}



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
            usleep( delay );
            last = now + delay;
        }
        else
            last = now;
    }

    glutPostRedisplay();
}



void read_func()
{
    char buf[4096];

    for( ;; ) {
        cin.read( buf, 4096 );
        if( g_run )
            fische_audiodata( g_fische, buf, 4096 );
        else
            break;
    }
}



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

void parse_commandline( int& argc, char**& argv )
{
    namespace po = boost::program_options;
    po::options_description desc( "fische options" );
    desc.add_options()
        ( "help,h", "this help message" )
        ( "detail,d", po::value<int>( &g_detail )->default_value( 1 ), "level of detail [0..3]" )
        ( "nervous,n", po::value<bool>( &g_nervous_start )->default_value( false )->implicit_value( true ), "start in nervous mode (more mode changes)" );
    ;

    po::variables_map vm;
    po::store( po::parse_command_line( argc, argv, desc ), vm );
    po::notify( vm );

    if( vm.count( "help" ) ) {
        cout << desc << "\n";
        exit( EXIT_SUCCESS );
    }
}

int main( int argc, char** argv )
{
    glut_gl_init( argc, argv );
    parse_commandline( argc, argv );

    fische_init();
    texture_init();

    boost::thread reader_thread( read_func );
    glutMainLoop();

    g_run = false;

    fische_free( g_fische );
}
