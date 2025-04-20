/*
 * Actividad de Animación
 * Estudiantes:
 * Ervin Fernando Amaya Villalta - AV16023
 * Roberto Antonio Ortiz Acevedo - OA14002
 * */

#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_mixer.h"

#define RUTA_AUDIO "resources/audio/sweden.wav"

void suelo();

void ruedas();

void MainVehicle();


// funcion para cargar audio
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variables para audio
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play


int frameNumber; // Numero de frames
int animating = 0;      // 0 sin animación
// Se cambia con la llamada a las funciones startAnimation() and pauseAnimation()

//Definimos variables
double rotateWorld_y = 0;
double rotateWorld_x = 15;
double rotateWorld_z = 0;

GLfloat WorldX = 0.0f;
GLfloat WorldY = -1.0f;
GLfloat WorldZ = -1.5f;
GLfloat scale = 0.1f;

//Parametros Globales del personaje
GLfloat step = 1.75;
GLfloat RotPersoAngle = 180.0f, RotPersoX = 0.0f, RotPersoY = 1.0f, RotPersoZ = 0.0f;
GLfloat PosPersoX = 0.0f, PosPersoY = 0.0f, PosPersoZ = 0.0f;

//Control de las ruedas
GLfloat RotAngleWheel = 0, RotWheelX = 0, RotWheelY = 0, RotWheelZ = 0;

//Parametros

GLuint ListWheel, ListVehicle, ListSuelo;

//Arreglo de imagenes
GLuint texture[0];


//parametros de la fuente de luz
GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {1.0f, 1.0f, 1.0f, 0.0f};

void text() {
    char text[40];
    sprintf(text, "Rotation:%.0f", RotAngleWheel);
    glColor3f(0, 0, 0);
    glRasterPos3f(-30, 15, scale);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void pauseAnimation() {
    // Llamamo a la función para detener la animación
    animating = 0;
}

void updateFrame() {
    // En esta funcion agregamos el codigo que hara la secuencia de cada escena como si fuera un fotograma

    //Hacemos que la tetera gire
    for (int i = 3; i <= 100; i++) {
        RotAngleWheel += 0.2;
        RotWheelY = 1;
        PosPersoZ += 0.02;
    }
    //Verificamos el numero de frames para detener animación
    if (frameNumber == 100) {
        pauseAnimation();
        frameNumber = 0;
    }
    //Almacenamos el numero de frames
    frameNumber++;
    printf("Numero de Frame: %d \n", frameNumber);
}

void timerFunction(int timerID) {
    // Invocamos la funcion para controlar el tiempo de la ejecucion de funciones
    if (animating) {
        updateFrame();
        glutTimerFunc(30, timerFunction, 0);
        glutPostRedisplay();
    }
}

void startAnimation() {
    // llamamos la función para iniciar la animación
    if (!animating) {
        animating = 1;
        glutTimerFunc(30, timerFunction, 1);
    }
}


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

    ListWheel = glGenLists(1);
    glNewList(ListWheel, GL_COMPILE);
    ruedas();
    glEndList();

    ListVehicle = glGenLists(1);
    glNewList(ListVehicle, GL_COMPILE);
    MainVehicle();
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

void cylinder() {
    const double PI = 3.14159;

    /* top triangle */
    double i, resolution = 0.1;
    double height = 2;
    double radius = 0.75;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= 0; i -= resolution) {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f(0.5, 0.5);
    glVertex3f(radius, height, 0);
    glEnd();

    /* bottom triangle: note: for is in reverse order */
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 0, 0);  /* center */
    for (i = 0; i <= 2 * PI; i += resolution) {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
    }
    glEnd();

    /* middle tube */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= 2 * PI; i += resolution) {
        const float tc = (i / (float) (2 * PI));
        glTexCoord2f(tc, 0.0);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
        glTexCoord2f(tc, 1.0);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to zero degrees */
    glTexCoord2f(0.0, 0.0);
    glVertex3f(radius, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();
}

void ruedas() {
    texture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "rueda.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    //glGenTextures( 1, &tex );
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    const double PI = 3.14159;

    /* top triangle */
    double i, resolution = 0.1;
    double height = 23.5;
    double radius = 7;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= 0; i -= resolution) {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f(0.5, 0.5);
    glVertex3f(radius, height, 0);
    glEnd();

    /* bottom triangle: note: for is in reverse order */
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(0, 0, 0);  /* center */
    for (i = 0; i <= 2 * PI; i += resolution) {
        glTexCoord2f(0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
    }
    glEnd();

    /* middle tube */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= 2 * PI; i += resolution) {
        const float tc = (i / (float) (2 * PI));
        glTexCoord2f(tc, 0.0);
        glVertex3f(radius * cos(i), 0, radius * sin(i));
        glTexCoord2f(tc, 1.0);
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to zero degrees */
    glTexCoord2f(0.0, 0.0);
    glVertex3f(radius, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();
}

void MainVehicle() {
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

    // Atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.0f, -3.5f, 12.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(25.0f, -3.5f, 12.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(25.0f, 3.5f, 12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.0f, 3.5f, 12.5f);
    glEnd();

    //Soporte techo atras
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(8.0f, 19.5f, 12.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(7.0f, 19.5f, 12.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(9.0f, 3.5f, 12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10.0f, 3.5f, 12.5f);
    glEnd();

    //Soporte techo adelante
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(8.0f, 19.5f, -12.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(7.0f, 19.5f, -12.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(9.0f, 3.5f, -12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10.0f, 3.5f, -12.5f);
    glEnd();

    // Frente
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-35.0f, -3.5f, -12.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-35.0f, 3.5f, -12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(25.0f, 3.5f, -12.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(25.0f, -3.5f, -12.5f);
    glEnd();

    // Arriba
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-25.0f, 20.5f, -12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(15.0f, 17.5f, -12.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(15.0f, 17.5f, 12.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-25.0f, 20.5f, 12.5f);
    glEnd();

    // Abajo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-10.0f, -5.5f, -12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10.0f, -5.5f, -12.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10.0f, -5.5f, 12.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-10.0f, -5.5f, 12.5f);
    glEnd();

    // lado izquierdo
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_POLYGON);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10.0f, -5.5f, -12.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(15.0f, 5.5f, -12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(15.0f, 5.5f, 12.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10.0f, -5.5f, 12.5f);
    glEnd();

    // Lado Derecho
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_POLYGON);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-20.0f, -3.5f, -12.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-20.0f, -3.5f, 12.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-25.0f, 3.5f, 12.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-25.0f, 3.5f, -12.5f);
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

    // Rotar la camara en el eje X,Y y Z
    glRotatef(rotateWorld_x, 1.0, 0.0, 0.0);
    glRotatef(rotateWorld_y, 0.0, 1.0, 0.0);
    glRotatef(rotateWorld_z, 0.0, 0.0, 1.0);
    glTranslatef(WorldX, WorldY, WorldZ);    // Transladar la camara en los 3 ejes
    // Otras transformaciones
    glScalef(scale, scale, scale); //Configurar la escala de la escena

    glTranslatef(0.0, -22.5, 0.0);
    glCallList(ListSuelo);
    glTranslatef(0.0, 22.5, 0.0);

    //PERSONAJE
    glRotatef(RotPersoAngle, RotPersoX, RotPersoY, RotPersoZ); //Coordina la rotación del personaje
    glTranslatef(PosPersoX, PosPersoY, PosPersoZ); //Para coordinar la posición del personaje

    //Chasis
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, -10, 0);
    glCallList(ListVehicle);
    glTranslatef(0, 10, 0);

    //Ruedas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glRotatef(90, 1, 0, 0);
    glTranslatef(-35.0, -11.5, 13.0);
    glRotatef(RotAngleWheel, RotWheelX, RotWheelY, RotWheelZ);
    glCallList(ListWheel);
    glRotatef(RotAngleWheel, -1 * RotWheelX, -1 * RotWheelY, -1 * RotWheelZ);
    glTranslatef(60, 0, 0);
    glRotatef(RotAngleWheel, RotWheelX, RotWheelY, RotWheelZ);
    glCallList(ListWheel);
    glRotatef(RotAngleWheel, -1 * RotWheelX, -1 * RotWheelY, -1 * RotWheelZ);
    glRotatef(-90, 0, 1, 0);

    text();
    //glFlush();
    glutSwapBuffers();

}

// Función para controlar teclas especiales
void specialKeys(int key, int x, int y) {

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_UP)
        rotateWorld_x += 5;

        //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotateWorld_x -= 5;
        //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F2)
        rotateWorld_z += 7;
        //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotateWorld_z -= 7;

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
    GLfloat temp;
    switch (key) {
        case ' ':
            if (animating) {
                pauseAnimation();
                SDL_PauseAudio(1);
            } else {
                startAnimation();
                SDL_PauseAudio(0);
            }
        case 'w':
            if (RotPersoAngle != 180) {

                //Corrige las coordenadas cuando proviene de 270
                if (RotPersoAngle == 270) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                //Corrige las coordenadas cuando proviene de 0
                if (RotPersoAngle == 90) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                RotPersoAngle = 180;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            RotAngleWheel += 15;
            RotWheelY = 1;
            PosPersoZ += step;
            break;

        case 'a':
            if (RotPersoAngle != 270) {

                if (RotPersoAngle == 180) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                if (RotPersoAngle == 0) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                RotPersoAngle = 270;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            RotAngleWheel += 15;
            RotWheelY = 1;
            PosPersoZ += step;
            break;

        case 's' :

            if (RotPersoAngle != 0) {

                //Corrige las coordenadas cuando proviene de 270
                if (RotPersoAngle == 270) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                //Corrige las coordenadas cuando proviene de 0
                if (RotPersoAngle == 90) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                RotPersoAngle = 0;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            RotAngleWheel += 15;
            RotWheelY = 1;
            PosPersoZ += step;
            break;

        case 'd' :
            if (RotPersoAngle != 90) {

                if (RotPersoAngle == 180) {
                    temp = PosPersoX;
                    PosPersoX = -1 * PosPersoZ;
                    PosPersoZ = temp;
                }

                if (RotPersoAngle == 0) {
                    temp = PosPersoX;
                    PosPersoX = PosPersoZ;
                    PosPersoZ = -1 * temp;
                }

                RotPersoAngle = 90;
                RotPersoY = 1;
                PosPersoX *= -1;
                PosPersoZ *= -1;
            }
            RotAngleWheel += 15;
            RotWheelY = 1;
            PosPersoZ += step;
            break;
        case '8' :
            WorldY -= 0.1f;
            break;
        case '5' :
            WorldY += 0.1f;
            break;
        case '4':
            WorldX -= 0.1f;
            break;
        case '6':
            WorldX += 0.1f;
            break;
        case '7':
            rotateWorld_y += 5;
            break;
        case '9':
            rotateWorld_y -= 5;
            break;
        case '-':
            WorldZ -= 0.1f;
            break;
        case '+':
            WorldZ += 0.1f;
            break;
        case 'r':
            if (step == 1.75) {
                step = 5.75;
            } else {
                step = 1.75;
            }
            break;
        case 'q':
            exit(0);            // exit
    }
    glutPostRedisplay();
}


void update(int value) {
    rotateWorld_y += 5;
    rotateWorld_x += 6;
    rotateWorld_z += 7;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char *argv[]) {

    /*if (SDL_Init(SDL_INIT_AUDIO) < 0) exit(1);
    // Setup audio mode
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *mus;  // Background Music

    mus = Mix_LoadMUS(RUTA_AUDIO);
    Mix_PlayMusic(mus, 1); //Music loop=1*/

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

    //CODIGO DEL AUDIO
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        return 1;

    // Variables locales
    static Uint32 wav_length; // Longitud de nuestra muestra
    static Uint8 *wav_buffer; // Buffer que contiene nuestro archivo de audio
    static SDL_AudioSpec wav_spec; // Las especificaciones de nuestra pieza de música

    /* Cargar el WAV */
    // Las especificaciones, la longitud y el búfer de nuestro wav se llenan
    if( SDL_LoadWAV(RUTA_AUDIO, &wav_spec, &wav_buffer, &wav_length) == NULL )
    {
        return 1;
    }
    // Establecer la función de devolución de llamada
    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;

    // Establecer nuestras variables estáticas globales
    audio_pos = wav_buffer; // Copia el buffer de sonido
    audio_len = wav_length; // Copia la longitud del archivo

    /*Abrir el dispositivo de audio */
    if ( SDL_OpenAudio(&wav_spec, NULL) < 0 )
    {
        fprintf(stderr, "No se pudo abrir el audio: %s\n", SDL_GetError());
        exit(-1);
    }

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


//Función de devolución de llamada de audio donde se recoren los valores del bufer
void my_audio_callback(void *userdata, Uint8 *stream, int len)
{

    if (audio_len ==0)
        return;

    len = ( len > audio_len ? audio_len : len );

    SDL_memcpy (stream, audio_pos, len); // Simplemente copie desde un buffer en el otro
    //SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME / 2); // Mezclar de un buffer a otro

    audio_pos += len;
    audio_len -= len;
}
