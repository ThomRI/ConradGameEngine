#include "TestTriangle.h"

TestTriangle::TestTriangle(int size) :
    StaticMesh(3)
{
    float vertices[3 * 3] = {-size, -size, 0.0,   size, -size, 0.0,  -size, size, 0.0};

    float colors[3 * 3];
    std::fill_n(colors, 3 * 3, 1.0);

    //float colors[] = {1.0, 0.0, 0.0,    0.0, 1.0, 0.0,  0.0, 0.0, 1.0};

    float tex[] = {0.0, 1.0,    1.0, 0.0,   1.0, 1.0};

    setVertices(vertices, 3*3);
    setColors(colors, 3*3);
    setTexCoords(tex, 3*2);

    AbstractTexture *texture = new AbstractTexture("textures/crate13.jpg");
    getMaterial()->setDiffuseTexture(texture);
    getMaterial()->getDiffuseTexture()->load();

    load();
}

TestTriangle::~TestTriangle()
{
    //dtor
}
