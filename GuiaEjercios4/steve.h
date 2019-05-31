#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h> 

//Arreglo de imagenes
GLuint texture[0];

void steveHead(){
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
	
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, -5.0f, 5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 5.0f, 5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 5.0f);
	glEnd();
	
	// parte de Atras
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -5.0f, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, 5.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, 5.0f, -5.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -5.0f, -5.0f);
	glEnd();
	// Arriba
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, -5.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 5.0f, 5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, 5.0f, 5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 5.0f, -5.0f);
	glEnd();
	
	// Abajo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, -5.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, -5.0f, -5.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -5.0f, 5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 5.0f);
	glEnd();
	
	// lado Derecho
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, -5.0f, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 5.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, 5.0f, 5.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -5.0f, 5.0f);
	glEnd();
	
	// Lado Izquierdo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, -5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, -5.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void steveTorso(){
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
	
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -7.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, -7.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 7.5f, 2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 7.5f, 2.5f);
	glEnd();
	
	// parte de Atras
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -7.5f, -2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, 7.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, 7.5f, -2.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -7.5f, -2.5f);
	glEnd();
	// Arriba
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_POLYGON);
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 7.5, -2.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 7.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, 7.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 7.5f, -2.5f);
	glEnd();
	
	// Abajo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, -7.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, -7.5f, -2.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -7.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -7.5f, 2.5f);
	glEnd();
	
	// lado Derecho
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_POLYGON);
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, -7.5f, -2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f, 7.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, 7.5f, 2.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -7.5f, 2.5f);
	glEnd();
	
	// Lado Izquierdo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -7.5f, -2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -7.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, 7.5f, 2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 7.5f, -2.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
