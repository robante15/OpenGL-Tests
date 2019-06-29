#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h> // freeglut instead of glut because glut is DEPRECATED
#include "listas.h"

using namespace std;

GLfloat ortho = 100;
GLfloat step = ortho / 100;
GLfloat defaultRotX = -45.0f, defaultRotZ = -135.0f;


GLfloat X = 0.0f; // Translate screen to x direction (left or right)
GLfloat Y = 0.0f; // Translate screen to y direction (up or down)
GLfloat Z = 0.0f; // Translate screen to z direction (zoom in or out)
GLfloat rotX = defaultRotX; // Rotate screen on x axis
GLfloat rotY = 0.0f; // Rotate screen on y axis
GLfloat rotZ = defaultRotZ; // Rotate screen on z axis
GLfloat rotLx = 0.0f; // Translate screen by using the glulookAt function (left or right)
GLfloat rotLy = 0.0f; // Translate screen by using the glulookAt function (up or down)
GLfloat rotLz = 0.0f; // Translate screen by using the glulookAt function (zoom in or out)





// window title
#define WINDOW_TITLE_PREFIX "3D"

// default window's size, but these settings are override later
int
        CurrentWidth = 800,
        CurrentHeight = 600,
        WindowHandle = 0;

// frame-counter var
unsigned FrameCount = 0;

// function prototypes
void Initialize(int, char *[]);

void InitWindow(int, char *[]);

void ResizeFunction(int, int);

void RenderFunction();

void TimerFunction(int);

void IdleFunction();

void display();

void xyz();

void keyboard(unsigned char, int, int);

void specialKey(int, int, int);

void translateRotate();

// entry point
int main(int argc, char *argv[]) {

    Initialize(argc, argv);

    glutMainLoop();

    exit(EXIT_SUCCESS);
}

// all drawings here
void display() {


    translateRotate(); // put this function before each drawing you make.
    xyz();


    translateRotate(); // put this function before each drawing you make.

    //suelo();
    //glCallList(gramita);


    pared();
    glCallList(ladrillos);
    glRotatef(90,0,0,1);
    glCallList(ladrillos);
    glRotatef(90,0,0,1);
    glCallList(ladrillos);
    glRotatef(90,0,0,1);
    glCallList(ladrillos);
}


void xyz() {

    // glRotatef and glTranslatef

    cout << "rot(" << rotX << ", " << rotY << ", " << rotZ << ")" << endl;
    cout << "trans(" << X << ", " << Y << ", " << Z << ")" << endl;

    // up or down or zoom in zoom out
    // Draw the positive side of the lines x,y,z
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0); // Green for x axis
    glVertex3f(0, 0, 0);
    glVertex3f(10 * ortho, 0, 0);
    glColor3f(1.0, 0.0, 0.0); // Red for y axis
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10 * ortho, 0);
    glColor3f(0.0, 0.0, 1.0); // Blue for z axis
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10 * ortho);

    glEnd();

    // Dotted lines for the negative sides of x,y,z
    glEnable(GL_LINE_STIPPLE);    // Enable line stipple to use a
    // dotted pattern for the lines
    glLineStipple(1, 0x0101);    // Dotted stipple pattern for the lines
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);    // Green for x axis
    glVertex3f(-10 * ortho, 0, 0);
    glVertex3f(0, 0, 0);
    glColor3f(1.0, 0.0, 0.0);    // Red for y axis
    glVertex3f(0, 0, 0);
    glVertex3f(0, -10 * ortho, 0);
    glColor3f(0.0, 0.0, 1.0);    // Blue for z axis
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -10 * ortho);

    glEnd();

    glDisable(GL_LINE_STIPPLE);    // Disable the line stipple
    glPopMatrix();        // Don't forget to pop the Matrix
}

void Initialize(int argc, char *argv[]) {

    GLenum GlewInitResult;

    InitWindow(argc, argv);

    GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult) {
        fprintf(
                stderr,
                "ERROR: %s\n",
                glewGetErrorString(GlewInitResult)
        );
        exit(EXIT_FAILURE);
    }

    // print system's capability
    fprintf(
            stdout,
            "INFO: OpenGL Version: %s\n",
            glGetString(GL_VERSION)
    );

    // OpenGL clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // red
    //glClearColor(0.0f, 1.0f, 0.0f, 0.0f); // green
    //glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // blue
    //glClearColor(1.0f, 0.0f, 1.0f, 0.0f); // purple
    //glClearColor(0.0f, 0.0f, 0.5f, 0.0f); // dark blue

    // flags to enable materials and lighting
    /*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
}

void InitWindow(int argc, char *argv[]) {
    glutInit(&argc, argv);

    // set OpenGL's major and minor versions
    glutInitContextVersion(1, 0);

    // Only not deprecated methods allowed
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    // set behavior on window close by user
    glutSetOption(
            GLUT_ACTION_ON_WINDOW_CLOSE,
            GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    // settings initial values for the window, this override deafult values on top
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

    // way to render frames
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // Setup display mode to
    glShadeModel(GL_FLAT); // Set the shading model to GL_FLAT
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(0.5f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // if windowHandle is greater than 0, then no errors on creating the window
    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if (WindowHandle < 1) {
        fprintf(
                stderr,
                "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }

    // reset draws to the new size
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(RenderFunction);

    // behavior to run at idle
    glutIdleFunc(IdleFunction);
    glutTimerFunc(0, TimerFunction, 0);

    // other function calls
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
}

void ResizeFunction(int Width, int Height) {
    CurrentWidth = Width;
    CurrentHeight = Height;

    glViewport(0, 0, (GLsizei) CurrentWidth, (GLsizei) CurrentHeight); // Set the viewport
    glMatrixMode(GL_PROJECTION);    // Set the Matrix mode
    glLoadIdentity();
    //gluPerspective(75, (GLfloat) CurrentWidth / (GLfloat) CurrentHeight, 0, 300.0);
    glOrtho(-ortho, ortho, -ortho, ortho, -ortho, ortho);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*gluLookAt(rotLx, rotLy, rotLz + 15.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);*/
}

void RenderFunction() {
    ++FrameCount; // increasing fps counter
    glClear(GL_COLOR_BUFFER_BIT);


    // DRAWINGS START
    display();
    // DRAWINGS END

    // send all draws
    glPopMatrix();
    glFlush();

    // OpenGL is the front when calling to glutSwapBuffers();
    glutSwapBuffers();
    //glutPostRedisplay();
}

void IdleFunction() {
    glutPostRedisplay();
}

void TimerFunction(int Value) {
    if (0 != Value) {
        char *TempString = (char *)
                malloc(512 + strlen(WINDOW_TITLE_PREFIX));

        sprintf(
                TempString,
                "%s: %d FPS @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
        );

        glutSetWindowTitle(TempString);
        free(TempString);
    }

    FrameCount = 0;
    glutTimerFunc(250, TimerFunction, 1);
}

// This function is used for the navigation keys
void keyboard(unsigned char key, int x, int y) {
    switch (key) {   // x,X,y,Y,z,Z uses the glRotatef() function

        // I-J-K-L-U-O for 90 degrees rotation

        case 'j': // Rotates on x axis by -90 degree
        case 'J':
            rotX -= 90.0f;
            break;
        case 'l': // Rotates on x axis by 90 degree
        case 'L':
            rotX += 90.0f;
            break;

        case 'k': // Rotates on y axis by -90 degree
        case 'K':
            rotY -= 90.0f;
            break;
        case 'i': // Rotates on y axis by 90 degree
        case 'I':
            rotY += 90.0f;
            break;
        case 'u': // Rotates on z axis by -90 degree
        case 'U':
            rotZ -= 90.0f;
            break;
        case 'o': // Rotates on z axis by 90 degree
        case 'O':
            rotZ += 90.0f;
            break;

        case 'r': // Default, resets the translations vies from starting view
        case 'R':
            X = Y = 0.0f;
            Z = 0.0f;
            rotX = defaultRotX;
            rotY = 0.0f;
            rotZ = defaultRotZ;
            rotLx = 0.0f;
            rotLy = 0.0f;
            rotLz = 0.0f;
            break;

            // W-A-S-D

        case 's': // Rotates screen on x axis
        case 'S':
            rotX -= step;
            break;
        case 'w': // Opposite way
        case 'W':
            rotX += step;
            break;

        case 'd': // Rotates screen on z axis
        case 'D':
            rotZ -= step;
            break;

        case 'a': // Opposite way
        case 'A':
            rotZ += step;
            break;

        default:
            break;
    }
    glutPostRedisplay(); // Redraw the scene
}

// called on special key pressed
void specialKey(int key, int x, int y) {

// The keys below are using the gluLookAt() function for navigation
// Check which key is pressed

    switch (key) {
        case GLUT_KEY_LEFT : // Rotate on x axis
            X -= step;
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

// this function is used to move objects along with XYZ
void translateRotate() {
    glPushMatrix();    // It is important to push the Matrix before calling
    glRotatef(rotX, 1.0, 0.0, 0.0); // Rotate on x
    glRotatef(rotY, 0.0, 1.0, 0.0); // Rotate on y
    glRotatef(rotZ, 0.0, 0.0, 1.0); // Rotate on z
    glTranslatef(X, Y, Z);    //
}