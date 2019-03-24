#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstring>

static GLfloat *Hex2RGB(std::string hex);

static void ejercicio3(std::string colorHexa, GLfloat anchoLinea, int opcion);

static void ejercicio4(std::string colorHexa, GLfloat anchoLinea, int opcion);

static GLfloat *Cart2Polar(GLfloat coorX, GLfloat coorY);

static GLfloat *Polar2Cart(GLfloat radio, GLfloat angle);

static GLfloat Grados2Radianes(GLfloat grados);

static void ejercicio5(GLfloat size, GLfloat petalos, std::string colorHexa, GLfloat anchoLinea) {
    GLfloat radio;
    GLfloat angle;
    GLfloat *coordenadasXY;

    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_STRIP);

    for (GLfloat i = 0; i <= 360; ++i) {
        //r=6*sen(7*anle)
        angle = Grados2Radianes(i);
        radio = size*sin(petalos*angle);
        coordenadasXY = Polar2Cart(radio, angle);
        glVertex2f(coordenadasXY[0], coordenadasXY[1]);
    }
    glEnd();
}

static void ejercicio6(GLfloat size, GLfloat petalos, std::string colorHexa, GLfloat anchoLinea) {
    GLfloat radio;
    GLfloat angle;
    GLfloat *coordenadasXY;

    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_STRIP);

    for (GLfloat i = 0; i <= 360; ++i) {
        //r=6.15cos(3angle)
        angle = Grados2Radianes(i);
        radio = size * cos(petalos * angle);
        coordenadasXY = Polar2Cart(radio, angle);
        glVertex2f(coordenadasXY[0], coordenadasXY[1]);
    }
    glEnd();
}

static void ejercicio7(GLfloat constante, GLfloat rotacion, std::string colorHexa, GLfloat anchoLinea) {
    GLfloat radio;
    GLfloat angle;
    GLfloat *coordenadasXY;

    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_STRIP);

    for (GLfloat i = 0; i <= rotacion; ++i) {
        //r=aθ
        angle = Grados2Radianes(i);
        radio = constante * angle;
        coordenadasXY = Polar2Cart(radio, angle);
        glVertex2f(coordenadasXY[0], coordenadasXY[1]);
    }
    glEnd();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    ejercicio5(6, 7, "#FFFFFF", 1.0);
    //ejercicio6(6.15, 3, "#FFFFFF", 1.0);
    //ejercicio7(0.3, 1080, "#FFFFFF", 1.0);
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

static GLfloat Grados2Radianes(GLfloat grados) {
    GLfloat radianes;
    radianes = (M_PI * grados) / 180;
    return radianes;
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

static GLfloat *Cart2Polar(GLfloat coorX, GLfloat coorY) {
    GLfloat *polar = new GLfloat[2];

    GLfloat radio = sqrt(pow(coorX, 2) + pow(coorY, 2));
    GLfloat angle = atan(coorY / coorX);

    polar[0] = radio;
    polar[1] = angle;

    return polar;

}

static GLfloat *Polar2Cart(GLfloat radio, GLfloat angle) {
    GLfloat *cartesiano = new GLfloat[2];

    GLfloat coorX = radio * cos(angle);
    GLfloat coorY = radio * sin(angle);

    cartesiano[0] = coorX;
    cartesiano[1] = coorY;

    return cartesiano;

}

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