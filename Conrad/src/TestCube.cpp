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

    //float vertices[36 * 3] = {0.0};
    float colors[] = {  1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,

                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,

                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,

                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,

                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,

                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0};

    if(!setVertices(vertices, 3 * 36) || !setColors(colors, 3 * 36)) {
        std::cout << "Error updating vertices or colors" << std::endl;
    }

    load();
}

TestCube::~TestCube()
{
    //dtor
}
