#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "TestCube.h"
#include "TestTriangle.h"
#include "utilities.hpp"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;

    Application *app = new Application("Sexer", 640, 480);
    if(!app->init()) {
        cout << "Error setting up SDL or context" << endl;
    }

    Shader shader(string("shaders/basic/texture.vert"), string("shaders/basic/texture.frag"));
    app->getRenderer()->setShader(shader); // loads the shader


    TestCube *cube = new TestCube(1.0);
    app->getRenderer()->addMesh(cube);

    /*StaticMesh *mesh = loadOBJ_static("cube.obj", false);
    AbstractTexture *texture = new AbstractTexture("textures/crate13.jpg");
    //float tex[6] = {1.0, 0.0,   0.0, 1.0,   0.0, 0.0};

    mesh->setTexture(texture);

    mesh->load();
    app->getRenderer()->addMesh(mesh);*/

    /*TestTriangle *triangle = new TestTriangle(2.0);
    app->getRenderer()->addMesh(triangle);*/

    app->loop(120); // 120 fps

    return 0;
}
