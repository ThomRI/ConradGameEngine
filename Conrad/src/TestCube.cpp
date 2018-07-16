#include "TestCube.h"

using namespace std;

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
    float colors[36 * 3] = {0.0};

    cout << "Cube size : " << 36 * 3 * sizeof(float) << endl;

    if(!setVertices(vertices, 3 * 36) || !setColors(colors, 3 * 36)) {
        cout << "Error updating vertices or colors" << endl;
    }

    load();
}

TestCube::~TestCube()
{
    //dtor
}
