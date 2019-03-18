#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstring>

static GLfloat *Hex2RGB(std::string hex);

static void lineStrip(GLfloat arregloPuntos[][3], int cFil, int cCol, std::string colorHexa, GLfloat anchoLinea);

static void circuloPoligono(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc);

static void
circuloLineas(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc, GLfloat anchoLinea);

static void
sectorCirculoLinea(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc,
                   GLfloat anchoLinea, GLfloat rotacionG, GLfloat aperturaGrad);

static void
sectorCirculoPoly(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc, GLfloat rotacionG,
                  GLfloat aperturaGrad);

static void segmentoCirculoPoly(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc,
                                GLfloat rotacionG, GLfloat aperturaGrad);

static void
segmentoCirculoLinea(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc,
                     GLfloat anchoLinea, GLfloat rotacionG, GLfloat aperturaGrad);

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat array1[4][3] = {
            {-1.0, 0.0,  0.0},
            {0.0,  -1.0, 0.0},
            {1.0,  0.0,  0.0},
            {0.0,  1.0,  0.0}
    };

    GLfloat array2[4][3] = {
            {1.0,  0.0,  0.0},
            {0.0,  1.0,  0.0},
            {-1.0, 0.0,  0.0},
            {0.0,  -1.0, 0.0}
    };

    lineStrip(array1, 4, 3, "00FFF0", 1);
    sectorCirculoLinea(5.5, 5.5, 4, "00FF00", 15, 1, 315, 90);
    sectorCirculoPoly(-5.5, 5.5, 4, "00FF00", 15, 35, 125);
    circuloPoligono(1, 7.5, 2, "00FF00", 15);
    circuloLineas(-7.5, 3, 2, "00FF00", 15,2);
    segmentoCirculoPoly(-2.5,2.5,2.5,"FF0000",25,0,270);
    segmentoCirculoLinea(3,2.5,2.5,"0000FF",25,1,180,270);


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
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("-- Ejemplo TriangleFan --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

static void circuloPoligono(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc) {
    glBegin(GL_POLYGON);

    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);

    for (int i = 0; i < fracCirc + 1; i++) {  // +1 para cerrar
        glVertex2f(coorX + radio * cos(2.0 * M_PI * i / fracCirc),
                   coorY + radio * sin(2.0 * M_PI * i / fracCirc));
    }
    glEnd();
}

static void
circuloLineas(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc, GLfloat anchoLinea) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < fracCirc + 1; i++) {  // +1 para cerrar
        glVertex2f(coorX + radio * cos(2.0 * M_PI * i / fracCirc),
                   coorY + radio * sin(2.0 * M_PI * i / fracCirc));
    }
    glEnd();
}

static GLfloat Grados2Radianes(GLfloat grados) {
    GLfloat radianes;
    radianes = (M_PI * grados) / 180;
    return radianes;
}

static void
sectorCirculoLinea(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc,
                   GLfloat anchoLinea, GLfloat rotacionG, GLfloat aperturaGrad) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_LOOP);

    GLfloat rotacionRad = Grados2Radianes(rotacionG);
    GLfloat aperturaRad = Grados2Radianes(aperturaGrad);

    glVertex2f(coorX, coorY);

    for (int i = 0; i < fracCirc + 1; i++) {  // +1 para cerrar
        glVertex2f(coorX + radio * cos(rotacionRad + aperturaRad * i / fracCirc),
                   coorY + radio * sin(rotacionRad + aperturaRad * i / fracCirc));
    }
    glEnd();
}

static void
sectorCirculoPoly(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc, GLfloat rotacionG,
                  GLfloat aperturaGrad) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glBegin(GL_POLYGON);

    GLfloat rotacionRad = Grados2Radianes(rotacionG);
    GLfloat aperturaRad = Grados2Radianes(aperturaGrad);

    glVertex2f(coorX, coorY);

    for (int i = 0; i < fracCirc + 1; i++) {  // +1 para cerrar
        glVertex2f(coorX + radio * cos(rotacionRad + aperturaRad * i / fracCirc),
                   coorY + radio * sin(rotacionRad + aperturaRad * i / fracCirc));
    }
    glEnd();
}

static void
segmentoCirculoLinea(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc,
                     GLfloat anchoLinea, GLfloat rotacionG, GLfloat aperturaGrad) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_LOOP);

    GLfloat rotacionRad = Grados2Radianes(rotacionG);
    GLfloat aperturaRad = Grados2Radianes(aperturaGrad);

    for (int i = 0; i < fracCirc + 1; i++) {  // +1 para cerrar
        glVertex2f(coorX + radio * cos(rotacionRad + aperturaRad * i / fracCirc),
                   coorY + radio * sin(rotacionRad + aperturaRad * i / fracCirc));
    }
    glEnd();
}

static void
segmentoCirculoPoly(GLfloat coorX, GLfloat coorY, GLfloat radio, std::string colorHexa, GLint fracCirc,
                    GLfloat rotacionG, GLfloat aperturaGrad) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glBegin(GL_POLYGON);

    GLfloat rotacionRad = Grados2Radianes(rotacionG);
    GLfloat aperturaRad = Grados2Radianes(aperturaGrad);


    for (int i = 0; i < fracCirc + 1; i++) {  // +1 para cerrar
        glVertex2f(coorX + radio * cos(rotacionRad + aperturaRad * i / fracCirc),
                   coorY + radio * sin(rotacionRad + aperturaRad * i / fracCirc));
    }
    glEnd();
}

static void lineStrip(GLfloat arregloPuntos[][3], int cFil, int cCol, std::string colorHexa, GLfloat anchoLinea) {
    GLfloat *color = Hex2RGB(colorHexa);
    glColor3fv(color);
    glLineWidth(anchoLinea);
    glBegin(GL_LINE_STRIP);


    for (int fila = 0; fila < cFil; fila++) {
        GLfloat vertex[3];
        for (int columna = 0; columna < cCol; columna++) {
            vertex[columna] = arregloPuntos[fila][columna];
            std::cout << arregloPuntos[fila][columna];
        }
        std::cout << std::endl;
        glVertex3fv(vertex);
    }
    glEnd();
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