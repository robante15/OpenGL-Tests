# Bouncing Spheres: A Modular 3D OpenGL Project

This project is a 3D graphics application built with OpenGL 1.1 and GLUT, featuring bouncing spheres inside a wireframe cube, with a modular camera system, dynamic lighting, and user controls. The codebase is organized into modules inspired by the design principles of **librw** (an open-source reimplementation of RenderWare, used in GTA III decompilation projects), emphasizing modularity, reusability, and clarity. It serves as an educational tool for learning 3D graphics, matrix transformations, and object-oriented programming in C++.

## Project Overview

The application renders a 3D scene where:
- Spheres with random colors and velocities bounce inside a 10x10x10 wireframe cube.
- A user-controlled camera allows navigation using WASD keys (movement), QE keys (vertical movement), and mouse dragging (rotation).
- A single point light illuminates the spheres, with togglable lighting and adjustable rendering styles (filled, wireframe, points).
- Users can add/remove spheres, adjust their speed, stop/resume motion, and toggle lighting and rendering styles via keyboard controls.

The project is designed for educational purposes, demonstrating:
- Modular C++ programming with separate classes for mathematics, camera, spheres, and scene management.
- 3D transformations using custom vector and matrix classes.
- OpenGL pipeline concepts (modelview, projection, lighting).
- User input handling with GLUT.

## File Structure

The project consists of the following files, organized to promote modularity and maintainability:

- **`math.h`, `math.cpp`**:
  - Defines `Vector3` and `Matrix4` classes for 3D vector and matrix operations.
  - `Vector3`: Supports addition, subtraction, dot product, cross product, normalization, and length calculation.
  - `Matrix4`: Implements a 4x4 matrix with a `lookAt` function to compute view matrices and `getOpenGLMatrix` to interface with OpenGL.
  - Used by the camera and sphere modules for transformations.

- **`camera.h`, `camera.cpp`**:
  - Implements the `Camera` class for 3D navigation.
  - Stores position, forward direction, and up vector as `Vector3`.
  - Supports movement (forward, right, up) and rotation (yaw, pitch) via keyboard and mouse input.
  - Computes the view matrix using `Matrix4::lookAt`, replacing `gluLookAt`.

- **`sphere.h`, `sphere.cpp`**:
  - Defines the `TSphere` class for bouncing spheres.
  - Each sphere has a position, direction, speed, and color (all as `Vector3`).
  - Handles bouncing logic (collision with cube boundaries), speed modification, and motion control.
  - Generates random initial positions, directions, and colors.

- **`scene.h`, `scene.cpp`**:
  - Implements the `Scene` class, managing the OpenGL context, rendering, and user input.
  - Contains a vector of `TSphere` pointers, a `Camera` instance, and a `GLUquadric` for rendering spheres.
  - Handles lighting setup, rendering loop, and input processing (keyboard, mouse).
  - Uses static callback functions to interface with GLUT.

- **`main.cpp`**:
  - Entry point of the application.
  - Initializes GLUT, creates a `Scene` instance, and registers callbacks for rendering, input, and idle processing.

## Workflow

The program's execution follows this flow:

1. **Initialization** (`main.cpp`):
   - GLUT is initialized with a double-buffered RGBA window (800x600 pixels) and depth testing.
   - A `Scene` object is created, initializing the camera, one sphere, lighting, and OpenGL state.

2. **Scene Setup** (`Scene::Scene`, `Scene::initGL`):
   - The camera is positioned at `(3, 3, 14)`, looking at `(0, 0, 0)` with up vector `(0, 1, 0)`.
   - A point light (`GL_LIGHT0`) is configured at `(0, 5, 5)` with ambient, diffuse, and specular components.
   - A `GLUquadric` is created for sphere rendering with smooth normals.

3. **Rendering Loop** (`Scene::display`):
   - Clears the color and depth buffers.
   - Sets the modelview matrix using the camera's view matrix (`camera->getViewMatrix().getOpenGLMatrix`).
   - Renders the wireframe cube (white, unaffected by lighting when lighting is disabled).
   - Renders each sphere at its position with its color, using `gluSphere`.
   - Swaps buffers to display the frame.

4. **Input Handling** (`Scene::keyboard`, `Scene::mouse`, `Scene::motion`):
   - Keyboard: Processes keys for camera movement (WASDQE), sphere control (+, -, t, r, 0, p), lighting toggle (l), and style change (c).
   - Mouse: Dragging the left button rotates the camera (yaw and pitch).
   - Ensures the camera stays above `z=6.0` to avoid entering the cube.

5. **Update Loop** (`Scene::idle`):
   - Updates each sphere's position, checking for collisions with the cube boundaries.
   - Sleeps for 33ms to limit the frame rate to ~30 FPS.
   - Requests a redraw with `glutPostRedisplay`.

6. **Reshape** (`Scene::reshape`):
   - Adjusts the viewport and projection matrix (`gluPerspective`) when the window is resized.
   - Uses a 60° field of view, near plane at 1.0, and far plane at 100.0.

## Key Functions and Classes

### Classes
- **`Vector3`** (`math.h`):
  - Represents a 3D vector with operations like `operator+`, `dot`, `cross`, `normalized`, and `length`.
  - Used for positions, directions, and colors.

- **`Matrix4`** (`math.h`):
  - Represents a 4x4 matrix for transformations.
  - `lookAt(eye, center, up)`: Computes a view matrix for the camera.
  - `getOpenGLMatrix(out)`: Converts the matrix to an OpenGL-compatible `float[16]`.

- **`Camera`** (`camera.h`):
  - Manages camera position, orientation, and movement.
  - Methods:
    - `moveForward(delta)`, `moveRight(delta)`, `moveUp(delta)`: Translates the camera.
    - `rotate(delta_yaw, delta_pitch)`: Rotates the camera (pitch limited to ±90°).
    - `getViewMatrix()`: Returns the view matrix using `Matrix4::lookAt`.
    - `update()`: Recalculates forward and up vectors after rotation.

- **`TSphere`** (`sphere.h`):
  - Represents a bouncing sphere.
  - Methods:
    - `test()`: Updates position and reverses direction on cube boundary collision.
    - `modifySpeed(inc)`: Adjusts speed and direction.
    - `restoreSpeed(new_speed)`: Resets speed to original or specified value.
    - `getPos()`, `getColor()`, `getSpeed()`: Accessors for rendering and control.

- **`Scene`** (`scene.h`):
  - Manages the scene, rendering, and input.
  - Methods:
    - `display()`: Renders the scene.
    - `reshape(width, height)`: Updates projection matrix.
    - `idle()`: Updates sphere positions.
    - `keyboard(key, x, y)`: Handles keyboard input.
    - `mouse(button, state, x, y)`, `motion(x, y)`: Handles mouse input.
    - Static callbacks (`displayCallback`, etc.): Interface with GLUT.

### User Controls
- **Camera**:
  - **WASD**: Move forward/backward, left/right.
  - **QE**: Move up/down.
  - **Mouse (left drag)**: Rotate (yaw and pitch).
- **Spheres**:
  - **t**: Add a new sphere.
  - **r**: Remove the last sphere.
  - **+**, **-**: Increase/decrease speed.
  - **0**: Stop all spheres.
  - **p**: Restore original speeds.
- **Rendering**:
  - **l**: Toggle lighting.
  - **c**: Cycle sphere rendering style (filled, wireframe, points).
- **Exit**:
  - **Esc**: Close the application.

## Understanding the Code

### Core Concepts
1. **Modular Design**:
   - The code is split into modules (`math`, `camera`, `sphere`, `scene`) for reusability and maintainability, inspired by **librw**.
   - Each module has a clear responsibility (e.g., `math` for vector/matrix math, `camera` for navigation).

2. **Camera System**:
   - The `Camera` class uses `Vector3` for position, forward, and up vectors, and `Matrix4` for the view matrix.
   - Movement is relative to the camera's orientation (e.g., `forward` for WASD), and rotation uses yaw/pitch for natural control.
   - The view matrix is computed with `Matrix4::lookAt`, applied to `GL_MODELVIEW` in `Scene::display`.

3. **OpenGL Pipeline**:
   - **GL_MODELVIEW**: Combines the view matrix (camera) and model transformations (object positions).
   - **GL_PROJECTION**: Defines a perspective projection (60° FOV, near=1.0, far=100.0).
   - Lighting uses `GL_LIGHT0` with ambient, diffuse, and specular components, and `GL_COLOR_MATERIAL` for sphere colors.

4. **Sphere Dynamics**:
   - Spheres move with constant velocity, reversing direction when hitting the cube boundaries (`±5` in X, Y, Z).
   - Random colors and initial directions add visual variety.

### Key Implementation Details
- **View Matrix**: The camera's view matrix transforms world coordinates to camera space, applied via `glMultMatrixf` in `Scene::display`.
- **Lighting**: A single point light at `(0, 5, 5)` creates realistic shading on spheres, with togglable lighting to observe raw colors.
- **GLUquadric**: Used for rendering spheres with smooth normals, supporting filled, wireframe, and point styles.
- **Error Checking**: `Scene::checkGLError` logs OpenGL errors for debugging.

## Compilation and Execution

### Dependencies
- **OpenGL**, **GLU**, **GLUT/freeglut**: Required for rendering and window management.
- **C++11**: For `<random>`, `<thread>`, and modern features.

#### Linux (Ubuntu)
```bash
sudo apt-get install freeglut3 freeglut3-dev mesa-common-dev libstdc++6
```

#### Windows (MinGW)
```bash
pacman -S mingw-w64-x86_64-freeglut
```
Copy `freeglut.dll` to the executable directory or `C:\Windows\System32`.

#### macOS
```bash
brew install freeglut
```

### Compile
Place all source files in the same directory and use:

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

### Run
```bash
./bouncing_spheres  # Linux/macOS
./bouncing_spheres.exe  # Windows
```

## Debugging Tips
- **Black Screen**: Check the view matrix in `Scene::display`. Print `view_matrix` to verify values:
  ```cpp
  float view_matrix[16];
  camera->getViewMatrix().getOpenGLMatrix(view_matrix);
  printf("View Matrix:\n");
  for (int i = 0; i < 4; ++i) {
      printf("%f %f %f %f\n", view_matrix[i], view_matrix[i+4], view_matrix[i+8], view_matrix[i+12]);
  }
  ```
- **GL Errors**: Enable `Scene::checkGLError` calls to log OpenGL errors.
- **Camera Issues**: Verify `Camera::update` recalculates `forward` and `up` correctly.
- **Tools**: Use **gdb**, **VSCode** (with `tasks.json` and `launch.json`), or **RenderDoc** for deeper inspection.

## Additional Information

### Inspiration from librw
The project draws inspiration from **librw**, an open-source reimplementation of RenderWare used in GTA III decompilation:
- **Modularity**: Like `rwcore.h` (math) and `rpworld.h` (scene management), our `math`, `camera`, and `scene` modules are independent.
- **Camera**: The `Camera` class emulates `RwCamera`, using vectors and matrices for natural 3D navigation.
- **Extensibility**: The codebase can be extended with entities, textures, or shaders, mirroring RenderWare's flexibility.

### Potential Extensions
- **Lighting Mini-Project**: Add two more lights (directional red, point green) and a solid cube with normals, with controls for `shininess` (keys 1, 2, 3).
- **Collisions**: Implement sphere-sphere collision detection using `Vector3::length`.
- **Textures**: Apply textures to spheres or the cube using OpenGL texture mapping.
- **Entity System**: Create a base `Entity` class for spheres and other objects, inspired by `RpClump`.
- **Modern OpenGL**: Migrate to OpenGL 3.3+ with shaders for better performance and flexibility.

### Notes
- The camera ensures `z >= 6.0` to prevent entering the cube, maintaining visibility.
- The frame rate is capped at ~30 FPS using a 33ms sleep in `Scene::idle`.
- The project uses OpenGL 1.1 for simplicity but can be adapted to modern OpenGL.

## License
This project is provided for educational purposes. Feel free to use, modify, and distribute it under the [MIT License](LICENSE).

## Acknowledgments
- Inspired by **librw** and the GTA III decompilation community.
- Built with OpenGL, GLU, and freeglut.
- Developed as part of a 3D graphics learning journey.

For questions or contributions, open an issue or pull request on the repository.