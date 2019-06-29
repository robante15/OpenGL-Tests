#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstring>

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

    std::cout << decimal <<std::endl;

    return decimal;
}

static GLfloat *Hex2RGB(std::string hex) {
    float *color = new float[3];

    if (hex[0] == '#'){
        hex = hex.erase(0, 1);
    }

    char char1[2];
    strcpy(char1,hex.substr(0, 2).c_str());

    char char2[2];
    strcpy(char2,hex.substr(2, 2).c_str());

    char char3[2];
    strcpy(char3,hex.substr(4, 2).c_str());

    color[0] = (float)Hex2Dec(char1,2)/255;
    color[1] = (float)Hex2Dec(char2,2)/255;
    color[2] = (float)Hex2Dec(char3,2)/255;

    std::cout << "Color0: " << color[0] << " Color1: " << color[1] << " Color2: " << color[2] << std::endl;

    return color;
}

void circuloTeselado(float radio, int numPuntos) {
    GLfloat *color = Hex2RGB("2bc234");
    glColor3fv(color);
    glBegin(GL_LINES);

    for (int i = 0; i <= numPuntos; i++) {
        float Angulo = i * (2.0 * M_PI / numPuntos);
        float X = cos(Angulo) * radio;
        float Y = sin(Angulo) * radio;
        glVertex2f(X, Y);

        float Angulo2 = (i + 1) * (2.0 * M_PI / numPuntos);
        float X2 = cos(Angulo2) * radio;
        float Y2 = sin(Angulo2) * radio;
        glVertex2f(X2, Y2);

    }
}

void circuloLineal(float radio, int numPuntos) {
    glColor3f(1.0f, 1.0f, 1.0f); //Color azul
    glBegin(GL_LINES);
    for (int i = 0; i <= numPuntos; i++) {
        glVertex2f(0, 0);
        float Angulo = i * (2.0 * M_PI / numPuntos);
        float X = cos(Angulo) * radio;
        float Y = sin(Angulo) * radio;
        glVertex2f(X, Y);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    circuloTeselado(0.5, 15);

    glEnd();
    glFlush();

}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

float Grados2Radianes(float grados) {
    float radianes = grados * (M_PI / 180);
    return radianes;
}

float CalculoY(float X, float radio) {
    float Y = sqrt(radio * radio - X * X);
    return Y;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("-- Ejemplo Circulo --");
    //std::cout << argc << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
