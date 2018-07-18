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
    /*float colors[] = {  1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
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
                        1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0};*/
    float colors[3 * 36];
    std::fill_n(colors, 3 * 36, 1.0);

    float tex[] = {0, 0,   1, 0,   1, 1,     // Face 1
                   0, 0,   0, 1,   1, 1,     // Face 1

                   0, 0,   1, 0,   1, 1,     // Face 2
                   0, 0,   0, 1,   1, 1,     // Face 2

                   0, 0,   1, 0,   1, 1,     // Face 3
                   0, 0,   0, 1,   1, 1,     // Face 3

                   0, 0,   1, 0,   1, 1,     // Face 4
                   0, 0,   0, 1,   1, 1,     // Face 4

                   0, 0,   1, 0,   1, 1,     // Face 5
                   0, 0,   0, 1,   1, 1,     // Face 5

                   0, 0,   1, 0,   1, 1,     // Face 6
                   0, 0,   0, 1,   1, 1};    // Face 6


    setVertices(vertices, 3 * 36);
    setColors(colors, 3 * 36);
    if(!setTexCoords(tex, 2 * 36)) {
        std::cout << "Error setting tex coords" << std::endl;
    }

    AbstractTexture *texture = new AbstractTexture("textures/crate13.jpg");
    if(!setTexture(texture)) {
        std::cout << "Error loading texture : " << SDL_GetError() << std::endl;
    }

    load();
}

TestCube::~TestCube()
{
    //dtor
}
