#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstring>

//Ayuda a la converción de Hexadecimal a Decimal, ya que analiza los caracteres y los convierte en numero
int charHec2Dec(char caracter) {
    if (isdigit(caracter))
        return caracter - '0';
    return 10 + (toupper(caracter) - 'A');
}

//Hace la conversión de Hexadecimal a Decimal
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

    std::cout << decimal << std::endl;

    return decimal;
}

/*Convierte una cadena de codigo de color Hexadecimal a un GLfloat RGB que ya puede ser usado para definir color
 *Como parametro de entrada se le pasa un String "#FFFFFF" que debe de ser un codigo de color Hexa */
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

    std::cout << "Color0: " << color[0] << " Color1: " << color[1] << " Color2: " << color[2] << std::endl;

    return color;
}


/*void circuloTeselado(float radio, int numPuntos) {
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
}*/

/*void circuloLineal(float radio, int numPuntos) {
    glColor3f(1.0f, 1.0f, 1.0f); //Color azul
    glBegin(GL_LINES);
    for (int i = 0; i <= numPuntos; i++) {
        glVertex2f(0, 0);
        float Angulo = i * (2.0 * M_PI / numPuntos);
        float X = cos(Angulo) * radio;
        float Y = sin(Angulo) * radio;
        glVertex2f(X, Y);
    }
}*/

//Función para la conversión de Grados a Radianes (Ya que las funciones trabajan con radianes, pero les ingresamos grados
float Grados2Radianes(float grados) {
    float radianes = grados * (M_PI / 180);
    return radianes;
}

float CalculoY(float X, float radio) {
    float Y = sqrt(radio * radio - X * X);
    return Y;
}

/*Este es un circulo solido, hecho con poligonos, sus valores de entrada son:
 * coorX: Coordenada en X para la creación del objeto
 * coorY: Coordenada en Y para la creación del objeto
 * radio: Radio de la circunferencia
 * colorHexa, el color que tendrá el objeto
 * fracCirc: Cantidad de segmentos que tendrá el circulo*/
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

/*Este es el perimetro de un circulo, hecho con lineas, sus valores de entrada son:
 * coorX: Coordenada en X para la creación del objeto
 * coorY: Coordenada en Y para la creación del objeto
 * radio: Radio de la circunferencia
 * colorHexa, el color que tendrá el objeto
 * fracCirc: Cantidad de segmentos que tendrá el circulo
 * anchoLinea: El grosor que tendrá la linea con la que se dibuja el circulo*/
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

/*Dibuja el sector de un circulo con lineas, sus valores de entrada son:
 * coorX: Coordenada en X para la creación del objeto
 * coorY: Coordenada en Y para la creación del objeto
 * radio: Radio de la circunferencia
 * colorHexa, el color que tendrá el objeto
 * fracCirc: Cantidad de segmentos que tendrá el circulo
 * anchoLinea: El grosor que tendrá la linea con la que se dibuja el circulo
 * rotacionG: Es la rotación que tendrá el objeto
 * aperturaGrad: Es la apertura en grados que tendrá el sector del circulo*/
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

/*Dibuja el sector de un circulo con poligonos, sus valores de entrada son:
 * coorX: Coordenada en X para la creación del objeto
 * coorY: Coordenada en Y para la creación del objeto
 * radio: Radio de la circunferencia
 * colorHexa, el color que tendrá el objeto
 * fracCirc: Cantidad de segmentos que tendrá el circulo
 * rotacionG: Es la rotación que tendrá el objeto
 * aperturaGrad: Es la apertura en grados que tendrá el sector del circulo*/
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

/*Dibuja el segmento de un circulo con lineas, sus valores de entrada son:
 * coorX: Coordenada en X para la creación del objeto
 * coorY: Coordenada en Y para la creación del objeto
 * radio: Radio de la circunferencia
 * colorHexa, el color que tendrá el objeto
 * fracCirc: Cantidad de segmentos que tendrá el circulo
 * anchoLinea: El grosor que tendrá la linea con la que se dibuja el circulo
 * rotacionG: Es la rotación que tendrá el objeto
 * aperturaGrad: Es la apertura en grados que tendrá el sector del circulo*/
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

/*Dibuja el segmento de un circulo con poligonos, sus valores de entrada son:
 * coorX: Coordenada en X para la creación del objeto
 * coorY: Coordenada en Y para la creación del objeto
 * radio: Radio de la circunferencia
 * colorHexa, el color que tendrá el objeto
 * fracCirc: Cantidad de segmentos que tendrá el circulo
 * rotacionG: Es la rotación que tendrá el objeto
 * aperturaGrad: Es la apertura en grados que tendrá el sector del circulo*/
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

/* Se ingresa un Array de valores y con este se va dibujando un LineStrip, sus valores son:
 * arregloPuntos[][3]: Es el array del cual tomará los valores en X,Y,Z para dibujar el lineStrip
 * cFil: es la cantidad de Filas que tiene el arreglo
 * cCol: La cantidad de columnas del Array
 * colorHexa: Color en Hexadecimal para la linea
 * anchoLinea: Es el grosor que tendrá la linea*/
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