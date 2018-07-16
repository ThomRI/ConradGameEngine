#include "TestCube.h"

TestCube::TestCube(float size) :
    StaticMesh(36) // 36 vertices as for 6 (2 triangles) per faces and 6 faces
{
    float vertices[] = {-size, -size, size,  -size, -size, -size,   size, -size, -size,
                        size, -size, size,   size, -size, size,     -size, -size, size,

                        size, -size, size,  -size, size, size,  -size, -size, size,
                        size, -size, size,  size, size, size,   -size, size, size,

                        size, -size, -size,  size, size, -size,  size, size, size,
                        size, -size, -size,  size, -size, size,  size, size, size,

                        -size, -size, -size,  -size, size, -size,   -size, size, size,
                        -size, -size, -size,  -size, -size, size,   -size, size, size,

                        size, size, -size,  -size, size, -size,     -size, size, size,
                        size, size, -size,  size, size, size,       -size, size, size,

                        size, -size, -size,  -size, -size, -size,  -size, size, -size,
                        size, -size, -size,  size, size, -size,    -size, size, -size};

    float colors[36] = {0.0};

    setVertices(vertices, 36);
    setColors(colors, 36);

    if(load()) {
        std::cout << "Cube loaded successfully !" << endl;
    }
}

TestCube::~TestCube()
{
    //dtor
}
