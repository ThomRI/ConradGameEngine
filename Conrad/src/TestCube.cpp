#include "TestCube.h"

TestCube::TestCube(float size) :
    StaticMesh(36) // 36 vertices as for 6 (2 triangles) per faces and 6 faces
{
    float vertices[] = {-size, -size, size,  -size, -size, -size,   size, -size, -size, // FRONT DOWN
                        size, -size, size,   size, -size, size,     -size, -size, size, // FRONT UP

                        size, -size, size,  -size, size, size,  -size, -size, size,     // UP DOWN
                        size, -size, size,  size, size, size,   -size, size, size,      // UP UP

                        size, -size, -size,  size, size, -size,  size, size, size,      // RIGHT DOWN
                        size, -size, -size,  size, -size, size,  size, size, size,      // RIGHT UP

                        -size, -size, -size,  -size, size, -size,   -size, size, size,  // LEFT DOWN
                        -size, -size, -size,  -size, -size, size,   -size, size, size,  // LEFT UP

                        size, size, -size,  -size, size, -size,     -size, size, size,  // BACK DOWN
                        size, size, -size,  size, size, size,       -size, size, size,  // BACK UP

                        size, -size, -size,  -size, -size, -size,  -size, size, -size,  // DOWN DOWN
                        size, -size, -size,  size, size, -size,    -size, size, -size}; // DOWN UP

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

    float tex[] = { 0.0, 0.0,   0.0, 1.0,   1.0, 0.0,
                    0.0, 1.0,   1.0, 1.0,   1.0, 0.0,

                    0.0, 0.0,   0.0, 1.0,   1.0, 0.0,
                    0.0, 1.0,   1.0, 1.0,   1.0, 0.0,

                    0.0, 0.0,   0.0, 1.0,   1.0, 0.0,
                    0.0, 1.0,   1.0, 1.0,   1.0, 0.0,

                    0.0, 0.0,   0.0, 1.0,   1.0, 0.0,
                    0.0, 1.0,   1.0, 1.0,   1.0, 0.0,

                    0.0, 0.0,   0.0, 1.0,   1.0, 0.0,
                    0.0, 1.0,   1.0, 1.0,   1.0, 0.0,

                    0.0, 0.0,   0.0, 1.0,   1.0, 0.0,
                    0.0, 1.0,   1.0, 1.0,   1.0, 0.0};


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
