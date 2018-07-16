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

    Shader shader(string("shaders/basic/color3D.vert"), string("shaders/basic/color3D.frag"));
    app->getRenderer()->setShader(shader); // loads the shader

    TestCube *cube = new TestCube(2.5);
    app->getRenderer()->addMesh(cube);

    app->loop(1000); // 60 fps

    return 0;
}
