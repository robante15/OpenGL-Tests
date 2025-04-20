/**
 * @struct GLColor
 * @brief Representa un color en el espacio RGB.
 *
 * Esta estructura se utiliza para definir un color utilizando componentes
 * flotantes para el rojo, verde y azul (RGB).
 *
 * @var GLColor::r
 * Componente roja del color. Valor en el rango [0.0, 1.0].
 *
 * @var GLColor::g
 * Componente verde del color. Valor en el rango [0.0, 1.0].
 *
 * @var GLColor::b
 * Componente azul del color. Valor en el rango [0.0, 1.0].
 */
struct GLColor {
    float rgb[3];
};


/**
 * @brief Convierte un color en formato RGB a un color en formato GLColor.
 * 
 * @param r Componente rojo del color (0-255).
 * @param g Componente verde del color (0-255).
 * @param b Componente azul del color (0-255).
 * @return GLColor Estructura que representa el color en formato GLColor, 
 *         donde cada componente (r, g, b) está normalizado en el rango [0.0, 1.0].
 */
GLColor RGBtoGLCOLOR(int r, int g, int b) {
    GLColor color;
    color.rgb[0] = (float)r / 255.0f;
    color.rgb[1] = (float)g / 255.0f;
    color.rgb[2] = (float)b / 255.0f;
    return color;
}