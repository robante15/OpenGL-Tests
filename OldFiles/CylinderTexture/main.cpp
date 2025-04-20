#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <SOIL/SOIL.h>

GLuint gramitaTexture[0];

GLfloat X = 0.0f; // Translate screen to x direction (left or right)
GLfloat Y = 0.0f; // Translate screen to y direction (up or down)
GLfloat Z = 0.0f; // Translate screen to z direction (zoom in or out)
GLfloat step = 6;

void cylinder()
{
    const double PI = 3.14159;

    /* top triangle */
    double i, resolution  = 0.1;
    double height = 2;
    double radius = 0.75;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f( 0.5, 0.5 );
        glVertex3f(0, height, 0);  /* center */
        for (i = 2 * PI; i >= 0; i -= resolution)

        {
            glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
            glVertex3f(radius * cos(i), height, radius * sin(i));
        }
        /* close the loop back to 0 degrees */
        glTexCoord2f( 0.5, 0.5 );
        glVertex3f(radius, height, 0);
    glEnd();

    /* bottom triangle: note: for is in reverse order */
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f( 0.5, 0.5 );
        glVertex3f(0, 0, 0);  /* center */
        for (i = 0; i <= 2 * PI; i += resolution)
        {
            glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
            glVertex3f(radius * cos(i), 0, radius * sin(i));
        }
    glEnd();

    /* middle tube */
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i <= 2 * PI; i += resolution)
        {
            const float tc = ( i / (float)( 2 * PI ) );
            glTexCoord2f( tc, 0.0 );
            glVertex3f(radius * cos(i), 0, radius * sin(i));
            glTexCoord2f( tc, 1.0 );
            glVertex3f(radius * cos(i), height, radius * sin(i));
        }
        /* close the loop back to zero degrees */
        glTexCoord2f( 0.0, 0.0 );
        glVertex3f(radius, 0, 0);
        glTexCoord2f( 0.0, 1.0 );
        glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();
}

GLuint tex;
void init()
{
    unsigned char data[] =
    {
        128, 128, 128, 255,
        255, 0, 0, 255,
        0, 255, 0, 255,
        0, 0, 255, 255,
    };

	gramitaTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "cesped.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    //glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, gramitaTexture[0] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    //glTexImage2D( GL_TEXTURE_2D, 0,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
}

/*void timer( int value )
{
    angle += 6;
    glutPostRedisplay();
    glutTimerFunc( 16, timer, 0 );
}*/

void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1.0, 0.1, 100.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 0, -5 );

    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );

    glRotatef(Y, 1, 0, 0); //Rota en el eje Z
    glRotatef(X, 0, 1, 0); //Rota en el eje Z
	glRotatef(Z, 0, 0, 1); //Rota en el eje Z
    
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, gramitaTexture[0] );
    cylinder();

    glutSwapBuffers();
}

void specialKey(int key, int x, int y) {

// The keys below are using the gluLookAt() function for navigation
// Check which key is pressed

    switch (key) {
        case GLUT_KEY_LEFT : // Rotate on x axis
            X -= step;
			//glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT : // Rotate on x axis (opposite)
            X += step;
            break;
        case GLUT_KEY_UP : // Rotate on y axis
            Y += step;
            break;
        case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
            Y -= step;
            break;
        case GLUT_KEY_PAGE_UP: // Rotate on z axis
            Z -= step;
            break;
        case GLUT_KEY_PAGE_DOWN:// Rotate on z axis (opposite)
            Z += step;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redraw the scene
}

int main(int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 600, 600 );
    glutCreateWindow( "GLUT" );
    init();
    glutDisplayFunc( display );
    glutSpecialFunc(specialKey);
    //glutTimerFunc( 0, timer, 0 );
    glutMainLoop();
    return 0;
}
