cmake_minimum_required(VERSION 2.8) #Versión mínima de cmake 
# Project Name
PROJECT(Parcial2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#########################################################
# INCLUYENDO LIBRERIA GLUT
#########################################################
find_package(GLUT REQUIRED) #buscar la libreria GlUT
include_directories(${GLUT_INCLUDE_DIRS}) # incluir los directorios 
link_directories(${GLUT_LIBRARY_DIRS}) #Linkeo de directorios 
add_definitions(${GLUT_DEFINITIONS}) #Agregar las definiciones 
#########################################################
# INCLUYENDO LIBRERIA OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
#########################################################
# Incluyendo archivos 
#########################################################
add_executable(executable main.cpp) # Agregando nombre del script y compilado

########################################################
# Linkeo de librerías 
#########################################################
# creación del ejecutable "hello"
target_link_libraries(executable ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SDL2_LIBRARIES})
