#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <SOIL/SOIL.h>

void soil();

// for SOIL
GLuint gramitaTexture[0];
GLuint ladrilloTexture[0];
GLuint concretoTexture[0];
GLuint windowsTexture[0];
GLuint pelotaTexture[0];


GLuint gramita, ladrillos, concreto, windows, arcwindows, door, planet;


void planeta() {
    glNewList(planet, GL_COMPILE);
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //textura
    glShadeModel(GL_SMOOTH); //Bordes

    pelotaTexture[1] = SOIL_load_OGL_texture //Llamamos a la imagen
            (
                    "balon.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
    glEnable(GL_TEXTURE_2D);

    //usamos la autogeneración de coordenadas
    GLfloat plano_s[4] = {0.5, 0, 0, 0}; // X
    GLfloat plano_t[4] = {0, 2, 0, 0}; // Y
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, plano_s);
    glEnable(GL_TEXTURE_GEN_S);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, plano_t);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_T);

    //glutSolidTeapot(30);
    glutSolidSphere(40.5f, 45.0, 45.0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_T);

    glPopMatrix();
    glFlush();
    glEndList();

}

static void acera(){
    concreto = glGenLists(2);
    glNewList (concreto, GL_COMPILE);


    concretoTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "concreto.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, concretoTexture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, -20.0f, 000.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 20.0f, -20.0f, 000.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 20.0f, 20.0f, 000.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0f, 20.0f, 000.0f);
    glEnd();

    glEndList ();
}

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

    glEndList ();
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
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -25.0f, 0.0f, 0.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f( 25.0f, 0.0f, 0.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f( 25.0f, 0.0f, 75.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f( -25.0f, 0.0f, 75.0f);
    glEnd();

    glEndList ();
}

static void ventanas(){
    windows = glGenLists(4);
    glNewList (windows, GL_COMPILE);

    windowsTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "windows.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, windowsTexture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -9.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 9.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 9.0f, 0.0f, 37.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -9.0f, 0.0f, 37.0f);
    glEnd();

    glEndList ();
}

static void Arcventanas(){
    arcwindows = glGenLists(4);
    glNewList (arcwindows, GL_COMPILE);

    windowsTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "arcwindow.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, windowsTexture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -10.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f, 0.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -10.0f, 0.0f, 50.0f);
    glEnd();

    glEndList ();
}

static void puerta(){
    door = glGenLists(4);
    glNewList (door, GL_COMPILE);

    windowsTexture[0] = SOIL_load_OGL_texture // cargamos la imagen
            (
                    "door.bmp",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, windowsTexture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -7.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 7.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 7.0f, 0.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -7.0f, 0.0f, 50.0f);
    glEnd();

    glEndList ();
}


static void generadorObjetos(GLfloat verticesArray[][3], GLint faces[][3], int fFil, GLfloat mat_ambient[], GLfloat mat_diffuse[], GLfloat mat_specular[], GLfloat shine[], GLfloat mat_emission[]) {
    glBegin(GL_TRIANGLE_FAN);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    for (int filas = 0; filas < fFil; ++filas) {
        GLfloat vertex[3];
        for (int columnas = 0; columnas < 4; ++columnas) {
            int vfila = faces[filas][columnas] - 1;
            //std::cout << vfila+1 << std::endl;
            std::cout << verticesArray[vfila][0] << verticesArray[vfila][1] << verticesArray[vfila][2] << std::endl;
            vertex[0] = verticesArray[vfila][0];
            vertex[1] = verticesArray[vfila][1];
            vertex[2] = verticesArray[vfila][2];
            glVertex3fv(vertex);
        }
        //std::cout << std::endl << std::endl;
        //glVertex3fv(vertex);
    }
    glEnd();
}

GLfloat techoVertices[57][3] = {
        {0.987193,1.623829,0.007324},
        {0.062193,1.086329,0.407324},
        {0.987193,0.548829,0.007324},
        {-0.862807,1.623829,0.007324},
        {-0.862807,1.623829,0.007324},
        {0.062193,-0.988671,0.407324},
        {0.062193,1.086329,0.407324},
        {-0.862807,-1.526171,0.007324},
        {-0.787807,-1.451171,0.007324},
        {-0.862807,-1.526171,0.007324},
        {-0.862807,1.623829,0.007324},
        {0.987193,-1.526171,0.007324},
        {0.912193,-1.451171,0.007324},
        {0.987193,-0.451171,0.007324},
        {0.912193,-0.526171,0.007324},
        {0.912193,-1.451171,0.007324},
        {-0.787807,-0.526171,0.007324},
        {0.912193,-0.526171,0.007324},
        {-0.787807,-1.451171,0.007324},
        {-0.787807,-0.526171,0.007324},
        {-0.787807,0.623829,0.007324},
        {-0.787807,1.548829,0.007324},
        {0.912193,1.548829,0.007324},
        {0.987193,1.623829,0.007324},
        {0.912193,0.623829,0.007324},
        {0.987193,0.548829,0.007324},
        {0.412193,0.623829,0.007324},
        {0.587193,0.548829,0.007324},
        {0.512193,0.223829,0.007324},
        {0.412193,0.223829,0.007324},
        {0.512193,0.223829,0.007324},
        {0.512193,-0.126171,0.007324},
        {0.412193,0.223829,0.007324},
        {0.512193,-0.126171,0.007324},
        {0.587193,-0.451171,0.007324},
        {0.412193,-0.126171,0.007324},
        {0.412193,-0.526171,0.007324},
        {0.587193,-0.451171,0.007324},
        {0.062193,-0.988671,0.407324},
        {0.987193,-0.451171,0.007324},
        {0.587193,-0.451171,0.007324},
        {0.062193,1.086329,0.407324},
        {0.062193,-0.988671,0.407324},
        {0.587193,0.548829,0.007324},
        {0.062193,1.086329,0.407324},
        {0.587193,0.548829,0.007324},
        {0.987193,0.548829,0.007324},
        {0.987193,-0.451171,0.007324},
        {0.987193,-1.526171,0.007324},
        {-0.862807,-1.526171,0.007324},
        {0.412193,-0.526171,0.007324},
        {-0.787807,0.623829,0.007324},
        {0.412193,-0.126171,0.007324},
        {0.412193,0.623829,0.007324},
        {-0.787807,1.548829,0.007324},
        {0.912193,0.623829,0.007324},
        {0.912193,1.548829,0.007324}
};

GLint techoFaces[44][3] = {
        {1,2,3},
        {1,4,2},
        {5,6,7},
        {6,5,8},
        {38,39,40},
        {41,42,43},
        {42,41,44},
        {45,46,47},
        {48,6,49},
        {6,50,49},
        {9,10,11},
        {10,9,12},
        {13,12,9},
        {12,13,14},
        {14,13,15},
        {9,11,20},
        {20,11,21},
        {21,11,22},
        {22,11,23},
        {24,23,11},
        {24,25,23},
        {26,25,24},
        {26,27,25},
        {28,27,26},
        {29,27,28},
        {27,29,30},
        {28,34,29},
        {35,34,28},
        {35,36,34},
        {35,37,36},
        {37,35,15},
        {14,15,35},
        {16,17,18},
        {17,16,19},
        {31,32,33},
        {18,17,51},
        {52,51,17},
        {51,52,53},
        {53,52,32},
        {32,52,33},
        {33,52,54},
        {54,52,55},
        {54,55,56},
        {56,55,57}
};

GLfloat amb_GrisClaro[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat dif_GrisClaro[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat spec_GrisClaro[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shine_GrisClaro[] = {100.0f};
GLfloat emi_nada[] = {0.0,0.0,0.0,0.0};