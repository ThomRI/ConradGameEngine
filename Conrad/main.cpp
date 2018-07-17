#include <iostream>
#include "Application.h"
#include "Shader.h"
#include "TestCube.h"

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

    app->loop(120); // 120 fps

    return 0;
}
