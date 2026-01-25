cmake_minimum_required(VERSION 3.10)

project(main LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenMP
find_package(OpenMP REQUIRED)

# FreeGLUT
set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(LIBS/freeglut)

# OpenGL
find_package(OpenGL REQUIRED)

# Executável
add_executable(main
    "TRABALHO FINAL/main.cpp"
    CLASSES/INTERFACE/Interface.cpp
)

# Includes
target_include_directories(main PRIVATE
    CLASSES
    LIBS
    LIBS/freeglut/include
)

# Linkagem
target_link_libraries(main PRIVATE
    freeglut_static
    ${OPENGL_LIBRARIES}
    OpenMP::OpenMP_CXX
)

# Definir que freeglut é estático
target_compile_definitions(main PRIVATE FREEGLUT_STATIC)
