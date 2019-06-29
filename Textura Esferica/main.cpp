#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

//GLuint tex;
GLUquadric* sphere;

GLuint gramitaTexture[0];

GLfloat X = 0.0f; // Translate screen to x direction (left or right)
GLfloat Y = 0.0f; // Translate screen to y direction (up or down)
GLfloat Z = 0.0f; // Translate screen to z direction (zoom in or out)
GLfloat step = 6;

void make_tex(void)
{
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
	for (int x = 0; x < 255; x++) {
	    unsigned char *p = data[y][x];
	    p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
	}
    }
    
    gramitaTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "balon.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    
    //glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, gramitaTexture[0]);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}



void draw(void)
{
    glClearColor(0.5, 0.5, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0,-2.0);
    
    glRotatef(Y, 1, 0, 0); //Rota en el eje Z
    glRotatef(X, 0, 1, 0); //Rota en el eje Z
	glRotatef(Z, 0, 0, 1); //Rota en el eje Z

    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, gramitaTexture[0]);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.0, 32, 16);

    glutSwapBuffers();
}

void resize(int w, int h)
{
    if (!h)
	h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0*w/h, 0.1, 100.0);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    make_tex();
    sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
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
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 512);

    glutCreateWindow("Test");


    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
	glutSpecialFunc(specialKey);
    init();

    glutMainLoop();
}
