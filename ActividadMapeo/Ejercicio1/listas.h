#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <SOIL/SOIL.h>

// for SOIL
GLuint gramitaTexture[0];
GLuint ladrilloTexture[0];


GLuint gramita, ladrillos;

static void suelo(){
    gramita = glGenLists(1);
    glNewList (gramita, GL_COMPILE);


    gramitaTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "cesped.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gramitaTexture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-200.0f, -200.0f, 000.0f);
    glTexCoord2f(8.0f, 0.0f); glVertex3f( 200.0f, -200.0f, 000.0f);
    glTexCoord2f(8.0f, 8.0f); glVertex3f( 200.0f, 200.0f, 000.0f);
    glTexCoord2f(0.0f, 8.0f); glVertex3f(-200.0f, 200.0f, 000.0f);
    glEnd();

    glPopMatrix();
    glFlush();
    glEndList ();
    glutSwapBuffers();
}

static void pared(){
    ladrillos = glGenLists(3);
    glNewList (ladrillos, GL_COMPILE);

    ladrilloTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "pared.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ladrilloTexture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -25.0f, 25.0f, 0.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f( 25.0f, 25.0f, 0.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f( 0.0f, 0.0f, 75.0f);
    //glTexCoord2f(0.0f, 2.0f); glVertex3f( -25.0f, 0.0f, 75.0f);
    glEnd();

    glEndList ();
}