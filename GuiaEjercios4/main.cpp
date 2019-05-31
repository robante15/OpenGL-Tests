#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
//#include "steve.h"

void suelo();

void steveHead();

void steveTorso();

void steveBrazo();

void stevePierna();

//Definimos variables
double rotate_y = 0;
double rotate_x = 0;
double rotate_z = 0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 0.1f;
GLfloat PosPersoX = 0.0f, PosPersoY = 0.0f, PosPersoZ = 0.0f;

GLuint ListHead, ListTorso, ListBrazo, ListPierna, ListSuelo;

//Arreglo de imagenes
GLuint texture[0];


//parametros de la fuente de luz
GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {1.0f, 1.0f, 1.0f, 0.0f};

void init(void) {
    //Carga la textura
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.046f, 0.714f, 0.945f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TEST
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    //activa la luz
    glEnable(GL_LIGHT0);

    ListHead = glGenLists(1);
    glNewList(ListHead, GL_COMPILE);
    steveHead();
    glEndList();

    ListTorso = glGenLists(1);
    glNewList(ListTorso, GL_COMPILE);
    steveTorso();
    glEndList();

    ListBrazo = glGenLists(1);
    glNewList(ListBrazo, GL_COMPILE);
    steveBrazo();
    glEndList();

    ListPierna = glGenLists(1);
    glNewList(ListPierna, GL_COMPILE);
    stevePierna();
    glEndList();

    ListSuelo = glGenLists(1);
    glNewList(ListSuelo, GL_COMPILE);
    suelo();
    glEndList();
}

void suelo() {
    texture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "suelo.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-400.0f, 00.0f, -400.0f);
    glTexCoord2f(32.0f, 0.0f);
    glVertex3f(400.0f, 00.0f, -400.0f);
    glTexCoord2f(32.0f, 32.0f);
    glVertex3f(400.0f, 00.0f, 400.0f);
    glTexCoord2f(0.0f, 32.0f);
    glVertex3f(-400.0f, 00.0f, 400.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}


void steveHead() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "head/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, 5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, 5.0f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, -5.0f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, 5.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, 5.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, -5.0f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, -5.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, -5.0f, -5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 5.0f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, -5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, -5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 5.0f, 5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 5.0f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, -5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 5.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, 5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void steveTorso() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "torso/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, 2.5f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, -2.5f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 7.5, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, -2.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, 2.5f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(5.0f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(5.0f, -7.5f, 2.5f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-5.0f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void steveBrazo() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "arm/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void stevePierna() {
//Definicion de texturas
    texture[0] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/front.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[1] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/back.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[2] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/top.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    texture[3] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/button.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[4] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/right.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    texture[5] = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
            (
                    "leg/left.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glEnd();

    // parte de Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glEnd();
    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glEnd();

    // lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2.5f, -7.5f, 2.5f);
    glEnd();

    // Lado Izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-2.5f, -7.5f, 2.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.5f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Transladar el cubo a las siguientes coordenadas
    glTranslatef(0.0f, 0.0f, -5.5f);

    // Rotar en el eje X,Y y Z
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    glTranslatef(X, Y, Z);    // Transladar en los 3 ejes
    // Otras transformaciones
    glScalef(scale, scale, scale);

    glTranslatef(0.0, -22.5, 0.0);
    glCallList(ListSuelo);
    glTranslatef(0.0, 22.5, 0.0);

    //PERSONAJE

    glTranslatef(PosPersoX, PosPersoY, PosPersoZ);

    glCallList(ListTorso);
    glTranslatef(0.0, 12.5, 0.0);
    glCallList(ListHead);
    glTranslatef(7.5, -12.5, 0.0);
    glCallList(ListBrazo);
    glTranslatef(-15.0, 0.0, 0.0);
    glCallList(ListBrazo);
    glTranslatef(5, -15.0, 0.0);
    glCallList(ListPierna);
    glTranslatef(5, 0.0, 0.0f);
    glCallList(ListPierna);




    //glFlush();
    glutSwapBuffers();

}

// Función para controlar teclas especiales
void specialKeys(int key, int x, int y) {

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_UP)
        rotate_x += 7;
        //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
        //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z += 7;
        //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;

    //  Solicitar actualización de visualización
    glutPostRedisplay();

}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float) w / (float) h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y) {
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    switch (key) {
        case 'w':
            PosPersoZ -= 2.5f;
            break;
        case 'a':
            PosPersoX -= 2.5f;
            break;
        case 's' :
            PosPersoZ += 2.5f;
            break;
        case 'd' :
            PosPersoX += 2.5f;
            break;
        case '8' :
            Y -= 0.1f;
            break;
        case '5' :
            Y += 0.1f;
            break;
        case '4':
            X -=0.1f;
            break;
        case '6':
            X +=0.1f;
            break;
        case '7':
            rotate_y += 7;
            break;
        case '9':
            rotate_y -= 7;
            break;
        case '-':
            Z -= 0.1f;
            break;
        case '+':
            Z += 0.1f;
            break;
        case 'q':
            exit(0);            // exit
    }
    glutPostRedisplay();
}


void update(int value) {
    rotate_y += 5;
    rotate_x += 6;
    rotate_z += 7;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[]) {

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc, argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    // Crear ventana
    glutCreateWindow("Cubo con texturas");
    init();
    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);

    // Funciones de retrollamada
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    //glutTimerFunc(30, update, 0);
    // Pasar el control de eventos a GLUT
    glutMainLoop();

    // Regresar al sistema operativo
    return 0;

}
