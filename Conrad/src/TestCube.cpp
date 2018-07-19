#include "TestCube.h"

TestCube::TestCube(float size) :
    StaticMesh(36) // 36 vertices as for 6 (2 triangles) per faces and 6 faces
{
    float vertices[] = {   -size, -size, -size,   size, -size, -size,   size, size, -size,     // Face 1
                           -size, -size, -size,   -size, size, -size,   size, size, -size,     // Face 1

                           size, -size, size,   size, -size, -size,   size, size, -size,       // Face 2
                           size, -size, size,   size, size, size,   size, size, -size,         // Face 2

                           -size, -size, size,   size, -size, size,   size, -size, -size,      // Face 3
                           -size, -size, size,   -size, -size, -size,   size, -size, -size,    // Face 3

                           -size, -size, size,   size, -size, size,   size, size, size,        // Face 4
                           -size, -size, size,   -size, size, size,   size, size, size,        // Face 4

                           -size, -size, -size,   -size, -size, size,   -size, size, size,     // Face 5
                           -size, -size, -size,   -size, size, -size,   -size, size, size,     // Face 5

                           -size, size, size,   size, size, size,   size, size, -size,         // Face 6
                           -size, size, size,   -size, size, -size,   size, size, -size};      // Face 6
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

    float normals[] = { 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
                        0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,
                        1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,
                        -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
                        0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
                        0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
                        0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,
                        1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,
                        -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
                        0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0};

    /*float colors[3 * 36];
    std::fill_n(colors, 3 * 36, 1.0);*/


    setVertices(vertices, 3 * 36);
    setColors(colors, 3 * 36);
    setVertexNormals(normals, 3 * 36);

    load();
}

TestCube::~TestCube()
{
    //dtor
}
