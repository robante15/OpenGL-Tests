#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstring>

static GLfloat *Hex2RGB(std::string hex);

static void ejercicio3(std::string colorHexa, GLfloat anchoLinea, int opcion) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_STRIP);

    GLfloat x;
    GLfloat y;
    for (float i = -3; i <= 3; i += 0.1) {

        if ((i >= -0.15 && i <= 0.20) && (opcion == 6 || opcion == 4)) {
            glEnd();
            glBegin(GL_LINE_STRIP);
        }

        x = i;

        switch (opcion) {
            case 1:
                y = sinh(x);
                break;
            case 2:
                y = cosh(x);
                break;
            case 3:
                y = tanh(x);
                break;
            case 4:
                y = cosh(x) / sinh(x);
                break;
            case 5:
                y = 1 / cosh(x);
                break;
            case 6:
                y = 1 / sinh(x);
        }


        glVertex2f(x, y);
    }
    glEnd();
}

static void ejercicio4(std::string colorHexa, GLfloat anchoLinea, int opcion) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_STRIP);

    GLfloat x;
    GLfloat y;

    if (opcion == 1) {
        for (float i = -5; i <= 5; i += 0.1) {
            x = i;
            y = log(x + sqrt(pow(x, 2) + 1));
            glVertex2f(x, y);
        }
    }

    if (opcion == 2) {
        for (float i = 1; i <= 5; i += 0.1) {
            x = i;
            y = log(x + sqrt(pow(x, 2) - 1));
            glVertex2f(x, y);
        }
    }

    if (opcion == 3) {
        for (float i = -0.99; i <= 1.0; i += 0.1) {
            x = i;
            y = 0.5 * log((1 + x) / (1 - x));
            glVertex2f(x, y);
        }
    }

    if (opcion == 4) {
        for (float i = -5; i <= 5; i += 0.1) {
            if (i >= -1.0001 && i <= 1.1) {
                glEnd();
                glBegin(GL_LINE_STRIP);
            }
            x = i;
            y = 0.5 * log((x + 1) / (x - 1));
            glVertex2f(x, y);
        }
    }

    if (opcion == 5) {
        for (float i = 0.01; i <= 0.99; i += 0.01) {
            x = i;
            y = log(0.5 + (sqrt((1 / pow(x, 2)) - 1)));
            glVertex2f(x, y);
        }
    }

    if (opcion == 6) {
        for (float i = -5; i <= 5; i += 0.001) {
            if (i >= -0.708 && i <= 0.001) {
                glEnd();
                glBegin(GL_LINE_STRIP);
            }
            x = i;
            y = log(sqrt(1 + 1 / x * x) + 1 / x);
            glVertex2f(x, y);
        }
    }


    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    ejercicio4("FFFFFF", 1.0, 6);
    glFlush();
}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("-- Guia de Ejercicios --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

int charHec2Dec(char caracter) {
    if (isdigit(caracter))
        return caracter - '0';
    return 10 + (toupper(caracter) - 'A');
}

unsigned long long Hex2Dec(char *cadenaHexadecimal, int longitud) {
    unsigned long long decimal = 0;
    int potencia = 0;
    for (int i = longitud - 1; i >= 0; i--) {
        // Obtener el decimal, por ejemplo para A es 10, para F 15 y para 9 es 9
        int valorActual = charHec2Dec(cadenaHexadecimal[i]);
        // Elevar 16 a la potencia que se va incrementando, y multiplicarla por el
        // valor
        unsigned long long elevado = pow(16, potencia) * valorActual;

        // Agregar al número
        decimal += elevado;
        // Avanzar en la potencia
        potencia++;
    }

    //std::cout << decimal << std::endl;

    return decimal;
}

static GLfloat *Hex2RGB(std::string hex) {
    float *color = new float[3];

    if (hex[0] == '#') {
        hex = hex.erase(0, 1);
    }

    char char1[2];
    strcpy(char1, hex.substr(0, 2).c_str());

    char char2[2];
    strcpy(char2, hex.substr(2, 2).c_str());

    char char3[2];
    strcpy(char3, hex.substr(4, 2).c_str());

    color[0] = (float) Hex2Dec(char1, 2) / 255;
    color[1] = (float) Hex2Dec(char2, 2) / 255;
    color[2] = (float) Hex2Dec(char3, 2) / 255;

    return color;
}