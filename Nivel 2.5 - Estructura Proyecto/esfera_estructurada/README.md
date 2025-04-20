# Esferas Rebotando: Un Proyecto Modular 3D con OpenGL

Este proyecto es una aplicación de gráficos 3D construida con OpenGL 1.1 y GLUT, que presenta esferas rebotando dentro de un cubo de alambre, con un sistema de cámara modular, iluminación dinámica y controles de usuario. El código está organizado en módulos inspirados en los principios de diseño de **librw** (una reimplementación de RenderWare usada en proyectos de descompilación de GTA III), con énfasis en modularidad, reutilización y claridad. Sirve como herramienta educativa para aprender gráficos 3D, transformaciones de matrices y programación orientada a objetos en C++.

## Descripción del Proyecto

La aplicación renderiza una escena 3D donde:

- Esferas con colores y velocidades aleatorias rebotan dentro de un cubo de alambre de 10x10x10.
- Una cámara controlada por el usuario permite navegar usando las teclas WASD (movimiento), QE (movimiento vertical) y arrastre con el ratón (rotación).
- Una luz puntual ilumina las esferas, con iluminación switchable y estilos de renderizado ajustables (relleno, alambre, puntos).
- Los usuarios pueden agregar/eliminar esferas, ajustar su velocidad, detener/reanudar el movimiento, y alternar estilos de iluminación y renderizado mediante el teclado.

Este proyecto está diseñado con fines educativos, demostrando:

- Programación modular en C++ con clases separadas para matemáticas, cámara, esferas y administración de la escena.
- Transformaciones 3D usando clases personalizadas de vectores y matrices.
- Conceptos del pipeline de OpenGL (modelview, proyección, iluminación).
- Manejo de entrada de usuario con GLUT.

## Estructura de Archivos

El proyecto está compuesto por los siguientes archivos, organizados para promover la modularidad y el mantenimiento:

- **`math.h`, `math.cpp`**:
    - Define las clases `Vector3` y `Matrix4` para operaciones con vectores y matrices 3D.
    - `Vector3`: Soporta suma, resta, producto punto, producto cruz, normalización y cálculo de longitud.
    - `Matrix4`: Implementa una matriz 4x4 con una función `lookAt` para calcular matrices de vista y `getOpenGLMatrix` para interactuar con OpenGL.
    - Usado por los módulos de cámara y esfera para transformaciones.

- **`camera.h`, `camera.cpp`**:
    - Implementa la clase `Camera` para navegación 3D.
    - Almacena posición, dirección hacia adelante y vector hacia arriba como `Vector3`.
    - Soporta movimiento (adelante, derecha, arriba) y rotación (yaw, pitch) mediante entrada de teclado y ratón.
    - Calcula la matriz de vista usando `Matrix4::lookAt`, reemplazando `gluLookAt`.

- **`sphere.h`, `sphere.cpp`**:
    - Define la clase `TSphere` para esferas rebotando.
    - Cada esfera tiene una posición, dirección, velocidad y color (todos como `Vector3`).
    - Maneja la lógica de rebote (colisión con los límites del cubo), modificación de velocidad y control de movimiento.
    - Genera posiciones, direcciones y colores iniciales aleatorios.

- **`scene.h`, `scene.cpp`**:
    - Implementa la clase `Scene`, gestionando el contexto de OpenGL, renderizado y entrada del usuario.
    - Contiene un vector de punteros a `TSphere`, una instancia de `Camera` y un `GLUquadric` para renderizar esferas.
    - Maneja la configuración de iluminación, el bucle de renderizado y el procesamiento de entrada (teclado, ratón).
    - Usa funciones de callback estáticas para interactuar con GLUT.

- **`main.cpp`**:
    - Punto de entrada de la aplicación.
    - Inicializa GLUT, crea una instancia de `Scene` y registra callbacks para renderizado, entrada y procesamiento en reposo.

## Flujo de Trabajo

La ejecución del programa sigue este flujo:

1. **Inicialización** (`main.cpp`):
    - GLUT se inicializa con una ventana RGBA de doble búfer (800x600 píxeles) y prueba de profundidad.
    - Se crea un objeto `Scene`, que inicializa la cámara, una esfera, la iluminación y el estado de OpenGL.

2. **Configuración de la Escena** (`Scene::Scene`, `Scene::initGL`):
    - La cámara se posiciona en `(3, 3, 14)`, mirando hacia `(0, 0, 0)` con el vector hacia arriba `(0, 1, 0)`.
    - Se configura una luz puntual (`GL_LIGHT0`) en `(0, 5, 5)` con componentes ambientales, difusas y especulares.
    - Se crea un `GLUquadric` para renderizar esferas con normales suaves.

3. **Bucle de Renderizado** (`Scene::display`):
    - Limpia los búferes de color y profundidad.
    - Establece la matriz de modelo-vista usando la matriz de vista de la cámara (`camera->getViewMatrix().getOpenGLMatrix`).
    - Renderiza el cubo wireframe (blanco, no afectado por la iluminación cuando está desactivada).
    - Renderiza cada esfera en su posición con su color, usando `gluSphere`.
    - Intercambia los búferes para mostrar el fotograma.

4. **Manejo de Entrada** (`Scene::keyboard`, `Scene::mouse`, `Scene::motion`):
    - Teclado: Procesa teclas para mover la cámara (WASDQE), controlar esferas (+, -, t, r, 0, p), alternar iluminación (l) y cambiar el estilo (c).
    - Ratón: Arrastrar con el botón izquierdo rota la cámara (yaw y pitch).
    - Asegura que la cámara permanezca por encima de `z=6.0` para evitar entrar al cubo.

5. **Bucle de Actualización** (`Scene::idle`):
    - Actualiza la posición de cada esfera, verificando colisiones con los límites del cubo.
    - Duerme durante 33ms para limitar la tasa de fotogramas a ~30 FPS.
    - Solicita un redibujado con `glutPostRedisplay`.

6. **Redimensionar** (`Scene::reshape`):
    - Ajusta el viewport y la matriz de proyección (`gluPerspective`) cuando se redimensiona la ventana.
    - Usa un campo de visión de 60°, un plano cercano a 1.0 y un plano lejano a 100.0.

## Funciones y Clases Clave

### Clases
- **`Vector3`** (`math.h`):
    - Representa un vector 3D con operaciones como `operator+`, `dot`, `cross`, `normalized` y `length`.
    - Usado para posiciones, direcciones y colores.

- **`Matrix4`** (`math.h`):
    - Representa una matriz 4x4 para transformaciones.
    - `lookAt(eye, center, up)`: Calcula una matriz de vista para la cámara.
    - `getOpenGLMatrix(out)`: Convierte la matriz a un formato compatible con OpenGL (`float[16]`).

- **`Camera`** (`camera.h`):
    - Gestiona la posición, orientación y movimiento de la cámara.
    - Métodos:
        - `moveForward(delta)`, `moveRight(delta)`, `moveUp(delta)`: Translada la cámara.
        - `rotate(delta_yaw, delta_pitch)`: Rota la cámara (pitch limitado a ±90°).
        - `getViewMatrix()`: Devuelve la matriz de vista usando `Matrix4::lookAt`.
        - `update()`: Recalcula los vectores `forward` y `up` después de la rotación.

- **`TSphere`** (`sphere.h`):
    - Representa una esfera rebotando.
    - Métodos:
        - `test()`: Actualiza la posición y revierte la dirección al colisionar con los límites del cubo.
        - `modifySpeed(inc)`: Ajusta la velocidad y dirección.
        - `restoreSpeed(new_speed)`: Restaura la velocidad al valor original o especificado.
        - `getPos()`, `getColor()`, `getSpeed()`: Accesores para renderizado y control.

- **`Scene`** (`scene.h`):
    - Gestiona la escena, el renderizado y la entrada del usuario.
    - Métodos:
        - `display()`: Renderiza la escena.
        - `reshape(width, height)`: Actualiza la matriz de proyección.
        - `idle()`: Actualiza las posiciones de las esferas.
        - `keyboard(key, x, y)`: Maneja la entrada del teclado.
        - `mouse(button, state, x, y)`, `motion(x, y)`: Maneja la entrada del ratón.
        - Callbacks estáticos (`displayCallback`, etc.): Interfaz con GLUT.

### Controles del Usuario

- **Cámara**:
  - **WASD**: mover adelante/atrás, izquierda/derecha.
  - **QE**: mover arriba/abajo.
  - **Ratón (botón izquierdo)**: rotar (yaw y pitch).
- **Esferas**:
  - **t**: agregar esfera.
  - **r**: eliminar última esfera.
  - **+**, **-**: aumentar/disminuir velocidad.
  - **0**: detener todas.
  - **p**: restaurar velocidades.
- **Renderizado**:
  - **l**: alternar iluminación.
  - **c**: cambiar estilo de renderizado.
- **Salir**:
  - **Esc**: cerrar aplicación.

## Entendiendo el Código

### Conceptos Clave
1. **Diseño Modular**:
    - El código está dividido en módulos (`math`, `camera`, `sphere`, `scene`) para promover la reutilización y el mantenimiento, inspirado en **librw**.
    - Cada módulo tiene una responsabilidad clara (por ejemplo, `math` para matemáticas de vectores/matrices, `camera` para navegación).

2. **Sistema de Cámara**:
    - La clase `Camera` utiliza `Vector3` para los vectores de posición, dirección hacia adelante y hacia arriba, y `Matrix4` para la matriz de vista.
    - El movimiento es relativo a la orientación de la cámara (por ejemplo, `forward` para WASD), y la rotación usa yaw/pitch para un control natural.
    - La matriz de vista se calcula con `Matrix4::lookAt` y se aplica a `GL_MODELVIEW` en `Scene::display`.

3. **Pipeline de OpenGL**:
    - **GL_MODELVIEW**: Combina la matriz de vista (cámara) y las transformaciones del modelo (posiciones de los objetos).
    - **GL_PROJECTION**: Define una proyección en perspectiva (FOV de 60°, cercano=1.0, lejano=100.0).
    - La iluminación utiliza `GL_LIGHT0` con componentes ambientales, difusas y especulares, y `GL_COLOR_MATERIAL` para los colores de las esferas.

4. **Dinámica de las Esferas**:
    - Las esferas se mueven con velocidad constante, invirtiendo la dirección al chocar con los límites del cubo (`±5` en X, Y, Z).
    - Los colores y direcciones iniciales aleatorios añaden variedad visual.

### Detalles Clave de Implementación
- **Matriz de Vista**: La matriz de vista de la cámara transforma las coordenadas del mundo al espacio de la cámara, aplicada mediante `glMultMatrixf` en `Scene::display`.
- **Iluminación**: Una única luz puntual en `(0, 5, 5)` crea sombras realistas en las esferas, con iluminación conmutable para observar los colores sin procesar.
- **GLUquadric**: Utilizado para renderizar esferas con normales suaves, soportando estilos de relleno, alambre y puntos.
- **Verificación de Errores**: `Scene::checkGLError` registra errores de OpenGL para depuración.

## Compilación y Ejecución

### Dependencias
- **OpenGL**, **GLU**, **GLUT/freeglut**: Requeridos para renderizado y gestión de ventanas.
- **C++11**: Para `<random>`, `<thread>` y características modernas.

#### Linux (Ubuntu)
```bash
sudo apt-get install freeglut3 freeglut3-dev mesa-common-dev libstdc++6
```

#### Windows (MinGW)
```bash
pacman -S mingw-w64-x86_64-freeglut
```
Copia `freeglut.dll` al directorio del ejecutable o a `C:\Windows\System32`.

#### macOS
```bash
brew install freeglut
```

### Compilar
Coloca todos los archivos fuente en el mismo directorio y usa:

#### Linux
```bash
g++ -o bouncing_spheres main.cpp scene.cpp sphere.cpp camera.cpp math.cpp -lGL -lGLU -lglut -std=c++11
```

#### Windows (MinGW)
```bash
g++ -o bouncing_spheres.exe main.cpp scene.cpp sphere.cpp camera.cpp math.cpp -lopengl32 -lglu32 -lfreeglut -std=c++11
```

#### macOS
```bash
g++ -o bouncing_spheres main.cpp scene.cpp sphere.cpp camera.cpp math.cpp -framework OpenGL -framework GLUT -std=c++11
```

### Ejecutar
```bash
./bouncing_spheres  # Linux/macOS
./bouncing_spheres.exe  # Windows
```

## Consejos para Depuración
- **Pantalla Negra**: Verifica la matriz de vista en `Scene::display`. Imprime `view_matrix` para comprobar los valores:
    ```cpp
    float view_matrix[16];
    camera->getViewMatrix().getOpenGLMatrix(view_matrix);
    printf("Matriz de Vista:\n");
    for (int i = 0; i < 4; ++i) {
            printf("%f %f %f %f\n", view_matrix[i], view_matrix[i+4], view_matrix[i+8], view_matrix[i+12]);
    }
    ```
- **Errores de OpenGL**: Habilita las llamadas a `Scene::checkGLError` para registrar errores de OpenGL.
- **Problemas con la Cámara**: Verifica que `Camera::update` recalcula correctamente los vectores `forward` y `up`.
- **Herramientas**: Usa **gdb**, **VSCode** (con `tasks.json` y `launch.json`), o **RenderDoc** para una inspección más profunda.

## Información Adicional

### Inspiración de librw
El proyecto se inspira en **librw**, una reimplementación de código abierto de RenderWare utilizada en la descompilación de GTA III:
- **Modularidad**: Al igual que `rwcore.h` (matemáticas) y `rpworld.h` (gestión de escenas), nuestros módulos `math`, `camera` y `scene` son independientes.
- **Cámara**: La clase `Camera` emula a `RwCamera`, utilizando vectores y matrices para una navegación 3D natural.
- **Extensibilidad**: La base de código puede ampliarse con entidades, texturas o shaders, reflejando la flexibilidad de RenderWare.

### Posibles Extensiones
- **Mini-Proyecto de Iluminación**: Agregar dos luces más (una direccional roja y una puntual verde) y un cubo sólido con normales, con controles para ajustar el `brillo` (teclas 1, 2, 3).
- **Colisiones**: Implementar detección de colisiones entre esferas utilizando `Vector3::length`.
- **Texturas**: Aplicar texturas a las esferas o al cubo utilizando mapeo de texturas en OpenGL.
- **Sistema de Entidades**: Crear una clase base `Entity` para esferas y otros objetos, inspirado en `RpClump`.
- **OpenGL Moderno**: Migrar a OpenGL 3.3+ con shaders para mejorar el rendimiento y la flexibilidad.

### Notas
- La cámara asegura que `z >= 6.0` para evitar entrar en el cubo, manteniendo la visibilidad.
- La tasa de fotogramas está limitada a ~30 FPS utilizando una pausa de 33ms en `Scene::idle`.
- El proyecto utiliza OpenGL 1.1 por simplicidad, pero puede adaptarse a OpenGL moderno.

## Agradecimientos
- Inspirado por **librw** y la comunidad de descompilación de GTA III.
- Desarrollado con OpenGL, GLU y freeglut.
- Desarrollado como parte de un proceso de aprendizaje de gráficos 3D.

Para preguntas o contribuciones, abre una incidencia o solicitud de incorporación de cambios en el repositorio.